// DBTranDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "DBTranDlg.h"
#include "afxdialogex.h"
#include "GetInputDlg.h"
#include "GmpSmartDll.h"

// CDBTranDlg dialog

IMPLEMENT_DYNAMIC(CDBTranDlg, CDialogEx)

CDBTranDlg::CDBTranDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CDBTranDlg::IDD, pParent)
{
	memset(TranDbName, 0, sizeof(TranDbName));
	initDone = false;
}

CDBTranDlg::~CDBTranDlg()
{
}

void CDBTranDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Z, m_list_Z);
	DDX_Control(pDX, IDC_LIST_TRANSACTION, m_listTransaction);
	DDX_Control(pDX, IDC_LIST_ITEMS, m_listItems);
}


BEGIN_MESSAGE_MAP(CDBTranDlg, CDialogEx)
	//	ON_BN_CLICKED(IDOK, &CDBTranDlg::OnBnClickedOk)
	ON_WM_SIZE()
	//	ON_WM_SIZING()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_Z, &CDBTranDlg::OnNMDblclkListZ)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TRANSACTION, &CDBTranDlg::OnDblclkListTransaction)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_Z, &CDBTranDlg::OnLvnItemchangedListZ)
	//ON_BN_CLICKED(IDC_BUTTON_DROPTABLE, &CDBTranDlg::OnBnClickedButtonDroptable)
END_MESSAGE_MAP()


// CDBTranDlg message handlers


BOOL CDBTranDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::DestroyWindow();
}

BOOL CDBTranDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_list_Z.InsertColumn(0, L"Z No"		, 0, 1);
	m_list_Z.InsertColumn(1, L"Fiþ Sayýsý"	, 0, 1);
	m_list_Z.InsertColumn(2, L"EKU No"		, 0, 1);

	uint16 ZNo;
	uint16 FNo;
	uint16 EKUNo;

	if (FP3_GetCurrentFiscalCounters(m_hInt, &ZNo, &FNo, &EKUNo) == TRAN_RESULT_OK)
	{
		int nItem;
		for (int k = 1; k < ZNo; k++)
		{
			nItem = m_list_Z.InsertItem(LVIF_TEXT | LVIF_STATE, 0, L"", LVIS_SELECTED, LVIS_SELECTED, 0, 0);
			InsertItemText(&m_list_Z, nItem, 0, "%d", k);
		}

		nItem = m_list_Z.InsertItem(LVIF_TEXT | LVIF_STATE, 0, L"", LVIS_SELECTED, LVIS_SELECTED, 0, 0);
		if (nItem != -1)
		{
			int i = 0;
			InsertItemText(&m_list_Z, nItem, i++, "%d", ZNo);
			InsertItemText(&m_list_Z, nItem, i++, "%d", FNo);
			InsertItemText(&m_list_Z, nItem, i++, "%d", EKUNo);
		}
	}

	initDone = true;

	m_list_Z.SetExtendedStyle(m_list_Z.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_listTransaction.SetExtendedStyle(m_listTransaction.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_listItems.SetExtendedStyle(m_listItems.GetExtendedStyle() | LVS_EX_FULLROWSELECT);


	ResizeControls();

	return TRUE;
}

void CDBTranDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (initDone)
		ResizeControls();
}

void CDBTranDlg::OnNMDblclkListZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;
	CString ZNo;
	char swlWord[1024];
	*pResult = 0;

	uint16 readlen = 0;

	memset(TranDbName, 0, sizeof(TranDbName));

	if (FP3_GetTlvData(m_hInt, GMP_EXT_DEVICE_TAG_TRAN_DB_NAME, (uint8*)TranDbName, sizeof(TranDbName) - 1, &readlen) == TRAN_RESULT_OK)
	{
		if (row >= 0)
		{
			ZNo		= m_list_Z.GetItemText(row, 0);

			sprintf(swlWord, "SELECT * FROM TBL_TRANSACTION WHERE ZNO=%d;", atol(CT2A((LPCTSTR)ZNo)));
			FillListControlFromDBExt(m_hInt, TranDbName, &m_listTransaction, swlWord);
		}
	}
}

