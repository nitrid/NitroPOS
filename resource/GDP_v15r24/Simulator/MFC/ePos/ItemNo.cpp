// ItemNo.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "ItemNo.h"
#include "afxdialogex.h"


// ItemNo dialog

IMPLEMENT_DYNAMIC(CItemNo, CDialogEx)

CItemNo::CItemNo(CWnd* pParent /*=NULL*/)
		: CDialogEx(CItemNo::IDD, pParent)
		, m_csItemNo(_T(""))
{

}

CItemNo::~CItemNo()
{
}

void CItemNo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ITEM_NO, m_csItemNo);
}


BEGIN_MESSAGE_MAP(CItemNo, CDialogEx)
	ON_BN_CLICKED(IDOK, &CItemNo::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ALL, &CItemNo::OnBnClickedButtonAll)
END_MESSAGE_MAP()


// ItemNo message handlers


void CItemNo::OnBnClickedOk()
{
	UpdateData(true);

	m_iItemNo = atol(CT2A((LPCTSTR)m_csItemNo));
	if (m_iItemNo == 0)
		return;

	CDialogEx::OnOK();
}


void CItemNo::OnBnClickedButtonAll()
{
	m_iItemNo = 0xFFFF;
	if (m_iItemNo == 0)
		return;
	CDialogEx::OnOK();
}
