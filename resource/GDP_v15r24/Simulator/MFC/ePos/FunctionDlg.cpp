// FunctionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "FunctionDlg.h"
#include "afxdialogex.h"
#include "GmpSmartDll.h"

// CFunctionDlg dialog

IMPLEMENT_DYNAMIC(CFunctionDlg, CDialogEx)

CFunctionDlg::CFunctionDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CFunctionDlg::IDD, pParent)
		, m_ZNo_Start(0)
		, m_ZNo_Finish(0)
		, m_FNo_Start(0)
		, m_FNo_Finish(0)
		, m_Date_Start((__time32_t)0)
		, m_Time_Start((__time32_t)0)
		, m_Date_Finish((__time32_t)0)
		, m_Time_Finish((__time32_t)0)
		, m_EkuNo(1)
{

}

CFunctionDlg::~CFunctionDlg()
{
}

void CFunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_PARAM_YUKLE, m_GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE);
	DDX_Control(pDX, IDC_RADIO_Z_RAPOR, m_GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR);
	DDX_Control(pDX, IDC_RADIO_X_RAPOR, m_GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR);
	DDX_Control(pDX, IDC_RADIO_MALI_RAPOR, m_GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR);
	DDX_Control(pDX, IDC_RADIO_EKU_RAPOR, m_GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR);
	DDX_Control(pDX, IDC_RADIO_MALI_KUMULATIF, m_GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF);
	DDX_Control(pDX, IDC_RADIO_Z_RAPOR_GONDER, m_GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER);
	DDX_Control(pDX, IDC_RADIO_CEKMECE_ACMA, m_GMP_EXT_DEVICE_FUNC_BIT_CEKMECE_ACMA);
	DDX_Control(pDX, IDC_RADIO_BANKA_GUN_SONU, m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_GUN_SONU);
	DDX_Control(pDX, IDC_RADIO_BANKA_PARAM_YUKLE, m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_PARAM_YUKLE);
	DDX_Control(pDX, IDC_RADIO_BANKA_IADE, m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_IADE);
	DDX_Control(pDX, IDC_RADIO_BANKA_IPTAL, m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_IPTAL);
	DDX_Control(pDX, IDC_RADIO_BANKA_TRANS_INQUERY, m_GMP_EXT_DEVICE_FUNC_BIT_TRANS_INQUERY);
	DDX_Control(pDX, IDC_RADIO_VAS_REFUND_ISLEM, m_GMP_EXT_DEVICE_FUNC_PAYMENT_VAS_IPTAL);

	DDX_Text(pDX, IDC_EDIT_ZNO_START, m_ZNo_Start);
	DDV_MinMaxInt(pDX, m_ZNo_Start, 0, 999999);
	DDX_Text(pDX, IDC_EDIT_ZNO_FINISH, m_ZNo_Finish);
	DDV_MinMaxInt(pDX, m_ZNo_Finish, 0, 999999);
	DDX_Text(pDX, IDC_EDIT_FNO_START, m_FNo_Start);
	DDV_MinMaxInt(pDX, m_FNo_Start, 0, 999999);
	DDX_Text(pDX, IDC_EDIT_FNO_FINISH, m_FNo_Finish);
	DDV_MinMaxInt(pDX, m_FNo_Finish, 0, 999999);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_Date_Start);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_Time_Start);
	DDX_DateTimeCtrl(pDX, IDC_DATE_FINISH, m_Date_Finish);
	DDX_DateTimeCtrl(pDX, IDC_TIME_FINISH, m_Time_Finish);
	DDX_Text(pDX, IDC_EDIT_EKUNO, m_EkuNo);
	DDV_MinMaxInt(pDX, m_EkuNo, 1, 999999);
}

