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

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CYBatteries::CYBatteries()
{
	HDEVINFO hBatDevInfo= 
			SetupDiGetClassDevs(&GUID_DEVICE_BATTERY, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

	int nIndex = 0, nNumberOfBatteries = 0;
	for(;;){
		BOOL bEnumDev;
		SP_DEVICE_INTERFACE_DATA devInterfaceData;
		devInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		bEnumDev = SetupDiEnumDeviceInterfaces(hBatDevInfo, NULL, &GUID_DEVICE_BATTERY, nIndex, &devInterfaceData);
		// FIXED A BUG 06/07/2004
		// it was trying to get device information even when SetupDi... fails.
		if(bEnumDev){
			// add battery when successful
			DWORD reqSize;
			SetupDiGetDeviceInterfaceDetail(hBatDevInfo, &devInterfaceData, NULL, 0, &reqSize, NULL);

			PSP_DEVICE_INTERFACE_DETAIL_DATA pDevDetailData;
			pDevDetailData = reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(std::malloc(reqSize));
			pDevDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			SetupDiGetDeviceInterfaceDetail(hBatDevInfo, &devInterfaceData, pDevDetailData, reqSize, NULL, NULL);
			CString csDevicePath = pDevDetailData->DevicePath;
			std::free(pDevDetailData);
			CYBattery* pcyBattery = new CYBattery;
			pcyBattery->Open(csDevicePath);
			m_vcpBatteries.push_back(pcyBattery);
			nNumberOfBatteries++;
		}else{
			// FIXED A BUG 06/06/2004, where batteries are not correctly detected
			// according to the SDK document, we must double-check with GetLastError()
			// because there are some cases that SetupDiEnumDeviceInterface fails due to different reasons
			if(GetLastError() == ERROR_NO_MORE_ITEMS){
				break;
			}
		}
		nIndex++;
	}
	SetupDiDestroyDeviceInfoList(hBatDevInfo);
	m_nBatteries = nNumberOfBatteries;
	
}

CYBatteries::~CYBatteries()
{
	while(m_nBatteries--){
		delete m_vcpBatteries[m_nBatteries];
		m_vcpBatteries.pop_back();
	}
}
