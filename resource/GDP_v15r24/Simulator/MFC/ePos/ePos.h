
// ePos.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// CePosApp:
// See ePos.cpp for the implementation of this class
//

class CePosApp : public CWinApp
{
public:
	CePosApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CePosApp theApp;

void DoEvents(void);
int  FillListControlFromDBExt(HINT hInt, char* dbName, CListCtrl* plistCtrl, char* swlWord);
void InsertItemText(CListCtrl* plist, int nItem, int colomn, char * buffer, ...);
int DBExecute(HINT hInt, char* dbName, CListCtrl* plistCtrl, char* swlWord);