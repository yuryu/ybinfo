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
// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__CF244373_8410_471E_B7B4_1216C0BA68CD__INCLUDED_)
#define AFX_STDAFX_H__CF244373_8410_471E_B7B4_1216C0BA68CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// Argument could be zero.
#pragma warning(disable: 6387)

#include "targetver.h"

#pragma warning(push)

// WTL/ATL related warnings
#pragma warning(disable: 26110 26454 26812 6001)

#include <atlbase.h>
#include <atlstr.h>
#include <wtl/atlapp.h>

#include <wtl/atlmisc.h>
#include <wtl/atlctrls.h>
#include <wtl/atlctrlx.h>
#include <wtl/atlddx.h>
#include <wtl/atluser.h>
#include <wtl/atlgdi.h>

#pragma warning(pop)

#include <initguid.h>
#include <batclass.h>

#include <winioctl.h>
#include <initguid.h>
#include <setupapi.h>

#include <crtdbg.h>

#include <vector>
#include <cstdlib>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STDAFX_H__CF244373_8410_471E_B7B4_1216C0BA68CD__INCLUDED_)
