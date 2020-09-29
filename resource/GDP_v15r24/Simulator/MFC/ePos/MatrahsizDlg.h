#pragma once


// CMatrahsizDlg dialog

class CMatrahsizDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMatrahsizDlg)

public:
	CMatrahsizDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMatrahsizDlg();

// Dialog Data
	enum { IDD = IDD_MATRAHSIZ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_csTckNo;
};
