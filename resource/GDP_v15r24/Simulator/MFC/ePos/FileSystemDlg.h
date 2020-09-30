#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CFileSystemDlg dialog

class CFileSystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileSystemDlg)

public:
	CFileSystemDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileSystemDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_FILESYSTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HINT m_hInt;
	CListCtrl m_ListHostFiles;
	CEdit m_EditHostDir;
	afx_msg void OnBnClickedButtonHostDir();
	virtual BOOL OnInitDialog();
	void ListHostFiles();
	afx_msg void OnEnChangeEditHostDir();
	CListCtrl m_ListEcrFiles;
	afx_msg void OnBnClickedButtonEcrDir();
	CButton m_ButtonEcrDir;
	afx_msg void OnNMDblclkListEcrFiles(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonEcrRoot();
	afx_msg void OnBnClickedButtonCopyToEcr();
	afx_msg void OnBnClickedButtonCopyToHost();
	CString GetFileName(CListCtrl* plistCtrl);
	int GetFileSize(CListCtrl* plistCtrl);
	afx_msg void OnBnClickedButtonEcrRemove();
	afx_msg void OnNMDblclkListHostFiles(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonEcrRename();
};
