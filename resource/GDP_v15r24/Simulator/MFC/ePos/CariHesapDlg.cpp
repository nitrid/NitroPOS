// InvoiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "CariHesapDlg.h"
#include "afxdialogex.h"


// CCariHesapDlg dialog

IMPLEMENT_DYNAMIC(CCariHesapDlg, CDialogEx)

CCariHesapDlg::CCariHesapDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CCariHesapDlg::IDD, pParent)
		, m_csCariHesapCustomerName(_T(""))
		, m_csCariHesapVKN(_T(""))
		, m_csCariHesapTCKN(_T(""))
		, m_csCariHesapDokumanNo(_T(""))
		, m_dateCariHesapDate(COleDateTime::GetCurrentTime())
{

}

CCariHesapDlg::~CCariHesapDlg()
{
}

void CCariHesapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_SET_CARI_HESAP_CUSTOMERNAME, m_csCariHesapCustomerName);
	DDX_Text(pDX, IDC_EDIT_SET_CARI_HESAP_VKN, m_csCariHesapVKN);
	DDX_Text(pDX, IDC_EDIT_SET_CARI_HESAP_TCKN, m_csCariHesapTCKN);

	DDX_Text(pDX, IDC_EDIT_SET_CARI_HESAP_DOKUMAN_NO, m_csCariHesapDokumanNo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SET_CARI_HESAP_DATE, m_dateCariHesapDate);
	GetDlgItem(IDC_DATETIMEPICKER_SET_CARI_HESAP_DATE)->EnableWindow(TRUE);
}

#define IDC_CHECKBOX_DATE(i) (7000+i)

BEGIN_MESSAGE_MAP(CCariHesapDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCariHesapDlg::OnBnClickedOk)
	/*ON_BN_CLICKED(IDC_CHECKBOX_DATE(1) , &CCariHesapDlg::OnBnClickedCheckOrderDate)
	ON_BN_CLICKED(IDC_CHECKBOX_DATE(2) , &CCariHesapDlg::OnBnClickedCheckDespatchDate)*/
END_MESSAGE_MAP()


// CCariHesapDlg message handlers

//void CCariHesapDlg::CheckBox( int item )
//{
//	int i = item-1;
//
//	m_checkBoxDate[i].SetCheck( !m_checkBoxDate[i].GetCheck() );
//
//	if( m_checkBoxDate[i].GetCheck() )
//	{
//		m_flagValue |= m_multipleDateFlags[i].flagValue;
//		if(i == 0)
//		{
//				GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_ORDER_DATE)->EnableWindow(TRUE);
//				GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_ORDERNO)->EnableWindow(TRUE);
//		}
//		else
//		{
//				GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_DESPATCH_DATE)->EnableWindow(TRUE);
//				GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_DESPATCHNO)->EnableWindow(TRUE);
//		}
//	}
//	else
//	{
//		m_flagValue &= ~m_multipleDateFlags[i].flagValue;
//		if(i == 0)
//		{
//				GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_ORDERNO)->SetWindowTextW(_T(" "));
//
//				GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_ORDER_DATE)->EnableWindow(FALSE);
//				GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_ORDERNO)->EnableWindow(FALSE);
//		}
//		else
//		{
//				GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_DESPATCHNO)->SetWindowTextW(_T(" "));
//				GetDlgItem(IDC_DATETIMEPICKER_SET_ONLINE_INVOICE_DESPATCH_DATE)->EnableWindow(FALSE);
//				GetDlgItem(IDC_EDIT_SET_ONLINE_INVOICE_DESPATCHNO)->EnableWindow(FALSE);
//		}
//	}
//}

//void CCariHesapDlg::OnBnClickedCheckOrderDate() { CheckBox(1); }
//void CCariHesapDlg::OnBnClickedCheckDespatchDate() { CheckBox(2); }
void CCariHesapDlg::OnBnClickedOk()
{
	UpdateData(true);
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
BOOL CCariHesapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	myFont = new CFont();

	myFont->CreateFont(20, 0, 0, 0, FW_HEAVY, false, false,
					   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					   FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));

	/*m_comboInvoiceType.SetFont(myFont,true);

	m_comboInvoiceType.AddString(L"E FATURA");
	m_comboInvoiceType.AddString(L"E ARÞÝV");

	m_comboInvoiceType.SetCurSel(0);
	m_byteCariHesapType = m_comboInvoiceType.GetCurSel();*/

#define WIDTH			500
#define HEIGHT			30
#define HEIGHT1			50

#define TOP(i)			520 + (HEIGHT*i)+ (HEIGHT1*i)
#define LEFT			410
#define BOTTOM(i)		520 + (HEIGHT*(i+1))+ (HEIGHT1*i)
#define RIGHT			40 + WIDTH

	/*for(int i=0;i<m_numberOfmultipleFlags;i++)
	{
			m_checkBoxDate[i].Create( m_multipleDateFlags[i].caption, WS_CHILD|WS_VISIBLE|BS_CHECKBOX, CRect(LEFT,TOP(i),RIGHT,BOTTOM(i)), this,IDC_CHECKBOX_DATE(i+1) );

			if( m_multipleDateFlags[i].defaultValue )
			{
				m_checkBoxDate[i].SetCheck(true);
				m_flagValue |= m_multipleDateFlags[i].flagValue;
			}
	}*/
	return TRUE;  // return TRUE unless you set the focus to a control
}
void CCariHesapDlg::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	//m_byteCariHesapType = m_comboInvoiceType.GetCurSel();
}
BOOL CCariHesapDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	delete myFont;
	return CDialogEx::DestroyWindow();
}
void CCariHesapDlg::InsertFlag(CString caption, unsigned  long long flagValue, bool defaultValue)
{
	/*if( m_numberOfmultipleFlags >= MAX_NUMBER_OF_CB)
		return;

	m_multipleDateFlags[m_numberOfmultipleFlags].caption = caption;
	m_multipleDateFlags[m_numberOfmultipleFlags].flagValue = flagValue;
	m_multipleDateFlags[m_numberOfmultipleFlags].defaultValue = defaultValue;

	m_numberOfmultipleFlags++;*/
}


