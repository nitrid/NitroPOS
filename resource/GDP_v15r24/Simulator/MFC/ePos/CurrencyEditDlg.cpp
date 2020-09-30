// C:\Users\cgunkan\IngeDev7_workspace\emre\GMPSmartDLL_p12\Simulator\MFC\ePos\CurrencyEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "CurrencyEditDlg.h"
#include "afxdialogex.h"


// CCurrencyEditDlg dialog

IMPLEMENT_DYNAMIC(CCurrencyEditDlg, CDialogEx)

CCurrencyEditDlg::CCurrencyEditDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CCurrencyEditDlg::IDD, pParent)
		, m_CurrencyCode(_T(""))
		, m_CurrencySymbol(_T(""))
		, m_CurrencyShortName(_T(""))
		, m_CurrencyDigitGroupSymbol(_T(""))
		, m_CurrencyDecimalSymbol(_T(""))
		, m_CurrencyExponent(_T(""))
		, m_CurrencySymbolPosition(_T(""))
		, m_CurrencyTLRate(_T(""))
		, m_CurrencyCode2(_T(""))
		, m_CurrencySymbol2(_T(""))
		, m_CurrencyShortName2(_T(""))
		, m_CurrencyDigitGroupSymbol2(_T(""))
		, m_CurrencyDecimalSymbol2(_T(""))
		, m_CurrencyExponent2(_T(""))
		, m_CurrencySymbolPosition2(_T(""))
		, m_CurrencyTLRate2(_T(""))
		, m_CurrencyCode3(_T(""))
		, m_CurrencySymbol3(_T(""))
		, m_CurrencyShortName3(_T(""))
		, m_CurrencyDigitGroupSymbol3(_T(""))
		, m_CurrencyDecimalSymbol3(_T(""))
		, m_CurrencyExponent3(_T(""))
		, m_CurrencySymbolPosition3(_T(""))
		, m_CurrencyTLRate3(_T(""))
		, m_CurrencyCode4(_T(""))
		, m_CurrencySymbol4(_T(""))
		, m_CurrencyShortName4(_T(""))
		, m_CurrencyDigitGroupSymbol4(_T(""))
		, m_CurrencyDecimalSymbol4(_T(""))
		, m_CurrencyExponent4(_T(""))
		, m_CurrencySymbolPosition4(_T(""))
		, m_CurrencyTLRate4(_T(""))
		, m_CurrencyCode5(_T(""))
		, m_CurrencyCode6(_T(""))
		, m_CurrencySymbol5(_T(""))
		, m_CurrencySymbol6(_T(""))
		, m_CurrencyShortName5(_T(""))
		, m_CurrencyShortName6(_T(""))
		, m_CurrencyDigitGroupSymbol5(_T(""))
		, m_CurrencyDigitGroupSymbol6(_T(""))
		, m_CurrencyDecimalSymbol5(_T(""))
		, m_CurrencyDecimalSymbol6(_T(""))
		, m_CurrencyExponent5(_T(""))
		, m_CurrencySymbolPosition5(_T(""))
		, m_CurrencySymbolPosition6(_T(""))
		, m_CurrencyTLRate5(_T(""))
		, m_CurrencyTLRate6(_T(""))
		, m_DeleteProfile(FALSE)
{

}

CCurrencyEditDlg::~CCurrencyEditDlg()
{
}

void CCurrencyEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CURRENCY_CODE, m_CurrencyCode);
	DDX_Text(pDX, IDC_CURRENCY_SYMBOL, m_CurrencySymbol);
	DDX_Text(pDX, IDC_CURRENCY_SHORT_NAME, m_CurrencyShortName);
	DDX_Text(pDX, IDC_CURRENCY_DIGIT_GROUP_SYMBO, m_CurrencyDigitGroupSymbol);
	DDX_Text(pDX, IDC_CURRENCY_DECIMAL_SYMBOL, m_CurrencyDecimalSymbol);
	DDX_Text(pDX, IDC_CURRENCY_EXPONENT, m_CurrencyExponent);
	DDX_CBString(pDX, IDC_CURRENCY_SYMBOL_POSITION, m_CurrencySymbolPosition);
	DDX_Text(pDX, IDC_CURRENCY_TL_RATE, m_CurrencyTLRate);
	DDX_Control(pDX, IDC_CURRENCY_SYMBOL_POSITION, m_CurrencySymbolPosCtrl);
	DDX_Text(pDX, IDC_CURRENCY_CODE2, m_CurrencyCode2);
	DDX_Text(pDX, IDC_CURRENCY_SYMBOL2, m_CurrencySymbol2);
	DDX_Text(pDX, IDC_CURRENCY_SHORT_NAME2, m_CurrencyShortName2);
	DDX_Text(pDX, IDC_CURRENCY_DIGIT_GROUP_SYMBOL2, m_CurrencyDigitGroupSymbol2);
	DDX_Text(pDX, IDC_CURRENCY_DECIMAL_SYMBOL2, m_CurrencyDecimalSymbol2);
	DDX_Text(pDX, IDC_CURRENCY_EXPONENT2, m_CurrencyExponent2);
	DDX_CBString(pDX, IDC_CURRENCY_SYMBOL_POSITION2, m_CurrencySymbolPosition2);
	DDX_Text(pDX, IDC_CURRENCY_TL_RATE2, m_CurrencyTLRate2);
	DDX_Control(pDX, IDC_CURRENCY_SYMBOL_POSITION2, m_CurrencySymbolPositionCtrl2);
	DDX_Text(pDX, IDC_CURRENCY_CODE3, m_CurrencyCode3);
	DDX_Text(pDX, IDC_CURRENCY_SYMBOL3, m_CurrencySymbol3);
	DDX_Text(pDX, IDC_CURRENCY_SHORT_NAME3, m_CurrencyShortName3);
	DDX_Text(pDX, IDC_CURRENCY_DIGIT_GROUP_SYMBOL3, m_CurrencyDigitGroupSymbol3);
	DDX_Text(pDX, IDC_CURRENCY_DECIMAL_SYMBOL3, m_CurrencyDecimalSymbol3);
	DDX_Text(pDX, IDC_CURRENCY_EXPONENT3, m_CurrencyExponent3);
	DDX_CBString(pDX, IDC_CURRENCY_SYMBOL_POSITION3, m_CurrencySymbolPosition3);
	DDX_Control(pDX, IDC_CURRENCY_SYMBOL_POSITION3, m_CurrencySymbolPositionCtrl3);
	DDX_Text(pDX, IDC_CURRENCY_TL_RATE3, m_CurrencyTLRate3);
	DDX_Text(pDX, IDC_CURRENCY_CODE4, m_CurrencyCode4);
	DDX_Text(pDX, IDC_CURRENCY_SYMBOL4, m_CurrencySymbol4);
	DDX_Text(pDX, IDC_CURRENCY_SHORT_NAME4, m_CurrencyShortName4);
	DDX_Text(pDX, IDC_CURRENCY_DIGIT_GROUP_SYMBOL4, m_CurrencyDigitGroupSymbol4);
	DDX_Text(pDX, IDC_CURRENCY_DECIMAL_SYMBOL4, m_CurrencyDecimalSymbol4);
	DDX_Text(pDX, IDC_CURRENCY_EXPONENT4, m_CurrencyExponent4);
	DDX_CBString(pDX, IDC_CURRENCY_SYMBOL_POSITION4, m_CurrencySymbolPosition4);
	DDX_Control(pDX, IDC_CURRENCY_SYMBOL_POSITION4, m_CurrencySymbolPositionCtrl4);
	DDX_Text(pDX, IDC_CURRENCY_TL_RATE4, m_CurrencyTLRate4);
	DDX_Text(pDX, IDC_CURRENCY_CODE5, m_CurrencyCode5);
	DDX_Text(pDX, IDC_CURRENCY_CODE6, m_CurrencyCode6);
	DDX_Text(pDX, IDC_CURRENCY_SYMBOL5, m_CurrencySymbol5);
	DDX_Text(pDX, IDC_CURRENCY_SYMBOL6, m_CurrencySymbol6);
	DDX_Text(pDX, IDC_CURRENCY_SHORT_NAME5, m_CurrencyShortName5);
	DDX_Text(pDX, IDC_CURRENCY_SHORT_NAME6, m_CurrencyShortName6);
	DDX_Text(pDX, IDC_CURRENCY_DIGIT_GROUP_SYMBOL5, m_CurrencyDigitGroupSymbol5);
	DDX_Text(pDX, IDC_CURRENCY_DIGIT_GROUP_SYMBOL6, m_CurrencyDigitGroupSymbol6);
	DDX_Text(pDX, IDC_CURRENCY_DECIMAL_SYMBOL5, m_CurrencyDecimalSymbol5);
	DDX_Text(pDX, IDC_CURRENCY_DECIMAL_SYMBOL6, m_CurrencyDecimalSymbol6);
	DDX_Text(pDX, IDC_CURRENCY_EXPONENT5, m_CurrencyExponent5);
	DDX_Text(pDX, IDC_CURRENCY_EXPONENT6, m_CurrencyExponent6);
	DDX_CBString(pDX, IDC_CURRENCY_SYMBOL_POSITION5, m_CurrencySymbolPosition5);
	DDX_CBString(pDX, IDC_CURRENCY_SYMBOL_POSITION6, m_CurrencySymbolPosition6);
	DDX_Control(pDX, IDC_CURRENCY_SYMBOL_POSITION5, m_CurrencySymbolPositionCtrl5);
	DDX_Control(pDX, IDC_CURRENCY_SYMBOL_POSITION6, m_CurrencySymbolPositionCtrl6);
	DDX_Text(pDX, IDC_CURRENCY_TL_RATE5, m_CurrencyTLRate5);
	DDX_Text(pDX, IDC_CURRENCY_TL_RATE6, m_CurrencyTLRate6);
	DDX_Check(pDX, IDC_CHECK_DELETE_PROFILE, m_DeleteProfile);
	DDX_Control(pDX, IDC_CHECK_DELETE_PROFILE, m_DeleteProfileCtrl);
}


BEGIN_MESSAGE_MAP(CCurrencyEditDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CURRENCY_SYMBOL_POSITION, &CCurrencyEditDlg::OnCbnSelchangeCurrencySymbolPosition)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CCurrencyEditDlg message handlers


void CCurrencyEditDlg::OnCbnSelchangeCurrencySymbolPosition()
{
	// TODO: Add your control notification handler code here
}


int CCurrencyEditDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CCurrencyEditDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	m_CurrencySymbolPosCtrl.SetCurSel(0);
	SetWindowText((LPCTSTR)m_profileName); // caption
}
