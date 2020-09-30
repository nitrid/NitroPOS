// FileSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "FileSystemDlg.h"
#include "afxdialogex.h"
#include "GetInputDlg.h"


// CFileSystemDlg dialog

IMPLEMENT_DYNAMIC(CFileSystemDlg, CDialogEx)

CFileSystemDlg::CFileSystemDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CFileSystemDlg::IDD, pParent)
{

}

CFileSystemDlg::~CFileSystemDlg()
{
}

void CFileSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOST_FILES, m_ListHostFiles);
	DDX_Control(pDX, IDC_EDIT_HOST_DIR, m_EditHostDir);
	DDX_Control(pDX, IDC_LIST_ECR_FILES, m_ListEcrFiles);
	DDX_Control(pDX, IDC_BUTTON_ECR_DIR, m_ButtonEcrDir);
}


BEGIN_MESSAGE_MAP(CFileSystemDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_HOST_DIR, &CFileSystemDlg::OnBnClickedButtonHostDir)
	ON_EN_CHANGE(IDC_EDIT_HOST_DIR, &CFileSystemDlg::OnEnChangeEditHostDir)
	ON_BN_CLICKED(IDC_BUTTON_ECR_DIR, &CFileSystemDlg::OnBnClickedButtonEcrDir)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ECR_FILES, &CFileSystemDlg::OnNMDblclkListEcrFiles)
	ON_BN_CLICKED(IDC_BUTTON_ECR_ROOT, &CFileSystemDlg::OnBnClickedButtonEcrRoot)
	ON_BN_CLICKED(IDC_BUTTON_COPY_TO_ECR, &CFileSystemDlg::OnBnClickedButtonCopyToEcr)
	ON_BN_CLICKED(IDC_BUTTON_COPY_TO_HOST, &CFileSystemDlg::OnBnClickedButtonCopyToHost)
	ON_BN_CLICKED(IDC_BUTTON_ECR_REMOVE, &CFileSystemDlg::OnBnClickedButtonEcrRemove)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_HOST_FILES, &CFileSystemDlg::OnNMDblclkListHostFiles)
	ON_BN_CLICKED(IDC_BUTTON_ECR_RENAME, &CFileSystemDlg::OnBnClickedButtonEcrRename)
END_MESSAGE_MAP()


// CFileSystemDlg message handlers


void CFileSystemDlg::ListHostFiles()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	m_ListHostFiles.DeleteAllItems();

	hFind = FindFirstFileEx(L"*.*", FindExInfoStandard
							, &FindFileData
							, FindExSearchNameMatch
							, NULL
							, 0
						   );
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			CString filename;

			int index = m_ListHostFiles.InsertItem(LVIF_TEXT | LVIF_STATE, m_ListHostFiles.GetItemCount(), NULL, 0, LVIS_SELECTED, 0, 0);

			CString csLine;
			csLine.Format(L"%d", FindFileData.nFileSizeLow);
			if (FindFileData.nFileSizeLow)
			{
				m_ListHostFiles.SetItemText(index, 0, FindFileData.cFileName);
				m_ListHostFiles.SetItemText(index, 1, csLine);
			}
			else
				m_ListHostFiles.SetItemText(index, 0, L"/" + CString(FindFileData.cFileName));

		}
		while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
}

void CFileSystemDlg::OnBnClickedButtonHostDir()
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

		m_EditHostDir.SetWindowTextW(path);

	}
}


BOOL CFileSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListHostFiles.InsertColumn(0, L"Name", 0);
	m_ListHostFiles.InsertColumn(1, L"Size", 0);
	m_ListHostFiles.SetColumnWidth(0, 300);
	m_ListHostFiles.SetColumnWidth(1, 70);

	m_ListEcrFiles.InsertColumn(0, L"Name", 0);
	m_ListEcrFiles.InsertColumn(1, L"Size", 0);
	m_ListEcrFiles.SetColumnWidth(0, 300);
	m_ListEcrFiles.SetColumnWidth(1, 70);

	TCHAR buffer[512];
	GetCurrentDirectory(512, buffer);
	m_EditHostDir.SetWindowTextW(buffer);

	OnBnClickedButtonEcrRoot();

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CFileSystemDlg::OnEnChangeEditHostDir()
{
	CString cs;

	m_EditHostDir.GetWindowTextW(cs);
	SetCurrentDirectory(cs);
	ListHostFiles();
}


