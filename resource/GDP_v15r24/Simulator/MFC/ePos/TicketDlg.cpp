// TicketDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "TicketDlg.h"
#include "afxdialogex.h"
#include "ePosDlg.h"

// CTicketDlg dialog

IMPLEMENT_DYNAMIC(CTicketDlg, CDialogEx)

CTicketDlg::CTicketDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CTicketDlg::IDD, pParent)
{

}

CTicketDlg::~CTicketDlg()
{
}

void CTicketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILM_TYPE, m_comboFilmType);
	DDX_Control(pDX, IDC_COMBO_TICKET_TYPE, m_comboTicketType);
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_comboDepartment);
}


BEGIN_MESSAGE_MAP(CTicketDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTicketDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_FILM_TYPE, &CTicketDlg::OnCbnSelchangeComboFilmType)
	ON_CBN_SELCHANGE(IDC_COMBO_TICKET_TYPE, &CTicketDlg::OnCbnSelchangeComboTicketType)
	ON_CBN_SELCHANGE(IDC_COMBO_DEPARTMENT, &CTicketDlg::OnCbnSelchangeComboDepartment)
END_MESSAGE_MAP()


// CTicketDlg message handlers


void CTicketDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


BOOL CTicketDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	delete myFont;

	return CDialogEx::DestroyWindow();
}


BOOL CTicketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_TicketType = 0;
	m_departmentIndex = 0;

	myFont = new CFont();

	myFont->CreateFont(20, 0, 0, 0, FW_HEAVY, false, false,
					   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					   FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));

	m_comboFilmType.SetFont(myFont, true);
	m_comboTicketType.SetFont(myFont, true);
	m_comboDepartment.SetFont(myFont, true);

	m_comboFilmType.AddString(L"YERLÝ FÝLM");
	m_comboFilmType.AddString(L"YABANCI FÝLM");
	m_comboFilmType.SetCurSel(0);

	m_comboTicketType.AddString(L"TAM");
	m_comboTicketType.AddString(L"ÖÐRENCÝ");
	m_comboTicketType.AddString(L"ÝNDÝRÝMLÝ");
	m_comboTicketType.AddString(L"DAVETLÝ");
	m_comboTicketType.SetCurSel(0);

	ST_INTERFACE_DATA* pstInterfaceData = ((CePosDlg*)GetParent())->GetInterfaceDataPointer(((CePosDlg*)GetParent())->GetSelectedInterface());
	if (pstInterfaceData)
	{
		for (int i = 0; i < pstInterfaceData->numberOfTotalDepartments; i++)
		{
			CString cs;
			cs = CString(pstInterfaceData->stDepartments[i].szDeptName);
			m_comboDepartment.AddString(cs);
		}
		m_comboDepartment.SetCurSel(0);
	}

	return TRUE;
}


void CTicketDlg::OnCbnSelchangeComboFilmType()
{
	UpdateData(true);
	m_TicketType = (m_comboFilmType.GetCurSel() * 4) + m_comboTicketType.GetCurSel();
}


void CTicketDlg::OnCbnSelchangeComboTicketType()
{
	UpdateData(true);
	m_TicketType = (m_comboFilmType.GetCurSel() * 4) + m_comboTicketType.GetCurSel();
}


void CTicketDlg::OnCbnSelchangeComboDepartment()
{
	UpdateData(true);
	m_departmentIndex = m_comboDepartment.GetCurSel();
}
