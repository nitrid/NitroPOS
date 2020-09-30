#pragma once
#include "afxwin.h"


// CTicketDlg dialog

class CTicketDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTicketDlg)

public:
	CTicketDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTicketDlg();

// Dialog Data
	enum { IDD = IDD_TICKET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	byte m_TicketType;
	byte m_departmentIndex;
	CFont* myFont;
	CComboBox m_comboFilmType;
	CComboBox m_comboTicketType;
	CComboBox m_comboDepartment;
	afx_msg void OnBnClickedOk();
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboFilmType();
	afx_msg void OnCbnSelchangeComboTicketType();
	afx_msg void OnCbnSelchangeComboDepartment();
};