void CFileSystemDlg::OnBnClickedButtonEcrDir()
{
#define MAX_FILES 64

	ST_FILE stFile[MAX_FILES];
	memset(&stFile, 0, sizeof(stFile));
	uint16 numberOfFilesReceived = 0;
	int retcode;
	int i;
	CString csEcrDirectory;

	m_ButtonEcrDir.GetWindowTextW(csEcrDirectory);
	m_ListEcrFiles.DeleteAllItems();

	retcode = FP3_FileSystem_DirListFiles(m_hInt, CT2A((LPCTSTR)csEcrDirectory) , stFile, MAX_FILES, &numberOfFilesReceived);
	if (retcode == TRAN_RESULT_OK)
	{
		for (i = 0; i < numberOfFilesReceived; i++)
		{
			CString filename;

			int index = m_ListEcrFiles.InsertItem(LVIF_TEXT | LVIF_STATE, m_ListEcrFiles.GetItemCount(), NULL, 0, LVIS_SELECTED, 0, 0);

			m_ListEcrFiles.SetItemText(index, 0, CString(stFile[i].fileName));

			CString csSize;
			csSize.Format(L"%d", stFile[i].fileSize);
			m_ListEcrFiles.SetItemText(index, 1, csSize);
		}
	}

	if (retcode)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox((CString) ErrorString, L"Return Code", MB_OK);
	}
}


void CFileSystemDlg::OnNMDblclkListEcrFiles(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;

	POSITION pos = m_ListEcrFiles.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;

	row = m_ListEcrFiles.GetNextSelectedItem(pos);

	// ilk Column'da id'si olmalý
	CString cs = m_ListEcrFiles.GetItemText(row, 0);

	if (cs.GetAt(0) == '/')
	{
		m_ButtonEcrDir.SetWindowTextW(cs);
		OnBnClickedButtonEcrDir();
	}
}


void CFileSystemDlg::OnBnClickedButtonEcrRoot()
{
	m_ButtonEcrDir.SetWindowTextW(L"");
	OnBnClickedButtonEcrDir();
}

CString CFileSystemDlg::GetFileName(CListCtrl* plistCtrl)
{
	POSITION pos = plistCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
		return L"";

	int row = plistCtrl->GetNextSelectedItem(pos);

	// ilk Column'da id'si olmalý
	return plistCtrl->GetItemText(row, 0);

}

int CFileSystemDlg::GetFileSize(CListCtrl* plistCtrl)
{
	POSITION pos = plistCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
		return 0;

	int row = plistCtrl->GetNextSelectedItem(pos);

	// ilk Column'da id'si olmalý
	return atoi(CT2A((LPCTSTR)plistCtrl->GetItemText(row, 1)));

}

