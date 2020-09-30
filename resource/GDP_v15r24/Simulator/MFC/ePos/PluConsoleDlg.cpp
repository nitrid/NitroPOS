// PluConsoleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "PluConsoleDlg.h"
#include "afxdialogex.h"
#include "GetInputDlg.h"
#include "ePosDlg.h"

// CPluConsoleDlg dialog

IMPLEMENT_DYNAMIC(CPluConsoleDlg, CDialogEx)

CPluConsoleDlg::CPluConsoleDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CPluConsoleDlg::IDD, pParent)
		, m_popupMenuActiveControl(0)
{

}

CPluConsoleDlg::~CPluConsoleDlg()
{
}

void CPluConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PLU_GRUP, m_listECRPluGrups);
	DDX_Control(pDX, IDC_LIST_PLU_GRUP2, m_listECRPluGrup2);
	DDX_Control(pDX, IDC_LIST_PLU_ITEM, m_listECRPluItems);
	DDX_Control(pDX, IDC_LIST_HOST_PLU_GRUP, m_listHostPluGrups);
	DDX_Control(pDX, IDC_LIST_HOST_PLU_GRUP2, m_listHostPluGrup2);
	DDX_Control(pDX, IDC_LIST_HOST_PLU_ITEM, m_listHostPluItems);
	DDX_Control(pDX, IDC_BUTTON_UPLOAD_FULL, m_buttonUploadFull);
	DDX_Control(pDX, IDC_LIST_HOST_DB_FILES, m_listHostDbFiles);
	DDX_Control(pDX, IDC_EDIT_HOST_PATH, m_EditHostPath);
	DDX_Control(pDX, IDC_BUTTON_DOWNLOAD_FULL, m_buttonDownloadFull);
	//  DDX_Control(pDX, IDC_EDIT_ECR_PATH, m_EditEcrPath);
	DDX_Control(pDX, IDC_LIST_ECR_DB_FILE, m_listEcrPluFileName);
	DDX_Control(pDX, IDC_BUTTON_REFRESH_PLU_DB_INFO, m_buttonRefreshEcrPluDbInfo);
	DDX_Control(pDX, IDC_BUTTON_SELECT_HoST_DIR, m_ButtonSelectHostDir);
}


BEGIN_MESSAGE_MAP(CPluConsoleDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PLU_GRUP, &CPluConsoleDlg::OnDblclkListPluGrup)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PLU_GRUP2, &CPluConsoleDlg::OnDblclkListPluGrup2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PLU_GRUP, &CPluConsoleDlg::OnRclickListPluGrup)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_MENU_INSERTNEW, &CPluConsoleDlg::OnPopupMenuInsertnew)
	ON_COMMAND(ID_POPUP_MENU_UPDATE, &CPluConsoleDlg::OnPopupMenuUpdate)
	ON_COMMAND(ID_POPUP_MENU_DELETE, &CPluConsoleDlg::OnPopupMenuDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PLU_GRUP, &CPluConsoleDlg::OnClickListPluGrup)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PLU_GRUP2, &CPluConsoleDlg::OnClickListPluGrup2)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PLU_ITEM, &CPluConsoleDlg::OnClickListPluItem)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PLU_GRUP2, &CPluConsoleDlg::OnRclickListPluGrup2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PLU_ITEM, &CPluConsoleDlg::OnRclickListPluItem)
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD_FULL, &CPluConsoleDlg::OnBnClickedButtonUploadFull)
	ON_EN_CHANGE(IDC_EDIT_HOST_PATH, &CPluConsoleDlg::OnChangeEditHostPath)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD_FULL, &CPluConsoleDlg::OnBnClickedButtonDownloadFull)
	//ON_BN_CLICKED(IDC_BUTTON_ECR_SHOW_TABLES, &CPluConsoleDlg::OnBnClickedButtonEcrShowTables)
	ON_LBN_DBLCLK(IDC_LIST_ECR_DB_FILE, &CPluConsoleDlg::OnDblclkListEcrDbFile)
	ON_LBN_DBLCLK(IDC_LIST_HOST_DB_FILES, &CPluConsoleDlg::OnDblclkListHostDbFiles)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_HOST_PLU_GRUP, &CPluConsoleDlg::OnDblclkListHostPluGrup)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_HOST_PLU_GRUP2, &CPluConsoleDlg::OnDblclkListHostPluGrup2)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_PLU_DB_INFO, &CPluConsoleDlg::OnBnClickedButtonRefreshPluDbInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_HOST_PLU_GRUP, &CPluConsoleDlg::OnRclickListHostPluGrup)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_HOST_PLU_GRUP2, &CPluConsoleDlg::OnRclickListHostPluGrup2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_HOST_PLU_ITEM, &CPluConsoleDlg::OnRclickListHostPluItem)
	ON_NOTIFY(NM_CLICK, IDC_LIST_HOST_PLU_GRUP, &CPluConsoleDlg::OnClickListHostPluGrup)
	ON_NOTIFY(NM_CLICK, IDC_LIST_HOST_PLU_GRUP2, &CPluConsoleDlg::OnClickListHostPluGrup2)
	ON_NOTIFY(NM_CLICK, IDC_LIST_HOST_PLU_ITEM, &CPluConsoleDlg::OnClickListHostPluItem)
	ON_LBN_SELCHANGE(IDC_LIST_HOST_DB_FILES, &CPluConsoleDlg::OnLbnSelchangeListHostDbFiles)
	ON_LBN_SELCHANGE(IDC_LIST_ECR_DB_FILE, &CPluConsoleDlg::OnLbnSelchangeListEcrDbFile)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_HoST_DIR, &CPluConsoleDlg::OnBnClickedButtonSelectHostDir)
END_MESSAGE_MAP()


// CPluConsoleDlg message handlers


