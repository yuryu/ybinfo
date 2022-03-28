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
// YbInfoDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "YbInfo.h"
#include "YbInfoDlg.h"

#include "YBattery.h"
#include "YBInfoDlg.h"
#include "AboutDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CYbInfoDlg ダイアログ

CYbInfoDlg::CYbInfoDlg(): m_iAutoUpdate(0)
{
	//{{AFX_DATA_INIT(CYbInfoDlg)
	m_csManufactureName = _T("");
	m_csUniqueId = _T("");
	m_csDeviceName = _T("");
	m_csManufactureDate = _T("");
	m_nSelectedBattery = -1;
	m_csSerialNumber = _T("");
	m_csCurrentCapacity = _T("");
	m_csFullChargedCapacity = _T("");
	m_csDesignedCapacity = _T("");
	m_csVoltage = _T("");
	m_bRelativeCapacity = FALSE;
	m_bShortTerm = FALSE;
	m_bSystemBattery = FALSE;
	m_bChargeable = FALSE;
	m_csStatus = _T("");
	m_csCycleCount = _T("");
	m_csRate = _T("");
	m_csChemistryCode = _T("");
	m_csLowCapacity = _T("");
	m_csWarnCapacity = _T("");
	m_csEstimatedTime = _T("");
	m_csTemperature = _T("");
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = static_cast<HICON>(::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR));
	_ASSERT(m_hIcon);
	const BOOL bLoaded = m_csUnknown.LoadString(IDS_UNKNOWN);
	_ASSERT(bLoaded);
}

