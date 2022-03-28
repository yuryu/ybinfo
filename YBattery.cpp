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

CYBattery::CYBattery():
	m_hBattery(nullptr),
	m_ulBatTag(0)
{
}

CYBattery::~CYBattery()
{
	CloseIfOpen();
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
	return true;
}

bool CYBattery::CloseIfOpen()
{
	if(m_hBattery){
		::CloseHandle(m_hBattery);
		m_hBattery = nullptr;
		return true;
	}
	return false;
}

ULONG CYBattery::GetNewTag()
{
	ULONG ulWait = 5000;
	ULONG ulTag;
	DWORD dwBytesReturned;

	BOOL bResult = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_TAG, &ulWait, sizeof(ULONG),
					&ulTag, sizeof(ULONG), &dwBytesReturned, NULL);
	if(!bResult){
		m_ulBatTag = 0;
		return 0;
	}
	m_ulBatTag = ulTag;
	return ulTag;
}

bool CYBattery::QueryInfoString(const BATTERY_QUERY_INFORMATION_LEVEL level, const CStringW& csPlaceholder, CStringW& csOutStr)
{
	wchar_t wszStrTemp[200] = { 0 };
	const auto bSucceeded = QueryInfo(level, wszStrTemp);
	if (bSucceeded) {
		csOutStr = CStringW(std::move(wszStrTemp));
	} else {
		csOutStr = csPlaceholder;
	}
	return bSucceeded;
}

bool CYBattery::QueryStatus(BATTERY_STATUS &batStat)
{
	BATTERY_WAIT_STATUS batWaitStatus;
	DWORD dwBytesReturned;
	
	batWaitStatus.BatteryTag = m_ulBatTag;
	batWaitStatus.Timeout = 0;
	const BOOL bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_STATUS, 
				&batWaitStatus, sizeof(batWaitStatus),
				&batStat, sizeof(batStat), &dwBytesReturned, nullptr);
	return bSucceeded;
}
