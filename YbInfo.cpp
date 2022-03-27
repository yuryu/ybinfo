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
// YbInfo.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYbInfoApp �N���X�̍\�z

CYbInfoApp::CYbInfoApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CYbInfoApp �I�u�W�F�N�g

CYbInfoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CYbInfoApp �N���X�̏�����

BOOL CYbInfoApp::InitInstance()
{
	AfxEnableControlContainer();

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

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
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <��ݾ�> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
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
