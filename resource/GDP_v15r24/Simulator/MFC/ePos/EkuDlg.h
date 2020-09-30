#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "GmpSmartDll.h"


// CEkuDlg dialog

class CEkuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEkuDlg)

public:
	CEkuDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEkuDlg();
	int m_subCommand;

// Dialog Data
	enum { IDD = IDD_DIALOG_EKU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	HINT m_hInt;
	int LoadEkuHeader(void);
	int LoadEkuModuleInfo(void);
	void DisplayError(int retcode);
	int ReadData(void);
	CListBox m_listPrinter;
	CFont* myFont;
	int m_ZNoStart;
	int m_FNoStart;
	int PrintHeader(ST_EKU_APPINF *pstEKUAppInfo);
	ST_EKU_MODULE_INFO *pstEkuModuleInfo;
	ST_EKU_HEADER *pstEkuHeader;
	ST_EKU_APPINF stEKUAppInfo;

	void Print(CListBox* plist, char * buffer, ...);
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSearchByZnoFno();
	afx_msg void OnBnClickedButtonSearchByDateTime();
	COleDateTime m_DateStart;
	COleDateTime m_DateEnd;
	COleDateTime m_TimeStart;
	COleDateTime m_TimeEnd;
	CListBox m_listEkuHeader;
	CListBox m_listEkuModuleInfo;
	afx_msg void OnBnClickedButtonReadModuleInfo();
	afx_msg void OnBnClickedButtonReadHeader();
	afx_msg void OnBnClickedButtonEkuPing();
	afx_msg void OnBnClickedButtonEkuPresent();
	afx_msg void OnBnClickedButtonEkuReset();
	afx_msg void OnBnClickedButtonReadDataNext();
};
