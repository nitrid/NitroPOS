#pragma once
#include "afxwin.h"


// CDoPayment dialog

class CDoPayment : public CDialogEx
{
	DECLARE_DYNAMIC(CDoPayment)

public:
	CDoPayment(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDoPayment();

// Dialog Data
	enum { IDD = IDD_DIALOG_DO_PAYMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_typeOfPayments; // 0:PAYMENT_		1:REVERSE_PAYMENT_
	CFont* myFont;
	unsigned long m_PaymentType;
	CListBox m_ListPaymentTypes;
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeListPaymentTypes();
	afx_msg void OnDblclkListPaymentTypes();
	afx_msg void OnBnClickedOk();
	virtual INT_PTR DoModal(BYTE typeOfPayment = 0);
};
