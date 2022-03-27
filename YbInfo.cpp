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
// YbInfo.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "YbInfo.h"
#include "YbInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYbInfoApp

BEGIN_MESSAGE_MAP(CYbInfoApp, CWinApp)
	//{{AFX_MSG_MAP(CYbInfoApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYbInfoApp クラスの構築

CYbInfoApp::CYbInfoApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CYbInfoApp オブジェクト

CYbInfoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CYbInfoApp クラスの初期化

BOOL CYbInfoApp::InitInstance()
{
	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

	// checking if running on Windows 2000 or later
	if(!IsRunningOnWin2kOrLater()){
		AfxMessageBox(IDS_ERR_REQWIN2K, MB_ICONSTOP | MB_OK);
		return FALSE;
	}

	CYbInfoDlg dlg;
	m_pMainWnd = &dlg;

	if(dlg.m_cyBatteries.m_nBatteries == 0){
		AfxMessageBox(IDS_ERR_NOBATTERIES);
//		return FALSE;
	}

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
		//       記述してください。
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

bool CYbInfoApp::IsRunningOnWin2kOrLater()
{
	OSVERSIONINFO osVerInfo;

	osVerInfo.dwOSVersionInfoSize = sizeof(osVerInfo);
	GetVersionEx(&osVerInfo);
	
	// check if running under win2k or later
	// **BUG** doesn't detect correctly under some circumstances
	// more specific reports are needed
	bool isNt = osVerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT;
	bool is2kOrLater = osVerInfo.dwMajorVersion >= 5;

	return isNt && is2kOrLater;

}
