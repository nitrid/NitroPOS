#pragma once
#include "afxwin.h"

#include "GmpSmartDll.h"

#define MAX_UNIQUE_ID 256

// CSelectUniqueId dialog

class CSelectUniqueId : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectUniqueId)

public:
	CSelectUniqueId(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectUniqueId();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECT_UNIQUE_ID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HINT m_hInt;
	CListBox m_listUniqueId;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeListUniqueId();
	afx_msg void OnDblclkListUniqueId();
	ST_UNIQUE_ID stUniqueIdList[MAX_UNIQUE_ID];
	uint16 numberOfItems;
	ST_UNIQUE_ID stUniqueIdSelected;
};
