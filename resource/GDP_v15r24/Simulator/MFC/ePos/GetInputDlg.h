#pragma once
#include "afxwin.h"


// CGetInputDlg dialog
typedef struct
{
	unsigned long long flagValue;
	CString caption;
	bool	defaultValue;
} ST_FLAG;

#define MAX_NUMBER_OF_FLAG 32

class CGetInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGetInputDlg)

public:
	CGetInputDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGetInputDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_GETINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	ST_FLAG m_multipleFlags[MAX_NUMBER_OF_FLAG];
	CButton m_checkBox[MAX_NUMBER_OF_FLAG];
	int m_numberOfmultipleFlags;
	CString m_caption;
	CString m_input;
	int m_type;
	unsigned long long m_flagValue;
	CEdit m_EditInput;
	CEdit m_EditLabel;

	void CheckBox(int item);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckBox1();
	afx_msg void OnBnClickedCheckBox2();
	afx_msg void OnBnClickedCheckBox3();
	afx_msg void OnBnClickedCheckBox4();
	afx_msg void OnBnClickedCheckBox5();
	afx_msg void OnBnClickedCheckBox6();
	afx_msg void OnBnClickedCheckBox7();
	afx_msg void OnBnClickedCheckBox8();
	afx_msg void OnBnClickedCheckBox9();
	afx_msg void OnBnClickedCheckBox10();
	afx_msg void OnBnClickedCheckBox11();
	afx_msg void OnBnClickedCheckBox12();
	afx_msg void OnBnClickedCheckBox13();
	afx_msg void OnBnClickedCheckBox14();
	afx_msg void OnBnClickedCheckBox15();
	afx_msg void OnBnClickedCheckBox16();
	afx_msg void OnBnClickedCheckBox17();
	afx_msg void OnBnClickedCheckBox18();
	afx_msg void OnBnClickedCheckBox19();
	afx_msg void OnBnClickedCheckBox20();
	afx_msg void OnBnClickedCheckBox21();
	afx_msg void OnBnClickedCheckBox22();
	afx_msg void OnBnClickedCheckBox23();
	afx_msg void OnBnClickedCheckBox24();
	afx_msg void OnBnClickedCheckBox25();
	afx_msg void OnBnClickedCheckBox26();
	afx_msg void OnBnClickedCheckBox27();
	afx_msg void OnBnClickedCheckBox28();
	afx_msg void OnBnClickedCheckBox29();
	afx_msg void OnBnClickedCheckBox30();
	afx_msg void OnBnClickedCheckBox31();
	afx_msg void OnBnClickedCheckBox32();
	virtual INT_PTR DoModal(CString caption, CString Input, int type);
	void InsertFlag(CString caption, unsigned long long flagValue, bool defaultValue);
	virtual BOOL OnInitDialog();
	CFont* myFont;
	virtual BOOL DestroyWindow();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
