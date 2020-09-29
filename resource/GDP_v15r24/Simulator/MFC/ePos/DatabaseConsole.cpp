// DatabaseConsole.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "DatabaseConsole.h"
#include "afxdialogex.h"
#include "GmpSmartDll.h"


// CDatabaseConsole dialog

IMPLEMENT_DYNAMIC(CDatabaseConsole, CDialogEx)

CDatabaseConsole::CDatabaseConsole(CWnd* pParent /*=NULL*/)
		: CDialogEx(CDatabaseConsole::IDD, pParent)
{

}

CDatabaseConsole::~CDatabaseConsole()
{
}

void CDatabaseConsole::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATABASE_NAME, m_ListDatabaseName);
	DDX_Control(pDX, IDC_LIST_TABLES, m_ListTables);
	DDX_Control(pDX, IDC_LIST_ROWS, m_ListRows);
	DDX_Control(pDX, IDC_EDIT_SQLWORD, m_EditBoxSqlword);
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonExecute);
}


BEGIN_MESSAGE_MAP(CDatabaseConsole, CDialogEx)
	ON_LBN_DBLCLK(IDC_LIST_DATABASE_NAME, &CDatabaseConsole::OnDblclkListDatabaseName)
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGED()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TABLES, &CDatabaseConsole::OnDblclkListTables)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDC_MENU_DROP_TABLE, &CDatabaseConsole::OnMenuDropTable)
	ON_BN_CLICKED(IDC_BUTTON1, &CDatabaseConsole::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDatabaseConsole message handlers
BOOL CDatabaseConsole::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::DestroyWindow();
}


