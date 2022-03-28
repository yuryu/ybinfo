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
// YBattery.h: CYBattery クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YBATTERY_H__D9369154_8921_47BE_8B46_8BA9DE7BD304__INCLUDED_)
#define AFX_YBATTERY_H__D9369154_8921_47BE_8B46_8BA9DE7BD304__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

class CYBattery  
{
public:
	CYBattery() = delete;
	CYBattery(LPCTSTR devicePath);
	~CYBattery();

	bool Open();
	bool QueryInfoString(const BATTERY_QUERY_INFORMATION_LEVEL level, const CStringW& csPlaceholder, CStringW& csOutStr);
	template <typename T> bool QueryInfo(const BATTERY_QUERY_INFORMATION_LEVEL level, T& out);
	bool QueryStatus(BATTERY_STATUS& batStat);
	ULONG GetNewTag();

private:
	bool CloseIfOpen();

	ULONG m_ulBatTag;
	HANDLE m_hBattery;
	const CString m_csDevicePath;
};

template<typename T>
bool CYBattery::QueryInfo(const BATTERY_QUERY_INFORMATION_LEVEL level, T& out)
{
	BATTERY_QUERY_INFORMATION batQueryInfo = {
		.BatteryTag = m_ulBatTag,
		.InformationLevel = level,
		.AtRate = 0,
	};
	DWORD dwBytesReturned;
	const BOOL bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
		&batQueryInfo, sizeof(batQueryInfo), &out, sizeof(out),
		&dwBytesReturned, nullptr);
	return bSucceeded;
}


#endif // !defined(AFX_YBATTERY_H__D9369154_8921_47BE_8B46_8BA9DE7BD304__INCLUDED_)