BOOL CYbInfoDlg::PreTranslateMessage(MSG* pMsg) {
	return ::IsDialogMessage(m_hWnd, pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CYbInfoDlg メッセージ ハンドラ

LRESULT CYbInfoDlg::OnInitDialog([[maybe_unused]] UINT uMsg, [[maybe_unused]] WPARAM wParam, [[maybe_unused]] LPARAM lParam, [[maybe_unused]] BOOL& bHandled)
{
	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	_ASSERTE((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	_ASSERTE(IDM_ABOUTBOX < 0xF000);

	CMenu pSysMenu(GetSystemMenu(FALSE));
	if (pSysMenu.IsMenu())
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu.AppendMenu(MF_SEPARATOR);
			pSysMenu.AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	pSysMenu.Detach();

	// register object for message filtering
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	_ASSERT(pLoop);
	pLoop->AddMessageFilter(this);

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	const HICON hIconSmall = static_cast<HICON>(::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR));
	SetIcon(hIconSmall, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	CenterWindow();

	DoDataExchange(DDX_LOAD);

	m_spAutoUpdate.SetRange(0, UD_MAXVAL);
	m_spAutoUpdate.SetBuddy(::GetDlgItem(m_hWnd, IDC_E_AUTOUPDATE));

	if(m_cyBatteries.m_nBatteries == 0){
		m_cbUpdate.EnableWindow(FALSE);
		m_cbUpdate.ModifyStyle(BS_DEFPUSHBUTTON, BS_PUSHBUTTON);
		m_cbOk.ModifyStyle(BS_PUSHBUTTON, BS_DEFPUSHBUTTON);
		return TRUE;
	}
	
	CWaitCursor waitCursor;
	m_cbBatteryList.Clear();
	for(int i = 0; i < m_cyBatteries.m_nBatteries; i++){
		CStringW csDeviceName;
		if (m_cyBatteries.m_vcpBatteries[i]->GetNewTag()) {
			m_cyBatteries.m_vcpBatteries[i]->QueryInfoString(BatteryDeviceName, m_csUnknown, csDeviceName);
		} else {
			csDeviceName = m_csUnknown;
		}
		CString csTemp;
		csTemp.Format(_T("%d: %s"), i, csDeviceName.GetString());
		m_cbBatteryList.AddString(std::move(csTemp));
	}
	m_nSelectedBattery = 0;
	waitCursor.Restore();
	UpdateBatteryInformation();

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

LRESULT CYbInfoDlg::OnSysCommand([[maybe_unused]] UINT uMsg, WPARAM wParam, [[maybe_unused]] LPARAM lParam, BOOL& bHandled)
{
	UINT nID = static_cast<UINT>(wParam);

	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		OpenAboutDialog();
	}
	else
	{
		bHandled = FALSE;
	}
	return 0;
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

LRESULT CYbInfoDlg::OnPaint([[maybe_unused]] UINT uMsg, [[maybe_unused]] WPARAM wParam, [[maybe_unused]] LPARAM lParam, BOOL& bHandled)
{
	if (IsIconic())
	{
		CPaintDC dc(m_hWnd); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) m_hWnd, 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		bHandled = false;
	}
	return 0;
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
LRESULT CYbInfoDlg::OnQueryDragIcon([[maybe_unused]] UINT uMsg, [[maybe_unused]] WPARAM wParam, [[maybe_unused]] LPARAM lParam, [[maybe_unused]] BOOL& bHandled)
{
	return reinterpret_cast<LRESULT>(m_hIcon);
}

LRESULT CYbInfoDlg::OnHelp([[maybe_unused]] UINT uMsg, [[maybe_unused]] WPARAM wParam, [[maybe_unused]] LPARAM lParam, [[maybe_unused]] BOOL& bHandled)
{
	OpenAboutDialog();
	return 0;
}

LRESULT CYbInfoDlg::OnBUpdate([[maybe_unused]] WORD wNotifyCode, [[maybe_unused]] WORD wID, [[maybe_unused]] HWND hWndCtl, [[maybe_unused]] BOOL& bHandled)
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateBatteryInformation();
	return 0;
}

LRESULT CYbInfoDlg::OnSelendokCbBatterylist([[maybe_unused]] WORD wNotifyCode, [[maybe_unused]] WORD wID, [[maybe_unused]] HWND hWndCtl, [[maybe_unused]] BOOL& bHandled)
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	DoDataExchange(DDX_SAVE);
	UpdateBatteryInformation();
	return 0;
}

void CYbInfoDlg::UpdateBatteryInformation()
{
	CYBattery* pcyBattery = m_cyBatteries.m_vcpBatteries[m_nSelectedBattery];

	if (!pcyBattery->GetNewTag()) {
		return;
	}
	pcyBattery->QueryInfoString(BatteryManufactureName, m_csUnknown, m_csManufactureName);
	pcyBattery->QueryInfoString(BatteryDeviceName, m_csUnknown, m_csDeviceName);
	pcyBattery->QueryInfoString(BatteryUniqueID, m_csUnknown, m_csUniqueId);
	pcyBattery->QueryInfoString(BatterySerialNumber, m_csUnknown, m_csSerialNumber);
	BATTERY_MANUFACTURE_DATE manufactureDate;
	if (pcyBattery->QueryInfo(BatteryManufactureDate, manufactureDate)) {
		m_csManufactureDate.Format(IDS_DATEFORMAT,
			manufactureDate.Year,
			manufactureDate.Month,
			manufactureDate.Day);
	} else {
		m_csManufactureDate = m_csUnknown;
	}

	BATTERY_INFORMATION batInfo;
	pcyBattery->QueryInfo(BatteryInformation, batInfo);
	BATTERY_STATUS batStat;
	pcyBattery->QueryStatus(batStat);

	UINT uCapFormat = IDS_CAPACITYFORMAT;
	if(batInfo.Capabilities & BATTERY_CAPACITY_RELATIVE){
		uCapFormat = IDS_RELCAPACITYFORMAT;
		m_bRelativeCapacity = TRUE;
	}

	m_bShortTerm = batInfo.Capabilities & BATTERY_IS_SHORT_TERM ? TRUE : FALSE;
	m_bSystemBattery = batInfo.Capabilities & BATTERY_SYSTEM_BATTERY ? TRUE : FALSE;
	m_bChargeable = batInfo.Technology ? TRUE : FALSE;
	
	m_csDesignedCapacity.Format(uCapFormat, batInfo.DesignedCapacity);
	m_csFullChargedCapacity.Format(uCapFormat, batInfo.FullChargedCapacity);
	m_csCurrentCapacity.Format(uCapFormat, batStat.Capacity);

	m_pCapacity.SetRange32(0, batInfo.FullChargedCapacity);
	m_pCapacity.SetPos(batStat.Capacity);

	m_csLowCapacity.Format(uCapFormat, batInfo.DefaultAlert1);
	m_csWarnCapacity.Format(uCapFormat, batInfo.DefaultAlert2);

	int iProgressColor = 0;
	if (batInfo.FullChargedCapacity) {
		iProgressColor = batStat.Capacity * 255 / batInfo.FullChargedCapacity;
	}
	m_pCapacity.SendMessage(PBM_SETBARCOLOR, 0,
		(LPARAM)RGB(255 - iProgressColor, iProgressColor, iProgressColor / 2));


	if(batStat.Voltage == BATTERY_UNKNOWN_VOLTAGE){
		m_csVoltage = m_csUnknown;
	}else{
		m_csVoltage.Format(IDS_VOLTAGEFORMAT, batStat.Voltage);
	}

	std::vector<CString> statusList;

	if(batStat.PowerState & BATTERY_POWER_ON_LINE){
		CString csTemp;
		csTemp.LoadString(IDS_STATPOWERONLINE);
		statusList.push_back(std::move(csTemp));
	}
	if(batStat.PowerState & BATTERY_DISCHARGING){
		CString csTemp;
		csTemp.LoadString(IDS_STATDISCHARGE);
		statusList.push_back(std::move(csTemp));
	}
	if(batStat.PowerState & BATTERY_CHARGING){
		CString csTemp;
		csTemp.LoadString(IDS_STATCHARGE);
		statusList.push_back(std::move(csTemp));
	}
	if(batStat.PowerState & BATTERY_CRITICAL){
		CString csTemp;
		csTemp.LoadString(IDS_STATCRITICAL);
		statusList.push_back(std::move(csTemp));
	}
	m_csStatus.Empty();
	for (auto& status: statusList)
	{
		if (!m_csStatus.IsEmpty()) {
			m_csStatus.AppendChar(_T(' '));
		}
		m_csStatus.Append(std::move(status));
	}

	if(batInfo.CycleCount){
		m_csCycleCount.Format(IDS_CYCLECOUNTFORMAT, batInfo.CycleCount);
	}else{
		m_csCycleCount = m_csUnknown;
	}
	if(batStat.Rate == BATTERY_UNKNOWN_RATE){
		m_csRate = m_csUnknown;
	}else{
		if(m_bRelativeCapacity){
			m_csRate.Format(IDS_RELRATEFORMAT, abs(batStat.Rate));
		}else{
			m_csRate.Format(IDS_RATEFORMAT, abs(batStat.Rate));
		}
	}

	m_csChemistryCode.Empty();
	for(int i = 0; i < 4; i++){
		if(batInfo.Chemistry[i] == 0){
			break;
		}
		m_csChemistryCode += batInfo.Chemistry[i];
	}
	
	ULONG ulEstimatedTime;
	if (pcyBattery->QueryInfo(BatteryEstimatedTime, ulEstimatedTime)) {
		m_csEstimatedTime.Format(IDS_TIMEFORMAT,
			ulEstimatedTime / 3600,
			ulEstimatedTime % 3600 / 60,
			ulEstimatedTime % 60);
	} else {
		m_csEstimatedTime = m_csUnknown;
	}

	ULONG ulTemperature;
	if(pcyBattery->QueryInfo(BatteryTemperature, ulTemperature)) {
		m_csTemperature.Format(IDS_TEMPFORMAT,
			ulTemperature / 10,
			ulTemperature % 10);
	}else{
		m_csTemperature = m_csUnknown;
	}

	DoDataExchange(DDX_LOAD);
}

LRESULT CYbInfoDlg::OnEnChangeEAutoupdate([[maybe_unused]] WORD wNotifyCode, [[maybe_unused]] WORD wID, [[maybe_unused]] HWND hWndCtl, [[maybe_unused]] BOOL& bHandled)
{
	// TODO :  これが RICHEDIT コントロールの場合、まず、CDialog::OnInitDialog() 関数をオーバーライドして、
	// OR 状態の ENM_CORRECTTEXT フラグをマスクに入れて、
	// CRichEditCtrl().SetEventMask() を呼び出さない限り、
	// コントロールは、この通知を送信しません。

	// TODO :  ここにコントロール通知ハンドラ コードを追加してください。
	if(m_eAutoUpdate.m_hWnd && m_eAutoUpdate.GetWindowTextLength() <= 0){
		return 0;
	}

	DoDataExchange(DDX_SAVE);
	KillTimer(AutoUpdateTimerId);
	if(m_iAutoUpdate){
		SetTimer(AutoUpdateTimerId, m_iAutoUpdate * 1000, NULL);
	}
	return 0;
}

LRESULT CYbInfoDlg::OnTimer([[maybe_unused]] UINT uMsg, WPARAM wParam, [[maybe_unused]] LPARAM lParam, BOOL& bHandled)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	const UINT_PTR nIDEvent = wParam;

	if(nIDEvent == AutoUpdateTimerId){
		UpdateBatteryInformation();
	}
	else {
		bHandled = FALSE;
	}
	return 0;
}

LRESULT CYbInfoDlg::OnOK([[maybe_unused]] WORD wNotifyCode, [[maybe_unused]] WORD wID, [[maybe_unused]] HWND hWndCtl, [[maybe_unused]] BOOL& bHandled)
{
	CloseDialog(0);
	return 0;
}

LRESULT CYbInfoDlg::OnCancel([[maybe_unused]] WORD wNotifyCode, [[maybe_unused]] WORD wID, [[maybe_unused]] HWND hWndCtl, [[maybe_unused]] BOOL& bHandled)
{
	CloseDialog(0);
	return 0;
}

void CYbInfoDlg::OpenAboutDialog() {
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CYbInfoDlg::CloseDialog(int nVal) {
	// unregister message filtering
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	_ASSERT(pLoop);
	pLoop->RemoveMessageFilter(this);
	DestroyWindow();
	::PostQuitMessage(nVal);
}
