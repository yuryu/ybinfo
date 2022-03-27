/*
    Yuryu's Battery Information, displays detailed battery info.
    Copyright (C) 2008 Yuryu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
