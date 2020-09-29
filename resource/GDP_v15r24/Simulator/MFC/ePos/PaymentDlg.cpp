// PaymentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "PaymentDlg.h"
#include "afxdialogex.h"
#include "ePosDlg.h"

// CPaymentDlg dialog

IMPLEMENT_DYNAMIC(CPaymentDlg, CDialogEx)

CPaymentDlg::CPaymentDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CPaymentDlg::IDD, pParent)
		, m_selectedPayment(0)
{

}

CPaymentDlg::~CPaymentDlg()
{
}

void CPaymentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PAYMENT, m_listPayment);
	DDX_Control(pDX, IDC_LIST_BANK_PAYMENT, m_listBankPayment);
}


BEGIN_MESSAGE_MAP(CPaymentDlg, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PAYMENT, &CPaymentDlg::OnItemchangedListPayment)
	ON_BN_CLICKED(IDOK, &CPaymentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPaymentDlg message handlers


BOOL CPaymentDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::DestroyWindow();
}


BOOL CPaymentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rectParent;
	CRect rectChildList_Items;
	CString cs;
	int numberOfColumns;

	GetWindowRect(&rectParent);

	// Payment
	rectChildList_Items.left	=  20 + rectParent.left;
	rectChildList_Items.right	= -20 + rectParent.right;
	rectChildList_Items.top		=  40 + rectParent.top;
	rectChildList_Items.bottom	= 200 + rectChildList_Items.top;
	ScreenToClient(&rectChildList_Items);
	m_listPayment.MoveWindow(&rectChildList_Items);
	m_listPayment.SetExtendedStyle(m_listPayment.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	numberOfColumns = 0;
	m_listPayment.InsertColumn(numberOfColumns++, L"typeOfPayment");			// EPaymentTypes
	m_listPayment.InsertColumn(numberOfColumns++, L"subtypeOfPayment");		// EPaymentSubtypes
	m_listPayment.InsertColumn(numberOfColumns++, L"flags");
	m_listPayment.InsertColumn(numberOfColumns++, L"dateOfPayment");
	m_listPayment.InsertColumn(numberOfColumns++, L"orgAmount");
	m_listPayment.InsertColumn(numberOfColumns++, L"payAmount");
	for (int i = 0; i < numberOfColumns; i++)
		m_listPayment.SetColumnWidth(i, ((rectChildList_Items.Width() / numberOfColumns)) - 1);

	for (int i = 0; i < m_numberOfPayments; i++)
	{
		numberOfColumns = 0;
		int nItem = m_listPayment.InsertItem(LVIF_TEXT | LVIF_STATE, m_listPayment.GetItemCount(), L"", 0, 0, 0, 0);

		WCHAR Buffer[256];
		const char *Ptr = ((CePosDlg*)GetParent())->GetPaymentTypeName(m_stPayment[i].typeOfPayment);
		memset(Buffer, 0x00, sizeof(Buffer));
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, Ptr, (int)strlen(Ptr), NULL, 0);
		MultiByteToWideChar(CP_UTF8, 0, Ptr, (int)strlen(Ptr), Buffer, size_needed);
		m_listPayment.SetItemText(nItem, numberOfColumns++, Buffer);

		Ptr = ((CePosDlg*)GetParent())->GetPaymentSubtypeName(m_stPayment[i].subtypeOfPayment);
		memset(Buffer, 0x00, sizeof(Buffer));
		size_needed = MultiByteToWideChar(CP_UTF8, 0, Ptr, (int)strlen(Ptr), NULL, 0);
		MultiByteToWideChar(CP_UTF8, 0, Ptr, (int)strlen(Ptr), Buffer, size_needed);
		m_listPayment.SetItemText(nItem, numberOfColumns++, Buffer);

		cs.Format(L"%08X", m_stPayment[i].flags);
		m_listPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs.Format(L"%08X", m_stPayment[i].dateOfPayment);
		m_listPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(((CePosDlg*)GetParent())->formatAmount(m_stPayment[i].orgAmount, m_stPayment[i].orgAmountCurrencyCode));
		m_listPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(((CePosDlg*)GetParent())->formatAmount(m_stPayment[i].payAmount, m_stPayment[i].payAmountCurrencyCode));
		m_listPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(((CePosDlg*)GetParent())->formatAmount(m_stPayment[i].cashBackAmountInTL, CURRENCY_TL));
		m_listPayment.SetItemText(nItem, numberOfColumns++, cs);

	}

	// Bank Payments
	rectChildList_Items.left	=  20 + rectParent.left;
	rectChildList_Items.right	= -20 + rectParent.right;
	rectChildList_Items.top		= 250 + rectParent.top;
	rectChildList_Items.bottom	= 200 + rectChildList_Items.top;
	ScreenToClient(&rectChildList_Items);
	m_listBankPayment.MoveWindow(&rectChildList_Items);
	m_listBankPayment.SetExtendedStyle(m_listBankPayment.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	numberOfColumns = 0;
	m_listBankPayment.InsertColumn(numberOfColumns++, L"bankName");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"bankBkmId");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"terminalId");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"merchantId");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"batchNo");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"stan");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"authorizeCode");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"transFlag");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"Error");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"Error");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"Card PAN");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"Card Holder Name");
	m_listBankPayment.InsertColumn(numberOfColumns++, L"Card Input Type");
	for (int i = 0; i < numberOfColumns; i++)
		m_listBankPayment.SetColumnWidth(i, ((rectChildList_Items.Width() / numberOfColumns)) - 1);

	m_listPayment.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

	return TRUE;  // return TRUE unless you set the focus to a control
}


