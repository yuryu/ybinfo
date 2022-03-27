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
