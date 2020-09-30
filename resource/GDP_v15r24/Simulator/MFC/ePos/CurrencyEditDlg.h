#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "GmpSmartDll.h"

// CCurrencyEditDlg dialog

class CCurrencyEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCurrencyEditDlg)

public:
	CCurrencyEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCurrencyEditDlg();

// Dialog Data
	enum { IDD = IDD_CURRENCYEDITDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_profileName;
	CString m_CurrencyCode;
	CString m_CurrencySymbol;
	CString m_CurrencyShortName;
	CString m_CurrencyDigitGroupSymbol;
	CString m_CurrencyDecimalSymbol;
	CString m_CurrencyExponent;
	CString m_CurrencySymbolPosition;
	CString m_CurrencyTLRate;
	afx_msg void OnCbnSelchangeCurrencySymbolPosition();
	CComboBox m_CurrencySymbolPosCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CString m_CurrencyCode2;
	CString m_CurrencySymbol2;
	CString m_CurrencyShortName2;
	CString m_CurrencyDigitGroupSymbol2;
	CString m_CurrencyDecimalSymbol2;
	CString m_CurrencyExponent2;
	CString m_CurrencySymbolPosition2;
	CString m_CurrencyTLRate2;
	CComboBox m_CurrencySymbolPositionCtrl2;
	CString m_CurrencyCode3;
	CString m_CurrencySymbol3;
	CString m_CurrencyShortName3;
	CString m_CurrencyDigitGroupSymbol3;
	CString m_CurrencyDecimalSymbol3;
	CString m_CurrencyExponent3;
	CString m_CurrencySymbolPosition3;
	CComboBox m_CurrencySymbolPositionCtrl3;
	CString m_CurrencyTLRate3;
	CString m_CurrencyCode4;
	CString m_CurrencySymbol4;
	CString m_CurrencyShortName4;
	CString m_CurrencyDigitGroupSymbol4;
	CString m_CurrencyDecimalSymbol4;
	CString m_CurrencyExponent4;
	CString m_CurrencySymbolPosition4;
	CComboBox m_CurrencySymbolPositionCtrl4;
	CString m_CurrencyTLRate4;
	CString m_CurrencyCode5;
	CString m_CurrencyCode6;
	CString m_CurrencySymbol5;
	CString m_CurrencySymbol6;
	CString m_CurrencyShortName5;
	CString m_CurrencyShortName6;
	CString m_CurrencyDigitGroupSymbol5;
	CString m_CurrencyDigitGroupSymbol6;
	CString m_CurrencyDecimalSymbol5;
	CString m_CurrencyDecimalSymbol6;
	CString m_CurrencyExponent5;
	CString m_CurrencyExponent6;
	CString m_CurrencySymbolPosition5;
	CString m_CurrencySymbolPosition6;
	CComboBox m_CurrencySymbolPositionCtrl5;
	CComboBox m_CurrencySymbolPositionCtrl6;
	CString m_CurrencyTLRate5;
	CString m_CurrencyTLRate6;
	BOOL m_DeleteProfile;
	CButton m_DeleteProfileCtrl;
};
