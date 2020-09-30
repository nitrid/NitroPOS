#pragma once


// CItemNo dialog

class CItemNo : public CDialogEx
{
	DECLARE_DYNAMIC(CItemNo)

public:
	CItemNo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CItemNo();

// Dialog Data
	enum { IDD = IDD_ITEM_NO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_csItemNo;
	int m_iItemNo;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAll();
};
