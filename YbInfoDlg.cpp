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
// YbInfoDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "YbInfo.h"
#include "YbInfoDlg.h"

#include "YBattery.h"
#include "YBInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���Ă��� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// ���b�Z�[�W �n���h��������܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYbInfoDlg �_�C�A���O

CYbInfoDlg::CYbInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYbInfoDlg::IDD, pParent)
	, m_iAutoUpdate(0)
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
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYbInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYbInfoDlg)
	DDX_Control(pDX, IDOK, m_cbOk);
	DDX_Control(pDX, IDC_B_UPDATE, m_cbUpdate);
	DDX_Control(pDX, IDC_P_CAPACITY, m_pCapacity);
	DDX_Control(pDX, IDC_CB_BATTERYLIST, m_cbBatteryList);
	DDX_Text(pDX, IDC_E_MANUFACTURENAME, m_csManufactureName);
	DDX_Text(pDX, IDC_E_UNIQUEID, m_csUniqueId);
	DDX_Text(pDX, IDC_E_DEVICENAME, m_csDeviceName);
	DDX_Text(pDX, IDC_E_MANUFACTUREDATE, m_csManufactureDate);
	DDX_CBIndex(pDX, IDC_CB_BATTERYLIST, m_nSelectedBattery);
	DDX_Text(pDX, IDC_E_SERIALNUMBER, m_csSerialNumber);
	DDX_Text(pDX, IDC_E_CURRENTCAPACITY, m_csCurrentCapacity);
	DDX_Text(pDX, IDC_E_CURRENTFULLCAPACITY, m_csFullChargedCapacity);
	DDX_Text(pDX, IDC_E_DESIGNEDCAPACITY, m_csDesignedCapacity);
	DDX_Text(pDX, IDC_E_VOLTAGE, m_csVoltage);
	DDX_Check(pDX, IDC_C_RELATIVE, m_bRelativeCapacity);
	DDX_Check(pDX, IDC_C_SHORTTERM, m_bShortTerm);
	DDX_Check(pDX, IDC_C_SYSTEMBATTERY, m_bSystemBattery);
	DDX_Check(pDX, IDC_C_CHARGEABLE, m_bChargeable);
	DDX_Text(pDX, IDC_E_STATUS, m_csStatus);
	DDX_Text(pDX, IDC_E_CYCLECOUNT, m_csCycleCount);
	DDX_Text(pDX, IDC_E_RATE, m_csRate);
	DDX_Text(pDX, IDC_E_CHEMCODE, m_csChemistryCode);
	DDX_Text(pDX, IDC_E_LOWCAPACITY, m_csLowCapacity);
	DDX_Text(pDX, IDC_E_WARNCAPACITY, m_csWarnCapacity);
	DDX_Text(pDX, IDC_E_ESTIMATEDTIME, m_csEstimatedTime);
	DDX_Text(pDX, IDC_E_TEMPERATURE, m_csTemperature);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SPIN_AUTOUPDATE, m_spAutoUpdate);
	DDX_Text(pDX, IDC_E_AUTOUPDATE, m_iAutoUpdate);
	DDX_Control(pDX, IDC_E_AUTOUPDATE, m_eAutoUpdate);
}

BEGIN_MESSAGE_MAP(CYbInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CYbInfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_B_UPDATE, OnBUpdate)
	ON_CBN_SELENDOK(IDC_CB_BATTERYLIST, OnSelendokCbBatterylist)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_E_AUTOUPDATE, OnEnChangeEAutoupdate)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYbInfoDlg ���b�Z�[�W �n���h��

BOOL CYbInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���ڂ��V�X�e�� ���j���[�֒ǉ����܂��B

	// IDM_ABOUTBOX �̓R�}���h ���j���[�͈̔͂łȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	
	m_spAutoUpdate.SetRange(0, UD_MAXVAL);
	m_spAutoUpdate.SetBuddy(&m_eAutoUpdate);


	if(m_cyBatteries.m_nBatteries == 0){
		m_cbUpdate.EnableWindow(FALSE);
		m_cbUpdate.ModifyStyle(BS_DEFPUSHBUTTON, BS_PUSHBUTTON);
		m_cbOk.ModifyStyle(BS_PUSHBUTTON, BS_DEFPUSHBUTTON);
		return TRUE;
	}
	m_cbBatteryList.BeginWaitCursor();
	m_cbBatteryList.Clear();
	for(int i = 0; i < m_cyBatteries.m_nBatteries; i++){
		CString csTemp;
		csTemp.Format(_T("%d: %s"), i, m_cyBatteries.m_vcpBatteries[i]->m_csDeviceName);
		m_cbBatteryList.AddString(csTemp);
	}
	m_nSelectedBattery = 0;
	m_cbBatteryList.EndWaitCursor();
	UpdateBatteryInformation();

	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

void CYbInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CYbInfoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CYbInfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CYbInfoDlg::OnBUpdate() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateBatteryInformation();
}

void CYbInfoDlg::OnSelendokCbBatterylist() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateData(TRUE);
	UpdateBatteryInformation();
	
}

