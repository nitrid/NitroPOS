#pragma once
#include "atlcomtime.h"
#include "afxwin.h"


// CInvoiceDlg dialog

class CInvoiceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInvoiceDlg)

public:
	CInvoiceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInvoiceDlg();

// Dialog Data
	enum { IDD = IDD_INVOICE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CFont* myFont;
	byte	m_byteFaturaTipi;
	CString m_csInvoiceNo;
	COleDateTime m_dateInvoiceDate;
	CString m_csInvoiceAmount;
	afx_msg void OnBnClickedOk();
	CComboBox m_comboFaturaTipi;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL DestroyWindow();
	CString m_TCK_NO;
	CString m_VK_NO;
	afx_msg void OnEnChangeEditTckNo();
	afx_msg void OnEnChangeEditVkNo();
	BOOL m_Irsaliye;
};