BOOL CPluConsoleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Current Directory
	TCHAR currentDir[1024];
	GetCurrentDirectory(1024, currentDir);
	m_EditHostPath.SetWindowTextW(currentDir);

	m_listECRPluGrups.SetExtendedStyle(m_listECRPluGrups.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_listECRPluGrup2.SetExtendedStyle(m_listECRPluGrup2.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_listECRPluItems.SetExtendedStyle(m_listECRPluGrup2.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	m_listHostPluGrups.SetExtendedStyle(m_listHostPluGrups.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_listHostPluGrup2.SetExtendedStyle(m_listHostPluGrup2.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_listHostPluItems.SetExtendedStyle(m_listHostPluItems.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	ResizeControls();

	UpdateHostDbFiles();

	RefreshEcrPluDbFileName();

	return TRUE;  // return TRUE unless you set the focus to a control
}

int CPluConsoleDlg::UpdatePluGrups(CListCtrl* plist, int pluGrupParent)
{
	char sqlWord[256];

	sprintf(sqlWord, "SELECT ROWID,* FROM TBL_PLU_GRUP WHERE PLU_GRUP_PARENT=%d;", pluGrupParent);
	return FillListControlFromDBExt(m_hInt, m_PluDbName, plist, sqlWord);
}

int CPluConsoleDlg::UpdateHostPluItems(char* filename, CListCtrl* plist, int pluGrupParent)
{
	char sqlWord[256];

	sprintf(sqlWord, "SELECT ROWID,* FROM TBL_PLU WHERE PLU_GRUP_PARENT=%d;", pluGrupParent);
	return FillListControlFromHostDB(filename, plist, sqlWord);
}

int CPluConsoleDlg::UpdatePluItems(CListCtrl* plist, int pluGrupParent)
{
	char sqlWord[256];

	sprintf(sqlWord, "SELECT ROWID,* FROM TBL_PLU WHERE PLU_GRUP_PARENT=%d;", pluGrupParent);
	return FillListControlFromDBExt(m_hInt, m_PluDbName, plist, sqlWord);
}

int CPluConsoleDlg::GetSelectedId_ECRGrup()
{
	POSITION pos = m_listECRPluGrups.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return -1;

	int row = m_listECRPluGrups.GetNextSelectedItem(pos);

	// ilk Column'da id'si olmalý
	CString cs = m_listECRPluGrups.GetItemText(row, 2);

	return atol(CT2A((LPCTSTR)cs));
}

int CPluConsoleDlg::GetSelectedId_ECRGrup2()
{
	POSITION pos = m_listECRPluGrup2.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return -1;

	int row = m_listECRPluGrup2.GetNextSelectedItem(pos);

	// ilk Column'da id'si olmalý
	CString cs = m_listECRPluGrup2.GetItemText(row, 2);

	return atol(CT2A((LPCTSTR)cs));
}

int CPluConsoleDlg::GetSelectedId_HostGrup()
{
	POSITION pos = m_listHostPluGrups.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return -1;

	int row = m_listHostPluGrups.GetNextSelectedItem(pos);

	// ilk Column'da id'si olmalý
	CString cs = m_listHostPluGrups.GetItemText(row, 2);

	return atol(CT2A((LPCTSTR)cs));
}

int CPluConsoleDlg::GetSelectedId_HostGrup2()
{
	POSITION pos = m_listHostPluGrup2.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return -1;

	int row = m_listHostPluGrup2.GetNextSelectedItem(pos);

	// ilk Column'da id'si olmalý
	CString cs = m_listHostPluGrup2.GetItemText(row, 2);

	return atol(CT2A((LPCTSTR)cs));
}

void CPluConsoleDlg::OnDblclkListPluGrup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;

	UpdatePluGrups(&m_listECRPluGrup2, GetSelectedId_ECRGrup());
}

void CPluConsoleDlg::OnDblclkListPluGrup2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;

	UpdatePluItems(&m_listECRPluItems, GetSelectedId_ECRGrup2());
}

void CPluConsoleDlg::OnRclickListPluGrup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_listECRPluGrups.m_hWnd, GetMessagePos());
	*pResult = 0;
}
void CPluConsoleDlg::OnRclickListPluGrup2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_listECRPluGrup2.m_hWnd, GetMessagePos());
	*pResult = 0;
}
void CPluConsoleDlg::OnRclickListPluItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_listECRPluItems.m_hWnd, GetMessagePos());
	*pResult = 0;
}
void CPluConsoleDlg::OnRclickListHostPluGrup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_listHostPluGrups.m_hWnd, GetMessagePos());
	*pResult = 0;
}
void CPluConsoleDlg::OnRclickListHostPluGrup2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_listHostPluGrup2.m_hWnd, GetMessagePos());
	*pResult = 0;
}
void CPluConsoleDlg::OnRclickListHostPluItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_listHostPluItems.m_hWnd, GetMessagePos());
	*pResult = 0;
}

void CPluConsoleDlg::OnContextMenu(CWnd* pWnd, CPoint ptMousePos)
{
	CMenu menu;
	CMenu* pPopup;

	int id = pWnd->GetDlgCtrlID();

	switch (id)
	{
	case IDC_LIST_PLU_GRUP:
	case IDC_LIST_PLU_GRUP2:
	case IDC_LIST_PLU_ITEM:
	case IDC_LIST_HOST_PLU_GRUP:
	case IDC_LIST_HOST_PLU_GRUP2:
	case IDC_LIST_HOST_PLU_ITEM:
		m_popupMenuActiveControl = id;
		break;
	default:
		m_popupMenuActiveControl = NULL;
		return;
	}

	// if Shift-F10
	if (ptMousePos.x == -1 && ptMousePos.y == -1)
		ptMousePos = (CPoint) GetMessagePos();

	pWnd->ScreenToClient(&ptMousePos);

	// the font popup is stored in a resource
	menu.LoadMenu(IDR_MENU_PLU_CONTEXTMENU);
	pPopup = menu.GetSubMenu(0);
	pWnd->ClientToScreen(&ptMousePos);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN, ptMousePos.x, ptMousePos.y, this);
}

char* CPluConsoleDlg::GetSelectedHostFileName()
{
	CString csFileNameHost;
	static char filename[128];

	memset(filename, 0x00, sizeof(filename));

	int index = m_listHostDbFiles.GetCurSel();
	if (index >= 0)
	{
		m_listHostDbFiles.GetText(index, csFileNameHost);
		csFileNameHost = csFileNameHost.Left(csFileNameHost.Find(' ', 0));

		strcpy(filename,  CT2A((LPCTSTR)csFileNameHost));
	}

	return filename;
}

CString CPluConsoleDlg::GetHeaderName(CListCtrl* plist, int col)
{
	CString columnName;
	HDITEM hdi;
	enum   { sizeOfBuffer = 512 };
	TCHAR  lpBuffer[sizeOfBuffer];
	bool   fFound = false;

	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = sizeOfBuffer;

	plist->GetHeaderCtrl()->GetItem(col, &hdi);
	columnName = CString(hdi.pszText);

	return columnName;
}

CString CPluConsoleDlg::GetUpdateString(CListCtrl* plist, int nItem)
{
	CString output;
	CString columnName;
	CString columnData;

	int nColumnCount = plist->GetHeaderCtrl()->GetItemCount();
	output.Empty();

	for (int i = 1; i < nColumnCount; i++)
	{
		columnName = GetHeaderName(plist, i);
		columnData = plist->GetItemText(nItem, i);

		if (!columnData.GetLength())
			continue;

		if (output.GetLength())
			output.AppendFormat(L",");

		if ((columnName == L"PLU_GRUP_NAME") || (columnName == L"PLU_NAME") || (columnName == L"PLU_BARCODE"))
			output.AppendFormat(L"%s='%s'", columnName, columnData);
		else
			output.AppendFormat(L"%s=%s", columnName, columnData);

	}

	output.AppendFormat(L" WHERE ROWID=%s", plist->GetItemText(nItem, 0));

	return output;
}

CString CPluConsoleDlg::GetDeleteString(CListCtrl* plist, int nItem)
{
	CString output;
	CString columnName;
	CString columnData;

	HDITEM hdi;
	enum   { sizeOfBuffer = 256 };
	TCHAR  lpBuffer[sizeOfBuffer];
	bool   fFound = false;

	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = sizeOfBuffer;

	int nColumnCount = plist->GetHeaderCtrl()->GetItemCount();
	output.Empty();

	output.AppendFormat(L" WHERE ROWID=%s", plist->GetItemText(nItem, 0));

	return output;
}