void CDBTranDlg::OnDblclkListTransaction(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;
	CString ZNo;
	CString FNo;
	char swlWord[1024];
	*pResult = 0;

	ZNo.Empty();
	FNo.Empty();

	if (row >= 0)
	{
		int nColumnCount = m_listTransaction.GetHeaderCtrl()->GetItemCount();
		LVCOLUMN col;
		CString colName;
		TCHAR szName[128];
		col.mask	= LVCF_TEXT;
		col.pszText = szName;
		col.cchTextMax = sizeof(szName) - 1;

		for (int i = 0; i < nColumnCount; i++)
		{
			memset(szName, 0x00, sizeof(szName));
			if (!m_listTransaction.GetColumn(i, &col))
				break;

			colName = CString(col.pszText);

			if (colName == "ZNO")
				ZNo	= m_listTransaction.GetItemText(row, i);
			else if (colName == "FNO")
				FNo	= m_listTransaction.GetItemText(row, i);
		}

		if (strlen(TranDbName) == 0)
		{
			uint16 readlen = 0;
			FP3_GetTlvData(m_hInt, GMP_EXT_DEVICE_TAG_TRAN_DB_NAME, (uint8*)TranDbName, sizeof(TranDbName) - 1, &readlen);
		}

		if (ZNo.GetLength() && FNo.GetLength())
		{
			sprintf(swlWord, "SELECT * FROM TBL_ITEM WHERE ZNO=%d AND FNO=%d;", atol(CT2A((LPCTSTR)ZNo)), atol(CT2A((LPCTSTR)FNo)));
			FillListControlFromDBExt(m_hInt, TranDbName , &m_listItems, swlWord);
		}
	}
}

void CDBTranDlg::OnLvnItemchangedListZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CDBTranDlg::ResizeControls(void)
{
#define GROUP_1_HIGH			200
#define GROUP_2_HIGH			200
#define MARGIN					10

	CRect rectParent;
	CRect rectParentOrg;
	CRect rectChildList_Items;

	GetWindowRect(&rectParent);
	GetWindowRect(&rectParentOrg);

	int LEFT	= rectParent.left + (2 * MARGIN);
	int RIGHT	= rectParent.right - (2 * MARGIN);
	int TOP		= rectParent.top + (4 * MARGIN);
	int BOTTOM	= rectParent.bottom - (2 * MARGIN);

	// m_listECRPluGrups Names
	rectChildList_Items.left	= LEFT;
	rectChildList_Items.right	= RIGHT;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + GROUP_1_HIGH;
	TOP += (GROUP_1_HIGH + MARGIN);
	ScreenToClient(&rectChildList_Items);
	m_list_Z.MoveWindow(&rectChildList_Items);
	m_list_Z.SetColumnWidth(0, ((rectChildList_Items.Width() / 5)*1) - 5);
	m_list_Z.SetColumnWidth(1, ((rectChildList_Items.Width() / 5)*2) - 5);
	m_list_Z.SetColumnWidth(2, ((rectChildList_Items.Width() / 5)*2) - 5);


	// m_listPluGrups2 Names
	rectChildList_Items.left	= LEFT;
	rectChildList_Items.right	= RIGHT;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + GROUP_2_HIGH;
	TOP += (GROUP_2_HIGH + MARGIN);
	ScreenToClient(&rectChildList_Items);
	m_listTransaction.MoveWindow(&rectChildList_Items);

	// m_listECRPluItems Names
	rectChildList_Items.left	= LEFT;
	rectChildList_Items.right	= RIGHT;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= BOTTOM;
	TOP = BOTTOM + MARGIN;
	ScreenToClient(&rectChildList_Items);
	m_listItems.MoveWindow(&rectChildList_Items);

}