BOOL CDatabaseConsole::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ResizeControls();
	char m_PluDbName[64];
	uint32 PluDbSize;
	int retcode;

	uint16 readlen = 0;
	char TranDbName[64];
	uint32 TranDbSize = 0;

	memset(TranDbName, 0, sizeof(TranDbName));
	memset(m_PluDbName, 0x00, sizeof(m_PluDbName));

	retcode = FP3_GetTlvData(m_hInt, GMP_EXT_DEVICE_TAG_TRAN_DB_NAME, (uint8*)TranDbName, sizeof(TranDbName) - 1, &readlen);
	if (retcode != TRAN_RESULT_OK)
		return FALSE;

	retcode = FP3_GetTlvData(m_hInt, GMP_EXT_DEVICE_TAG_TRAN_DB_SIZE, (uint8*) & TranDbSize, sizeof(TranDbSize), &readlen);
	if (retcode != TRAN_RESULT_OK)
		return FALSE;

	retcode = FP3_GetTlvData(m_hInt, GMP_EXT_DEVICE_TAG_PLU_DB_NAME, (uint8*)m_PluDbName, sizeof(m_PluDbName) - 1, &readlen);
	if (retcode != TRAN_RESULT_OK)
		return FALSE;

	retcode = FP3_GetTlvData(m_hInt, GMP_EXT_DEVICE_TAG_PLU_DB_SIZE, (uint8*) & PluDbSize, sizeof(PluDbSize), &readlen);
	if (retcode != TRAN_RESULT_OK)
		return FALSE;

	m_ListDatabaseName.ResetContent();
	m_ListDatabaseName.AddString((CString)TranDbName);
	m_ListDatabaseName.AddString((CString)m_PluDbName);

	m_ListTables.SetExtendedStyle(m_ListTables.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_ListRows.SetExtendedStyle(m_ListRows.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDatabaseConsole::OnDblclkListDatabaseName()
{
	int index = m_ListDatabaseName.GetCurSel();

	if (index < 0)
		return;

	CString cs;
	m_ListDatabaseName.GetText(index, cs);

	FillListControlFromDBExt(m_hInt, CT2A((LPCTSTR)cs), &m_ListTables, "SELECT * FROM sqlite_master;");
}

void CDatabaseConsole::ResizeControls(void)
{
#define DATABASE_NAME_WIDTH		200
#define DATABASE_NAME_HIGTH		200
#define SQLWORD_HIGH			30
#define EXECUTE_BUTTON_WITDH	80

	CRect rectParent;
	CRect rectParentOrg;
	CRect rectChildList_Items;

	GetWindowRect(&rectParent);
	GetWindowRect(&rectParentOrg);

	// Database Names
	rectChildList_Items.left	= rectParent.left + 20;
	rectChildList_Items.right	= rectChildList_Items.left	+ DATABASE_NAME_WIDTH;
	rectChildList_Items.top		= rectParent.top  + 40;
	rectChildList_Items.bottom	= rectChildList_Items.top	+ DATABASE_NAME_HIGTH;
	ScreenToClient(&rectChildList_Items);
	m_ListDatabaseName.MoveWindow(&rectChildList_Items);

	// Table Names
	rectChildList_Items.left	= rectParent.left	+ 20 + DATABASE_NAME_WIDTH + 10;
	rectChildList_Items.right	= rectParent.right	- 20;
	rectChildList_Items.top		= rectParent.top	+ 40;
	rectChildList_Items.bottom	= rectChildList_Items.top	+ DATABASE_NAME_HIGTH;
	ScreenToClient(&rectChildList_Items);
	m_ListTables.MoveWindow(&rectChildList_Items);

	// Sqlword
	rectChildList_Items.left	= rectParent.left	+ 20;
	rectChildList_Items.right	= rectParent.right	- 20 - EXECUTE_BUTTON_WITDH;
	rectChildList_Items.top		= rectParent.top	+ 40 + DATABASE_NAME_HIGTH + 10;
	rectChildList_Items.bottom	= rectParent.top	+ 40 + DATABASE_NAME_HIGTH + 10 + SQLWORD_HIGH;
	ScreenToClient(&rectChildList_Items);
	m_EditBoxSqlword.MoveWindow(&rectChildList_Items);

	// Execute
	rectChildList_Items.left	= rectParent.right	- 20 - EXECUTE_BUTTON_WITDH + 5 ;
	rectChildList_Items.right	= rectParent.right	- 20;
	rectChildList_Items.top		= rectParent.top	+ 40 + DATABASE_NAME_HIGTH + 10;
	rectChildList_Items.bottom	= rectParent.top	+ 40 + DATABASE_NAME_HIGTH + 10 + SQLWORD_HIGH;
	ScreenToClient(&rectChildList_Items);
	m_ButtonExecute.MoveWindow(&rectChildList_Items);

	// Table Names
	rectChildList_Items.left	= rectParent.left	+ 20;
	rectChildList_Items.right	= rectParent.right	- 20;
	rectChildList_Items.top		= rectParent.top	+ 40 + DATABASE_NAME_HIGTH + 10 + SQLWORD_HIGH + 10;
	rectChildList_Items.bottom	= rectParent.bottom	- 20;
	ScreenToClient(&rectChildList_Items);
	m_ListRows.MoveWindow(&rectChildList_Items);
}

void CDatabaseConsole::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

}

void CDatabaseConsole::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	ResizeControls();
}


void CDatabaseConsole::OnDblclkListTables(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;
	CString type;
	CString name;
	*pResult = 0;

	type.Empty();
	name.Empty();

	if (row >= 0)
	{
		int nColumnCount = m_ListTables.GetHeaderCtrl()->GetItemCount();
		LVCOLUMN col;
		CString colName;
		TCHAR szName[128];
		col.mask	= LVCF_TEXT;
		col.pszText = szName;
		col.cchTextMax = sizeof(szName) - 1;

		for (int i = 0; i < nColumnCount; i++)
		{
			memset(szName, 0x00, sizeof(szName));
			if (!m_ListTables.GetColumn(i, &col))
				break;

			colName = CString(col.pszText);

			if (colName == "type")
				type	= m_ListTables.GetItemText(row, i);
			else if (colName == "name")
				name	= m_ListTables.GetItemText(row, i);
		}

		if (!type.GetLength() || !name.GetLength())
			return;

		if (type == "table")
		{
			CString databaseName;
			CString connectString;
			int index = m_ListDatabaseName.GetCurSel();
			if (index < 0)
				return;
			m_ListDatabaseName.GetText(index, databaseName);

			connectString.Format(L"SELECT * FROM %s;", name);
			FillListControlFromDBExt(m_hInt, CT2A((LPCTSTR)databaseName), &m_ListRows, CT2A((LPCTSTR)connectString));
		}
	}
}

