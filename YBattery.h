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
	ULONG m_ulTemperature;
	ULONG m_ulEstimatedTime;
	bool GetBatteryStatus(BATTERY_STATUS& batStat);
	CString m_csUniqueId;
	CString m_csSerialNumber;
	bool Update();
	BATTERY_MANUFACTURE_DATE m_manufactureDate;
	CString m_csManufactureName;
	CString m_csDeviceName;
	ULONG GetNewTag();
	bool Open(const CString& csBatDevice);
	bool GetBatteryInformation(BATTERY_INFORMATION& batInfo);
	CYBattery();
	virtual ~CYBattery();

private:
	bool QueryString(BATTERY_QUERY_INFORMATION& batQueryInfo, CString& csOutStr);
	ULONG m_ulBatTag;
	bool CloseIfOpen();
	HANDLE m_hBattery;
};

#endif // !defined(AFX_YBATTERY_H__D9369154_8921_47BE_8B46_8BA9DE7BD304__INCLUDED_)
