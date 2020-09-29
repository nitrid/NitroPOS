// PasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "PasswordDlg.h"
#include "afxdialogex.h"


// CPasswordDlg dialog

IMPLEMENT_DYNAMIC(CPasswordDlg, CDialogEx)

CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CPasswordDlg::IDD, pParent)
		, m_Password(_T(""))
{

}

CPasswordDlg::~CPasswordDlg()
{
}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Password);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_CtrlPassword);
	DDX_Control(pDX, IDC_EDIT_CAPTION, m_CtrlCaption);
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPasswordDlg message handlers


INT_PTR CPasswordDlg::DoModal(CString caption)
{
	m_caption = caption;
	return CDialogEx::DoModal();
}


void CPasswordDlg::OnBnClickedOk()
{
	UpdateData(true);

	CDialogEx::OnOK();
}


BOOL CPasswordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	myFont = new CFont();

	myFont->CreateFont(32, 0, 0, 0, FW_HEAVY, false, false,
					   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					   FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));

	m_CtrlPassword.SetFont(myFont, true);
	m_CtrlCaption.SetFont(myFont, true);

	m_CtrlCaption.SetWindowTextW(m_caption);
	SetWindowTextW(m_caption);

	return TRUE;  // return TRUE unless you set the focus to a control

}


BOOL CPasswordDlg::DestroyWindow()
{
	delete myFont;

	return CDialogEx::DestroyWindow();
}
