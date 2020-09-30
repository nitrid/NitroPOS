#pragma once
#include "atlcomtime.h"
#include "afxwin.h"


// COnlineInvoiceDlg dialog
typedef struct
{
	unsigned long long flagValue;
	CString caption;
	bool	defaultValue;
} CHECK_FLAG;

#define MAX_NUMBER_OF_CB 2

class COnlineInvoiceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COnlineInvoiceDlg)

public:
	COnlineInvoiceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COnlineInvoiceDlg();

// Dialog Data
	enum { IDD = IDD_SET_ONLINE_INVOICE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CFont* myFont;
	CHECK_FLAG m_multipleDateFlags[MAX_NUMBER_OF_CB];
	CButton m_checkBoxDate[MAX_NUMBER_OF_CB];

	int m_numberOfmultipleFlags;
	CString m_caption;
	CString m_input;
	int m_type;
	unsigned long long m_flagValue;
	byte	m_byteOnlineInvoiceType;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCheckOrderDate();
	afx_msg void OnBnClickedCheckDespatchDate();
	virtual BOOL DestroyWindow();
	void CheckBox(int item);

	CString m_csOnlineInvoiceCustomerInfo;
	CString m_csOnlineInvoiceVKN;
	CString m_csOnlineInvoiceHomeAddress;
	CString m_csOnlineInvoiceDistrict;
	CString m_csOnlineInvoiceCity;
	CString m_csOnlineInvoiceCountry;
	CString m_csOnlineInvoiceEmail;
	CString m_csOnlineInvoiceWeb;
	CString m_csOnlineInvoicePhone;
	CString m_csOnlineInvoiceTaxOffice;
	CComboBox m_comboInvoiceType;
	CString m_csOnlineInvoiceEttn;
	COleDateTime m_dateOnlineInvoiceOrderDate;
	CString m_csOnlineInvoiceOrderNo;
	COleDateTime m_dateOnlineInvoiceDespatchDate;
	CString m_csOnlineInvoiceDespatchNo;
	CString m_csOnlineInvoiceLabel;

	void InsertFlag(CString caption, unsigned long long flagValue, bool defaultValue);

};
