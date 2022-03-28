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
// YBattery.cpp: CYBattery クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "YbInfo.h"
#include "YBattery.h"

#include "resource.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CYBattery::CYBattery()
{
	m_hBattery = NULL;
}

CYBattery::~CYBattery()
{
	CloseIfOpen();
}


bool CYBattery::GetBatteryInformation(BATTERY_INFORMATION &batInfo)
{
	BATTERY_QUERY_INFORMATION batQueryInfo;
	BOOL bSucceeded;
	DWORD dwBytesReturned;

	batQueryInfo.BatteryTag = m_ulBatTag;
	batQueryInfo.InformationLevel = BatteryInformation;
	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), &batInfo, sizeof(batInfo),
					&dwBytesReturned, NULL);
	ATLTRACE(_T("error = %d\n"), GetLastError());
	return !bSucceeded;
		
}

bool CYBattery::Open(const CString &csBatDevice)
{
	CloseIfOpen();
	m_hBattery = CreateFile(csBatDevice, GENERIC_READ, 
						FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if(m_hBattery == INVALID_HANDLE_VALUE){
		m_hBattery = NULL;
		return false;
	}
	return Update();
}

bool CYBattery::CloseIfOpen()
{
	if(m_hBattery){
		CloseHandle(m_hBattery);
		m_hBattery = NULL;
		return true;
	}
	return false;
}

ULONG CYBattery::GetNewTag()
{
	ULONG ulWait = 5000;
	ULONG ulTag;
	DWORD dwBytesReturned;

	BOOL bResult;
	bResult = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_TAG, &ulWait, sizeof(ULONG),
					&ulTag, sizeof(ULONG), &dwBytesReturned, NULL);
	if(bResult == FALSE){
		m_ulBatTag = 0;
		return 0;
	}
	m_ulBatTag = ulTag;
	return ulTag;
}


//DEL ULONG CYBattery::GetTemperature()
//DEL {
//DEL 	ULONG batTemp;
//DEL 	BATTERY_QUERY_INFORMATION batQueryInfo;
//DEL 	BOOL bSucceeded;
//DEL 	DWORD dwBytesReturned;
//DEL 
//DEL 	batQueryInfo.InformationLevel = BatteryTemperature;
//DEL 	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
//DEL 					&batQueryInfo, sizeof(batQueryInfo), &batTemp, sizeof(batTemp),
//DEL 					&dwBytesReturned, NULL);
//DEL 	if(bSucceeded){
//DEL 		return batTemp;
//DEL 	}else{
//DEL 		return 0;
//DEL 	}
//DEL }

bool CYBattery::Update()
{
	if(GetNewTag() == 0){
		return false;
	}

	BATTERY_QUERY_INFORMATION batQueryInfo;
	BOOL bSucceeded;
	DWORD dwBytesReturned;

	batQueryInfo.BatteryTag = m_ulBatTag;

	batQueryInfo.InformationLevel = BatteryManufactureName;
	QueryString(batQueryInfo, m_csManufactureName);

	batQueryInfo.InformationLevel = BatteryDeviceName;
	QueryString(batQueryInfo, m_csDeviceName);

	batQueryInfo.InformationLevel = BatterySerialNumber;
	QueryString(batQueryInfo, m_csSerialNumber);

	batQueryInfo.InformationLevel = BatteryUniqueID;
	QueryString(batQueryInfo, m_csUniqueId);

	batQueryInfo.InformationLevel = BatteryManufactureDate;
	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), &m_manufactureDate, sizeof(m_manufactureDate),
					&dwBytesReturned, NULL);
	if(bSucceeded){
		// nothing to do
	}else{
		ZeroMemory(&m_manufactureDate, sizeof(m_manufactureDate));
	}

	batQueryInfo.InformationLevel = BatteryEstimatedTime;
	batQueryInfo.AtRate = 0;
	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), &m_ulEstimatedTime, sizeof(ULONG),
					&dwBytesReturned, NULL);
	if(bSucceeded){
		// nothing to do
	}else{
		m_ulEstimatedTime = BATTERY_UNKNOWN_TIME;
	}

	batQueryInfo.InformationLevel = BatteryTemperature;
	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), &m_ulTemperature, sizeof(ULONG),
					&dwBytesReturned, NULL);
	if(bSucceeded){
		// nothing to do
	}else{
		m_ulTemperature = 0;
	}

	return true;

}

bool CYBattery::QueryString(BATTERY_QUERY_INFORMATION& batQueryInfo, CString& csOutStr)
{
	wchar_t wszStrTemp[200];
	BOOL bSucceeded = FALSE;
	DWORD dwBytesReturned = 0;

	ZeroMemory(wszStrTemp, sizeof(wszStrTemp));
	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), wszStrTemp, sizeof(wszStrTemp),
					&dwBytesReturned, NULL);
	if(bSucceeded){
		csOutStr = CString(wszStrTemp);
	}else{
		csOutStr.LoadString(IDS_UNKNOWN);
	}
	return !bSucceeded;

}

bool CYBattery::GetBatteryStatus(BATTERY_STATUS &batStat)
{
	BATTERY_WAIT_STATUS batWaitStatus;
	DWORD dwBytesReturned;
	
	batWaitStatus.BatteryTag = m_ulBatTag;
	batWaitStatus.Timeout = 0;
	BOOL bSucceeded;
	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_STATUS, 
				&batWaitStatus, sizeof(batWaitStatus),
				&batStat, sizeof(batStat), &dwBytesReturned, NULL);

	return !bSucceeded;

}