void CPluConsoleDlg::OnPopupMenuInsertnew()
{
	ST_DATABASE_RESULT stDatabaseResult;
	CString sqlWord;
	sqlWord.Empty();
	CGetInputDlg GetInputDlg;
	int retcode;
	CString grupParentId = CString(L"0");
	CString grupName, GrupId;
	char* hostFileName = NULL;
	sqlite3* db = NULL;
	char *zErrMsg = NULL;

	memset(&stDatabaseResult, 0x00, sizeof(stDatabaseResult));
	stDatabaseResult.StructSize = sizeof(stDatabaseResult);


	// Get All Inputs for the new raw
	switch (m_popupMenuActiveControl)
	{
	case IDC_LIST_HOST_PLU_GRUP2:
	case IDC_LIST_PLU_GRUP2:
		if (GetInputDlg.DoModal(L"GRUP PARENT ID", L"", 2) != IDOK)
			return;
		grupParentId = GetInputDlg.m_input;
		if (!grupParentId.GetLength() || (grupParentId == L"0"))
			return;

	case IDC_LIST_HOST_PLU_GRUP:
	case IDC_LIST_PLU_GRUP:
		if (GetInputDlg.DoModal(L"GRUP ADI", L"", 1) != IDOK)
			return;
		grupName = GetInputDlg.m_input;
		if (GetInputDlg.DoModal(L"GRUP ID", L"", 2) != IDOK)
			return;
		GrupId = GetInputDlg.m_input;

		sqlWord.Format(L"INSERT INTO TBL_PLU_GRUP (PLU_GRUP_ID,PLU_GRUP_NAME,PLU_GRUP_PARENT,PLU_GRUP_FLAG,RECORD_STATUS) VALUES(%s,'%s',%s,0,0);", GrupId, grupName, grupParentId);
		break;

	case IDC_LIST_HOST_PLU_ITEM:
	case IDC_LIST_PLU_ITEM:
	{
		CString pluName, pluBarcode;

		if (GetInputDlg.DoModal(L"GRUP ID", L"", 2) != IDOK)
			return;
		GrupId = GetInputDlg.m_input;

		if (GetInputDlg.DoModal(L"PLU NAME", L"", 1) != IDOK)
			return;
		pluName = GetInputDlg.m_input;

		if (GetInputDlg.DoModal(L"PLU BARCODE", L"", 1) != IDOK)
			return;
		pluBarcode = GetInputDlg.m_input;

		sqlWord.Format(L"INSERT INTO TBL_PLU (PLU_NAME,PLU_BARCODE,PLU_GRUP_PARENT,PLU_FLAG,PLU_AMOUNT1_CURRENCY,PLU_AMOUNT1,RECORD_STATUS) VALUES('%s','%s',%s,0,949,0,0);", pluName, pluBarcode, GrupId);
	}
	break;

	default:
		return;
	}

	switch (m_popupMenuActiveControl)
	{
	case IDC_LIST_PLU_GRUP2:
	case IDC_LIST_PLU_GRUP:
	case IDC_LIST_PLU_ITEM:
		retcode = FP3_Database_Open(m_hInt, m_PluDbName);
		if ((retcode != TRAN_RESULT_OK))
			goto Exit;

		retcode = FP3_Database_Execute(m_hInt,  CT2A((LPCTSTR)sqlWord), &stDatabaseResult);
		if (retcode != TRAN_RESULT_OK)
			goto Exit;

		FP3_Database_FreeStructure(m_hInt, &stDatabaseResult);
		break;

	case IDC_LIST_HOST_PLU_GRUP2:
	case IDC_LIST_HOST_PLU_GRUP:
		hostFileName = GetSelectedHostFileName();
		if (!strlen(hostFileName))
			return;

		retcode = sqlite3_open(hostFileName, &db);
		if ((retcode != SQLITE_OK))
			goto Exit;

		retcode = sqlite3_exec(db, CT2A((LPCTSTR)sqlWord), NULL, 0, &zErrMsg);
		if (retcode != SQLITE_OK)
			goto Exit;
		break;

	case IDC_LIST_HOST_PLU_ITEM:
		hostFileName = GetSelectedHostFileName();
		if (!strlen(hostFileName))
			return;

		retcode = sqlite3_open(hostFileName, &db);
		if ((retcode != SQLITE_OK))
			goto Exit;
#if 1
		retcode = sqlite3_exec(db, CT2A((LPCTSTR)sqlWord), NULL, 0, &zErrMsg);
		if (retcode != SQLITE_OK)
			goto Exit;

		break;
#else

		for (int k = 0; k <= 100000; k++)
		{

			if (!(k % 100))
			{
				CString cs;
				cs.Format(L"Insert Status %d", k);
				SetWindowTextW(cs);
			}

			sqlWord.Empty();
			sqlWord.Format(L"INSERT INTO TBL_PLU (PLU_NAME,PLU_BARCODE,PLU_GRUP_PARENT,PLU_FLAG,PLU_UNIT,PLU_AMOUNT1_CURRENCY,PLU_AMOUNT1,PLU_AMOUNT2_CURRENCY,PLU_AMOUNT2,PLU_AMOUNT3_CURRENCY,PLU_AMOUNT3,RECORD_STATUS) VALUES('PRODUCT %08d','9990%08d',%s,0,1,949,%d,949,%d,949,%d,0);", k + 1, k + 1, GrupId, k + 1, k + 2, k + 3);

			retcode = sqlite3_exec(db, CT2A((LPCTSTR)sqlWord), NULL, 0, &zErrMsg);
			if (retcode != SQLITE_OK)
				goto Exit;
		}
		break;
#endif
	}

Exit:
	if (zErrMsg)
	{
		MessageBox((CString)zErrMsg, L"Error", MB_OK);
		sqlite3_free(zErrMsg);
	}
	else if (retcode != TRAN_RESULT_OK)
		DisplayError(retcode);

	if (FP3_Database_GetHandle(m_hInt))
		FP3_Database_Close(m_hInt);

	if (db)
		sqlite3_close(db);

	switch (m_popupMenuActiveControl)
	{
	case IDC_LIST_PLU_GRUP:
		UpdatePluGrups(&m_listECRPluGrups, 0);
		break;
	case IDC_LIST_HOST_PLU_GRUP:
		UpdateHostPluGrups(hostFileName, &m_listHostPluGrups, 0);
		break;

	case IDC_LIST_PLU_GRUP2:
		UpdatePluGrups(&m_listECRPluGrup2, GetSelectedId_ECRGrup());
		break;
	case IDC_LIST_HOST_PLU_GRUP2:
		UpdateHostPluGrups(hostFileName, &m_listHostPluGrup2, GetSelectedId_HostGrup());
		break;

	case IDC_LIST_PLU_ITEM:
		UpdatePluItems(&m_listECRPluItems, GetSelectedId_ECRGrup2());
		break;
	case IDC_LIST_HOST_PLU_ITEM:
		UpdateHostPluItems(hostFileName, &m_listHostPluItems, GetSelectedId_HostGrup2());
		break;
	default:
		return;
	}
}

