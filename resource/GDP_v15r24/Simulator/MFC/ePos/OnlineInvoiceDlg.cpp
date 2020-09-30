// InvoiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "OnlineInvoiceDlg.h"
#include "afxdialogex.h"


// COnlineInvoiceDlg dialog

IMPLEMENT_DYNAMIC(COnlineInvoiceDlg, CDialogEx)

COnlineInvoiceDlg::COnlineInvoiceDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(COnlineInvoiceDlg::IDD, pParent)
		, m_csOnlineInvoiceCustomerInfo(_T(""))
		, m_csOnlineInvoiceVKN(_T(""))
		, m_csOnlineInvoiceHomeAddress(_T(""))
		, m_csOnlineInvoiceDistrict(_T(""))
		, m_csOnlineInvoiceCity(_T(""))
		, m_csOnlineInvoiceCountry(_T(""))
		, m_csOnlineInvoiceEmail(_T(""))
		, m_csOnlineInvoiceWeb(_T(""))
		, m_csOnlineInvoicePhone(_T(""))
		, m_csOnlineInvoiceTaxOffice(_T(""))
		//m_comboInvoiceType
		, m_csOnlineInvoiceEttn(_T(""))
		, m_dateOnlineInvoiceOrderDate(COleDateTime::GetCurrentTime())
		, m_csOnlineInvoiceOrderNo(_T(""))
		, m_dateOnlineInvoiceDespatchDate(COleDateTime::GetCurrentTime())
		, m_csOnlineInvoiceDespatchNo(_T(""))
		, m_csOnlineInvoiceLabel(_T(""))
		, m_numberOfmultipleFlags(0)
{

}

COnlineInvoiceDlg::~COnlineInvoiceDlg()
{
}

void COnlineInvoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_CUSTOMERINFO, m_csOnlineInvoiceCustomerInfo);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_VKN, m_csOnlineInvoiceVKN);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_HOMEADDRESS, m_csOnlineInvoiceHomeAddress);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_DISTRICT, m_csOnlineInvoiceDistrict);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_CITY, m_csOnlineInvoiceCity);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_COUNTRY, m_csOnlineInvoiceCountry);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_EMAIL, m_csOnlineInvoiceEmail);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_WEB, m_csOnlineInvoiceWeb);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_PHONE, m_csOnlineInvoicePhone);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_TAXOFFICE, m_csOnlineInvoiceTaxOffice);
	DDX_Control(pDX, IDC_SET_ONLINE_INVOICE_TYPE, m_comboInvoiceType);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_ETTN, m_csOnlineInvoiceEttn);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_ORDER_DATE, m_dateOnlineInvoiceOrderDate);
	GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_ORDER_DATE)->EnableWindow(FALSE);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_ORDERNO, m_csOnlineInvoiceOrderNo);
	GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_ORDERNO)->EnableWindow(FALSE);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_DESPATCH_DATE, m_dateOnlineInvoiceDespatchDate);
	GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_DESPATCH_DATE)->EnableWindow(FALSE);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_DESPATCHNO, m_csOnlineInvoiceDespatchNo);
	GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_DESPATCHNO)->EnableWindow(FALSE);
	DDX_Text(pDX, IDC_EDIT_SET_ONLINE_INVOICE_LABEL, m_csOnlineInvoiceLabel);
}

#define IDC_CHECKBOX_DATE(i) (7000+i)

BEGIN_MESSAGE_MAP(COnlineInvoiceDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &COnlineInvoiceDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECKBOX_DATE(1) , &COnlineInvoiceDlg::OnBnClickedCheckOrderDate)
	ON_BN_CLICKED(IDC_CHECKBOX_DATE(2) , &COnlineInvoiceDlg::OnBnClickedCheckDespatchDate)
END_MESSAGE_MAP()


// COnlineInvoiceDlg message handlers

void COnlineInvoiceDlg::CheckBox(int item)
{
	int i = item - 1;

	m_checkBoxDate[i].SetCheck(!m_checkBoxDate[i].GetCheck());

	if (m_checkBoxDate[i].GetCheck())
	{
		m_flagValue |= m_multipleDateFlags[i].flagValue;
		if (i == 0)
		{
			GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_ORDER_DATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_ORDERNO)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_DESPATCH_DATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_DESPATCHNO)->EnableWindow(TRUE);
		}
	}
	else
	{
		m_flagValue &= ~m_multipleDateFlags[i].flagValue;
		if (i == 0)
		{
			GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_ORDERNO)->SetWindowTextW(_T(" "));

			GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_ORDER_DATE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_ORDERNO)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_DESPATCHNO)->SetWindowTextW(_T(" "));
			GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_DESPATCH_DATE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_DESPATCHNO)->EnableWindow(FALSE);
		}
	}
}

void COnlineInvoiceDlg::OnBnClickedCheckOrderDate()
{
	CheckBox(1);
}
void COnlineInvoiceDlg::OnBnClickedCheckDespatchDate()
{
	CheckBox(2);
}
void COnlineInvoiceDlg::OnBnClickedOk()
{
	UpdateData(true);
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
BOOL COnlineInvoiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	myFont = new CFont();

	myFont->CreateFont(20, 0, 0, 0, FW_HEAVY, false, false,
					   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					   FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));

	m_comboInvoiceType.SetFont(myFont, true);

	m_comboInvoiceType.AddString(L"E FATURA");
	m_comboInvoiceType.AddString(L"E ARÞÝV");

	m_comboInvoiceType.SetCurSel(0);
	m_byteOnlineInvoiceType = m_comboInvoiceType.GetCurSel();

#define WIDTH			500
#define HEIGHT			30
#define HEIGHT1			50

#define TOP(i)			520 + (HEIGHT*i)+ (HEIGHT1*i)
#define LEFT			410
#define BOTTOM(i)		520 + (HEIGHT*(i+1))+ (HEIGHT1*i)
#define RIGHT			40 + WIDTH

	for (int i = 0; i < m_numberOfmultipleFlags; i++)
	{
		m_checkBoxDate[i].Create(m_multipleDateFlags[i].caption, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, CRect(LEFT, TOP(i), RIGHT, BOTTOM(i)), this, IDC_CHECKBOX_DATE(i + 1));

		if (m_multipleDateFlags[i].defaultValue)
		{
			m_checkBoxDate[i].SetCheck(true);
			m_flagValue |= m_multipleDateFlags[i].flagValue;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}
void COnlineInvoiceDlg::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	m_byteOnlineInvoiceType = m_comboInvoiceType.GetCurSel();
}
BOOL COnlineInvoiceDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	delete myFont;
	return CDialogEx::DestroyWindow();
}
void COnlineInvoiceDlg::InsertFlag(CString caption, unsigned  long long flagValue, bool defaultValue)
{
	if (m_numberOfmultipleFlags >= MAX_NUMBER_OF_CB)
		return;

	m_multipleDateFlags[m_numberOfmultipleFlags].caption = caption;
	m_multipleDateFlags[m_numberOfmultipleFlags].flagValue = flagValue;
	m_multipleDateFlags[m_numberOfmultipleFlags].defaultValue = defaultValue;

	m_numberOfmultipleFlags++;
}


