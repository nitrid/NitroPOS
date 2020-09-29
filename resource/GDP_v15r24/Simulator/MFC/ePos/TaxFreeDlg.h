#pragma once
#include "atlcomtime.h"
#include "afxwin.h"


// COnlineInvoiceDlg dialog

class CTaxFreeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaxFreeDlg)

public:
	CTaxFreeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTaxFreeDlg();

// Dialog Data
	enum { IDD = IDD_TAXFREE_INFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CFont* myFont;
	byte m_byteCountryCode;
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();

	CString m_csTaxFreeBuyerName;
	CString m_csTaxFreeBuyerSurname;
	CString m_csTaxFreeVKN;
	CString m_csTaxFreeCity;
	CString m_csTaxFreeCountry;
	CComboBox m_comboCountryCode;
	COleDateTime m_dateTaxFreeOrderDate;
	CString m_csTaxFreeEttn;
	CString m_csTaxFreeLabel;
	CString m_CountryCode;
};