void CPluConsoleDlg::OnPopupMenuUpdate()
{
	ST_DATABASE_RESULT stDatabaseResult;
	CString sqlWord;
	sqlWord.Empty();
	CGetInputDlg GetInputDlg;
	int retcode = TRAN_RESULT_OK;
	POSITION pos;
	int nItem = -1;
	CListCtrl* pList = NULL;
	char* hostFileName = NULL;
	sqlite3* db = NULL;
	char *zErrMsg = NULL;

	memset(&stDatabaseResult, 0x00, sizeof(stDatabaseResult));
	stDatabaseResult.StructSize = sizeof(stDatabaseResult);

	switch (m_popupMenuActiveControl)
	{
	case IDC_LIST_PLU_GRUP:
		pList = &m_listECRPluGrups;
		break;
	case IDC_LIST_PLU_GRUP2:
		pList = &m_listECRPluGrup2;
		break;
	case IDC_LIST_PLU_ITEM:
		pList = &m_listECRPluItems;
		break;

	case IDC_LIST_HOST_PLU_GRUP:
		pList = &m_listHostPluGrups;
		break;
	case IDC_LIST_HOST_PLU_GRUP2:
		pList = &m_listHostPluGrup2;
		break;
	case IDC_LIST_HOST_PLU_ITEM:
		pList = &m_listHostPluItems;
		break;

	default:
		return;
	}

	pos = pList->GetFirstSelectedItemPosition();
	if (pos == NULL)
		goto Exit;
	nItem =  pList->GetNextSelectedItem(pos);
	if (nItem < 0)
		goto Exit;

	switch (m_popupMenuActiveControl)
	{
	case IDC_LIST_PLU_GRUP:
	case IDC_LIST_PLU_GRUP2:
	case IDC_LIST_PLU_ITEM:
		retcode = FP3_Database_Open(m_hInt, m_PluDbName);
		if ((retcode != TRAN_RESULT_OK))
			goto Exit;
		break;

	case IDC_LIST_HOST_PLU_GRUP:
	case IDC_LIST_HOST_PLU_GRUP2:
	case IDC_LIST_HOST_PLU_ITEM:
		hostFileName = GetSelectedHostFileName();
		if (!strlen(hostFileName))
			return;

		retcode = sqlite3_open(hostFileName, &db);
		if ((retcode != SQLITE_OK))
			goto Exit;

		break;
	}

	while (nItem >= 0)
	{
		sqlWord.Empty();

		switch (m_popupMenuActiveControl)
		{
		case IDC_LIST_PLU_GRUP:
		case IDC_LIST_PLU_GRUP2:
		case IDC_LIST_HOST_PLU_GRUP:
		case IDC_LIST_HOST_PLU_GRUP2:
			sqlWord.Format(L"UPDATE TBL_PLU_GRUP SET %s;", GetUpdateString(pList, nItem));
			break;
		case IDC_LIST_PLU_ITEM:
		case IDC_LIST_HOST_PLU_ITEM:
			sqlWord.Format(L"UPDATE TBL_PLU SET %s;", GetUpdateString(pList, nItem));
			break;
		default:
			goto Exit;
		}

		switch (m_popupMenuActiveControl)
		{
		case IDC_LIST_PLU_GRUP:
		case IDC_LIST_PLU_GRUP2:
		case IDC_LIST_PLU_ITEM:
			retcode = FP3_Database_Execute(m_hInt,  CT2A((LPCTSTR)sqlWord), &stDatabaseResult);
			if (retcode != TRAN_RESULT_OK)
				goto Exit;

			FP3_Database_FreeStructure(m_hInt, &stDatabaseResult);
			break;

		case IDC_LIST_HOST_PLU_GRUP:
		case IDC_LIST_HOST_PLU_GRUP2:
		case IDC_LIST_HOST_PLU_ITEM:
			retcode = sqlite3_exec(db, CT2A((LPCTSTR)sqlWord), NULL, 0, &zErrMsg);
			if (retcode != SQLITE_OK)
				goto Exit;
			break;
		}

		nItem = pList->GetNextSelectedItem(pos);
	}

Exit:
	if (zErrMsg)
	{
		MessageBox((CString)zErrMsg, L"Error", MB_OK);
		sqlite3_free(zErrMsg);
	}
	else if (retcode != TRAN_RESULT_OK)
		DisplayError(retcode);

	if (FP3_Database_GetHandle(m_hInt))
		FP3_Database_Close(m_hInt);

	if (db)
		sqlite3_close(db);

	switch (m_popupMenuActiveControl)
	{
	case IDC_LIST_PLU_GRUP:
		UpdatePluGrups(&m_listECRPluGrups, 0);
		break;
	case IDC_LIST_HOST_PLU_GRUP:
		UpdateHostPluGrups(hostFileName, &m_listHostPluGrups, 0);
		break;

	case IDC_LIST_PLU_GRUP2:
		UpdatePluGrups(&m_listECRPluGrup2, GetSelectedId_ECRGrup());
		break;
	case IDC_LIST_HOST_PLU_GRUP2:
		UpdateHostPluGrups(hostFileName, &m_listHostPluGrup2, GetSelectedId_HostGrup());
		break;

	case IDC_LIST_PLU_ITEM:
		UpdatePluItems(&m_listECRPluItems, GetSelectedId_ECRGrup2());
		break;
	case IDC_LIST_HOST_PLU_ITEM:
		UpdateHostPluItems(hostFileName, &m_listHostPluItems, GetSelectedId_HostGrup2());
		break;
	default:
		return;
	}
}

void CPluConsoleDlg::OnPopupMenuDelete()
{
	ST_DATABASE_RESULT stDatabaseResult;
	CString sqlWord;
	sqlWord.Empty();
	CGetInputDlg GetInputDlg;
	int retcode;
	POSITION pos;
	int nItem = -1;
	CListCtrl* pList = NULL;
	char* hostFileName = NULL;
	sqlite3* db = NULL;
	char *zErrMsg = NULL;

	memset(&stDatabaseResult, 0x00, sizeof(stDatabaseResult));
	stDatabaseResult.StructSize = sizeof(stDatabaseResult);

	switch (m_popupMenuActiveControl)
	{
	case IDC_LIST_PLU_GRUP:
		pList = &m_listECRPluGrups;
		break;
	case IDC_LIST_PLU_GRUP2:
		pList = &m_listECRPluGrup2;
		break;
	case IDC_LIST_PLU_ITEM:
		pList = &m_listECRPluItems;
		break;

	case IDC_LIST_HOST_PLU_GRUP:
		pList = &m_listHostPluGrups;
		break;
	case IDC_LIST_HOST_PLU_GRUP2:
		pList = &m_listHostPluGrup2;
		break;
	case IDC_LIST_HOST_PLU_ITEM:
		pList = &m_listHostPluItems;
		break;

	default:
		return;
	}

	pos = pList->GetFirstSelectedItemPosition();
	if (pos == NULL)
		goto Exit;
	nItem =  pList->GetNextSelectedItem(pos);
	if (nItem < 0)
		goto Exit;

	switch (m_popupMenuActiveControl)
	{
	case IDC_LIST_PLU_GRUP:
	case IDC_LIST_PLU_GRUP2:
	case IDC_LIST_PLU_ITEM:
		retcode = FP3_Database_Open(m_hInt, m_PluDbName);
		if ((retcode != TRAN_RESULT_OK))
			goto Exit;
		break;

	case IDC_LIST_HOST_PLU_GRUP:
	case IDC_LIST_HOST_PLU_GRUP2:
	case IDC_LIST_HOST_PLU_ITEM:
		hostFileName = GetSelectedHostFileName();
		if (!strlen(hostFileName))
			return;

		retcode = sqlite3_open(hostFileName, &db);
		if ((retcode != SQLITE_OK))
			goto Exit;

		break;
	}

	while (nItem >= 0)
	{
		sqlWord.Empty();

		switch (m_popupMenuActiveControl)
		{
		case IDC_LIST_PLU_GRUP:
		case IDC_LIST_PLU_GRUP2:
		case IDC_LIST_HOST_PLU_GRUP:
		case IDC_LIST_HOST_PLU_GRUP2:
			sqlWord.Format(L"DELETE FROM TBL_PLU_GRUP %s;", GetDeleteString(pList, nItem));
			break;
		case IDC_LIST_PLU_ITEM:
		case IDC_LIST_HOST_PLU_ITEM:
			sqlWord.Format(L"DELETE FROM TBL_PLU %s;", GetDeleteString(pList, nItem));
			break;
		default:
			goto Exit;
		}

		switch (m_popupMenuActiveControl)
		{
		case IDC_LIST_PLU_GRUP:
		case IDC_LIST_PLU_GRUP2:
		case IDC_LIST_PLU_ITEM:
			retcode = FP3_Database_Execute(m_hInt,  CT2A((LPCTSTR)sqlWord), &stDatabaseResult);
			if (retcode != TRAN_RESULT_OK)
				goto Exit;

			FP3_Database_FreeStructure(m_hInt, &stDatabaseResult);
			break;

		case IDC_LIST_HOST_PLU_GRUP:
		case IDC_LIST_HOST_PLU_GRUP2:
		case IDC_LIST_HOST_PLU_ITEM:
			retcode = sqlite3_exec(db, CT2A((LPCTSTR)sqlWord), NULL, 0, &zErrMsg);
			if (retcode != SQLITE_OK)
				goto Exit;
			break;
		}

		nItem = pList->GetNextSelectedItem(pos);
	}

Exit:
	if (zErrMsg)
	{
		MessageBox((CString)zErrMsg, L"Error", MB_OK);
		sqlite3_free(zErrMsg);
	}
	else if (retcode != TRAN_RESULT_OK)
		DisplayError(retcode);

	if (FP3_Database_GetHandle(m_hInt))
		FP3_Database_Close(m_hInt);

	if (db)
		sqlite3_close(db);

	switch (m_popupMenuActiveControl)
	{
	case IDC_LIST_PLU_GRUP:
		UpdatePluGrups(&m_listECRPluGrups, 0);
		break;
	case IDC_LIST_HOST_PLU_GRUP:
		UpdateHostPluGrups(hostFileName, &m_listHostPluGrups, 0);
		break;

	case IDC_LIST_PLU_GRUP2:
		UpdatePluGrups(&m_listECRPluGrup2, GetSelectedId_ECRGrup());
		break;
	case IDC_LIST_HOST_PLU_GRUP2:
		UpdateHostPluGrups(hostFileName, &m_listHostPluGrup2, GetSelectedId_HostGrup());
		break;

	case IDC_LIST_PLU_ITEM:
		UpdatePluItems(&m_listECRPluItems, GetSelectedId_ECRGrup2());
		break;
	case IDC_LIST_HOST_PLU_ITEM:
		UpdateHostPluItems(hostFileName, &m_listHostPluItems, GetSelectedId_HostGrup2());
		break;
	default:
		return;
	}
}

