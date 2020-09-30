#pragma once
#include "afxcmn.h"


// CDBTranDlg dialog

class CDBTranDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDBTranDlg)

public:
	CDBTranDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDBTranDlg();

// Dialog Data
	enum { IDD = IDD_DB_TRAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HINT m_hInt;
	bool initDone;
	CListCtrl m_list_Z;
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMDblclkListZ(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listTransaction;
	CListCtrl m_listItems;
	afx_msg void OnDblclkListTransaction(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListZ(NMHDR *pNMHDR, LRESULT *pResult);
	void ResizeControls(void);
	char TranDbName[64];

};
