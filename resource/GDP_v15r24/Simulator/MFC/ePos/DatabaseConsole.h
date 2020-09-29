#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDatabaseConsole dialog

class CDatabaseConsole : public CDialogEx
{
	DECLARE_DYNAMIC(CDatabaseConsole)

public:
	CDatabaseConsole(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDatabaseConsole();

// Dialog Data
	enum { IDD = IDD_DIALOG_DATABASE_CONSOLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HINT m_hInt;
	void ResizeControls(void);
	CListBox m_ListDatabaseName;
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListDatabaseName();
	CListCtrl m_ListTables;
	CListCtrl m_ListRows;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnDblclkListTables(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMenuDropTable();
	CEdit m_EditBoxSqlword;
	CButton m_ButtonExecute;
	afx_msg void OnBnClickedButton1();
	virtual void OnOK();
	afx_msg void OnLbnSelchangeListDatabaseName();
};