void CPluConsoleDlg::DisplayError(int retcode)
{
	char ErrorString[128];
	GetErrorMessage(retcode, ErrorString);
	CString cs = CString(ErrorString);
	MessageBox(cs, L"Error", MB_OK);
}

void CPluConsoleDlg::ResizeControls(void)
{
#define GROUP_1_HIGH			150
#define GROUP_2_HIGH			150
#define DBNAME_HIGH				30
#define MARGIN					4

	CRect rectParent;
	CRect rectParentOrg;
	CRect rectChildList_Items;

	GetWindowRect(&rectParent);
	GetWindowRect(&rectParentOrg);

	int LEFT	= rectParent.left + (4 * MARGIN);
	int MIDDLE1	= rectParent.left + (rectParent.Width() / 2) - (2 * MARGIN);
	int MIDDLE2	= rectParent.left + (rectParent.Width() / 2) + (2 * MARGIN);
	int RIGHT	= rectParent.right - (4 * MARGIN);
	int TOP		= rectParent.top + (12 * MARGIN);
	int BOTTOM	= rectParent.bottom - (4 * MARGIN);

	//=====================================================================================
	//m_EditHostPath
	rectChildList_Items.left	= LEFT;
	rectChildList_Items.right	= MIDDLE1 - (16 * MARGIN);
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + (1 * DBNAME_HIGH) - MARGIN;
	ScreenToClient(&rectChildList_Items);
	m_EditHostPath.MoveWindow(&rectChildList_Items);
	// m_ButtonSelectHostDir
	rectChildList_Items.left	= MIDDLE1 - (15 * MARGIN);
	rectChildList_Items.right	= MIDDLE1;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + (1 * DBNAME_HIGH) - MARGIN;
	ScreenToClient(&rectChildList_Items);
	m_ButtonSelectHostDir.MoveWindow(&rectChildList_Items);
	// m_EditEcrPath
	rectChildList_Items.left	= MIDDLE2;
	rectChildList_Items.right	= RIGHT;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + (1 * DBNAME_HIGH) - MARGIN;
	ScreenToClient(&rectChildList_Items);
	m_buttonRefreshEcrPluDbInfo.MoveWindow(&rectChildList_Items);
	m_buttonRefreshEcrPluDbInfo.SetWindowTextW(L"REFRESH ECR PLU DB Name (Size) / Grups LastModified / Items LastModified");
	TOP += ((1 * DBNAME_HIGH) + MARGIN);

	//=====================================================================================
	//m_EditHostPluDbName
	rectChildList_Items.left	= LEFT;
	rectChildList_Items.right	= MIDDLE1;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + (2 * DBNAME_HIGH);
	ScreenToClient(&rectChildList_Items);
	m_listHostDbFiles.MoveWindow(&rectChildList_Items);
	//m_EditEcrPluDbName
	rectChildList_Items.left	= MIDDLE2;
	rectChildList_Items.right	= RIGHT;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + (2 * DBNAME_HIGH);
	ScreenToClient(&rectChildList_Items);
	m_listEcrPluFileName.MoveWindow(&rectChildList_Items);
	TOP += ((2 * DBNAME_HIGH) + (1 * MARGIN));

	//=====================================================================================
	//m_buttonDownloadFull
	rectChildList_Items.left	= LEFT + (MIDDLE1 - LEFT) / 2;
	rectChildList_Items.right	= MIDDLE1;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + (1 * DBNAME_HIGH);
	ScreenToClient(&rectChildList_Items);
	m_buttonDownloadFull.MoveWindow(&rectChildList_Items);
	//m_buttonUploadFull
	rectChildList_Items.left	= MIDDLE2;
	rectChildList_Items.right	= MIDDLE2 + (RIGHT - MIDDLE2) / 2;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + (1 * DBNAME_HIGH);
	ScreenToClient(&rectChildList_Items);
	m_buttonUploadFull.MoveWindow(&rectChildList_Items);
	TOP += ((1 * DBNAME_HIGH) + (3 * MARGIN));

	//=====================================================================================
	// m_listHostPluGrups Names
	rectChildList_Items.left	= LEFT;
	rectChildList_Items.right	= MIDDLE1;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + GROUP_1_HIGH;
	ScreenToClient(&rectChildList_Items);
	m_listHostPluGrups.MoveWindow(&rectChildList_Items);
	// m_listECRPluGrups Names
	rectChildList_Items.left	= MIDDLE2;
	rectChildList_Items.right	= RIGHT;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + GROUP_1_HIGH;
	ScreenToClient(&rectChildList_Items);
	m_listECRPluGrups.MoveWindow(&rectChildList_Items);
	TOP += (GROUP_1_HIGH + MARGIN);

	//=====================================================================================
	// m_listHostPluGrup2 Names
	rectChildList_Items.left	= LEFT;
	rectChildList_Items.right	= MIDDLE1;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + GROUP_2_HIGH;
	ScreenToClient(&rectChildList_Items);
	m_listHostPluGrup2.MoveWindow(&rectChildList_Items);
	// m_listECRPluGrup2 Names
	rectChildList_Items.left	= MIDDLE2;
	rectChildList_Items.right	= RIGHT;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= TOP + GROUP_2_HIGH;
	ScreenToClient(&rectChildList_Items);
	m_listECRPluGrup2.MoveWindow(&rectChildList_Items);
	TOP += (GROUP_2_HIGH + MARGIN);

	//=====================================================================================
	// m_listHostPluItems Names
	rectChildList_Items.left	= LEFT;
	rectChildList_Items.right	= MIDDLE1;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= BOTTOM;
	ScreenToClient(&rectChildList_Items);
	m_listHostPluItems.MoveWindow(&rectChildList_Items);
	// m_listECRPluItems Names
	rectChildList_Items.left	= MIDDLE2;
	rectChildList_Items.right	= RIGHT;
	rectChildList_Items.top		= TOP;
	rectChildList_Items.bottom	= BOTTOM;
	ScreenToClient(&rectChildList_Items);
	m_listECRPluItems.MoveWindow(&rectChildList_Items);
	TOP = BOTTOM + MARGIN;
}

void CPluConsoleDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	ResizeControls();
	// TODO: Add your message handler code here
}

int CPluConsoleDlg::UpdateHostDbFiles(void)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	m_listHostDbFiles.ResetContent();

	hFind = FindFirstFileEx(L"*.d", FindExInfoStandard
							, &FindFileData
							, FindExSearchNameMatch
							, NULL
							, 0
						   );
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFileEx failed (%d)\n", GetLastError());
		return 0;
	}
	else
	{
		do
		{
			CString filename;

			uint32 lastModifiedPluGrups = GetMax_LastModified(CT2A((LPCTSTR)FindFileData.cFileName), "TBL_PLU_GRUP");
			uint32 lastModifiedPluItems = GetMax_LastModified(CT2A((LPCTSTR)FindFileData.cFileName), "TBL_PLU");

			filename.Format(L"%s (%ld bytes) / %d / %d", FindFileData.cFileName, FindFileData.nFileSizeLow, lastModifiedPluGrups, lastModifiedPluItems);
			m_listHostDbFiles.AddString(filename);

		}
		while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}

	return 0;
}

int CPluConsoleDlg::CreateDatabase(sqlite3* db, char* dbName)
{
	return 0;
	/*	int retcode;
		uint16 numberOfColumns = 24;
		ST_DATABASE_RESULT stDatabaseResult;
		char swlWord[256]= "SELECT sql FROM sqlite_master;";

		memset( &stDatabaseResult, 0x00, sizeof(stDatabaseResult));
		stDatabaseResult.StructSize = sizeof(stDatabaseResult);

		retcode = _Database_Open(dbName);
		if( (retcode != TRAN_RESULT_OK)  )
			goto Exit;

		retcode = _Database_Query( swlWord, &numberOfColumns );
		if( retcode != TRAN_RESULT_OK )
			goto Exit;

		if( (retcode = _Database_QueryColomnCaptions(&stDatabaseResult)) == TRAN_RESULT_OK )
		{
			if( stDatabaseResult.pstCaptionArray )
			{
				_Database_FreeStructure(&stDatabaseResult);

				do
				{
					retcode = _Database_QueryReadLine( 50, numberOfColumns, &stDatabaseResult);
					if( (retcode != SQLITE_ROW) && (retcode != SQLITE_DONE) )
						break;

					for( int line=0;line<stDatabaseResult.numberOfLines;line++ )
					{
						MessageBox((CString)stDatabaseResult.pstLineArray[line].pstColomnArray[0].data, L"", MB_OK);

					}
				}while( retcode == SQLITE_ROW );
			}
		}

		_Database_FreeStructure(&stDatabaseResult);
		retcode = _Database_QueryFinish();

	Exit:
		if( _Database_GetHandle() )
			_Database_Close();

		if( retcode )
		{
			char ErrorString[128];
			GetErrorMessage( retcode, ErrorString );
			MessageBox( (CString) ErrorString, L"Return Code", MB_OK );
		}

		return retcode;
	*/
}

void CPluConsoleDlg::OnBnClickedButtonUploadFull()
{
	char HostFileName[64];
	int retcode;

	uint32	offset = 0;
	uint32	whence = 0;
	uint8	buffer[1024];
	uint16  ReadLen;

	if (strlen(m_PluDbName) == 0)
		return;

	memset(HostFileName, 0x00, sizeof(HostFileName));
	strcpy(HostFileName, m_PluDbName);

	if (PathFileExists((CString)HostFileName))
	{
		if (MessageBox(L"A file with the same name already exists in the host computer. It will be removed if you continue. Do you want to proceed?", L"WARNINIG", MB_OKCANCEL) != IDOK)
			return;
	}

	DeleteFile((CString)HostFileName);

	FILE* pFileHost = fopen(HostFileName, "ab");
	if (pFileHost == NULL)
	{
		MessageBox(L"File can not be opened in host computer", L"fopen", MB_OK);
		return;
	}
	fseek(pFileHost, 0, 0);

	uint64 time1 = GetTickCount64();

	while (1)
	{

Label_Retry:
		do
		{
			retcode = FP3_FileSystem_FileRead(m_hInt, m_PluDbName, offset, FS_SEEKSET, buffer, sizeof(buffer), &ReadLen);
			if (retcode == DLL_RETCODE_RECV_BUSY)
				Sleep(1000);
		}
		while (retcode == DLL_RETCODE_RECV_BUSY);

		if (retcode == APP_ERR_FILE_EOF)
			break;

		if (retcode != TRAN_RESULT_OK)
		{
			char ErrorString[128];
			GetErrorMessage(retcode, ErrorString);

			if (MessageBox((CString)ErrorString, L"RETRY ?", MB_RETRYCANCEL) != IDRETRY)
				goto Exit;
			goto Label_Retry;
		}

		if (fwrite(buffer, 1, ReadLen, pFileHost) != ReadLen)
			MessageBox(L"File Write Error", L"fwrite", MB_OK);

		offset += ReadLen;

		if (m_PluDbSize)
		{
			uint64 time2 = GetTickCount64();

			unsigned long long perc = (offset * 10000) / m_PluDbSize;
			unsigned long long elapsedSecond = ((time2 - time1) / 1000);
			unsigned long long remaingSecond = 0;
			if (perc)
				remaingSecond = ((elapsedSecond * 10000) / (perc)) - elapsedSecond;

			CString cs;
			cs.Format(L"Upload Status %%%ld.%02ld  (%d:%02d:%02d secs)", perc / 100, perc % 100, remaingSecond / 3600, (remaingSecond % 3600) / 60, (remaingSecond % 3600) % 60);
			SetWindowTextW(cs);
		}
		DoEvents();
	}

	SetWindowTextW(L"PLU Console");

	if (retcode == APP_ERR_FILE_EOF)
	{
		fclose(pFileHost);
		pFileHost = NULL;

		UpdateHostDbFiles();

		MessageBox(L"File has succesfully uploaded", L"File Upload", MB_OK);
		retcode = TRAN_RESULT_OK;
	}

Exit:
	if (pFileHost)
		fclose(pFileHost);

	if (retcode)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox((CString) ErrorString, L"Return Code", MB_OK);
	}
}

void CPluConsoleDlg::OnChangeEditHostPath()
{
	CString csHostDir;
	m_listHostDbFiles.ResetContent();

	m_EditHostPath.GetWindowText(csHostDir);

	if (!SetCurrentDirectory(csHostDir))
		return;

	UpdateHostDbFiles();
}

