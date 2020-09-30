// SelectUniqueId.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "SelectUniqueId.h"
#include "afxdialogex.h"
#include "ePosDlg.h"


// CSelectUniqueId dialog

IMPLEMENT_DYNAMIC(CSelectUniqueId, CDialogEx)

CSelectUniqueId::CSelectUniqueId(CWnd* pParent /*=NULL*/)
		: CDialogEx(CSelectUniqueId::IDD, pParent)
{

}

CSelectUniqueId::~CSelectUniqueId()
{
}

void CSelectUniqueId::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UNIQUE_ID, m_listUniqueId);
}


BEGIN_MESSAGE_MAP(CSelectUniqueId, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_UNIQUE_ID, &CSelectUniqueId::OnLbnSelchangeListUniqueId)
	ON_LBN_DBLCLK(IDC_LIST_UNIQUE_ID, &CSelectUniqueId::OnDblclkListUniqueId)
END_MESSAGE_MAP()


// CSelectUniqueId message handlers


BOOL CSelectUniqueId::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int retcode;
	uint16 totalNumberOfItems = 0;
	uint16 numberOfItemsInThis = 0;

	memset(&stUniqueIdSelected, 0x00, sizeof(ST_UNIQUE_ID));
	memset(stUniqueIdList, 0x00, 256 * sizeof(ST_UNIQUE_ID));

	numberOfItems = 0;
	do
	{
		retcode = FP3_FunctionGetUniqueIdList(m_hInt, &stUniqueIdList[numberOfItems], MAX_UNIQUE_ID - numberOfItems, numberOfItems, &totalNumberOfItems, &numberOfItemsInThis, 50000);
		if (retcode != TRAN_RESULT_OK)
			break;

		numberOfItems += numberOfItemsInThis;

	}
	while (numberOfItems < totalNumberOfItems);

	if (retcode != TRAN_RESULT_OK)
	{
		((CePosDlg*)GetParent())->HandleErrorCode(retcode);
		OnCancel();
	}
	else
	{
		for (int i = 0; i < numberOfItems; i++)
		{
			CString cs;
			cs.Empty();
			for (int t = 0; t < 24; t++)
			{
				CString cs1;
				cs1.Format(L"%02X", stUniqueIdList[i].uniqueId[t]);
				cs += cs1;
			}

			m_listUniqueId.AddString(cs);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CSelectUniqueId::OnLbnSelchangeListUniqueId()
{
	// TODO: Add your control notification handler code here
}


void CSelectUniqueId::OnDblclkListUniqueId()
{
	int index = m_listUniqueId.GetCurSel();

	memcpy(&stUniqueIdSelected, &stUniqueIdList[index], sizeof(ST_UNIQUE_ID));

	OnOK();
}
