// DoPayment.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "DoPayment.h"
#include "afxdialogex.h"
#include "GMPSmartDLL.h"


// CDoPayment dialog

IMPLEMENT_DYNAMIC(CDoPayment, CDialogEx)

CDoPayment::CDoPayment(CWnd* pParent /*=NULL*/)
		: CDialogEx(CDoPayment::IDD, pParent)
{

}

CDoPayment::~CDoPayment()
{
}

void CDoPayment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PAYMENT_TYPES, m_ListPaymentTypes);
}


BEGIN_MESSAGE_MAP(CDoPayment, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_PAYMENT_TYPES, &CDoPayment::OnLbnSelchangeListPaymentTypes)
	ON_LBN_DBLCLK(IDC_LIST_PAYMENT_TYPES, &CDoPayment::OnDblclkListPaymentTypes)
	ON_BN_CLICKED(IDOK, &CDoPayment::OnBnClickedOk)
END_MESSAGE_MAP()


// CDoPayment message handlers


BOOL CDoPayment::DestroyWindow()
{
	delete myFont;

	return CDialogEx::DestroyWindow();
}

BOOL CDoPayment::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	myFont = new CFont();

	myFont->CreateFont(24, 0, 0, 0, FW_HEAVY, false, false,
					   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					   FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));
	m_ListPaymentTypes.SetFont(myFont, true);

	if (m_typeOfPayments == 0)
	{
		m_ListPaymentTypes.AddString(L"PAYMENT_BY_VAS_APPLICATION");
		m_ListPaymentTypes.AddString(L"PAYMENT_CASH_TL");
		m_ListPaymentTypes.AddString(L"PAYMENT_CASH_CURRENCY");
		m_ListPaymentTypes.AddString(L"PAYMENT_BANKING_CARD");
		m_ListPaymentTypes.AddString(L"PAYMENT_YEMEKCEKI");
		m_ListPaymentTypes.AddString(L"PAYMENT_MOBILE");
		m_ListPaymentTypes.AddString(L"PAYMENT_HEDIYE_CEKI");
		m_ListPaymentTypes.AddString(L"PAYMENT_IKRAM");
		m_ListPaymentTypes.AddString(L"PAYMENT_ODEMESIZ");
		m_ListPaymentTypes.AddString(L"PAYMENT_KAPORA");
		m_ListPaymentTypes.AddString(L"PAYMENT_PUAN");
		m_ListPaymentTypes.AddString(L"PAYMENT_GIDER_PUSULASI");
		m_ListPaymentTypes.AddString(L"PAYMENT_BANKA_TRANSFERI");
		m_ListPaymentTypes.AddString(L"PAYMENT_CEK");
		m_ListPaymentTypes.AddString(L"PAYMENT_ACIK_HESAP");
	}
	else if (m_typeOfPayments == 1)
	{
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_CASH");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_BANK_CARD_VOID");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_BANK_CARD_REFUND");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_YEMEKCEKI");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_MOBILE");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_HEDIYE_CEKI");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_PUAN");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_ACIK_HESAP");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_KAPORA");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_GIDER_PUSULASI");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_BANKA_TRANSFERI");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_CEK");
	}
	else
	{
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_BY_VAS_APPLICATION");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_CASH");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_BANK_CARD_VOID");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_BANK_CARD_REFUND");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_YEMEKCEKI");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_MOBILE");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_HEDIYE_CEKI");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_PUAN");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_ACIK_HESAP");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_KAPORA");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_GIDER_PUSULASI");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_BANKA_TRANSFERI");
		m_ListPaymentTypes.AddString(L"REVERSE_PAYMENT_CEK");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDoPayment::OnLbnSelchangeListPaymentTypes()
{
	// TODO: Add your control notification handler code here
}


void CDoPayment::OnDblclkListPaymentTypes()
{
	int index = m_ListPaymentTypes.GetCurSel();
	unsigned long PaymentType[15]			= { PAYMENT_VAS_ALL,
										PAYMENT_CASH_TL,
										PAYMENT_CASH_CURRENCY,
										PAYMENT_BANK_CARD,
										PAYMENT_YEMEKCEKI,
										PAYMENT_MOBILE,
										PAYMENT_HEDIYE_CEKI,
										PAYMENT_IKRAM,
										PAYMENT_ODEMESIZ,
										PAYMENT_KAPORA,
										PAYMENT_PUAN,
										PAYMENT_GIDER_PUSULASI,
										PAYMENT_BANKA_TRANSFERI,
										PAYMENT_CEK,
										PAYMENT_ACIK_HESAP
									  };
	unsigned long ReversePaymentType[15]	= {(unsigned long)REVERSE_PAYMENT_CASH,
											(unsigned long)REVERSE_PAYMENT_BANK_CARD_VOID,
											(unsigned long)REVERSE_PAYMENT_BANK_CARD_REFUND,
											(unsigned long)REVERSE_PAYMENT_YEMEKCEKI,
											(unsigned long)REVERSE_PAYMENT_MOBILE,
											(unsigned long)REVERSE_PAYMENT_HEDIYE_CEKI,
											(unsigned long)REVERSE_PAYMENT_PUAN,
											(unsigned long)REVERSE_PAYMENT_ACIK_HESAP,
											(unsigned long)REVERSE_PAYMENT_KAPORA,
											(unsigned long)REVERSE_PAYMENT_GIDER_PUSULASI,
											(unsigned long)REVERSE_PAYMENT_BANKA_TRANSFERI,
											(unsigned long)REVERSE_PAYMENT_CEK,
										   };
	unsigned long ReversePaymentType2[15]	=
	{
		(unsigned long)PAYMENT_OTHER_REVERSE,
		(unsigned long)REVERSE_PAYMENT_CASH,
		(unsigned long)REVERSE_PAYMENT_BANK_CARD_VOID,
		(unsigned long)REVERSE_PAYMENT_BANK_CARD_REFUND,
		(unsigned long)REVERSE_PAYMENT_YEMEKCEKI,
		(unsigned long)REVERSE_PAYMENT_MOBILE,
		(unsigned long)REVERSE_PAYMENT_HEDIYE_CEKI,
		(unsigned long)REVERSE_PAYMENT_PUAN,
		(unsigned long)REVERSE_PAYMENT_ACIK_HESAP,
		(unsigned long)REVERSE_PAYMENT_KAPORA,
		(unsigned long)REVERSE_PAYMENT_GIDER_PUSULASI,
		(unsigned long)REVERSE_PAYMENT_BANKA_TRANSFERI,
		(unsigned long)REVERSE_PAYMENT_CEK,
	};

	if (m_typeOfPayments == 0)
		m_PaymentType = PaymentType[index];
	else if (m_typeOfPayments == 1)
		m_PaymentType = ReversePaymentType[index];
	else
		m_PaymentType = ReversePaymentType2[index];
	OnOK();
}


void CDoPayment::OnBnClickedOk()
{
	if (m_ListPaymentTypes.GetCurSel() >= 0)
		OnDblclkListPaymentTypes();
	else
		return;

//	CDialogEx::OnOK();
}


INT_PTR CDoPayment::DoModal(BYTE typeOfPayment)
{
	m_typeOfPayments = typeOfPayment;

	return CDialogEx::DoModal();
}
