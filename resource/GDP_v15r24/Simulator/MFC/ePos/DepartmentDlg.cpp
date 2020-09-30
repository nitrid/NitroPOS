// DepartmentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "DepartmentDlg.h"
#include "afxdialogex.h"
#include "GetInputDlg.h"


// CDepartmentDlg dialog

IMPLEMENT_DYNAMIC(CDepartmentDlg, CDialogEx)

CDepartmentDlg::CDepartmentDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CDepartmentDlg::IDD, pParent)
{

}

CDepartmentDlg::~CDepartmentDlg()
{
}

void CDepartmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TAXRATES, m_listTaxRates);
	DDX_Control(pDX, IDC_LIST_DEPARTMENTS, m_listDepartments);
}


BEGIN_MESSAGE_MAP(CDepartmentDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DEPARTMENTS, &CDepartmentDlg::OnDblclkListDepartments)
	ON_BN_CLICKED(IDOK, &CDepartmentDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DEPARTMENTS, &CDepartmentDlg::OnLvnItemchangedListDepartments)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TAXRATES, &CDepartmentDlg::OnLvnItemchangedListTaxrates)
END_MESSAGE_MAP()


// CDepartmentDlg message handlers


BOOL CDepartmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int nItem;
	CString cs, cs2;
	int i;
	CRect rectParent;
	CRect rectChildList_Items;

	GetWindowRect(&rectParent);

	// Taxrates
	rectChildList_Items.left	=  20 + rectParent.left;
	rectChildList_Items.right	= -20 + rectParent.right;
	rectChildList_Items.top		=  40 + rectParent.top;
	rectChildList_Items.bottom	= 200 + rectChildList_Items.top	;
	ScreenToClient(&rectChildList_Items);
	m_listTaxRates.MoveWindow(&rectChildList_Items);
	m_listTaxRates.InsertColumn(0, L"Tax Index");
	m_listTaxRates.InsertColumn(1, L"Tax Rate (%)");
	m_listTaxRates.SetColumnWidth(0, ((rectChildList_Items.Width() / 4)*2) - 2);
	m_listTaxRates.SetColumnWidth(1, ((rectChildList_Items.Width() / 4)*2) - 2);

	// Departments
	rectChildList_Items.left	=  20 + rectParent.left;
	rectChildList_Items.right	= -20 + rectParent.right;
	rectChildList_Items.top		= 300 + rectParent.top;
	rectChildList_Items.bottom	= 250 + rectChildList_Items.top	;
	ScreenToClient(&rectChildList_Items);
	m_listDepartments.MoveWindow(&rectChildList_Items);
	i = 0;
	m_listDepartments.InsertColumn(i++, L"Deparment Index");
	m_listDepartments.InsertColumn(i++, L"Tax Index");
	m_listDepartments.InsertColumn(i++, L"Name");
	m_listDepartments.InsertColumn(i++, L"Unit Type");
	m_listDepartments.InsertColumn(i++, L"Amount");
	m_listDepartments.InsertColumn(i++, L"Currency");
	m_listDepartments.InsertColumn(i++, L"Limit Amount");
	m_listDepartments.InsertColumn(i++, L"Lunch Voucher");
	i = 0;
	m_listDepartments.SetColumnWidth(i++, ((rectChildList_Items.Width() / 8)*1) - 2);
	m_listDepartments.SetColumnWidth(i++, ((rectChildList_Items.Width() / 8)*1) - 2);
	m_listDepartments.SetColumnWidth(i++, ((rectChildList_Items.Width() / 8)*1) - 2);
	m_listDepartments.SetColumnWidth(i++, ((rectChildList_Items.Width() / 8)*1) - 2);
	m_listDepartments.SetColumnWidth(i++, ((rectChildList_Items.Width() / 8)*1) - 2);
	m_listDepartments.SetColumnWidth(i++, ((rectChildList_Items.Width() / 8)*1) - 2);
	m_listDepartments.SetColumnWidth(i++, ((rectChildList_Items.Width() / 8)*1) - 2);
	m_listDepartments.SetColumnWidth(i++, ((rectChildList_Items.Width() / 8)*1) - 2);

	m_listTaxRates.SetExtendedStyle(m_listTaxRates.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_listDepartments.SetExtendedStyle(m_listDepartments.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	for (i = numberOfTotalTaxratesReceived - 1; i >= 0; i--)
	{
		nItem = m_listTaxRates.InsertItem(LVIF_TEXT | LVIF_STATE, 0, L"", 0, 0, 0, 0);

		cs.Format(L"%d", i);
		m_listTaxRates.SetItemText(nItem, 0, cs);

		cs.Format(L"%%%d.%02d",  stTaxRates[i].taxRate / 100,  stTaxRates[i].taxRate % 100);
		m_listTaxRates.SetItemText(nItem, 1, cs);
	}

	for (i = numberOfTotalDepartmentsReceived - 1; i >= 0; i--)
	{
		int j = 0;
		nItem = m_listDepartments.InsertItem(LVIF_TEXT | LVIF_STATE, 0, L"", 0, 0, 0, 0);

		cs.Format(L"%d", i);
		m_listDepartments.SetItemText(nItem, j++, cs);

		cs.Format(L"%d",  stDepartments[i].u8TaxIndex);
		m_listDepartments.SetItemText(nItem, j++, cs);

		cs = CString(stDepartments[i].szDeptName);
		m_listDepartments.SetItemText(nItem, j++, cs);

		cs.Format(L"%d",  stDepartments[i].iUnitType);
		m_listDepartments.SetItemText(nItem, j++, cs);

		cs.Format(L"%lld",  stDepartments[i].u64Price);
		m_listDepartments.SetItemText(nItem, j++, cs);

		cs.Format(L"%d",  stDepartments[i].iCurrencyType);
		m_listDepartments.SetItemText(nItem, j++, cs);

		cs.Format(L"%lld",  stDepartments[i].u64Limit);
		m_listDepartments.SetItemText(nItem, j++, cs);

		cs.Format(L"%s",  stDepartments[i].bLuchVoucher ? CString("1") : CString("0"));
		m_listDepartments.SetItemText(nItem, j++, cs);
	}

	return TRUE;
}


void CDepartmentDlg::OnDblclkListDepartments(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;
	CGetInputDlg GetInputDlg;
	int type = 1;	// 1 text, 2 numeric only

	switch (column)
	{
	case 0:
		// ilk kolonda index var, deðiþtirilmemeli
		return;
	case 2:
		type = 1;
		break;
	default:
		type = 2;
		break;
	}

	CString cs = m_listDepartments.GetItemText(row, column);
	if (GetInputDlg.DoModal(L"YENÝ DEÐER", cs, type) != IDOK)
		return;

	if (column == 7)
	{
		if (GetInputDlg.m_input.Compare(L"0") != 0)
		{
			GetInputDlg.m_input.Format(L"%s", CString("1"));
		}
	}

	m_listDepartments.SetItemText(row, column, GetInputDlg.m_input);
}


void CDepartmentDlg::OnBnClickedOk()
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*) m_listDepartments.GetDlgItem(0);
	int maxColumn = pHeader->GetItemCount();
	int maxRow		= m_listDepartments.GetItemCount();
	int row;
	int column;
	int index;

	for (row = 0; row < maxRow; row++)
	{
		for (column = 0; column < maxColumn; column++)
		{
			CString cs = m_listDepartments.GetItemText(row, column);
			switch (column)
			{
			case 0:
				index = atol(CT2A((LPCTSTR)cs));
				if (index >= 12)
					return;
				break;
			case 1:
				stDepartments[index].u8TaxIndex = (uint8)atol(CT2A((LPCTSTR)cs));
				if (stDepartments[index].u8TaxIndex >= 8)
					return;
				break;
			case 2:
				memset(stDepartments[index].szDeptName, 0x00, sizeof(stDepartments[index].szDeptName));
				memcpy(stDepartments[index].szDeptName, CT2A((LPCTSTR)cs), MINI(strlen(CT2A((LPCTSTR)cs)) , sizeof(stDepartments[index].szDeptName) - 1));
				break;

			case 3:
				stDepartments[index].iUnitType = (EItemUnitTypes)atol(CT2A((LPCTSTR)cs));
				break;

			case 4:
				stDepartments[index].u64Price = atol(CT2A((LPCTSTR)cs));
				break;

			case 5:
				stDepartments[index].iCurrencyType = (ECurrency)atol(CT2A((LPCTSTR)cs));
				break;

			case 6:
				stDepartments[index].u64Limit = atol(CT2A((LPCTSTR)cs));
				break;

			case 7:
				stDepartments[index].bLuchVoucher = (uint8) atol(CT2A((LPCTSTR)cs));
				break;

			default:
				break;
			}
		}
	}

	CDialogEx::OnOK();
}


void CDepartmentDlg::OnLvnItemchangedListDepartments(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	*pResult = 0;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CDepartmentDlg::OnLvnItemchangedListTaxrates(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