void CPluConsoleDlg::RefreshEcrPluDbFileName()
{
	int retcode = TRAN_RESULT_OK;
	CString cs;
	CString csPluDbName;
	uint16 PluDbType;
	uint32 PluDbGrupsLastModified;
	uint32 PluDbItemsLastModified;

	m_PluDbSize = 0;
	memset(m_PluDbName, 0x00, sizeof(m_PluDbName));
	retcode = FP3_GetPluDatabaseInfo(m_hInt, m_PluDbName, &PluDbType, (uint32*) & m_PluDbSize, &PluDbGrupsLastModified, &PluDbItemsLastModified);
	if (retcode != TRAN_RESULT_OK)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);

		MessageBox((CString)ErrorString, L"ERROR", MB_OK);
		return;
	}

	csPluDbName = CString(m_PluDbName);
	cs.Format(L"%s (%ld bytes) / %ld / %ld", csPluDbName, m_PluDbSize, PluDbGrupsLastModified, PluDbItemsLastModified);

	m_listEcrPluFileName.ResetContent();
	m_listEcrPluFileName.AddString(cs);
}

void CPluConsoleDlg::OnBnClickedButtonDownloadFull()
{
#define TEMP_FILE_NAME "tmp.tmp"

	int retcode = TRAN_RESULT_OK;

	unsigned long long sourceFileSize = 0;
	unsigned long long sourceFileOffset = 0;

	FILE* pSourceFileHandle = NULL;
	char* sourceFileName = GetSelectedHostFileName();
	if (!strlen(sourceFileName))
		return;

	if (strcmp(m_PluDbName, sourceFileName))
	{
		// that means; PLU DB Name in ECR and the new file name (to be downloaded into ECR) are not the same. So, ECR PLU DB file name will be changed !!
		if (MessageBox(L"The existnig ECR PLU DB file name will be changed. Do you want to proceed?", L"WARNINIG", MB_OKCANCEL) != IDOK)
			return;
	}
	else
	{
		if (MessageBox(L"Current PLU DB file in ECR will be removed. Do you want to proceed?", L"WARNINIG", MB_OKCANCEL) != IDOK)
			return;
	}

	pSourceFileHandle = fopen(sourceFileName, "rb");
	if (pSourceFileHandle == NULL)
	{
		MessageBox(L"File can not opened in Host Computer", L"fopen", MB_OK);
		goto Exit;
	}

	// Get the full size of the SOURCE file
	fseek(pSourceFileHandle , 0 , SEEK_END);
	sourceFileSize = ftell(pSourceFileHandle);
	fseek(pSourceFileHandle , 0 , SEEK_SET);

	// Remove temp file in ECR (if any)
	retcode = FP3_FileSystem_FileRemove(m_hInt, TEMP_FILE_NAME);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	uint64 time1 = GetTickCount64();

	while (sourceFileOffset < sourceFileSize)
	{
		byte buffer[1024*3];
		int errorCounter = 0;

		int ReadLen = (int)fread(buffer, 1, sizeof(buffer), pSourceFileHandle);
		if (ReadLen == 0)
			goto Exit;

Label_Retry:
		do
		{
			retcode = FP3_FileSystem_FileWrite(m_hInt, TEMP_FILE_NAME, (uint32)sourceFileOffset, FS_SEEKSET, buffer, ReadLen);

			switch (retcode)
			{
			case TRAN_RESULT_OK:
				break;
			case DLL_RETCODE_RECV_BUSY:
				Sleep(1000);
				break;
			default:
				errorCounter++;
				Sleep(500);
				break;
			}

			if (errorCounter > 3)
				break;
		}
		while (retcode != TRAN_RESULT_OK);

		if (retcode != TRAN_RESULT_OK)
		{
			char ErrorString[128];
			GetErrorMessage(retcode, ErrorString);

			if (MessageBox((CString)ErrorString, L"RETRY DOWNLOAD ?", MB_RETRYCANCEL) != IDRETRY)
				goto Exit;
			goto Label_Retry;
		}

		sourceFileOffset += ReadLen;

		if (sourceFileSize)
		{
			uint64 time2 = GetTickCount64();

			unsigned long long perc = (sourceFileOffset * 10000) / sourceFileSize;
			unsigned long long elapsedSecond = ((time2 - time1) / 1000);
			unsigned long long remaingSecond = 0;
			if (perc)
				remaingSecond = ((elapsedSecond * 10000) / (perc)) - elapsedSecond;

			CString cs;
			cs.Format(L"Download Status %%%ld.%02ld  (%d:%02d:%02d secs)", perc / 100, perc % 100, remaingSecond / 3600, (remaingSecond % 3600) / 60, (remaingSecond % 3600) % 60);
			SetWindowTextW(cs);
		}
		DoEvents();
	}

	// Remove old PLU DB file in ECR
	retcode = FP3_FileSystem_FileRemove(m_hInt, m_PluDbName);
	if (retcode != TRAN_RESULT_OK)
	{
		MessageBox(L"FP3_FileSystem_FileRemove", L"ERROR", MB_OK);
		goto Exit;
	}

	// Rename temp file
	retcode = FP3_FileSystem_FileRename(m_hInt, TEMP_FILE_NAME, sourceFileName);
	if (retcode != TRAN_RESULT_OK)
	{
		MessageBox(L"FP3_FileSystem_FileRename", L"ERROR", MB_OK);
		goto Exit;
	}

	retcode = FP3_SetPluDatabaseInfo(m_hInt, sourceFileName, 0);
	if (retcode != TRAN_RESULT_OK)
	{
		MessageBox(L"FP3_SetPluDatabaseInfo", L"ERROR", MB_OK);
		goto Exit;
	}

Exit:
	SetWindowTextW(L"PLU Console");

	if (pSourceFileHandle)
		fclose(pSourceFileHandle);

	RefreshEcrPluDbFileName();

	if (retcode)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox((CString) ErrorString, L"Return Code", MB_OK);
	}
}

void CPluConsoleDlg::OnDblclkListEcrDbFile()
{
	UpdatePluGrups(&m_listECRPluGrups, 0);

	m_listECRPluGrup2.DeleteAllItems();
	m_listECRPluItems.DeleteAllItems();
}

void CPluConsoleDlg::OnDblclkListHostDbFiles()
{
	char* hostFileName = GetSelectedHostFileName();
	if (!strlen(hostFileName))
		return;

	UpdateHostPluGrups(hostFileName, &m_listHostPluGrups, 0);

	m_listHostPluGrup2.DeleteAllItems();
	m_listHostPluItems.DeleteAllItems();
}

int CPluConsoleDlg::UpdateHostPluGrups(char* FileName, CListCtrl* plist, int pluGrupParent)
{
	char sqlWord[256];

	sprintf(sqlWord, "SELECT ROWID,* FROM TBL_PLU_GRUP WHERE PLU_GRUP_PARENT=%d;", pluGrupParent);
	return FillListControlFromHostDB(FileName, plist, sqlWord);
}