BEGIN_MESSAGE_MAP(CFunctionDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFunctionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_PARAM_YUKLE, &CFunctionDlg::OnBnClickedRadioParamYukle)
	ON_BN_CLICKED(IDC_RADIO_Z_RAPOR, &CFunctionDlg::OnBnClickedRadioZRapor)
	ON_BN_CLICKED(IDC_RADIO_X_RAPOR, &CFunctionDlg::OnBnClickedRadioXRapor)
	ON_BN_CLICKED(IDC_RADIO_MALI_RAPOR, &CFunctionDlg::OnBnClickedRadioMaliRapor)
	ON_BN_CLICKED(IDC_RADIO_EKU_RAPOR, &CFunctionDlg::OnBnClickedRadioEkuRapor)
	ON_BN_CLICKED(IDC_RADIO_MALI_KUMULATIF, &CFunctionDlg::OnBnClickedRadioMaliKumulatif)
	ON_BN_CLICKED(IDC_RADIO_Z_RAPOR_GONDER, &CFunctionDlg::OnBnClickedRadioZRaporGonder)
	ON_BN_CLICKED(IDC_RADIO_CEKMECE_ACMA, &CFunctionDlg::OnBnClickedRadioCekmeceAcma)
	ON_BN_CLICKED(IDC_RADIO_BANKA_GUN_SONU, &CFunctionDlg::OnBnClickedRadioBankaGunSonu)
	ON_BN_CLICKED(IDC_RADIO_BANKA_PARAM_YUKLE, &CFunctionDlg::OnBnClickedRadioBankaParamYukle)
	ON_BN_CLICKED(IDC_RADIO_BANKA_IADE, &CFunctionDlg::OnBnClickedRadioBankaIade)
	ON_BN_CLICKED(IDC_RADIO_BANKA_IPTAL, &CFunctionDlg::OnBnClickedRadioBankaIptal)
	ON_BN_CLICKED(IDC_RADIO_BANKA_TRANS_INQUERY, &CFunctionDlg::OnBnClickedRadioTransInquery)
	ON_BN_CLICKED(IDC_RADIO_VAS_REFUND_ISLEM, &CFunctionDlg::OnBnClickedRadioVasPaymentRefund)
END_MESSAGE_MAP()


// CFunctionDlg message handlers


void CFunctionDlg::OnBnClickedOk()
{
	UpdateData(true);
	CDialogEx::OnOK();
}

void CFunctionDlg::ResetAllCheckBoxes()
{
	m_GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_CEKMECE_ACMA.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_GUN_SONU.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_PARAM_YUKLE.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_IADE.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_IPTAL.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_BIT_TRANS_INQUERY.SetCheck(false);
	m_GMP_EXT_DEVICE_FUNC_PAYMENT_VAS_IPTAL.SetCheck(false);
}

void CFunctionDlg::RearrangeDialogControls(int id)
{
	ResetAllCheckBoxes();

	switch (id)
	{
	case IDC_RADIO_PARAM_YUKLE:
		m_GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE;
		break;
	case IDC_RADIO_Z_RAPOR:
		m_GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR;
		break;
	case IDC_RADIO_X_RAPOR:
		m_GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR;
		break;
	case IDC_RADIO_MALI_RAPOR:
		m_GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR;
		break;
	case IDC_RADIO_EKU_RAPOR:
		m_GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR;
		break;
	case IDC_RADIO_MALI_KUMULATIF:
		m_GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF;
		break;
	case IDC_RADIO_Z_RAPOR_GONDER:
		m_GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER;
		break;
	case IDC_RADIO_CEKMECE_ACMA:
		m_GMP_EXT_DEVICE_FUNC_BIT_CEKMECE_ACMA.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_CEKMECE_ACMA;
		break;
	case IDC_RADIO_BANKA_GUN_SONU:
		m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_GUN_SONU.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_BANKA_GUN_SONU;
		break;
	case IDC_RADIO_BANKA_PARAM_YUKLE:
		m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_PARAM_YUKLE.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_BANKA_PARAM_YUKLE;
		break;
	case IDC_RADIO_BANKA_IADE:
		m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_IADE.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BANKA_IADE;
		break;
	case IDC_RADIO_BANKA_IPTAL:
		m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_IPTAL.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BANKA_IPTAL;
		break;
	case IDC_RADIO_BANKA_TRANS_INQUERY:
		m_GMP_EXT_DEVICE_FUNC_BIT_TRANS_INQUERY.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_TRANS_INQUERY;
		break;
	case IDC_RADIO_VAS_REFUND_ISLEM:
		m_GMP_EXT_DEVICE_FUNC_PAYMENT_VAS_IPTAL.SetCheck(true);
		m_FunctionFlag = GMP_EXT_DEVICE_FUNC_PAYMENT_VAS_IPTAL;
		break;
	}
}

