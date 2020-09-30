#pragma once
#include "afxcmn.h"
#include "GmpSmartDll.h"

// CPaymentDlg dialog

class CPaymentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPaymentDlg)

public:
	CPaymentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPaymentDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PAYMENTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_selectedPayment;
	ST_PAYMENT	m_stPayment[24];
	int m_numberOfPayments;
	CListCtrl m_listPayment;
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	virtual INT_PTR DoModal(ST_PAYMENT* pstPayment, int numberOfPayments);
	CListCtrl m_listBankPayment;
	afx_msg void OnItemchangedListPayment(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
