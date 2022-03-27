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
// YbInfoDlg.h : ヘッダー ファイル
//

#if !defined(AFX_YBINFODLG_H__EE768B2C_D747_4A2F_8191_C711CC4E966E__INCLUDED_)
#define AFX_YBINFODLG_H__EE768B2C_D747_4A2F_8191_C711CC4E966E__INCLUDED_

#include "YBatteries.h"
#include "afxwin.h"
#include "afxcmn.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CYbInfoDlg ダイアログ

class CYbInfoDlg : public CDialog
{
// 構築
public:
	void UpdateBatteryInformation();
	CYBatteries m_cyBatteries;
	CYbInfoDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CYbInfoDlg)
	enum { IDD = IDD_YBINFO_DIALOG };
	CButton	m_cbOk;
	CButton	m_cbUpdate;
	CProgressCtrl	m_pCapacity;
	CComboBox	m_cbBatteryList;
	CString	m_csManufactureName;
	CString	m_csUniqueId;
	CString	m_csDeviceName;
	CString	m_csManufactureDate;
	int		m_nSelectedBattery;
	CString	m_csSerialNumber;
	CString	m_csCurrentCapacity;
	CString	m_csFullChargedCapacity;
	CString	m_csDesignedCapacity;
	CString	m_csVoltage;
	BOOL	m_bRelativeCapacity;
	BOOL	m_bShortTerm;
	BOOL	m_bSystemBattery;
	BOOL	m_bChargeable;
	CString	m_csStatus;
	CString	m_csCycleCount;
	CString	m_csRate;
	CString	m_csChemistryCode;
	CString	m_csLowCapacity;
	CString	m_csWarnCapacity;
	CString	m_csEstimatedTime;
	CString	m_csTemperature;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CYbInfoDlg)
	public:
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CYbInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUpdate();
	afx_msg void OnSelendokCbBatterylist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CSpinButtonCtrl m_spAutoUpdate;
	int m_iAutoUpdate;
	CEdit m_eAutoUpdate;
public:
	afx_msg void OnEnChangeEAutoupdate();
public:
	afx_msg void OnTimer(UINT nIDEvent);

protected:
	static const UINT AutoUpdateTimerId = 5783;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_YBINFODLG_H__EE768B2C_D747_4A2F_8191_C711CC4E966E__INCLUDED_)
