#pragma once
#include "atlcomtime.h"
#include "afxwin.h"


// CCariHesapDlg dialog
//typedef struct
//{
//	unsigned long long flagValue;
//	CString caption;
//	bool	defaultValue;
//}CHECK_FLAG;

#define MAX_NUMBER_OF_CB 2

class CCariHesapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCariHesapDlg)

public:
	CCariHesapDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCariHesapDlg();

// Dialog Data
	enum { IDD = IDD_SET_CARI_HESAP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CFont* myFont;
	//CHECK_FLAG m_multipleDateFlags[MAX_NUMBER_OF_CB];
	CButton m_checkBoxDate[MAX_NUMBER_OF_CB];

	int m_numberOfmultipleFlags;
	CString m_caption;
	CString m_input;
	int m_type;
	unsigned long long m_flagValue;
	byte	m_byteCariHesapType;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCheckOrderDate();
	afx_msg void OnBnClickedCheckDespatchDate();
	virtual BOOL DestroyWindow();
	void CheckBox(int item);

	CString m_csCariHesapCustomerName;
	CString m_csCariHesapVKN;
	CString m_csCariHesapTCKN;
	CString m_csCariHesapDokumanNo;
	COleDateTime m_dateCariHesapDate;

	void InsertFlag(CString caption, unsigned long long flagValue, bool defaultValue);

};
