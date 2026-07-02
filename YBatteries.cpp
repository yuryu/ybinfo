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
	const HDEVINFO hRawDevInfo = ::SetupDiGetClassDevs(&GUID_DEVICE_BATTERY, nullptr, nullptr, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if(hRawDevInfo == INVALID_HANDLE_VALUE){
		return;
	}
	const std::unique_ptr<std::remove_pointer<HDEVINFO>::type, decltype(&::SetupDiDestroyDeviceInfoList)> hBatDevInfo(
		hRawDevInfo, ::SetupDiDestroyDeviceInfoList);

	// device interface indices are not guaranteed to be contiguous, so failures
	// other than ERROR_NO_MORE_ITEMS don't end the enumeration; the index cap
	// keeps a persistent error from looping forever
	for(DWORD nIndex = 0; nIndex < MaxBatteries; nIndex++){
		SP_DEVICE_INTERFACE_DATA devInterfaceData;
		devInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		const BOOL bEnumDev = ::SetupDiEnumDeviceInterfaces(hBatDevInfo.get(), nullptr, &GUID_DEVICE_BATTERY, nIndex, &devInterfaceData);
		if(!bEnumDev){
			if(::GetLastError() == ERROR_NO_MORE_ITEMS){
				break;
			}
			continue;
		}

		DWORD reqSize = 0;
		::SetupDiGetDeviceInterfaceDetail(hBatDevInfo.get(), &devInterfaceData, nullptr, 0, &reqSize, nullptr);
		if(::GetLastError() != ERROR_INSUFFICIENT_BUFFER){
			continue;
		}

		const auto pDetailBuffer = std::make_unique<std::byte[]>(reqSize);
		const auto pDevDetailData = reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(pDetailBuffer.get());
		// cbSize must always be the fixed length of the struct.
		pDevDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		if(!::SetupDiGetDeviceInterfaceDetail(hBatDevInfo.get(), &devInterfaceData, pDevDetailData, reqSize, nullptr, nullptr)){
			continue;
		}

		auto pcyBattery = std::make_unique<CYBattery>(pDevDetailData->DevicePath);
		if (pcyBattery->Open()) {
			m_vcpBatteries.push_back(std::move(pcyBattery));
		}
	}
}