void CYbInfoDlg::UpdateBatteryInformation()
{
	CYBattery* pcyBattery;

	pcyBattery = m_cyBatteries.m_vcpBatteries[m_nSelectedBattery];

	pcyBattery -> Update();
	m_csManufactureName = pcyBattery->m_csManufactureName;
	m_csDeviceName = pcyBattery->m_csDeviceName;
	m_csUniqueId = pcyBattery->m_csUniqueId;
	m_csSerialNumber = pcyBattery->m_csSerialNumber;
	if(pcyBattery->m_manufactureDate.Year == 0 &&
		pcyBattery->m_manufactureDate.Month == 0 &&
		pcyBattery->m_manufactureDate.Day == 0){
		m_csManufactureDate.LoadString(IDS_UNKNOWN);
	}else{
		m_csManufactureDate.Format(IDS_DATEFORMAT,
			pcyBattery->m_manufactureDate.Year,
			pcyBattery->m_manufactureDate.Month,
			pcyBattery->m_manufactureDate.Day);
	}

	BATTERY_INFORMATION batInfo;
	pcyBattery->GetBatteryInformation(batInfo);
	BATTERY_STATUS batStat;
	pcyBattery->GetBatteryStatus(batStat);

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

	int iProgressColor = batStat.Capacity * 255 / batInfo.FullChargedCapacity;
	m_pCapacity.SendMessage(PBM_SETBARCOLOR, 0,
		(LPARAM)RGB(255 - iProgressColor, iProgressColor, iProgressColor / 2));

/*
	CString csCapPerTemp;
	csCapPerTemp.Format(IDS_CAPPERFORMAT, batStat.Capacity * 100 / batInfo.FullChargedCapacity);
*/

	if(batStat.Voltage == BATTERY_UNKNOWN_VOLTAGE){
		m_csVoltage.LoadString(IDS_UNKNOWN);
	}else{
		m_csVoltage.Format(IDS_VOLTAGEFORMAT, batStat.Voltage);
	}

	CString csTemp;
	m_csStatus.Empty();
	if(batStat.PowerState & BATTERY_POWER_ON_LINE){
		csTemp.LoadString(IDS_STATPOWERONLINE);
		m_csStatus += csTemp;
	}
	if(batStat.PowerState & BATTERY_DISCHARGING){
		csTemp.LoadString(IDS_STATDISCHARGE);
		if(m_csStatus.IsEmpty()){
			m_csStatus += csTemp;
		}else{
			m_csStatus += " ";
			m_csStatus += csTemp;
		}
	}
	if(batStat.PowerState & BATTERY_CHARGING){
		csTemp.LoadString(IDS_STATCHARGE);
		if(m_csStatus.IsEmpty()){
			m_csStatus += csTemp;
		}else{
			m_csStatus += " ";
			m_csStatus += csTemp;
		}
	}
	if(batStat.PowerState & BATTERY_CRITICAL){
		csTemp.LoadString(IDS_STATCRITICAL);
		if(m_csStatus.IsEmpty()){
			m_csStatus += csTemp;
		}else{
			m_csStatus += " ";
			m_csStatus += csTemp;
		}
	}
	if(batInfo.CycleCount){
		m_csCycleCount.Format(IDS_CYCLECOUNTFORMAT, batInfo.CycleCount);
	}else{
		m_csCycleCount.LoadString(IDS_UNKNOWN);
	}
	if(batStat.Rate == BATTERY_UNKNOWN_RATE){
		m_csRate.LoadString(IDS_UNKNOWN);
	}else{
		if(m_bRelativeCapacity){
			m_csRate.Format(IDS_RELRATEFORMAT, abs(batStat.Rate));
		}else{
			m_csRate.Format(IDS_RATEFORMAT, abs(batStat.Rate));
		}
	}

	int i;
	m_csChemistryCode.Empty();
	for(i = 0; i < 4; i++){
		if(batInfo.Chemistry[i] == 0){
			break;
		}
		m_csChemistryCode += batInfo.Chemistry[i];
	}
	
	if(pcyBattery->m_ulEstimatedTime == BATTERY_UNKNOWN_TIME){
		m_csEstimatedTime.LoadString(IDS_UNKNOWN);
	}else{
		m_csEstimatedTime.Format(IDS_TIMEFORMAT,
			pcyBattery->m_ulEstimatedTime / 3600,
			pcyBattery->m_ulEstimatedTime % 3600 / 60,
			pcyBattery->m_ulEstimatedTime % 60);
	}

	if(pcyBattery->m_ulTemperature){
		m_csTemperature.Format(IDS_TEMPFORMAT,
			pcyBattery->m_ulTemperature / 10,
			pcyBattery->m_ulTemperature % 10);
	}else{
		m_csTemperature.LoadString(IDS_UNKNOWN);
	}

	UpdateData(FALSE);

}

void CYbInfoDlg::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	return;
	//CDialog::WinHelp(dwData, nCmd);
}


void CYbInfoDlg::OnEnChangeEAutoupdate()
{
	// TODO :  ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�܂��ACDialog::OnInitDialog() �֐����I�[�o�[���C�h���āA
	// OR ��Ԃ� ENM_CORRECTTEXT �t���O���}�X�N�ɓ���āA
	// CRichEditCtrl().SetEventMask() ���Ăяo���Ȃ�����A
	// �R���g���[���́A���̒ʒm�𑗐M���܂���B

	// TODO :  �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����Ă��������B
	if(m_eAutoUpdate.GetWindowTextLength() <= 0){
		return;
	}

	UpdateData(TRUE);
	KillTimer(AutoUpdateTimerId);
	if(m_iAutoUpdate){
		SetTimer(AutoUpdateTimerId, m_iAutoUpdate * 1000, NULL);
	}

}

void CYbInfoDlg::OnTimer(UINT nIDEvent)
{
	// TODO : �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	if(nIDEvent == AutoUpdateTimerId){
		UpdateBatteryInformation();
	}
	CDialog::OnTimer(nIDEvent);
}