void CDatabaseConsole::OnContextMenu(CWnd* pWnd, CPoint ptMousePos)
{
	CMenu menu;
	CMenu* pPopup;

	int id = pWnd->GetDlgCtrlID();
	/*
		switch (id)
		{
		case IDC_LIST_PLU_GRUP:
			m_popupMenuActiveControl = id;
			break;
		case IDC_LIST_PLU_GRUP2:
			m_popupMenuActiveControl = id;
			break;
		case IDC_LIST_PLU_ITEM:
			m_popupMenuActiveControl = id;
			break;
		default:
			m_popupMenuActiveControl = NULL;
			return;
		}
		*/
	// if Shift-F10
	if (ptMousePos.x == -1 && ptMousePos.y == -1)
		ptMousePos = (CPoint) GetMessagePos();

	pWnd->ScreenToClient(&ptMousePos);

	// the font popup is stored in a resource
	menu.LoadMenu(IDR_MENU_DATABASE_TABLE_CONTEXT);
	pPopup = menu.GetSubMenu(0);
	pWnd->ClientToScreen(&ptMousePos);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN, ptMousePos.x, ptMousePos.y, this);
}

void CDatabaseConsole::OnMenuDropTable()
{
	POSITION pos = m_ListTables.GetFirstSelectedItemPosition();
	int nColumnCount = m_ListTables.GetHeaderCtrl()->GetItemCount();

	LVCOLUMN col;
	CString colName;
	CString type;
	CString name;
	CString databaseName;
	CString connectString;
	TCHAR szName[128];

	if (pos == NULL)
		return;
	int row = m_ListTables.GetNextSelectedItem(pos);
	if (row < 0)
		return;

	col.mask	= LVCF_TEXT;
	col.pszText = szName;
	col.cchTextMax = sizeof(szName) - 1;

	for (int i = 0; i < nColumnCount; i++)
	{
		memset(szName, 0x00, sizeof(szName));
		if (!m_ListTables.GetColumn(i, &col))
			break;

		colName = CString(col.pszText);

		if (colName == "type")
			type	= m_ListTables.GetItemText(row, i);
		else if (colName == "name")
			name	= m_ListTables.GetItemText(row, i);
	}

	if (!type.GetLength() || !name.GetLength())
		return;

	if (type != "table")
		return;

	int index = m_ListDatabaseName.GetCurSel();
	if (index < 0)
		return;

	connectString.Format(L"Do you really want to DELETE %s %s ?", type, name);
	if (MessageBox(connectString, L"DELETE", MB_OKCANCEL) != IDOK)
		return;

	m_ListDatabaseName.GetText(index, databaseName);
	connectString.Format(L"DROP TABLE IF EXISTS %s;", name);
	DBExecute(m_hInt, CT2A((LPCTSTR)databaseName), &m_ListRows, CT2A((LPCTSTR)connectString));
}


void CDatabaseConsole::OnBnClickedButton1()
{
	CString csSqlword;
	CString databaseName;

	m_EditBoxSqlword.GetWindowTextW(csSqlword);
	if (csSqlword.GetLength() == 0)
		return;

	int index = m_ListDatabaseName.GetCurSel();
	if (index < 0)
	{
		MessageBox(L"Select a Database", L"No Database Selected", MB_OK);
		return;
	}
	m_ListDatabaseName.GetText(index, databaseName);

	FillListControlFromDBExt(m_hInt, CT2A((LPCTSTR)databaseName), &m_ListRows, CT2A((LPCTSTR)csSqlword));
}


void CDatabaseConsole::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	OnBnClickedButton1();
}