int CPluConsoleDlg::FillListControlFromHostDB(char* dbName, CListCtrl* plistCtrl, char* swlWord)
{
	sqlite3 *db = NULL;
	char *zErrMsg = 0;
	int retcode;
	uint16 numberOfColumns = 24;
	sqlite3_stmt* psqlite3_stmt = NULL;
	int dbNumberOfTotalColumns;

	CRect rect;
	plistCtrl->GetWindowRect(&rect);
	plistCtrl->DeleteAllItems();

	int nColumnCount = plistCtrl->GetHeaderCtrl()->GetItemCount();
	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
		plistCtrl->DeleteColumn(0);

	retcode = sqlite3_open(dbName, &db);
	if ((retcode != SQLITE_OK))
		goto Exit;

	retcode = sqlite3_prepare_v2(db, swlWord, -1, &psqlite3_stmt, 0);
	if (retcode != SQLITE_OK)
		goto Exit;
	dbNumberOfTotalColumns = sqlite3_column_count(psqlite3_stmt);

	for (int i = 0; i < dbNumberOfTotalColumns; i++)
	{
		CString cs = CString((char*)sqlite3_column_name(psqlite3_stmt, i));
		plistCtrl->InsertColumn(i, cs);
		plistCtrl->SetColumnWidth(i, cs.GetLength() * 8);
	}

	do
	{
//		DoEvents();

		retcode = sqlite3_step(psqlite3_stmt);
		if (retcode != SQLITE_ROW)
			break;

		int nItem = plistCtrl->InsertItem(LVIF_TEXT | LVIF_STATE, plistCtrl->GetItemCount(), L"", NULL, NULL, 0, 0);

		for (int i = 0; i < dbNumberOfTotalColumns; i++)
		{
			char data[2048];
			memset(data, 0x00, sizeof(data));
			switch (sqlite3_column_type(psqlite3_stmt, i))
			{
			case SQLITE_FLOAT:
			case SQLITE_INTEGER:
				sprintf(data, "%ld", sqlite3_column_int(psqlite3_stmt, i));
				break;
			case SQLITE_TEXT: // string
				strcpy(data, (char*)sqlite3_column_text(psqlite3_stmt, i));
				break;
			case SQLITE_NULL: // byte
			case SQLITE_BLOB: // blob
			default:
				strcpy(data, "");
				break;
			}
			InsertItemText(plistCtrl, nItem, i, "%s", data);

			if (plistCtrl->GetColumnWidth(i) < (int)strlen(data)*8)
				plistCtrl->SetColumnWidth(i, (int)strlen(data)*8);
		}
	}
	while (retcode == SQLITE_ROW);

	if (retcode == SQLITE_DONE)
		retcode = SQLITE_OK;

Exit:
	if (psqlite3_stmt)
		sqlite3_finalize(psqlite3_stmt);
	psqlite3_stmt = NULL;

	if (db)
		sqlite3_close(db);
	db = NULL;

	if (retcode)
	{
		CString cs;
		cs.Format(L"sqlite error code %d", retcode);
		MessageBox(cs, L"Return Code", MB_OK);
	}

	return retcode;
}

void CPluConsoleDlg::OnDblclkListHostPluGrup(NMHDR *pNMHDR, LRESULT *pResult)
{
	char* hostFileName = GetSelectedHostFileName();
	if (!strlen(hostFileName))
		return;

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;

	UpdateHostPluGrups(hostFileName, &m_listHostPluGrup2, GetSelectedId_HostGrup());
}


void CPluConsoleDlg::OnDblclkListHostPluGrup2(NMHDR *pNMHDR, LRESULT *pResult)
{
	char* hostFileName = GetSelectedHostFileName();
	if (!strlen(hostFileName))
		return;

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;

	UpdateHostPluItems(hostFileName, &m_listHostPluItems, GetSelectedId_HostGrup2());
}

void CPluConsoleDlg::OnBnClickedButtonRefreshPluDbInfo()
{
	RefreshEcrPluDbFileName();
}

uint32 CPluConsoleDlg::GetMax_LastModified(char* filename, char* TableName)
{
	int16 	retcode;
	char 	zSql[1024];
	sqlite3_stmt	*sqlStmt;
	uint32 lastModified = 0;
	sqlite3* db = NULL;

	retcode = sqlite3_open(filename, &db);
	if (retcode != SQLITE_OK)
		goto Exit;

	sprintf(zSql, "SELECT MAX(LAST_MODIFIED) FROM %s;", TableName);
	retcode = sqlite3_prepare_v2(db, zSql, -1, &sqlStmt, 0);
	if (retcode != SQLITE_OK)
		goto Exit;

	// fetch a row's status
	if (sqlite3_step(sqlStmt) == SQLITE_ROW)
		lastModified = sqlite3_column_int(sqlStmt, 0);
	sqlite3_finalize(sqlStmt);

Exit:
	if (db)
	{
		sqlite3_close(db);
		db = NULL;
	}

	return lastModified;
}

void CPluConsoleDlg::OnClickListPluGrup(NMHDR *pNMHDR, LRESULT *pResult)
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
		return;
	case 4:
		type = 1;
		break;
	default:
		type = 2;
		break;
	}

	CString cs = m_listECRPluGrups.GetItemText(row, column);
	if (GetInputDlg.DoModal(GetHeaderName(&m_listECRPluGrups, column), cs, type) != IDOK)
		return;
	m_listECRPluGrups.SetItemText(row, column, GetInputDlg.m_input);
}

void CPluConsoleDlg::OnClickListPluGrup2(NMHDR *pNMHDR, LRESULT *pResult)
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
		return;
	case 4:
		type = 1;
		break;
	default:
		type = 2;
		break;
	}

	CString cs = m_listECRPluGrup2.GetItemText(row, column);
	if (GetInputDlg.DoModal(GetHeaderName(&m_listECRPluGrup2, column), cs, type) != IDOK)
		return;
	m_listECRPluGrup2.SetItemText(row, column, GetInputDlg.m_input);
}
void CPluConsoleDlg::OnClickListPluItem(NMHDR *pNMHDR, LRESULT *pResult)
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
		return;
	case 1:
	case 5:
		type = 1;
		break;
	default:
		type = 2;
		break;
	}

	CString cs = m_listECRPluItems.GetItemText(row, column);
	if (GetInputDlg.DoModal(GetHeaderName(&m_listECRPluItems, column), cs, type) != IDOK)
		return;
	m_listECRPluItems.SetItemText(row, column, GetInputDlg.m_input);
}


void CPluConsoleDlg::OnClickListHostPluGrup(NMHDR *pNMHDR, LRESULT *pResult)
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
		return;
	case 4:
		type = 1;
		break;
	default:
		type = 2;
		break;
	}

	CString cs = m_listHostPluGrups.GetItemText(row, column);
	if (GetInputDlg.DoModal(GetHeaderName(&m_listHostPluGrups, column), cs, type) != IDOK)
		return;
	m_listHostPluGrups.SetItemText(row, column, GetInputDlg.m_input);
}


void CPluConsoleDlg::OnClickListHostPluGrup2(NMHDR *pNMHDR, LRESULT *pResult)
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
		return;
	case 4:
		type = 1;
		break;
	default:
		type = 2;
		break;
	}

	CString cs = m_listHostPluGrup2.GetItemText(row, column);
	if (GetInputDlg.DoModal(GetHeaderName(&m_listHostPluGrup2, column), cs, type) != IDOK)
		return;
	m_listHostPluGrup2.SetItemText(row, column, GetInputDlg.m_input);
}

void CPluConsoleDlg::OnClickListHostPluItem(NMHDR *pNMHDR, LRESULT *pResult)
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
		return;
	case 1:
	case 5:
		type = 1;
		break;
	default:
		type = 2;
		break;
	}

	CString cs = m_listHostPluItems.GetItemText(row, column);
	if (GetInputDlg.DoModal(GetHeaderName(&m_listHostPluItems, column), cs, type) != IDOK)
		return;
	m_listHostPluItems.SetItemText(row, column, GetInputDlg.m_input);
}


void CPluConsoleDlg::OnLbnSelchangeListHostDbFiles()
{
	// TODO: Add your control notification handler code here
}


void CPluConsoleDlg::OnLbnSelchangeListEcrDbFile()
{
	// TODO: Add your control notification handler code here
}


void CPluConsoleDlg::OnBnClickedButtonSelectHostDir()
{
	BROWSEINFO bi = {0};
	bi.lpszTitle = _T("Select Folder");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl != 0)
	{
		// get the name of the folder
		TCHAR path[MAX_PATH];
		SHGetPathFromIDList(pidl, path);

		// free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		m_EditHostPath.SetWindowTextW(path);

	}
}
