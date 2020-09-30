
// ePos.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ePos.h"
#include "ePosDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MSG msg;
void DoEvents(void)
{
	for (int i = 0; i < 8; i++)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}

// CePosApp

BEGIN_MESSAGE_MAP(CePosApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CePosApp construction

CePosApp::CePosApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CePosApp object

CePosApp theApp;


// CePosApp initialization

CePosDlg* m_dlg;
BOOL CePosApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CePosDlg dlg;
	m_pMainWnd = &dlg;
	m_dlg = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void InsertItemText(CListCtrl* plist, int nItem, int colomn, char * buffer, ...)
{
	va_list 		args;
	char tmp[512];
	CString cs;

	va_start(args, buffer);
	vsprintf(tmp, buffer, args);
	va_end(args);
	cs = tmp;

	plist->SetItemText(nItem, colomn, cs);
}

int FillListControlFromDBExt(HINT hInt, char* dbName, CListCtrl* plistCtrl, char* swlWord)
{
	int retcode;
	uint16 numberOfColumns = 24;
	ST_DATABASE_RESULT stDatabaseResult;

	retcode = FP3_Database_Open(hInt, dbName);
	if ((retcode != TRAN_RESULT_OK))
		goto Exit;

	retcode = FP3_Database_Query(hInt, swlWord, &numberOfColumns);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	memset(&stDatabaseResult, 0x00, sizeof(stDatabaseResult));
	stDatabaseResult.StructSize = sizeof(stDatabaseResult);

	if ((retcode = FP3_Database_QueryColomnCaptions(hInt, &stDatabaseResult)) == TRAN_RESULT_OK)
	{
		if (stDatabaseResult.pstCaptionArray)
		{
			CRect rect;
			plistCtrl->GetWindowRect(&rect);
			plistCtrl->DeleteAllItems();

			int nColumnCount = plistCtrl->GetHeaderCtrl()->GetItemCount();
			// Delete all of the columns.
			for (int i = 0; i < nColumnCount; i++)
				plistCtrl->DeleteColumn(0);

			numberOfColumns = stDatabaseResult.pstCaptionArray[0].numberOfColomns;
			for (int i = 0; i < numberOfColumns; i++)
			{
				CString cs;
				cs = CString(stDatabaseResult.pstCaptionArray[0].pstColomnArray[i].data);
				plistCtrl->InsertColumn(i, cs);
				plistCtrl->SetColumnWidth(i, cs.GetLength() * 8);
			}
			FP3_Database_FreeStructure(hInt, &stDatabaseResult);

			if (numberOfColumns == 0)
			{
				retcode = FP3_Database_QueryFinish(hInt);
				goto Exit;
			}

			do
			{
				retcode = FP3_Database_QueryReadLine(hInt, 50, numberOfColumns, &stDatabaseResult);
				if ((retcode != SQLITE_ROW) && (retcode != SQLITE_DONE))
					break;

				for (int line = 0; line < stDatabaseResult.numberOfLines; line++)
				{
					int nItem = plistCtrl->InsertItem(LVIF_TEXT | LVIF_STATE, plistCtrl->GetItemCount(), L"", NULL, NULL, 0, 0);
					for (int i = 0; i < stDatabaseResult.pstLineArray[line].numberOfColomns; i++)
					{
						InsertItemText(plistCtrl, nItem, i, "%s", (char*)stDatabaseResult.pstLineArray[line].pstColomnArray[i].data);

						if (plistCtrl->GetColumnWidth(i) < (int)strlen((char*)stDatabaseResult.pstLineArray[line].pstColomnArray[i].data)*8)
							plistCtrl->SetColumnWidth(i, (int)strlen((char*)stDatabaseResult.pstLineArray[line].pstColomnArray[i].data)*8);
					}
				}

			}
			while (retcode == SQLITE_ROW);
		}
	}

	retcode = FP3_Database_FreeStructure(hInt, &stDatabaseResult);
	retcode = FP3_Database_QueryFinish(hInt);

Exit:
	if (FP3_Database_GetHandle(hInt))
		FP3_Database_Close(hInt);

	if (retcode)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		CString cs = CString(ErrorString);
		MessageBox(NULL, cs, L"Return Code", MB_OK);
	}

	return retcode;
}

int DBExecute(HINT hInt, char* dbName, CListCtrl* plistCtrl, char* swlWord)
{
	int retcode;
	uint16 numberOfColumns = 24;
	ST_DATABASE_RESULT stDatabaseResult;

	retcode = FP3_Database_Open(hInt, dbName);
	if ((retcode != TRAN_RESULT_OK))
		goto Exit;

	memset(&stDatabaseResult, 0x00, sizeof(stDatabaseResult));
	stDatabaseResult.StructSize = sizeof(stDatabaseResult);

	retcode = FP3_Database_Execute(hInt, swlWord, &stDatabaseResult);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	if (stDatabaseResult.pstCaptionArray)
	{
		CRect rect;
		plistCtrl->GetWindowRect(&rect);
		plistCtrl->DeleteAllItems();

		int nColumnCount = plistCtrl->GetHeaderCtrl()->GetItemCount();
		// Delete all of the columns.
		for (int i = 0; i < nColumnCount; i++)
			plistCtrl->DeleteColumn(0);

		numberOfColumns = stDatabaseResult.pstCaptionArray[0].numberOfColomns;
		for (int i = 0; i < numberOfColumns; i++)
		{
			CString cs;
			cs = CString(stDatabaseResult.pstCaptionArray[0].pstColomnArray[i].data);
			plistCtrl->InsertColumn(i, cs);
			plistCtrl->SetColumnWidth(i, cs.GetLength() * 8);
		}

		for (int line = 0; line < stDatabaseResult.numberOfLines; line++)
		{
			int nItem = plistCtrl->InsertItem(LVIF_TEXT | LVIF_STATE, plistCtrl->GetItemCount(), L"", NULL, NULL, 0, 0);
			for (int i = 0; i < stDatabaseResult.pstLineArray[line].numberOfColomns; i++)
			{
				InsertItemText(plistCtrl, nItem, i, "%s", (char*)stDatabaseResult.pstLineArray[line].pstColomnArray[i].data);

				if (plistCtrl->GetColumnWidth(i) < (int)strlen((char*)stDatabaseResult.pstLineArray[line].pstColomnArray[i].data)*8)
					plistCtrl->SetColumnWidth(i, (int)strlen((char*)stDatabaseResult.pstLineArray[line].pstColomnArray[i].data)*8);
			}
		}
	}

	FP3_Database_FreeStructure(hInt, &stDatabaseResult);

Exit:
	if (FP3_Database_GetHandle(hInt))
		FP3_Database_Close(hInt);

	if (retcode)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		CString cs = CString(ErrorString);
		MessageBox(NULL, cs, L"Return Code", MB_OK);
	}

	return retcode;
}

int CallbackFunctionSend(BYTE* buffer, int len)
{
	/*	CString cs;
		cs.Format(L"%d", len );

		m_dlg->m_listPrinterOutput.AddString(cs);
	*/
	return 0;
}
