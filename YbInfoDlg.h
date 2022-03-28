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

#include "StdAfx.h"

#include "resource.h"
#include "YBatteries.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CYbInfoDlg ダイアログ

class CYbInfoDlg : public CDialogImpl<CYbInfoDlg>, public CWinDataExchange<CYbInfoDlg>, public CMessageFilter
{
// 構築
public:
	void UpdateBatteryInformation();
	CYBatteries m_cyBatteries;
	CYbInfoDlg();	// 標準のコンストラクタ
	virtual BOOL PreTranslateMessage(MSG* pMsg);


// ダイアログ データ
	//{{AFX_DATA(CYbInfoDlg)
	enum { IDD = IDD_YBINFO_DIALOG };
	CButton	m_cbOk;
	CButton	m_cbUpdate;
	CProgressBarCtrl	m_pCapacity;
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
	CUpDownCtrl m_spAutoUpdate;
	int m_iAutoUpdate;
	CEdit m_eAutoUpdate;
	//}}AFX_DATA

// インプリメンテーション
	HICON m_hIcon;
	CString m_csUnknown;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CYbInfoDlg)
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnQueryDragIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHelp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnBUpdate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSelendokCbBatterylist(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEnChangeEAutoupdate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	void OpenAboutDialog();
	void CloseDialog(int nVal);

	static constexpr UINT_PTR AutoUpdateTimerId = 5783;

	BEGIN_DDX_MAP(CYbInfoDlg)
		DDX_CONTROL_HANDLE(IDOK, m_cbOk);
		DDX_CONTROL_HANDLE(IDC_B_UPDATE, m_cbUpdate);
		DDX_CONTROL_HANDLE(IDC_P_CAPACITY, m_pCapacity);
		DDX_CONTROL_HANDLE(IDC_CB_BATTERYLIST, m_cbBatteryList);
		DDX_TEXT(IDC_E_MANUFACTURENAME, m_csManufactureName);
		DDX_TEXT(IDC_E_UNIQUEID, m_csUniqueId);
		DDX_TEXT(IDC_E_DEVICENAME, m_csDeviceName);
		DDX_TEXT(IDC_E_MANUFACTUREDATE, m_csManufactureDate);
		DDX_COMBO_INDEX(IDC_CB_BATTERYLIST, m_nSelectedBattery);
		DDX_TEXT(IDC_E_SERIALNUMBER, m_csSerialNumber);
		DDX_TEXT(IDC_E_CURRENTCAPACITY, m_csCurrentCapacity);
		DDX_TEXT(IDC_E_CURRENTFULLCAPACITY, m_csFullChargedCapacity);
		DDX_TEXT(IDC_E_DESIGNEDCAPACITY, m_csDesignedCapacity);
		DDX_TEXT(IDC_E_VOLTAGE, m_csVoltage);
		DDX_CHECK(IDC_C_RELATIVE, m_bRelativeCapacity);
		DDX_CHECK(IDC_C_SHORTTERM, m_bShortTerm);
		DDX_CHECK(IDC_C_SYSTEMBATTERY, m_bSystemBattery);
		DDX_CHECK(IDC_C_CHARGEABLE, m_bChargeable);
		DDX_TEXT(IDC_E_STATUS, m_csStatus);
		DDX_TEXT(IDC_E_CYCLECOUNT, m_csCycleCount);
		DDX_TEXT(IDC_E_RATE, m_csRate);
		DDX_TEXT(IDC_E_CHEMCODE, m_csChemistryCode);
		DDX_TEXT(IDC_E_LOWCAPACITY, m_csLowCapacity);
		DDX_TEXT(IDC_E_WARNCAPACITY, m_csWarnCapacity);
		DDX_TEXT(IDC_E_ESTIMATEDTIME, m_csEstimatedTime);
		DDX_TEXT(IDC_E_TEMPERATURE, m_csTemperature);
		DDX_CONTROL_HANDLE(IDC_SPIN_AUTOUPDATE, m_spAutoUpdate);
		DDX_INT_RANGE(IDC_E_AUTOUPDATE, m_iAutoUpdate, 0, INT_MAX);
		DDX_CONTROL_HANDLE(IDC_E_AUTOUPDATE, m_eAutoUpdate);
	END_DDX_MAP()

	BEGIN_MSG_MAP(CYbInfoDlg)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_QUERYDRAGICON, OnQueryDragIcon)
		MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_HELP, OnHelp)
		COMMAND_HANDLER(IDC_B_UPDATE, BN_CLICKED, OnBUpdate)
		COMMAND_HANDLER(IDC_CB_BATTERYLIST, CBN_SELENDOK, OnSelendokCbBatterylist)
		COMMAND_HANDLER(IDC_E_AUTOUPDATE, EN_CHANGE, OnEnChangeEAutoupdate)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_YBINFODLG_H__EE768B2C_D747_4A2F_8191_C711CC4E966E__INCLUDED_)