void CFunctionDlg::OnBnClickedRadioParamYukle()
{
	RearrangeDialogControls(IDC_RADIO_PARAM_YUKLE);
}
void CFunctionDlg::OnBnClickedRadioZRapor()
{
	RearrangeDialogControls(IDC_RADIO_Z_RAPOR);
}
void CFunctionDlg::OnBnClickedRadioXRapor()
{
	RearrangeDialogControls(IDC_RADIO_X_RAPOR);
}
void CFunctionDlg::OnBnClickedRadioMaliRapor()
{
	RearrangeDialogControls(IDC_RADIO_MALI_RAPOR);
}
void CFunctionDlg::OnBnClickedRadioEkuRapor()
{
	RearrangeDialogControls(IDC_RADIO_EKU_RAPOR);
}
void CFunctionDlg::OnBnClickedRadioMaliKumulatif()
{
	RearrangeDialogControls(IDC_RADIO_MALI_KUMULATIF);
}
void CFunctionDlg::OnBnClickedRadioZRaporGonder()
{
	RearrangeDialogControls(IDC_RADIO_Z_RAPOR_GONDER);
}
void CFunctionDlg::OnBnClickedRadioCekmeceAcma()
{
	RearrangeDialogControls(IDC_RADIO_CEKMECE_ACMA);
}
void CFunctionDlg::OnBnClickedRadioBankaGunSonu()
{
	RearrangeDialogControls(IDC_RADIO_BANKA_GUN_SONU);
}
void CFunctionDlg::OnBnClickedRadioBankaParamYukle()
{
	RearrangeDialogControls(IDC_RADIO_BANKA_PARAM_YUKLE);
}
void CFunctionDlg::OnBnClickedRadioBankaIade()
{
	RearrangeDialogControls(IDC_RADIO_BANKA_IADE);
}
void CFunctionDlg::OnBnClickedRadioBankaIptal()
{
	RearrangeDialogControls(IDC_RADIO_BANKA_IPTAL);
}
void CFunctionDlg::OnBnClickedRadioTransInquery()
{
	RearrangeDialogControls(IDC_RADIO_BANKA_TRANS_INQUERY);
}
void CFunctionDlg::OnBnClickedRadioVasPaymentRefund()
{
	RearrangeDialogControls(IDC_RADIO_VAS_REFUND_ISLEM);
}

BOOL CFunctionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE.SetCheck(true);
	m_FunctionFlag = GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

// CLoyaltySelection dialog

IMPLEMENT_DYNAMIC(CLoyaltySelection, CDialogEx)

CLoyaltySelection::CLoyaltySelection(CWnd* pParent /*=NULL*/)
		: CDialogEx(CLoyaltySelection::IDD, pParent)
{

}

CLoyaltySelection::~CLoyaltySelection()
{
}

void CLoyaltySelection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_LOYALTY_ISLEM   , m_LOYALTY_PROCESS);
	DDX_Control(pDX, IDC_RADIO_MUSTERI_SORGU   , m_MUSTERI_SORGU);
	DDX_Control(pDX, IDC_RADIO_LOYALTY_DISCOUNT, m_LOYALTY_DISCOUNT);
}

BEGIN_MESSAGE_MAP(CLoyaltySelection, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoyaltySelection::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_LOYALTY_DISCOUNT, &CLoyaltySelection::OnBnClickedRadioLoyaltyDiscount)
	ON_BN_CLICKED(IDC_RADIO_LOYALTY_ISLEM   , &CLoyaltySelection::OnBnClickedRadioLoyaltyProcess)
	ON_BN_CLICKED(IDC_RADIO_MUSTERI_SORGU   , &CLoyaltySelection::OnBnClickedRadioMusteriSorgu)
END_MESSAGE_MAP()


// CFunctionDlg message handlers


void CLoyaltySelection::OnBnClickedOk()
{
	UpdateData(true);
	CDialogEx::OnOK();
}

void CLoyaltySelection::ResetAllCheckBoxes()
{
	m_MUSTERI_SORGU.SetCheck(false);
	m_LOYALTY_PROCESS.SetCheck(false);
	m_LOYALTY_DISCOUNT.SetCheck(false);
}

void CLoyaltySelection::RearrangeDialogControls(int id)
{
	ResetAllCheckBoxes();

	switch (id)
	{
	case IDC_RADIO_LOYALTY_ISLEM:
		m_LOYALTY_PROCESS.SetCheck(true);
		m_Value = IDC_RADIO_LOYALTY_ISLEM;
		break;
	case IDC_RADIO_MUSTERI_SORGU:
		m_MUSTERI_SORGU.SetCheck(true);
		m_Value = IDC_RADIO_MUSTERI_SORGU;
		break;
	case IDC_RADIO_LOYALTY_DISCOUNT:
		m_LOYALTY_DISCOUNT.SetCheck(true);
		m_Value = IDC_RADIO_LOYALTY_DISCOUNT;
		break;
	}
}

void CLoyaltySelection::OnBnClickedRadioLoyaltyDiscount()
{
	RearrangeDialogControls(IDC_RADIO_LOYALTY_DISCOUNT);
}

void CLoyaltySelection::OnBnClickedRadioLoyaltyProcess()
{
	RearrangeDialogControls(IDC_RADIO_LOYALTY_ISLEM);
}
void CLoyaltySelection::OnBnClickedRadioMusteriSorgu()
{
	RearrangeDialogControls(IDC_RADIO_MUSTERI_SORGU);
}

BOOL CLoyaltySelection::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_MUSTERI_SORGU.SetCheck(true);
	m_Value = IDC_RADIO_MUSTERI_SORGU;

	return TRUE;  // return TRUE unless you set the focus to a control
}

