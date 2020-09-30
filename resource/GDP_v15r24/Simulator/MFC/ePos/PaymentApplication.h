#pragma once
#include "afxwin.h"
#include "GmpSmartDll.h"

// CPaymentApplication dialog


class CPaymentApplication : public CDialogEx
{
	DECLARE_DYNAMIC(CPaymentApplication)

public:
	CPaymentApplication(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPaymentApplication();

// Dialog Data
	enum { IDD = IDD_PAYMENT_APPLICATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listPaymentApplications;
	ST_PAYMENT_APPLICATION_INFO stPaymentApplicationInfo[32];
	ST_PAYMENT_APPLICATION_INFO* pstPaymentApplicationInfoSelected;
	uint8 numberOfTotalRecords;
	uint8 numberOfTotalRecordsReceived;

	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedOk();
};


// CPaymentApplication dialog


class CVasLoyaltyService : public CDialogEx
{
	DECLARE_DYNAMIC(CVasLoyaltyService)

public:
	CVasLoyaltyService(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVasLoyaltyService();

// Dialog Data
	enum { IDD = IDD_VAS_LOYALTY_SERVICE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listLoyaltyService;
	ST_LOYALTY_SERVICE_INFO stVasLoyaltyServiceInfo[32];
	ST_LOYALTY_SERVICE_INFO* pstVasLoyaltyServiceInfoSelected;
	uint8 numberOfTotalRecords;
	uint8 numberOfTotalRecordsReceived;

	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedOk();
};


class CVasPaymentService : public CDialogEx
{
	DECLARE_DYNAMIC(CVasPaymentService)

public:
	CVasPaymentService(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVasPaymentService();

// Dialog Data
	enum { IDD = IDD_VAS_PAYMENT_SERVICE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListPaymentService;
	uint8    selectedPaymentService;
	ST_VAS_PAYMENT_INFO  stVasPaymentServiceInfo;
	uint8 numberOfTotalRecords;
	uint8 numberOfTotalRecordsReceived;

	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedOk();
};
