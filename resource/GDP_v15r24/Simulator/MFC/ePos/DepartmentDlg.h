#pragma once
#include "afxcmn.h"
#include "GmpSmartDll.h"


// CDepartmentDlg dialog

class CDepartmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDepartmentDlg)

public:
	CDepartmentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDepartmentDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DEPARTMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	uint8 numberOfTotalDepartmentsReceived;
	uint8 numberOfTotalTaxratesReceived;
	ST_DEPARTMENT	stDepartments[12];
	ST_TAX_RATE		stTaxRates[8];
	CListCtrl m_listTaxRates;
	CListCtrl m_listDepartments;
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListDepartments(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedListDepartments(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListTaxrates(NMHDR *pNMHDR, LRESULT *pResult);
};