INT_PTR CPaymentDlg::DoModal(ST_PAYMENT* pstPayment, int numberOfPayments)
{
	// TODO: Add your specialized code here and/or call the base class
	m_numberOfPayments = numberOfPayments;

	memcpy(&m_stPayment[0], pstPayment, sizeof(ST_PAYMENT) * numberOfPayments);
	return CDialogEx::DoModal();
}



void CPaymentDlg::OnItemchangedListPayment(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;
	int nItem;
	int numberOfColumns;
	CString cs;

	m_selectedPayment = row;

	m_listBankPayment.DeleteAllItems();

	switch (m_stPayment[row].typeOfPayment)
	{
	case REVERSE_PAYMENT_CASH:
	case PAYMENT_CASH_TL:
	case PAYMENT_CASH_CURRENCY:
		break;

	case REVERSE_PAYMENT_BANK_CARD_VOID:
	case REVERSE_PAYMENT_BANK_CARD_REFUND:
	case PAYMENT_BANK_CARD:
	case PAYMENT_MOBILE:
	case REVERSE_PAYMENT_MOBILE:
		nItem = m_listBankPayment.InsertItem(LVIF_TEXT | LVIF_STATE, m_listBankPayment.GetItemCount(), L"", 0, 0, 0, 0);
		numberOfColumns = 0;

		cs = CString(m_stPayment[row].stBankPayment.bankName);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs.Format(L"%d", m_stPayment[row].stBankPayment.bankBkmId);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(m_stPayment[row].stBankPayment.terminalId);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(m_stPayment[row].stBankPayment.merchantId);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs.Format(L"%d", m_stPayment[row].stBankPayment.batchNo);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs.Format(L"%d", m_stPayment[row].stBankPayment.stan);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(m_stPayment[row].stBankPayment.authorizeCode);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs.Format(L"%02X%02X", m_stPayment[row].stBankPayment.transFlag[0], m_stPayment[row].stBankPayment.transFlag[1]);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(m_stPayment[row].stBankPayment.stPaymentErrMessage.AppErrorMsg) + CString(L" / ") + CString(m_stPayment[row].stBankPayment.stPaymentErrMessage.AppErrorCode);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(m_stPayment[row].stBankPayment.stPaymentErrMessage.ErrorMsg) + CString(L" / ") + CString(m_stPayment[row].stBankPayment.stPaymentErrMessage.ErrorCode);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(m_stPayment[row].stBankPayment.stCard.pan);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs = CString(m_stPayment[row].stBankPayment.stCard.holderName);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		cs.Format(L"%d", m_stPayment[row].stBankPayment.stCard.inputType);
		m_listBankPayment.SetItemText(nItem, numberOfColumns++, cs);

		break;

	default:
		break;
	}
}


void CPaymentDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
