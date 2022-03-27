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

// YBatteries.h: CYBatteries クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_YBATTERIES_H__2020652B_477C_4953_9B0D_AFFC64BDE37B__INCLUDED_)
#define AFX_YBATTERIES_H__2020652B_477C_4953_9B0D_AFFC64BDE37B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CYBattery;

class CYBatteries  
{
public:
	int m_nBatteries;
	std::vector<CYBattery*> m_vcpBatteries;

	CYBatteries();
	virtual ~CYBatteries();

};

#endif // !defined(AFX_YBATTERIES_H__2020652B_477C_4953_9B0D_AFFC64BDE37B__INCLUDED_)
