#pragma once
#include "afxwin.h"
#include "atlcomtime.h"


// CFunctionDlg dialog

class CFunctionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFunctionDlg)

public:
	CFunctionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFunctionDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_FUNCTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	unsigned int m_FunctionFlag;
	void RearrangeDialogControls(int id);
	void ResetAllCheckBoxes();
	afx_msg void OnBnClickedOk();
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_CEKMECE_ACMA;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_GUN_SONU;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_PARAM_YUKLE;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_IADE;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_BANKA_IPTAL;
	CButton m_GMP_EXT_DEVICE_FUNC_BIT_TRANS_INQUERY;
	CButton m_GMP_EXT_DEVICE_FUNC_PAYMENT_VAS_IPTAL;


	afx_msg void OnBnClickedRadioParamYukle();
	afx_msg void OnBnClickedRadioZRapor();
	afx_msg void OnBnClickedRadioXRapor();
	afx_msg void OnBnClickedRadioMaliRapor();
	afx_msg void OnBnClickedRadioEkuRapor();
	afx_msg void OnBnClickedRadioMaliKumulatif();
	afx_msg void OnBnClickedRadioZRaporGonder();
	afx_msg void OnBnClickedRadioKasiyerSec();
	afx_msg void OnBnClickedRadioKasiyerLogout();
	afx_msg void OnBnClickedRadioCekmeceAcma();
	afx_msg void OnBnClickedRadioBankaGunSonu();
	afx_msg void OnBnClickedRadioBankaParamYukle();
	afx_msg void OnBnClickedRadioBankaIade();
	afx_msg void OnBnClickedRadioBankaIptal();
	afx_msg void OnBnClickedRadioTransInquery();
	afx_msg void OnBnClickedRadioVasPaymentRefund();
	virtual BOOL OnInitDialog();
	int m_ZNo_Start;
	int m_ZNo_Finish;
	int m_FNo_Start;
	int m_FNo_Finish;
	COleDateTime m_Date_Start;
	COleDateTime m_Time_Start;
	COleDateTime m_Date_Finish;
	COleDateTime m_Time_Finish;
	int m_EkuNo;
	afx_msg void OnBnClickedRadioBankaTransInquery2();
};

// CFunctionDlg dialog

class CLoyaltySelection : public CDialogEx
{
	DECLARE_DYNAMIC(CLoyaltySelection)

public:
	unsigned int m_Value;
	CLoyaltySelection(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoyaltySelection();

// Dialog Data
	enum { IDD = IDD_LOYALTY_SELECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void RearrangeDialogControls(int id);
	void ResetAllCheckBoxes();
	afx_msg void OnBnClickedOk();
	CButton m_MUSTERI_SORGU;
	CButton m_LOYALTY_PROCESS;
	CButton m_LOYALTY_DISCOUNT;

	afx_msg void OnBnClickedRadioMusteriSorgu();
	afx_msg void OnBnClickedRadioLoyaltyProcess();
	afx_msg void OnBnClickedRadioLoyaltyDiscount();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioParamYukle();
};

