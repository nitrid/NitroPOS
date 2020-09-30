#pragma once
#include "afxwin.h"


// CPasswordDlg dialog

class CPasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPasswordDlg)

public:
	CPasswordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPasswordDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_caption;
	CFont* myFont;
	CString m_Password;
	CEdit m_CtrlPassword;
	virtual INT_PTR DoModal(CString caption);
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	CEdit m_CtrlCaption;
};