void CFileSystemDlg::OnBnClickedButtonCopyToEcr()
{
	uint32 retcode = TRAN_RESULT_OK;

	CString csFileNamePlu;
	FILE* pFileHost = NULL;
	char hostPathName[512];
	char ecrPathName[512];
	CString csHostFileDir;
	CString csEcrFileDir;
	CString csHostFileName;

	// HOST FILE NAME
	m_EditHostDir.GetWindowTextW(csHostFileDir);
	if (csHostFileDir.GetLength() == 0)
		return;
	csHostFileName = GetFileName(&m_ListHostFiles);
	if (csHostFileName.GetLength() == 0)
		return;
	strcpy(hostPathName, CT2A((LPCTSTR)(csHostFileDir + "/" + csHostFileName)));

	m_ButtonEcrDir.GetWindowTextW(csEcrFileDir);
	if (csEcrFileDir.GetLength() == 0)
		return;


	pFileHost = fopen(hostPathName, "rb");
	if (pFileHost == NULL)
	{
		MessageBox(L"File can not opened in Host Computer", L"fopen", MB_OK);
		goto Exit;
	}

	fseek(pFileHost , 0 , SEEK_END);
	unsigned long long HostFileSize = ftell(pFileHost);
	fseek(pFileHost , 0 , SEEK_SET);

	strcpy(ecrPathName, CT2A((LPCTSTR)(csEcrFileDir + "/" + csHostFileName)));
	retcode = FP3_FileSystem_FileRemove(m_hInt, ecrPathName);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	uint64 time1 = GetTickCount64();

	int ReadLen = 0;
	uint32 offset = 0;

	while (offset < HostFileSize)
	{
		byte buffer[1024*1];
		int errorCounter = 0;

		ReadLen = (int)fread(buffer, 1, sizeof(buffer), pFileHost);
		if (ReadLen == 0)
			goto Exit;

Label_Retry:
		do
		{
			retcode = FP3_FileSystem_FileWrite(m_hInt, ecrPathName, offset, FS_SEEKSET, buffer, ReadLen);
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

			if (MessageBox((CString)ErrorString, L"RETRY ?", MB_RETRYCANCEL) != IDRETRY)
				goto Exit;
			goto Label_Retry;
		}

		offset += ReadLen;

		if (HostFileSize)
		{
			uint64 time2 = GetTickCount64();

			unsigned long long perc = (offset * 10000) / HostFileSize;
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

Exit:
	SetWindowTextW(L"File System");

	if (pFileHost)
		fclose(pFileHost);
	pFileHost = NULL;

	if (retcode)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox((CString) ErrorString, L"Return Code", MB_OK);
	}

	OnBnClickedButtonEcrDir();
}


void CFileSystemDlg::OnBnClickedButtonCopyToHost()
{
	int retcode = TRAN_RESULT_OK;

	CString csFileNamePlu;
	FILE* pFileHost = NULL;
	char hostPathName[512];
	char ecrPathName[512];
	CString csHostFileDir;
	CString csEcrFileDir;
	CString csEcrFileName;

	// HOST FILE NAME
	m_EditHostDir.GetWindowTextW(csHostFileDir);
	if (csHostFileDir.GetLength() == 0)
		return;
	unsigned long long EcrFileSize = GetFileSize(&m_ListEcrFiles);
	if (EcrFileSize == 0)
		return;
	csEcrFileName = GetFileName(&m_ListEcrFiles);
	if (csEcrFileName.GetLength() == 0)
		return;

	m_ButtonEcrDir.GetWindowTextW(csEcrFileDir);
	if (csEcrFileDir.GetLength() == 0)
		return;

	strcpy(hostPathName, CT2A((LPCTSTR)(csHostFileDir + "/" + csEcrFileName)));
	strcpy(ecrPathName, CT2A((LPCTSTR)(csEcrFileDir + "/" + csEcrFileName)));

	remove(hostPathName);

	pFileHost = fopen(hostPathName, "ab");
	if (pFileHost == NULL)
	{
		MessageBox(L"File can not opened in Host Computer", L"fopen", MB_OK);
		goto Exit;
	}

	uint64 time1 = GetTickCount64();
	uint16 ReadLen = 0;
	byte buffer[1024];
	uint32 offset = 0;
	while (1)
	{

Label_Retry:
		do
		{
			retcode = FP3_FileSystem_FileRead(m_hInt, ecrPathName, offset, FS_SEEKSET, buffer, sizeof(buffer), &ReadLen);
			if (retcode == DLL_RETCODE_RECV_BUSY)
				Sleep(1000);
		}
		while (retcode == DLL_RETCODE_RECV_BUSY);

		if (retcode == APP_ERR_FILE_EOF)
			goto Exit;

		if (retcode != TRAN_RESULT_OK)
		{
			char ErrorString[128];
			GetErrorMessage(retcode, ErrorString);

			if (MessageBox((CString)ErrorString, L"RETRY ?", MB_RETRYCANCEL) != IDRETRY)
				goto Exit;
			goto Label_Retry;
		}

		fwrite(buffer, 1, ReadLen, pFileHost);

		offset += ReadLen;

		if (EcrFileSize)
		{
			uint64 time2 = GetTickCount64();

			unsigned long long perc = (offset * 10000) / EcrFileSize;
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

Exit:
	SetWindowTextW(L"File System");

	if (pFileHost)
		fclose(pFileHost);
	pFileHost = NULL;

	if (retcode && (retcode != APP_ERR_FILE_EOF))
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox((CString) ErrorString, L"Return Code", MB_OK);
	}

	ListHostFiles();
}


void CFileSystemDlg::OnBnClickedButtonEcrRemove()
{
	int retcode = TRAN_RESULT_OK;
	CString csFileNamePlu;
	FILE* pFileHost = NULL;
	char ecrPathName[512];
	CString csEcrFileDir;
	CString csEcrFileName;

	// ECR FILE NAME
	m_ButtonEcrDir.GetWindowTextW(csEcrFileDir);
	if (csEcrFileDir.GetLength() == 0)
		return;
	csEcrFileName = GetFileName(&m_ListEcrFiles);
	if (csEcrFileName.GetLength() == 0)
		return;

	strcpy(ecrPathName, CT2A((LPCTSTR)(csEcrFileDir + "/" + csEcrFileName)));
	retcode = FP3_FileSystem_FileRemove(m_hInt, ecrPathName);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;


Exit:
	if (retcode)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox((CString) ErrorString, L"Return Code", MB_OK);
	}

	OnBnClickedButtonEcrDir();
}


void CFileSystemDlg::OnNMDblclkListHostFiles(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	int row = pNMItemActivate->iItem;
	int column = pNMItemActivate->iSubItem;

	POSITION pos = m_ListHostFiles.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;

	row = m_ListHostFiles.GetNextSelectedItem(pos);

	// ilk Column'da id'si olmalý
	CString cs = m_ListHostFiles.GetItemText(row, 0);

	if (cs.GetAt(0) == '/')
	{
		CString currentDir;
		TCHAR buffer[1024];

		m_EditHostDir.GetWindowTextW(currentDir);
		currentDir += cs;

		SetCurrentDirectory(currentDir);
		GetCurrentDirectory(1024, buffer);

		m_EditHostDir.SetWindowTextW(buffer);

//		ListHostFiles();
	}
}


void CFileSystemDlg::OnBnClickedButtonEcrRename()
{
	int retcode = TRAN_RESULT_OK;
	CString csFileNamePlu;
	FILE* pFileHost = NULL;
	char ecrPathNameOld[512];
	char ecrPathNameNew[512];
	CString csEcrFileDir;
	CString csEcrFileName;
	CString csNewFileName;
	CGetInputDlg GetInputDlg;

	// ECR FILE NAME
	m_ButtonEcrDir.GetWindowTextW(csEcrFileDir);
	if (csEcrFileDir.GetLength() == 0)
		return;
	csEcrFileName = GetFileName(&m_ListEcrFiles);
	if (csEcrFileName.GetLength() == 0)
		return;

	if (GetInputDlg.DoModal(L"Type NEW file name", csEcrFileName, 1) != IDOK)
		return;
	csNewFileName = GetInputDlg.m_input;

	strcpy(ecrPathNameOld, CT2A((LPCTSTR)(csEcrFileDir + "/" + csEcrFileName)));
	strcpy(ecrPathNameNew, CT2A((LPCTSTR)(csEcrFileDir + "/" + csNewFileName)));

	retcode = FP3_FileSystem_FileRename(m_hInt, ecrPathNameOld, ecrPathNameNew);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

Exit:
	if (retcode)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox((CString) ErrorString, L"Return Code", MB_OK);
	}

	OnBnClickedButtonEcrDir();
}
