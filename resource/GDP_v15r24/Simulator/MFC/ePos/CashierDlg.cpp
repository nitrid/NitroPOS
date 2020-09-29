// CashierDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "CashierDlg.h"
#include "afxdialogex.h"
#include "PasswordDlg.h"
#include "GmpSmartDll.h"
#include "GetInputDlg.h"
#include "string.h"

// CCashierDlg dialog


/** Returns the smaller of two inputs */
#ifndef MINI
#define MINI(x,y)  				( ((x) < (y)) ? (x) : (y) )
#endif

IMPLEMENT_DYNAMIC(CCashierDlg, CDialogEx)

CCashierDlg::CCashierDlg(CWnd* pParent)
		: CDialogEx(CCashierDlg::IDD, pParent)
		, m_cashierIndex(0)
		, activeCashier(0)
		, m_activeCashierIndex(_T(""))
		, m_activeCashierName(_T(""))
{

}

CCashierDlg::~CCashierDlg()
{
}

void CCashierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST_CASHIER, m_listCashier);
	DDX_Control(pDX, IDC_LIST_CASHIERS, m_ListCashiers);
	//  DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Text(pDX, IDC_EDIT_ACTIVE_CASHIER_INDEX, m_activeCashierIndex);
	DDX_Text(pDX, IDC_EDIT_ACTIVE_CASHIER_NAME, m_activeCashierName);
}


BEGIN_MESSAGE_MAP(CCashierDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCashierDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CASHIERS, &CCashierDlg::OnNMDblclkListCashiers)
	ON_BN_CLICKED(IDC_BUTTON1, &CCashierDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CASHIERS, &CCashierDlg::OnLvnItemchangedListCashiers)
	ON_BN_CLICKED(IDC_BUTTON2, &CCashierDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT_ACTIVE_CASHIER_INDEX, &CCashierDlg::OnEnChangeEditActiveCashierIndex)
END_MESSAGE_MAP()


// CCashierDlg message handlers


BOOL CCashierDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListCashiers.InsertColumn(0, L"Index");
	m_ListCashiers.InsertColumn(1, L"Name");
	m_ListCashiers.InsertColumn(2, L"Flag");

	CRect rectParent;
	CRect rectChildList_Items;

	GetWindowRect(&rectParent);

	rectChildList_Items.left	=  20 + rectParent.left;
	rectChildList_Items.right	= -20 + rectParent.right;
	rectChildList_Items.top		= 150 + rectParent.top;
	rectChildList_Items.bottom	= -50 + rectParent.bottom;

	ScreenToClient(&rectChildList_Items);

	m_ListCashiers.MoveWindow(&rectChildList_Items);

	m_ListCashiers.SetColumnWidth(0, ((rectChildList_Items.Width() / 5)*1) - 1);
	m_ListCashiers.SetColumnWidth(1, ((rectChildList_Items.Width() / 5)*3) - 1);
	m_ListCashiers.SetColumnWidth(2, ((rectChildList_Items.Width() / 5)*1) - 1);


	m_activeCashierIndex.Format(L"%d", activeCashier);
	if (activeCashier < numberOfTotalCashiers)
		m_activeCashierName = CString(stCashierTable[activeCashier].name);

	for (int i = 0; i < numberOfTotalCashiers; i++)
	{
		int nItem;
		CString cs;
		cs.Empty();
		cs = CString(stCashierTable[i].name);

		if (activeCashier == stCashierTable[i].index)
			nItem = m_ListCashiers.InsertItem(LVIF_TEXT | LVIF_STATE, 0, L"", LVIS_SELECTED, LVIS_SELECTED, 0, 0);
		else
			nItem = m_ListCashiers.InsertItem(LVIF_TEXT | LVIF_STATE, 0, L"", 0, 0, 0, 0);

		cs.Format(L"%d", stCashierTable[i].index);
		m_ListCashiers.SetItemText(nItem, 0, cs);

		cs = CString(stCashierTable[i].name);
		m_ListCashiers.SetItemText(nItem, 1, cs);

		cs.Format(L"%08X", stCashierTable[i].flags);
		m_ListCashiers.SetItemText(nItem, 2, cs);
	}

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCashierDlg::OnBnClickedOk()
{

}

void CCashierDlg::OnNMDblclkListCashiers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;
	CPasswordDlg PasswordDlg;

	CString cs_index = m_ListCashiers.GetItemText(row, 0);

	m_cashierIndex = (short)atol(CT2A((LPCTSTR)cs_index));

	if (PasswordDlg.DoModal(L"KASÝYER ÞÝFRESÝ") != IDOK)
		return;

	retcode = FP3_FunctionCashierLogin(m_hInt, m_cashierIndex, CT2A((LPCTSTR)(PasswordDlg.m_Password)));
	CDialogEx::OnOK();
}


void CCashierDlg::OnBnClickedButton1()
{
	retcode = FP3_FunctionCashierLogout(m_hInt);
	CDialogEx::OnOK();
}


void CCashierDlg::OnLvnItemchangedListCashiers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CCashierDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	char KasiyerAdi[16], KasiyerIndex[2], KasiyerSifre[5], AdminSifre[5]  ;


	CGetInputDlg* pcInput;

	short m_cashierIndex;

	memset(KasiyerAdi, 0 , 16);
	memset(KasiyerIndex, 0 , 2);
	memset(KasiyerSifre, 0 , 5);
	memset(AdminSifre, 0 , 5);

	pcInput = new CGetInputDlg;
	uint8 len;

	if (pcInput->DoModal((CString) "KASÝYER ADI", (CString) KasiyerAdi, 1) != IDOK)
		return ;
	len = (uint8)strlen(CT2A((LPCTSTR)(pcInput->m_input)));
	memcpy((void*) KasiyerAdi, CT2A((LPCTSTR)(pcInput->m_input)), MINI(len , 16));

	if (pcInput->DoModal((CString) "KASÝYER INDEX", (CString) KasiyerIndex, 1) != IDOK)
		return ;
	memcpy((void*) KasiyerIndex, CT2A((LPCTSTR)(pcInput->m_input)) , 1);


	if (pcInput->DoModal((CString) "KASÝYER ÞÝFRE", (CString) KasiyerSifre, 1) != IDOK)
		return ;
	len = (uint8)strlen(CT2A((LPCTSTR)(pcInput->m_input)));
	memcpy((void*) KasiyerSifre, CT2A((LPCTSTR)(pcInput->m_input)), MINI(len , 4));

	if (pcInput->DoModal((CString) "YÖNETÝCÝ ÞÝFRE", (CString) AdminSifre, 1) != IDOK)
		return ;
	len = (uint8)strlen(CT2A((LPCTSTR)(pcInput->m_input)));
	memcpy((void*) AdminSifre, CT2A((LPCTSTR)(pcInput->m_input)), MINI(len , 4));

	delete pcInput;
	m_cashierIndex = (short)atol(CT2A((LPCTSTR)KasiyerIndex));
	if (m_cashierIndex > 3)
		return;

	retcode = FP3_FunctionAddCashier(m_hInt, m_cashierIndex, KasiyerAdi , KasiyerSifre , AdminSifre) ;

	CDialogEx::OnOK();
	return;
}


void CCashierDlg::OnEnChangeEditActiveCashierIndex()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
