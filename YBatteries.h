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
