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

#include "stdafx.h"
#include "AboutDlg.h"
#include "YbInfo.h"

#include <atlstr.h>
#include <commctrl.h>
#include <shellapi.h>

CAboutDlg::CAboutDlg()
{
}

LRESULT CAboutDlg::OnInitDialog([[maybe_unused]] UINT uMsg, [[maybe_unused]] WPARAM wParam, [[maybe_unused]] LPARAM lParam, [[maybe_unused]] BOOL& bHandled)
{
	const auto hInstance = _Module.GetResourceInstance();
	if (const auto hSource = ::FindResource(hInstance, MAKEINTRESOURCE(IDR_ACKNOWLEDGEMENTS), RT_RCDATA)) {
		if (const auto hData = ::LoadResource(hInstance, hSource)) {
			// acknowledgements.txt is ASCII with CRLF line endings, enforced
			// by .gitattributes, and is embedded verbatim by the resource
			// compiler.
			const CStringA csAcknowledgementsA(static_cast<const char*>(::LockResource(hData)),
				static_cast<int>(::SizeofResource(hInstance, hSource)));
			SetDlgItemText(IDC_E_ACKNOWLEDGEMENTS, CString(csAcknowledgementsA));
		}
	}
	return TRUE;
}

LRESULT CAboutDlg::OnCloseCmd([[maybe_unused]] WORD wNotifyCode, WORD wID, [[maybe_unused]] HWND hWndCtl, [[maybe_unused]] BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CAboutDlg::OnLicenseLink([[maybe_unused]] int idCtrl, LPNMHDR pnmh, [[maybe_unused]] BOOL& bHandled)
{
	const auto pLink = reinterpret_cast<const NMLINK*>(pnmh);
	::ShellExecute(nullptr, _T("open"), pLink->item.szUrl, nullptr, nullptr, SW_SHOWNORMAL);
	return 0;
}
