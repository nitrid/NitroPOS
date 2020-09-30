// MatrahsizDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "MatrahsizDlg.h"
#include "afxdialogex.h"


// CMatrahsizDlg dialog

IMPLEMENT_DYNAMIC(CMatrahsizDlg, CDialogEx)

CMatrahsizDlg::CMatrahsizDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CMatrahsizDlg::IDD, pParent)
		, m_csTckNo(_T(""))
{

}

CMatrahsizDlg::~CMatrahsizDlg()
{
}

void CMatrahsizDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TCKNO, m_csTckNo);
}


BEGIN_MESSAGE_MAP(CMatrahsizDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMatrahsizDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMatrahsizDlg message handlers


void CMatrahsizDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CDialogEx::OnOK();
}
