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

CAppModule _Module;

int Run([[maybe_unused]] PTSTR pCmdLine, [[maybe_unused]] int nCmdShow) {
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CYbInfoDlg dlg;
	if (dlg.m_cyBatteries.Count() == 0) {
		AtlMessageBox(nullptr, IDS_ERR_NOBATTERIES);
	}
	if (!dlg.Create(nullptr)) {
		ATLTRACE(_T("Dialog creation failed"));
		return EXIT_FAILURE;
	}
	dlg.ShowWindow(nCmdShow);
	const auto nRet = theLoop.Run();
	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain([[maybe_unused]] HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow) {
	auto hRes = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	::DefWindowProc(nullptr, 0, 0, 0);

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES | ICC_STANDARD_CLASSES | ICC_PROGRESS_CLASS | ICC_UPDOWN_CLASS | ICC_LINK_CLASS);

	hRes = _Module.Init(nullptr, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	const auto nRet = Run(pCmdLine, nCmdShow);

	_Module.Term();

	::CoUninitialize();
	return nRet;
}
