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
