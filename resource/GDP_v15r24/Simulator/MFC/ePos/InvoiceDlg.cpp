// InvoiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "InvoiceDlg.h"
#include "afxdialogex.h"


// CInvoiceDlg dialog

IMPLEMENT_DYNAMIC(CInvoiceDlg, CDialogEx)

CInvoiceDlg::CInvoiceDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CInvoiceDlg::IDD, pParent)
		, m_csInvoiceNo(_T("123"))
		, m_dateInvoiceDate(COleDateTime::GetCurrentTime())
		, m_csInvoiceAmount(_T(""))
		, m_TCK_NO(_T("12345678901"))
		, m_VK_NO(_T(""))
		, m_Irsaliye(FALSE)
{

}

CInvoiceDlg::~CInvoiceDlg()
{
}

void CInvoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INVOICE_NO, m_csInvoiceNo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_INVOICE_DATE, m_dateInvoiceDate);
	DDX_Text(pDX, IDC_EDIT_INVOICE_AMOUNT, m_csInvoiceAmount);
	DDX_Control(pDX, IDC_COMBO1, m_comboFaturaTipi);
	DDX_Text(pDX, IDC_EDIT_TCK_NO, m_TCK_NO);
	DDX_Text(pDX, IDC_EDIT_VK_NO, m_VK_NO);
	DDX_Check(pDX, IDC_CHECK_IRSALIYE, m_Irsaliye);
}


BEGIN_MESSAGE_MAP(CInvoiceDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInvoiceDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CInvoiceDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT_TCK_NO, &CInvoiceDlg::OnEnChangeEditTckNo)
	ON_EN_CHANGE(IDC_EDIT_VK_NO, &CInvoiceDlg::OnEnChangeEditVkNo)
END_MESSAGE_MAP()


// CInvoiceDlg message handlers


void CInvoiceDlg::OnBnClickedOk()
{
	UpdateData(true);

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


BOOL CInvoiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	myFont = new CFont();

	myFont->CreateFont(20, 0, 0, 0, FW_HEAVY, false, false,
					   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					   FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));

	m_comboFaturaTipi.SetFont(myFont, true);

	m_comboFaturaTipi.AddString(L"KAÐIT FATURA");
	m_comboFaturaTipi.AddString(L"E FATURA");
	m_comboFaturaTipi.AddString(L"E ARÞÝV");

	m_comboFaturaTipi.SetCurSel(0);
	m_byteFaturaTipi = m_comboFaturaTipi.GetCurSel();
	return TRUE;

}


void CInvoiceDlg::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	m_byteFaturaTipi = m_comboFaturaTipi.GetCurSel();
}


BOOL CInvoiceDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	delete myFont;
	return CDialogEx::DestroyWindow();
}


void CInvoiceDlg::OnEnChangeEditTckNo()
{
	UpdateData(true);
	m_VK_NO.Empty();
	UpdateData(false);
}


void CInvoiceDlg::OnEnChangeEditVkNo()
{
	UpdateData(true);
	m_TCK_NO.Empty();
	UpdateData(false);
}
