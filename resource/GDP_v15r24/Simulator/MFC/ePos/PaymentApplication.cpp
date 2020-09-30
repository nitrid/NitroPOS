// PaymentApplication.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "PaymentApplication.h"
#include "afxdialogex.h"

extern void getAppTypeName(uint32 typeOfPayment, char *szAppTypeName);
extern void getDefaultPaymentName(uint32 typeOfPayment, char *szPaymentName);

// CPaymentApplication dialog

IMPLEMENT_DYNAMIC(CPaymentApplication, CDialogEx)

CPaymentApplication::CPaymentApplication(CWnd* pParent /*=NULL*/)
		: CDialogEx(CPaymentApplication::IDD, pParent)
		, pstPaymentApplicationInfoSelected(NULL)
{
	for (int i = 0; i < (sizeof(stPaymentApplicationInfo) / sizeof(ST_PAYMENT_APPLICATION_INFO)); ++i)
	{
		memset(&stPaymentApplicationInfo[i], 0x00, sizeof(ST_PAYMENT_APPLICATION_INFO));
		stPaymentApplicationInfo[i].StructSize = sizeof(ST_PAYMENT_APPLICATION_INFO);
	}
	numberOfTotalRecords = 0;
	numberOfTotalRecordsReceived = 0;
}

CPaymentApplication::~CPaymentApplication()
{
}

void CPaymentApplication::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listPaymentApplications);
}


BEGIN_MESSAGE_MAP(CPaymentApplication, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CPaymentApplication::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &CPaymentApplication::OnBnClickedOk)
END_MESSAGE_MAP()


// CPaymentApplication message handlers


BOOL CPaymentApplication::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ST_PAYMENT_APPLICATION_INFO payInfo;

	for (int i = 0; i < numberOfTotalRecordsReceived; i++)
	{
		CString cs;
		CString name;
		char szAppTypeName[32];

		name = CString(stPaymentApplicationInfo[i].name);

		memset(szAppTypeName, 0x00, sizeof(szAppTypeName));
		getAppTypeName(stPaymentApplicationInfo[i].AppType, szAppTypeName);

		cs.Format(L"%-20s [%d] [%04X] [%04X] [%04X] [%s]"
				  , name
				  , stPaymentApplicationInfo[i].u16BKMId
				  , stPaymentApplicationInfo[i].u16AppId
				  , stPaymentApplicationInfo[i].Status
				  , stPaymentApplicationInfo[i].Priority
				  , CString(szAppTypeName)
				 );

		m_listPaymentApplications.AddString(cs);
	}

	pstPaymentApplicationInfoSelected = &payInfo;

	return TRUE;
}


void CPaymentApplication::OnLbnSelchangeList1()
{
	int i =	m_listPaymentApplications.GetCurSel();

	pstPaymentApplicationInfoSelected = &stPaymentApplicationInfo[i];

	// TODO: Add your control notification handler code here
}


void CPaymentApplication::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

// CVasLoyaltyService dialog

IMPLEMENT_DYNAMIC(CVasLoyaltyService, CDialogEx)

CVasLoyaltyService::CVasLoyaltyService(CWnd* pParent /*=NULL*/)
		: CDialogEx(CVasLoyaltyService::IDD, pParent)
		, pstVasLoyaltyServiceInfoSelected(NULL)
{
	for (int i = 0; i < (sizeof(stVasLoyaltyServiceInfo) / sizeof(ST_LOYALTY_SERVICE_INFO)); ++i)
	{
		memset(&stVasLoyaltyServiceInfo[i], 0x00, sizeof(ST_LOYALTY_SERVICE_INFO));
		stVasLoyaltyServiceInfo[i].StructSize = sizeof(ST_LOYALTY_SERVICE_INFO);
	}
	numberOfTotalRecords = 0;
	numberOfTotalRecordsReceived = 0;
}

CVasLoyaltyService::~CVasLoyaltyService()
{
}

void CVasLoyaltyService::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listLoyaltyService);
}


BEGIN_MESSAGE_MAP(CVasLoyaltyService, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CVasLoyaltyService::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &CVasLoyaltyService::OnBnClickedOk)
END_MESSAGE_MAP()


// CPaymentApplication message handlers


BOOL CVasLoyaltyService::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	for (int i = 0; i < numberOfTotalRecordsReceived; i++)
	{
		CString cs;
		CString name;
		char    CustomerId[32];
		name = CString(stVasLoyaltyServiceInfo[i].name);

		memset(CustomerId, 0x00, sizeof(CustomerId));
		if (strlen(stVasLoyaltyServiceInfo[i].CustomerId))
			sprintf(CustomerId, "[%s]", stVasLoyaltyServiceInfo[i].CustomerId);

		cs.Format(L"%-20s [%d] %s"
				  , name
				  , stVasLoyaltyServiceInfo[i].ServiceId
				  , CString(CustomerId)
				 );

		m_listLoyaltyService.AddString(cs);
	}
	pstVasLoyaltyServiceInfoSelected = &stVasLoyaltyServiceInfo[0];

	return TRUE;
}


void CVasLoyaltyService::OnLbnSelchangeList1()
{
	int i =	m_listLoyaltyService.GetCurSel();

	pstVasLoyaltyServiceInfoSelected = &stVasLoyaltyServiceInfo[i];

	// TODO: Add your control notification handler code here
}


void CVasLoyaltyService::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

// CVasPaymentService dialog

IMPLEMENT_DYNAMIC(CVasPaymentService, CDialogEx)

CVasPaymentService::CVasPaymentService(CWnd* pParent /*=NULL*/)
		: CDialogEx(CVasPaymentService::IDD, pParent)
		, selectedPaymentService(0xFF)
{

	memset(&stVasPaymentServiceInfo, 0x00, sizeof(ST_VAS_PAYMENT_INFO));

	stVasPaymentServiceInfo.StructSize = sizeof(ST_VAS_PAYMENT_INFO);

	numberOfTotalRecords = 0;
	numberOfTotalRecordsReceived = 0;
}

CVasPaymentService::~CVasPaymentService()
{
}

void CVasPaymentService::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListPaymentService);
}

BEGIN_MESSAGE_MAP(CVasPaymentService, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CVasPaymentService::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &CVasPaymentService::OnBnClickedOk)
END_MESSAGE_MAP()


// CPaymentApplication message handlers

BOOL CVasPaymentService::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for (int i = 0; i < numberOfTotalRecordsReceived; i++)
	{
		CString cs;
		char defaultPaymentName[32];

		memset(defaultPaymentName, 0x00, sizeof(defaultPaymentName));

		getDefaultPaymentName(stVasPaymentServiceInfo.List[i].PaymentType, defaultPaymentName);

		cs.Format(L"%-20s [%04X] [%s]"
				  , CString(stVasPaymentServiceInfo.List[i].PaymentName)
				  , stVasPaymentServiceInfo.List[i].PaymentType
				  , CString(defaultPaymentName)
				 );

		m_ListPaymentService.AddString(cs);
	}

	selectedPaymentService = 0xFF;

	return TRUE;
}


void CVasPaymentService::OnLbnSelchangeList1()
{
	selectedPaymentService = m_ListPaymentService.GetCurSel();

	// TODO: Add your control notification handler code here
}


void CVasPaymentService::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
