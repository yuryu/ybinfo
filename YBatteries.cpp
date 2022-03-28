/*
 Yuryu's Battery Information, displays detailed battery info.

 Copyright 2008 Yuryu / Emma Haruka Iwao

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
// YBatteries.cpp: CYBatteries クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "YbInfo.h"
#include "YBatteries.h"

#include "YBattery.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CYBatteries::CYBatteries()
{
	std::unique_ptr<std::remove_pointer<HDEVINFO>::type, decltype(&::SetupDiDestroyDeviceInfoList)> hBatDevInfo(
		::SetupDiGetClassDevs(&GUID_DEVICE_BATTERY, nullptr, nullptr, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE),
		::SetupDiDestroyDeviceInfoList);

	int nNumberOfBatteries = 0;
	for(int nIndex = 0; ; nIndex++){
		SP_DEVICE_INTERFACE_DATA devInterfaceData;
		devInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		const BOOL bEnumDev = ::SetupDiEnumDeviceInterfaces(hBatDevInfo.get(), nullptr, &GUID_DEVICE_BATTERY, nIndex, &devInterfaceData);
		// FIXED A BUG 06/07/2004
		// it was trying to get device information even when SetupDi... fails.
		if(bEnumDev){
			// add battery when successful
			DWORD reqSize;
			::SetupDiGetDeviceInterfaceDetail(hBatDevInfo.get(), &devInterfaceData, nullptr, 0, &reqSize, nullptr);

			std::unique_ptr<SP_DEVICE_INTERFACE_DETAIL_DATA> pDevDetailData(
				reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(::operator new(reqSize)));
			// cbSize must always be the fixed length of the struct.
			pDevDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
			::SetupDiGetDeviceInterfaceDetail(hBatDevInfo.get(), &devInterfaceData, pDevDetailData.get(), reqSize, nullptr, nullptr);

			auto pcyBattery = std::make_unique<CYBattery>(pDevDetailData->DevicePath);
			if (pcyBattery->Open()) {
				m_vcpBatteries.push_back(std::move(pcyBattery));
				nNumberOfBatteries++;
			}
		}else{
			// FIXED A BUG 06/06/2004, where batteries are not correctly detected
			// according to the SDK document, we must double-check with GetLastError()
			// because there are some cases that SetupDiEnumDeviceInterface fails due to different reasons
			if(::GetLastError() == ERROR_NO_MORE_ITEMS){
				break;
			}
		}
	}
	m_nBatteries = nNumberOfBatteries;
}

CYBatteries::~CYBatteries()
{
}
