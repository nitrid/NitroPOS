#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "GmpSmartDll.h"


// CCashierDlg dialog

class CCashierDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCashierDlg)

public:
	CCashierDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCashierDlg();

// Dialog Data
	enum { IDD = IDD_CASHIER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HINT m_hInt;
	int retcode;
	uint16 activeCashier;
	byte numberOfTotalCashiers;
	ST_CASHIER		stCashierTable[10];
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CListCtrl m_ListCashiers;
	short m_cashierIndex;
	afx_msg void OnNMDblclkListCashiers(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_activeCashierIndex;
	CString m_activeCashierName;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedListCashiers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEditActiveCashierIndex();
};
