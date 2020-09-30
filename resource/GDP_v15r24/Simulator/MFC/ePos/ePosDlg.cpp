
// ePosDlg.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ePos.h"
#include "ePosDlg.h"
#include "afxdialogex.h"
#include "PaymentApplication.h"
#include "ItemNo.h"
#include "TicketDlg.h"
#include "invoiceDlg.h"
#include "OnlineInvoiceDlg.h"
#include "CariHesapDlg.h"
#include "TaxFreeDlg.h"
#include "MatrahsizDlg.h"
#include "CashierDlg.h"
#include "UserMessageDlg.h"
#include "DBTranDlg.h"
#include "FunctionDlg.h"
#include "PasswordDlg.h"
#include "DepartmentDlg.h"
#include "PluConsoleDlg.h"
#include "GetInputDlg.h"
#include "EkuDlg.h"
#include "PaymentDlg.h"
#include "SelectUniqueId.h"
#include "DoPayment.h"
#include "DatabaseConsole.h"
#include "FileSystemDlg.h"
#include "CurrencyEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef DEVELOPMENT
#define RESPONSE_FLAGS GMP3_OPTION_ECHO_PRINTER | GMP3_OPTION_ECHO_ITEM_DETAILS | GMP3_OPTION_ECHO_PAYMENT_DETAILS | GMP3_OPTION_ECHO_LOYALTY_DETAILS
#else
#define RESPONSE_FLAGS GMP3_OPTION_ECHO_ITEM_DETAILS | GMP3_OPTION_ECHO_PAYMENT_DETAILS
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CePosDlg dialog

CePosDlg::CePosDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CePosDlg::IDD, pParent)
		, m_csInput(_T(""))
		, m_csTtemCount(_T(""))
		, m_pingTimer(NULL)
		, m_ServerSocket(INVALID_SOCKET)
		, m_ClientSocket(INVALID_SOCKET)
		, m_MEcrClientSocket(INVALID_SOCKET)
		, m_MEcrServerSocket(INVALID_SOCKET)
		, m_TaxExceptional_Taxless(false)
		, m_TaxExceptional_Vat_Excluded(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void getAppTypeName(uint32 typeOfPayment, char *szAppTypeName)
{
	if (typeOfPayment == 0)
		return;

	switch (typeOfPayment)
	{
	case TLV_OKC_ASSIST_VAS_TYPE_ADISYON:
		strcpy(szAppTypeName, "TYPE_ADISYON");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_IN_FLIGHT:
		strcpy(szAppTypeName, "TYPE_IN_FLIGHT");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_INGENICO:
		strcpy(szAppTypeName, "TYPE_INGENICO");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_OTHER:
		strcpy(szAppTypeName, "TYPE_OTHER");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_AKTIFNOKTA:
		strcpy(szAppTypeName, "TYPE_AKTIF.");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_MOBIL_ODEME:
		strcpy(szAppTypeName, "TYPE_MOBIL_ODEME");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_OTOPARK:
		strcpy(szAppTypeName, "TYPE_OTOPARK");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_YEMEKCEKI:
		strcpy(szAppTypeName, "TYPE_YEMEKCEKI");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_LOYALTY:
		strcpy(szAppTypeName, "TYPE_LOYALTY");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_PAYMENT:
		strcpy(szAppTypeName, "TYPE_ODEME");
		break;
	case TLV_OKC_ASSIST_VAS_TYPE_ALL:
		break;
	default:
		strcpy(szAppTypeName, "TYPE_UNKNOWN");
		break;
	}
}

void getDefaultPaymentName(uint32 typeOfPayment, char *szPaymentName)
{
	switch (typeOfPayment)
	{
	case PAYMENT_YEMEKCEKI:
		strcpy(szPaymentName, "YEMEK ÇEKÝ");
		break;

	case REVERSE_PAYMENT_YEMEKCEKI:
		strcpy(szPaymentName, "YEMEK ÇEKÝ ÝADE");
		break;

	case REVERSE_PAYMENT_MOBILE:
	case PAYMENT_MOBILE:
		strcpy(szPaymentName, "MOBÝL ÖDEME");
		break;

	case REVERSE_PAYMENT_HEDIYE_CEKI:
	case PAYMENT_HEDIYE_CEKI:
		strcpy(szPaymentName, "HEDÝYE ÇEKÝ");
		break;

	case PAYMENT_IKRAM:
		strcpy(szPaymentName, "ÝKRAM");
		break;

	case PAYMENT_ODEMESIZ:
		strcpy(szPaymentName, "ÖDEMESÝZ");
		break;

	case PAYMENT_KAPORA:
		strcpy(szPaymentName, "KAPORA");
		break;

	case PAYMENT_PUAN:
	case REVERSE_PAYMENT_PUAN:
		strcpy(szPaymentName, "PUAN");
		break;

	case PAYMENT_GIDER_PUSULASI:
		strcpy(szPaymentName, "GÝDER PUSULASI");
		break;

	case PAYMENT_BANKA_TRANSFERI:
		strcpy(szPaymentName, "BANKA TRANSFERÝ");
		break;

	case PAYMENT_CEK:
		strcpy(szPaymentName, "ÇEK");
		break;

	case PAYMENT_ACIK_HESAP:
		strcpy(szPaymentName, "AÇIK HESAP");
		break;

	case PAYMENT_DIGER:
		strcpy(szPaymentName, "DÝÐER");
		break;

	case REVERSE_PAYMENT_ACIK_HESAP:
		strcpy(szPaymentName, "AÇIK HESAP");
		break;
	case REVERSE_PAYMENT_BANK_CARD_VOID:
	case REVERSE_PAYMENT_BANK_CARD_REFUND:
	case PAYMENT_BANK_CARD:
		strcpy(szPaymentName, "KREDÝ");
		break;

	case PAYMENT_CASH_TL:
	case PAYMENT_CASH_CURRENCY:
		strcpy(szPaymentName, "NAKÝT");
		break;

	case REVERSE_PAYMENT_CASH:
		strcpy(szPaymentName, "NAKÝT ÝADE");
		break;

	default:
		if (typeOfPayment & REVERSE_PAYMENT_ALL)
			strcpy(szPaymentName, "ÝADE");
		else
			strcpy(szPaymentName, "ÖDEME");
		break;
	}
}

void CePosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COM_INFO, m_listPrinterOutput);
	DDX_Control(pDX, IDC_LIST_BATCH_COMMAND, m_listBatchCommand);
	DDX_Control(pDX, IDC_EDIT_MAIN_DISPLAY, m_ListControlMainDisplay);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_EditControlInput);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_csInput);
	DDX_Control(pDX, IDC_COMBO_CURRENCY, m_comboBoxCurrency);
	DDX_Control(pDX, IDC_LIST_TRANSACTION, m_listTransaction);
	DDX_Control(pDX, IDC_LIST_STATUS, m_listStatus);
	DDX_Control(pDX, IDC_TREE_INTERFACE, m_treeIterface);
	DDX_Control(pDX, IDC_LIST_TEST_MODE, m_ListMasterECRMode);
	DDX_Control(pDX, IDC_LIST_INTERFACE_SETTINGS, m_ListInterfaceSettings);
}

BEGIN_MESSAGE_MAP(CePosDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_NEW_BACKGROUND_TRANSACTION , &CePosDlg::OnInterfacePopupMenuNewBackgroundTransaction)
	ON_COMMAND(ID__TRANSFERBACKGROUNGTRXINTOFRONTSCREEN , &CePosDlg::OnInterfacePopupMenuTransferBackgroundTrxintoFrontScreen)
	ON_BN_CLICKED(IDC_BUTTON_PAIR, &CePosDlg::OnBnClickedButtonPair)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_1, &CePosDlg::OnBnClickedButtonDepartman1)
	ON_BN_CLICKED(IDC_BUTTON_TICKETHEADER, &CePosDlg::OnBnClickedButtonTicketheader)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_2, &CePosDlg::OnBnClickedButtonDepartman2)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_3, &CePosDlg::OnBnClickedButtonDepartman3)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_4, &CePosDlg::OnBnClickedButtonDepartman4)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_5, &CePosDlg::OnBnClickedButtonDepartman5)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_6, &CePosDlg::OnBnClickedButtonDepartman6)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_7, &CePosDlg::OnBnClickedButtonDepartman7)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_8, &CePosDlg::OnBnClickedButtonDepartman8)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_9, &CePosDlg::OnBnClickedButtonDepartman9)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_10, &CePosDlg::OnBnClickedButtonDepartman10)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_11, &CePosDlg::OnBnClickedButtonDepartman11)
	ON_BN_CLICKED(IDC_BUTTON_DEPARTMAN_12, &CePosDlg::OnBnClickedButtonDepartman12)
	ON_BN_CLICKED(IDC_CHECKBOX_BANKING_OPT1, &CePosDlg::OnBnClickedCheckBox1)
	ON_BN_CLICKED(IDC_CHECKBOX_BANKING_OPT2, &CePosDlg::OnBnClickedCheckBox2)
	ON_BN_CLICKED(IDC_CHECKBOX_BANKING_OPT3, &CePosDlg::OnBnClickedCheckBox3)
	ON_BN_CLICKED(IDC_CHECKBOX_BANKING_OPT4, &CePosDlg::OnBnClickedCheckBox4)
	ON_BN_CLICKED(IDC_CHECKBOX_BANKING_OPT5, &CePosDlg::OnBnClickedCheckBox5)
	ON_BN_CLICKED(IDC_CHECKBOX_BANKING_OPT6, &CePosDlg::OnBnClickedCheckBox6)
	ON_BN_CLICKED(IDC_CHECKBOX_BANKING_OPT7, &CePosDlg::OnBnClickedCheckBox7)
	ON_BN_CLICKED(IDC_CHECKBOX_BANKING_OPT8, &CePosDlg::OnBnClickedCheckBox8)
	ON_BN_CLICKED(IDC_BUTTON_NAKIT, &CePosDlg::OnBnClickedButtonNakit)
	ON_BN_CLICKED(IDC_BUTTON_PLU, &CePosDlg::OnBnClickedButtonPlu)
	ON_BN_CLICKED(IDC_BUTTON_INVOICE, &CePosDlg::OnBnClickedButtonInvoice)
	ON_BN_CLICKED(IDC_SET_EXCHANGE_PROFILE, &CePosDlg::OnBnClickedButtonSetExchangeProfile)
	ON_BN_CLICKED(IDC_BUTTON_REVERSE_PAYMENTS, &CePosDlg::OnBnClickedButtonReversePayments)
	ON_BN_CLICKED(IDC_BUTTON_VOID_ALL, &CePosDlg::OnBnClickedButtonVoidAll)
	ON_BN_CLICKED(IDC_BUTTON_VOID_ITEM, &CePosDlg::OnBnClickedButtonVoidItem)
	ON_BN_CLICKED(IDC_BUTTON_MATRAHSIZ, &CePosDlg::OnBnClickedButtonMatrahsiz)
	ON_BN_CLICKED(IDC_BUTTON_YEMEKCEKI, &CePosDlg::OnBnClickedButtonYemekCeki)
	ON_BN_CLICKED(IDC_BUTTON_LOYALTY, &CePosDlg::OnBnClickedButtonLoyalty)
	ON_BN_CLICKED(IDC_BUTTON_TAXEXCEPTION_TAXLESS, &CePosDlg::OnBnClickedButtonTaxExceptionTaxless)
	ON_BN_CLICKED(IDC_BUTTON_TAXEXCEPTION_VAT_EXCLUDED, &CePosDlg::OnBnClickedButtonTaxExceptionVatExcluded)
	ON_BN_CLICKED(IDC_BUTTON_TAXFREE_SET, &CePosDlg::OnBnClickedButtonTaxfreeSet)
	ON_BN_CLICKED(IDC_BUTTON_TAXFREE_SET_TAXREFUND_AMOUNT, &CePosDlg::OnBnClickedButtonTaxfreeSetTaxfundAmount)
	ON_BN_CLICKED(IDC_BUTTON_VOID_MATRAHSIZ, &CePosDlg::OnBnClickedButtonXXX2)
	ON_BN_CLICKED(IDC_BUTTON_KASA_AVANS, &CePosDlg::OnBnClickedButtonKasaAvans)
	ON_BN_CLICKED(IDC_BUTTON_CARI_HESAP, &CePosDlg::OnBnClickedButtonCariHesap)
	ON_BN_CLICKED(IDC_BUTTON_KASA_ODEME, &CePosDlg::OnBnClickedButtonKasaOdeme)
	ON_BN_CLICKED(IDC_BUTTON_PRETOTAL, &CePosDlg::OnBnClickedButtonPretotal)
	ON_BN_CLICKED(IDC_BUTTON_TUTAR_ARTIRIM, &CePosDlg::OnBnClickedButtonTutarArtirim)
	ON_BN_CLICKED(IDC_BUTTON_TUTAR_INDIR, &CePosDlg::OnBnClickedButtonTutarIndir)
	ON_BN_CLICKED(IDC_BUTTON_OTOPARK_ENTRY_TICKET, &CePosDlg::OnBnClickedButtonOtoparkEntryTicket)
	ON_BN_CLICKED(IDC_BUTTON_PERCENT_INC, &CePosDlg::OnBnClickedButtonPercentInc)
	ON_BN_CLICKED(IDC_BUTTON_PERCENT_DEC, &CePosDlg::OnBnClickedButtonPercentDec)
	ON_BN_CLICKED(IDC_BUTTON_VOID_PAYMENT, &CePosDlg::OnBnClickedButtonVoidPayment)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CePosDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_CONDITION, &CePosDlg::OnBnClickedButtonCondition)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_FLAGS, &CePosDlg::OnBnClickedButtonOptionFlags)
	ON_BN_CLICKED(IDC_BUTTON_GET_DEPARTMENTS, &CePosDlg::OnBnClickedButtonGetDepartments)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_CASHIER, &CePosDlg::OnBnClickedButtonSelectCashier)
	ON_BN_CLICKED(IDC_BUTTON_CURRENCY, &CePosDlg::OnBnClickedButtonCurrency)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CePosDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_JUMP_ECR_SINGLE_PAYMENT, &CePosDlg::OnBnClickedButtonJumpEcrForSinglePayment)
	ON_BN_CLICKED(IDC_BUTTON_JUMP_ECR_COMPLETE_PAYMENT, &CePosDlg::OnBnClickedButtonJumpEcrForCompletePayment)
	ON_BN_CLICKED(IDC_BUTTON_GETINPUT, &CePosDlg::OnBnClickedButtonGetInput)
	ON_BN_CLICKED(IDC_BUTTON_COMM_SCENARIO, &CePosDlg::OnBnClickedButtonSetCommScenario)
	ON_BN_CLICKED(IDC_BUTTON_CURRENCY2, &CePosDlg::OnBnClickedButtonGetSetCurrencyProfile)
	ON_BN_CLICKED(IDC_BUTTON_SET_uAPPLICATION_COMMAND, &CePosDlg::OnBnClickedButtonSetuApplicationCommand)
	ON_BN_CLICKED(IDC_BUTTON_0, &CePosDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, &CePosDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CePosDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CePosDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CePosDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CePosDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CePosDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CePosDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CePosDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CePosDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_00, &CePosDlg::OnBnClickedButton00)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CePosDlg::OnBnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_PAYMENT_CASH, &CePosDlg::OnBnClickedButtonPaymentCash)
	ON_BN_CLICKED(IDC_BUTTON_BATCHCOMMAND_SEND			, &CePosDlg::OnBnClickedButtonBatchCommandSend)
	ON_BN_CLICKED(IDC_BUTTON_TESTTRANSACTION				, &CePosDlg::OnBnClickedButtonTestTransaction)
	ON_BN_CLICKED(IDC_BUTTON_BATCHCOMMAND_LISTENANDSEND	, &CePosDlg::OnBnClickedButtonBatchCommandListenAndSend)
	ON_BN_CLICKED(IDC_BUTTON_BATCHCOMMAND_CLEARLIST		, &CePosDlg::OnBnClickedButtonBatchCommandClearList)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CePosDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_GET_PLU, &CePosDlg::OnBnClickedButtonGetPlu)
	ON_BN_CLICKED(IDC_BUTTON_STATUS, &CePosDlg::OnBnClickedButtonStatus)
	ON_BN_CLICKED(IDC_BUTTON_PRETOTAL3, &CePosDlg::OnBnClickedButtonPretotal3)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_TOTALS_AND_PAYMENTS, &CePosDlg::OnBnClickedButtonPrintTotalsAndPayments)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_BEFORE_MF, &CePosDlg::OnBnClickedButtonPrintBeforeMf)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_MF, &CePosDlg::OnBnClickedButtonPrintMf)
	ON_BN_CLICKED(IDC_BUTTON_ECHO, &CePosDlg::OnBnClickedButtonEcho)
	ON_BN_CLICKED(IDC_BUTTON_CREDIT, &CePosDlg::OnBnClickedButtonCredit)
	ON_BN_CLICKED(IDC_BUTTON_TICKET, &CePosDlg::OnBnClickedButtonTicket)
	ON_BN_CLICKED(IDC_BUTTON_TICKETHEADER2, &CePosDlg::OnBnClickedButtonFiscalPrinterStart)
	ON_BN_CLICKED(IDC_BUTTON_REFUND, &CePosDlg::OnBnClickedButtonRefund)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_TICKET, &CePosDlg::OnBnClickedButtonCloseTicket)
	ON_BN_CLICKED(IDC_BUTTON_PERCENT_DEC2, &CePosDlg::OnBnClickedButtonPercentDec2)
	ON_BN_CLICKED(IDC_BUTTON_FUNCTION, &CePosDlg::OnBnClickedButtonFunction)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PLU_CONSOLE, &CePosDlg::OnBnClickedButtonPluConsole)
	ON_BN_CLICKED(IDC_BUTTON_EKU_CONSOLE, &CePosDlg::OnBnClickedButtonEkuConsole)
	ON_BN_CLICKED(IDC_BUTTON_FILESYSTEM_CONSOLE, &CePosDlg::OnBnClickedButtonFileSystemConsole)
	ON_BN_CLICKED(IDC_BUTTON_PING, &CePosDlg::OnBnClickedButtonPing)
	ON_BN_CLICKED(IDC_BUTTON_GET_HANDLE_LIST, &CePosDlg::OnBnClickedButtonGetHandleList)
	ON_BN_CLICKED(IDC_BUTTON_READ_CARD, &CePosDlg::OnBnClickedButtonReadCard)
	ON_BN_CLICKED(IDC_BUTTON_GET_UNIQUE_ID, &CePosDlg::OnBnClickedButtonGetUniqueId)
	ON_BN_CLICKED(IDC_BUTTON_GET_SET_FISCAL_HEADER, &CePosDlg::OnBnClickedButtonGetSetFiscalHeader)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_UNIQUE_ID, &CePosDlg::OnBnClickedButtonSelectUniqueId)
	ON_BN_CLICKED(IDC_BUTTON_PAYMENT, &CePosDlg::OnBnClickedButtonPayment)
	ON_BN_CLICKED(IDC_BUTTON_DATABASE_CONSOLE, &CePosDlg::OnBnClickedButtonDatabaseConsole)
	ON_WM_WINDOWPOSCHANGED()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FUCTIONALCONTROLS, &CePosDlg::OnSelchangeTabFunctionalControls)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_COMMAND_MODE, &CePosDlg::OnSelchangeTabCommandMode)
	ON_LBN_SELCHANGE(IDC_LIST_STATUS, &CePosDlg::OnLbnSelchangeListStatus)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_INTERFACE, &CePosDlg::OnSelchangedTreeInterface)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_INTERFACE, &CePosDlg::OnRclickTreeInterface)
	ON_BN_CLICKED(IDC_BUTTON_MECR_GET_BG_TRX_LIST	, &CePosDlg::OnBnClickedButtonGetMEcrBGTrxList)
	ON_BN_CLICKED(IDC_BUTTON_MECR_GET_BG_TRX_DATA	, &CePosDlg::OnBnClickedButtonGetMEcrBGTrxData)
	ON_BN_CLICKED(IDC_BUTTON_MECR_SET_BG_TRX_STATUS	, &CePosDlg::OnBnClickedButtonSetMEcrBGTrxStatus)
	ON_BN_CLICKED(IDC_BUTTON_MECR_LISTEN	, &CePosDlg::OnBnClickedButtonListenMEcr)
	ON_BN_CLICKED(IDC_BUTTON_SET_ONLINE_INVOICE, &CePosDlg::OnBnClickedButtonSetOnlineInvoice)
	ON_BN_CLICKED(IDC_BUTTON_TAXFREE_INFO, &CePosDlg::OnBnClickedButtonTaxFreeInfo)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_PAIRING_STATUS, &CePosDlg::OnBnClickedButtonCheckPairingStatus)

	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

#define TAB_ECR			0
#define TAB_ECR_EXT		1
#define TAB_FUNCTIONS	2
#define TAB_BANKING		3
#define TAB_CONSOLES	4
#define TAB_DEVELOPERS	5

#define TAB_SINGLE_COMMAND_MODE		0
#define TAB_BATCH_COMMAND_MODE		1
#define TAB_MASTERECR_MODE			2

extern	int CallbackFunctionSend(BYTE*buffer, int len);


// CePosDlg message handlers

BOOL CePosDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//yunus
	// TODO: Add extra initialization here
	//gmp3Library = LoadLibrary(L"GmpSmartDLL.dll");

	//if( !gmp3Library )
	//{
	//	MessageBox(L"GmpSmartDLL.dll Yüklenemedi", L"HATA", MB_OKCANCEL );
	//	return FALSE;
	//}

	memset(&m_GMPPairResp, 0x00, sizeof(m_GMPPairResp));
	myFont1 = new CFont();
	myFont2 = new CFont();
	myFont3 = new CFont();
	buttonFont = new CFont();
	buttonFontBig = new CFont();

	myFont1->CreateFont(56, 0, 0, 0, FW_HEAVY, false, false,
						0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
						FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));
	myFont2->CreateFont(14, 0, 0, 0, FW_MEDIUM, false, false,
						0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
						FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));
	myFont3->CreateFont(32, 0, 0, 0, FW_HEAVY, false, false,
						0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
						FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));
	buttonFont->CreateFont(15, 0, 0, 0, FW_REGULAR, false, false,
						   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
						   FIXED_PITCH | FF_MODERN, _T("Arial"));
	buttonFontBig->CreateFont(24, 0, 0, 0, FW_BLACK, false, false,
							  0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
							  FIXED_PITCH | FF_MODERN, _T("Arial"));

	m_EditControlInput.SetFont(myFont1, true);
	m_listPrinterOutput.SetFont(myFont2, true);
	m_ListMasterECRMode.SetFont(myFont2, true);
	m_listBatchCommand.SetFont(myFont2, true);
	m_listTransaction.SetFont(myFont2, true);
	m_listStatus.SetFont(myFont2, true);
	m_comboBoxCurrency.SetFont(myFont2, true);
	m_ListControlMainDisplay.SetFont(myFont3, true);


	m_myImageList.Create(20, 20, ILC_COLOR16, 0, 0);
	m_myImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_IDE280));
	m_myImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_TICKET));
	m_myImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_DB));
	m_treeIterface.SetFont(myFont2, true);
	m_treeIterface.SetImageList(&m_myImageList, TVSIL_NORMAL);
	m_treeIterface.SetImageList(&m_myImageList, TVSIL_STATE);

	m_pEditBkBrush = new CBrush(RGB(255, 255, 255));

	CreateButton(&m_Button_TestTransaction				, L"Test\nTrx"	, IDC_BUTTON_TESTTRANSACTION);
	CreateButton(&m_Button_GetHandleList, L"Get Handles", IDC_BUTTON_GET_HANDLE_LIST);
	CreateButton(&m_Button_Ping, L"Ping", IDC_BUTTON_PING);
	CreateButton(&m_Button_Echo, L"Echo", IDC_BUTTON_ECHO);
	CreateButton(&m_Button_Pair, L"Pair", IDC_BUTTON_PAIR);
	CreateButton(&m_Button_TicketSale, L"Cinema\nTicket", IDC_BUTTON_TICKET);
	CreateButton(&m_Button_PLUSale, L"PLU\nSale", IDC_BUTTON_PLU);
	CreateButton(&m_Button_ReadTransactionFromECR, L"RELOAD\nTICKET", IDC_BUTTON_STATUS);
	CreateButton(&m_Button_VoidAllTicket, L"VOID\nTICKET", IDC_BUTTON_VOID_ALL);

	CreateButton(&m_Button_JumpEcr_ForSinglePayment	, L"Jump ECR\nSingle Payment", IDC_BUTTON_JUMP_ECR_SINGLE_PAYMENT);
	CreateButton(&m_Button_JumpEcr_ForCompletePayment	, L"Jump ECR\nComplete Payment", IDC_BUTTON_JUMP_ECR_COMPLETE_PAYMENT);
	CreateButton(&m_Button_GetInput	, L"Get Input", IDC_BUTTON_GETINPUT);
	CreateButton(&m_Button_SetCommScenario	, L"Comm Scenario", IDC_BUTTON_COMM_SCENARIO);
	CreateButton(&m_Button_SetuApplicationCommand, L"Set uApp\nCommand", IDC_BUTTON_SET_uAPPLICATION_COMMAND);

	CreateButton(&m_Button_OpenHandle, L"Open Handle", IDC_BUTTON_TICKETHEADER2);
	CreateButton(&m_Button_PLUConsole, L"PLU\nConsole", IDC_BUTTON_PLU_CONSOLE);
	CreateButton(&m_Button_Functions, L"Functions", IDC_BUTTON_FUNCTION);
	CreateButton(&m_Button_SelectUniqueId, L"Select\nUnique Id", IDC_BUTTON_SELECT_UNIQUE_ID);
	CreateButton(&m_Button_GetUniqueId, L"Get\nUnique Id", IDC_BUTTON_GET_UNIQUE_ID);
	CreateButton(&m_Button_GetSetFiscalHeader, L"Get/Set\nTicket Hdr", IDC_BUTTON_GET_SET_FISCAL_HEADER);
	CreateButton(&m_Button_TicketHeader, L"Ticket Header", IDC_BUTTON_TICKETHEADER);
	CreateButton(&m_Button_CashierConsole, L"Cashier\nConsole", IDC_BUTTON_SELECT_CASHIER);
	CreateButton(&m_Button_TaxDepartments, L"Tax &\nDepartments", IDC_BUTTON_GET_DEPARTMENTS);
	CreateButton(&m_Button_MoneyCollection, L"MONEY\nCOLLECT", IDC_BUTTON_MATRAHSIZ);
	CreateButton(&m_Button_Taxless, L"Diplomatic Sale", IDC_BUTTON_TAXEXCEPTION_TAXLESS);
	CreateButton(&m_Button_Vat_Excluded, L"Diplomatic Sale\n(VAT Excluded)", IDC_BUTTON_TAXEXCEPTION_VAT_EXCLUDED);
	CreateButton(&m_Button_YemekCeki, L"YEMEK ÇEKÝ", IDC_BUTTON_YEMEKCEKI);
	CreateButton(&m_Button_Loyalty, L"LOYALTY", IDC_BUTTON_LOYALTY);
	CreateButton(&m_Button_CheckPairingStatus, L"Check Pairing\nStatus", IDC_BUTTON_CHECK_PAIRING_STATUS);

	CreateButton(&m_Button_TaxfreeSet, L"TAX FREE TICKET", IDC_BUTTON_TAXFREE_SET);
	CreateButton(&m_Button_TaxfreeSetTaxrefundAmount, L"Set TaxRefund", IDC_BUTTON_TAXFREE_SET_TAXREFUND_AMOUNT);
	CreateButton(&m_Button_VoidItem, L"Void Item", IDC_BUTTON_VOID_ITEM);
	CreateButton(&m_Button_PrintTotals, L"Print Totals", IDC_BUTTON_PRINT_TOTALS_AND_PAYMENTS);
	CreateButton(&m_Button_EKUConsole, L"EKU\nConsole", IDC_BUTTON_EKU_CONSOLE);
	CreateButton(&m_Button_FileSystemConsole, L"File System\nConsole", IDC_BUTTON_FILESYSTEM_CONSOLE);
	CreateButton(&m_Button_ExchangeTable, L"Exchange\nTable", IDC_BUTTON_CURRENCY);
	CreateButton(&m_Button_GetSetCurrencyProfile, L"Get/Set\nCurrencyProfile", IDC_BUTTON_CURRENCY2);
	CreateButton(&m_Button_VoidMatrahsiz, L"", IDC_BUTTON_VOID_MATRAHSIZ);
	CreateButton(&m_Button_IncreaseAmount, L"Increase\nAmount", IDC_BUTTON_TUTAR_ARTIRIM);
	CreateButton(&m_Button_PrintPreMF, L"Print Pre-MF", IDC_BUTTON_PRINT_BEFORE_MF);
	CreateButton(&m_Button_TransactionConsole, L"Transaction\nConsole", IDC_BUTTON_PERCENT_DEC2);
	CreateButton(&m_Button_KasaAvans, L"Kasa Avans", IDC_BUTTON_KASA_AVANS);
	CreateButton(&m_Button_IncreasePercent, L"Increase\n%", IDC_BUTTON_PERCENT_INC);
	CreateButton(&m_Button_PrintMF, L"Print MF", IDC_BUTTON_PRINT_MF);
	CreateButton(&m_Button_KasaPayment, L"Kasa Payment", IDC_BUTTON_KASA_ODEME);
	CreateButton(&m_Button_CariHesap, L"Cari Hesap", IDC_BUTTON_CARI_HESAP);
	CreateButton(&m_Button_DecreaseAmount, L"Decrease\nAmount", IDC_BUTTON_TUTAR_INDIR);
	CreateButton(&m_Button_CloseHandle, L"Close Handle", IDC_BUTTON_CLOSE);
	CreateButton(&m_Button_Condition, L"Condition", IDC_BUTTON_CONDITION);
	CreateButton(&m_Button_OptionFlags, L"Option Flags", IDC_BUTTON_OPTION_FLAGS);
	CreateButton(&m_Button_PaymentCash, L"Cash\nPayment", IDC_BUTTON_PAYMENT_CASH);
	CreateButton(&m_Button_DatabaseConsole, L"DB\nConsole", IDC_BUTTON_DATABASE_CONSOLE);
	CreateButton(&m_Button_UserMessage, L"User Message", IDC_BUTTON_PRETOTAL3);
	CreateButton(&m_Button_ReadCard, L"Read Card", IDC_BUTTON_READ_CARD);
	CreateButton(&m_Button_DecreasePercent, L"Decrease\n%", IDC_BUTTON_PERCENT_DEC);
	CreateButton(&m_Button_PluRead, L"PLU Read", IDC_BUTTON_GET_PLU);

	CreateButton(&m_Button_0, L"0"		, IDC_BUTTON_0, NULL, NULL);
	CreateButton(&m_Button_1, L"1"		, IDC_BUTTON_1, NULL, NULL);
	CreateButton(&m_Button_2, L"2"		, IDC_BUTTON_2, NULL, NULL);
	CreateButton(&m_Button_3, L"3"		, IDC_BUTTON_3, NULL, NULL);
	CreateButton(&m_Button_4, L"4"		, IDC_BUTTON_4, NULL, NULL);
	CreateButton(&m_Button_5, L"5"		, IDC_BUTTON_5, NULL, NULL);
	CreateButton(&m_Button_6, L"6"		, IDC_BUTTON_6, NULL, NULL);
	CreateButton(&m_Button_7, L"7"		, IDC_BUTTON_7, NULL, NULL);
	CreateButton(&m_Button_8, L"8"		, IDC_BUTTON_8, NULL, NULL);
	CreateButton(&m_Button_9, L"9"		, IDC_BUTTON_9, NULL, NULL);
	CreateButton(&m_Button_00, L"00"	, IDC_BUTTON_00, NULL, NULL);
	CreateButton(&m_Button_Point, L"."	, IDC_BUTTON_POINT, NULL, NULL);

	CreateButton(&m_Button_OtoparkEntryTicket, L"PARKING ENTRY", IDC_BUTTON_OTOPARK_ENTRY_TICKET);
	CreateButton(&m_Button_ReversePayments, L"REVERSE\nPAYMENTS", IDC_BUTTON_REVERSE_PAYMENTS);
	CreateButton(&m_Button_Multiply, L"X", IDC_BUTTON_MULTIPLY);
	CreateButton(&m_Button_Backspace, L"<--", IDC_BUTTON_DELETE);
	CreateButton(&m_Button_Subtotal, L"SUBTOTAL", IDC_BUTTON_PRETOTAL);
	CreateButton(&m_Button_Refund, L"REFUND TICKET", IDC_BUTTON_REFUND);
	CreateButton(&m_Button_Invoice, L"INVOICE SALE", IDC_BUTTON_INVOICE);
	CreateButton(&m_Button_PaymentList, L"VOID PAYMENTS", IDC_BUTTON_VOID_PAYMENT);
	CreateButton(&m_Button_PaymentDoAny, L"OTHER PAYMENTS", IDC_BUTTON_PAYMENT);
	CreateButton(&m_Button_PaymentDoCredit, L"CREDIT", IDC_BUTTON_CREDIT);
	CreateButton(&m_Button_PaymentDoCash, L"CASH", IDC_BUTTON_NAKIT);
	CreateButton(&m_Button_CloseTicket, L"CLOSE TICKET", IDC_BUTTON_CLOSE_TICKET);
	CreateButton(&m_Button_SetOnlineInvoice, L"SET ONLINE INVOICE", IDC_BUTTON_SET_ONLINE_INVOICE);
	CreateButton(&m_Button_SetExchangeProfile, L"SET EXCHANGE PROFILE", IDC_SET_EXCHANGE_PROFILE);

	CreateButton(&m_Button_TaxFreeInfo, L"ONLINE TAXFREE", IDC_BUTTON_TAXFREE_INFO);
	CreateButton(&m_ButtonDepartman1, L"---", IDC_BUTTON_DEPARTMAN_1);
	CreateButton(&m_ButtonDepartman2, L"---", IDC_BUTTON_DEPARTMAN_2);
	CreateButton(&m_ButtonDepartman3, L"---", IDC_BUTTON_DEPARTMAN_3);
	CreateButton(&m_ButtonDepartman4, L"---", IDC_BUTTON_DEPARTMAN_4);
	CreateButton(&m_ButtonDepartman5, L"---", IDC_BUTTON_DEPARTMAN_5);
	CreateButton(&m_ButtonDepartman6, L"---", IDC_BUTTON_DEPARTMAN_6);
	CreateButton(&m_ButtonDepartman7, L"---", IDC_BUTTON_DEPARTMAN_7);
	CreateButton(&m_ButtonDepartman8, L"---", IDC_BUTTON_DEPARTMAN_8);
	CreateButton(&m_ButtonDepartman9, L"---", IDC_BUTTON_DEPARTMAN_9);
	CreateButton(&m_ButtonDepartman10, L"---", IDC_BUTTON_DEPARTMAN_10);
	CreateButton(&m_ButtonDepartman11, L"---", IDC_BUTTON_DEPARTMAN_11);
	CreateButton(&m_ButtonDepartman12, L"---", IDC_BUTTON_DEPARTMAN_12);

	CreateButton(&m_Button_BatchCommand_Send			, L"Send\nOn Cable"	, IDC_BUTTON_BATCHCOMMAND_SEND);
	CreateButton(&m_Button_BatchCommand_ListenAndSend	, L"Listen & Send"	, IDC_BUTTON_BATCHCOMMAND_LISTENANDSEND);
	CreateButton(&m_Button_BatchCommand_ClearList		, L"Clear List"		, IDC_BUTTON_BATCHCOMMAND_CLEARLIST);

	CreateButton(&m_ButtonGetMEcrBGTrxList	 , L"Get Trx List", IDC_BUTTON_MECR_GET_BG_TRX_LIST);
	CreateButton(&m_ButtonGetMEcrBGTrxData	 , L"Get Trx Data", IDC_BUTTON_MECR_GET_BG_TRX_DATA);
	CreateButton(&m_ButtonSetMEcrBGTrxStatus, L"Set Trx Status", IDC_BUTTON_MECR_SET_BG_TRX_STATUS);
	CreateButton(&m_ButtonListenMEcr		 , L"Listen", IDC_BUTTON_MECR_LISTEN);

	CreateCheckBox(&m_CheckBox_Banking_Opt[0], L"MANUAL PAN ENTRY NOT ALLOWED", IDC_CHECKBOX_BANKING_OPT1);
	CreateCheckBox(&m_CheckBox_Banking_Opt[1], L"LOYALTY POINT NOT SUPPORTED", IDC_CHECKBOX_BANKING_OPT2);
	CreateCheckBox(&m_CheckBox_Banking_Opt[2], L"FORCED SALE", IDC_CHECKBOX_BANKING_OPT3);
	CreateCheckBox(&m_CheckBox_Banking_Opt[3], L"ASK FOR MISSING REFUND INPUTS", IDC_CHECKBOX_BANKING_OPT4);
	CreateCheckBox(&m_CheckBox_Banking_Opt[4], L"ALL INPUTS FROM ECR", IDC_CHECKBOX_BANKING_OPT5);
	CreateCheckBox(&m_CheckBox_Banking_Opt[5], L"DO NOT ASK FOR MISSING LOYALTY POINT", IDC_CHECKBOX_BANKING_OPT6);
	CreateCheckBox(&m_CheckBox_Banking_Opt[6], L"AUTHORISATION FOR INVOICE PAYMENT", IDC_CHECKBOX_BANKING_OPT7);
	CreateCheckBox(&m_CheckBox_Banking_Opt[7], L"SALE WITHOUT CAMPAIGN", IDC_CHECKBOX_BANKING_OPT8);

	m_TabCommandMode.Create(TCS_TABS | WS_CHILD | WS_VISIBLE | WS_TABSTOP | TCS_BUTTONS | WS_BORDER , CRect(0, 0, 1, 1), this, IDC_TAB_COMMAND_MODE);
	m_TabCommandMode.SetFont(buttonFont, true);
	m_TabCommandMode.InsertItem(TAB_SINGLE_COMMAND_MODE	, L"Single Cmd");
#ifdef DEVELOPMENT
	m_TabCommandMode.InsertItem(TAB_BATCH_COMMAND_MODE		, L"Batch Cmd");
	m_TabCommandMode.InsertItem(TAB_MASTERECR_MODE			, L"MasterECR");
#endif

	m_TabFunctionalControls.Create(TCS_TABS | WS_CHILD | WS_VISIBLE | WS_TABSTOP | TCS_BUTTONS | WS_BORDER , CRect(0, 0, 1, 1), this, IDC_TAB_FUCTIONALCONTROLS);
	m_TabFunctionalControls.SetFont(buttonFont, true);
	m_TabFunctionalControls.InsertItem(TAB_ECR		, L"ECR");
	m_TabFunctionalControls.InsertItem(TAB_ECR_EXT	, L"ECR Ext");
	m_TabFunctionalControls.InsertItem(TAB_FUNCTIONS	, L"Functions");
	m_TabFunctionalControls.InsertItem(TAB_BANKING	, L"Banking");
#ifdef DEVELOPMENT
	m_TabFunctionalControls.InsertItem(TAB_CONSOLES, L"Consoles");
	m_TabFunctionalControls.InsertItem(TAB_DEVELOPERS, L"Developer");
#endif

	m_listBatchCommand.InsertColumn(0, L"Line", 0);
	m_listBatchCommand.InsertColumn(1, L"Command", 0);
	m_listBatchCommand.InsertColumn(2, L"Result", 0);

	ShowWindow(SW_SHOWMAXIMIZED);

	OnSelchangeTabFunctionalControls(NULL, NULL);
	OnSelchangeTabCommandMode(NULL, NULL);
#define DLL_VERSION_MIN	"1703060800"

	memset(m_dllVersion, 0x00, sizeof(m_dllVersion));
	if (GMP_GetDllVersion(m_dllVersion) != TRAN_RESULT_OK)
	{
		MessageBox(CString("Uncompatible DLL Version.") + CString("\nDll Version Expected (minimum): ") + CString(DLL_VERSION_MIN) + CString("\nDll Version Found : ") + CString(m_dllVersion), L"Error", MB_OK);
		OnOK();
	}
	else if (memcmp(m_dllVersion, DLL_VERSION_MIN, strlen(DLL_VERSION_MIN)) < 0)
	{
		MessageBox(CString("Uncompatible DLL Version.") + CString("\nDll Version Expected (minimum): ") + CString(DLL_VERSION_MIN) + CString("\nDll Version Found : ") + CString(m_dllVersion), L"Error", MB_OK);
		OnOK();
	}

	CString caption;
	caption.Format(L"ePOS %S - DLL Vers %S", GMP_SIM_VERSION, m_dllVersion);  // Versiyon Check
	SetWindowTextW(caption);

	//GMP_SetCallbackFunction( CallbackFunctionSend );
	memset(&stHandleList, 0, sizeof(stHandleList));
	memset(&stTransactionData, 0, sizeof(stTransactionData));

	UpdateInterfaceWindow();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CePosDlg::UpdateInterfaceWindow(void)
{
#define MAX_NUMBER_OF_INTERFACES 16

	HINT hInt[MAX_NUMBER_OF_INTERFACES];

	uint32 numberOfInterfaces = FP3_GetInterfaceHandleList(hInt, MAX_NUMBER_OF_INTERFACES);

	for (unsigned int i = 0; i < numberOfInterfaces; i++)
	{
		char InterfaceId[256];
		memset(InterfaceId, 0x00, sizeof(InterfaceId));
		FP3_GetInterfaceID(hInt[i], InterfaceId, sizeof(InterfaceId) - 1);

		HTREEITEM hInterface = CTreeCtrlInsertf(&m_treeIterface, NULL, FALSE, InterfaceId);
		if (hInterface == NULL)
			continue;

		// This is interface buffer to keep interface related ECR data....
		DWORD_PTR ptr = (DWORD_PTR)malloc(sizeof(ST_INTERFACE_DATA));
		if (ptr)
		{
			memset((void*)ptr, 0x00, sizeof(ST_INTERFACE_DATA));
			((ST_INTERFACE_DATA*)ptr)->hInt = hInt[i];
			m_treeIterface.SetItemData(hInterface, ptr);
		}

		if (i == 0)
			m_treeIterface.Select(hInterface, TVGN_CARET);
	}
}

ST_INTERFACE_DATA* CePosDlg::GetInterfaceDataPointer(HINT hInt)
{
	HTREEITEM hInterface = m_treeIterface.GetRootItem();

	while (hInterface)
	{
		ST_INTERFACE_DATA* ptr = (ST_INTERFACE_DATA*)m_treeIterface.GetItemData(hInterface);

		if (ptr)
		{
			if (ptr->hInt == hInt)
				return ptr;
		}

		hInterface = m_treeIterface.GetNextItem(hInterface, TVGN_NEXT);
	}

	return NULL;
}

ST_TRANSACTION_DATA* CePosDlg::GetTransactionDataPointer(HINT hInt, HTRX hTrx)
{
	int retcode = APP_ERR_GMP3_INVALID_HANDLE;

	HTREEITEM hInterface = m_treeIterface.GetRootItem();

	while (hInterface)
	{
		ST_INTERFACE_DATA* int_ptr = (ST_INTERFACE_DATA*)m_treeIterface.GetItemData(hInterface);
		if (int_ptr)
		{
			if (int_ptr->hInt == hInt)
			{
				HTREEITEM hTransaction = m_treeIterface.GetNextItem(hInterface, TVGN_CHILD);
				while (hTransaction)
				{
					ST_TRANSACTION_DATA* ptr = (ST_TRANSACTION_DATA*)m_treeIterface.GetItemData(hTransaction);
					if (ptr)
					{
						if (ptr->hTrx == hTrx)
							return ptr;
					}
					hTransaction = m_treeIterface.GetNextItem(hTransaction, TVGN_NEXT);
				}
			}
		}
		hInterface = m_treeIterface.GetNextItem(hInterface, TVGN_NEXT);
	}

	return NULL;
}

HTREEITEM CePosDlg::CTreeCtrlInsertf(CTreeCtrl* pTree, HTREEITEM hParent, bool isBackgroundTrx, char * buffer, ...)
{
	va_list 		args;
	char tmp[512];
	CString cs;
	HTREEITEM hItem;

	va_start(args, buffer);
	vsprintf(tmp, buffer, args);
	va_end(args);
	cs = tmp;

	hItem = pTree->InsertItem(TVIF_TEXT
							  , cs
							  , 0
							  , 0
							  , 0
							  , 0
							  , 0
							  , hParent
							  , NULL);

	if (hItem != NULL)
	{
		pTree->Expand(hParent, TVE_EXPAND);

		if (hParent)
		{
			if (isBackgroundTrx)
				// BackgroundTrx icon
				pTree->SetItemImage(hItem, 2, 2);
			else
				// frontscreen Trx icon
				pTree->SetItemImage(hItem, 1, 1);

			pTree->SelectItem(hItem);
		}
		else
			// interface icon
			pTree->SetItemImage(hItem, 0, 0);
	}

	return hItem;
}

void CePosDlg::CreateButton(CButton* pbutton, LPCTSTR caption, UINT id, UINT color, UINT bitmap)
{
	pbutton->Create(caption, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON | BS_MULTILINE | BS_BITMAP | BS_CENTER | BS_VCENTER    , CRect(0, 0, 1, 1), this, id);

	switch (id)
	{
	case IDC_BUTTON_0:
	case IDC_BUTTON_1:
	case IDC_BUTTON_2:
	case IDC_BUTTON_3:
	case IDC_BUTTON_4:
	case IDC_BUTTON_5:
	case IDC_BUTTON_6:
	case IDC_BUTTON_7:
	case IDC_BUTTON_8:
	case IDC_BUTTON_9:
	case IDC_BUTTON_00:
	case IDC_BUTTON_POINT:
		pbutton->SetFont(buttonFontBig, true);
		break;
	default:
		pbutton->SetFont(buttonFont, true);
		break;
	}

	if (bitmap)
	{
		CBitmap bmp;
		bmp.LoadMappedBitmap(bitmap);
		pbutton->SetBitmap(bmp);
	}

}

void CePosDlg::CreateCheckBox(CButton* pButton, LPCTSTR Caption, UINT id, UINT color, UINT bitmap)
{
	pButton->Create(Caption, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON | BS_BITMAP | BS_VCENTER | BS_CHECKBOX, CRect(0, 0, 1, 1), this, id);

	pButton->SetFont(buttonFont, true);
}

void CePosDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CePosDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CePosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CePosDlg::DestroyWindow()
{
	//yunus
	//if(gmp3Library)
	//	FreeLibrary(gmp3Library);

	return CDialogEx::DestroyWindow();
}

void CePosDlg::DepartmentSale(int deptIndex)
{
	int retcode;
	char name[32+1] = "";
	char barcode[32+1] = "";
	ST_ITEM stItem;

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	uint16 currency = 0;
	uint32 amount = 0;
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);

	uint8 unitType = 0;
	uint32 itemCount = 0;
	uint8  itemCountPrecition = 0;
	GetTypedItemCount(&itemCount, &itemCountPrecition);
	if (itemCount == 0)
		itemCount = 1;

	memset(&stItem, 0x00, sizeof(stItem));
	stItem.type				= ITEM_TYPE_DEPARTMENT;
	stItem.subType			= 0;
	stItem.deptIndex		= deptIndex - 1;
	stItem.amount			= amount;
	stItem.currency			= currency;
	stItem.count			= itemCount;
	stItem.unitType			= unitType;
	stItem.pluPriceIndex	= 0;
	stItem.countPrecition	= itemCountPrecition;

	//if( deptIndex == 11 )
	//{
	//	// Department-11 is configured as INCREASE department for demostration of Increases...
	//	stItem.promotion.type	= ITEM_PROMOTION_INCREASE;
	//
	//	// default increase is %50 of one item price
	//	stItem.promotion.amount = amount /2;
	//	GetIntegerInput( L"INCREASE Amount", (int*)&stItem.promotion.amount );
	//
	//	sprintf( stItem.promotion.ticketMsg, "KAMPANYA ÝPTALÝ" );
	//	GetStringInput ( L"INCREASE Msg", stItem.promotion.ticketMsg );
	//}
	//else if( deptIndex == 12 )
	//{
	//	// Department-12 is configured as DISCOUNT department for demostration of Discounts...
	//	stItem.promotion.type	= ITEM_PROMOTION_DISCOUNT;
	//
	//	// default discount is %50 off of one item price
	//	stItem.promotion.amount = (amount /2);
	//	GetIntegerInput( L"DISCOUNT Amount (with decimals)", (int*)&stItem.promotion.amount );
	//
	//	sprintf( stItem.promotion.ticketMsg, "KAMPANYA ÝNDÝRÝMÝ" );
	//	GetStringInput ( L"DISCOUNT Msg", stItem.promotion.ticketMsg );
	//}

	/*if(m_TaxExceptional_Taxless)
		stItem.flag			|= ITEM_OPTION_TAX_EXCEPTION_TAXLESS;
	m_TaxExceptional_Taxless = false;*/

	if (m_TaxExceptional_Taxless)
		stItem.flag			|= ITEM_TAX_EXCEPTION_VAT_INCLUDED_TO_PRICE;
	m_TaxExceptional_Taxless = false;

	if (m_TaxExceptional_Vat_Excluded)
		stItem.flag			|= ITEM_TAX_EXCEPTION_VAT_NOT_INCLUDED_TO_PRICE;
	m_TaxExceptional_Vat_Excluded = false;

	strcpy(stItem.name, name);
	strcpy(stItem.barcode, barcode);

	if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
	{
		if (hTrx == NULL)
		{
			retcode = StartTicket(hInt, &hTrx, TProcessSale);
			if (retcode != TRAN_RESULT_OK)
			{
				HandleErrorCode(retcode);
				return;
			}
		}

		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		retcode = FP3_ItemSale(hInt, hTrx, &stItem, pstTicket);
		if (retcode != TRAN_RESULT_OK)
		{
			HandleErrorCode(retcode);
			return;
		}

		DisplayTransaction(pstTicket, false);
		DisplayItem(pstTicket, pstTicket->totalNumberOfItems - 1);
	}
	else
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		bufferLen = prepare_ItemSale(&buffer[0], sizeof(buffer), &stItem);
		AddIntoCommandBatch(L"prepare_ItemSale", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
}

void CePosDlg::OnBnClickedButtonDepartman1()
{
	DepartmentSale(1);
}
void CePosDlg::OnBnClickedButtonDepartman2()
{
	DepartmentSale(2);
}
void CePosDlg::OnBnClickedButtonDepartman3()
{
	DepartmentSale(3);
}
void CePosDlg::OnBnClickedButtonDepartman4()
{
	DepartmentSale(4);
}
void CePosDlg::OnBnClickedButtonDepartman5()
{
	DepartmentSale(5);
}
void CePosDlg::OnBnClickedButtonDepartman6()
{
	DepartmentSale(6);
}
void CePosDlg::OnBnClickedButtonDepartman7()
{
	DepartmentSale(7);
}
void CePosDlg::OnBnClickedButtonDepartman8()
{
	DepartmentSale(8);
}
void CePosDlg::OnBnClickedButtonDepartman9()
{
	DepartmentSale(9);
}
void CePosDlg::OnBnClickedButtonDepartman10()
{
	DepartmentSale(10);
}
void CePosDlg::OnBnClickedButtonDepartman11()
{
	DepartmentSale(11);
}
void CePosDlg::OnBnClickedButtonDepartman12()
{
	DepartmentSale(12);
}

void CePosDlg::CheckBox(int item)
{
	m_CheckBox_Banking_Opt[item].SetCheck(!m_CheckBox_Banking_Opt[item].GetCheck());
}

void CePosDlg::OnBnClickedCheckBox1()
{
	CheckBox(0);
}
void CePosDlg::OnBnClickedCheckBox2()
{
	CheckBox(1);
}
void CePosDlg::OnBnClickedCheckBox3()
{
	CheckBox(2);
}
void CePosDlg::OnBnClickedCheckBox4()
{
	CheckBox(3);
}
void CePosDlg::OnBnClickedCheckBox5()
{
	CheckBox(4);
}
void CePosDlg::OnBnClickedCheckBox6()
{
	CheckBox(5);
}
void CePosDlg::OnBnClickedCheckBox7()
{
	CheckBox(6);
}
void CePosDlg::OnBnClickedCheckBox8()
{
	CheckBox(7);
}

void CePosDlg::OnBnClickedButtonPair()
{
	ST_GMP_PAIR GMPPair;
	char pFileName[64] = "GMP.INI";
	int retcode = NULL;
	HINT hInt = GetSelectedInterface();

	memset(&GMPPair, 0x00, sizeof(GMPPair));

	// Önce ECHO ile cihaz ile olan baðlantýyý test et
	retcode = Echo();
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	CTime &Time = CTime::GetCurrentTime();

	// Init Yapýlabilir
	strcpy(GMPPair.szProcOrderNumber, "00001");
	sprintf(GMPPair.szProcDate, "%02d%02d%02d", Time.GetDay(), Time.GetMonth(), Time.GetYear() % 100);
	sprintf(GMPPair.szProcTime, "%02d%02d%02d", Time.GetHour(), Time.GetMinute(), Time.GetSecond());
	strcpy(GMPPair.szExternalDeviceBrand, "FirmBrand");
	strcpy(GMPPair.szExternalDeviceModel, "FirmModel");
	strcpy(GMPPair.szExternalDeviceSerialNumber, "0123456789");
	strcpy(GMPPair.szEcrSerialNumber, "9876543210");

	retcode = FP3_GMP_StartPairingInit(hInt, &GMPPair, &m_GMPPairResp);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	// This will updateEcho status on window
	retcode = Echo();
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	retcode = ReadDepartmentsAndTaxRatesFromECR(hInt);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;
	DisplayDepartmentsAndTaxRates(hInt);

	retcode = ReadCurrencyFromECR(hInt);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;
	DisplayCurrency(hInt);

	retcode = ReadOpenTransactionHandleListFromECR(hInt);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	// This is the handle of the active (front screen) transaction in ECR. If it exists, it must be Reloaded and processed.
	HTRX hTrx = CTreeCtrlFindFrontScreenHandle(hInt);
	if (hTrx == NULL)
		// No FrontScreen Transaction, no need to reload...
		goto Exit;

	// Find the active (FrontScreen Trx) in Interface TreeCtrl and select it
	CTreeCtrlFindTransactionHandle(hInt, hTrx, TRUE);

	retcode = ReadTransactionFromECR(hInt, hTrx);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	// Display the details of Trx
	DisplayTransaction(hInt, hTrx, FALSE);

Exit:
	HandleErrorCode(retcode);
}

int CePosDlg::ReadOpenTransactionHandleListFromECR(HINT hInt)
{
	int retcode = TRAN_RESULT_OK;

	ST_HANDLE_LIST stHandleList[64];
	uint16 totalNumberOfHandles = 0;
	uint16 totalNumberOfHandlesInThis = 0;
	uint16 totalNumberOfHandlesReaded = 0;
	bool isBackgroundTrx = FALSE;

	// Remove all Trx records from the Tree View
	CTreeCtrlRemoveTransactionHandle(hInt, 0xFFFFFFFF);

	do
	{
		totalNumberOfHandlesInThis = 0;
		memset(stHandleList, 0x00, sizeof(stHandleList));

		retcode = FP3_FunctionGetHandleList(hInt, stHandleList, TRAN_STATUS_FREE, totalNumberOfHandlesReaded, sizeof(stHandleList) / sizeof(ST_HANDLE_LIST), &totalNumberOfHandles, &totalNumberOfHandlesInThis, TIMEOUT_DEFAULT);
		if (retcode != TRAN_RESULT_OK)
			goto Exit;

		for (int m = 0; m < totalNumberOfHandlesInThis; m++)
		{
			if (stHandleList[m].Handle)
				CTreeCtrlInsertTransactionHandle((HTRX)stHandleList[m].Handle, isBackgroundTrx);

			// only the first handle in the structure is the FrontHandle. The rest must be background handle
			isBackgroundTrx = TRUE;
		}

		totalNumberOfHandlesReaded += totalNumberOfHandlesInThis;
	}
	while (totalNumberOfHandlesReaded < totalNumberOfHandles);

Exit:
	return retcode;
}

void CePosDlg::AddIntoCommandBatch(CString commandName, uint32 commandType, uint8* buffer, uint16 bufferLen)
{
	// get memory for CommandType + data + 2 bytes length
	uint8* dataPtr = (uint8*)malloc(bufferLen + 6);

	memcpy((uint8*)&dataPtr[0], &commandType	, 4);
	memcpy((uint8*)&dataPtr[4], &bufferLen		, 2);
	memcpy((uint8*)&dataPtr[6], buffer			, bufferLen);

	int index = m_listBatchCommand.InsertItem(LVIF_TEXT | LVIF_STATE, m_listBatchCommand.GetItemCount(), NULL, 0, LVIS_SELECTED, 0, 0);

	CString csLine;
	csLine.Format(L"%d", index + 1);
	m_listBatchCommand.SetItemText(index, 0, csLine);
	m_listBatchCommand.SetItemText(index, 1, commandName);
#ifdef _WIN64
	m_listBatchCommand.SetItemData(index, (DWORD)((unsigned long long)dataPtr));
#else /*_WIN64*/
	m_listBatchCommand.SetItemData(index, (DWORD)dataPtr);
#endif /*_WIN64*/
}

void CePosDlg::DisplayInfo(char * buffer, ...)
{
	va_list 		args;
	char tmp[512];
	CString cs;

	va_start(args, buffer);
	vsprintf(tmp, buffer, args);
	va_end(args);
	cs = tmp;

	m_ListControlMainDisplay.SetWindowTextW(cs);
}

void CePosDlg::CListBoxPrintf(CListBox* pList, char * buffer, ...)
{
	va_list 		args;
	char tmp[512];
	CString cs;

	va_start(args, buffer);
	vsprintf(tmp, buffer, args);
	va_end(args);
	cs = tmp;

	pList->AddString(cs);
}

void CePosDlg::PrintInfo(CListBox* plistBox, uint32 flag, char * buffer)
{
	char tmp[512];
	CString cs;
	int iFontSize = 38;		// default

	if (flag & GMP3_PS_24)
		iFontSize = 24;
	else if (flag & GMP3_PS_12)
		iFontSize = 12;
	else if (flag & GMP3_PS_16)
		iFontSize = 16;
	else if (flag & GMP3_PS_48)
		iFontSize = 48;
	else if (flag & GMP3_PS_32)
		iFontSize = 32;
	else if (flag & GMP3_PS_38)
		iFontSize = 38;

	int numberOfBytesDirectlyCopy	= ((int)strlen(buffer) / iFontSize) * iFontSize;
	int numberOfBytesToProcess		= ((int)strlen(buffer) % iFontSize);

	memset(tmp, 0, sizeof(tmp));
	memcpy(tmp, buffer, numberOfBytesDirectlyCopy);

	if ((flag & GMP3_PS_CENTER) && numberOfBytesToProcess)
	{
		int numberOfSpaces = iFontSize - numberOfBytesToProcess;

		memset(&tmp[numberOfBytesDirectlyCopy], ' ', iFontSize);
		memcpy(&tmp[numberOfBytesDirectlyCopy+(numberOfSpaces/2)], &buffer[numberOfBytesDirectlyCopy], numberOfBytesToProcess);
	}
	else if ((flag & GMP3_PS_RIGHT) && numberOfBytesToProcess)
	{
		int numberOfSpaces = iFontSize - numberOfBytesToProcess;

		memset(&tmp[numberOfBytesDirectlyCopy], ' ', iFontSize);
		memcpy(&tmp[numberOfBytesDirectlyCopy+numberOfSpaces], &buffer[numberOfBytesDirectlyCopy], numberOfBytesToProcess);
	}
	else
		memcpy(&tmp[numberOfBytesDirectlyCopy], &buffer[numberOfBytesDirectlyCopy], numberOfBytesToProcess);

	cs = CString(tmp);
	plistBox->AddString(cs);
}

void CePosDlg::StatusInfo(char * buffer, ...)
{
	va_list 		args;
	char tmp[512];
	CString cs;

	va_start(args, buffer);
	vsprintf(tmp, buffer, args);
	va_end(args);
	cs = tmp;

	m_listStatus.AddString(cs);
}

void CePosDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}

void CePosDlg::DisplayErrorMessage(int errorCode)
{
	char ErrorString[128];
	GetErrorMessage(errorCode, ErrorString);
	DisplayInfo(ErrorString);
}

void CePosDlg::HandleErrorCode(int errorCode)
{
	HTRX hTrx = NULL;
	DisplayErrorMessage(errorCode);
}

int CePosDlg::StartTicket(HINT hInt, HTRX* phTrx, TTicketType ticketType)
{
	int retcode = TRAN_RESULT_OK;
	uint8  buffer[1024*2];
	uint16 bufferLen = 0;
	ST_MULTIPLE_RETURN_CODE stMultipleReturnCode[10];
	uint16 numberOfMultipleReturnCode;

	for (int i = 0; i < (sizeof(stMultipleReturnCode) / sizeof(ST_MULTIPLE_RETURN_CODE)); ++i)
	{
		memset(&stMultipleReturnCode[i], 0x00, sizeof(ST_MULTIPLE_RETURN_CODE));
		stMultipleReturnCode[i].StructSize = sizeof(ST_MULTIPLE_RETURN_CODE);
	}

	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);

	if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
	{
		if (*phTrx == NULL)
		{
			m_listPrinterOutput.ResetContent();

			if (ticketType != TProcessSale)
				memset(ptr->m_uniqueId, 0xFF, sizeof(ptr->m_uniqueId));

			bufferLen = 0;
			bufferLen += prepare_Start(&buffer[bufferLen], sizeof(buffer) - bufferLen, ptr->m_uniqueId, sizeof(ptr->m_uniqueId), NULL, 0, NULL, 0);
			bufferLen += prepare_TicketHeader(&buffer[bufferLen], sizeof(buffer) - bufferLen, ticketType);
			bufferLen += prepare_OptionFlags(&buffer[bufferLen], sizeof(buffer) - bufferLen, RESPONSE_FLAGS, 0);

			retcode = FP3_MultipleCommand(hInt, phTrx, &stMultipleReturnCode[0], &numberOfMultipleReturnCode, buffer, bufferLen, NULL, 10000);
			if (retcode == TRAN_RESULT_OK)
			{
				for (int t = 0; t < numberOfMultipleReturnCode; t++)
				{
					retcode = stMultipleReturnCode[t].retcode;
					switch (t)
					{
					case 0: // prepare_Start
						if (retcode == APP_ERR_ALREADY_DONE)
						{
							MessageBox(L"There is an ACTIVE FRONT-SCREEN Transaction in ECR and You can not start simultanious multiple FRONT-SCREEN Transactions on a single interface!\n\nActive FRONT SCREEN Transaction Handle in ECR will be Inserted & Selected on interface window.", L"Active Transaction Found", MB_OK);
							if (CTreeCtrlFindTransactionHandle(hInt, *phTrx, TRUE) == FALSE)
								CTreeCtrlInsertTransactionHandle(*phTrx, FALSE);
						}
						else if (retcode == TRAN_RESULT_OK)
							CTreeCtrlInsertTransactionHandle(*phTrx, FALSE);

						break;

					case 1: // prepare_TicketHeader
						if (stMultipleReturnCode[t].retcode == APP_ERR_ALREADY_DONE)
						{
							MessageBox(L"There is an ACTIVE FRONT-SCREEN Transaction in ECR and You can not start simultanious multiple FRONT-SCREEN Transactions on a single interface!\n\nActive FRONT SCREEN Transaction Handle in ECR will be Inserted & Selected on interface window.", L"Active Transaction Found", MB_OK);
							if (CTreeCtrlFindTransactionHandle(hInt, *phTrx, TRUE) == FALSE)
								CTreeCtrlInsertTransactionHandle(*phTrx, FALSE);
						}

						break;

					case 2: // prepare_OptionFlags
						break;
					}
				}
			}
		}

		if (retcode != 0)
			HandleErrorCode(retcode);
	}
	else
	{
		if (ticketType != TProcessSale)
			memset(ptr->m_uniqueId, 0xFF, sizeof(ptr->m_uniqueId));

		bufferLen = prepare_Start(&buffer[0], sizeof(buffer), ptr->m_uniqueId, sizeof(ptr->m_uniqueId), NULL, 0, NULL, 0);
		AddIntoCommandBatch(L"_prepare_Start", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

		bufferLen = prepare_TicketHeader(&buffer[0], sizeof(buffer), ticketType);
		AddIntoCommandBatch(L"_prepare_TicketHeader", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

		bufferLen = prepare_OptionFlags(&buffer[0], sizeof(buffer), RESPONSE_FLAGS, 0);
		AddIntoCommandBatch(L"_prepare_OptionFlags", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}

	return retcode;
}


void CePosDlg::OnBnClickedButtonTicketheader()
{
	int retcode = TRAN_RESULT_OK;
	CGetInputDlg* pcInput;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"TProcessSale"	, TProcessSale	, true);
	pcInput->InsertFlag(L"TInvoice"		, TInvoice		, false);
	pcInput->InsertFlag(L"TRefund"			, TRefund		, false);
	pcInput->InsertFlag(L"TInfo"			, TInfo			, false);
	pcInput->InsertFlag(L"TAvans"			, TAvans		, false);
	pcInput->InsertFlag(L"TPayment"		, TPayment		, false);
	if (pcInput->DoModal(L"TICKET HEADER TYPE ?", L"", 4) != IDOK)
		return;
	TTicketType ticketType = (TTicketType)pcInput->m_flagValue;
	delete pcInput;

	if (m_TabCommandMode.GetCurSel() ==  TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		bufferLen = prepare_TicketHeader(&buffer[0], sizeof(buffer), ticketType);
		AddIntoCommandBatch(L"_prepare_TicketHeader", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

		//		bufferLen = _prepare_OptionFlags( &buffer[0], sizeof(buffer), RESPONSE_FLAGS, 0 );
		//		AddIntoCommandBatch( L"_prepare_OptionFlags", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen );
	}
	else
	{
		retcode = FP3_TicketHeader(GetSelectedInterface(), GetSelectedTransaction(), ticketType);
		HandleErrorCode(retcode);
	}
}

uint32 CePosDlg::getAmount(CString m_csInput)
{
	uint32 amount;
	CString inputWithoutDot;
	int DotLocation;
	int precition = 0;

	DotLocation = m_csInput.Find('.');
	if (DotLocation < 0)
		// No '.'
		inputWithoutDot = m_csInput;
	else
	{
		precition = m_csInput.GetLength() - DotLocation - 1;
		inputWithoutDot = m_csInput.Left(DotLocation) + m_csInput.Right(precition);
	}

	amount = atol(CT2A((LPCTSTR)inputWithoutDot));
	while (precition < 2)
	{
		amount *= 10;
		precition++;
	}

	return amount;
}

char* CePosDlg::formatCount(uint32 itemCount, byte ItemCountPrecision, uint16 itemUnitType)
{
	static byte index = 0;
	static char cs[48][48];
	char tmpFormat[48];

	index = (index + 1) % 48;

	memset(cs[index], 0x00, sizeof(cs[index]));
	memset(tmpFormat, 0x00, sizeof(tmpFormat));

	sprintf(tmpFormat, "%%ld.%%0%dd", ItemCountPrecision);
	sprintf(cs[index], tmpFormat
			, itemCount / (long)pow((double)10, ItemCountPrecision)
			, itemCount % (long)pow((double)10, ItemCountPrecision)
		   );

	switch (itemUnitType)
	{
	case ITEM_NONE:
		break;
	case ITEM_NUMBER:
		strcat(cs[index], " Adt");
		break;
	case ITEM_KILOGRAM:
		strcat(cs[index], " Kg");
		break;
	case ITEM_GRAM:
		strcat(cs[index], " gr");
		break;
	case ITEM_LITRE:
		strcat(cs[index], " lt");
		break;
	}

	return cs[index];
}

char* CePosDlg::formatAmount(uint32 amount, uint16 currency)
{
	static byte index = 0;
	static char cs[48][48];

	index = (index + 1) % 48;

	memset(cs[index], 0x00, sizeof(cs[index]));

	sprintf(cs[index], "%ld.%02d"	, amount / 100
			, amount % 100
		   );

	switch (currency)
	{
	case CURRENCY_NONE:
		break;
	case CURRENCY_DOLAR:
		strcat(cs[index], "$");
		break;
	case CURRENCY_EU:
		strcat(cs[index], "€");
		break;
	case CURRENCY_TL:
		strcat(cs[index], "TL");
		break;
	default:
		strcat(cs[index], "?");
		break;
	}

	return cs[index];
}

int CePosDlg::GetPayment(ST_PAYMENT_REQUEST stPaymentRequest[], int numberOfPayments)
{
	int retcode;
	char display[256];
	memset(display, 0x00, sizeof(display));

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_Payment(&buffer[0], sizeof(buffer), &stPaymentRequest[0]);
		AddIntoCommandBatch(L"_prepare_Payment", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
		return TRAN_RESULT_OK;
	}
	else
	{
		HTRX hTrx = GetSelectedTransaction();
		HINT hInt = GetSelectedInterface();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		if (hTrx != 0)
		{
			retcode = FP3_Payment(hInt, hTrx, &stPaymentRequest[0], pstTicket);
			uint32 TicketAmount = pstTicket->TotalReceiptAmount + pstTicket->KatkiPayiAmount;

			switch (retcode)
			{
			case TRAN_RESULT_OK:

				if (pstTicket->KasaAvansAmount)
				{
					sprintf(display, "KASA AVANS TOTAL: %s", formatAmount(pstTicket->KasaAvansAmount, CURRENCY_TL));
					TicketAmount = pstTicket->KasaAvansAmount;
				}
				else if (pstTicket->invoiceAmount)
				{
					sprintf(display, "INVOICE TOTAL : %s", formatAmount(pstTicket->invoiceAmount, CURRENCY_TL));
					TicketAmount = pstTicket->invoiceAmount;
				}
				else
				{
					if ((TTicketType)pstTicket->ticketType == TCariHesap)
						sprintf(display, "TOTAL : %s", formatAmount(pstTicket->stPayment[0].payAmount, CURRENCY_TL));
					else
						sprintf(display, "TOTAL : %s", formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL));
				}

				if (pstTicket->CashBackAmount)
					sprintf(&display[strlen(display)], "\r\nCASHBACK : %s", formatAmount(pstTicket->CashBackAmount, CURRENCY_TL));
				else
				{
					if ((TTicketType)pstTicket->ticketType == TCariHesap)
						sprintf(&display[strlen(display)], "\r\nREMAIN : %s", formatAmount(pstTicket->KasaPaymentAmount, CURRENCY_TL));
					else
						sprintf(&display[strlen(display)], "\r\nREMAIN : %s" , formatAmount(pstTicket->KasaPaymentAmount != 0 ? pstTicket->KasaPaymentAmount - pstTicket->stPayment[0].payAmount : TicketAmount - pstTicket->TotalReceiptPayment, CURRENCY_TL));
				}

				if ((stPaymentRequest[0].typeOfPayment == PAYMENT_BANK_CARD) || (stPaymentRequest[0].typeOfPayment == PAYMENT_MOBILE))
				{
					sprintf(&display[strlen(display)], "\r\n%s"				, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.bankName);
					sprintf(&display[strlen(display)], "\r\nONAY KODU : %6.6s" , pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.authorizeCode);
					sprintf(&display[strlen(display)], "\r\n%s"				, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stCard.pan);
				}

				if (pstTicket->TotalReceiptPayment >= TicketAmount)
				{
					retcode = FP3_PrintTotalsAndPayments(hInt, hTrx);
					if (retcode !=  TRAN_RESULT_OK)
						break;

					retcode = FP3_PrintBeforeMF(hInt, hTrx);
					if (retcode !=  TRAN_RESULT_OK)
						break;

					ST_USER_MESSAGE stUserMessage[3];
					memset(&stUserMessage, 0x00, sizeof(stUserMessage));

					stUserMessage[0].StructSize = 0;
					stUserMessage[0].flag = GMP3_PS_38 | GMP3_PS_CENTER;
					strcpy((char*)stUserMessage[0].message, "Teþekkür Ederiz");
					stUserMessage[0].len = (uint8)strlen((char*)stUserMessage[0].message);

					stUserMessage[1].StructSize = 0;
					stUserMessage[1].flag = GMP3_PS_GRAPHIC | GMP3_PS_CENTER;
					strcpy((char*)stUserMessage[1].message, "/Bitmap/INGE.bmp");
					stUserMessage[1].len = (uint8)strlen((char*)stUserMessage[1].message);

					stUserMessage[2].StructSize = 0;
					stUserMessage[2].flag = GMP3_PS_38;
					strcpy((char*)stUserMessage[2].message, "\n");
					stUserMessage[2].len = (uint8)strlen((char*)stUserMessage[2].message);

					FP3_PrintUserMessage(hInt, hTrx, stUserMessage, 3,  pstTicket);
					//retcode = FP3_PrintUserMessage( hInt, hTrx, stUserMessage, 3,  pstTicket);
					//if( retcode != TRAN_RESULT_OK )
					//	break;

					retcode = FP3_PrintMF(hInt, hTrx);
					if (retcode !=  TRAN_RESULT_OK)
						break;

					DisplayTransaction(pstTicket, false);

					retcode = TransactionHandle_CloseAndRemove(hInt, hTrx);
				}
				else
					DisplayTransaction(pstTicket, false);
				break;

			case APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_NO_MORE_ERROR_CODE:
				DisplayTransaction(pstTicket, false);
				break;

			case APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_MORE_ERROR_CODE:
				DisplayTransaction(pstTicket, false);

				if ((stPaymentRequest[0].typeOfPayment == PAYMENT_BANK_CARD) || (stPaymentRequest[0].typeOfPayment == PAYMENT_MOBILE))
				{
					sprintf(&display[strlen(display)], "\r\n%s(%s)"	, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stPaymentErrMessage.ErrorMsg
							, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stPaymentErrMessage.ErrorCode
						   );
					sprintf(&display[strlen(display)], "\r\n%s(%s)"	, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stPaymentErrMessage.AppErrorMsg
							, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stPaymentErrMessage.AppErrorCode
						   );
				}

				break;

			default:
				break;
			}

			if (strlen(display))
				DisplayInfo(display);

			if (retcode != TRAN_RESULT_OK)
				HandleErrorCode(retcode);
		}
	}

	m_csInput.Empty();
	m_comboBoxCurrency.SetCurSel(0);
	m_csTtemCount.Empty();

	return retcode;
}

int CePosDlg::ReversePayment(ST_PAYMENT_REQUEST* pstPaymentRequest)
{
	int retcode;
	char display[256];
	uint32 TicketAmount;
	uint32 PaymentAmount;

	memset(display, 0x00, sizeof(display));

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_ReversePayment(&buffer[0], sizeof(buffer), pstPaymentRequest, 1);
		AddIntoCommandBatch(L"_prepare_ReversePayment", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
		return TRAN_RESULT_OK;
	}
	else
	{
		HTRX hTrx = GetSelectedTransaction();
		HINT hInt = GetSelectedInterface();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		retcode = FP3_ReversePayment(hInt, hTrx, pstPaymentRequest, 1, pstTicket);

		switch (retcode)
		{
		case TRAN_RESULT_OK:
			TicketAmount = pstTicket->TotalReceiptAmount;
			PaymentAmount = pstTicket->TotalReceiptPayment;

			switch (pstTicket->ticketType)
			{
			case TPayment:
				sprintf(display, "KASA PAYMENT TOTAL: %s", formatAmount(pstTicket->KasaPaymentAmount, CURRENCY_TL));
				TicketAmount = pstTicket->KasaPaymentAmount;
				PaymentAmount = pstTicket->TotalReceiptReversedPayment;
				break;
			case TRefund:
				sprintf(display, "REFUND TOTAL : %s", formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL));
				TicketAmount = pstTicket->TotalReceiptAmount;
				PaymentAmount = pstTicket->TotalReceiptReversedPayment;
				break;
			case TCariHesap:
				sprintf(display, "TOTAL : %s", formatAmount(pstTicket->stPayment[0].payAmount, CURRENCY_TL));
				break;
			default:
				sprintf(display, "TOTAL : %s", formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL));
				TicketAmount = pstTicket->TotalReceiptAmount;
				break;
			}

			if ((TTicketType)pstTicket->ticketType == TCariHesap)
				sprintf(&display[strlen(display)], "\r\nREMAIN : %s" , formatAmount(pstTicket->KasaPaymentAmount, CURRENCY_TL));
			else
				sprintf(&display[strlen(display)], "\r\nREMAIN : %s" , formatAmount(TicketAmount - PaymentAmount, CURRENCY_TL));

			if ((pstPaymentRequest->typeOfPayment == REVERSE_PAYMENT_BANK_CARD_VOID) || (pstPaymentRequest->typeOfPayment == REVERSE_PAYMENT_BANK_CARD_REFUND) || (pstPaymentRequest->typeOfPayment == REVERSE_PAYMENT_MOBILE))
			{
				sprintf(&display[strlen(display)], "\r\n%s"				, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.bankName);
				sprintf(&display[strlen(display)], "\r\nONAY KODU : %6.6s" , pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.authorizeCode);
				sprintf(&display[strlen(display)], "\r\n%s"				, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stCard.pan);
			}

			if (PaymentAmount >= TicketAmount)
			{
				retcode = FP3_PrintTotalsAndPayments(hInt, hTrx);
				if (retcode !=  TRAN_RESULT_OK)
					break;

				retcode = FP3_PrintBeforeMF(hInt, hTrx);
				if (retcode !=  TRAN_RESULT_OK)
					break;

				ST_USER_MESSAGE stUserMessage[2];
				memset(&stUserMessage, 0x00, sizeof(stUserMessage));
				stUserMessage[0].flag = GMP3_PS_38 | GMP3_PS_CENTER;
				strcpy((char*)stUserMessage[0].message, "Ýadeniz Gerçekleþti");
				stUserMessage[0].len = (uint8)strlen((char*)stUserMessage[0].message);

				retcode = FP3_PrintUserMessage(hInt, hTrx, stUserMessage, 1,  pstTicket);
				if (retcode !=  TRAN_RESULT_OK)
					break;

				retcode = FP3_PrintMF(hInt, hTrx);
				if (retcode !=  TRAN_RESULT_OK)
					break;

				retcode = TransactionHandle_CloseAndRemove(hInt, hTrx);
				if (retcode !=  TRAN_RESULT_OK)
					break;
			}

			DisplayTransaction(pstTicket, false);
			break;

		case APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_NO_MORE_ERROR_CODE:
			DisplayTransaction(pstTicket, false);
			break;

		case APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_MORE_ERROR_CODE:
			DisplayTransaction(pstTicket, false);

			switch (pstPaymentRequest->typeOfPayment)
			{
			case REVERSE_PAYMENT_BANK_CARD_VOID:
			case REVERSE_PAYMENT_BANK_CARD_REFUND:
			case REVERSE_PAYMENT_YEMEKCEKI:
			case REVERSE_PAYMENT_MOBILE:
			case REVERSE_PAYMENT_HEDIYE_CEKI:
				sprintf(&display[strlen(display)], "\r\n%s(%s)"	, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stPaymentErrMessage.ErrorMsg
						, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stPaymentErrMessage.ErrorCode
					   );
				sprintf(&display[strlen(display)], "\r\n%s(%s)"	, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stPaymentErrMessage.AppErrorMsg
						, pstTicket->stPayment[pstTicket->totalNumberOfPayments-1].stBankPayment.stPaymentErrMessage.AppErrorCode
					   );
				break;
			}

			break;

		default:
			break;
		}

		if (retcode != TRAN_RESULT_OK)
			HandleErrorCode(retcode);
		else if (strlen(display))
			DisplayInfo(display);
	}

	m_csInput.Empty();
	m_csTtemCount.Empty();
	m_comboBoxCurrency.SetCurSel(0);

	return retcode;
}

void CePosDlg::OnBnClickedButtonNakit()
{
	uint16 currency = 0;
	uint32 amount = 0;
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);

	ST_PAYMENT_REQUEST stPaymentRequest[1];
	memset(stPaymentRequest, 0, sizeof(ST_PAYMENT_REQUEST));

	stPaymentRequest[0].typeOfPayment			= PAYMENT_CASH_TL;
	stPaymentRequest[0].subtypeOfPayment		= NULL;
	stPaymentRequest[0].payAmount				= amount;
	stPaymentRequest[0].payAmountCurrencyCode	= currency;

	GetPayment(stPaymentRequest, 1);
}

void CePosDlg::GetTypedItemCount(uint32* pItemCount, uint8* pItemCountPrecition)
{
	int  itemcountDotLocation =  m_csTtemCount.Find('.');
	*pItemCountPrecition = 0;
	*pItemCount = 0;

	if (itemcountDotLocation >= 0)
	{
		*pItemCountPrecition = m_csTtemCount.GetLength() - m_csTtemCount.Find('.') - 1;
		*pItemCount = atol(CT2A((LPCTSTR)(m_csTtemCount.Left(itemcountDotLocation) + m_csTtemCount.Right(*pItemCountPrecition))));
	}
	else
		// No '.'
		*pItemCount = atol(CT2A((LPCTSTR)m_csTtemCount));

	m_csTtemCount.Empty();
}

void CePosDlg::OnBnClickedButtonPlu()
{
	int retcode;
	ST_ITEM stItem;
	uint8  CurrencyProfileIndex = 0;
	// PLU Barcode...
	m_EditControlInput.GetWindowTextW(m_csInput);
	if (!m_csInput.GetLength())
		return;

	uint32 amount = 0;
	uint16 currency = (uint16)m_comboBoxCurrency.GetItemData(m_comboBoxCurrency.GetCurSel());

	uint8 unitType = 0;
	uint32 itemCount = 0;
	uint8  itemCountPrecition = 0;
	GetTypedItemCount(&itemCount, &itemCountPrecition);

	memset(&stItem, 0x00, sizeof(stItem));
	stItem.type			= ITEM_TYPE_PLU;
	stItem.subType		= 0;
	stItem.deptIndex	= 0;
	stItem.amount		= amount;
	stItem.currency		= currency;
	stItem.count		= itemCount;
	stItem.unitType		= unitType;
	stItem.pluPriceIndex = 0;
	stItem.countPrecition	= itemCountPrecition;
	/*if(m_TaxExceptional_Taxless)
		stItem.flag			|= ITEM_OPTION_TAX_EXCEPTION_TAXLESS;
	m_TaxExceptional_Taxless = false;*/

	if (m_TaxExceptional_Taxless)
		stItem.flag			|= ITEM_TAX_EXCEPTION_VAT_INCLUDED_TO_PRICE;
	m_TaxExceptional_Taxless = false;

	if (m_TaxExceptional_Vat_Excluded)
		stItem.flag			|= ITEM_TAX_EXCEPTION_VAT_NOT_INCLUDED_TO_PRICE;
	m_TaxExceptional_Vat_Excluded = false;

	strcpy(stItem.name, "");
	strcpy(stItem.barcode, CT2A((LPCTSTR)m_csInput));

	if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
	{
		HTRX hTrx = GetSelectedTransaction();
		HINT hInt = GetSelectedInterface();

		retcode = StartTicket(hInt, &hTrx, TProcessSale);
		if (retcode != TRAN_RESULT_OK)
			return;

		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		retcode = FP3_ItemSale(hInt, hTrx, &stItem, pstTicket);
		if (retcode)
		{
			HandleErrorCode(retcode);
			return;
		}

		DisplayTransaction(pstTicket, false);
		DisplayItem(pstTicket, pstTicket->totalNumberOfItems - 1);
	}
	else
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		bufferLen = prepare_ItemSale(&buffer[0], sizeof(buffer), &stItem);
		AddIntoCommandBatch(L"_prepare_ItemSale", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}

	m_csInput.Empty();
	m_comboBoxCurrency.SetCurSel(0);
	m_EditControlInput.SetWindowTextW(m_csInput);
}


void CePosDlg::OnBnClickedButtonGetSetCurrencyProfile()
{
	ST_EXCHANGE_PROFILE	stExchangeProfileTable[4];
	CGetInputDlg* pcInput;
	CCurrencyEditDlg CurrencyDlg;
	int		retcode;
	uint32	fInputType = 0;
	uint8	i, Index, ProfileProcessType = 0;
	char    profileName[24];
	bool    newProfile = false;

	HINT hInt = GetSelectedInterface();

	memset(stExchangeProfileTable, 0x00, sizeof(stExchangeProfileTable));
	if (retcode = FP3_GetCurrencyProfile(hInt, stExchangeProfileTable))
	{
		HandleErrorCode(retcode);
		return ;
	}
	Index = 0;
	pcInput = new CGetInputDlg;
	for (i = 0; i < MAX_EXCHANGE_PROFILE_COUNT; i++)
	{
		if (stExchangeProfileTable[i].NumberOfCurrency == 0)
			continue;
		pcInput->InsertFlag((CString)stExchangeProfileTable[i].ProfileName, ++Index, false);
	}
	pcInput->InsertFlag((CString)"YENI PROFIL", ++Index, false);

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	if (pcInput->DoModal(L"Select Exchange Profile ?", L"", 4) != IDOK)
		return;
	fInputType = (uint32)pcInput->m_flagValue;
	delete pcInput;

	//Flag secilmis mi? Yada TSM Profile secil mis mi?
	if (fInputType == 0)  // || fInputType == 1
		return;

	// Max 4 profile tanimlanabilir
	if (fInputType > MAX_EXCHANGE_PROFILE_COUNT)
		return;

	if (fInputType ==  Index) // yeni secildi..
	{
		memset(profileName, 0x00, sizeof(profileName));
		if (!GetStringInput(L"PROFILE ADI GIRINIZ?", profileName))
			return;
		CurrencyDlg.m_profileName = (CString)profileName;
		//Index i ayarla
		fInputType--;

		//TSM i kopyala
		stExchangeProfileTable[fInputType] = stExchangeProfileTable[0];
		// copy Profile Name
		strcpy(stExchangeProfileTable[fInputType].ProfileName, profileName);
		newProfile = true;
	}
	else
		//Index i ayarla
		fInputType--;

	for (i = 0; i < stExchangeProfileTable[fInputType].NumberOfCurrency; i++)
	{
		switch (i)
		{
		case 0:
			CurrencyDlg.m_CurrencyCode.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].code);

			CurrencyDlg.m_CurrencySymbol.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].prefix);
			CurrencyDlg.m_CurrencyShortName.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].sign);
			CurrencyDlg.m_CurrencyDigitGroupSymbol.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].tousandSeperator);

			CurrencyDlg.m_CurrencyDecimalSymbol.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].centSeperator);
			CurrencyDlg.m_CurrencyExponent.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].numberOfCentDigit);
			CurrencyDlg.m_CurrencySymbolPosition.Format(stExchangeProfileTable[fInputType].ExchangeRecords[i].locationOfSign == 'L' ? (CString)"LEFT" : (CString)"RIGHT");
			CurrencyDlg.m_CurrencyTLRate.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].rate);
			break;
		case 1:
			CurrencyDlg.m_CurrencyCode2.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].code);

			CurrencyDlg.m_CurrencySymbol2.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].prefix);
			CurrencyDlg.m_CurrencyShortName2.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].sign);
			CurrencyDlg.m_CurrencyDigitGroupSymbol2.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].tousandSeperator);

			CurrencyDlg.m_CurrencyDecimalSymbol2.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].centSeperator);
			CurrencyDlg.m_CurrencyExponent2.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].numberOfCentDigit);
			CurrencyDlg.m_CurrencySymbolPosition2.Format(stExchangeProfileTable[fInputType].ExchangeRecords[i].locationOfSign == 'L' ? (CString)"LEFT" : (CString)"RIGHT");
			CurrencyDlg.m_CurrencyTLRate2.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].rate);
			break;
		case 2:
			CurrencyDlg.m_CurrencyCode3.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].code);

			CurrencyDlg.m_CurrencySymbol3.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].prefix);
			CurrencyDlg.m_CurrencyShortName3.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].sign);
			CurrencyDlg.m_CurrencyDigitGroupSymbol3.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].tousandSeperator);

			CurrencyDlg.m_CurrencyDecimalSymbol3.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].centSeperator);
			CurrencyDlg.m_CurrencyExponent3.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].numberOfCentDigit);
			CurrencyDlg.m_CurrencySymbolPosition3.Format(stExchangeProfileTable[fInputType].ExchangeRecords[i].locationOfSign == 'L' ? (CString)"LEFT" : (CString)"RIGHT");
			CurrencyDlg.m_CurrencyTLRate3.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].rate);
			break;
		case 3:
			CurrencyDlg.m_CurrencyCode4.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].code);

			CurrencyDlg.m_CurrencySymbol4.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].prefix);
			CurrencyDlg.m_CurrencyShortName4.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].sign);
			CurrencyDlg.m_CurrencyDigitGroupSymbol4.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].tousandSeperator);

			CurrencyDlg.m_CurrencyDecimalSymbol4.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].centSeperator);
			CurrencyDlg.m_CurrencyExponent4.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].numberOfCentDigit);
			CurrencyDlg.m_CurrencySymbolPosition4.Format(stExchangeProfileTable[fInputType].ExchangeRecords[i].locationOfSign == 'L' ? (CString)"LEFT" : (CString)"RIGHT");
			CurrencyDlg.m_CurrencyTLRate4.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].rate);
			break;
		case 4:
			CurrencyDlg.m_CurrencyCode5.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].code);

			CurrencyDlg.m_CurrencySymbol5.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].prefix);
			CurrencyDlg.m_CurrencyShortName5.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].sign);
			CurrencyDlg.m_CurrencyDigitGroupSymbol5.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].tousandSeperator);

			CurrencyDlg.m_CurrencyDecimalSymbol5.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].centSeperator);
			CurrencyDlg.m_CurrencyExponent5.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].numberOfCentDigit);
			CurrencyDlg.m_CurrencySymbolPosition5.Format(stExchangeProfileTable[fInputType].ExchangeRecords[i].locationOfSign == 'L' ? (CString)"LEFT" : (CString)"RIGHT");
			CurrencyDlg.m_CurrencyTLRate5.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].rate);
			break;
		case 5:
			CurrencyDlg.m_CurrencyCode6.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].code);

			CurrencyDlg.m_CurrencySymbol6.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].prefix);
			CurrencyDlg.m_CurrencyShortName6.Format(L"%0.3s", (CString)stExchangeProfileTable[fInputType].ExchangeRecords[i].sign);
			CurrencyDlg.m_CurrencyDigitGroupSymbol6.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].tousandSeperator);

			CurrencyDlg.m_CurrencyDecimalSymbol6.Format(L"%c", stExchangeProfileTable[fInputType].ExchangeRecords[i].centSeperator);
			CurrencyDlg.m_CurrencyExponent6.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].numberOfCentDigit);
			CurrencyDlg.m_CurrencySymbolPosition6.Format(stExchangeProfileTable[fInputType].ExchangeRecords[i].locationOfSign == 'L' ? (CString)"LEFT" : (CString)"RIGHT");
			CurrencyDlg.m_CurrencyTLRate6.Format(L"%d", stExchangeProfileTable[fInputType].ExchangeRecords[i].rate);
			break;
		default:
			break;
		}
	}

	if (CurrencyDlg.DoModal() != IDOK)
		return;

	/// copy data to the profile again....only rate of the currency must be saved

	stExchangeProfileTable[fInputType].ExchangeRecords[0].rate = atoi(CStringA(CurrencyDlg.m_CurrencyTLRate.GetString()));
	stExchangeProfileTable[fInputType].ExchangeRecords[1].rate = atoi(CStringA(CurrencyDlg.m_CurrencyTLRate2.GetString()));
	stExchangeProfileTable[fInputType].ExchangeRecords[2].rate = atoi(CStringA(CurrencyDlg.m_CurrencyTLRate3.GetString()));
	stExchangeProfileTable[fInputType].ExchangeRecords[3].rate = atoi(CStringA(CurrencyDlg.m_CurrencyTLRate4.GetString()));
	stExchangeProfileTable[fInputType].ExchangeRecords[4].rate = atoi(CStringA(CurrencyDlg.m_CurrencyTLRate5.GetString()));
	stExchangeProfileTable[fInputType].ExchangeRecords[5].rate = atoi(CStringA(CurrencyDlg.m_CurrencyTLRate6.GetString()));


	/*  ADDED FOR TEST*/
	stExchangeProfileTable[fInputType].ExchangeRecords[0].tousandSeperator = '.';
	stExchangeProfileTable[fInputType].ExchangeRecords[0].centSeperator = ',';
	stExchangeProfileTable[fInputType].ExchangeRecords[0].numberOfCentDigit = 4;

	stExchangeProfileTable[fInputType].ExchangeRecords[1].tousandSeperator = '.';
	stExchangeProfileTable[fInputType].ExchangeRecords[1].centSeperator = ',';
	stExchangeProfileTable[fInputType].ExchangeRecords[1].numberOfCentDigit = 4;

	stExchangeProfileTable[fInputType].ExchangeRecords[2].tousandSeperator = '.';
	stExchangeProfileTable[fInputType].ExchangeRecords[2].centSeperator = ',';
	stExchangeProfileTable[fInputType].ExchangeRecords[2].numberOfCentDigit = 4;

	stExchangeProfileTable[fInputType].ExchangeRecords[3].tousandSeperator = '.';
	stExchangeProfileTable[fInputType].ExchangeRecords[3].centSeperator = ',';
	stExchangeProfileTable[fInputType].ExchangeRecords[3].numberOfCentDigit = 4;

	/*  END FOR TEST*/

	//ProfileProcessType		Ecr Profile type if ProfileProcessType : 1 update, 2: add,  3:delete
	ProfileProcessType = 3; // add
	if (CurrencyDlg.m_DeleteProfile == TRUE)
		ProfileProcessType = 3; // delete
	else if (newProfile)
		ProfileProcessType = 2; // add
	else
		ProfileProcessType = 1; // update

	CPasswordDlg PasswordDlg;
	if (PasswordDlg.DoModal(L"YÖNETÝCÝ ÞÝFRESÝ") != IDOK)
		return;

	retcode = FP3_SetCurrencyProfile(hInt, CT2A((LPCTSTR)PasswordDlg.m_Password), fInputType, ProfileProcessType , &stExchangeProfileTable[fInputType]);

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonSetExchangeProfile()
{
#define FLAG_EXCHANGE_PROFILE_1		0x01
#define FLAG_EXCHANGE_PROFILE_2		0x02
#define FLAG_EXCHANGE_PROFILE_3		0x03
#define FLAG_EXCHANGE_PROFILE_4		0x04

	int retcode = TRAN_RESULT_OK;
	CGetInputDlg* pcInput;
	CCurrencyEditDlg CurrencyDlg;
	uint32 fInputType = 0;
	uint8 i;
	uint32 GL_Dialog_retcode = TRAN_RESULT_OK;

	HTRX hTrx = GetSelectedTransaction();
	HINT hInt = GetSelectedInterface();


	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);
	if (ptr == NULL)
		return ;

	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (retcode = FP3_GetCurrencyProfile(hInt, ptr->stExchangeProfileTable))
	{
		HandleErrorCode(retcode);
		return ;
	}

	pcInput = new CGetInputDlg;
	for (i = 0; i < MAX_EXCHANGE_PROFILE_COUNT; i++)
	{
		if (ptr->stExchangeProfileTable[i].NumberOfCurrency == 0)
			continue;
		pcInput->InsertFlag((CString) ptr->stExchangeProfileTable[i].ProfileName, i + 1, false);

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	if (pcInput->DoModal(L"Select Exchange Profile ?", L"", 4) != IDOK)
		return;
	fInputType = (uint32)pcInput->m_flagValue;
	delete pcInput;

	retcode = FP3_SetCurrencyProfileIndex(hInt, hTrx, fInputType - 1, pstTicket);

	if (GL_Dialog_retcode != TRAN_RESULT_OK)
		DisplayInfo("GL_Dialog_retcode = %04X", GL_Dialog_retcode);

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonSetOnlineInvoice()
{
#define FLAG_GETDIALOG_TYPE_TEXT		0x0001

	int retcode;
	COnlineInvoiceDlg onlineInvoiceDlg;
	ST_ONLINE_INVIOCE_INFO stOnlineInvoiceInfo;
	uint64 activeFlags;
	bool ticketStartLocally = false;

	memset(&stOnlineInvoiceInfo, 0x00, sizeof(stOnlineInvoiceInfo));

	// Handle the return value from DoModal

	onlineInvoiceDlg.InsertFlag(L"Aktif"		, FLAG_GETDIALOG_TYPE_TEXT		, false);
	onlineInvoiceDlg.InsertFlag(L"Aktif"		, FLAG_GETDIALOG_TYPE_TEXT		, false);

	if (onlineInvoiceDlg.DoModal() != IDOK)
		return;

	sprintf((char*)stOnlineInvoiceInfo.CustomerName	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceCustomerInfo), onlineInvoiceDlg.m_csOnlineInvoiceCustomerInfo.GetLength());

	sprintf((char*)stOnlineInvoiceInfo.VKN	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceVKN), onlineInvoiceDlg.m_csOnlineInvoiceVKN.GetLength());
	sprintf((char*)stOnlineInvoiceInfo.HomeAddress	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceHomeAddress), onlineInvoiceDlg.m_csOnlineInvoiceHomeAddress.GetLength());
	sprintf((char*)stOnlineInvoiceInfo.District	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceDistrict), onlineInvoiceDlg.m_csOnlineInvoiceDistrict.GetLength());
	sprintf((char*)stOnlineInvoiceInfo.City	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceCity), onlineInvoiceDlg.m_csOnlineInvoiceCity.GetLength());
	sprintf((char*)stOnlineInvoiceInfo.Country	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceCountry), onlineInvoiceDlg.m_csOnlineInvoiceCountry.GetLength());
	sprintf((char*)stOnlineInvoiceInfo.Mail	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceEmail), onlineInvoiceDlg.m_csOnlineInvoiceEmail.GetLength());
	sprintf((char*)stOnlineInvoiceInfo.WebSite	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceWeb), onlineInvoiceDlg.m_csOnlineInvoiceWeb.GetLength());
	sprintf((char*)stOnlineInvoiceInfo.Phone	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoicePhone), onlineInvoiceDlg.m_csOnlineInvoicePhone.GetLength());
	sprintf((char*)stOnlineInvoiceInfo.TaxOffice	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceTaxOffice), onlineInvoiceDlg.m_csOnlineInvoiceTaxOffice.GetLength());

	if (onlineInvoiceDlg.m_csOnlineInvoiceOrderNo != " ")
	{
		LongToBcd(onlineInvoiceDlg.m_dateOnlineInvoiceOrderDate.GetDay()	, &stOnlineInvoiceInfo.OrderDate[3], 1);
		LongToBcd(onlineInvoiceDlg.m_dateOnlineInvoiceOrderDate.GetMonth()	, &stOnlineInvoiceInfo.OrderDate[2], 1);
		LongToBcd(onlineInvoiceDlg.m_dateOnlineInvoiceOrderDate.GetYear()	, &stOnlineInvoiceInfo.OrderDate[1], 1);
		LongToBcd(20	, &stOnlineInvoiceInfo.OrderDate[0], 1);

		sprintf((char*)stOnlineInvoiceInfo.OrderDate	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceOrderNo), onlineInvoiceDlg.m_csOnlineInvoiceOrderNo.GetLength());

	}
	if (onlineInvoiceDlg.m_csOnlineInvoiceDespatchNo != " ")
	{
		LongToBcd(onlineInvoiceDlg.m_dateOnlineInvoiceDespatchDate.GetDay()	, &stOnlineInvoiceInfo.DespatchDate[3], 1);
		LongToBcd(onlineInvoiceDlg.m_dateOnlineInvoiceDespatchDate.GetMonth()	, &stOnlineInvoiceInfo.DespatchDate[2], 1);
		LongToBcd(onlineInvoiceDlg.m_dateOnlineInvoiceDespatchDate.GetYear()	, &stOnlineInvoiceInfo.DespatchDate[1], 1);
		LongToBcd(20	, &stOnlineInvoiceInfo.DespatchDate[0], 1);

		sprintf((char*)stOnlineInvoiceInfo.DespatchNo	, CT2A((LPCTSTR)onlineInvoiceDlg.m_csOnlineInvoiceDespatchNo), onlineInvoiceDlg.m_csOnlineInvoiceDespatchNo.GetLength());
	}

	HTRX hTrx = GetSelectedTransaction();
	HINT hInt = GetSelectedInterface();
	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);
	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (hTrx == NULL)
	{
		m_listPrinterOutput.ResetContent();

		retcode = TransactionHandle_StartAndInsert(hInt, &hTrx, FALSE, ptr->m_uniqueId, sizeof(ptr->m_uniqueId));
		if (retcode != TRAN_RESULT_OK)
			goto EXIT;

		pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);
		ticketStartLocally = true;

		retcode = FP3_OptionFlags(hInt, hTrx, &activeFlags,  RESPONSE_FLAGS, 0x00000000, TIMEOUT_DEFAULT);
		if (retcode != TRAN_RESULT_OK)
			goto EXIT;
	}

	retcode = FP3_SetOnlineInvoice(hInt, hTrx, &stOnlineInvoiceInfo, pstTicket);
	if (retcode != TRAN_RESULT_OK)
		goto EXIT;

	retcode = FP3_TicketHeader(hInt, hTrx, TInvoice);
	if ((retcode != TRAN_RESULT_OK) && (retcode != APP_ERR_TICKET_HEADER_ALREADY_PRINTED))
		goto EXIT;

EXIT:
	HandleErrorCode(retcode);

	if (retcode)
	{
		if (ticketStartLocally)
			TransactionHandle_CloseAndRemove(hInt, hTrx);
		return;
	}

	DisplayTransaction(pstTicket, false);
}

void CePosDlg::OnBnClickedButtonCheckPairingStatus()
{
	int retcode;
	HINT hInt = GetSelectedInterface();

	retcode = FP3_IsGmpPairingDone(hInt);
	if (retcode == 0)
		MessageBox(L"Eþleþme yapýlmamýþ", L"Warning", MB_OK);
	else
		MessageBox(L"Eþleþme yapýlmýþ. Fakat eþlenilen ÖKC ile harici cihaza takýlý ÖKC ayný cihaz olmayabilir. Lütfen kontrol ediniz.", L"Warning", MB_OK);
}
void CePosDlg::OnBnClickedButtonTaxFreeInfo()
{
	int retcode;
	CTaxFreeDlg taxFreeDlg;
	ST_TAXFREE_INFO stTaxFreeInfo;
	uint64 activeFlags;
	bool ticketStartLocally = false;

	memset(&stTaxFreeInfo, 0x00, sizeof(stTaxFreeInfo));

	// Handle the return value from DoModal

	if (taxFreeDlg.DoModal() != IDOK)
		return;

	sprintf((char*)stTaxFreeInfo.BuyerName	, CT2A((LPCTSTR)taxFreeDlg.m_csTaxFreeBuyerName), taxFreeDlg.m_csTaxFreeBuyerName.GetLength());
	sprintf((char*)stTaxFreeInfo.BuyerSurname	, CT2A((LPCTSTR)taxFreeDlg.m_csTaxFreeBuyerSurname), taxFreeDlg.m_csTaxFreeBuyerSurname.GetLength());

	sprintf((char*)stTaxFreeInfo.ID	, CT2A((LPCTSTR)taxFreeDlg.m_csTaxFreeVKN), taxFreeDlg.m_csTaxFreeVKN.GetLength());
	sprintf((char*)stTaxFreeInfo.City	, CT2A((LPCTSTR)taxFreeDlg.m_csTaxFreeCity), taxFreeDlg.m_csTaxFreeCity.GetLength());
	sprintf((char*)stTaxFreeInfo.Country	, CT2A((LPCTSTR)taxFreeDlg.m_csTaxFreeCountry), taxFreeDlg.m_csTaxFreeCountry.GetLength());

	CString text;
	CString subText;

	text = taxFreeDlg.m_CountryCode;
	subText = text.Left(2);

	sprintf((char*)stTaxFreeInfo.CountryCode	, CT2A((LPCTSTR)subText), 2);

	LongToBcd(taxFreeDlg.m_dateTaxFreeOrderDate.GetDay()	, &stTaxFreeInfo.OrderDate[2], 1);
	LongToBcd(taxFreeDlg.m_dateTaxFreeOrderDate.GetMonth()	, &stTaxFreeInfo.OrderDate[1], 1);
	LongToBcd(taxFreeDlg.m_dateTaxFreeOrderDate.GetYear()	, &stTaxFreeInfo.OrderDate[0], 1);

	sprintf((char*)stTaxFreeInfo.Ettn	, CT2A((LPCTSTR)taxFreeDlg.m_csTaxFreeEttn), taxFreeDlg.m_csTaxFreeEttn.GetLength());
	sprintf((char*)stTaxFreeInfo.Identifier	, CT2A((LPCTSTR)taxFreeDlg.m_csTaxFreeLabel), taxFreeDlg.m_csTaxFreeLabel.GetLength());

	HTRX hTrx = GetSelectedTransaction();
	HINT hInt = GetSelectedInterface();
	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);
	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (hTrx == NULL)
	{
		m_listPrinterOutput.ResetContent();

		retcode = TransactionHandle_StartAndInsert(hInt, &hTrx, FALSE, ptr->m_uniqueId, sizeof(ptr->m_uniqueId));
		if (retcode != TRAN_RESULT_OK)
			goto EXIT;

		pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);
		ticketStartLocally = true;

		retcode = FP3_OptionFlags(hInt, hTrx, &activeFlags,  RESPONSE_FLAGS, 0x00000000, TIMEOUT_DEFAULT);
		if (retcode != TRAN_RESULT_OK)
			goto EXIT;
	}

	retcode = FP3_SetTaxFreeInfo(hInt, hTrx, &stTaxFreeInfo, pstTicket);
	if (retcode != TRAN_RESULT_OK)
		goto EXIT;

	retcode = FP3_TicketHeader(hInt, hTrx, TInvoice);
	if ((retcode != TRAN_RESULT_OK) && (retcode != APP_ERR_TICKET_HEADER_ALREADY_PRINTED))
		goto EXIT;

EXIT:
	HandleErrorCode(retcode);

	if (retcode)
	{
		if (ticketStartLocally)
			TransactionHandle_CloseAndRemove(hInt, hTrx);
		return;
	}

	DisplayTransaction(pstTicket, false);
}
void CePosDlg::OnBnClickedButtonInvoice()
{
	int retcode;
	CInvoiceDlg invoiceDlg;
	ST_INVIOCE_INFO stInvoiceInfo;
	uint64 activeFlags;
	bool ticketStartLocally = false;

	memset(&stInvoiceInfo, 0x00, sizeof(stInvoiceInfo));

	if (invoiceDlg.DoModal() != IDOK)
		return;

	stInvoiceInfo.source	= invoiceDlg.m_byteFaturaTipi;
	stInvoiceInfo.amount	= atol(CT2A((LPCTSTR)invoiceDlg.m_csInvoiceAmount));
	stInvoiceInfo.currency	= CURRENCY_TL;

	sprintf((char*)stInvoiceInfo.no	, CT2A((LPCTSTR)invoiceDlg.m_csInvoiceNo), invoiceDlg.m_csInvoiceNo.GetLength());
	sprintf((char*)stInvoiceInfo.tck_no, CT2A((LPCTSTR)invoiceDlg.m_TCK_NO), invoiceDlg.m_TCK_NO.GetLength());
	sprintf((char*)stInvoiceInfo.vk_no	, CT2A((LPCTSTR)invoiceDlg.m_VK_NO), invoiceDlg.m_VK_NO.GetLength());

	LongToBcd(invoiceDlg.m_dateInvoiceDate.GetDay()	, &stInvoiceInfo.date[2], 1);
	LongToBcd(invoiceDlg.m_dateInvoiceDate.GetMonth()	, &stInvoiceInfo.date[1], 1);
	LongToBcd(invoiceDlg.m_dateInvoiceDate.GetYear()	, &stInvoiceInfo.date[0], 1);

	if (invoiceDlg.m_Irsaliye)
		stInvoiceInfo.flag |= INVOICE_FLAG_IRSALIYE;

	HTRX hTrx = GetSelectedTransaction();
	HINT hInt = GetSelectedInterface();
	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);
	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (hTrx == NULL)
	{
		m_listPrinterOutput.ResetContent();

		retcode = TransactionHandle_StartAndInsert(hInt, &hTrx, FALSE, ptr->m_uniqueId, sizeof(ptr->m_uniqueId));
		if (retcode != TRAN_RESULT_OK)
			goto EXIT;

		pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);
		ticketStartLocally = true;

		retcode = FP3_OptionFlags(hInt, hTrx, &activeFlags,  RESPONSE_FLAGS, 0x00000000, TIMEOUT_DEFAULT);
		if (retcode != TRAN_RESULT_OK)
			goto EXIT;
	}

	retcode = FP3_SetInvoice(hInt, hTrx, &stInvoiceInfo, pstTicket);
	if (retcode != TRAN_RESULT_OK)
		goto EXIT;

	retcode = FP3_TicketHeader(hInt, hTrx, TInvoice);
	if ((retcode != TRAN_RESULT_OK) && (retcode != APP_ERR_TICKET_HEADER_ALREADY_PRINTED))
		goto EXIT;

EXIT:
	HandleErrorCode(retcode);

	if (retcode)
	{
		if (ticketStartLocally)
			TransactionHandle_CloseAndRemove(hInt, hTrx);
		return;
	}

	DisplayTransaction(pstTicket, false);
}

void CePosDlg::OnBnClickedButtonOtoparkEntryTicket()
{
	int retcode;
	char carPlateNo[24+1] = "34 ABC 99";

	if (!GetStringInput(L"CAR IDENTIFICATION", carPlateNo))
		return;

	HTRX hTrx = GetSelectedTransaction();
	HINT hInt = GetSelectedInterface();

	if (StartTicket(hInt, &hTrx, TOtopark))
		return;

	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (retcode = FP3_SetParkingTicket(hInt, hTrx, carPlateNo, pstTicket))
		goto Exit;

	if (retcode = FP3_PrintBeforeMF(hInt, hTrx))
		goto Exit;

	if (retcode = FP3_PrintMF(hInt, hTrx))
		goto Exit;

Exit:
	HandleErrorCode(retcode);
	TransactionHandle_CloseAndRemove(hInt, hTrx);
}

void CePosDlg::OnBnClickedButtonVoidAll()
{

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_VoidAll(&buffer[0], sizeof(buffer));
		AddIntoCommandBatch(L"_prepare_VoidAll", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		HINT hInt = GetSelectedInterface();
		HTRX hTrx = GetSelectedTransaction();

		int retcode = FP3_VoidAll(hInt, hTrx, NULL);
		if (retcode == TRAN_RESULT_OK)
			TransactionHandle_CloseAndRemove(hInt, hTrx);
		HandleErrorCode(retcode);
	}

	m_csInput.Empty();
	m_csTtemCount.Empty();
	m_comboBoxCurrency.SetCurSel(0);
	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButtonVoidItem()
{
	int index = 1;
	int retcode;

	uint8 unitType = 0;
	uint32 itemCount = 0;
	uint8  itemCountPrecition = 0;
	GetTypedItemCount(&itemCount, &itemCountPrecition);
	if (itemCount == 0)
		itemCount = 1;

	if (!GetIntegerInput(L"Index Of Item To void (1 Based)", &index))
		return;
	if (index == 0)
		return;

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_VoidItem(&buffer[0], sizeof(buffer), (uint16)index - 1, itemCount, itemCountPrecition);
		AddIntoCommandBatch(L"_prepare_VoidItem", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		HINT hInt = GetSelectedInterface();
		HTRX hTrx = GetSelectedTransaction();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		if (retcode = FP3_VoidItem(hInt, hTrx, index - 1, itemCount, itemCountPrecition, pstTicket))
		{
			HandleErrorCode(retcode);
			return;
		}

		DisplayTransaction(pstTicket, false);
		// Show last item
		DisplayItem(pstTicket, (uint16)index - 1);
	}

	m_csInput.Empty();
	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButtonTaxExceptionTaxless()
{
	m_TaxExceptional_Taxless = !m_TaxExceptional_Taxless;

	if (m_TaxExceptional_Taxless)
		DisplayInfo("%s", "TAXLESS (Diplomatic) IS ACTIVE");
	else
		DisplayInfo("%s", "TAXLESS (Diplomatic) IS INACTIVE");
}

void CePosDlg::OnBnClickedButtonLoyalty()
{
	OnTransactionLoyalty();

	m_csInput.Empty();
	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButtonTaxExceptionVatExcluded()
{
	m_TaxExceptional_Vat_Excluded = !m_TaxExceptional_Vat_Excluded;

	if (m_TaxExceptional_Vat_Excluded)
		DisplayInfo("%s", "DIPLOMATIC SALE VAT EXCLUDED IS ACTIVE");
	else
		DisplayInfo("%s", "DIPLOMATIC SALE VAT EXCLUDED IS INACTIVE");
}

void CePosDlg::OnBnClickedButtonYemekCeki()
{
	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	StartTicket(hInt, &hTrx, TYemekceki);

	m_csInput.Empty();
	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButtonMatrahsiz()
{
	int retcode;
	int commision = 0;
	char szCommission[12];

	uint16 currency = 0;
	uint32 amount = 0;
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	if (amount == 0)
		return;

	uint8 unitType = 0;
	uint32 itemCount = 0;
	uint8  itemCountPrecition = 0;
	GetTypedItemCount(&itemCount, &itemCountPrecition);
	if (itemCount == 0)
		itemCount = 1;

	ST_ITEM stItem;
	memset(&stItem, 0x00, sizeof(stItem));
	stItem.type				= ITEM_TYPE_MONEYCOLLECTION;
	stItem.deptIndex		= 0;
	stItem.amount			= amount;
	stItem.currency			= currency;
	stItem.count			= itemCount;
	stItem.unitType			= 0;
	stItem.pluPriceIndex	= 0;
	stItem.countPrecition	= itemCountPrecition;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	CGetInputDlg* pcInput;
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"MATRAHSIZ_TYPE_ILAC"					, MATRAHSIZ_TYPE_ILAC, false);
	pcInput->InsertFlag(L"MATRAHSIZ_TYPE_MUAYANE"				, MATRAHSIZ_TYPE_MUAYANE, true);
	pcInput->InsertFlag(L"MATRAHSIZ_TYPE_MUAYANE_RECETE"		, MATRAHSIZ_TYPE_MUAYANE_RECETE, false);
	pcInput->InsertFlag(L"MATRAHSIZ_TYPE_INVOICE_COLLECTION"	, MATRAHSIZ_TYPE_INVOICE_COLLECTION, false);
	if (pcInput->DoModal(L"SUBTYPE OF NON-TAXABLE ITEM?", L"", 4) != IDOK)
		return;
	stItem.subType = (uint8)pcInput->m_flagValue;
	delete pcInput;

	switch (stItem.subType)
	{
	case MATRAHSIZ_TYPE_ILAC:
	case MATRAHSIZ_TYPE_MUAYANE:
	case MATRAHSIZ_TYPE_MUAYANE_RECETE:
		strcpy(stItem.tckno, "123456791110");
		if (!GetStringInput(L"TC No ?", stItem.tckno))
			return;
		break;

	case MATRAHSIZ_TYPE_INVOICE_COLLECTION:
		strcpy(szCommission, "0");
		if (!GetStringInput(L"COMMISSION AMOUNT?", szCommission))
			return;

		commision = atoi(szCommission);

		////
		//stItem.Date = 0x00045678;

		CTime time = CTime::GetCurrentTime();

		LongToBcd(time.GetDay()	, &stItem.Date[2], 1);
		LongToBcd(time.GetMonth()	, &stItem.Date[1], 1);
		LongToBcd(time.GetYear()	, &stItem.Date[0], 1);



		//stItem.Date[2]  = 0x16;
		//stItem.Date[1]  = 0x05;
		//stItem.Date[0]  = 0x10;

		//stItem.Date[2]  = 0x10;
		//stItem.Date[1]  = 0x05;
		//stItem.Date[0]  = 0x0a;

		strcpy(stItem.firm, "TURK TELEKOM A.Þ.");
		if (!GetStringInput(L"UTULITY FIRM ?", stItem.firm))
			return;

		strcpy(stItem.invoiceNo, "A-12345678");
		if (!GetStringInput(L"INVOICE NO ?", stItem.invoiceNo))
			return;

		strcpy(stItem.subscriberId, "02124440333");
		if (!GetStringInput(L"SUBSCRIBER ID ?", stItem.subscriberId))
			return;
		break;
	}

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	if (commision)
	{
		StartTicket(hInt, &hTrx, TProcessSale);
	}
	else
	{
		StartTicket(hInt, &hTrx, TInfo);
	}
	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		bufferLen = prepare_ItemSale(&buffer[0], sizeof(buffer), &stItem);
		AddIntoCommandBatch(L"prepare_ItemSale", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		if (retcode = FP3_ItemSale(hInt, hTrx, &stItem, pstTicket))
		{
			HandleErrorCode(retcode);
			return;
		}
		if (commision)
		{
			memset(&stItem, 0x00, sizeof(stItem));
			stItem.type				= ITEM_TYPE_DEPARTMENT;
			stItem.deptIndex		= 0;
			stItem.amount			= commision;
			stItem.currency			= currency;
			stItem.count			= 1;
			stItem.unitType			= 0;
			stItem.pluPriceIndex	= 0;
			stItem.countPrecition	= 0;
			strcpy(stItem.name, "FATURA TAHSÝLAT ÜCRETÝ");

			if (retcode = FP3_ItemSale(hInt, hTrx, &stItem, pstTicket))
			{
				HandleErrorCode(retcode);
				return;
			}
		}

		DisplayTransaction(pstTicket, false);
	}
}

void CePosDlg::OnBnClickedButtonXXX2()
{
}

void CePosDlg::OnBnClickedButtonCariHesap()
{
#define FLAG_GETDIALOG_TYPE_TEXT		0x0001

	int retcode;
	CCariHesapDlg cariHesapDlg;
	//uint64 activeFlags;
	bool ticketStartLocally = false;

	uint16 currency = 0;
	uint32 amount = 0;
	char sCustomerName[24+1];
	char sTCKN[11+1], sVKN[11+1], sBelgeNo[11+1], sBelgeDate[11+1];
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	if (amount == 0)
	{
		MessageBox(L"Lütfen tutar giriniz!", L"Error", MB_OK);
		return;
	}
	if (cariHesapDlg.DoModal() != IDOK)
		return;

	memset(sCustomerName, 0x00, sizeof(sCustomerName));
	memset(sTCKN, 0x00, sizeof(sTCKN));
	memset(sVKN, 0x00, sizeof(sVKN));
	memset(sBelgeNo, 0x00, sizeof(sBelgeNo));
	memset(sBelgeDate, 0x00, sizeof(sBelgeDate));

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;
		bufferLen = prepare_KasaAvans(&buffer[0], sizeof(buffer), amount, "", "", "");
		AddIntoCommandBatch(L"_prepare_KasaAvans", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		HINT hInt = GetSelectedInterface();
		HTRX hTrx = GetSelectedTransaction();

		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);


		if (cariHesapDlg.m_csCariHesapCustomerName.IsEmpty())
		{
			MessageBox(L"Lütfen Müþteri Adýný giriniz!", L"Error", MB_OK);
			return;
		}
		else
			sprintf((char*)sCustomerName	, CT2A((LPCTSTR)cariHesapDlg.m_csCariHesapCustomerName), cariHesapDlg.m_csCariHesapCustomerName.GetLength());

		if ((cariHesapDlg.m_csCariHesapTCKN.IsEmpty()) && (cariHesapDlg.m_csCariHesapVKN.IsEmpty()))
		{
			MessageBox(L"Lütfen TCKN ya da VKN giriniz!", L"Error", MB_OK);
			return;
		}
		else
		{
			sprintf((char*)sTCKN	, CT2A((LPCTSTR)cariHesapDlg.m_csCariHesapTCKN), cariHesapDlg.m_csCariHesapTCKN.GetLength());
			sprintf((char*)sVKN	, CT2A((LPCTSTR)cariHesapDlg.m_csCariHesapVKN), cariHesapDlg.m_csCariHesapVKN.GetLength());
		}
		if (cariHesapDlg.m_csCariHesapDokumanNo.IsEmpty())
		{
			MessageBox(L"Lütfen Döküman Numarasýný giriniz!", L"Error", MB_OK);
			return;
		}
		else
			sprintf((char*)sBelgeNo	, CT2A((LPCTSTR)cariHesapDlg.m_csCariHesapDokumanNo), cariHesapDlg.m_csCariHesapDokumanNo.GetLength());

		int dayI, monI, yearI, yearItwodigit;
		dayI = cariHesapDlg.m_dateCariHesapDate.GetDay();
		monI = cariHesapDlg.m_dateCariHesapDate.GetMonth();
		yearI = cariHesapDlg.m_dateCariHesapDate.GetYear();
		yearItwodigit = yearI % 100;
		sprintf(sBelgeDate, "%02d%02d%02d", dayI, monI, yearItwodigit);

		if (StartTicket(hInt, &hTrx, TCariHesap))
			return;

		pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		if (retcode = FP3_CariHesap(hInt, hTrx, amount, pstTicket, sCustomerName, sTCKN, sVKN, sBelgeNo, sBelgeDate))
		{
			HandleErrorCode(retcode);
			return;
		}

		DisplayTransaction(pstTicket, false);
	}

}

void CePosDlg::OnBnClickedButtonKasaAvans()
{
	uint16 currency = 0;
	unsigned long long AdvanceType;
	uint32 amount = 0;
	char sCustomerName[24+1];
	char sTCKN[11+1], sVKN[11+1];
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	if (amount == 0)
		return;

	int retcode;
	memset(sCustomerName, 0x00, sizeof(sCustomerName));
	memset(sTCKN, 0x00, sizeof(sTCKN));
	memset(sVKN, 0x00, sizeof(sVKN));
	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;
		//int prepare_KasaAvans( uint8* Buffer, int MaxSize, long amount , char* pCustomerName, char* pTckn, char* pVkn )
		bufferLen = prepare_KasaAvans(&buffer[0], sizeof(buffer), amount, "", "", "");
		AddIntoCommandBatch(L"_prepare_KasaAvans", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		CGetInputDlg* pcInput;

		////////////////////////////////////////////////////////////////////////////////////////////////////////
		pcInput = new CGetInputDlg;
		pcInput->InsertFlag(L"MÜÞTERÝ AVANSI"		, 1, true);
		pcInput->InsertFlag(L"KASA AVANSI"	, 2, false);
		if (pcInput->DoModal(L"PLEASE SELECT ADVANCE TYPE", L"", 4) != IDOK)
			return;
		AdvanceType =  pcInput->m_flagValue;
		delete pcInput;

		HINT hInt = GetSelectedInterface();
		HTRX hTrx = GetSelectedTransaction();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		switch (AdvanceType)
		{
		case 1:

			if (!GetStringInputLn(L"CUSTOMER NAME", sCustomerName, 24))
				return;

			if (!GetStringInputLn(L"Enter TCKN or skip to enter VKN", sTCKN, 11))
				return;
			if (strlen(sTCKN) == 0)
			{
				if (!GetStringInputLn(L"VKN", sVKN, 11))
					return;
			}

			if (StartTicket(hInt, &hTrx, TAvans))
				return;

			pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

			if (retcode = FP3_CustomerAvans(hInt, hTrx, amount, pstTicket, sCustomerName, sTCKN, sVKN, TIMEOUT_DEFAULT))
			{
				HandleErrorCode(retcode);
				return;
			}
			break;
		default:
		case 2:
			if (StartTicket(hInt, &hTrx, TKasaAvans))
				return;

			pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

			if (retcode = FP3_KasaAvans(hInt, hTrx, amount, pstTicket))
			{
				HandleErrorCode(retcode);
				return;
			}

		}

		DisplayTransaction(pstTicket, false);
	}
}

void CePosDlg::OnBnClickedButtonKasaOdeme()
{
	uint16 currency = 0;
	uint32 amount = 0;
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	if (amount == 0)
	{
		MessageBox(L"Enter an Amount!", L"Error", MB_OK);
		return;
	}

	int retcode;

	HTRX hTrx = GetSelectedTransaction();
	HINT hInt = GetSelectedInterface();

	if (StartTicket(hInt, &hTrx, TPayment))
		return;

	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (retcode = FP3_KasaPayment(hInt, hTrx, amount, pstTicket))
	{
		HandleErrorCode(retcode);
		return;
	}

	DisplayTransaction(pstTicket, false);
}

void CePosDlg::OnBnClickedButtonPretotal()
{
	int retcode;

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_Pretotal(&buffer[0], sizeof(buffer));
		AddIntoCommandBatch(L"_prepare_Pretotal", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		HINT hInt = GetSelectedInterface();
		HTRX hTrx = GetSelectedTransaction();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		if (hTrx != 0)
		{
			if (retcode = FP3_Pretotal(hInt, hTrx, pstTicket))
			{
				HandleErrorCode(retcode);
				return;
			}

			DisplayInfo("ARATOPLAM %s", formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL));

			DisplayTransaction(pstTicket, false);
		}
	}
}

void CePosDlg::OnBnClickedButtonTutarArtirim()
{
	uint16 currency = 0;
	uint32 amount = 0;
	char Text[128+1];

	memset(Text, 0, sizeof(Text));
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	if (amount == 0)
		return;

	CItemNo itemNoDlg;
	int retcode;

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();
	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (itemNoDlg.DoModal() == IDOK)
	{
		if (itemNoDlg.m_iItemNo != 0xFFFF)  // Discount on ALL TICKET
			// othervise -1 to get the zero based index of the item
			itemNoDlg.m_iItemNo--;

		if (!GetStringInput(L"ARTTIRIM METNÝ GÝRÝN", Text))
			return;

		if (strlen(Text) > 22)
			Text[22] = NULL;

		if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
		{
			uint8	buffer[1024];
			uint16	bufferLen = 0;

			// start
			bufferLen = prepare_Plus(&buffer[0], sizeof(buffer), amount, itemNoDlg.m_iItemNo);
			AddIntoCommandBatch(L"_prepare_Plus", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
		}
		else
		{
			if (retcode = FP3_Plus(hInt, hTrx, amount , Text, pstTicket, itemNoDlg.m_iItemNo))
			{
				HandleErrorCode(retcode);
				return;
			}

			DisplayTransaction(pstTicket, false);

			if (itemNoDlg.m_iItemNo == 0xFFFF)
			{
				DisplayInfo("%s (%s)\r\n%s\r\n%s %s"
							, "TUTAR ARTIRIM"
							, "TÜM FÝÞ"
							, formatAmount(amount, CURRENCY_TL)
							, "ARATOPLAM"
							, formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL)
						   );
			}
			else
			{
				DisplayInfo("%s (%s %d)\r\n+%s\r\n%s X %s %s"
							, "TUTAR ARTIRIM"
							, "ÜRÜN"
							, itemNoDlg.m_iItemNo
							, formatAmount(amount, CURRENCY_TL)
							, formatCount(pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCount, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCountPrecision, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemUnitType)
							, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].Name
							, formatAmount((uint32)pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemPrice, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCurrencyType)
						   );
			}
		}
	}
}

void CePosDlg::OnBnClickedButtonTutarIndir()
{
	uint16 currency = 0;
	uint32 amount = 0;
	char Text[128+1];

	memset(Text, 0, sizeof(Text));
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	if (amount == 0)
		return;

	CItemNo itemNoDlg;
	int retcode;

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();
	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (itemNoDlg.DoModal() == IDOK)
	{
		if (itemNoDlg.m_iItemNo != 0xFFFF)  // Discount on ALL TICKET
			// othervise -1 to get the zero based index of the item
			itemNoDlg.m_iItemNo--;

		if (!GetStringInput(L"ÝNDÝRÝM METNÝ GÝRÝN", Text))
			return;

		if (strlen(Text) > 22)
			Text[22] = NULL;

		if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
		{
			uint8	buffer[1024];
			uint16	bufferLen = 0;

			// start
			bufferLen = prepare_Minus(&buffer[0], sizeof(buffer), amount, itemNoDlg.m_iItemNo);
			AddIntoCommandBatch(L"_prepare_Minus", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
		}
		else
		{
			if (retcode = FP3_Minus(hInt, hTrx, amount, Text, pstTicket, itemNoDlg.m_iItemNo))
			{
				HandleErrorCode(retcode);
				return;
			}

			DisplayTransaction(pstTicket, false);
			if (itemNoDlg.m_iItemNo == 0xFFFF)
			{
				DisplayInfo("%s (%s)\r\n%s\r\n%s %s"
							, "TUTAR ÝNDÝRÝM"
							, "TÜM FÝÞ"
							, formatAmount(amount, CURRENCY_TL)
							, "ARATOPLAM"
							, formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL)
						   );
			}
			else
			{
				DisplayInfo("%s (%s %d)\r\n-%s\r\n%s X %s %s"
							, "TUTAR ÝNDÝRÝM"
							, "ÜRÜN"
							, itemNoDlg.m_iItemNo
							, formatAmount(amount, CURRENCY_TL)
							, formatCount(pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCount,  pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCountPrecision,  pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemUnitType)
							,  pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].Name
							, formatAmount((uint32) pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemPrice,  pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCurrencyType)
						   );
			}
		}
	}
}

void CePosDlg::OnBnClickedButtonPercentInc()
{
	m_EditControlInput.GetWindowTextW(m_csInput);
	CItemNo itemNoDlg;
	int retcode;
	uint32 changedAmount;
	char Text[128+1];

	memset(Text, 0, sizeof(Text));

	if (itemNoDlg.DoModal() == IDOK)
	{
		if (itemNoDlg.m_iItemNo != 0xFFFF)  // Discount on ALL TICKET
			// othervise -1 to get the zero based index of the item
			itemNoDlg.m_iItemNo--;

		if (!GetStringInput(L"ARTTIRIM METÝN ALANI", Text))
			return;

		if (strlen(Text) > 22)
			Text[22] = NULL;

		if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
		{
			uint8	buffer[1024];
			uint16	bufferLen = 0;

			// start
			bufferLen = prepare_Inc(&buffer[0], sizeof(buffer), (byte)atol(CT2A((LPCTSTR)m_csInput)), itemNoDlg.m_iItemNo);
			AddIntoCommandBatch(L"_prepare_Inc", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
		}
		else
		{
			HINT hInt = GetSelectedInterface();
			HTRX hTrx = GetSelectedTransaction();
			ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

			if (retcode = FP3_Inc(hInt, hTrx, (byte)atol(CT2A((LPCTSTR)m_csInput)), Text, pstTicket, itemNoDlg.m_iItemNo, &changedAmount))
			{
				HandleErrorCode(retcode);
				return;
			}

			DisplayTransaction(pstTicket, false);

			if (itemNoDlg.m_iItemNo == 0xFFFF)
			{
				DisplayInfo("%s (%s)\r\n%s\r\n%s %s"
							, "YÜZDE ARTIRIM"
							, "TÜM FÝÞ"
							, formatAmount(changedAmount, CURRENCY_TL)
							, "ARATOPLAM"
							, formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL)
						   );
			}
			else
			{
				DisplayInfo("%s (%s %d)\r\n+%s\r\n%s X %s %s"
							, "YÜZDE ARTIRIM"
							, "ÜRÜN"
							, itemNoDlg.m_iItemNo
							, formatAmount(changedAmount, CURRENCY_TL)
							, formatCount(pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCount, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCountPrecision, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemUnitType)
							, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].Name
							, formatAmount((uint32)pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemPrice, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCurrencyType)
						   );
			}
		}
	}

	m_csInput.Empty();
	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButtonPercentDec()
{
	m_EditControlInput.GetWindowTextW(m_csInput);
	CItemNo itemNoDlg;
	int retcode;
	uint32 changedAmount;
	char Text[128];

	memset(Text, 0, sizeof(Text));

	if (itemNoDlg.DoModal() == IDOK)
	{
		if (itemNoDlg.m_iItemNo != 0xFFFF)  // Discount on ALL TICKET
			// othervise -1 to get the zero based index of the item
			itemNoDlg.m_iItemNo--;


		if (!GetStringInput(L"ÝNDÝRÝM METÝN ALANI", Text))
			return;

		if (strlen(Text) > 22)
			Text[22] = NULL;

		if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
		{
			uint8	buffer[1024];
			uint16	bufferLen = 0;

			// start
			bufferLen = prepare_Dec(&buffer[0], sizeof(buffer), (byte)atol(CT2A((LPCTSTR)m_csInput)), itemNoDlg.m_iItemNo);
			AddIntoCommandBatch(L"_prepare_Dec", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
		}
		else
		{
			HINT hInt = GetSelectedInterface();
			HTRX hTrx = GetSelectedTransaction();
			ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

			if (retcode = FP3_Dec(hInt, hTrx, (byte)atol(CT2A((LPCTSTR)m_csInput)) , Text, pstTicket, itemNoDlg.m_iItemNo, &changedAmount))
			{
				HandleErrorCode(retcode);
				return;
			}

			DisplayTransaction(pstTicket, false);

			if (itemNoDlg.m_iItemNo == 0xFFFF)
			{
				DisplayInfo("%s (%s)\r\n%s\r\n%s %s"
							, "YÜZDE ÝNDÝRÝM"
							, "TÜM FÝÞ"
							, formatAmount(changedAmount, CURRENCY_TL)
							, "ARATOPLAM"
							, formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL)
						   );
			}
			else
			{
				DisplayInfo("%s (%s %d)\r\n-%s\r\n%s X %s %s"
							, "YÜZDE ÝNDÝRÝM"
							, "ÜRÜN"
							, itemNoDlg.m_iItemNo
							, formatAmount(changedAmount, CURRENCY_TL)
							, formatCount(pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCount, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCountPrecision, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemUnitType)
							, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].Name
							, formatAmount((uint32)pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemPrice, pstTicket->SaleInfo[itemNoDlg.m_iItemNo-1].ItemCurrencyType)
						   );
			}
		}
	}
	m_csInput.Empty();
	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButtonVoidPayment()
{
	m_EditControlInput.GetWindowTextW(m_csInput);
	int retcode;
	uint16 indexOfPayment;
	CPaymentDlg PaymentDlg;
	char display[2048];

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	if (hTrx == NULL)
	{
		MessageBox(L"Please SELECT a Transaction Handle", L"No Transaction Handle Found", MB_OK);
		return;
	}

	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (!m_csInput.GetLength())
	{
		retcode = ReadTransactionFromECR(hInt, hTrx);
		if (retcode != TRAN_RESULT_OK)
		{
			HandleErrorCode(retcode);
			return;
		}

		DisplayTransaction(pstTicket, FALSE);

		if (PaymentDlg.DoModal(&pstTicket->stPayment[0], pstTicket->totalNumberOfPayments) != IDOK)
			return;

		indexOfPayment = PaymentDlg.m_selectedPayment + 1;
	}
	else
		indexOfPayment = (uint16)atol(CT2A((LPCTSTR)m_csInput));

	if (indexOfPayment == 0)
		return;

	if (retcode = FP3_VoidPayment(hInt, hTrx, indexOfPayment - 1, pstTicket))
	{
		HandleErrorCode(retcode);
		return;
	}

	uint32 TicketAmount = pstTicket->TotalReceiptAmount;
	uint32 PaymentAmount = pstTicket->TotalReceiptPayment;

	memset(display, 0x00, sizeof(display));

	switch (pstTicket->ticketType)
	{
	case TAvans:
		sprintf(display, "KASA AVANS TOTAL: %s", formatAmount(pstTicket->KasaAvansAmount, CURRENCY_TL));
		TicketAmount = pstTicket->KasaAvansAmount;
		break;
	case TPayment:
		sprintf(display, "KASA PAYMENT TOTAL: %s", formatAmount(pstTicket->KasaPaymentAmount, CURRENCY_TL));
		TicketAmount = pstTicket->KasaPaymentAmount;
		PaymentAmount = pstTicket->TotalReceiptReversedPayment;
		break;
	case TInvoice:
		sprintf(display, "INVOICE TOTAL : %s", formatAmount(pstTicket->invoiceAmount, CURRENCY_TL));
		TicketAmount = pstTicket->invoiceAmount;
		break;
	case TRefund:
		sprintf(display, "REFUND TOTAL : %s", formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL));
		TicketAmount = pstTicket->TotalReceiptAmount;
		PaymentAmount = pstTicket->TotalReceiptReversedPayment;
		break;
	case TCariHesap:
		sprintf(display, "TOTAL : %s", formatAmount(pstTicket->stPayment[0].payAmount, CURRENCY_TL));
		break;
	default:
		sprintf(display, "TOTAL : %s", formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL));
		TicketAmount = pstTicket->TotalReceiptAmount;
		break;
	}

	if (pstTicket->CashBackAmount)
		sprintf(&display[strlen(display)], "\r\nCASHBACK : %s", formatAmount(pstTicket->CashBackAmount, CURRENCY_TL));
	else
	{
		if ((TTicketType)pstTicket->ticketType == TCariHesap)
			sprintf(&display[strlen(display)], "\r\nREMAIN : %s" , formatAmount(pstTicket->KasaPaymentAmount, CURRENCY_TL));
		sprintf(&display[strlen(display)], "\r\nREMAIN : %s" , formatAmount(TicketAmount - PaymentAmount, CURRENCY_TL));
	}
	if (strlen(display))

		DisplayInfo(display);

	DisplayTransaction(pstTicket, false);
	m_csInput.Empty();
	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButtonOptionFlags()
{
	int retcode;
	CGetInputDlg* pcInput;
	uint64 optionFlagsToSet		= 0;
	uint64 optionFlagsToClear	= 0;
	uint64 activeFlags			= 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"GMP3_OPTION_ECHO_ITEM_DETAILS"		, GMP3_OPTION_ECHO_ITEM_DETAILS, false);
	pcInput->InsertFlag(L"GMP3_OPTION_ECHO_PAYMENT_DETAILS"	, GMP3_OPTION_ECHO_PAYMENT_DETAILS, false);
	pcInput->InsertFlag(L"GMP3_OPTION_ECHO_PRINTER"			, GMP3_OPTION_ECHO_PRINTER, false);
	pcInput->InsertFlag(L"GMP3_OPTION_NO_RECEIPT_LIMIT_CONTROL_FOR_ITEMS"			, GMP3_OPTION_NO_RECEIPT_LIMIT_CONTROL_FOR_ITEMS, false);

	if (pcInput->DoModal(L"OPTION FLAGS TO SET", L"", 3) != IDOK)
		return;
	optionFlagsToSet = pcInput->m_flagValue;
	delete pcInput;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"GMP3_OPTION_ECHO_ITEM_DETAILS"		, GMP3_OPTION_ECHO_ITEM_DETAILS, false);
	pcInput->InsertFlag(L"GMP3_OPTION_ECHO_PAYMENT_DETAILS"	, GMP3_OPTION_ECHO_PAYMENT_DETAILS, false);
	pcInput->InsertFlag(L"GMP3_OPTION_ECHO_PRINTER"			, GMP3_OPTION_ECHO_PRINTER, false);
	if (pcInput->DoModal(L"OPTION FLAGS TO CLEAR", L"", 3) != IDOK)
		return;
	optionFlagsToClear = pcInput->m_flagValue;
	delete pcInput;

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_OptionFlags(&buffer[0], sizeof(buffer), optionFlagsToSet, optionFlagsToClear);
		AddIntoCommandBatch(L"_prepare_OptionFlags", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		retcode = FP3_OptionFlags(GetSelectedInterface(), GetSelectedTransaction(), &activeFlags,  optionFlagsToSet, optionFlagsToClear , TIMEOUT_DEFAULT);
		HandleErrorCode(retcode);
	}
}

void CePosDlg::OnBnClickedButtonCondition()
{
	ST_CONDITIONAL_IF stConditionalIf;
	uint8	buffer[1024];
	uint16	bufferLen = 0;
	CGetInputDlg cIn;

	if (m_TabCommandMode.GetCurSel() != TAB_BATCH_COMMAND_MODE)
		return;

	memset(&stConditionalIf, 0x00, sizeof(stConditionalIf));

	CGetInputDlg* pcInput;

	//////////////////////////////////// ID of the condition ////////////////////////////////////
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"GMP3_CONTITION_ID_PAYMENT_TOTAL_AMOUNT"			, GMP3_CONTITION_ID_PAYMENT_TOTAL_AMOUNT		, false);
	pcInput->InsertFlag(L"GMP3_CONTITION_ID_IS_TICKET_PAYMENT_COMPLETED"	, GMP3_CONTITION_ID_IS_TICKET_PAYMENT_COMPLETED	, false);
	if (pcInput->DoModal(L"CONTITION ID", L"", 4) != IDOK)
		return;
	stConditionalIf.id = (EConditionIds)pcInput->m_flagValue;
	delete pcInput;

	////////////////////////////////////// TestFormule of the condition ////////////////////////////////////
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"Is Equal ?"			, EIsEqual			, true);
	pcInput->InsertFlag(L"Is Bigger ?"			, EIsBigger			, false);
	pcInput->InsertFlag(L"Is EqualOrBigger ?"	, EIsEqualOrBigger	, false);
	pcInput->InsertFlag(L"Is Smaller ?"			, EIsSmaller		, false);
	pcInput->InsertFlag(L"Is EqualOrSmaller ?"	, EIsEqualOrSmaller	, false);
	if (pcInput->DoModal(L"TEST FORMULE", L"", 4) != IDOK)
		return;
	stConditionalIf.eTestFormule = (EConditionTest)pcInput->m_flagValue;
	delete pcInput;


	//////////////////////////////////// Test Value to compare ////////////////////////////////////
	CString csLine = L"0";
	if (cIn.DoModal(L"VALUE TO COMPARE?", csLine, 2) != IDOK)
		return;
	stConditionalIf.ui64TestValue = (uint64)atol(CT2A((LPCTSTR)cIn.m_input));



	////////////////////////////////////// ifTrue_GOTO of the condition ////////////////////////////////////
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"CONDITION_GOTO_NEXT"			, CONDITION_GOTO_NEXT		, true);
	pcInput->InsertFlag(L"CONDITION_GOTO_PRIVOUS"		, CONDITION_GOTO_PRIVOUS	, false);
	pcInput->InsertFlag(L"CONDITION_GOTO_LAST"			, CONDITION_GOTO_LAST		, false);
	pcInput->InsertFlag(L"CONDITION_GOTO_END"			, CONDITION_GOTO_END		, false);
	pcInput->InsertFlag(L"SUB COMMAND LINE ?"			, 0xEEEE					, false);
	if (pcInput->DoModal(L"if TRUE, GOTO?", L"", 4) != IDOK)
		return;
	if (pcInput->m_flagValue == 0xEEEE)
	{
		CString csLine = L"0";
		if (cIn.DoModal(L"GOTO SUBCOMMAND NO?", csLine, 2) != IDOK)
		{
			delete pcInput;
			return;
		}
		stConditionalIf.IfTrue_GOTO = (uint16)atol(CT2A((LPCTSTR)cIn.m_input));
	}
	else
		stConditionalIf.IfTrue_GOTO = (uint16)pcInput->m_flagValue;
	delete pcInput;

	////////////////////////////////////// ifFalse_GOTO of the condition ////////////////////////////////////
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"CONDITION_GOTO_NEXT"			, CONDITION_GOTO_NEXT		, false);
	pcInput->InsertFlag(L"CONDITION_GOTO_PRIVOUS"		, CONDITION_GOTO_PRIVOUS	, false);
	pcInput->InsertFlag(L"CONDITION_GOTO_LAST"			, CONDITION_GOTO_LAST		, true);
	pcInput->InsertFlag(L"CONDITION_GOTO_END"			, CONDITION_GOTO_END		, false);
	pcInput->InsertFlag(L"SUB COMMAND LINE ?"			, 0xEEEE					, false);
	if (pcInput->DoModal(L"if FALSE, GOTO?", L"", 4) != IDOK)
		return;
	if (pcInput->m_flagValue == 0xEEEE)
	{
		CString csLine = L"0";
		if (cIn.DoModal(L"GOTO SUBCOMMAND NO?", csLine, 2) != IDOK)
		{
			delete pcInput;
			return;
		}
		stConditionalIf.IfFalse_GOTO = (uint16)atol(CT2A((LPCTSTR)cIn.m_input));
	}
	else
		stConditionalIf.IfFalse_GOTO = (uint16)pcInput->m_flagValue;
	delete pcInput;

	// start
	bufferLen = prepare_Condition(&buffer[0], sizeof(buffer), &stConditionalIf);
	AddIntoCommandBatch(L"_prepare_Condition", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
}

void CePosDlg::OnBnClickedButtonClose()
{
	int retcode = 0;

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_Close(&buffer[0], sizeof(buffer));
		AddIntoCommandBatch(L"_prepare_Close", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		HTRX hTrx = GetSelectedTransaction();
		HINT hInt = GetSelectedInterface();

		retcode = TransactionHandle_CloseAndRemove(hInt, hTrx);
		HandleErrorCode(retcode);
	}
}

int CePosDlg::ReadDepartmentsAndTaxRatesFromECR(HINT hInt)
{
	int retcode = 0;

	ST_INTERFACE_DATA* pstInterfaceData = GetInterfaceDataPointer(hInt);
	if (pstInterfaceData == NULL)
		return retcode;

	memset(&pstInterfaceData->stDepartments, 0x00, sizeof(pstInterfaceData->stDepartments));
	memset(&pstInterfaceData->stTaxRates, 0x00, sizeof(pstInterfaceData->stTaxRates));
	pstInterfaceData->numberOfTotalTaxRates = 0;
	pstInterfaceData->numberOfTotalDepartments = 0;

	if (retcode = FP3_GetTaxRates(hInt, &pstInterfaceData->numberOfTotalTaxRates, &pstInterfaceData->numberOfReceivedTaxRates, pstInterfaceData->stTaxRates, 8))
	{
		HandleErrorCode(retcode);
		return retcode;
	}

	if (retcode = FP3_GetDepartments(hInt, &pstInterfaceData->numberOfTotalDepartments, &pstInterfaceData->numberOfReceivedDepartments, pstInterfaceData->stDepartments, 12))
	{
		HandleErrorCode(retcode);
		return retcode;
	}

	return retcode;
}

void CePosDlg::DisplayDepartmentsAndTaxRates(HINT hInt)
{
	CButton* idDepartmenButtons[] = { &m_ButtonDepartman1, &m_ButtonDepartman2, &m_ButtonDepartman3, &m_ButtonDepartman4, &m_ButtonDepartman5, &m_ButtonDepartman6, &m_ButtonDepartman7, &m_ButtonDepartman8, &m_ButtonDepartman9, &m_ButtonDepartman10, &m_ButtonDepartman11, &m_ButtonDepartman12 };

	ST_INTERFACE_DATA* pstInterfaceData = GetInterfaceDataPointer(hInt);
	if (pstInterfaceData == NULL)
		return;

	for (int i = 0; i < 12; i++)
	{
		idDepartmenButtons[i]->SetWindowText(L"----");

		if (pstInterfaceData->stDepartments[i].u8TaxIndex >= pstInterfaceData->numberOfTotalTaxRates)
			continue;

		CString cs, cs2;
		cs = CString(pstInterfaceData->stDepartments[i].szDeptName);

		CString csCurrency;
		switch (pstInterfaceData->stDepartments[i].iCurrencyType)
		{
		case CURRENCY_TL:
			csCurrency = _T("TL");
			break;
		case CURRENCY_EU:
			csCurrency = _T("€");
			break;
		case CURRENCY_DOLAR:
			csCurrency = _T("$");
			break;
		default:
			csCurrency = _T("");
			break;
		}

		cs2.Format(L"%s\n(%%%d.%02d)\n%llu.%02llu %s", cs, pstInterfaceData->stTaxRates[pstInterfaceData->stDepartments[i].u8TaxIndex].taxRate / 100, pstInterfaceData->stTaxRates[pstInterfaceData->stDepartments[i].u8TaxIndex].taxRate % 100, pstInterfaceData->stDepartments[i].u64Price / 100, pstInterfaceData->stDepartments[i].u64Price % 100, csCurrency);
		idDepartmenButtons[i]->SetWindowText(cs2);
	}
}


void CePosDlg::OnBnClickedButtonGetDepartments()
{
	int retcode;
	CDepartmentDlg DepartmentDlg;

	HINT hInt = GetSelectedInterface();

	ST_INTERFACE_DATA* pstInterfaceData = GetInterfaceDataPointer(hInt);
	if (pstInterfaceData == NULL)
		return;

	memset(DepartmentDlg.stDepartments, 0x00, sizeof(pstInterfaceData->stDepartments));
	memset(DepartmentDlg.stTaxRates, 0x00, sizeof(pstInterfaceData->stTaxRates));

	if (retcode = FP3_GetTaxRates(hInt, &pstInterfaceData->numberOfTotalTaxRates, &DepartmentDlg.numberOfTotalTaxratesReceived, DepartmentDlg.stTaxRates, 8))
	{
		HandleErrorCode(retcode);
		return;
	}

	if (retcode = FP3_GetDepartments(hInt, &pstInterfaceData->numberOfTotalDepartments, &DepartmentDlg.numberOfTotalDepartmentsReceived, DepartmentDlg.stDepartments, 12))
	{
		HandleErrorCode(retcode);
		return;
	}

	if (DepartmentDlg.DoModal() != IDOK)
		return;

	CPasswordDlg PasswordDlg;
	if (PasswordDlg.DoModal(L"YÖNETÝCÝ ÞÝFRESÝ") != IDOK)
		return;

	retcode = FP3_SetDepartments(hInt, DepartmentDlg.stDepartments, 12, CT2A((LPCTSTR)PasswordDlg.m_Password));
	if (retcode == TRAN_RESULT_OK)
	{
		retcode = ReadDepartmentsAndTaxRatesFromECR(hInt);
		DisplayDepartmentsAndTaxRates(hInt);
	}

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonSelectCashier()
{
	int retcode;
	uint8 numberOfTotalRecordsReceived;
	CCashierDlg dlgCashier;

	dlgCashier.m_hInt = GetSelectedInterface();
	memset(dlgCashier.stCashierTable, 0x00, sizeof(dlgCashier.stCashierTable));
	if (retcode = FP3_GetCashierTable(dlgCashier.m_hInt, &dlgCashier.numberOfTotalCashiers, &numberOfTotalRecordsReceived, dlgCashier.stCashierTable, sizeof(dlgCashier.stCashierTable) / sizeof(ST_CASHIER), &dlgCashier.activeCashier))
	{
		HandleErrorCode(retcode);
		return;
	}

	if (dlgCashier.DoModal() != IDOK)
		return;

	HandleErrorCode(dlgCashier.retcode);

	if (dlgCashier.retcode == TRAN_RESULT_OK)
		Echo();
}

int CePosDlg::ReadCurrencyFromECR(HINT hInt)
{
	int retcode = 0;
	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);
	if (ptr == NULL)
		return retcode;

	memset(ptr->stExchangeProfileTable, 0x00, sizeof(ptr->stExchangeProfileTable));
	if (retcode = FP3_GetCurrencyProfile(hInt, ptr->stExchangeProfileTable))
	{
		HandleErrorCode(retcode);
		return retcode;
	}

	return retcode;
}

void CePosDlg::DisplayCurrency(HINT hInt)
{
	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);
	if (ptr == NULL)
		return;
	uint8 index = 0;

	m_comboBoxCurrency.ResetContent();
	m_comboBoxCurrency.InsertString(0, L"---");
	m_comboBoxCurrency.SetItemData(0, 0);

	m_comboBoxCurrency.InsertString(1, L"TL");
	m_comboBoxCurrency.SetItemData(1, CURRENCY_TL);

	/*	for( int i=0;i<ptr->numberOfReceivedExchangeRates;i++ )
		{
			CString cs;
			cs.Format( L"%c%c%c 1%c=%d.%02dTL"	, ptr->stExchangeTable[i].prefix[0], ptr->stExchangeTable[i].prefix[1], ptr->stExchangeTable[i].prefix[2]
				, ptr->stExchangeTable[i].sign[0]
				, ptr->stExchangeTable[i].rate/100
				, ptr->stExchangeTable[i].rate%100
				);

			m_comboBoxCurrency.InsertString(i+2, cs);
			m_comboBoxCurrency.SetItemData (i+2, ptr->stExchangeTable[i].code );
		}
		*/

	index = 2;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < ptr->stExchangeProfileTable[i].NumberOfCurrency; j++)
		{
			CString cs;
			int a, b;

			a = (int)ptr->stExchangeProfileTable[i].ExchangeRecords[j].rate / (10000);
			b = (int)ptr->stExchangeProfileTable[i].ExchangeRecords[j].rate % (10000);
			//cs.Format( L"%c%c%c %c%c%c=%d.%04dTL %s"
			cs.Format(L"%0.3s %0.3s=%d.%04dTL %s"
					  , (CString)ptr->stExchangeProfileTable[i].ExchangeRecords[j].prefix //, ptr->stExchangeProfileTable[i].ExchangeRecords[j].prefix[1], ptr->stExchangeProfileTable[i].ExchangeRecords[j].prefix[2]
					  , (CString)ptr->stExchangeProfileTable[i].ExchangeRecords[j].sign //, ptr->stExchangeProfileTable[i].ExchangeRecords[j].sign[1], ptr->stExchangeProfileTable[i].ExchangeRecords[j].sign[2]
					  , a , b, (CString)ptr->stExchangeProfileTable[i].ProfileName);

			m_comboBoxCurrency.InsertString(index, cs);
			m_comboBoxCurrency.SetItemData(index++, ptr->stExchangeProfileTable[i].ExchangeRecords[j].code);
		}
	}

	m_comboBoxCurrency.SetCurSel(0);
}

void CePosDlg::OnBnClickedButtonCurrency()
{
	HINT hInt = GetSelectedInterface();
	if (ReadCurrencyFromECR(hInt) == TRAN_RESULT_OK)
		DisplayCurrency(hInt);
}

void CePosDlg::KeyboardEntry(CString input)
{
	int pointLocation;
	m_EditControlInput.GetWindowTextW(m_csInput);

	pointLocation = m_csInput.Find(L".");

	// ikinci noktaya izin verme
	if (input == L".")
		if (pointLocation >= 0)
			return;

	if (pointLocation >= 0)
	{
		if (m_csInput.GetLength() - pointLocation > 2)
			return;
	}

	m_csInput = m_csInput + input;

	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButtonJumpEcrForSinglePayment()
{

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_JumpToECR(&buffer[0], sizeof(buffer), GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT);
		AddIntoCommandBatch(L"_prepare_JumpToECR", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		HINT hInt = GetSelectedInterface();
		HTRX hTrx = GetSelectedTransaction();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		DisplayInfo("%s", "PLEASE USE ECRPOS FOR PAYMENT\r\nWAITING RESPONSE...");

		int retcode = FP3_JumpToECR(hInt, hTrx, GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT, pstTicket, TIMEOUT_DEFAULT);

		if (retcode != TRAN_RESULT_OK)
			HandleErrorCode(retcode);
		else
		{
			DisplayTransaction(pstTicket, false);

			char display[512];

			sprintf(display, "TOPLAM : %s", formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL));
			if (pstTicket->CashBackAmount)
				sprintf(&display[strlen(display)], "\r\nP.ÜSTÜ : %s", formatAmount(pstTicket->CashBackAmount, CURRENCY_TL));
			else if (pstTicket->TotalReceiptAmount)
				sprintf(&display[strlen(display)], "\r\nKALAN : %s" , formatAmount(pstTicket->TotalReceiptAmount - pstTicket->TotalReceiptPayment, CURRENCY_TL));
			else
				sprintf(&display[strlen(display)], "\r\nÖDENEN : %s" , formatAmount(pstTicket->TotalReceiptPayment, CURRENCY_TL));
			DisplayInfo(display);
		}
	}
}

void CePosDlg::OnBnClickedButtonSetuApplicationCommand()
{
	int retcode ;
	uint8  commandBuffer[1024*16];
	uint16 commandBufferLen = GetBatchCommand(commandBuffer);
	char uApplicationName[128];
	char functionName[128];
	uint32 uApplicationId = 0;
	uint32 functionId = 0;
	uint32 functionFlags = 0;
	uint32 functionVersion = 1;

	strcpy(uApplicationName, "uAPP01");
	if (!GetStringInput(L"uAPPLICATION NAME?", uApplicationName))
		return;

	if (!GetIntegerInput(L"uAPPLICATION ID?", (int*)&uApplicationId))
		return;

	if (uApplicationId == 0)
	{
		if (MessageBox(L"This will Delete uApplication. Confirm?", L"Delete uApplication", MB_OKCANCEL) != IDOK)
			return;
	}
	else
	{
		strcpy(functionName, "Function 1");
		if (!GetStringInput(L"FUNCTION NAME?", functionName))
			return;

		if (!GetIntegerInput(L"FUNCTION ID?", (int*)&functionId))
			return;

		if (!GetIntegerInput(L"FUNCTION VERSION?", (int*)&functionVersion))
			return;

		////////////////////////////////////////////////////////////////////////////////////////////////////////
		CGetInputDlg* pcInput;
		pcInput = new CGetInputDlg;
		pcInput->InsertFlag(L"DELETE EXISTING FUNCTIONS"	, 0x0001, false);
		if (pcInput->DoModal(L"FUNCTION FLAGS ?", L"", 4) != IDOK)
			return;
		functionFlags = (uint32)pcInput->m_flagValue;
		delete pcInput;
	}

	retcode = FP3_SetuApplicationFunction(GetSelectedInterface(), (uint8*)uApplicationName, uApplicationId, (uint8*)functionName, functionId, functionVersion, functionFlags, commandBuffer, commandBufferLen, "0000");

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonSetCommScenario()
{

}

void CePosDlg::OnBnClickedButtonGetInput()
{
#define FLAG_GETDIALOG_TYPE_TEXT		0x0001
#define FLAG_GETDIALOG_TYPE_INTEGER		0x0002
#define FLAG_GETDIALOG_TYPE_DATE		0x0004
#define FLAG_GETDIALOG_TYPE_HOUR		0x0008
#define FLAG_GETDIALOG_TYPE_AMOUNT		0x0010
#define FLAG_GETDIALOG_TYPE_MENU		0x0020
#define FLAG_GETDIALOG_TYPE_PASSWORD	0x0040
#define FLAG_GETDIALOG_TYPE_MSGBOX		0x0080
#define FLAG_GETDIALOG_TYPE_CARPLATE	0x1000
#define FLAG_GETDIALOG_TYPE_BARCODE		0x2000

	int retcode = TRAN_RESULT_OK;
	CGetInputDlg* pcInput;
	uint32 fInputType = 0;
	int bufferLen;
	uint8 buffer[1024*4];
	uint32 GL_Dialog_retcode = TRAN_RESULT_OK;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"TEXT"		, FLAG_GETDIALOG_TYPE_TEXT		, false);
	pcInput->InsertFlag(L"INTEGER"		, FLAG_GETDIALOG_TYPE_INTEGER	, true);
	pcInput->InsertFlag(L"DATE"		, FLAG_GETDIALOG_TYPE_DATE		, false);
	pcInput->InsertFlag(L"HOUR"		, FLAG_GETDIALOG_TYPE_HOUR		, false);
	pcInput->InsertFlag(L"AMOUNT"		, FLAG_GETDIALOG_TYPE_AMOUNT	, false);
	pcInput->InsertFlag(L"MENU"		, FLAG_GETDIALOG_TYPE_MENU		, false);
	pcInput->InsertFlag(L"PASSWORD"	, FLAG_GETDIALOG_TYPE_PASSWORD	, false);
	pcInput->InsertFlag(L"MSG BOX"		, FLAG_GETDIALOG_TYPE_MSGBOX	, false);
	pcInput->InsertFlag(L"CAR PLATE"	, FLAG_GETDIALOG_TYPE_CARPLATE	, false);
	pcInput->InsertFlag(L"BARCODE"	, FLAG_GETDIALOG_TYPE_BARCODE	, false);

	if (pcInput->DoModal(L"GET INPUT TYPE ?", L"", 4) != IDOK)
		return;
	fInputType = (uint32)pcInput->m_flagValue;
	delete pcInput;

	if (fInputType & FLAG_GETDIALOG_TYPE_TEXT)
	{
		char value[24] = {"abcd"};
		if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
		{
			retcode = GetDialogInput_Text(&GL_Dialog_retcode, 0x0FFFFF, "TEXT ENTRY TITLE", "TEXT", "/c/c/c/c/c/c", value, sizeof(value) - 1, 30000);
			if (retcode == TRAN_RESULT_OK)
				if (GL_Dialog_retcode == TRAN_RESULT_OK)
					DisplayInfo("%s", value);
		}
		else
		{
			bufferLen = prepare_Text(buffer, sizeof(buffer), 0x0FFFFF, "TEXT ENTRY TITLE", "TEXT", "/c/c/c/c/c/c", value, 30000);
			AddIntoCommandBatch(L"_prepare_Text", GMP3_EXT_DEVICE_GET_DATA_REQ, buffer, bufferLen);
		}
	}
	else if (fInputType & FLAG_GETDIALOG_TYPE_INTEGER)
	{
		char value[24] = {"1234"};
		if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
		{
			retcode = GetDialogInput_Text(&GL_Dialog_retcode, 0x0FFFFF, "INTEGER ENTRY TITLE", "INTEGER", "/d/d/d/d/d/d", value, sizeof(value) - 1, 30000);
			if (retcode == TRAN_RESULT_OK)
				if (GL_Dialog_retcode == TRAN_RESULT_OK)
					DisplayInfo("%s", value);
		}
		else
		{
			bufferLen = prepare_Text(buffer, sizeof(buffer), 0x0FFFFF, "INTEGER ENTRY TITLE", "INTEGER", "/d/d/d/d/d/d", value, 30000);
			AddIntoCommandBatch(L"_prepare_Text", GMP3_EXT_DEVICE_GET_DATA_REQ, buffer, bufferLen);
		}
	}
	else if (fInputType & FLAG_GETDIALOG_TYPE_DATE)
	{
		ST_DATE_TIME value;
		memset(&value, 0x00, sizeof(value));

		CTime time = CTime::GetCurrentTime();
		value.day		= time.GetDay();
		value.month		= time.GetMonth();
		value.year		= time.GetYear();

		if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
		{
			retcode = GetDialogInput_Date(&GL_Dialog_retcode, 0x0FFFFF, "DATE ENTRY TITLE", "DATE (D/M/Y)", "d/m/y", &value, sizeof(value), 30000);
			if (retcode == TRAN_RESULT_OK)
				if (GL_Dialog_retcode == TRAN_RESULT_OK)
					DisplayInfo("%02d/%02d/%04d", value.day, value.month, value.year);
		}
		else
		{
			bufferLen = prepare_Date(buffer, sizeof(buffer), 0x0FFFFF, "DATE ENTRY TITLE", "DATE (D/M/Y)", "d/m/y", &value, 30000);
			AddIntoCommandBatch(L"_prepare_Date", GMP3_EXT_DEVICE_GET_DATA_REQ, buffer, bufferLen);
		}
	}
	else if (fInputType & FLAG_GETDIALOG_TYPE_HOUR)
	{
		ST_DATE_TIME value;
		memset(&value, 0x00, sizeof(value));

		CTime time = CTime::GetCurrentTime();
		value.second	= time.GetSecond();
		value.minute	= time.GetMinute();
		value.hour		= time.GetHour();

		if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
		{
			retcode = GetDialogInput_Date(&GL_Dialog_retcode, 0x0FFFFF, "TIME ENTRY TITLE", "TIME (H:M:S)", "H:M:S", &value, sizeof(value), 30000);
			if (retcode == TRAN_RESULT_OK)
				if (GL_Dialog_retcode == TRAN_RESULT_OK)
					DisplayInfo("%02d:%02d:%02d", value.hour, value.minute, value.second);
		}
		else
		{
			bufferLen = prepare_Date(buffer, sizeof(buffer), 0x0FFFFF, "DATE ENTRY TITLE", "DATE (D/M/Y)", "d/m/y", &value, 30000);
			AddIntoCommandBatch(L"_prepare_Date", GMP3_EXT_DEVICE_GET_DATA_REQ, buffer, bufferLen);
		}
	}
	else if (fInputType & FLAG_GETDIALOG_TYPE_AMOUNT)
	{
		char value[16]	= {"123456"};
		char symbol[16] = {"\x9E\x00"};		// TL
		uint8 align = 2;  // 0:GL_ALIGN_CENTER   1:GL_ALIGN_LEFT  2:GL_ALIGN_RIGHT	4:GL_ALIGN_TOP  8:GL_ALIGN_BOTTOM

		if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
		{
			retcode = GetDialogInput_Amount(&GL_Dialog_retcode, 0x0FFFFF, "AMOUNT ENTRY TITLE", "AMOUNT", "/d/d/d/d/d/d./D/D", value, 12, symbol, align, 30000);
			if (retcode == TRAN_RESULT_OK)
				if (GL_Dialog_retcode == TRAN_RESULT_OK)
					DisplayInfo("%s", value);
		}
		else
		{
			bufferLen = prepare_Amount(buffer, sizeof(buffer), 0x0FFFFF, "AMOUNT ENTRY TITLE", "AMOUNT", "/d/d/d/d/d/d./D/D", value, 12, symbol, align, 30000);
			AddIntoCommandBatch(L"_prepare_Amount", GMP3_EXT_DEVICE_GET_DATA_REQ,  buffer, bufferLen);
		}
	}
	else if (fInputType & FLAG_GETDIALOG_TYPE_BARCODE)
	{
		int Count = 1;
		int tmo = 10;
		if (!GetIntegerInput(L"NUMBER OF BARCODE TO READ?", (int*)&Count))
			return;
		if (!GetIntegerInput(L"TIMEOUT?", (int*)&tmo))
			return;
		retcode = GetDialogBarcode(&GL_Dialog_retcode, Count , buffer, tmo);
		if (retcode == TRAN_RESULT_OK)
			if (GL_Dialog_retcode == TRAN_RESULT_OK)
			{
				DisplayInfo("%s", buffer);
			}

	}
	else if (fInputType & FLAG_GETDIALOG_TYPE_MENU)
	{
		uint32 selected = 0;
		char* menu[24+1];
		char menuItems[24+1][24+1];
		uint8 menuType = 0;
		int i;

		// type Of the menü
		pcInput = new CGetInputDlg;
		pcInput->InsertFlag(L"MENU"				, 0, true);
		pcInput->InsertFlag(L"ICON MENU"			, 1, false);
		pcInput->InsertFlag(L"ICON BUTTON"			, 2, false);
		pcInput->InsertFlag(L"CHOICE MENU"			, 3, false);
		pcInput->InsertFlag(L"MULTI CHOICE MENU"	, 4, false);
		pcInput->InsertFlag(L"LIST"				, 5, false);
		if (pcInput->DoModal(L"TYPE OF THE MENU ?", L"", 4) != IDOK)
			return;
		menuType = (uint8)pcInput->m_flagValue;
		delete pcInput;

		if ((menuType == 1) || (menuType == 2))
		{
			// icon menu items are 2 strings...
			for (i = 0; i < 4; i++)
			{
				sprintf(menuItems[i*2], "GMP MENU ITEM %d", i + 1);
				menu[i*2] = menuItems[i*2];

				sprintf(menuItems[i*2+1], "iconfilename%d", i + 1);
				menu[i*2+1] = menuItems[i*2+1];
			}
			// must be null
			menu[i*2] = 0;
		}
		else
		{
			for (i = 0; i < 4; i++)
			{
				sprintf(menuItems[i], "GMP MENU ITEM %d", i + 1);
				menu[i] = menuItems[i];
			}

			// must be null
			menu[i] = 0;
		}

		if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
		{
			retcode = GetDialogInput_Menu(&GL_Dialog_retcode, 0x0FFFFF, menuType, "GMP3 MENU", menu, &selected, 3 , 30000);
			if (retcode == TRAN_RESULT_OK)
				if (GL_Dialog_retcode == TRAN_RESULT_OK)
					DisplayInfo("Selected Index = 0x%04X", selected);
		}
		else
		{
			bufferLen = prepare_Menu(buffer, sizeof(buffer), 0x0FFFFF, menuType, "GMP3 MENU", menu, &selected, 3 , 30000);
			AddIntoCommandBatch(L"_prepare_Menu", GMP3_EXT_DEVICE_GET_DATA_REQ, buffer, bufferLen);
		}
	}
	else if (fInputType & FLAG_GETDIALOG_TYPE_PASSWORD)
	{
		uint32 GL_Dialog_retcode;
		char value[24] = {"1234"};

		if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
		{
			retcode = GetDialogInput_Password(&GL_Dialog_retcode, 0x0FFFFF, "PASSWORD", "ÞÝFRE", "/d/d/d/d", value, sizeof(value) - 1, 30000);
			if (retcode == TRAN_RESULT_OK)
				if (GL_Dialog_retcode == TRAN_RESULT_OK)
					DisplayInfo("%s", value);
		}
		else
		{
			bufferLen = prepare_Password(buffer, sizeof(buffer), 0x0FFFFF, "PASSWORD", "ÞÝFRE", "/d/d/d/d", value, sizeof(value) - 1, 30000);
			AddIntoCommandBatch(L"_prepare_Password", GMP3_EXT_DEVICE_GET_DATA_REQ, buffer, bufferLen);
		}
	}
	else if (fInputType & FLAG_GETDIALOG_TYPE_MSGBOX)
	{
		uint32 GL_Dialog_retcode;

		if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
		{
			retcode = GetDialogInput_MsgBox(&GL_Dialog_retcode, 0x0FFFFF,  "Message Box", "ONAYLIYOR MUSUNUZ?", 1, 3, 30000);
			if (retcode == TRAN_RESULT_OK)
				DisplayInfo("%s", (GL_Dialog_retcode == TRAN_RESULT_OK) ? "OK" : "NOK");
		}
		else
		{
			bufferLen = prepare_MsgBox(buffer, sizeof(buffer), 0x0FFFFF, "Message Box", "ONAYLIYOR MUSUNUZ?", 1, 3, 30000);
			AddIntoCommandBatch(L"_prepare_MsgBox", GMP3_EXT_DEVICE_GET_DATA_REQ, buffer, bufferLen);
		}
	}
	else if (fInputType & FLAG_GETDIALOG_TYPE_CARPLATE)
	{
		char value[24];
		strcpy(value, "34ABC1234");

		if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
		{
			retcode = GetDialogInput_Text(&GL_Dialog_retcode, 0x0FFFFF, "PLATE ENTRY TITLE", "PLAKA", "/d/d /c/c/c /d/d/d/d", value, sizeof(value) - 1, 30000);
			if (retcode == TRAN_RESULT_OK)
				if (GL_Dialog_retcode == TRAN_RESULT_OK)
					DisplayInfo("%s", value);
		}
		else
		{
			bufferLen = prepare_Text(buffer, sizeof(buffer), 0x0FFFFF, "PLATE ENTRY TITLE", "PLAKA", "/d/d /c/c/c /d/d/d/d", value, 30000);
			AddIntoCommandBatch(L"_prepare_Text", GMP3_EXT_DEVICE_GET_DATA_REQ, buffer, bufferLen);
		}
	}
	else
		return;

	if (GL_Dialog_retcode != TRAN_RESULT_OK)
		DisplayInfo("GL_Dialog_retcode = %04X", GL_Dialog_retcode);

	if (retcode != TRAN_RESULT_OK)
		HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonJumpEcrForCompletePayment()
{
	CGetInputDlg* pcInput;
	uint64 optionFlagsToSet = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	pcInput = new CGetInputDlg;
	pcInput->InsertFlag(L"GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT"			, GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT			, false);
	pcInput->InsertFlag(L"GMP3_OPTION_RETURN_AFTER_COMPLETE_PAYMENT"		, GMP3_OPTION_RETURN_AFTER_COMPLETE_PAYMENT			, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_ITEM"					, GMP3_OPTION_DONT_ALLOW_NEW_ITEM					, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_VOID_ITEM"				, GMP3_OPTION_DONT_ALLOW_VOID_ITEM				 	, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_VOID_PAYMENT"				, GMP3_OPTION_DONT_ALLOW_VOID_PAYMENT				, false);
	pcInput->InsertFlag(L"GMP3_OPTION_CONTINUE_IN_OFFLINE_MODE"			, GMP3_OPTION_CONTINUE_IN_OFFLINE_MODE				, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_SEND_TRANSACTION_RESULT"		, GMP3_OPTION_DONT_SEND_TRANSACTION_RESULT			, false);

	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_TL"		, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_TL		 	, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_EXCHANGE", GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_EXCHANGE 	, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_BANKCARD"		, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_BANKCARD		, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_YEMEKCEKI"	, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_YEMEKCEKI	 	, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_MOBILE"		, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_MOBILE		 	, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_HEDIYECEKI"	, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_HEDIYECEKI	 	, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_IKRAM"		, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_IKRAM		 	, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ODEMESIZ"		, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ODEMESIZ		, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_KAPORA"		, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_KAPORA		 	, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_PUAN"			, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_PUAN			, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CEK"			, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CEK			    , false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ACIK_HESAP"	, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_PUAN			, false);
	pcInput->InsertFlag(L"GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT (ALL)"		, GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT				 	, false);

	if (pcInput->DoModal(L"JUMP OPTION FLAGS TO SET", L"", 3) != IDOK)
		return;
	optionFlagsToSet = pcInput->m_flagValue;
	delete pcInput;


	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_JumpToECR(&buffer[0], sizeof(buffer), optionFlagsToSet);
		AddIntoCommandBatch(L"_prepare_JumpToECR", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		HINT hInt = GetSelectedInterface();
		HTRX hTrx = GetSelectedTransaction();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		DisplayInfo("%s", "PLEASE USE ECRPOS FOR PAYMENT\r\nWAITING RESPONSE...");

		int retcode = FP3_JumpToECR(hInt, hTrx, optionFlagsToSet, pstTicket , TIMEOUT_DEFAULT);

		if (retcode != TRAN_RESULT_OK)
			HandleErrorCode(retcode);
		else
		{
			DisplayTransaction(pstTicket, false);

			char display[512];

			sprintf(display, "TOPLAM : %s", formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL));
			if (pstTicket->CashBackAmount)
				sprintf(&display[strlen(display)], "\r\nP.ÜSTÜ : %s", formatAmount(pstTicket->CashBackAmount, CURRENCY_TL));
			else if (pstTicket->TotalReceiptAmount)
				sprintf(&display[strlen(display)], "\r\nKALAN : %s" , formatAmount(pstTicket->TotalReceiptAmount - pstTicket->TotalReceiptPayment, CURRENCY_TL));
			else
				sprintf(&display[strlen(display)], "\r\nÖDENEN : %s" , formatAmount(pstTicket->TotalReceiptPayment, CURRENCY_TL));
			DisplayInfo(display);
		}
	}
}

void CePosDlg::OnBnClickedButtonDelete()
{
	m_EditControlInput.GetWindowTextW(m_csInput);

	if (!m_csInput.GetLength())
		return;

	m_csInput = m_csInput.Left(m_csInput.GetLength() - 1);

	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButton1()
{
	KeyboardEntry(L"1");
}

void CePosDlg::OnBnClickedButton2()
{
	KeyboardEntry(L"2");
}

void CePosDlg::OnBnClickedButton3()
{
	KeyboardEntry(L"3");
}

void CePosDlg::OnBnClickedButton4()
{
	KeyboardEntry(L"4");
}

void CePosDlg::OnBnClickedButton5()
{
	KeyboardEntry(L"5");
}

void CePosDlg::OnBnClickedButton6()
{
	KeyboardEntry(L"6");
}

void CePosDlg::OnBnClickedButton7()
{
	KeyboardEntry(L"7");
}

void CePosDlg::OnBnClickedButton8()
{
	KeyboardEntry(L"8");
}

void CePosDlg::OnBnClickedButton9()
{
	KeyboardEntry(L"9");
}

void CePosDlg::OnBnClickedButton00()
{
	KeyboardEntry(L"00");
}

void CePosDlg::OnBnClickedButton0()
{
	KeyboardEntry(L"0");
}

void CePosDlg::OnBnClickedButtonPaymentCash()
{
	int retcode;
	char display[256];
	memset(display, 0x00, sizeof(display));

	uint16 currency = 0;
	uint32 amount = 0;
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);

	ST_PAYMENT_REQUEST stPaymentRequest[1];
	memset(stPaymentRequest, 0, sizeof(ST_PAYMENT_REQUEST));

	stPaymentRequest[0].typeOfPayment			= PAYMENT_CASH_TL;
	stPaymentRequest[0].subtypeOfPayment		= NULL;
	stPaymentRequest[0].payAmount				= amount;
	stPaymentRequest[0].payAmountCurrencyCode	= currency;

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();
	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	retcode = FP3_Payment(hInt, hTrx, &stPaymentRequest[0], pstTicket);
	if (retcode == TRAN_RESULT_OK)
	{
		if (pstTicket->TotalReceiptAmount == 0)
			pstTicket->TotalReceiptAmount = pstTicket->invoiceAmount;

		sprintf(display, "TOPLAM : %s", formatAmount(pstTicket->TotalReceiptAmount, CURRENCY_TL));

		if (pstTicket->CashBackAmount)
			sprintf(&display[strlen(display)], "\r\nP.ÜSTÜ : %s", formatAmount(pstTicket->CashBackAmount, CURRENCY_TL));
		else if (pstTicket->TotalReceiptAmount)
			sprintf(&display[strlen(display)], "\r\nKALAN : %s" , formatAmount(pstTicket->TotalReceiptAmount - pstTicket->TotalReceiptPayment, CURRENCY_TL));
		else
			sprintf(&display[strlen(display)], "\r\nÖDENEN : %s" , formatAmount(pstTicket->TotalReceiptPayment, CURRENCY_TL));

		DisplayTransaction(pstTicket, false);
	}

	if (strlen(display))
		DisplayInfo(display);
	else if (retcode != TRAN_RESULT_OK)
		HandleErrorCode(retcode);

	m_csTtemCount.Empty();
}

void CePosDlg::OnBnClickedButtonPoint()
{
	KeyboardEntry(L".");
}

BOOL CePosDlg::PreTranslateMessage(MSG* pMsg)
{
	CString cs;

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_NUMPAD0:
		case VK_NUMPAD1:
		case VK_NUMPAD2:
		case VK_NUMPAD3:
		case VK_NUMPAD4:
		case VK_NUMPAD5:
		case VK_NUMPAD6:
		case VK_NUMPAD7:
		case VK_NUMPAD8:
		case VK_NUMPAD9:
			cs.Format(L"%c", (char) pMsg->wParam - 0x30);
			KeyboardEntry(cs);
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			cs.Format(L"%c", (char) pMsg->wParam);
			KeyboardEntry(cs);
			break;

		case 0xBE: // '.'
		case VK_DECIMAL:
			cs.Format(L"%c", '.');
			KeyboardEntry(cs);
			break;

		case VK_MULTIPLY:
		case 'x':
		case 'X':
			OnBnClickedButtonMultiply();

		case VK_DELETE:
			m_csInput.Empty();
			m_EditControlInput.SetWindowTextW(m_csInput);
			break;

		case VK_RETURN:
			m_EditControlInput.GetWindowTextW(m_csInput);
			if (m_csInput.GetLength())
			{
				OnBnClickedButtonPlu();
				m_csInput.Empty();
				m_EditControlInput.SetWindowTextW(m_csInput);
				return true;
			}
			break;

		case VK_BACK:
			OnBnClickedButtonDelete();
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

HBRUSH CePosDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{

	case CTLCOLOR_EDIT:
	case CTLCOLOR_MSGBOX:
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkColor(RGB(255, 255, 255));
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	}

	return hbr;
}

void CePosDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// Free the space allocated for the background brush
	delete m_pEditBkBrush;
	delete myFont1;
	delete myFont2;
	delete myFont3;
	delete buttonFont;
	delete buttonFontBig;
}

void CePosDlg::OnBnClickedButtonMultiply()
{
	CString csTmp;

	m_EditControlInput.GetWindowTextW(m_csInput);

	m_csTtemCount = m_csInput;
	m_csInput.Empty();
	csTmp.Format(L"%s X ", m_csTtemCount);

	m_ListControlMainDisplay.SetWindowTextW(csTmp);

	m_EditControlInput.SetWindowTextW(m_csInput);
}

void CePosDlg::OnBnClickedButtonGetPlu()
{
	m_EditControlInput.GetWindowTextW(m_csInput);
	int retcode;

	if (!m_csInput.GetLength())
		return;

	ST_PLU_RECORD stPluRecord;
	ST_PLU_GROUP_RECORD stPluGroupRecord[4];
	int numberOfGroups = sizeof(stPluGroupRecord) / sizeof(ST_PLU_GROUP_RECORD);

	memset(&stPluRecord, 0, sizeof(stPluRecord));
	memset(&stPluGroupRecord, 0, sizeof(stPluGroupRecord));

	m_listPrinterOutput.ResetContent();

	if (retcode = FP3_GetPLU(GetSelectedInterface(), CT2A((LPCTSTR)m_csInput), &stPluRecord, stPluGroupRecord, numberOfGroups))
	{
		HandleErrorCode(retcode);
	}
	else
	{
		CListBoxPrintf(&m_listPrinterOutput, "     PLU ÜRÜN ARAMA     ");
		CListBoxPrintf(&m_listPrinterOutput, "________________________");
		CListBoxPrintf(&m_listPrinterOutput, "BARCODE   : %s", stPluRecord.barcode);
		CListBoxPrintf(&m_listPrinterOutput, "ADI       : %s", stPluRecord.name);
		CListBoxPrintf(&m_listPrinterOutput, "KISIM INX : %d", stPluRecord.deptIndex);
		CListBoxPrintf(&m_listPrinterOutput, "BIRIM TIP : %d", stPluRecord.unitType);
		CListBoxPrintf(&m_listPrinterOutput, "DEÐÝÞTÝRME: %08X", stPluRecord.lastModified);
		CListBoxPrintf(&m_listPrinterOutput, "FLAG      : %08X", stPluRecord.flag);
		CListBoxPrintf(&m_listPrinterOutput, "FIYAT(%03d): %ld.%ld", stPluRecord.currency[0], stPluRecord.amount[0] / 100, stPluRecord.amount[0] % 100);
		CListBoxPrintf(&m_listPrinterOutput, "FIYAT(%03d): %ld.%ld", stPluRecord.currency[1], stPluRecord.amount[1] / 100, stPluRecord.amount[1] % 100);
		CListBoxPrintf(&m_listPrinterOutput, "FIYAT(%03d): %ld.%ld", stPluRecord.currency[2], stPluRecord.amount[2] / 100, stPluRecord.amount[2] % 100);

		for (int i = 0; i < numberOfGroups; i++)
		{
			if (!stPluGroupRecord[i].groupId)
				continue;

			CListBoxPrintf(&m_listPrinterOutput, " ");
			CListBoxPrintf(&m_listPrinterOutput, "GRUP %d", i);
			CListBoxPrintf(&m_listPrinterOutput, "ID  : %d", stPluGroupRecord[i].groupId);
			CListBoxPrintf(&m_listPrinterOutput, "ADI : %s", stPluGroupRecord[i].name);
			CListBoxPrintf(&m_listPrinterOutput, "FLAG: %08X", stPluGroupRecord[i].groupFlag);
		}
	}

	m_csInput.Empty();
	m_csTtemCount.Empty();
	m_comboBoxCurrency.SetCurSel(0);
	m_EditControlInput.SetWindowTextW(m_csInput);

}

void CePosDlg::DisplayItem(ST_TICKET* pstTicket, int i)
{
	DisplayInfo("%s X %s\r\n%s\r\n%s"
				, formatCount(pstTicket->SaleInfo[i].ItemCount, pstTicket->SaleInfo[i].ItemCountPrecision, pstTicket->SaleInfo[i].ItemUnitType)
				, formatAmount((uint32)pstTicket->SaleInfo[i].ItemPrice, pstTicket->SaleInfo[i].OriginalItemAmountCurrency)
				, pstTicket->SaleInfo[i].Name
				, pstTicket->SaleInfo[i].Barcode
			   );
}

void CePosDlg::DisplayTransaction_Item(ST_TICKET* pstTicket, int i)
{
	CListBoxPrintf(&m_listTransaction, "-ÜRÜN %d", i + 1);
	CListBoxPrintf(&m_listTransaction, "  TÝP/FLAG: %d / %08X"		, pstTicket->SaleInfo[i].ItemUnitType, pstTicket->SaleInfo[i].Flag);
	CListBoxPrintf(&m_listTransaction, "  ADI     : %s"			, pstTicket->SaleInfo[i].Name);
	CListBoxPrintf(&m_listTransaction, "  BARKOD  : %s"			, pstTicket->SaleInfo[i].Barcode);
	CListBoxPrintf(&m_listTransaction, "  FÝYAT   : %s"			, formatAmount((uint32)pstTicket->SaleInfo[i].ItemPrice, pstTicket->SaleInfo[i].ItemCurrencyType));
	CListBoxPrintf(&m_listTransaction, "  O.FÝYAT : %s"			, formatAmount(pstTicket->SaleInfo[i].OrigialItemAmount, pstTicket->SaleInfo[i].OriginalItemAmountCurrency));
	CListBoxPrintf(&m_listTransaction, "  ÝNDÝRM  : %s"			, formatAmount((uint32)pstTicket->SaleInfo[i].DecAmount, CURRENCY_TL));
	CListBoxPrintf(&m_listTransaction, "  ARTIRM  : %s"			, formatAmount((uint32)pstTicket->SaleInfo[i].IncAmount, CURRENCY_TL));
	CListBoxPrintf(&m_listTransaction, "  MÝKTAR  : %s"			, formatCount(pstTicket->SaleInfo[i].ItemCount , pstTicket->SaleInfo[i].ItemCountPrecision, pstTicket->SaleInfo[i].ItemUnitType));
}

const char *CePosDlg::GetPaymentTypeName(uint32 typeOfPayment)
{
	CString cs;

	switch (typeOfPayment)
	{
	case 0:
		return "NULL";
	case PAYMENT_CASH_TL:
		return "PAYMENT_CASH_TL";
	case PAYMENT_CASH_CURRENCY:
		return "PAYMENT_CASH_CURRENCY";
	case PAYMENT_BANK_CARD:
		return "PAYMENT_BANK_CARD";
	case PAYMENT_YEMEKCEKI:
		return "PAYMENT_YEMEKCEKI";
	case PAYMENT_MOBILE:
		return "PAYMENT_MOBILE";
	case PAYMENT_HEDIYE_CEKI:
		return "PAYMENT_HEDIYE_CEKI";
	case PAYMENT_IKRAM:
		return "PAYMENT_IKRAM";
	case PAYMENT_ODEMESIZ:
		return "PAYMENT_ODEMESIZ";
	case PAYMENT_KAPORA:
		return "PAYMENT_KAPORA";
	case PAYMENT_PUAN:
		return "PAYMENT_PUAN";
	case PAYMENT_GIDER_PUSULASI:
		return "PAYMENT_GIDER_PUSULASI";
	case PAYMENT_BANKA_TRANSFERI:
		return "PAYMENT_BANKA_TRANSFERI";
	case PAYMENT_CEK:
		return "PAYMENT_CEK";
	case PAYMENT_ACIK_HESAP:
		return "PAYMENT_ACIK_HESAP";
	case REVERSE_PAYMENT_CASH:
		return "REVERSE_PAYMENT_CASH";
	case REVERSE_PAYMENT_BANK_CARD_VOID:
		return "REVERSE_PAYMENT_BANK_CARD_VOID";
	case REVERSE_PAYMENT_BANK_CARD_REFUND:
		return "REVERSE_PAYMENT_BANK_CARD_REFUND";
	case REVERSE_PAYMENT_YEMEKCEKI:
		return "REVERSE_PAYMENT_YEMEKCEKI";
	case REVERSE_PAYMENT_MOBILE:
		return "REVERSE_PAYMENT_MOBILE";
	case REVERSE_PAYMENT_HEDIYE_CEKI:
		return "REVERSE_PAYMENT_HEDIYE_CEKI";
	}

	return "PAYMENT_UNDEFINED";
}

const char *CePosDlg::GetPaymentSubtypeName(uint32 subtypeOfPayment)
{
	switch (subtypeOfPayment)
	{
	case PAYMENT_SUBTYPE_PROCESS_ON_POS:
		return "PAYMENT_SUBTYPE_PROCESS_ON_POS";
	case PAYMENT_SUBTYPE_SALE:
		return "PAYMENT_SUBTYPE_SALE";
	case PAYMENT_SUBTYPE_INSTALMENT_SALE:
		return "PAYMENT_SUBTYPE_INSTALMENT_SALE";
	case PAYMENT_SUBTYPE_LOYALTY_PUAN:
		return "PAYMENT_SUBTYPE_LOYALTY_PUAN";
	case PAYMENT_SUBTYPE_ADVANCE_REFUND:
		return "PAYMENT_SUBTYPE_ADVANCE_REFUND";
	case PAYMENT_SUBTYPE_INSTALLMENT_REFUND:
		return "PAYMENT_SUBTYPE_INSTALLMENT_REFUND";
	case PAYMENT_SUBTYPE_REFERENCED_REFUND:
		return "PAYMENT_SUBTYPE_REFERENCED_REFUND";
	case PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD:
		return "PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD";
	case PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD:
		return "PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD";
	case PAYMENT_SUBTYPE_FORWARD_SALE:
		return "PAYMENT_SUBTYPE_FORWARD_SALE";
	}
	return "PAYMENT_SUBTYPE_UNDEFINED";
}

void CePosDlg::GetTypedAmount(uint32* pAmount, uint16* pCurrency)
{
	uint16 ComboData = (uint16)m_comboBoxCurrency.GetItemData(m_comboBoxCurrency.GetCurSel());
	*pAmount	= 0;
	*pCurrency	= ComboData;

	if (*pCurrency == CURRENCY_NONE)
		*pCurrency = CURRENCY_TL;

	if (!(*pCurrency == CURRENCY_TL))
	{

		HTRX hTrx = GetSelectedTransaction();
		HINT hInt = GetSelectedInterface();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);


		//if( FP3_SetCurrencyProfileIndex( hInt, hTrx, CurrencyProfileIndex, pstTicket ) )

	}
	m_comboBoxCurrency.SetCurSel(0);

	m_EditControlInput.GetWindowTextW(m_csInput);
	if (!m_csInput.GetLength())
		return;

	*pAmount = getAmount(m_csInput);

	m_csInput.Empty();
	m_EditControlInput.SetWindowTextW(m_csInput);

	return;
}


/* cemal sil
void CePosDlg::GetTypedAmount(uint32* pAmount, uint16* pCurrency)
{
	*pAmount	= 0;
	*pCurrency	= (uint16)m_comboBoxCurrency.GetItemData( m_comboBoxCurrency.GetCurSel());
	m_comboBoxCurrency.SetCurSel(0);

	if( *pCurrency == CURRENCY_NONE )
		*pCurrency = CURRENCY_TL;

	m_EditControlInput.GetWindowTextW(m_csInput);
	if(!m_csInput.GetLength())
		return;

	*pAmount = getAmount(m_csInput);

	m_csInput.Empty();
	m_EditControlInput.SetWindowTextW(m_csInput);

	return;
}
*/
void CePosDlg::OnBnClickedButtonReversePayments()
{
	int retcode = TRAN_RESULT_OK;
	CPaymentApplication stPaymentApplicationInfoDlg;
	ST_PAYMENT_REQUEST stReversePayment;
	CDoPayment doPayment;
	char szInput[128 + 1];
	CVasLoyaltyService  stVasLoyaltyServiceInfoDlg;

	uint16 currency = 0;
	uint32 amount = 0;
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	if (amount == 0)
		return;

	if (doPayment.DoModal(2) != IDOK)
		return;

	memset(&stReversePayment, 0, sizeof(ST_PAYMENT_REQUEST));

	stReversePayment.typeOfPayment				= doPayment.m_PaymentType;
	stReversePayment.subtypeOfPayment			= NULL;
	stReversePayment.payAmount					= amount;
	stReversePayment.payAmountCurrencyCode		= currency;

	switch (doPayment.m_PaymentType)
	{
	default:
		break;

	case PAYMENT_OTHER_REVERSE:

		retcode = FP3_GetVasApplicationInfo(GetSelectedInterface(), &stPaymentApplicationInfoDlg.numberOfTotalRecords, &stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.stPaymentApplicationInfo, TLV_OKC_ASSIST_VAS_TYPE_ALL);
		if (retcode != TRAN_RESULT_OK)
			break;
		else if (stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
			MessageBox(L"ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý", L"HATA", MB_OK);
		else
		{
			if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
				break;

			if (doPayment.DoModal(1) != IDOK)
				return;

			stReversePayment.typeOfPayment	= doPayment.m_PaymentType;

			if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->AppType == TLV_OKC_ASSIST_VAS_TYPE_LOYALTY)
			{
				if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected == NULL)
				{
					MessageBox(L"Lütfen UYGULAMA Seçiniz", L"HATA", MB_OK);
					break;
				}

				if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId == 0)
				{
					MessageBox(L"UYGULAMA ID == 0", L"HATA", MB_OK);
					break;
				}

				retcode = FP3_GetVasLoyaltyServiceInfo(GetSelectedInterface(), &stVasLoyaltyServiceInfoDlg.numberOfTotalRecords, &stVasLoyaltyServiceInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId, stVasLoyaltyServiceInfoDlg.stVasLoyaltyServiceInfo);
				if (retcode != TRAN_RESULT_OK)
					HandleErrorCode(retcode);
				else if (stVasLoyaltyServiceInfoDlg.numberOfTotalRecordsReceived == 0)
					MessageBox(L"ÖKC Üzerinde Servis Listesi Bulunamadý", L"HATA", MB_OK);
				else
				{
					if (stVasLoyaltyServiceInfoDlg.DoModal() != IDOK)
						break;

					if (stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected == NULL)
					{
						MessageBox(L"Lütfen Servis Seçiniz", L"HATA", MB_OK);
						break;
					}

//					GetStringInput( L"CUSTOMER ID ?",   stReversePayment.LoyaltyCustomerId);
					GetStringInput(L"PROVISION ID ?",  stReversePayment.PaymentProvisionId);

					stReversePayment.bankBkmId		  = stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->u16AppId;
					stReversePayment.LoyaltyServiceId = stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->ServiceId;
				}
			}
			else if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->AppType == TLV_OKC_ASSIST_VAS_TYPE_YEMEKCEKI)
			{
				GetStringInput(L"PROVISION ID ?",  stReversePayment.PaymentProvisionId);
			}
			else if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->AppType == TLV_OKC_ASSIST_VAS_TYPE_PAYMENT)
			{
				GetStringInput(L"PROVISION ID ?",  stReversePayment.PaymentProvisionId);

				stReversePayment.bankBkmId = stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId;
			}
		}
		break;

	case REVERSE_PAYMENT_BANK_CARD_REFUND:
		strcpy(szInput, "123456789012345");
		if (!GetStringInput(L"ORG MERCHANT ID (max 15)", szInput))
			return;
		memcpy(stReversePayment.OrgTransData.MerchantId, szInput, MINI(sizeof(stReversePayment.OrgTransData.MerchantId), strlen(szInput)));

		stReversePayment.OrgTransData.TransactionAmount = 0;
		if (!GetIntegerInput(L"ORG TRANSACTION AMOUNT", (int*)&stReversePayment.OrgTransData.TransactionAmount))
			return;

		strcpy(szInput, "1234567890");
		if (!GetStringInput(L"REF CODE OF ORG TRANSACTION (max 10)", szInput))
			return;
		memcpy(stReversePayment.OrgTransData.referenceCodeOfTransaction, szInput, MINI(sizeof(stReversePayment.OrgTransData.referenceCodeOfTransaction), strlen(szInput)));

		strcpy(szInput, "ABC123");
		if (!GetStringInput(L"AUTH CODE OF ORG TRANSACTION (max 6)", szInput))
			return;
		memcpy(stReversePayment.OrgTransData.AuthorizationCode, szInput, MINI(sizeof(stReversePayment.OrgTransData.AuthorizationCode), strlen(szInput)));

		strcpy(szInput, "123456789012");
		if (!GetStringInput(L"REF RRN OF ORG TRANSACTION (max 12)", szInput))
			return;
		memcpy(stReversePayment.OrgTransData.rrn, szInput, MINI(sizeof(stReversePayment.OrgTransData.rrn), strlen(szInput)));

		stReversePayment.OrgTransData.LoyaltyAmount = 0;
		if (!GetIntegerInput(L"ORG LOYALTY AMOUNT", (int*)&stReversePayment.OrgTransData.LoyaltyAmount))
			return;

		if (stReversePayment.OrgTransData.LoyaltyAmount)
		{
			stReversePayment.payAmountBonus = 0;
			if (!GetIntegerInput(L"LOYALTY AMOUNT TO REFUND", (int*)&stReversePayment.payAmountBonus))
				return;
		}

		strcpy(szInput, "1510221350");
		do
		{
			if (!GetStringInput(L"ORGINAL TRANSACTION DATE YYMMDDHHMM", szInput))
				return;
		}
		while (strlen(szInput) != 10);

		LongToBcd(atol(szInput), stReversePayment.OrgTransData.TransactionDate, 5);

		////////////////// TRANSACTION TYPE//////////////////////////
		stReversePayment.OrgTransData.TransactionType = 1;
		if (!GetIntegerInput(L"TYPE 1:SALE 2:INSTALMENT 3:POINT SALE", (int*)&stReversePayment.OrgTransData.TransactionType))
			return;

		if (stReversePayment.OrgTransData.TransactionType == 2)
		{
			////////////////// INSTALMENT//////////////////////////
			stReversePayment.OrgTransData.NumberOfinstallments = 1;
			if (!GetIntegerInput(L"INSTALMENT NUMBER (1-12)", (int*)&stReversePayment.OrgTransData.NumberOfinstallments))
				return;
		}

		// Burada özellikle break yok. Void de alýnanlar da alýnacak.

	case REVERSE_PAYMENT_BANK_CARD_VOID:

		retcode = FP3_GetPaymentApplicationInfo(GetSelectedInterface(), &stPaymentApplicationInfoDlg.numberOfTotalRecords, &stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.stPaymentApplicationInfo, sizeof(stPaymentApplicationInfoDlg.stPaymentApplicationInfo) / sizeof(ST_PAYMENT_APPLICATION_INFO));
		if (retcode != TRAN_RESULT_OK)
		{
			HandleErrorCode(retcode);
			return;
		}
		else if (stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
		{
			MessageBox(L"ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý", L"HATA", MB_OK);
			return;
		}

		if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
			return;

		stReversePayment.bankBkmId					= stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected ?  stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16BKMId : 0;					// banka uygulamasi ise bkm Id, VAS icin telium id kullanilir...

		////////////////// Termina ID //////////////////////////
		strcpy(szInput, "12345678");
		if (!GetStringInput(L"TERMINAL ID (max 8)", szInput))
			return;
		memcpy(stReversePayment.terminalId, szInput, MINI(sizeof(stReversePayment.terminalId), strlen(szInput)));

		////////////////// BATCH NO//////////////////////////
		stReversePayment.batchNo = 1;
		if (!GetIntegerInput(L"BATCH NO", (int*)&stReversePayment.batchNo))
			return;

		////////////////// STAN//////////////////////////
		stReversePayment.stanNo = 1;
		if (!GetIntegerInput(L"STAN", (int*)&stReversePayment.stanNo))
			return;

		break;
	}

	strcpy((char*)stReversePayment.rawData, "RawData from external application for the payment application");
	stReversePayment.rawDataLen = (uint16)strlen("RawData from external application for the payment application");

	retcode = ReversePayment(&stReversePayment);

	HandleErrorCode(retcode);
}

void CePosDlg::DisplayTransaction_Payment(ST_PAYMENT* pstPayment, int i)
{
	CListBoxPrintf(&m_listTransaction, "-PAYMENT %d", i + 1);
	CListBoxPrintf(&m_listTransaction, "  TÝP     : %s (%d)"		, GetPaymentTypeName(pstPayment->typeOfPayment), pstPayment->typeOfPayment);
	CListBoxPrintf(&m_listTransaction, "  ALT TÝP : %s (%d)"		, GetPaymentSubtypeName(pstPayment->subtypeOfPayment), pstPayment->subtypeOfPayment);
	CListBoxPrintf(&m_listTransaction, "  FLAG    : %02X"			, pstPayment->flags);
	if (pstPayment->flags & PARTIAL_PAYMENT_FLAG_MERCHANT)		CListBoxPrintf(&m_listTransaction, "          : PARTIAL_PAYMENT_FLAG_MERCHANT");
	if (pstPayment->flags & PARTIAL_PAYMENT_FLAG_CUSTOMER)		CListBoxPrintf(&m_listTransaction, "          : PARTIAL_PAYMENT_FLAG_CUSTOMER");
	if (pstPayment->flags & PARTIAL_PAYMENT_FLAG_CANCEL)		CListBoxPrintf(&m_listTransaction, "          : PARTIAL_PAYMENT_FLAG_CANCEL");
	if (pstPayment->flags & PARTIAL_PAYMENT_FLAG_CANCEL_SENT)	CListBoxPrintf(&m_listTransaction, "          : PARTIAL_PAYMENT_FLAG_CANCEL_SENT");
	if (pstPayment->flags & PARTIAL_PAYMENT_FLAG_TERMINAL_SAVED)CListBoxPrintf(&m_listTransaction, "          : PARTIAL_PAYMENT_FLAG_TERMINAL_SAVED");
	if (pstPayment->flags & PAYMENT_FLAG_CREDIT_DONE)			CListBoxPrintf(&m_listTransaction, "          : PAYMENT_FLAG_CREDIT_DONE");
	if (pstPayment->flags & PRE_PARTIAL_PAYMENT_FLAG_CANCEL)	CListBoxPrintf(&m_listTransaction, "          : PRE_PARTIAL_PAYMENT_FLAG_CANCEL");

	CListBoxPrintf(&m_listTransaction, "  DATETIME: %08X"			, pstPayment->dateOfPayment);
	CListBoxPrintf(&m_listTransaction, "  AMOUNT O: %s"			, formatAmount((uint32)pstPayment->orgAmount, pstPayment->orgAmountCurrencyCode));
	CListBoxPrintf(&m_listTransaction, "  AMOUNT P: %s"			, formatAmount((uint32)pstPayment->payAmount, pstPayment->payAmountCurrencyCode));

	if ((pstPayment->typeOfPayment == PAYMENT_BANK_CARD) || (pstPayment->typeOfPayment == PAYMENT_MOBILE))
	{
		CListBoxPrintf(&m_listTransaction, "  BANKA AD: %s"			, pstPayment->stBankPayment.bankName);
		CListBoxPrintf(&m_listTransaction, "  BKM ID  : %d"			, pstPayment->stBankPayment.bankBkmId);
		CListBoxPrintf(&m_listTransaction, "  TERMID  : %8.8s"			, pstPayment->stBankPayment.terminalId);
		CListBoxPrintf(&m_listTransaction, "  MERCH ID: %15.15s"		, pstPayment->stBankPayment.merchantId);
		CListBoxPrintf(&m_listTransaction, "  BATCH NO: %d"			, pstPayment->stBankPayment.batchNo);
		CListBoxPrintf(&m_listTransaction, "  STAN    : %d"			, pstPayment->stBankPayment.stan);
		CListBoxPrintf(&m_listTransaction, "  AUTHCODE: %6.6s"			, pstPayment->stBankPayment.authorizeCode);
		CListBoxPrintf(&m_listTransaction, "  CARD INFO");
		CListBoxPrintf(&m_listTransaction, "  TYPE    : %d"			, pstPayment->stBankPayment.stCard.type);
		CListBoxPrintf(&m_listTransaction, "  PAN     : %s"			, pstPayment->stBankPayment.stCard.pan);
		CListBoxPrintf(&m_listTransaction, "  NAME    : %s"			, pstPayment->stBankPayment.stCard.holderName);
		CListBoxPrintf(&m_listTransaction, "  INPT TYP: %d"			, pstPayment->stBankPayment.stCard.inputType);
		CListBoxPrintf(&m_listTransaction, "  BANKING ERROR");
		CListBoxPrintf(&m_listTransaction, "    CODE  : %4.4s"			, pstPayment->stBankPayment.stPaymentErrMessage.ErrorCode);
		CListBoxPrintf(&m_listTransaction, "    TEXT  : %s"			, pstPayment->stBankPayment.stPaymentErrMessage.ErrorMsg);
		CListBoxPrintf(&m_listTransaction, "  APPLICATION ERROR");
		CListBoxPrintf(&m_listTransaction, "    CODE  : %4.4s"			, pstPayment->stBankPayment.stPaymentErrMessage.AppErrorCode);
		CListBoxPrintf(&m_listTransaction, "    TEXT  : %s"			, pstPayment->stBankPayment.stPaymentErrMessage.AppErrorMsg);
	}
}

char* CePosDlg::getHexFormat(uint8* buffer, int len)
{
	static char str[2048];

	memset(str, 0, sizeof(str));

	for (int i = 0; i < len; i++)
		sprintf(&str[strlen(str)], "%02X", buffer[i]);

	return str;
}

void CePosDlg::DisplayZReport(ST_Z_REPORT *pZReport)
{
	m_listTransaction.ResetContent();

	CListBoxPrintf(&m_listTransaction, "*** %s ***", "Z REPORT");

	CListBoxPrintf(&m_listTransaction, "Z NO   : %d"					, pZReport->ZNo);
	CListBoxPrintf(&m_listTransaction, "F NO   : %d"					, pZReport->FNo);
	CListBoxPrintf(&m_listTransaction, "EJNO   : %d"					, pZReport->EJNo);
	CListBoxPrintf(&m_listTransaction, "DATE   : %02X/%02X/20%02X"	, pZReport->Date[2], pZReport->Date[1], pZReport->Date[0]);
	CListBoxPrintf(&m_listTransaction, "HOUR   : %02X:%02X"			, pZReport->Time[0], pZReport->Time[1]);

	CListBoxPrintf(&m_listTransaction, "*** %s ***", "COUNTERS");
	CListBoxPrintf(&m_listTransaction, "increaments            : %d", pZReport->countOf.increaments);
	CListBoxPrintf(&m_listTransaction, "decreases              : %d", pZReport->countOf.decreases);
	CListBoxPrintf(&m_listTransaction, "corrections            : %d", pZReport->countOf.corrections);
	CListBoxPrintf(&m_listTransaction, "fiscalReceipts         : %d", pZReport->countOf.fiscalReceipts);
	CListBoxPrintf(&m_listTransaction, "nonfiscalReceipts      : %d", pZReport->countOf.nonfiscalReceipts);
	CListBoxPrintf(&m_listTransaction, "customerReceipts       : %d", pZReport->countOf.customerReceipts);
	CListBoxPrintf(&m_listTransaction, "voidReceipts           : %d", pZReport->countOf.voidReceipts);
	CListBoxPrintf(&m_listTransaction, "invoiceSaleReceipts    : %d", pZReport->countOf.invoiceSaleReceipts);
	CListBoxPrintf(&m_listTransaction, "yemekcekiReceipts      : %d", pZReport->countOf.yemekcekiReceipts);
	CListBoxPrintf(&m_listTransaction, "carParkingEntryReceipts: %d", pZReport->countOf.carParkingEntryReceipts);
	CListBoxPrintf(&m_listTransaction, "fiscalReportReceipts   : %d", pZReport->countOf.fiscalReportReceipts);
	CListBoxPrintf(&m_listTransaction, "tasnifDisiReceipts     : %d", pZReport->countOf.tasnifDisiReceipts);
	CListBoxPrintf(&m_listTransaction, "invoiceReceipts        : %d", pZReport->countOf.invoiceReceipts);
	CListBoxPrintf(&m_listTransaction, "matrahsizReceipts      : %d", pZReport->countOf.matrahsizReceipts);
	CListBoxPrintf(&m_listTransaction, "serviceModeEntry       : %d", pZReport->countOf.serviceModeEntry);
	CListBoxPrintf(&m_listTransaction, "advanceCount	        : %d", pZReport->countOf.advanceReceipts);
	CListBoxPrintf(&m_listTransaction, "AcikHesapCount	        : %d", pZReport->countOf.openAccountReceipts);

	CListBoxPrintf(&m_listTransaction, "*** %s ***", "TICKET TOTALS");
	CListBoxPrintf(&m_listTransaction, "IncTotAmount        : %s", formatAmount((uint32)pZReport->IncTotAmount			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "DecTotAmount        : %s", formatAmount((uint32)pZReport->DecTotAmount			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "SaleVoidTotAmount   : %s", formatAmount((uint32)pZReport->SaleVoidTotAmount	 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "CorrectionTotAmount : %s", formatAmount((uint32)pZReport->CorrectionTotAmount	 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "DailyTotAmount      : %s", formatAmount((uint32)pZReport->DailyTotAmount		 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "DailyTotTax         : %s", formatAmount((uint32)pZReport->DailyTotTax			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "CumulativeTotAmount : %s", formatAmount((uint32)pZReport->CumulativeTotAmount	 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "CumulativeTotTax    : %s", formatAmount((uint32)pZReport->CumulativeTotTax		 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "AvansTotalAmount    : %s", formatAmount((uint32)pZReport->AvansTotalAmount		 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "OdemeTotalAmount    : %s", formatAmount((uint32)pZReport->OdemeTotalAmount		 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "TaxRefundTotalAmount: %s", formatAmount((uint32)pZReport->TaxRefundTotalAmount	 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "MatrahsizTotalAmount: %s", formatAmount((uint32)pZReport->MatrahsizTotalAmount	 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "CariHesapTotalAmount: %s", formatAmount((uint32)pZReport->OpenAccountTotalAmount, CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "totalReceiptAmount  : %s", formatAmount((uint32)pZReport->invoice.TotalAmount           , CURRENCY_NONE));



	CListBoxPrintf(&m_listTransaction, "*** %s ***", "PAYMENT TOTALS");
	CListBoxPrintf(&m_listTransaction, "cashTotal           : %s", formatAmount((uint32)pZReport->payment.cashTotal			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "creditTotal         : %s", formatAmount((uint32)pZReport->payment.creditTotal			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "otherTotal          : %s", formatAmount((uint32)pZReport->payment.otherTotal			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "foodReceiptTotal    : %s", formatAmount((uint32)pZReport->FoodRcptTotAmount			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "other.mobil         : %s", formatAmount((uint32)pZReport->payment.other.mobil			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "other.hediyeCeki    : %s", formatAmount((uint32)pZReport->payment.other.hediyeCeki		 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "other.ikram         : %s", formatAmount((uint32)pZReport->payment.other.ikram			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "other.odemesiz      : %s", formatAmount((uint32)pZReport->payment.other.odemesiz		 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "other.kapora        : %s", formatAmount((uint32)pZReport->payment.other.kapora			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "other.puan          : %s", formatAmount((uint32)pZReport->payment.other.puan			 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "other.giderPusulasi : %s", formatAmount((uint32)pZReport->payment.other.giderPusulasi	 , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "other.cek           : %s", formatAmount((uint32)pZReport->payment.other.cek             , CURRENCY_NONE));
	CListBoxPrintf(&m_listTransaction, "other.acikHesap     : %s", formatAmount((uint32)pZReport->payment.other.acikHesap	     , CURRENCY_NONE));

	CListBoxPrintf(&m_listTransaction, "*** %s ***", "DEPARTMENT TOTALS");
	for (int i = 0 ; i < MAX_DEPARTMENT_COUNT; ++i)
	{
		CListBoxPrintf(&m_listTransaction, "    DEPARTMEN %d, %s", i + 1, pZReport->department[i].name);
		CListBoxPrintf(&m_listTransaction, "    totalAmount   = %s", formatAmount((uint32)pZReport->department[i].totalAmount			 , CURRENCY_NONE));
		CListBoxPrintf(&m_listTransaction, "    totalQuantity = %lld", pZReport->department[i].totalQuantity);
	}

}

void CePosDlg::DisplayTransaction(HINT hInt, HTRX hTrx, bool itemDetail)
{
	DisplayTransaction(&(GetTransactionDataPointer(hInt, hTrx)->m_stTicket) , itemDetail);
}

void CePosDlg::DisplayTransaction(ST_TICKET* pstTicket, bool itemDetail)
{
	m_listTransaction.ResetContent();

	CListBoxPrintf(&m_listTransaction, "UNIQUE ID (%s)", getHexFormat(pstTicket->uniqueId, sizeof(pstTicket->uniqueId)));

	CListBoxPrintf(&m_listTransaction, "TICKET TYPE     : %d"					, pstTicket->ticketType);
	CListBoxPrintf(&m_listTransaction, "Z NO            : %d"					, pstTicket->ZNo);
	CListBoxPrintf(&m_listTransaction, "F NO            : %d"					, pstTicket->FNo);
	CListBoxPrintf(&m_listTransaction, "EJNO            : %d"					, pstTicket->EJNo);
	CListBoxPrintf(&m_listTransaction, "TRANSACTION FLAG: %08X"				, pstTicket->TransactionFlags);

	if (pstTicket->TransactionFlags & FLG_XTRANS_GMP3)									CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_GMP3");
	if (pstTicket->TransactionFlags & FLG_XTRANS_FROM_FILE)							CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_FROM_FILE");
	if (pstTicket->TransactionFlags & FLG_XTRANS_BACKGROUND_PROCESS)					CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_BACKGROUND_PROCESS");
	if (pstTicket->TransactionFlags & FLG_XTRANS_FROM_MASTER_OKC)						CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_FROM_MASTER_OKC");
	if (pstTicket->TransactionFlags & FLG_XTRANS_BANK_MONEY_COLLECTION_CASH)			CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_BANK_MONEY_COLLECTION_CASH");
	if (pstTicket->TransactionFlags & FLG_XTRANS_BANK_MONEY_COLLECTION)				CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_BANK_MONEY_COLLECTION");
	if (pstTicket->TransactionFlags & FLG_XTRANS_ONLY_BANK_REFUND_TICKET)				CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_ONLY_BANK_REFUND_TICKET");
	if (pstTicket->TransactionFlags & FLG_XTRANS_TAXFREE_PARAMETERS_SET)				CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_TAXFREE_PARAMETERS_SET");
	if (pstTicket->TransactionFlags & FLG_XTRANS_TICKETTING_EXISTS)					CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_TICKETTING_EXISTS");
	if (pstTicket->TransactionFlags & FLG_XTRANS_FULL_RCPT_CANCEL)						CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_FULL_RCPT_CANCEL");
	if (pstTicket->TransactionFlags & FLG_XTRANS_NONEY_COLLECTION_EXISTS)				CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_NONEY_COLLECTION_EXISTS");
	if (pstTicket->TransactionFlags & FLG_XTRANS_TAXLESS_ITEM_EXISTS)					CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_TAXLESS_ITEM_EXISTS");
	if (pstTicket->TransactionFlags & FLG_XTRANS_INVOICE_PARAMETERS_SET)				CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_INVOICE_PARAMETERS_SET");
	if (pstTicket->TransactionFlags & FLG_XTRANS_TICKET_HEADER_PRINTED)				CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_TICKET_HEADER_PRINTED");
	if (pstTicket->TransactionFlags & FLG_XTRANS_TICKET_TOTALS_AND_PAYMENTS_PRINTED)	CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_TICKET_TOTALS_AND_PAYMENTS_PRINTED");
	if (pstTicket->TransactionFlags & FLG_XTRANS_TICKET_FOOTER_BEFORE_MF_PRINTED)		CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_TICKET_FOOTER_BEFORE_MF_PRINTED");
	if (pstTicket->TransactionFlags & FLG_XTRANS_TICKET_FOOTER_MF_PRINTED)				CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_TICKET_FOOTER_MF_PRINTED");
	if (pstTicket->TransactionFlags & FLG_XTRANS_ONLINE_INVOICE_PARAMETERS_SET)				CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_ONLINE_INVOICE_PARAMETERS_SET");
	if (pstTicket->TransactionFlags & FLG_XTRANS_EXTERNAL_EFT_POS)						CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_EXTERNAL_EFT_POS");
	if (pstTicket->TransactionFlags & FLG_XTRANS_TICKET_SAVED_SUCCESSFULLY)			CListBoxPrintf(&m_listTransaction, "       - FLG_XTRANS_TICKET_SAVED_SUCCESSFULLY");

	CListBoxPrintf(&m_listTransaction, "OPTION FLAG     : %08X"				, pstTicket->OptionFlags);
	CListBoxPrintf(&m_listTransaction, "DATE            : %c%c/%c%c/20%c%c"	, pstTicket->szTicketDate[4], pstTicket->szTicketDate[5], pstTicket->szTicketDate[2], pstTicket->szTicketDate[3], pstTicket->szTicketDate[0], pstTicket->szTicketDate[1]);
	CListBoxPrintf(&m_listTransaction, "HOUR            : %c%c:%c%c:%c%c"		, pstTicket->szTicketTime[0], pstTicket->szTicketTime[1], pstTicket->szTicketTime[2], pstTicket->szTicketTime[3], pstTicket->szTicketTime[4], pstTicket->szTicketTime[5]);

	CListBoxPrintf(&m_listTransaction, "TOTAL RECEIPT A.: %ld.%02ld"			, (pstTicket->TotalReceiptAmount + pstTicket->KatkiPayiAmount) / 100, (pstTicket->TotalReceiptAmount + pstTicket->KatkiPayiAmount) % 100);
	if (pstTicket->KatkiPayiAmount)
		CListBoxPrintf(&m_listTransaction, "MATRAHSZ        : %ld.%02ld"			, pstTicket->KatkiPayiAmount / 100, pstTicket->KatkiPayiAmount % 100);

	CListBoxPrintf(&m_listTransaction, "TOTAL TAX       : %ld.%02ld"			, pstTicket->TotalReceiptTax / 100, pstTicket->TotalReceiptTax % 100);

	if (pstTicket->TotalReceiptDiscount)
		CListBoxPrintf(&m_listTransaction, "TOTAL DISCOUNT  : %ld.%02ld"			, pstTicket->TotalReceiptDiscount / 100, pstTicket->TotalReceiptDiscount % 100);

	if (pstTicket->TotalReceiptIncrement)
		CListBoxPrintf(&m_listTransaction, "TOTAL INCREAE   : %ld.%02ld"			, pstTicket->TotalReceiptIncrement / 100, pstTicket->TotalReceiptIncrement % 100);

	if (pstTicket->TotalReceiptItemCancel)
		CListBoxPrintf(&m_listTransaction, "TOTAL VOID      : %ld.%02ld"			, pstTicket->TotalReceiptItemCancel / 100, pstTicket->TotalReceiptItemCancel % 100);

	if (pstTicket->KasaAvansAmount)
		CListBoxPrintf(&m_listTransaction, "KASA AVANS      : %ld.%02ld"			, pstTicket->KasaAvansAmount / 100, pstTicket->KasaAvansAmount % 100);

	if (pstTicket->KasaPaymentAmount)
		CListBoxPrintf(&m_listTransaction, "KASA PAYMENT    : %ld.%02ld"			, pstTicket->KasaPaymentAmount / 100, pstTicket->KasaPaymentAmount % 100);

	if (pstTicket->CashBackAmount)
		CListBoxPrintf(&m_listTransaction, "CASHBACK        : %ld.%02ld"			, pstTicket->CashBackAmount / 100, pstTicket->CashBackAmount % 100);

	if (pstTicket->invoiceAmount)
		CListBoxPrintf(&m_listTransaction, "INVOICE         : %ld.%02ld"			, pstTicket->invoiceAmount / 100, pstTicket->invoiceAmount % 100);

	if (pstTicket->TaxFreeCalculated)
		CListBoxPrintf(&m_listTransaction, "TAXFREE CALCULA : %ld.%02ld"			, pstTicket->TaxFreeCalculated / 100, pstTicket->TaxFreeCalculated % 100);

	if (pstTicket->TaxFreeRefund)
		CListBoxPrintf(&m_listTransaction, "TAXFREE REFUND  : %ld.%02ld"			, pstTicket->TaxFreeRefund / 100, pstTicket->TaxFreeRefund % 100);

	if (pstTicket->TotalReceiptReversedPayment)
		CListBoxPrintf(&m_listTransaction, "REVERSE PAYMENTS: %s"					, formatAmount(pstTicket->TotalReceiptReversedPayment, CURRENCY_NONE));

	if (pstTicket->TotalReceiptPayment)
		CListBoxPrintf(&m_listTransaction, "PAYMENTS        : %s"					, formatAmount(pstTicket->TotalReceiptPayment, CURRENCY_NONE));


	for (int i = 0; i < 8; i++)
	{
		if (pstTicket->stTaxDetails[i].u32Amount == 0)
			continue;

		CListBoxPrintf(&m_listTransaction, "%02d.%02d  %-10s   %s"				, pstTicket->stTaxDetails[i].u16VATPercentage / 100, pstTicket->stTaxDetails[i].u16VATPercentage % 100
					   , formatAmount(pstTicket->stTaxDetails[i].u32Amount, CURRENCY_NONE)
					   , formatAmount(pstTicket->stTaxDetails[i].u32VAT, CURRENCY_NONE)
					  );

	}

	CListBoxPrintf(&m_listTransaction, "ITEMS TABLE     : %d", pstTicket->totalNumberOfItems);
	if (itemDetail)
		for (int i = 0; i < pstTicket->totalNumberOfItems; i++)
			DisplayTransaction_Item(pstTicket, i);

	CListBoxPrintf(&m_listTransaction, "PAYMENTS TABLE  : %d", pstTicket->totalNumberOfPayments);
	/*	if(itemDetail )
	for( int i=0;i<pstTicket->numberOfpayments;i++ )
	DisplayTransaction_Payment(&pstTicket->stPayment[i],i);
	*/

	CListBoxPrintf(&m_listTransaction, "LOYALTY TABLE  : %d", pstTicket->numberOfLoyaltyInThis);
	if (pstTicket->numberOfLoyaltyInThis)
	{
//		CListBoxPrintf( &m_listTransaction, "-KAMPANYA %d", pstTicket->numberOfLoyaltyInThis );
		CListBoxPrintf(&m_listTransaction, "  [APP ID][SERV.NAME][SERV.ID][CUST.ID][DISCOUNT]");
		for (int i = 0; i < pstTicket->numberOfLoyaltyInThis; i++)
			CListBoxPrintf(&m_listTransaction, "  [%02X][%s][%02X][%s][%d]", pstTicket->stLoyaltyService[i].u16AppId, pstTicket->stLoyaltyService[i].name, pstTicket->stLoyaltyService[i].ServiceId, pstTicket->stLoyaltyService[i].CustomerId, pstTicket->stLoyaltyService[i].TotalDiscountAmount);
	}

	if (pstTicket->rawDataLen)
	{
		CListBoxPrintf(&m_listTransaction, "RAW DATA LENGTH: %d", pstTicket->rawDataLen);
	}

	if (pstTicket->totalNumberOfPrinterLines == pstTicket->numberOfPrinterLinesInThis)
		m_listPrinterOutput.ResetContent();

	for (int i = 0; i < pstTicket->numberOfPrinterLinesInThis; i++)
		PrintInfo(&m_listPrinterOutput, pstTicket->stPrinterCopy[i].Flag, (char*)pstTicket->stPrinterCopy[i].line);
}

int CePosDlg::ReadTransactionFromECR(HINT hInt, HTRX hTrx)
{
	int retcode = TRAN_RESULT_OK;
	uint64 activeFlags;

	if (CTreeCtrlFindTransactionHandle(hInt, hTrx, TRUE) == FALSE)
		goto Exit;

	// This is the memory we save all trx data
	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);
	memset(pstTicket, 0x00, sizeof(ST_TICKET));

	retcode = FP3_OptionFlags(hInt, hTrx, &activeFlags, RESPONSE_FLAGS, 0 , TIMEOUT_DEFAULT);

	while (retcode == TRAN_RESULT_OK)
	{
		retcode = FP3_GetTicket(hInt, hTrx, pstTicket);
		if (retcode)
			goto Exit;

//#if (RESPONSE_FLAGS != 0)
//		if( pstTicket->totalNumberOfItems > pstTicket->numberOfItemsInThis )
//			continue;
//
//		if( pstTicket->totalNumberOfPayments > pstTicket->numberOfPaymentsInThis )
//			continue;
//
//		if( pstTicket->totalNumberOfPrinterLines > pstTicket->numberOfPrinterLinesInThis )
//			continue;
//#endif /*(RESPONSE_FLAGS == 0)*/

		// Tüm item ve printer satýrlarý geldi
		break;
	}

Exit:

	return retcode;
}

void CePosDlg::OnBnClickedButtonStatus()
{
	int retcode = TRAN_RESULT_OK;

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	if (hTrx == NULL)
	{
		MessageBox(L"Please SELECT a Transaction Handle", L"No Transaction Handle Found", MB_OK);
		return;
	}

	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	retcode = ReadTransactionFromECR(hInt, hTrx);
	if (retcode == TRAN_RESULT_OK)
		DisplayTransaction(pstTicket, TRUE);

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonPretotal3()
{
	CUserMessageDlg userMessageDlg;

//	m_stTicket.StructSize = sizeof(ST_TICKET);

	userMessageDlg.m_hInt = GetSelectedInterface();
	if (userMessageDlg.DoModal() != IDOK)
		return;

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_PrintUserMessage(&buffer[0], sizeof(buffer), userMessageDlg.stUserMeessage, userMessageDlg.numberOfUserMessages);
		AddIntoCommandBatch(L"_prepare_PrintUserMessage", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		int retcode = TRAN_RESULT_OK;

		HINT hInt = GetSelectedInterface();
		HTRX hTrx = GetSelectedTransaction();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		retcode = FP3_PrintUserMessage(hInt, hTrx, userMessageDlg.stUserMeessage, userMessageDlg.numberOfUserMessages, pstTicket);

		if (retcode != TRAN_RESULT_OK)
			HandleErrorCode(retcode);
		else
			DisplayTransaction(pstTicket, false);
	}
}

void CePosDlg::OnBnClickedButtonPrintTotalsAndPayments()
{
	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_PrintTotalsAndPayments(&buffer[0], sizeof(buffer));
		AddIntoCommandBatch(L"_prepare_PrintTotalsAndPayments", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		int retcode = FP3_PrintTotalsAndPayments(GetSelectedInterface(), GetSelectedTransaction());
		if (retcode != TRAN_RESULT_OK)
			HandleErrorCode(retcode);
	}
}

void CePosDlg::OnBnClickedButtonPrintBeforeMf()
{
	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_PrintBeforeMF(&buffer[0], sizeof(buffer));
		AddIntoCommandBatch(L"_prepare_PrintBeforeMF", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		int retcode = FP3_PrintBeforeMF(GetSelectedInterface(), GetSelectedTransaction());
		if (retcode != TRAN_RESULT_OK)
			HandleErrorCode(retcode);
	}
}

void CePosDlg::OnBnClickedButtonPrintMf()
{
	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_PrintMF(&buffer[0], sizeof(buffer));
		AddIntoCommandBatch(L"_prepare_PrintMF", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		int retcode = FP3_PrintMF(GetSelectedInterface(), GetSelectedTransaction());
		if (retcode != TRAN_RESULT_OK)
			HandleErrorCode(retcode);
	}
}

void CePosDlg::UpdateStatusDisplay(ST_GMP_PAIR_RESP *pGMPPairResp, ST_ECHO* pstEcho)
{
	m_listStatus.ResetContent();

	if (pstEcho == NULL)
		return;

#define ECR_SERVICE_MODE		0
#define ECR_USER_MODE			1
#define ECR_BLOCKED_MODE		8
#define ECR_MAINTENANCE_MODE	9
#define ECR_DEMO_MODE			10

	StatusInfo("retcode  : %04X"	, pstEcho->retcode);
	StatusInfo("kvc      : %02X%02X%02X%02X%02X%02X%02X%02X"	, pstEcho->kvc[0], pstEcho->kvc[1], pstEcho->kvc[2], pstEcho->kvc[3], pstEcho->kvc[4], pstEcho->kvc[5], pstEcho->kvc[6], pstEcho->kvc[7]);
	StatusInfo("status   : %08X"	, pstEcho->status);
	if (pstEcho->status & GMP3_STATE_BIT_PAIRED)		StatusInfo("     - GMP3_STATE_BIT_PAIRED");
	if (pstEcho->status & GMP3_STATE_BIT_KEY_EXPIRED)	StatusInfo("     - GMP3_STATE_BIT_KEY_EXPIRED");
	if (pstEcho->status & GMP3_STATE_BIT_FISCALIZED)	StatusInfo("     - GMP3_STATE_BIT_FISCALIZED");
	if (pstEcho->status & GMP3_STATE_BIT_OKC_MALI_MOD)	StatusInfo("     - GMP3_STATE_BIT_OKC_MALI_MOD");
	if (pstEcho->status & GMP3_STATE_BIT_PARAMETRE)	StatusInfo("     - GMP3_STATE_BIT_PARAMETRE");
	if (pstEcho->status & GMP3_STATE_BIT_NO_PAPER)		StatusInfo("     - GMP3_STATE_BIT_NO_PAPER");
	StatusInfo("Marka    : %s", pGMPPairResp->szEcrBrand);
	StatusInfo("Model    : %s", pGMPPairResp->szEcrModel);
	StatusInfo("S/N      : %s", pGMPPairResp->szEcrSerialNumber);
	StatusInfo("ECR SW V : %s", pstEcho->ecrVersion);

	switch (pstEcho->ecrMode)
	{
	case ECR_SERVICE_MODE:
		StatusInfo("Mode     : %s", "ECR_SERVICE_MODE");
		break;
	case ECR_USER_MODE:
		StatusInfo("Mode     : %s", "ECR_USER_MODE");
		break;
	case ECR_BLOCKED_MODE:
		StatusInfo("Mode     : %s", "ECR_BLOCKED_MODE");
		break;
	case ECR_MAINTENANCE_MODE:
		StatusInfo("Mode     : %s", "ECR_MAINTENANCE_MODE");
		break;
	case ECR_DEMO_MODE:
		StatusInfo("Mode     : %s", "ECR_DEMO_MODE");
		break;
	default:
		StatusInfo("Mode     : %s", "ECR_INVALID_MODE");
		break;
	}

	StatusInfo("Ksyr Indx: %d / %s"	, pstEcho->activeCashier.index , pstEcho->activeCashier.name);
	StatusInfo("Ksyr flag: %08X"	, pstEcho->activeCashier.flags);
	StatusInfo("MTU Size : %d*1024+%d bytes"	, pstEcho->mtuSize / 1024, pstEcho->mtuSize % 1024);
}

int CePosDlg::Echo()
{
	int retcode = 0;

	HINT hInt = GetSelectedInterface();

	ST_INTERFACE_DATA* pstInterfaceData = GetInterfaceDataPointer(hInt);
	if (pstInterfaceData == NULL)
		return retcode;

	memset(&pstInterfaceData->stEcho , 0x00, sizeof(ST_ECHO));
	retcode = FP3_Echo(hInt, &pstInterfaceData->stEcho);

	UpdateStatusDisplay(&m_GMPPairResp, &pstInterfaceData->stEcho);

	HandleErrorCode(retcode);
	return retcode;
}

void CePosDlg::OnBnClickedButtonEcho()
{
	Echo();
}

void CePosDlg::OnTransactionLoyalty(void)
{
	uint16 currency = 0;

	CPaymentApplication stPaymentApplicationInfoDlg;
	CVasLoyaltyService  stVasLoyaltyServiceInfoDlg;
	int					retcode = TRAN_RESULT_OK;
	ST_TICKET           stTicket;
	CLoyaltySelection   stLoyaltyProcessSelectionDlg;
	ST_LOYALTY_SERVICE_REQ stLoyaltyServiceReq;
	ST_PAYMENT_REQUEST  stPaymentRequest[1];
	CDoPayment			doPayment;
	uint32				Amount;
//	uint32				changedAmount;
	uint8				uniqueId[24];
	uint64				activeFlags;
	uint16				Currency;
	uint8				i;

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	memset(uniqueId, 0x00, sizeof(uniqueId));

	if (hTrx == NULL)
	{
		MessageBox(L"Lütfen Ýþlem Baþlatýnýz", L"HATA", MB_OK);
		goto EXIT;
	}

	memset(&stTicket, 0, sizeof(stTicket));

	retcode = FP3_OptionFlags(hInt, hTrx, &activeFlags,  RESPONSE_FLAGS, 0x00000000, TIMEOUT_DEFAULT);
	if (retcode != TRAN_RESULT_OK)
		goto EXIT;

	retcode = FP3_GetTicket(hInt, hTrx, &stTicket);
	if (retcode != TRAN_RESULT_OK)
	{
		goto EXIT;
	}

	if (stLoyaltyProcessSelectionDlg.DoModal() != IDOK)
		goto EXIT;

	GetTypedAmount(&Amount, &Currency);

	if (stLoyaltyProcessSelectionDlg.m_Value == IDC_RADIO_MUSTERI_SORGU)
	{
		retcode = FP3_GetVasApplicationInfo(hInt, &stPaymentApplicationInfoDlg.numberOfTotalRecords, &stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.stPaymentApplicationInfo, TLV_OKC_ASSIST_VAS_TYPE_LOYALTY);
		if (retcode != TRAN_RESULT_OK)
			HandleErrorCode(retcode);
		else if (stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
			MessageBox(L"ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý", L"HATA", MB_OK);
		else
		{
			if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
				goto EXIT;

			if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected == NULL)
			{
				MessageBox(L"Lütfen UYGULAMA Seçiniz", L"HATA", MB_OK);
				goto EXIT;
			}

			if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId == 0)
			{
				MessageBox(L"UYGULAMA ID == 0", L"HATA", MB_OK);
				goto EXIT;
			}

			retcode = FP3_GetVasLoyaltyServiceInfo(GetSelectedInterface(), &stVasLoyaltyServiceInfoDlg.numberOfTotalRecords, &stVasLoyaltyServiceInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId, stVasLoyaltyServiceInfoDlg.stVasLoyaltyServiceInfo);
			if (retcode != TRAN_RESULT_OK)
				HandleErrorCode(retcode);
			else if (stVasLoyaltyServiceInfoDlg.numberOfTotalRecordsReceived == 0)
				MessageBox(L"ÖKC Üzerinde Servis Listesi Bulunamadý", L"HATA", MB_OK);
			else
			{
				if (stVasLoyaltyServiceInfoDlg.DoModal() != IDOK)
					goto EXIT;

				if (stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected == NULL)
				{
					MessageBox(L"Lütfen Servis Seçiniz", L"HATA", MB_OK);
					goto EXIT;
				}

				memset(&stLoyaltyServiceReq, 0x00, sizeof(stLoyaltyServiceReq));

				GetStringInput(L"QR CODE ?",  stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->CustomerId);

				stLoyaltyServiceReq.ServiceId  = stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->ServiceId;
				stLoyaltyServiceReq.u16AppId   = stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->u16AppId;

				strcpy(stLoyaltyServiceReq.CustomerId, stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->CustomerId);
				stLoyaltyServiceReq.CustomerIdType = LOYALTY_CUSTOMER_ID_TYPE_MUSTERI_NO; // HOPI icin gerekli deger

				stLoyaltyServiceReq.Amount = Amount;

				stLoyaltyServiceReq.IsBenefit = TRUE;

				strcpy((char *) stLoyaltyServiceReq.rawData    , "RAW DATA FROM EXTERNAL DEVICE TO LOYALTY APPLICATION");
				stLoyaltyServiceReq.rawDataLen = (uint16) strlen("RAW DATA FROM EXTERNAL DEVICE TO LOYALTY APPLICATION");

				retcode = FP3_LoyaltyCustomerQuery(hInt, hTrx, &stLoyaltyServiceReq, &stTicket, 5 * 60 * TIMEOUT_DEFAULT);
				if (retcode != TRAN_RESULT_OK)
					goto EXIT;
			}
		}
	}
	else
	{
		if (Amount == 0)
		{
			MessageBox(L"LÜTFEN TUTAR GÝRÝNÝZ", L"HATA", MB_OK);
			goto EXIT;
		}

		if (stTicket.totalNumberOfItems == 0 && stTicket.TotalReceiptAmount == 0)
		{
			MessageBox(L"ÖDEME ALABÝLMEK ÝÇÝN LÜTFEN ÜRÜN GÝRÝNÝZ", L"HATA", MB_OK);
			goto EXIT;
		}

		if (stTicket.numberOfLoyaltyInThis == 0)
		{
			MessageBox(L"ÖDEME ALABÝLMEK ÝÇÝN LÜTFEN KAMPANYA TANIMLAYINIZ", L"HATA", MB_OK);
			goto EXIT;
		}

//		retcode = FP3_LoyaltyDiscount(hInt, hTrx, TRUE, Amount, 10, "100877", "ZUBIZU INDIRIMI", 0xFFFF, &changedAmount, &stTicket, 10*TIMEOUT_DEFAULT);

		stVasLoyaltyServiceInfoDlg.numberOfTotalRecords         = (uint8) stTicket.numberOfLoyaltyInThis;
		stVasLoyaltyServiceInfoDlg.numberOfTotalRecordsReceived = (uint8) stTicket.numberOfLoyaltyInThis;

		for (i = 0; i < stTicket.numberOfLoyaltyInThis; i++)
		{
			memcpy(stVasLoyaltyServiceInfoDlg.stVasLoyaltyServiceInfo[i].name, stTicket.stLoyaltyService[i].name, strlen((char *)stTicket.stLoyaltyService[i].name));
			stVasLoyaltyServiceInfoDlg.stVasLoyaltyServiceInfo[i].u16AppId  = stTicket.stLoyaltyService[i].u16AppId;
			stVasLoyaltyServiceInfoDlg.stVasLoyaltyServiceInfo[i].ServiceId = stTicket.stLoyaltyService[i].ServiceId;
			strcpy(stVasLoyaltyServiceInfoDlg.stVasLoyaltyServiceInfo[i].CustomerId, stTicket.stLoyaltyService[i].CustomerId);
		}

		if (stVasLoyaltyServiceInfoDlg.DoModal() != IDOK)
			goto EXIT;

		if (stLoyaltyProcessSelectionDlg.m_Value == IDC_RADIO_LOYALTY_DISCOUNT)
		{
			ST_LOYALTY_PROCESS stLoyaltyProcess;

			memset(&stLoyaltyProcess, 0x00, sizeof(stLoyaltyProcess));

			stLoyaltyProcess.Command    = 0x100;
			stLoyaltyProcess.ServiceId  = stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->ServiceId;
			strcpy((char *) stLoyaltyProcess.CustomerId, stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->CustomerId);
			stLoyaltyProcess.u16AppId   = stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->u16AppId;
			stLoyaltyProcess.Version    = 3;
			stLoyaltyProcess.LoyaltyDataLen = 512;

			memset(stLoyaltyProcess.LoyaltyData, 0x55, stLoyaltyProcess.LoyaltyDataLen);
			retcode = FP3_LoyaltyProcess(hInt, hTrx, &stLoyaltyProcess, &stTicket, 60 * TIMEOUT_DEFAULT);
//		retcode = FP3_LoyaltyDiscount(hInt, hTrx, TRUE, Amount, 10, "100877", "ZUBIZU INDIRIMI", 0xFFFF, &changedAmount, &stTicket, 10*TIMEOUT_DEFAULT);
		}
		else
		{
			if (doPayment.DoModal(0) !=  IDOK)
				doPayment.m_PaymentType = 0;

			memset(stPaymentRequest, 0, sizeof(ST_PAYMENT_REQUEST));

			stPaymentRequest[0].typeOfPayment			= doPayment.m_PaymentType;
			stPaymentRequest[0].subtypeOfPayment		= 0;
			stPaymentRequest[0].payAmount				= Amount;
			stPaymentRequest[0].payAmountCurrencyCode	= Currency;
			stPaymentRequest[0].bankBkmId				= stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->u16AppId;
			stPaymentRequest[0].numberOfinstallments	= 0;
			stPaymentRequest[0].LoyaltyServiceId		= stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->ServiceId;
			strcpy(stPaymentRequest[0].LoyaltyCustomerId, stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->CustomerId);

			retcode = GetPayment(stPaymentRequest, 1);
		}
	}

	DisplayTransaction(&stTicket, false);

EXIT:
	HandleErrorCode(retcode);
}

void CePosDlg::OnPaymentByVas(uint32 amount)
{
	uint16 currency = 0;

	CPaymentApplication stPaymentApplicationInfoDlg;
	CVasPaymentService  stVasPaymentServiceInfoDlg;

	int retcode = FP3_GetVasApplicationInfo(GetSelectedInterface(), &stPaymentApplicationInfoDlg.numberOfTotalRecords, &stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.stPaymentApplicationInfo, TLV_OKC_ASSIST_VAS_TYPE_PAYMENT);
	if (retcode != TRAN_RESULT_OK)
		HandleErrorCode(retcode);
	else if (stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
		MessageBox(L"ÖKC Üzerinde Ödeme Uygulamasi Bulunamadý", L"HATA", MB_OK);
	else
	{
		if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
			return;

		if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected == NULL)
		{
			MessageBox(L"Lütfen UYGULAMA Seçiniz", L"HATA", MB_OK);
			return;
		}

		retcode = FP3_GetVasPaymentServiceInfo(GetSelectedInterface(), &stVasPaymentServiceInfoDlg.numberOfTotalRecords, &stVasPaymentServiceInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId, &stVasPaymentServiceInfoDlg.stVasPaymentServiceInfo);
		if (retcode != TRAN_RESULT_OK)
		{
			HandleErrorCode(retcode);
			return;
		}

		if (stVasPaymentServiceInfoDlg.DoModal() != IDOK)
			return;

		if (stVasPaymentServiceInfoDlg.selectedPaymentService == 0xFF)
		{
			MessageBox(L"Lütfen ÖDEME Servisi Seçiniz", L"HATA", MB_OK);
			return;
		}

		ST_PAYMENT_REQUEST stPaymentRequest[1];
		memset(stPaymentRequest, 0, sizeof(ST_PAYMENT_REQUEST));

		stPaymentRequest[0].typeOfPayment			= stVasPaymentServiceInfoDlg.stVasPaymentServiceInfo.List[stVasPaymentServiceInfoDlg.selectedPaymentService].PaymentType;
		stPaymentRequest[0].subtypeOfPayment		= 0;
		stPaymentRequest[0].payAmount				= amount;
		stPaymentRequest[0].payAmountCurrencyCode	= CURRENCY_TL;
		stPaymentRequest[0].bankBkmId				= stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId;
		stPaymentRequest[0].numberOfinstallments	= 0;

		GetPayment(stPaymentRequest, 1);
	}
}
void CePosDlg::OnPaymentYemekCeki(uint32 amount)
{
	uint16 currency = 0;

	CPaymentApplication stPaymentApplicationInfoDlg;

	int retcode = FP3_GetVasApplicationInfo(GetSelectedInterface(), &stPaymentApplicationInfoDlg.numberOfTotalRecords, &stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.stPaymentApplicationInfo, TLV_OKC_ASSIST_VAS_TYPE_YEMEKCEKI);
	if (retcode != TRAN_RESULT_OK)
		HandleErrorCode(retcode);
	else if (stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
		MessageBox(L"ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý", L"HATA", MB_OK);
	else
	{
		if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
			return;

		if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected == NULL)
		{
			MessageBox(L"Lütfen UYGULAMA Seçiniz", L"HATA", MB_OK);
			return;
		}

		ST_PAYMENT_REQUEST stPaymentRequest[1];
		memset(stPaymentRequest, 0, sizeof(ST_PAYMENT_REQUEST));

		stPaymentRequest[0].typeOfPayment			= PAYMENT_YEMEKCEKI;
		stPaymentRequest[0].subtypeOfPayment		= 0;
		stPaymentRequest[0].payAmount				= amount;
		stPaymentRequest[0].payAmountCurrencyCode	= CURRENCY_TL;
		stPaymentRequest[0].bankBkmId				= stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected ?  stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId : NULL;
		stPaymentRequest[0].numberOfinstallments	= 0;

		GetPayment(stPaymentRequest, 1);
	}
}

void CePosDlg::OnBnClickedButtonCredit()
{
	uint16 currency = 0;
	uint32 amount = 0;
	CPaymentApplication stPaymentApplicationInfoDlg;

	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	if (amount == 0)
		return;

	CPaymentApplication PaymentApplicationInfoDlg;
	memset(&PaymentApplicationInfoDlg.stPaymentApplicationInfo, 0, sizeof(PaymentApplicationInfoDlg.stPaymentApplicationInfo));

	int retcode = FP3_GetPaymentApplicationInfo(GetSelectedInterface(), &PaymentApplicationInfoDlg.numberOfTotalRecords, &PaymentApplicationInfoDlg.numberOfTotalRecordsReceived, PaymentApplicationInfoDlg.stPaymentApplicationInfo, sizeof(PaymentApplicationInfoDlg.stPaymentApplicationInfo) / sizeof(ST_PAYMENT_APPLICATION_INFO));
	if (retcode != TRAN_RESULT_OK)
		HandleErrorCode(retcode);
	else if (PaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
		MessageBox(L"ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý", L"HATA", MB_OK);
	else
	{
		if (PaymentApplicationInfoDlg.DoModal() != IDOK)
			return;

		ST_PAYMENT_REQUEST stPaymentRequest[1];
		memset(stPaymentRequest, 0, sizeof(ST_PAYMENT_REQUEST));

		stPaymentApplicationInfoDlg.numberOfTotalRecords  = 5;
		stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived = 5;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[0].name		, "SELECT TRANS TYPE ON POS");
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[0].index = 0;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[1].name		, "SALE");
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[1].index = 1;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[2].name		, "INSTALMENT SALE");
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[2].index = 2;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[3].name		, "BONUS SALE");
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[3].index = 3;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[4].name		, "FORWARD SALE");
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[4].index = 4;

		if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
			return;

		switch (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->index)
		{
		case 0:
			stPaymentRequest[0].subtypeOfPayment = PAYMENT_SUBTYPE_PROCESS_ON_POS;
			break;
		case 1:
			stPaymentRequest[0].subtypeOfPayment = PAYMENT_SUBTYPE_SALE;
			break;
		case 2:
			stPaymentRequest[0].subtypeOfPayment = PAYMENT_SUBTYPE_INSTALMENT_SALE;
			break;
		case 3:
			stPaymentRequest[0].subtypeOfPayment = PAYMENT_SUBTYPE_LOYALTY_PUAN;
			break;
		case 4:
			stPaymentRequest[0].subtypeOfPayment = PAYMENT_SUBTYPE_FORWARD_SALE;
			break;
		default:
			return;
		}

		int numberOfinstallments = 0;
		int bonusAmount = 0;

		if ((stPaymentRequest[0].subtypeOfPayment == PAYMENT_SUBTYPE_PROCESS_ON_POS) || (stPaymentRequest[0].subtypeOfPayment == PAYMENT_SUBTYPE_INSTALMENT_SALE) || (stPaymentRequest[0].subtypeOfPayment == PAYMENT_SUBTYPE_FORWARD_SALE))
		{
			do
			{
				if (!GetIntegerInput(L"INSTALMENT COUNT", (int*)&numberOfinstallments))
					return;
			}
			while (numberOfinstallments > 12);
		}

		if (stPaymentRequest[0].subtypeOfPayment == PAYMENT_SUBTYPE_LOYALTY_PUAN)
		{
			// Partial bonus not supported for PAYMENT_SUBTYPE_LOYALTY_PUAN transaction
			bonusAmount = amount;
			//do
			//{
			//	bonusAmount/=100;
			//	if( !GetIntegerInput(  L"BONUS AMOUNT", (int*)&bonusAmount ) )
			//		break;
			//	bonusAmount*=100;
			//	if (!bonusAmount)
			//		break;
			//}while ( amount != bonusAmount );
		}

		stPaymentRequest[0].typeOfPayment			= PAYMENT_BANK_CARD;
		stPaymentRequest[0].payAmount				= amount;
		stPaymentRequest[0].payAmountBonus			= bonusAmount;
		stPaymentRequest[0].payAmountCurrencyCode	= currency;
		stPaymentRequest[0].bankBkmId				= PaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected ?  PaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16BKMId : NULL;
		stPaymentRequest[0].numberOfinstallments	= numberOfinstallments;

		stPaymentRequest[0].transactionFlag			= 0x00000000;
		if (m_CheckBox_Banking_Opt[0].GetCheck())
			stPaymentRequest[0].transactionFlag		|= BANK_TRAN_FLAG_MANUAL_PAN_ENTRY_NOT_ALLOWED;
		if (m_CheckBox_Banking_Opt[1].GetCheck())
			stPaymentRequest[0].transactionFlag		|= BANK_TRAN_FLAG_LOYALTY_POINT_NOT_SUPPORTED_FOR_TRANS;
		if (m_CheckBox_Banking_Opt[4].GetCheck())
			stPaymentRequest[0].transactionFlag		|= BANK_TRAN_FLAG_ALL_INPUT_FROM_EXTERNAL_SYSTEM;
		if (m_CheckBox_Banking_Opt[5].GetCheck())
			stPaymentRequest[0].transactionFlag		|= BANK_TRAN_FLAG_DO_NOT_ASK_FOR_MISSING_LOYALTY_POINT;
		if (m_CheckBox_Banking_Opt[6].GetCheck())
			stPaymentRequest[0].transactionFlag		|= BANK_TRAN_FLAG_AUTHORISATION_FOR_INVOICE_PAYMENT;
		if (m_CheckBox_Banking_Opt[7].GetCheck())
			stPaymentRequest[0].transactionFlag		|= BANK_TRAN_FLAG_SALE_WITHOUT_CAMPAIGN;

		strcpy((char*)stPaymentRequest[0].rawData, "RawData from external application for the payment application");
		stPaymentRequest[0].rawDataLen = (uint16)strlen("RawData from external application for the payment application");

		GetPayment(stPaymentRequest, 1);
	}
}

void CePosDlg::OnBnClickedButtonTicket()
{
	CTicketDlg ticketDlg;
	int retcode;
	char name[32+1] = "";
	char barcode[32+1] = "";
	ST_ITEM stItem;

	uint16 currency = 0;
	uint32 amount = 0;
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	//	if(amount==0)
	//		return;

	uint8 unitType = 0;
	uint32 itemCount = 0;
	uint8  itemCountPrecition = 0;
	GetTypedItemCount(&itemCount, &itemCountPrecition);
	if (itemCount == 0)
		itemCount = 1;

	if (ticketDlg.DoModal() != IDOK)
		return;

	memset(&stItem, 0x00, sizeof(stItem));
	stItem.type			= ITEM_TYPE_TICKET;
	stItem.subType		= ticketDlg.m_TicketType;
	stItem.deptIndex	= ticketDlg.m_departmentIndex;
	stItem.amount		= amount;
	stItem.currency		= currency;
	stItem.count		= itemCount;
	stItem.unitType		= unitType;
	stItem.pluPriceIndex = 0;
	stItem.countPrecition	= itemCountPrecition;

	/*if(m_TaxExceptional_Taxless)
		stItem.flag			|= ITEM_OPTION_TAX_EXCEPTION_TAXLESS;
	m_TaxExceptional_Taxless = false;*/

	if (m_TaxExceptional_Taxless)
		stItem.flag			|= ITEM_TAX_EXCEPTION_VAT_INCLUDED_TO_PRICE;
	m_TaxExceptional_Taxless = false;

	if (m_TaxExceptional_Vat_Excluded)
		stItem.flag			|= ITEM_TAX_EXCEPTION_VAT_NOT_INCLUDED_TO_PRICE;
	m_TaxExceptional_Vat_Excluded = false;

	strcpy(stItem.name, name);
	strcpy(stItem.barcode, barcode);

	if (m_TabCommandMode.GetCurSel() == TAB_SINGLE_COMMAND_MODE)
	{
		HINT hInt = GetSelectedInterface();
		HTRX hTrx = GetSelectedTransaction();

		retcode = StartTicket(hInt, &hTrx, TProcessSale);
		if (retcode != TRAN_RESULT_OK)
			return;

		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		if (hTrx == 0)
		{
			DisplayTransaction(pstTicket, false);
			DisplayItem(pstTicket, pstTicket->totalNumberOfItems - 1);
		}

		if (retcode = FP3_ItemSale(GetSelectedInterface(), hTrx, &stItem, pstTicket))
		{
			HandleErrorCode(retcode);
			return;
		}

		DisplayTransaction(pstTicket, false);
		DisplayItem(pstTicket, pstTicket->totalNumberOfItems - 1);
	}
	else
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		bufferLen = prepare_ItemSale(&buffer[0], sizeof(buffer), &stItem);
		AddIntoCommandBatch(L"_prepare_ItemSale", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
}


void CePosDlg::OnBnClickedButtonFiscalPrinterStart()
{
	int retcode = TRAN_RESULT_OK;

	HINT hInt = GetSelectedInterface();
	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);

	if (m_TabCommandMode.GetCurSel() ==  TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_Start(&buffer[0], (int)sizeof(buffer), ptr->m_uniqueId, (int)sizeof(ptr->m_uniqueId), NULL, 0, NULL, 0);
		AddIntoCommandBatch(L"prepare_Start", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		m_listPrinterOutput.ResetContent();

		HTRX hTrx = NULL;
		retcode = TransactionHandle_StartAndInsert(hInt, &hTrx, FALSE, ptr->m_uniqueId, sizeof(ptr->m_uniqueId));

		HandleErrorCode(retcode);
	}
}


void CePosDlg::OnBnClickedButtonRefund()
{
	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	if (StartTicket(hInt, &hTrx, TRefund))
		return;
}


void CePosDlg::OnBnClickedButtonCloseTicket()
{
	int retcode;
	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	retcode = FP3_PrintTotalsAndPayments(hInt, hTrx);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	retcode = FP3_PrintBeforeMF(hInt, hTrx);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	retcode = FP3_PrintMF(hInt, hTrx);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	TransactionHandle_CloseAndRemove(hInt, hTrx);

Exit:
	if (retcode != TRAN_RESULT_OK)
		HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonPercentDec2()
{
	CDBTranDlg dbTranDlg;

	dbTranDlg.m_hInt = GetSelectedInterface();

	dbTranDlg.DoModal();
}

void CePosDlg::OnBnClickedButtonFunction()
{
	int retcode = TRAN_RESULT_OK;
	CFunctionDlg FunctionDlg;
	COleDateTime zeroDate = (__time32_t)0;
	CPasswordDlg PasswordDlg;
	CPaymentApplication stPaymentApplicationInfoDlg;
	ST_PAYMENT_REQUEST stReversePayment;
	ST_TRANS_INQUIRY	stTransInquiry;
	CVasLoyaltyService  stVasLoyaltyServiceInfoDlg;
//	ST_LOYALTY_SERVICE_INFO stLoyaltyServiceInfo;
	ST_FUNCTION_PARAMETERS  stFunctionParameters;
	CDoPayment			doPayment;

	char	szInput[32];
	uint32	amount = 0;
	uint16  currency;
	uint8 currencyProfile = 0xFF;

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	memset(&stReversePayment, 0, sizeof(ST_PAYMENT_REQUEST));
	memset(&stTransInquiry, 0, sizeof(ST_TRANS_INQUIRY));

	if (FunctionDlg.DoModal() != IDOK)
		return;

	switch (FunctionDlg.m_FunctionFlag)
	{
	case GMP_EXT_DEVICE_FUNC_PAYMENT_VAS_IPTAL:

		GetTypedAmount(&amount, &currency);

		if (amount == 0)
		{
			MessageBox(L"LÜTFEN TUTAR GÝRÝNÝZ", L"HATA", MB_OK);
			break;
		}

		retcode = FP3_GetVasApplicationInfo(hInt, &stPaymentApplicationInfoDlg.numberOfTotalRecords, &stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.stPaymentApplicationInfo, TLV_OKC_ASSIST_VAS_TYPE_ALL);
		if (retcode != TRAN_RESULT_OK)
			break;
		else if (stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
			MessageBox(L"ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý", L"HATA", MB_OK);
		else
		{
			if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
				break;

			if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected == NULL)
			{
				MessageBox(L"Lütfen UYGULAMA Seçiniz", L"HATA", MB_OK);
				break;
			}

			if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId == 0)
			{
				MessageBox(L"UYGULAMA ID == 0", L"HATA", MB_OK);
				break;
			}

			if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->AppType == TLV_OKC_ASSIST_VAS_TYPE_LOYALTY)
			{
				retcode = FP3_GetVasLoyaltyServiceInfo(GetSelectedInterface(), &stVasLoyaltyServiceInfoDlg.numberOfTotalRecords, &stVasLoyaltyServiceInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId, stVasLoyaltyServiceInfoDlg.stVasLoyaltyServiceInfo);
				if (retcode != TRAN_RESULT_OK)
					HandleErrorCode(retcode);
				else if (stVasLoyaltyServiceInfoDlg.numberOfTotalRecordsReceived == 0)
					MessageBox(L"ÖKC Üzerinde Servis Listesi Bulunamadý", L"HATA", MB_OK);
				else
				{
					if (stVasLoyaltyServiceInfoDlg.DoModal() != IDOK)
						break;

					if (stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected == NULL)
					{
						MessageBox(L"Lütfen Servis Seçiniz", L"HATA", MB_OK);
						break;
					}

					if (doPayment.DoModal(1) != IDOK)
						return;

//					GetStringInput( L"CUSTOMER ID ?",   stReversePayment.LoyaltyCustomerId);
					GetStringInput(L"PROVISION ID ?",  stReversePayment.PaymentProvisionId);

					stReversePayment.typeOfPayment			= doPayment.m_PaymentType;
					stReversePayment.subtypeOfPayment		= NULL;
					stReversePayment.payAmount				= amount;
					stReversePayment.payAmountCurrencyCode	= currency;
					stReversePayment.bankBkmId			    = stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->u16AppId;
					stReversePayment.LoyaltyServiceId       = stVasLoyaltyServiceInfoDlg.pstVasLoyaltyServiceInfoSelected->ServiceId;
				}
			}
			else if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->AppType == TLV_OKC_ASSIST_VAS_TYPE_YEMEKCEKI)
			{
				GetStringInput(L"PROVISION ID ?",  stReversePayment.PaymentProvisionId);

				stReversePayment.typeOfPayment			= PAYMENT_YEMEKCEKI;
				stReversePayment.subtypeOfPayment		= NULL;
				stReversePayment.payAmount				= amount;
				stReversePayment.payAmountCurrencyCode	= currency;
				stReversePayment.bankBkmId			    = stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId;
			}
			else if (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->AppType == TLV_OKC_ASSIST_VAS_TYPE_PAYMENT)
			{
				if (doPayment.DoModal(1) != IDOK)
					return;

				GetStringInput(L"PROVISION ID ?",  stReversePayment.PaymentProvisionId);

				stReversePayment.typeOfPayment			= doPayment.m_PaymentType;
				stReversePayment.subtypeOfPayment		= NULL;
				stReversePayment.payAmount				= amount;
				stReversePayment.payAmountCurrencyCode	= currency;
				stReversePayment.bankBkmId			    = stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16AppId;
			}

			retcode = FP3_FunctionVasPaymentRefund(GetSelectedInterface(), &stReversePayment, 120 * 1000);
		}
		break;
	case GMP_EXT_DEVICE_FUNC_BANKA_IADE:
		if (m_csInput.GetLength())
		{
			amount = getAmount(m_csInput);
			m_csInput.Empty();
			m_EditControlInput.SetWindowTextW(m_csInput);
		}

		retcode = FP3_GetPaymentApplicationInfo(GetSelectedInterface(), &stPaymentApplicationInfoDlg.numberOfTotalRecords, &stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.stPaymentApplicationInfo, sizeof(stPaymentApplicationInfoDlg.stPaymentApplicationInfo) / sizeof(ST_PAYMENT_APPLICATION_INFO));
		if (retcode != TRAN_RESULT_OK)
		{
			HandleErrorCode(retcode);
			return;
		}
		else if (stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
		{
			MessageBox(_T("ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý"), _T("HATA"), MB_OK);
			return;
		}

		if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
			return;

		stReversePayment.bankBkmId					= stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected ?  stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16BKMId : 0;					// banka uygulamasi ise bkm Id, VAS icin telium id kullanilir...


		stReversePayment.typeOfPayment				= GMP_EXT_DEVICE_FUNC_BANKA_IADE;
		stReversePayment.payAmount					= amount;
		stReversePayment.payAmountCurrencyCode		= CURRENCY_TL;
		if (m_CheckBox_Banking_Opt[3].GetCheck())
			stReversePayment.transactionFlag		|= BANK_TRAN_FLAG_ASK_FOR_MISSING_REFUND_INPUTS;

		stPaymentApplicationInfoDlg.numberOfTotalRecords  = 15;
		stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived = 15;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[0].name		, "REFERANSLI IADE");
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[0].index = 0;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[1].name		, "PESIN IADE");   // referanssiz
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[1].index = 1;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[2].name		, "TAKSITLI IADE");   // referanssiz
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[2].index = 2;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[3].name		, "KARTSIZ REFERANSLI ÝADE");
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[3].index = 3;
		strcpy((char*)stPaymentApplicationInfoDlg.stPaymentApplicationInfo[4].name		, "KARTLI REFERANSLI ÝADE");
		stPaymentApplicationInfoDlg.stPaymentApplicationInfo[4].index = 4;

		stReversePayment.subtypeOfPayment			= PAYMENT_SUBTYPE_PROCESS_ON_POS;
		if (stPaymentApplicationInfoDlg.DoModal() == IDOK)
		{
			switch (stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->index)
			{
			case 0:
				stReversePayment.subtypeOfPayment = PAYMENT_SUBTYPE_REFERENCED_REFUND;
				break;
			case 1:
				stReversePayment.subtypeOfPayment = PAYMENT_SUBTYPE_ADVANCE_REFUND;
				break;
			case 2:
				stReversePayment.subtypeOfPayment = PAYMENT_SUBTYPE_INSTALLMENT_REFUND;
				break;
			case 3:
				stReversePayment.subtypeOfPayment = PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD;
				break;
			case 4:
				stReversePayment.subtypeOfPayment = PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD;
				break;
			default:
				break;
			}
		}

		if (stReversePayment.subtypeOfPayment == PAYMENT_SUBTYPE_ADVANCE_REFUND)
		{
			stReversePayment.payAmountBonus = 0;
			if (!GetIntegerInput(_T("LOYALTY AMOUNT TO REFUND"), (int*)&stReversePayment.payAmountBonus))
				return;
		}
		else if (stReversePayment.subtypeOfPayment == PAYMENT_SUBTYPE_INSTALLMENT_REFUND)
		{
			stReversePayment.numberOfinstallments = 1;
			if (!GetIntegerInput(_T("INSTALMENT NUMBER (1-12)"), (int*)&stReversePayment.numberOfinstallments))
				return;

			stReversePayment.payAmountBonus = 0;
			if (!GetIntegerInput(_T("LOYALTY AMOUNT TO REFUND"), (int*)&stReversePayment.payAmountBonus))
				return;
		}
		else if ((stReversePayment.subtypeOfPayment == PAYMENT_SUBTYPE_REFERENCED_REFUND)				||
				 (stReversePayment.subtypeOfPayment == PAYMENT_SUBTYPE_PROCESS_ON_POS)					||
				 (stReversePayment.subtypeOfPayment == PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD)		||
				 (stReversePayment.subtypeOfPayment == PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD))
		{
			// TODO
			strcpy(szInput, "123456789012345");
			if (!GetStringInput(_T("ORG MERCHANT ID (max 15)"), szInput))
				return;
			memcpy(stReversePayment.OrgTransData.MerchantId, szInput, MINI(sizeof(stReversePayment.OrgTransData.MerchantId), strlen(szInput)));

			////////////////// TRANSACTION TYPE//////////////////////////
			stReversePayment.OrgTransData.TransactionType = 1;
			if (!GetIntegerInput(_T("TYPE 1:SALE 2:INSTALMENT"), (int*)&stReversePayment.OrgTransData.TransactionType))
				return;

			if (stReversePayment.OrgTransData.TransactionType == 2)
			{
				////////////////// INSTALMENT//////////////////////////
				stReversePayment.OrgTransData.NumberOfinstallments = 1;
				if (!GetIntegerInput(_T("INSTALMENT NUMBER (1-12)"), (int*)&stReversePayment.OrgTransData.NumberOfinstallments))
					return;
			}

			stReversePayment.OrgTransData.TransactionAmount = 0;
			if (!GetIntegerInput(_T("ORG TRANSACTION AMOUNT"), (int*)&stReversePayment.OrgTransData.TransactionAmount))
				return;

			strcpy(szInput, "1234567890");
			if (!GetStringInput(_T("REF CODE OF TRANSACTION (max 10)"), szInput))
				return;
			memcpy(stReversePayment.OrgTransData.referenceCodeOfTransaction, szInput, MINI(sizeof(stReversePayment.OrgTransData.referenceCodeOfTransaction), strlen(szInput)));

			strcpy(szInput, "ABC123");
			if (!GetStringInput(_T("AUTH CODE (max 6)"), szInput))
				return;
			memcpy(stReversePayment.OrgTransData.AuthorizationCode, szInput, MINI(sizeof(stReversePayment.OrgTransData.AuthorizationCode), strlen(szInput)));

			strcpy(szInput, "123456789012");
			if (!GetStringInput(_T("REFRRN (max 12)"), szInput))
				return;
			memcpy(stReversePayment.OrgTransData.rrn, szInput, MINI(sizeof(stReversePayment.OrgTransData.rrn), strlen(szInput)));

			stReversePayment.OrgTransData.LoyaltyAmount = 0;
			if (!GetIntegerInput(_T("ORG LOYALTY AMOUNT"), (int*)&stReversePayment.OrgTransData.LoyaltyAmount))
				return;

			strcpy(szInput, "1510221350");
			do
			{
				if (!GetStringInput(_T("ORGINAL DATE YYMMDDHHMM"), szInput))
					return;

			}
			while (strlen(szInput) != 10);
			LongToBcd(atol(szInput), stReversePayment.OrgTransData.TransactionDate, 5);

			stReversePayment.payAmountBonus = 0;
			if (stReversePayment.OrgTransData.LoyaltyAmount)
			{
				if (!GetIntegerInput(_T("LOYALTY AMOUNT TO REFUND"), (int*)&stReversePayment.payAmountBonus))
					return;
			}
		}

		////////////////// Terminal ID //////////////////////////
		strcpy((char*)stReversePayment.terminalId, "02000462");
		if (!GetStringInput(_T("TERMINAL ID (max 8)"), (char*)stReversePayment.terminalId))
			return;

		strcpy((char*)stReversePayment.rawData, "RawData from external application for the payment application");
		stReversePayment.rawDataLen = (uint16)strlen("RawData from external application for the payment application");

		retcode = FP3_FunctionBankingRefund(GetSelectedInterface(), &stReversePayment, 120 * 1000);
		break;

	case GMP_EXT_DEVICE_FUNC_BANKA_IPTAL:
		if (m_csInput.GetLength())
		{
			amount = getAmount(m_csInput);
			m_csInput.Empty();
			m_EditControlInput.SetWindowTextW(m_csInput);
		}

		stReversePayment.typeOfPayment				= GMP_EXT_DEVICE_FUNC_BANKA_IPTAL;
		stReversePayment.subtypeOfPayment			= NULL;
		stReversePayment.payAmount					= amount;
		stReversePayment.payAmountCurrencyCode		= CURRENCY_TL;

		retcode = FP3_GetPaymentApplicationInfo(GetSelectedInterface(), &stPaymentApplicationInfoDlg.numberOfTotalRecords, &stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.stPaymentApplicationInfo, sizeof(stPaymentApplicationInfoDlg.stPaymentApplicationInfo) / sizeof(ST_PAYMENT_APPLICATION_INFO));
		if (retcode != TRAN_RESULT_OK)
		{
			HandleErrorCode(retcode);
			return;
		}
		else if (stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
		{
			MessageBox(_T("ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý"), L"HATA", MB_OK);
			return;
		}

		if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
			return;

		stReversePayment.bankBkmId					= stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected ?  stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16BKMId : 0;					// banka uygulamasi ise bkm Id, VAS icin telium id kullanilir...

		////////////////// Terminal ID //////////////////////////
		strcpy(szInput, "12345678");
		if (!GetStringInput(_T("TERMINAL ID (max 8)"), szInput))
			return;
		memcpy(stReversePayment.terminalId, szInput, MINI(sizeof(stReversePayment.terminalId), strlen(szInput)));

		////////////////// BATCH NO//////////////////////////
		stReversePayment.batchNo = 1;
		if (!GetIntegerInput(_T("BATCH NO"), (int*)&stReversePayment.batchNo))
			return;

		////////////////// STAN//////////////////////////
		stReversePayment.stanNo = 1;
		if (!GetIntegerInput(_T("STAN"), (int*)&stReversePayment.stanNo))
			return;

		strcpy((char*)stReversePayment.rawData, "RawData from external application for the payment application");
		stReversePayment.rawDataLen = (uint16)strlen("RawData from external application for the payment application");

		retcode = FP3_FunctionBankingRefund(GetSelectedInterface(), &stReversePayment, 120 * 1000);
		break;
	case GMP_EXT_DEVICE_FUNC_TRANS_INQUERY:

		retcode = FP3_GetPaymentApplicationInfo(GetSelectedInterface(), &stPaymentApplicationInfoDlg.numberOfTotalRecords, &stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived, stPaymentApplicationInfoDlg.stPaymentApplicationInfo, sizeof(stPaymentApplicationInfoDlg.stPaymentApplicationInfo) / sizeof(ST_PAYMENT_APPLICATION_INFO));
		if (retcode != TRAN_RESULT_OK)
		{
			HandleErrorCode(retcode);
			return;
		}
		else if (stPaymentApplicationInfoDlg.numberOfTotalRecordsReceived == 0)
		{
			MessageBox(_T("ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý"), L"HATA", MB_OK);
			return;
		}

		if (stPaymentApplicationInfoDlg.DoModal() != IDOK)
			return;

		stTransInquiry.BankBkmId = stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected ?  stPaymentApplicationInfoDlg.pstPaymentApplicationInfoSelected->u16BKMId : 0;					// banka uygulamasi ise bkm Id, VAS icin telium id kullanilir...

		////////////////// Terminal ID //////////////////////////
		strcpy(szInput, "12345678");
		if (!GetStringInput(_T("TERMINAL ID (max 8)"), szInput))
			return;
		memcpy(stTransInquiry.szTerminalId, szInput, MINI(sizeof(stTransInquiry.szTerminalId) - 1, strlen(szInput)));


		////////////////// BATCH NO//////////////////////////
		stTransInquiry.Batch = 1;
		if (!GetIntegerInput(_T("BATCH"), (int*)&stTransInquiry.Batch))
			return;

		////////////////// STAN//////////////////////////
		stTransInquiry.Stan = 1;
		if (!GetIntegerInput(_T("STAN"), (int*)&stTransInquiry.Stan))
			return;

		retcode = FP3_FunctionTransactionInquiry(GetSelectedInterface(), &stTransInquiry, 120 * 1000);
		break;

	case GMP_EXT_DEVICE_FUNC_BIT_CEKMECE_ACMA:
		retcode = FP3_FunctionOpenDrawer(GetSelectedInterface());
		break;

	case GMP_EXT_DEVICE_FUNC_BIT_BANKA_GUN_SONU:
	{
		uint16 numberOfreturnCodes = 0;
		ST_MULTIPLE_BANK_RESPONSE stMultipleBankReturn;

		memset(&stMultipleBankReturn, 0x00, sizeof(stMultipleBankReturn));
		stMultipleBankReturn.StructSize = sizeof(stMultipleBankReturn);

		int bkmId = 0;
		if (!GetIntegerInput(L"BKM ID (0 for all Banks)", &bkmId))
			return;
		retcode = FP3_FunctionBankingBatch(GetSelectedInterface(), (uint16)bkmId, &numberOfreturnCodes, &stMultipleBankReturn, 120 * 1000);
	}
	break;

	case GMP_EXT_DEVICE_FUNC_BIT_BANKA_PARAM_YUKLE:
		retcode = FP3_FunctionBankingParameter(GetSelectedInterface(), 120 * 1000);
		break;

	case GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE:
		retcode = FP3_FunctionEcrParameter(GetSelectedInterface(), 120 * 1000);
		break;

	case GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER:
	case GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR :
	case GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR:
	case GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR:
	case GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR:
	case GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF:
	case	GMP_EXT_DEVICE_FUNC_EKU_RAPOR_SON_FIS_KOPYA:

		if (PasswordDlg.DoModal(L"YÖNETÝCÝ ÞÝFRESÝ") != IDOK)
			break;

		memset(&stFunctionParameters, 0x00, sizeof(ST_FUNCTION_PARAMETERS));

		stFunctionParameters.start.ZNo	= FunctionDlg.m_ZNo_Start;
		stFunctionParameters.finish.ZNo = FunctionDlg.m_ZNo_Finish;
		stFunctionParameters.start.FNo	= FunctionDlg.m_FNo_Start;
		stFunctionParameters.finish.FNo = FunctionDlg.m_FNo_Finish;
		stFunctionParameters.EKUNo		= FunctionDlg.m_EkuNo;
		strcpy((char*)stFunctionParameters.Password.supervisor	, CT2A((LPCTSTR)(PasswordDlg.m_Password)));

		if (FunctionDlg.m_Date_Start != zeroDate)
		{
			stFunctionParameters.start.date.day		= FunctionDlg.m_Date_Start.GetDay();
			stFunctionParameters.start.date.month	= FunctionDlg.m_Date_Start.GetMonth();
			stFunctionParameters.start.date.year	= FunctionDlg.m_Date_Start.GetYear();
			stFunctionParameters.start.time.hour	= FunctionDlg.m_Date_Start.GetHour();
			stFunctionParameters.start.time.minute	= FunctionDlg.m_Date_Start.GetMinute();
			stFunctionParameters.start.time.second	= FunctionDlg.m_Date_Start.GetSecond();
		}

		if (FunctionDlg.m_Date_Finish != zeroDate)
		{
			stFunctionParameters.finish.date.day	= FunctionDlg.m_Date_Finish.GetDay();
			stFunctionParameters.finish.date.month	= FunctionDlg.m_Date_Finish.GetMonth();
			stFunctionParameters.finish.date.year	= FunctionDlg.m_Date_Finish.GetYear();
			stFunctionParameters.finish.time.hour	= FunctionDlg.m_Date_Finish.GetHour();
			stFunctionParameters.finish.time.minute	= FunctionDlg.m_Date_Finish.GetMinute();
			stFunctionParameters.finish.time.second	= FunctionDlg.m_Date_Finish.GetSecond();
		}

		if (FunctionDlg.m_FunctionFlag == GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER)
		{
			ST_Z_REPORT stZReport;
			memset(&stZReport, 0, sizeof(ST_Z_REPORT));
			retcode = FP3_FunctionReadZReport(GetSelectedInterface(), &stFunctionParameters, &stZReport, 120 * 1000);

			if (retcode == TRAN_RESULT_OK)
				DisplayZReport(&stZReport);
		}
		else
			retcode = FP3_FunctionReports(GetSelectedInterface(), FunctionDlg.m_FunctionFlag, &stFunctionParameters, 120 * 1000);
		break;
	}

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonPluConsole()
{
	CPluConsoleDlg PluConsoleDlg;

	PluConsoleDlg.m_hInt = GetSelectedInterface();

	if (PluConsoleDlg.DoModal() != IDOK)
		return;

}

void CePosDlg::OnBnClickedButtonFileSystemConsole()
{
	CFileSystemDlg filesystemDlg;

	filesystemDlg.m_hInt = GetSelectedInterface();
	filesystemDlg.DoModal();
}

void CePosDlg::OnBnClickedButtonEkuConsole()
{
	CEkuDlg ekuDlg;

	ekuDlg.m_hInt = GetSelectedInterface();

	ekuDlg.DoModal();
}

void CePosDlg::OnBnClickedButtonGetHandleList()
{
	HINT hInt = GetSelectedInterface();
	int retcode = ReadOpenTransactionHandleListFromECR(hInt);
	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonPing()
{
	if (m_pingTimer)
	{
		KillTimer(m_pingTimer);
		m_pingTimer = NULL;
	}
	else
		m_pingTimer = SetTimer(1, 1000, NULL);
}

void CePosDlg::OnBnClickedButtonReadCard()
{
	ST_CARD_INFO stCardInfo;

	memset(&stCardInfo, 0, sizeof(stCardInfo));
	int retcode = FP3_FunctionReadCard(GetSelectedInterface(), READER_TYPE_MCR | READER_TYPE_SCR | READER_TYPE_CLESS, &stCardInfo, 60 * 1000);

	if (retcode == TRAN_RESULT_OK)
	{
		DisplayInfo("CARD NO : %s\r\nCARD HOLDER NAME : %s", stCardInfo.pan, stCardInfo.holderName);
	}
	else
		HandleErrorCode(retcode);

}

void CePosDlg::OnBnClickedButtonGetSetFiscalHeader()
{
	ST_TICKET_HEADER stTicketHeader;
	uint16 totalNumberOfHeaderPlaces = 0;
	uint16 UsedNumberOfHeaderPlaces = 0;
	int retcode;
	CString cs;

	memset(&stTicketHeader, 0x00, sizeof(stTicketHeader));

	retcode = FP3_GetTicketHeader(GetSelectedInterface(), 0xFF, &stTicketHeader, &totalNumberOfHeaderPlaces);
	if (retcode != TRAN_RESULT_OK)
		goto EXIT;

	if (!GetStringInput(L"CUSTOMER NAME 1", stTicketHeader.szMerchName1))
		return;
	if (!GetStringInput(L"CUSTOMER NAME 2", stTicketHeader.szMerchName2))
		return;
	if (!GetStringInput(L"CUSTOMER ADDRESS 1", stTicketHeader.szMerchAddr1))
		return;
	if (!GetStringInput(L"CUSTOMER ADDRESS 2", stTicketHeader.szMerchAddr2))
		return;
	if (!GetStringInput(L"CUSTOMER ADDRESS 3", stTicketHeader.szMerchAddr3))
		return;
	if (!GetStringInput(L"CUSTOMER TAX OFFICE", stTicketHeader.VATOffice))
		return;
	if (!GetStringInput(L"CUSTOMER TAX NUMBER", stTicketHeader.VATNumber))
		return;
	if (!GetStringInput(L"CUSTOMER MERSIS NUMBER", stTicketHeader.MersisNo))
		return;
	if (!GetStringInput(L"CUSTOMER TICARI SICIL NUMBER", stTicketHeader.TicariSicilNo))
		return;
	if (!GetStringInput(L"CUSTOMER WEB", stTicketHeader.WebAddress))
		return;

	cs.Format(L"Total Space to SET Ticket Header = %d\nUsed = %d\n Free = %d", totalNumberOfHeaderPlaces, stTicketHeader.index + 1, totalNumberOfHeaderPlaces - stTicketHeader.index - 1);
	if (MessageBox(cs, L"Continue to SET a new Ticket Header", MB_OKCANCEL) != IDOK)
		return;

	retcode = FP3_FunctionChangeTicketHeader(GetSelectedInterface(), "0000", &totalNumberOfHeaderPlaces, &UsedNumberOfHeaderPlaces, &stTicketHeader);

EXIT:
	DisplayErrorMessage(retcode);
}

void CePosDlg::OnBnClickedButtonGetUniqueId()
{
	int retcode;

	HINT hInt = GetSelectedInterface();
	if (hInt == NULL)
		return;
	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);

	memset(ptr->m_uniqueId, 0x00, sizeof(ptr->m_uniqueId));
	retcode = FP3_FunctionCreateUniqueId(hInt, ptr->m_uniqueId, TIMEOUT_DEFAULT);
	if (retcode == TRAN_RESULT_OK)
	{
		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		for (int t = 0; t < 24; t++)
			sprintf(&buffer[t*2], "%02X", ptr->m_uniqueId[t]);

		DisplayInfo("UNIQUE ID: %s", buffer);
	}
	else
		HandleErrorCode(retcode);
}


void CePosDlg::OnBnClickedButtonSelectUniqueId()
{
	CSelectUniqueId SelectUniqueId;

	SelectUniqueId.m_hInt = GetSelectedInterface();

	if (SelectUniqueId.DoModal() != IDOK)
		return;

	HINT hInt = GetSelectedInterface();
	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);

	memcpy(ptr->m_uniqueId, SelectUniqueId.stUniqueIdSelected.uniqueId, sizeof(ptr->m_uniqueId));

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));

	for (int t = 0; t < 24; t++)
		sprintf(&buffer[t*2], "%02X", ptr->m_uniqueId[t]);

	DisplayInfo("UNIQUE ID: %s", buffer);
}

void CePosDlg::OnBnClickedButtonPayment()
{
	CDoPayment doPayment;

	uint16 currency = 0;
	uint32 amount = 0;
	uint8 currencyProfile = 0xFF;
	GetTypedAmount(&amount, &currency);
	if (amount == 0)
		return;

	if (doPayment.DoModal(0) !=  IDOK)
		return;

	switch (doPayment.m_PaymentType)
	{
	case PAYMENT_BANK_CARD:
		OnBnClickedButtonCredit();
		break;
	case PAYMENT_YEMEKCEKI:
		OnPaymentYemekCeki(amount);
		break;
	case PAYMENT_VAS_ALL:
		OnPaymentByVas(amount);
		break;
	case PAYMENT_CASH_CURRENCY:
	case PAYMENT_CASH_TL:
	case PAYMENT_MOBILE:
	case PAYMENT_HEDIYE_CEKI:
	case PAYMENT_IKRAM:
	case PAYMENT_ODEMESIZ:
	case PAYMENT_KAPORA:
	case PAYMENT_PUAN:
	case PAYMENT_GIDER_PUSULASI:
	case PAYMENT_BANKA_TRANSFERI:
	case PAYMENT_CEK:
	case PAYMENT_ACIK_HESAP:

		ST_PAYMENT_REQUEST stPaymentRequest[1];
		memset(stPaymentRequest, 0, sizeof(ST_PAYMENT_REQUEST));

		stPaymentRequest[0].typeOfPayment			= doPayment.m_PaymentType;
		stPaymentRequest[0].subtypeOfPayment		= NULL;
		stPaymentRequest[0].payAmount				= amount;
		stPaymentRequest[0].payAmountCurrencyCode	= currency;

		GetPayment(stPaymentRequest, 1);
		break;
	}
}

void CePosDlg::OnBnClickedButtonDatabaseConsole()
{
	CDatabaseConsole DatabaseConsole;

	DatabaseConsole.m_hInt = GetSelectedInterface();

	DatabaseConsole.DoModal();
}

void CePosDlg::Move(CWnd* pctrl, long left, long top, long width, long heigth)
{
	CRect rect;

	rect.left	= left;
	rect.right	= left + width;
	rect.top	= top;
	rect.bottom	= top + heigth;
	ScreenToClient(&rect);
	pctrl->MoveWindow(&rect);
}

void CePosDlg::ResizeControls(void)
{
#define	WIDTH_MACRO(x) (x*H_UNIT+(x-1)*MARGIN)
#define	HEIGHT_MACRO(x) ((x)*V_UNIT+((x)-1)*MARGIN)
#define	LEFT_MACRO(x)  (LEFT+(( H_UNIT+MARGIN)*(x)))
#define	TOP_MACRO(x)  (TOP+( V_UNIT+MARGIN)*(x))

	CRect rectParent;
	CRect rectParentOrg;

	GetWindowRect(&rectParent);
	GetWindowRect(&rectParentOrg);

	int MARGIN	= (rectParent.Width()  * 2) / 1000;
	if (MARGIN < 2)
		MARGIN = 2;
	int V_UNIT	= (rectParent.Height() * 18) / 1000;
	int H_UNIT	= (rectParent.Width()  * 60) / 10000;
	int LEFT	= rectParent.left	+ (8 * MARGIN);
	int RIGHT	= rectParent.right	- (8 * MARGIN);
	int TOP		= rectParent.top	+ (20 * MARGIN);
	int BOTTOM	= rectParent.bottom - (12 * MARGIN);
	int LINE	= 0;
	int COLUMN	= 0;

	//============================================== LISTS =====================================================
	LINE = 0;
	COLUMN	= 0;

	Move(&m_treeIterface			, LEFT_MACRO(COLUMN + 0)	, TOP_MACRO(LINE)		, WIDTH_MACRO(20), HEIGHT_MACRO(12));
	Move(&m_ListInterfaceSettings	, LEFT_MACRO(COLUMN + 0) , TOP_MACRO(LINE + 12)	, WIDTH_MACRO(20), HEIGHT_MACRO(4));
	Move(&m_listStatus				, LEFT_MACRO(COLUMN + 20), TOP_MACRO(LINE)		, WIDTH_MACRO(22), HEIGHT_MACRO(16));
	Move(&m_ListControlMainDisplay	, LEFT_MACRO(COLUMN + 42)	, TOP_MACRO(LINE)		, WIDTH_MACRO(59), HEIGHT_MACRO(12));
	Move(&m_TabCommandMode			, LEFT_MACRO(COLUMN + 101), TOP_MACRO(LINE)		, RIGHT - (LEFT_MACRO(COLUMN + 101)), HEIGHT_MACRO(44));
	Move(&m_listTransaction		, LEFT_MACRO(COLUMN + 102), TOP_MACRO(LINE + 2)		, RIGHT - (LEFT_MACRO(COLUMN + 103)), HEIGHT_MACRO(18));

	int widthOfListCtrl = RIGHT - (LEFT_MACRO(COLUMN + 103));
	Move(&m_listBatchCommand					, LEFT_MACRO(COLUMN + 102), TOP_MACRO(LINE + 2)	, widthOfListCtrl, HEIGHT_MACRO(38));
	Move(&m_ListMasterECRMode					, LEFT_MACRO(COLUMN + 102), TOP_MACRO(LINE + 2)	, widthOfListCtrl, HEIGHT_MACRO(38));
	Move(&m_Button_BatchCommand_Send			, LEFT_MACRO(COLUMN + 102) + widthOfListCtrl / 3*0, TOP_MACRO(LINE + 40), widthOfListCtrl / 3	, HEIGHT_MACRO(3));
	Move(&m_Button_BatchCommand_ListenAndSend	, LEFT_MACRO(COLUMN + 102) + widthOfListCtrl / 3*1, TOP_MACRO(LINE + 40), widthOfListCtrl / 3	, HEIGHT_MACRO(3));
	Move(&m_Button_BatchCommand_ClearList		, LEFT_MACRO(COLUMN + 102) + widthOfListCtrl / 3*2, TOP_MACRO(LINE + 40), widthOfListCtrl / 3	, HEIGHT_MACRO(3));

	Move(&m_ButtonListenMEcr					, LEFT_MACRO(COLUMN + 102) + widthOfListCtrl / 4*0, TOP_MACRO(LINE + 40), widthOfListCtrl / 4	, HEIGHT_MACRO(3));
	Move(&m_ButtonGetMEcrBGTrxList				, LEFT_MACRO(COLUMN + 102) + widthOfListCtrl / 4*1, TOP_MACRO(LINE + 40), widthOfListCtrl / 4	, HEIGHT_MACRO(3));
	Move(&m_ButtonGetMEcrBGTrxData				, LEFT_MACRO(COLUMN + 102) + widthOfListCtrl / 4*2, TOP_MACRO(LINE + 40), widthOfListCtrl / 4	, HEIGHT_MACRO(3));
	Move(&m_ButtonSetMEcrBGTrxStatus			, LEFT_MACRO(COLUMN + 102) + widthOfListCtrl / 4*3, TOP_MACRO(LINE + 40), widthOfListCtrl / 4	, HEIGHT_MACRO(3));

	m_listBatchCommand.SetColumnWidth(0, 32);
	m_listBatchCommand.SetColumnWidth(1, ((widthOfListCtrl - 32)*2 / 4) - 2);
	m_listBatchCommand.SetColumnWidth(2, ((widthOfListCtrl - 32)*2 / 4) - 2);

	LINE  = 12;
	Move(&m_EditControlInput		, LEFT_MACRO(COLUMN + 42)	, TOP_MACRO(LINE), WIDTH_MACRO(59), HEIGHT_MACRO(4));
	LINE = 20;
	Move(&m_TabFunctionalControls	, LEFT_MACRO(COLUMN + 0)	, TOP_MACRO(LINE), WIDTH_MACRO(42), HEIGHT_MACRO(24));
	Move(&m_listPrinterOutput			, LEFT_MACRO(COLUMN + 102), TOP_MACRO(LINE), RIGHT - (LEFT_MACRO(COLUMN + 103)), HEIGHT_MACRO(23));

	//==============================================  =====================================================
	LINE = 16;
	COLUMN	= 2;
	Move(&m_Button_GetHandleList	, LEFT_MACRO(COLUMN + 0) 	, TOP	+ (V_UNIT + MARGIN)*LINE/*+V_UNIT*/, WIDTH_MACRO(10), HEIGHT_MACRO(3));
	Move(&m_Button_Ping			, LEFT_MACRO(COLUMN + 10)	, TOP	+ (V_UNIT + MARGIN)*LINE/*+V_UNIT*/, WIDTH_MACRO(10), HEIGHT_MACRO(3));
	Move(&m_Button_Echo			, LEFT_MACRO(COLUMN + 20)	, TOP	+ (V_UNIT + MARGIN)*LINE/*+V_UNIT*/, WIDTH_MACRO(10), HEIGHT_MACRO(3));
	Move(&m_Button_Pair			, LEFT_MACRO(COLUMN + 30)	, TOP	+ (V_UNIT + MARGIN)*LINE/*+V_UNIT*/, WIDTH_MACRO(10), HEIGHT_MACRO(3));

	//==============================================  =====================================================
	LINE = 16;
	COLUMN	= 43;
	Move(&m_Button_TicketSale			, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE + V_UNIT, WIDTH_MACRO(12), HEIGHT_MACRO(3));
	Move(&m_Button_PLUSale				, LEFT_MACRO(COLUMN + 12), TOP	+ (V_UNIT + MARGIN)*LINE + V_UNIT, WIDTH_MACRO(12), HEIGHT_MACRO(3));
	COLUMN++;
	Move(&m_comboBoxCurrency			, LEFT_MACRO(COLUMN + 24), TOP + (V_UNIT + MARGIN)*LINE + V_UNIT, WIDTH_MACRO(16), HEIGHT_MACRO(3));
	Move(&m_Button_ReadTransactionFromECR	, LEFT_MACRO(COLUMN + 40), TOP + (V_UNIT + MARGIN)*LINE + V_UNIT, WIDTH_MACRO(8), HEIGHT_MACRO(3));
	Move(&m_Button_VoidAllTicket		, LEFT_MACRO(COLUMN + 48), TOP + (V_UNIT + MARGIN)*LINE + V_UNIT, WIDTH_MACRO(8), HEIGHT_MACRO(3));

	//============================================== FUNCTIONS =====================================================
	COLUMN	= 1;

	LINE = 24;
	Move(&m_Button_IncreaseAmount		, LEFT_MACRO(COLUMN + 0), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_IncreasePercent		, LEFT_MACRO(COLUMN + 8), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_DecreaseAmount		, LEFT_MACRO(COLUMN + 16), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_DecreasePercent		, LEFT_MACRO(COLUMN + 24), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_KasaAvans			, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_KasaPayment			, LEFT_MACRO(COLUMN + 8), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_CariHesap			, LEFT_MACRO(COLUMN + 16), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_VoidItem			, LEFT_MACRO(COLUMN + 0), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_Taxless				, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_Vat_Excluded		, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_CheckPairingStatus		, LEFT_MACRO(COLUMN + 16), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));

	LINE = 24;
	Move(&m_Button_Invoice				, LEFT_MACRO(COLUMN + 0)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_OtoparkEntryTicket	, LEFT_MACRO(COLUMN + 8)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_Refund				, LEFT_MACRO(COLUMN + 16)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_YemekCeki			, LEFT_MACRO(COLUMN + 24)	, TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_Loyalty 			, LEFT_MACRO(COLUMN + 32)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_TaxfreeSet					, LEFT_MACRO(COLUMN + 0), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_TaxfreeSetTaxrefundAmount	, LEFT_MACRO(COLUMN + 8), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_SetExchangeProfile 	, LEFT_MACRO(COLUMN + 16), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_SetOnlineInvoice					, LEFT_MACRO(COLUMN + 0), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_TaxFreeInfo					, LEFT_MACRO(COLUMN + 8), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));

	LINE = 24;
	Move(&m_Button_OpenHandle			, LEFT_MACRO(COLUMN + 0)	, TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_TicketHeader		, LEFT_MACRO(COLUMN + 8)	, TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_OptionFlags			, LEFT_MACRO(COLUMN + 16)	, TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_TestTransaction		, LEFT_MACRO(COLUMN + 24)	, TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_PaymentCash			, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_JumpEcr_ForCompletePayment	, LEFT_MACRO(COLUMN + 0), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_Condition			, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_PrintTotals			, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_PrintPreMF			, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_PrintMF				, LEFT_MACRO(COLUMN + 16), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_CloseHandle			, LEFT_MACRO(COLUMN + 24), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));

	LINE = 24;
	Move(&m_Button_SelectUniqueId		, LEFT_MACRO(COLUMN + 0)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_GetUniqueId			, LEFT_MACRO(COLUMN + 8)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_PluRead				, LEFT_MACRO(COLUMN + 16)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_GetSetFiscalHeader	, LEFT_MACRO(COLUMN + 24)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_Functions			, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_ReadCard			, LEFT_MACRO(COLUMN + 8), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_UserMessage			, LEFT_MACRO(COLUMN + 16), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_ExchangeTable		, LEFT_MACRO(COLUMN + 24), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_JumpEcr_ForSinglePayment	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_SetCommScenario				, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_GetSetCurrencyProfile	, LEFT_MACRO(COLUMN + 16), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_SetuApplicationCommand	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_GetInput				, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));

	LINE = 24;
	Move(&m_Button_PLUConsole			, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_CashierConsole		, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_EKUConsole			, LEFT_MACRO(COLUMN + 16), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_TransactionConsole	, LEFT_MACRO(COLUMN + 24), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_DatabaseConsole		, LEFT_MACRO(COLUMN + 32), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_TaxDepartments		, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_FileSystemConsole	, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));

	LINE = 24;
	Move(&m_CheckBox_Banking_Opt[0]	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*(LINE + 0), WIDTH_MACRO(20), HEIGHT_MACRO(2));
	Move(&m_CheckBox_Banking_Opt[1]	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*(LINE + 2), WIDTH_MACRO(20), HEIGHT_MACRO(2));
	Move(&m_CheckBox_Banking_Opt[2]	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*(LINE + 4), WIDTH_MACRO(20), HEIGHT_MACRO(2));
	Move(&m_CheckBox_Banking_Opt[3]	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*(LINE + 6), WIDTH_MACRO(20), HEIGHT_MACRO(2));
	Move(&m_CheckBox_Banking_Opt[4]	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*(LINE + 8), WIDTH_MACRO(20), HEIGHT_MACRO(2));
	Move(&m_CheckBox_Banking_Opt[5]	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*(LINE + 10), WIDTH_MACRO(20), HEIGHT_MACRO(2));
	Move(&m_CheckBox_Banking_Opt[6]	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*(LINE + 12), WIDTH_MACRO(20), HEIGHT_MACRO(2));
	Move(&m_CheckBox_Banking_Opt[7]	, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*(LINE + 14), WIDTH_MACRO(20), HEIGHT_MACRO(2));

	//======================================== DEPARTMENT =============================================================
	LINE = 20;
	COLUMN	= 43;
	Move(&m_ButtonDepartman1, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	Move(&m_ButtonDepartman7, LEFT_MACRO(COLUMN + 12), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_ButtonDepartman2, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	Move(&m_ButtonDepartman8, LEFT_MACRO(COLUMN + 12), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_ButtonDepartman3, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	Move(&m_ButtonDepartman9, LEFT_MACRO(COLUMN + 12), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_ButtonDepartman4, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	Move(&m_ButtonDepartman10, LEFT_MACRO(COLUMN + 12), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_ButtonDepartman5, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	Move(&m_ButtonDepartman11, LEFT_MACRO(COLUMN + 12), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_ButtonDepartman6, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));
	Move(&m_ButtonDepartman12, LEFT_MACRO(COLUMN + 12), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(12), HEIGHT_MACRO(4));

	//================================================================================================================
	LINE = 20;
	COLUMN	= 68;
	Move(&m_Button_MoneyCollection	, LEFT_MACRO(COLUMN + 0)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_VoidMatrahsiz	, LEFT_MACRO(COLUMN + 8), TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_ReversePayments	, LEFT_MACRO(COLUMN + 24)	, TOP + (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_1				, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_2				, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_3				, LEFT_MACRO(COLUMN + 16), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_PaymentList		, LEFT_MACRO(COLUMN + 24), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_4				, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_5				, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_6				, LEFT_MACRO(COLUMN + 16), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_PaymentDoAny	, LEFT_MACRO(COLUMN + 24), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_7				, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_8				, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_9				, LEFT_MACRO(COLUMN + 16), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_PaymentDoCredit	, LEFT_MACRO(COLUMN + 24), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_00				, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_0				, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_Point			, LEFT_MACRO(COLUMN + 16), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_PaymentDoCash	, LEFT_MACRO(COLUMN + 24), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	LINE += 4;
	Move(&m_Button_Multiply		, LEFT_MACRO(COLUMN + 0), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_Backspace		, LEFT_MACRO(COLUMN + 8), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_Subtotal		, LEFT_MACRO(COLUMN + 16), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));
	Move(&m_Button_CloseTicket		, LEFT_MACRO(COLUMN + 24), TOP	+ (V_UNIT + MARGIN)*LINE, WIDTH_MACRO(8), HEIGHT_MACRO(4));

}

void CePosDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);
	ResizeControls();
}

void CePosDlg::OnSelchangeTabCommandMode(NMHDR *pNMHDR, LRESULT *pResult)
{
	int command = SW_HIDE;
	m_listPrinterOutput.ShowWindow(command);
	m_listTransaction.ShowWindow(command);
	m_listBatchCommand.ShowWindow(command);
	m_ListMasterECRMode.ShowWindow(command);

	m_Button_BatchCommand_Send.ShowWindow(command);
	m_Button_BatchCommand_ListenAndSend.ShowWindow(command);
	m_Button_BatchCommand_ClearList.ShowWindow(command);

	m_ButtonListenMEcr.ShowWindow(command);
	m_ButtonGetMEcrBGTrxList.ShowWindow(command);
	m_ButtonGetMEcrBGTrxData.ShowWindow(command);
	m_ButtonSetMEcrBGTrxStatus.ShowWindow(command);

	command = SW_SHOW;
	switch (m_TabCommandMode.GetCurSel())
	{
	case TAB_SINGLE_COMMAND_MODE:
		m_listPrinterOutput.ShowWindow(command);
		m_listTransaction.ShowWindow(command);
		break;
	case TAB_BATCH_COMMAND_MODE:
		m_listBatchCommand.ShowWindow(command);

		m_Button_BatchCommand_Send.ShowWindow(command);
		m_Button_BatchCommand_ListenAndSend.ShowWindow(command);
		m_Button_BatchCommand_ClearList.ShowWindow(command);
		break;
	case TAB_MASTERECR_MODE:
		m_ListMasterECRMode.ShowWindow(command);

		m_ButtonListenMEcr.ShowWindow(command);
		m_ButtonGetMEcrBGTrxList.ShowWindow(command);
		m_ButtonGetMEcrBGTrxData.ShowWindow(command);
		m_ButtonSetMEcrBGTrxStatus.ShowWindow(command);
		break;
	}

	if (pResult)
		*pResult = 0;
}

void CePosDlg::OnSelchangeTabFunctionalControls(NMHDR *pNMHDR, LRESULT *pResult)
{
	int command = SW_HIDE;
	m_Button_VoidItem.ShowWindow(command);
	m_Button_Taxless.ShowWindow(command);
	m_Button_Vat_Excluded.ShowWindow(command);
	m_Button_IncreaseAmount.ShowWindow(command);
	m_Button_IncreasePercent.ShowWindow(command);
	m_Button_KasaAvans.ShowWindow(command);
	m_Button_KasaPayment.ShowWindow(command);
	m_Button_CariHesap.ShowWindow(command);
	m_Button_PluRead.ShowWindow(command);
	m_Button_GetSetFiscalHeader.ShowWindow(command);
	m_Button_DecreaseAmount.ShowWindow(command);
	m_Button_DecreasePercent.ShowWindow(command);
	m_Button_TaxfreeSet.ShowWindow(command);
	m_Button_TaxfreeSetTaxrefundAmount.ShowWindow(command);
	m_Button_CheckPairingStatus.ShowWindow(command);

	m_Button_Invoice.ShowWindow(command);
	m_Button_OtoparkEntryTicket.ShowWindow(command);
	m_Button_Refund.ShowWindow(command);
	m_Button_YemekCeki.ShowWindow(command);
	m_Button_Loyalty.ShowWindow(command);
	m_Button_SetOnlineInvoice.ShowWindow(command);
	m_Button_SetExchangeProfile.ShowWindow(command);

	m_Button_TaxFreeInfo.ShowWindow(command);

	m_Button_PLUConsole.ShowWindow(command);
	m_Button_CashierConsole.ShowWindow(command);
	m_Button_TaxDepartments.ShowWindow(command);
	m_Button_TransactionConsole.ShowWindow(command);
	m_Button_EKUConsole.ShowWindow(command);
	m_Button_DatabaseConsole.ShowWindow(command);
	m_Button_FileSystemConsole.ShowWindow(command);

	m_Button_Functions.ShowWindow(command);
	m_Button_ReadCard.ShowWindow(command);
	m_Button_UserMessage.ShowWindow(command);
	m_Button_SelectUniqueId.ShowWindow(command);
	m_Button_GetUniqueId.ShowWindow(command);
	m_Button_ExchangeTable.ShowWindow(command);
	m_Button_GetSetCurrencyProfile.ShowWindow(command);
	m_Button_SetuApplicationCommand.ShowWindow(command);
	m_Button_JumpEcr_ForSinglePayment.ShowWindow(command);
	m_Button_GetInput.ShowWindow(command);
	m_Button_SetCommScenario.ShowWindow(command);
	m_Button_JumpEcr_ForCompletePayment.ShowWindow(command);

	m_Button_OpenHandle.ShowWindow(command);
	m_Button_TicketHeader.ShowWindow(command);
	m_Button_OptionFlags.ShowWindow(command);
	m_Button_TestTransaction.ShowWindow(command);
	m_Button_PrintTotals.ShowWindow(command);
	m_Button_Condition.ShowWindow(command);
	m_Button_PrintPreMF.ShowWindow(command);
	m_Button_PrintMF.ShowWindow(command);
	m_Button_CloseHandle.ShowWindow(command);
	m_Button_PaymentCash.ShowWindow(command);

	m_CheckBox_Banking_Opt[0].ShowWindow(command);
	m_CheckBox_Banking_Opt[1].ShowWindow(command);
	m_CheckBox_Banking_Opt[2].ShowWindow(command);
	m_CheckBox_Banking_Opt[3].ShowWindow(command);
	m_CheckBox_Banking_Opt[4].ShowWindow(command);
	m_CheckBox_Banking_Opt[5].ShowWindow(command);
	m_CheckBox_Banking_Opt[6].ShowWindow(command);
	m_CheckBox_Banking_Opt[7].ShowWindow(command);

	command = SW_SHOW;
	switch (m_TabFunctionalControls.GetCurSel())
	{
	case TAB_ECR:
		m_Button_VoidItem.ShowWindow(command);
		m_Button_IncreaseAmount.ShowWindow(command);
		m_Button_IncreasePercent.ShowWindow(command);
		m_Button_KasaAvans.ShowWindow(command);
		m_Button_KasaPayment.ShowWindow(command);
		m_Button_CariHesap.ShowWindow(command);
		m_Button_DecreaseAmount.ShowWindow(command);
		m_Button_DecreasePercent.ShowWindow(command);
		m_Button_Taxless.ShowWindow(command);
		m_Button_Vat_Excluded.ShowWindow(command);
		m_Button_CheckPairingStatus.ShowWindow(command);

		break;

	case TAB_ECR_EXT:
		m_Button_TaxfreeSet.ShowWindow(command);
		m_Button_TaxfreeSetTaxrefundAmount.ShowWindow(command);
		m_Button_Invoice.ShowWindow(command);
		m_Button_OtoparkEntryTicket.ShowWindow(command);
		m_Button_Refund.ShowWindow(command);
		m_Button_YemekCeki.ShowWindow(command);
		m_Button_Loyalty.ShowWindow(command);
		m_Button_SetOnlineInvoice.ShowWindow(command);
		m_Button_TaxFreeInfo.ShowWindow(command);
		m_Button_SetExchangeProfile.ShowWindow(command);
		break;

	case TAB_BANKING:
		m_CheckBox_Banking_Opt[0].ShowWindow(command);
		m_CheckBox_Banking_Opt[1].ShowWindow(command);
		m_CheckBox_Banking_Opt[2].ShowWindow(command);
		m_CheckBox_Banking_Opt[3].ShowWindow(command);
		m_CheckBox_Banking_Opt[4].ShowWindow(command);
		m_CheckBox_Banking_Opt[5].ShowWindow(command);
		m_CheckBox_Banking_Opt[6].ShowWindow(command);
		m_CheckBox_Banking_Opt[7].ShowWindow(command);
		break;

	case TAB_CONSOLES:
		m_Button_PLUConsole.ShowWindow(command);
		m_Button_CashierConsole.ShowWindow(command);
		m_Button_TaxDepartments.ShowWindow(command);
		m_Button_TransactionConsole.ShowWindow(command);
		m_Button_EKUConsole.ShowWindow(command);
		m_Button_DatabaseConsole.ShowWindow(command);
		m_Button_FileSystemConsole.ShowWindow(command);
		break;
	case TAB_FUNCTIONS:
		m_Button_Functions.ShowWindow(command);
		m_Button_ReadCard.ShowWindow(command);
		m_Button_UserMessage.ShowWindow(command);
		m_Button_SelectUniqueId.ShowWindow(command);
		m_Button_GetUniqueId.ShowWindow(command);
		m_Button_ExchangeTable.ShowWindow(command);
		m_Button_GetSetCurrencyProfile.ShowWindow(command);
		m_Button_PluRead.ShowWindow(command);
		m_Button_JumpEcr_ForSinglePayment.ShowWindow(command);
		m_Button_GetInput.ShowWindow(command);
		m_Button_SetCommScenario.ShowWindow(command);
		m_Button_SetuApplicationCommand.ShowWindow(command);
		m_Button_GetSetFiscalHeader.ShowWindow(command);
		break;
	case TAB_DEVELOPERS:
		m_Button_OpenHandle.ShowWindow(command);
		m_Button_TicketHeader.ShowWindow(command);
		m_Button_PrintTotals.ShowWindow(command);
		m_Button_PrintPreMF.ShowWindow(command);
		m_Button_PrintMF.ShowWindow(command);
		m_Button_OptionFlags.ShowWindow(command);
		m_Button_TestTransaction.ShowWindow(command);
		m_Button_CloseHandle.ShowWindow(command);
		m_Button_PaymentCash.ShowWindow(command);
		m_Button_Condition.ShowWindow(command);
		m_Button_JumpEcr_ForCompletePayment.ShowWindow(command);
		break;
	}

	if (pResult)
		*pResult = 0;
}

void CePosDlg::OnBnClickedButtonBatchCommandSend()
{
	ProcessBatchCommand("123456789012");
}

int CePosDlg::GetBatchCommand(uint8* sendBuffer)
{
	int numberOfTotalCommands = m_listBatchCommand.GetItemCount();
	uint32 msgCommandType = 0;
	int sendBufferLen = 0;
	uint8	msgBuffer[1024*16];	// this is buffer for just one msg type (exp: GMP_FISCAL_PRINTER_REQ or GMP_EXT_DEVICE_GET ...
	uint16	msgBufferLen = 0;

	for (int i = 0; i < numberOfTotalCommands; i++)
	{
		uint8*  ptrData = NULL;
		uint16  dataLen = 0;
		uint32	dataCommandType;

		ptrData = (uint8*)m_listBatchCommand.GetItemData(i);
		if (!ptrData)
			// There is no data to send
			continue;

		// This is the data to be sent to ECR...
		memcpy((uint8*)&dataCommandType, &ptrData[0], 4);
		memcpy((uint8*)&dataLen		, &ptrData[4], 2);

		if (msgCommandType == 0)
			msgCommandType = dataCommandType;

		if (msgCommandType != dataCommandType)
		{
			// this means that the msgCommandType is changing in the list, so close the privous package..
			sendBufferLen += gmpSetTLV(&sendBuffer[sendBufferLen], msgCommandType, msgBuffer, msgBufferLen);
			msgBufferLen	= 0;
			msgCommandType	= dataCommandType;
		}

		memcpy((uint8*)&msgBuffer[msgBufferLen], &ptrData[6], dataLen);
		msgBufferLen += dataLen;
	}
	if (msgBufferLen)
	{
		// this means that the msgCommandType is changing in the list, so close the privous package..
		sendBufferLen += gmpSetTLV(&sendBuffer[sendBufferLen], msgCommandType, msgBuffer, msgBufferLen);
		msgBufferLen	= 0;
	}

	return sendBufferLen;
}

void CePosDlg::ProcessBatchCommand(char* sicilNo)
{
	int		retcode = TRAN_RESULT_OK;
	uint8	sendBuffer[1024*64];
	uint16	sendBufferLen = 0;
	ST_MULTIPLE_RETURN_CODE	stReturnCodes[1024]; // will return return codes of each subcommand
	uint32 msgCommandType = 0;
	uint8	msgBuffer[1024*16];	// this is buffer for just one msg type (exp: GMP_FISCAL_PRINTER_REQ or GMP_EXT_DEVICE_GET ...
	uint16	msgBufferLen = 0;
	uint16 numberOfreturnCodes = 0;
	uint16 tmpNumberOfreturnCodes = 0;

	memset(&stReturnCodes, 0x00, sizeof(stReturnCodes));

	// If Exists, first clear return codes colomn
	for (int i = 0; i < m_listBatchCommand.GetItemCount(); i++)
		m_listBatchCommand.SetItemText(i, 2, L"");

	// Prepare Data To Send
	sendBufferLen = GetBatchCommand(sendBuffer);
	if (sendBufferLen == 0)
		// Nothing to send...
		return;

	HTRX hTrx = GetSelectedTransaction();
	HINT hInt = GetSelectedInterface();

	ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

	if (m_ClientSocket != INVALID_SOCKET)
	{
		uint8 recvBuffer[1024*16];
		uint16 recvBufferLen = 0;

		// Reserve for len
		recvBufferLen += 2;
		// sicil
		memcpy(&recvBuffer[recvBufferLen], sicilNo, 12);
		recvBufferLen += 12;
		// Data
		memcpy(&recvBuffer[recvBufferLen], sendBuffer, sendBufferLen);
		recvBufferLen += sendBufferLen;
		// Len
		recvBuffer[0] = (recvBufferLen - 2) / 256;
		recvBuffer[1] = (recvBufferLen - 2) % 256;

		// SET Blocking Mode
		u_long iMode = 0; // 0 : Blocking Mode
		ioctlsocket(m_ClientSocket, FIONBIO, &iMode);

		DisplayInfo("Sending %d bytes", recvBufferLen);
		int sendLen = send(m_ClientSocket, (char*)recvBuffer, recvBufferLen, 0);
		if (sendLen == SOCKET_ERROR)
		{
			DisplayInfo("Client Socket Send Error = %d (%04X)", WSAGetLastError(), WSAGetLastError());
			return;
		}

		// SET Timeouts
		DWORD dwTime = 100000;
		setsockopt(m_ClientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&dwTime, sizeof(dwTime));
		DisplayInfo("Receiving...(TO=%d)", (int)dwTime);
		int recvLen = recv(m_ClientSocket, (char*)recvBuffer, sizeof(recvBuffer), 0);
		if (recvLen == SOCKET_ERROR)
		{
			DisplayInfo("Client Socket recv Error = %d (%04X)", WSAGetLastError(), WSAGetLastError());
			return;
		}

		if (recvLen == 0)
			DisplayInfo("Client socket disconnect");
		else if (recvLen > 0)
		{
			DisplayInfo("Received %d bytes", recvLen);

			uint8* recvFullBuffer = &recvBuffer[2+12]; // exclude 2 bytes len + sicil No
			uint16 recvFullBufferLen = recvLen - 14;
			uint16 recvbufferReadLen = 0;

			while (recvbufferReadLen < recvFullBufferLen)
			{
				uint32 msgCommandType = 0;
				msgBufferLen = 0;

				recvbufferReadLen += gmpReadTLVtag(&msgCommandType	, &recvFullBuffer[recvbufferReadLen]);
				recvbufferReadLen += gmpReadTLVlen(&msgBufferLen		, &recvFullBuffer[recvbufferReadLen]);

				memcpy(msgBuffer, &recvFullBuffer[recvbufferReadLen] , msgBufferLen);
				recvbufferReadLen += msgBufferLen;

				// Preceed received message
				switch (msgCommandType)
				{
				case GMP3_FISCAL_PRINTER_MODE_RES:
				case GMP3_FISCAL_PRINTER_MODE_RES_E:
					retcode = parse_FiscalPrinter(&stReturnCodes[numberOfreturnCodes], &tmpNumberOfreturnCodes, msgCommandType, msgBuffer, msgBufferLen, pstTicket);
					numberOfreturnCodes += tmpNumberOfreturnCodes;
					break;
				case GMP3_EXT_DEVICE_GET_DATA_RES:
				case GMP3_EXT_DEVICE_GET_DATA_RES_E:
					retcode = parse_GetEcr(&stReturnCodes[numberOfreturnCodes], &tmpNumberOfreturnCodes, msgCommandType, msgBuffer, msgBufferLen);
					numberOfreturnCodes += tmpNumberOfreturnCodes;
					break;
				}
			}
		}
		else
			DisplayInfo("Client socket error");

		iMode = 1; // 0 : Blocking Mode
		ioctlsocket(m_ClientSocket, FIONBIO, &iMode);
	}
	else
	{
		uint16 proccessedBufferReadLen = 0;
		uint16 tmpNumberOfreturnCodes = 0;

		while ((proccessedBufferReadLen < sendBufferLen) && (retcode == TRAN_RESULT_OK))
		{
			proccessedBufferReadLen += gmpReadTLVtag(&msgCommandType	, &sendBuffer[proccessedBufferReadLen]);
			proccessedBufferReadLen += gmpReadTLVlen(&msgBufferLen	, &sendBuffer[proccessedBufferReadLen]);
			memcpy(msgBuffer, &sendBuffer[proccessedBufferReadLen] , msgBufferLen);
			proccessedBufferReadLen += msgBufferLen;
			tmpNumberOfreturnCodes = 0;

			// Preceed received message
			switch (msgCommandType)
			{
			case GMP3_FISCAL_PRINTER_MODE_REQ:
			case GMP3_FISCAL_PRINTER_MODE_REQ_E:
				// Send to ECR and wait for the response (one error code for each sub command until one of them is failed !!)
				retcode = FP3_MultipleCommand(GetSelectedInterface(), &hTrx, &stReturnCodes[numberOfreturnCodes], &tmpNumberOfreturnCodes, msgBuffer, msgBufferLen, pstTicket, 1000 * 100);
				numberOfreturnCodes += tmpNumberOfreturnCodes;
				break;
			case GMP3_EXT_DEVICE_GET_DATA_REQ:
			case GMP3_EXT_DEVICE_GET_DATA_REQ_E:
				// Send to ECR and wait for the response (one error code for each sub command until one of them is failed !!)
				retcode = GetDialogInput_MultipleCommand(&stReturnCodes[numberOfreturnCodes], &tmpNumberOfreturnCodes, msgBuffer, msgBufferLen, 1000 * 100);
				numberOfreturnCodes += tmpNumberOfreturnCodes;
				break;
			}
		}
	}

	int indexOnListCtrl = 0;
	for (int t = 0; t < numberOfreturnCodes ; t++)
	{
		char returnCodeString[256];
		memset(returnCodeString, 0x00, sizeof(returnCodeString));

		// This is not a result of subCommand (it is a tag value in Get Response )
		if (stReturnCodes[t].indexOfSubCommand == 0)
			continue;

		// This is not a result of subCommand (it is a tag value in Get Response )
		if (stReturnCodes[t].subCommand == 0)
			continue;

		GetErrorMessage(stReturnCodes[t].retcode, returnCodeString);

		m_listBatchCommand.SetItemText(indexOnListCtrl++, 2, CString(returnCodeString));
	}

	if (retcode == TRAN_RESULT_OK)
	{
		// This does not mean all subcommands are OK, check returnCodes structure for each individual commands
		DisplayTransaction(pstTicket, false);
	}

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonBatchCommandClearList()
{
	int numberOfTotalCommands = m_listBatchCommand.GetItemCount();
	bool ErrorCodeCleared = false;

	// If Exists, first clear return codes colomn
	for (int i = 0; i < numberOfTotalCommands; i++)
	{
		CString returnCodeString;

		returnCodeString = m_listBatchCommand.GetItemText(i, 2);
		if (returnCodeString.GetLength())
		{
			m_listBatchCommand.SetItemText(i, 2, L"");
			ErrorCodeCleared = true;
		}
	}

	if (ErrorCodeCleared)
		return;

	// Then clear commands
	for (int i = 0; i < numberOfTotalCommands; i++)
	{
		uint8*  ptrData = NULL;

		ptrData = (uint8*)m_listBatchCommand.GetItemData(i);
		if (!ptrData)
			// No Data
			continue;

		free(ptrData);
	}
	m_listBatchCommand.DeleteAllItems();
}

void CePosDlg::OnBnClickedButtonBatchCommandListenAndSend()
{
	if (m_ServerSocket != INVALID_SOCKET)
	{
		closesocket(m_ServerSocket);
		WSACleanup();
		m_ServerSocket = INVALID_SOCKET;
		KillTimer(m_ServerSocketTimer);
		DisplayInfo("Server Socket Cosed !!");
		m_Button_BatchCommand_ListenAndSend.SetWindowTextW(L"NOT\nListening...");
	}
	else
	{
		ListenServerSocket(&m_ServerSocket, 4999);
		m_Button_BatchCommand_ListenAndSend.SetWindowTextW(L"Listening 4999");
		m_ServerSocketTimer = SetTimer(2, 100, NULL);
	}
}

void CePosDlg::ListenServerSocket(SOCKET *pSocket, uint16 port)
{
	WSADATA wsaData;
	int iResult;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family		= AF_INET;
	hints.ai_socktype	= SOCK_STREAM;
	hints.ai_protocol	= IPPROTO_TCP;
	hints.ai_flags		= AI_PASSIVE;

	// Resolve the server address and port
	CHAR tmp[16];
	sprintf(tmp, "%d", port);
	iResult = getaddrinfo(NULL, tmp, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		return;
	}

	// Create a SOCKET for connecting to server
	*pSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (*pSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		return;
	}

	// Setup the TCP listening socket
	iResult = bind(*pSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(*pSocket);
		*pSocket = INVALID_SOCKET;
		return;
	}

	freeaddrinfo(result);

	iResult = listen(*pSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(*pSocket);
		*pSocket = INVALID_SOCKET;
		return;
	}

	// Set Non-Blocking
	u_long iMode = 1;
	ioctlsocket(*pSocket, FIONBIO, &iMode);

	DisplayInfo("Listening TCP/IP %d", port);
}

uint16 CePosDlg::decodeTLVTag(int level, uint32 main_tag, uint8* maintag_Data, uint16 maintag_DataLen)
{
	char cTmp[128];
	memset(cTmp, 0x00, sizeof(cTmp));
	memset(cTmp, ' ', level);
	int readIndex = 0 ;

	CListBoxPrintf(&m_ListMasterECRMode, "%sTAG %X DataLen[%d]", cTmp, main_tag, maintag_DataLen);

	while (readIndex < maintag_DataLen)
	{
		uint32 tag = 0;
		uint16 tagDataLen;

		readIndex += gmpReadTLVtag(&tag		, &maintag_Data[readIndex]);
		readIndex += gmpReadTLVlen(&tagDataLen	, &maintag_Data[readIndex]);

		switch (tag)
		{
			// Function tags..
		case 0xFF8B13:
			decodeTLVTag(++level, tag, &maintag_Data[readIndex], tagDataLen);
			break;

			// Group tags..
		case 0xDF02:
			decodeTLVTag(++level, tag, &maintag_Data[readIndex], tagDataLen);
			break;

		default:
			CListBoxPrintf(&m_ListMasterECRMode, " %sTAG %X DataLen[%d]", cTmp, tag, tagDataLen);
			// &maintag_Data[readIndex], tagDataLen
			break;
		}

		readIndex += tagDataLen;
	}

	return 0;
}

uint16 CePosDlg::sendSocketData(SOCKET m_socket, uint8* tpdu, uint8* sicilNoOfClient, uint32 functionTag, uint8* Buffer, uint16 BufferLen)
{
	uint8 respMsg[16*1024];
	uint16 respMsgLen = 2;


	if (tpdu[0] == 0x60)
	{
		memcpy(&respMsg[respMsgLen], tpdu, 5);
		respMsgLen += 5;
	}

	// sicilno
	memcpy(&respMsg[respMsgLen], sicilNoOfClient, 12);
	respMsgLen += 12;

	// Function
	respMsgLen += gmpSetTLV(&respMsg[respMsgLen], functionTag, Buffer, BufferLen);

	respMsg[0] = (respMsgLen - 2) / 256;
	respMsg[1] = (respMsgLen - 2) % 256;

	uint8 lrc = 0;
	for (int i = 2; i < respMsgLen; i++)
		lrc ^= respMsg[i];

	respMsg[respMsgLen++] = lrc;

	// SET Blocking Mode
	u_long iMode = 0; // 0 : Blocking Mode
	ioctlsocket(m_socket, FIONBIO, &iMode);

	DisplayInfo("Sending %d bytes", respMsgLen);
	int sendLen = send(m_socket, (char*)respMsg, respMsgLen, 0);
	if (sendLen == SOCKET_ERROR)
	{
		DisplayInfo("Client Socket Send Error = %d (%04X)", WSAGetLastError(), WSAGetLastError());
		return 1;
	}

	return 0;
}

uint16	CePosDlg::ingSetTLV(uint8 *pmsg, uint16 Tag, uint8 *pdata, uint16 dataLen)
{
	memcpy(&pmsg[0], (uint8*)&Tag, 2);
	memcpy(&pmsg[2], (uint8*)&dataLen, 2);
	memcpy(&pmsg[4], (uint8*)pdata, dataLen);

	return dataLen + 4;
}


uint16 CePosDlg::processECRMessage(SOCKET m_socket, uint8* recvBuffer, uint16 recvLen)
{
#define SEGMENTATION 1500

	int retcode = TRAN_RESULT_OK;
	uint16 readIndex = 0;
	uint8 sicilNoOfClient[16];
	uint32 FunctionTag = 0;
	uint8* FunctionDataPtr = NULL;
	uint16 FunctionDataLen = 0;
	int level = 1;
	uint8 tpdu[5];
	static uint32 numberOfHandlesProcessed = 0;
	static uint32 numberOfCommandsProcessed = 0;

	uint8  devam = 0;

	uint32 servisId = 1234;
	uint8 Buffer[32*1024];
	uint16 buf_len = 0;

	uint8  veriGrubu_DF63[SEGMENTATION+1024];
	uint16 veriGrubu_DF63_len = 0;

	uint8  veriGrubu_DFE902[SEGMENTATION+1024];
	uint16 veriGrubu_DFE902_len = 0;

	memset(tpdu, 0, sizeof(tpdu));
	memset(sicilNoOfClient, 0, sizeof(sicilNoOfClient));

	HINT hInt = GetSelectedInterface();

	if (recvLen < 24)
	{
		CListBoxPrintf(&m_ListMasterECRMode, "INVALID Msg: Recived Len too short, %d bytes", recvLen);
		return 0;
	}

	uint16 expectedLen = (recvBuffer[0] * 0xFF) + recvBuffer[1];
	if (recvLen != (expectedLen + 3))
	{
		CListBoxPrintf(&m_ListMasterECRMode, "INVALID Msg: Recived Len:%d, Expected:%d", recvLen, expectedLen + 2);
		return 0;
	}

	// LRC Check...
	recvLen--;

	// Lenght of the msg
	readIndex += 2;

	if (recvBuffer[readIndex] == 0x60)
	{
		memcpy(tpdu, &recvBuffer[readIndex] , 5);
		CListBoxPrintf(&m_ListMasterECRMode, "TPDU Found: %02X %02X%02X %02X%02X ", recvBuffer[readIndex], recvBuffer[readIndex+1], recvBuffer[readIndex+2], recvBuffer[readIndex+3], recvBuffer[readIndex+4]);
		// 5 bytes TPDU
		readIndex += 5;
	}

	memcpy(sicilNoOfClient, &recvBuffer[readIndex], 12);
	readIndex += 12;
	CListBoxPrintf(&m_ListMasterECRMode, "Client Sicil: %s", sicilNoOfClient);

	// Function related data..
	readIndex += gmpReadTLVtag(&FunctionTag	, &recvBuffer[readIndex]);
	readIndex += gmpReadTLVlen(&FunctionDataLen, &recvBuffer[readIndex]);
	FunctionDataPtr = &recvBuffer[readIndex];

	// This is just for tracing needs...
	decodeTLVTag(level, FunctionTag, FunctionDataPtr, FunctionDataLen);

	switch (FunctionTag)
	{
		// GetListOfBackgroundTransaction
	case 0xFF8B20:
	{
#define MAX_NUMBER_OF_HANDLES 500

		if (stHandleList.pHandle == NULL)
		{
			stHandleList.pHandle = (ST_MASTERECR_BACKGROUND_TRX_HANDLE*)malloc(MAX_NUMBER_OF_HANDLES * sizeof(ST_MASTERECR_BACKGROUND_TRX_HANDLE));
			stHandleList.maxNumberOfHandles = MAX_NUMBER_OF_HANDLES;
		}

		if (stHandleList.numberOfHandlesInList == 0)
		{
			numberOfHandlesProcessed = 0;
			// Read All TrxList from Master ECR (s)
			retcode = FP3_GetListOfBackgroundTransaction(hInt, TRAN_STATUS_FREE, &stHandleList, TIMEOUT_DEFAULT);
			if (retcode != TRAN_RESULT_OK)
				break;
		}
	}
	break;

	// GetDataOfBackgroundTransaction (TransferBackgroundTransaction)
	case 0xFF8B21:
	{
		HTRX hTrx = NULL;
		uint8	IngenicoVeriGrubuData[2*1024];
		uint16	IngenicoVeriGrubuLen = 0;
		uint8	RestoranVeriGrubuData[2*1024];
		uint16	RestoranVeriGrubuLen = 0;

		IngenicoVeriGrubuLen = gmpSearchTLV(0xDF63  , 1, FunctionDataPtr, FunctionDataLen, IngenicoVeriGrubuData, sizeof(IngenicoVeriGrubuData));
		RestoranVeriGrubuLen = gmpSearchTLV(0xDFE901, 1, IngenicoVeriGrubuData, IngenicoVeriGrubuLen, RestoranVeriGrubuData, sizeof(RestoranVeriGrubuData));
		gmpSearchTLV(0xC001, 1, RestoranVeriGrubuData, RestoranVeriGrubuLen, (uint8*)&hTrx, sizeof(hTrx));

		//if( stTransactionData.Data == NULL )
		//{
		//	stTransactionData.Data = (uint8*)malloc(60*1024);
		//	stTransactionData.sizeOfBuffer = 60*1024;
		//}

		if (stTransactionData.lenOfData == 0)
		{
			numberOfCommandsProcessed = 0;
			// Read All TrxData from Master ECR (s)
			retcode = FP3_GetDataOfBackgroundTransaction(hInt, hTrx, &stTransactionData, TIMEOUT_DEFAULT);
			if (retcode != TRAN_RESULT_OK)
				break;
		}
	}
	break;

	default:
		goto Exit;
	}

	switch (FunctionTag)
	{
	case 0xFF8B20:
	{
		uint8  veriGrubu_C100[SEGMENTATION];
		uint16 veriGrubu_C100_len = 0;

		for (int k = numberOfHandlesProcessed; k < stHandleList.numberOfHandlesInList; k++)
		{
			uint8  veriGrubu_C101[128];
			uint16 veriGrubu_C101_len = 0;

			veriGrubu_C101_len += ingSetTLV(&veriGrubu_C101[veriGrubu_C101_len], 0xC010, (uint8*) & stHandleList.pHandle[k].hTrx, sizeof(stHandleList.pHandle[k].hTrx));
			if (strlen((char*)stHandleList.pHandle[k].sicilNoOfMasterEcr))
				veriGrubu_C101_len += ingSetTLV(&veriGrubu_C101[veriGrubu_C101_len], 0xC011, (uint8*)stHandleList.pHandle[k].sicilNoOfMasterEcr, (uint16)strlen((char*)stHandleList.pHandle[k].sicilNoOfMasterEcr));
			if (strlen((char*)stHandleList.pHandle[k].userDefination))
				veriGrubu_C101_len += ingSetTLV(&veriGrubu_C101[veriGrubu_C101_len], 0xC012, (uint8*)stHandleList.pHandle[k].userDefination, (uint16)strlen((char*)stHandleList.pHandle[k].userDefination));
			if (strlen((char*)stHandleList.pHandle[k].userDefinedGroup))
				veriGrubu_C101_len += ingSetTLV(&veriGrubu_C101[veriGrubu_C101_len], 0xC013, (uint8*)stHandleList.pHandle[k].userDefinedGroup, (uint16)strlen((char*)stHandleList.pHandle[k].userDefinedGroup));
			if (stHandleList.pHandle[k].totalAmount)
				veriGrubu_C101_len += ingSetTLV(&veriGrubu_C101[veriGrubu_C101_len], 0xC014, (uint8*) & stHandleList.pHandle[k].totalAmount, sizeof(stHandleList.pHandle[k].totalAmount));

			if ((veriGrubu_C100_len + veriGrubu_C101_len + 4) >= sizeof(veriGrubu_C100))
			{
				devam = 1;
				break;
			}

			veriGrubu_C100_len += ingSetTLV(&veriGrubu_C100[veriGrubu_C100_len], 0xC100, veriGrubu_C100, veriGrubu_C100_len);
			numberOfHandlesProcessed++;
		}

		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC000, (uint8*) & retcode, sizeof(retcode));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC001, (uint8*) & servisId, sizeof(servisId));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC002, (uint8*)stHandleList.sicilNoOfMasterEcr, 12);
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC003, (uint8*)stHandleList.nameOfMasterEcr, (uint16)strlen((char*)stHandleList.nameOfMasterEcr));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC004, (uint8*) & stHandleList.creationDateOfList, sizeof(stHandleList.creationDateOfList));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC005, (uint8*) & stHandleList.numberOfHandlesInList, sizeof(stHandleList.numberOfHandlesInList));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC100, (uint8*)veriGrubu_C100, veriGrubu_C100_len);
	}
	break;

	case 0xFF8B21:
		uint8  veriGrubu_C102[SEGMENTATION];
		uint16 veriGrubu_C102_len = 0;

		for (int k = numberOfCommandsProcessed; k < stTransactionData.numberOfCommandsInList ; k++)
		{
			uint8  cmdBuffer[1024];
			uint16 cmdBufferLen = 0;

			cmdBufferLen = gmpSearchTLV(GMP_TRANSACTION_COMMAND_RECORD, k, stTransactionData.Data, stTransactionData.lenOfData, cmdBuffer, sizeof(cmdBuffer));
			if ((veriGrubu_C102_len + cmdBufferLen + 4) >= sizeof(veriGrubu_C102))
			{
				devam = 1;
				break;
			}

			veriGrubu_C102_len += ingSetTLV(&veriGrubu_C102[veriGrubu_C102_len], 0xC103, (uint8*)cmdBuffer, cmdBufferLen);

			numberOfCommandsProcessed++;
		}

		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC000, (uint8*) & retcode, sizeof(retcode));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC001, (uint8*) & servisId, sizeof(servisId));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC002, (uint8*)stTransactionData.sicilNoOfMasterEcr, 12);
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC003, (uint8*)stTransactionData.nameOfMasterEcr, (uint16)strlen((char*)stTransactionData.nameOfMasterEcr));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC004, (uint8*) & stTransactionData.dateOfMasterEcr, sizeof(stTransactionData.dateOfMasterEcr));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC007, (uint8*) & stTransactionData.numberOfCommandsInList, sizeof(stTransactionData.numberOfCommandsInList));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC008, (uint8*)stTransactionData.signOfMasterEcr, sizeof(stTransactionData.signOfMasterEcr));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC010, (uint8*) & stTransactionData.transactionHandle, sizeof(stTransactionData.transactionHandle));
		veriGrubu_DFE902_len += ingSetTLV(&veriGrubu_DFE902[veriGrubu_DFE902_len], 0xC102, (uint8*)veriGrubu_C102, veriGrubu_C102_len);
		break;
	}

	// haberleþme devam
	veriGrubu_DF63_len += gmpSetTLV(&veriGrubu_DF63[veriGrubu_DF63_len], 0xDFE000, &devam			, sizeof(devam));
	// Veri Bloðu
	veriGrubu_DF63_len += gmpSetTLV(&veriGrubu_DF63[veriGrubu_DF63_len], 0xDFE902, veriGrubu_DFE902, veriGrubu_DFE902_len);


	/* ÝÞLEM GRUBU */
	uint8 islemGrubu[128];
	uint16 islemGrubuLen = 0;
	islemGrubuLen += gmpSetTLV(&islemGrubu[islemGrubuLen], 0xDF8204, (uint8*) & sicilNoOfClient, 12);
	islemGrubuLen += gmpSetTLV(&islemGrubu[islemGrubuLen], 0xDF8208, (uint8*)"\x00\x00\x00", 3);
	islemGrubuLen += gmpSetTLV(&islemGrubu[islemGrubuLen], 0xDF8209, (uint8*)"\x01\x01\x01", 3);
	islemGrubuLen += gmpSetTLV(&islemGrubu[islemGrubuLen], 0xDF820A, (uint8*)"\x02\x02\x02", 3);
	islemGrubuLen += gmpSetTLV(&islemGrubu[islemGrubuLen], 0xDF820D, (uint8*)"\x30\x30", 2);
	islemGrubuLen += gmpSetTLV(&islemGrubu[islemGrubuLen], 0xDFE010, (uint8*)"\x48\x48x48\x48", 4);

	buf_len = 0;
	buf_len += gmpSetTLV(&Buffer[buf_len], 0xDF02, islemGrubu		, islemGrubuLen);
	buf_len += gmpSetTLV(&Buffer[buf_len], 0xDF63, veriGrubu_DF63	, veriGrubu_DF63_len);
	buf_len;

	sendSocketData(m_socket, tpdu, sicilNoOfClient, FunctionTag | 0x000400, Buffer, buf_len);

Exit:
	return 0;
}

void CePosDlg::DecodeuApplicationRequest(char* sicilNo, uint8* recvBuffer, int recvLen)
{
#define MAX_NUMBER_OF_RETURNS 1024
	int		retcode = TRAN_RESULT_OK;
	ST_MULTIPLE_RETURN_CODE	stReturnCodes[MAX_NUMBER_OF_RETURNS]; // will return return codes of each subcommand
	ST_TICKET m_stTicket;
	uint32 msgCommandType = 0;
	uint8	msgBuffer[1024*16];	// this is buffer for just one msg type (exp: GMP_FISCAL_PRINTER_REQ or GMP_EXT_DEVICE_GET ...
	uint16	msgBufferLen = 0;
	uint16 numberOfreturnCodes = 0;
	uint16 tmpNumberOfreturnCodes = 0;
	CString displayData;
	displayData.Empty();
	uint8  returnDataBuffer[32][MAX_NUMBER_OF_RETURNS];

	memset(&m_stTicket, 0x00, sizeof(m_stTicket));
	memset(&stReturnCodes, 0x00, sizeof(stReturnCodes));

	// This is necassary to be able to read GET commands data..
	memset(&returnDataBuffer, 0x00, sizeof(returnDataBuffer));
	for (int t = 0; t < MAX_NUMBER_OF_RETURNS; t++)
	{
		stReturnCodes[t].pData = &returnDataBuffer[t][0];
		stReturnCodes[t].lengthOfData = 32;
	}

	memcpy(sicilNo, &recvBuffer[2], 12);

	uint8* recvFullBuffer = &recvBuffer[2+12]; // exclude 2 bytes len + sicil No
	uint16 recvFullBufferLen = recvLen - 14;
	uint16 recvbufferReadLen = 0;

	while (recvbufferReadLen < recvFullBufferLen)
	{
		uint32 msgCommandType = 0;
		msgBufferLen = 0;

		recvbufferReadLen += gmpReadTLVtag(&msgCommandType	, &recvFullBuffer[recvbufferReadLen]);
		recvbufferReadLen += gmpReadTLVlen(&msgBufferLen		, &recvFullBuffer[recvbufferReadLen]);

		memcpy(msgBuffer, &recvFullBuffer[recvbufferReadLen] , msgBufferLen);
		recvbufferReadLen += msgBufferLen;

		// Preceed received message
		switch (msgCommandType)
		{
		case GMP3_FISCAL_PRINTER_MODE_RES:
		case GMP3_FISCAL_PRINTER_MODE_RES_E:
			retcode = parse_FiscalPrinter(&stReturnCodes[numberOfreturnCodes], &tmpNumberOfreturnCodes, msgCommandType, msgBuffer, msgBufferLen, &m_stTicket);
			numberOfreturnCodes += tmpNumberOfreturnCodes;
			break;
		case GMP3_EXT_DEVICE_GET_DATA_RES:
		case GMP3_EXT_DEVICE_GET_DATA_RES_E:
			retcode = parse_GetEcr(&stReturnCodes[numberOfreturnCodes], &tmpNumberOfreturnCodes, msgCommandType, msgBuffer, msgBufferLen);
			numberOfreturnCodes += tmpNumberOfreturnCodes;
			break;
		}
	}

	CString csDataString;
	displayData.Format(L"SICIL NO: %s \r", CString(sicilNo));

	// Example how to parse & use the data
	for (int t = 0; t < numberOfreturnCodes ; t++)
	{
		char returnCodeString[256];
		CString tmp;

		memset(returnCodeString, 0x00, sizeof(returnCodeString));
		GetErrorMessage(stReturnCodes[t].retcode, returnCodeString);

		switch (stReturnCodes[t].subCommand)
		{
		case 0:
			csDataString = L"";
			break;

		case GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_PASSWORD:
		case GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_AMOUNT:
		case GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_TEXT:
			csDataString = CString(stReturnCodes[t].pData);
			break;
		case GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_DATE:
		{
			ST_DATE_TIME date;
			memcpy(&date, stReturnCodes[t].pData, MINI(sizeof(ST_DATE_TIME), stReturnCodes[t].lengthOfData));
			csDataString.Format(L"%d/%d/%d", date.year, date.month, date.day);
		}
		break;
		case GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_MENU:
		{
			uint16 itemSelected;
			memcpy(&itemSelected, stReturnCodes[t].pData, MINI(sizeof(itemSelected), stReturnCodes[t].lengthOfData));
			csDataString.Format(L"Selected %d", itemSelected);
		}
		break;
		case GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_MSGBOX:
			csDataString.Format(L"Check retcode");
			break;
		}

		tmp.Format(L"SubCmnd=%04X, return=%s, tag=%06X, len=%d %s %s",  stReturnCodes[t].subCommand, CString(returnCodeString),  stReturnCodes[t].tag,  stReturnCodes[t].lengthOfData, csDataString, CString("\r"));
		displayData += tmp;
	}

	if (displayData.GetLength())
		MessageBox(displayData, L"Client Received", MB_OK);

	if (retcode == TRAN_RESULT_OK)
		DisplayTransaction(&m_stTicket, true);

	HandleErrorCode(retcode);
}

int CePosDlg::TestTransaction()
{
	int retcode;
	uint8 uniqueId[24];
	ST_TICKET stTicket;
	int countOfItemSold = 0;
	ST_PAYMENT_REQUEST stPaymentRequest[1];

	memset(stPaymentRequest, 0, sizeof(ST_PAYMENT_REQUEST));

	HTRX hTrx = NULL;
	HINT hInt = GetSelectedInterface();

	for (int retry = 0; retry < 10; retry++)
	{
		hTrx = NULL;
		memset(&stTicket, 0x00, sizeof(stTicket));
		memset(uniqueId, 0x00, sizeof(uniqueId));

		retcode = TransactionHandle_StartAndInsert(hInt, &hTrx, FALSE, uniqueId, sizeof(uniqueId));

		// ECR is not ready to handlethis message, retry to send it again...
		if (retcode == DLL_RETCODE_RECV_BUSY)
			continue;

		if ((retcode == APP_ERR_GMP3_PAIRING_REQUIRED) || (retcode == DLL_RETCODE_PAIRING_REQUIRED))
		{
			// Pairing required....
			OnBnClickedButtonPair();
			continue;
		}

		if (retcode == APP_ERR_ALREADY_DONE)
		{
			// Get the copy of the ACTIVE transaction from ECR
			while (1)
			{
				retcode = FP3_GetTicket(hInt, hTrx, &stTicket);
				// ECR is not ready to handlethis message, retry to send it again...
				if (retcode == DLL_RETCODE_RECV_BUSY)
					continue;
				if (retcode != TRAN_RESULT_OK)
					goto EXIT;
				break;
			}

			// Void payments, if any...
			for (int i = 0; i < stTicket.totalNumberOfPayments; i++)
			{
				// already cancelled
				if (stTicket.stPayment[i].flags & PARTIAL_PAYMENT_FLAG_CANCEL)
					continue;

				while (1)
				{
					retcode = FP3_VoidPayment(hInt, hTrx, i, &stTicket);
					// ECR is not ready to handlethis message, retry to send it again...
					if (retcode == DLL_RETCODE_RECV_BUSY)
						continue;
					if (retcode != TRAN_RESULT_OK)
						goto EXIT;
					break;
				}
			}

			// Void the ticket..
			while (1)
			{
				retcode = FP3_VoidAll(hInt, hTrx, NULL);
				// ECR is not ready to handlethis message, retry to send it again...
				if (retcode == DLL_RETCODE_RECV_BUSY)
					continue;
				if (retcode != TRAN_RESULT_OK)
					goto EXIT;
				break;
			}

			// Close Ticket
			while (1)
			{
				retcode = TransactionHandle_CloseAndRemove(hInt, hTrx);
				// ECR is not ready to handlethis message, retry to send it again...
				if (retcode == DLL_RETCODE_RECV_BUSY)
					continue;
				if (retcode != TRAN_RESULT_OK)
					goto EXIT;
				break;
			}

			continue;
		}

		break;
	}

	if (retcode != TRAN_RESULT_OK)
		goto EXIT;

	while (1)
	{
		// ECR is not ready to handlethis message, retry to send it again...
		if (retcode == DLL_RETCODE_RECV_BUSY)
			continue;
		retcode = FP3_TicketHeader(hInt, hTrx, TProcessSale);
		if (retcode != TRAN_RESULT_OK)
			goto EXIT;
		break;
	}

	int numberOfItems = 1 + rand() % 20;
	int paymentTotal = 0;

	for (countOfItemSold = 0 ; countOfItemSold < numberOfItems ; countOfItemSold++)
	{
		ST_ITEM stItem;
		memset(&stItem, 0x00, sizeof(stItem));

		stItem.type				= ITEM_TYPE_DEPARTMENT;
		stItem.subType			= 0;
		stItem.deptIndex		= countOfItemSold % 8;
		stItem.amount			= (1 + countOfItemSold) * 100;
		paymentTotal			+= stItem.amount;
		stItem.currency			= CURRENCY_TL;
		stItem.count			= 1;
		stItem.unitType			= 0;
		stItem.pluPriceIndex	= 0;
		stItem.countPrecition	= 0;

		sprintf(stItem.name, "PRODUCT %d", countOfItemSold + 1);
		//		strcpy( stItem.barcode, "123456789" );

		while (1)
		{
			retcode = FP3_ItemSale(hInt, hTrx, &stItem, &stTicket);
			if (retcode == DLL_RETCODE_RECV_BUSY)
				continue;
			if (retcode != TRAN_RESULT_OK)
				goto EXIT;
			break;
		}
	}

	stPaymentRequest[0].typeOfPayment			= PAYMENT_CASH_TL;
	stPaymentRequest[0].subtypeOfPayment		= NULL;
	stPaymentRequest[0].payAmount				= paymentTotal;
	stPaymentRequest[0].payAmountCurrencyCode	= CURRENCY_TL;

	while (1)
	{
		retcode = FP3_Payment(hInt, hTrx, stPaymentRequest, &stTicket);
		if (retcode == DLL_RETCODE_RECV_BUSY)
			continue;
		if (retcode != TRAN_RESULT_OK)
			goto EXIT;
		break;
	}

	while (1)
	{
		retcode = FP3_PrintTotalsAndPayments(hInt, hTrx);
		if (retcode == DLL_RETCODE_RECV_BUSY)
			continue;
		if (retcode !=  TRAN_RESULT_OK)
			goto EXIT;
		break;
	}

	while (1)
	{
		retcode = FP3_PrintBeforeMF(hInt, hTrx);
		if (retcode == DLL_RETCODE_RECV_BUSY)
			continue;
		if (retcode !=  TRAN_RESULT_OK)
			goto EXIT;
		break;
	}

	while (1)
	{
		ST_USER_MESSAGE stUserMessage[3];
		memset(&stUserMessage, 0x00, sizeof(stUserMessage));
		stUserMessage[0].flag = GMP3_PS_38 | GMP3_PS_CENTER;
		strcpy((char*)stUserMessage[0].message, "Teþekkür Ederiz");
		stUserMessage[0].len = (uint8)strlen((char*)stUserMessage[0].message);

		retcode = FP3_PrintUserMessage(hInt, hTrx, stUserMessage, 1,  &stTicket);
		if (retcode == DLL_RETCODE_RECV_BUSY)
			continue;
		if (retcode !=  TRAN_RESULT_OK)
			goto EXIT;
		break;
	}

	while (1)
	{
		retcode = FP3_PrintMF(hInt, hTrx);
		if (retcode == DLL_RETCODE_RECV_BUSY)
			continue;
		if (retcode !=  TRAN_RESULT_OK)
			goto EXIT;
		break;
	}

	while (1)
	{
		retcode = TransactionHandle_CloseAndRemove(hInt, hTrx);
		if (retcode == DLL_RETCODE_RECV_BUSY)
			continue;
		if (retcode != TRAN_RESULT_OK)
			goto EXIT;
		break;
	}

EXIT:
	if (retcode != TRAN_RESULT_OK)
	{
		DisplayErrorMessage(retcode);

		FP3_VoidAll(hInt, hTrx, NULL);
	}

	TransactionHandle_CloseAndRemove(hInt, hTrx);

	return retcode;
}

void CePosDlg::OnTimer(UINT_PTR nIDEvent)
{
	int retcode;

	switch (nIDEvent)
	{
	case 2:
		// TCPIP Listen & Receive
		if (m_ServerSocket == INVALID_SOCKET)
			break;

		if (m_ClientSocket != INVALID_SOCKET)
		{
			uint8 recvBuffer[1024*16];
			int recvLen = 0 ;
			DWORD dwTime = 1;

			setsockopt(m_ClientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&dwTime, sizeof(dwTime));

			recvLen = recv(m_ClientSocket, (char*)recvBuffer, sizeof(recvBuffer), 0);
			if (recvLen == 0)
			{
				closesocket(m_ClientSocket);
				m_ClientSocket = INVALID_SOCKET;
				m_Button_BatchCommand_ListenAndSend.SetWindowTextW(L"Listening...");
			}
			else if (recvLen > 0)
			{
				char sicilNo[12+1];
				memset(sicilNo, 0, sizeof(sicilNo));

				DisplayInfo("Client Socket Data Len = %d", recvLen);
				// This is the first message coming from ECR after uApplication function processed
				// All Selective and option data in this package
				DecodeuApplicationRequest(sicilNo, recvBuffer, recvLen);

				// Reply ECR with a set of command (Batch Command list )
				// This function also receive response and parse it
				ProcessBatchCommand(sicilNo);

				// Done with ECR, close connection
				closesocket(m_ClientSocket);
				m_ClientSocket = INVALID_SOCKET;
				m_Button_BatchCommand_ListenAndSend.SetWindowTextW(L"Listening...");
			}
		}
		else
		{
			// Accept a client socket
			m_ClientSocket = accept(m_ServerSocket, NULL, NULL);
			if (m_ClientSocket == INVALID_SOCKET)
				break;
			m_Button_BatchCommand_ListenAndSend.SetWindowTextW(L"Connected");
		}

		break;

	case 1:
		// Ping

		retcode = FP3_Ping(GetSelectedInterface(), 1100);
		switch (retcode)
		{
		case TRAN_RESULT_OK:
			m_Button_Ping.SetWindowTextW(L"CONNECTED");
			break;
		case DLL_RETCODE_RECV_BUSY:
			m_Button_Ping.SetWindowTextW(L"BUSY");
			break;
		case DLL_RETCODE_TIMEOUT:
			m_Button_Ping.SetWindowTextW(L"DISCONNECTED");
			break;
		default:
			m_Button_Ping.SetWindowTextW(L"ERROR");
			HandleErrorCode(retcode);
			break;
		}
		break;

	case 4:
		// MECR TCPIP Listen & Receive
		if (m_MEcrServerSocket == INVALID_SOCKET)
			break;

		if (m_MEcrClientSocket != INVALID_SOCKET)
		{
			uint8 recvBuffer[1024*16];
			int recvLen = 0 ;
			DWORD dwTime = 1;

			setsockopt(m_MEcrClientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&dwTime, sizeof(dwTime));

			recvLen = recv(m_MEcrClientSocket, (char*)recvBuffer, sizeof(recvBuffer), 0);
			if (recvLen <= 0)
			{
				closesocket(m_MEcrClientSocket);
				m_MEcrClientSocket = INVALID_SOCKET;
				m_ButtonListenMEcr.SetWindowTextW(L"Listening...");

				CListBoxPrintf(&m_ListMasterECRMode, "Disconnected.", recvLen);
			}
			else if (recvLen > 0)
			{
				char sicilNo[12+1];
				memset(sicilNo, 0, sizeof(sicilNo));
				DisplayInfo("Client Socket Data Len = %d", recvLen);

				processECRMessage(m_MEcrClientSocket, recvBuffer, recvLen);

				m_ButtonListenMEcr.SetWindowTextW(L"Listening...");
			}
		}
		else
		{
			// Accept a client socket
			m_MEcrClientSocket = accept(m_MEcrServerSocket, NULL, NULL);
			if (m_MEcrClientSocket == INVALID_SOCKET)
				break;

			m_ButtonListenMEcr.SetWindowTextW(L"Connected");
			CListBoxPrintf(&m_ListMasterECRMode, "Connected...");

			if (stHandleList.pHandle)free(stHandleList.pHandle);
			memset(&stHandleList, 0, sizeof(stHandleList));
			if (stTransactionData.Data)free(stTransactionData.Data);
			memset(&stTransactionData, 0, sizeof(stTransactionData));
		}

		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

bool CePosDlg::GetStringInput(CString caption, CString* input)
{
	CGetInputDlg* pcInput;

	pcInput = new CGetInputDlg;
	if (pcInput->DoModal(caption, *input, 1) != IDOK)
		return false;
	*input = pcInput->m_input;
	delete pcInput;

	return true;
}

bool CePosDlg::GetStringInput(CString caption, char* input)
{
	CString cs = CString(input);

	if (!GetStringInput(caption, &cs))
		return false;

	strcpy(input, CT2A((LPCTSTR)(cs)));
	return true;
}

bool CePosDlg::GetStringInputLn(CString caption, char* input, uint16 MaxLen)
{
	CString cs = CString(input);

	if (!GetStringInput(caption, &cs))
		return false;

	memcpy(input, CT2A((LPCTSTR)(cs)), MINI(strlen(CT2A((LPCTSTR)(cs))), MaxLen));
	return true;
}

bool CePosDlg::GetIntegerInput(CString caption, int* input)
{
	CGetInputDlg* pcInput;
	CString cs;

	cs. Format(L"%d", *input);

	pcInput = new CGetInputDlg;
	if (pcInput->DoModal(caption, cs, 2) != IDOK)
		return false;
	*input = atol(CT2A((LPCTSTR)pcInput->m_input));
	delete pcInput;

	return true;
}

bool CePosDlg::GetIntegerInput(CString caption, char* input)
{
	CGetInputDlg* pcInput;
	CString cs;

	cs. Format(L"%s", input);

	pcInput = new CGetInputDlg;
	if (pcInput->DoModal(caption, cs, 2) != IDOK)
		return false;
	strcpy(input, CT2A((LPCTSTR)pcInput->m_input));
	delete pcInput;

	return true;
}

void CePosDlg::OnBnClickedButtonTaxfreeSet()
{
	int retcode = TRAN_RESULT_OK;
	char csName[32] = "JACK";
	char csSurname[32] = "DANIELS";
	char csIdentificationNo[32] = "BL123456";
	char csCity[32] = "NEW YORK";
	char csCountry[32] = "USA";

	if (!GetStringInput(L"PASSANGER NAME", csName))
		return;
	if (!GetStringInput(L"PASSANGER SURNAME", csSurname))
		return;
	if (!GetStringInput(L"PASSANGER ID NO", csIdentificationNo))
		return;
	if (!GetStringInput(L"PASSANGER CITY", csCity))
		return;
	if (!GetStringInput(L"PASSANGER COUNTRY", csCountry))
		return;

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_SetTaxFree(&buffer[0], sizeof(buffer), 0, csName, csSurname, csIdentificationNo, csCity, csCountry);
		AddIntoCommandBatch(L"prepare_SetTaxFree", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		bool localStart = false;
		uint64 activeFlags = 0;

		HINT hInt = GetSelectedInterface();
		ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);

		HTRX hTrx = GetSelectedTransaction();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		if (hTrx == NULL)
		{
			retcode = TransactionHandle_StartAndInsert(hInt, &hTrx, FALSE, ptr->m_uniqueId, sizeof(ptr->m_uniqueId));

			// handle opened locally here, in case of an error close it here!
			localStart = true;
			pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

			if (retcode == TRAN_RESULT_OK)
				retcode = FP3_OptionFlags(hInt, hTrx, &activeFlags,  RESPONSE_FLAGS, 0x00000000, TIMEOUT_DEFAULT);
		}

		if (retcode == TRAN_RESULT_OK)
			retcode = FP3_SetTaxFree(hInt, hTrx, 0, csName, csSurname, csIdentificationNo, csCity, csCountry, pstTicket);

		if (retcode == TRAN_RESULT_OK)
		{
			retcode = FP3_TicketHeader(hInt, hTrx, TTaxFree);

			if (retcode == TRAN_RESULT_OK)
				// local handle can not be closed after this point
				localStart = false;
		}

		if (retcode == TRAN_RESULT_OK)
			DisplayTransaction(pstTicket, false);
		else if (localStart)
			retcode = TransactionHandle_CloseAndRemove(hInt, hTrx);
	}

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonTaxfreeSetTaxfundAmount()
{
	uint32 amount = 0;
	int retcode = TRAN_RESULT_OK;

	if (m_csInput.GetLength())
	{
		amount = getAmount(m_csInput);
		m_csInput.Empty();
		m_EditControlInput.SetWindowTextW(m_csInput);
	}

	if (m_TabCommandMode.GetCurSel() == TAB_BATCH_COMMAND_MODE)
	{
		uint8	buffer[1024];
		uint16	bufferLen = 0;

		// start
		bufferLen = prepare_SetTaxFreeRefundAmount(&buffer[0], sizeof(buffer), amount, CURRENCY_TL);
		AddIntoCommandBatch(L"prepare_SetTaxFreeRefundAmount", GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
	}
	else
	{
		HTRX hTrx = GetSelectedTransaction();
		HINT hInt = GetSelectedInterface();
		ST_TICKET* pstTicket = &(GetTransactionDataPointer(hInt, hTrx)->m_stTicket);

		retcode = FP3_SetTaxFreeRefundAmount(GetSelectedInterface(), GetSelectedTransaction(), amount, CURRENCY_TL, pstTicket);

		if (retcode == TRAN_RESULT_OK)
			DisplayTransaction(pstTicket, false);
	}

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonTestTransaction()
{
	TestTransaction();
}


void CePosDlg::OnLbnSelchangeListStatus()
{
	// TODO: Add your control notification handler code here
}


void CePosDlg::OnSelchangedTreeInterface(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	HINT hInt = 0;
	CString interfaceID;
	HTREEITEM hInterface = NULL;
	HTREEITEM hTransaction = NULL;

	// Get the selected item in treectrl
	HTREEITEM hItem = m_treeIterface.GetSelectedItem();

	if (m_treeIterface.GetParentItem(hItem) == NULL)
	{
		// This is an INTERFACE ITEM
		hInterface = hItem;
	}
	else
	{
		// This is an TRANSACTION ITEM
		hTransaction = hItem;
		hInterface = m_treeIterface.GetParentItem(hTransaction);

	}

	interfaceID = m_treeIterface.GetItemText(hInterface);
	if (FP3_GetInterfaceHandleByID(&hInt, CT2A((LPCTSTR)interfaceID)) != TRAN_RESULT_OK)
		// There is no interface wth this ID (name)
		return;

	m_ListInterfaceSettings.ResetContent();

	ST_INTERFACE_XML_DATA stInterfaceXmlData;
	memset(&stInterfaceXmlData, 0, sizeof(stInterfaceXmlData));
	if (FP3_GetInterfaceXmlDataByHandle(hInt, &stInterfaceXmlData) == TRAN_RESULT_OK)
	{
		if (stInterfaceXmlData.IsTcpConnection)
		{
			CListBoxPrintf(&m_ListInterfaceSettings, "%s / %d"
						   , stInterfaceXmlData.IP
						   , stInterfaceXmlData.Port
						  );
			CListBoxPrintf(&m_ListInterfaceSettings, "RE-TRY=%d"
						   , stInterfaceXmlData.IpRetryCount
						  );
		}
		else
		{
			CListBoxPrintf(&m_ListInterfaceSettings, "%s, %d %d%c%d"
						   , stInterfaceXmlData.PortName
						   , stInterfaceXmlData.BaudRate
						   , stInterfaceXmlData.ByteSize
						   , (stInterfaceXmlData.Parity == 0) ? 'N' : 'O'
						   , stInterfaceXmlData.StopBit + 1
						  );
			CListBoxPrintf(&m_ListInterfaceSettings, "ICTO=%dms, RE-TRY=%d"
						   , stInterfaceXmlData.InterCharacterTimeOut
						   , stInterfaceXmlData.RetryCounter
						  );
		}

		CListBoxPrintf(&m_ListInterfaceSettings, "COMM_TO=%dms", stInterfaceXmlData.CommTimeOut);
		CListBoxPrintf(&m_ListInterfaceSettings, "ACK_TO=%dms"	, stInterfaceXmlData.AckTimeOut);
	}

	ST_INTERFACE_DATA* pInterfaceData = GetInterfaceDataPointer(hInt);
	if (pInterfaceData)
	{
		UpdateStatusDisplay(&m_GMPPairResp, &pInterfaceData->stEcho);
		DisplayDepartmentsAndTaxRates(hInt);
		DisplayCurrency(hInt);
	}

	if (hTransaction)
	{
		ST_TRANSACTION_DATA* ptr = (ST_TRANSACTION_DATA*)m_treeIterface.GetItemData(hTransaction);
		if (ptr)
			// This is Transaction
			DisplayTransaction(&ptr->m_stTicket, false);
	}
}

HINT CePosDlg::GetSelectedInterface(void)
{
	HINT hInt = 0;
	CString interfaceID;
	HTREEITEM hInterface = NULL;
	HTREEITEM hTransaction = NULL;

	// Get the selected item in treectrl
	HTREEITEM hItem = m_treeIterface.GetSelectedItem();

	while (m_treeIterface.GetParentItem(hItem) != NULL)
		hItem = m_treeIterface.GetParentItem(hItem);

	interfaceID = m_treeIterface.GetItemText(hItem);
	if (FP3_GetInterfaceHandleByID(&hInt, CT2A((LPCTSTR)interfaceID)) != TRAN_RESULT_OK)
		// There is no interface wth this ID (name)
		return NULL;

	return hInt;
}

int CePosDlg::TransactionHandle_StartAndInsert(HINT hInt, HTRX* phTrx, bool isBackgroundTransaction, byte* uniqueId, int lenOfuniqueId)
{
	int retcode;

	retcode = FP3_Start(hInt, phTrx, isBackgroundTransaction, uniqueId, lenOfuniqueId, NULL, 0, NULL, 0);
	switch (retcode)
	{
	case APP_ERR_ALREADY_DONE:
		if (CTreeCtrlFindTransactionHandle(hInt, *phTrx, TRUE) == FALSE)
			CTreeCtrlInsertTransactionHandle(*phTrx, FALSE);
		break;

	case TRAN_RESULT_OK:
		CTreeCtrlInsertTransactionHandle(*phTrx, isBackgroundTransaction);
		break;
	}

	return retcode;
}

/*
Only removes handle fromthe tree view, not from ECR!!!
hTrx = 0xFFFFFFFF means ann transactions fro the treeview
*/
int CePosDlg::CTreeCtrlRemoveTransactionHandle(HINT hInt, HTRX hTrx)
{
	HTREEITEM hInterface = m_treeIterface.GetRootItem();

	while (hInterface)
	{
		ST_INTERFACE_DATA* ptr_int = (ST_INTERFACE_DATA*)m_treeIterface.GetItemData(hInterface);
		if (ptr_int)
		{
			if (ptr_int->hInt == hInt)
			{
				HTREEITEM hTransaction		= m_treeIterface.GetNextItem(hInterface, TVGN_CHILD);
				while (hTransaction)
				{
					HTREEITEM hTransactionNext	= m_treeIterface.GetNextItem(hTransaction, TVGN_NEXT);

					bool deleteItem = (hTrx == 0xFFFFFFFF) ? TRUE : FALSE;
					ST_TRANSACTION_DATA* ptr = (ST_TRANSACTION_DATA*)m_treeIterface.GetItemData(hTransaction);
					if (ptr)
						if (ptr->hTrx == hTrx)
							deleteItem = TRUE;
					if (deleteItem)
					{
						if (ptr)
						{
							free(ptr);
							ptr = NULL;
						}
						m_treeIterface.SetItemData(hTransaction, (DWORD_PTR)ptr);
						m_treeIterface.DeleteItem(hTransaction);
						memset(ptr_int->m_uniqueId, 0x00, sizeof(ptr_int->m_uniqueId));
					}

					hTransaction = hTransactionNext;
				}
			}
		}

		hInterface = m_treeIterface.GetNextItem(hInterface, TVGN_NEXT);
	}

	return TRAN_RESULT_OK;
}

int CePosDlg::TransactionHandle_CloseAndRemove(HINT hInt, HTRX hTrx)
{
	int retcode = FP3_Close(hInt, hTrx, TIMEOUT_DEFAULT);
	if (retcode != TRAN_RESULT_OK)
		return retcode;

	return CTreeCtrlRemoveTransactionHandle(hInt, hTrx);
}

HTRX CePosDlg::GetSelectedTransaction(void)
{
	HINT hInt = 0;
	CString interfaceID;
	HTREEITEM hInterface = NULL;
	HTREEITEM hTransaction = NULL;

	// Get the selected item in treectrl
	HTREEITEM hItem = m_treeIterface.GetSelectedItem();

	if (m_treeIterface.GetParentItem(hItem) == NULL)
		// This is INTERFACE item, Not Transaction...
		return NULL;

	ST_TRANSACTION_DATA* ptr = (ST_TRANSACTION_DATA*)m_treeIterface.GetItemData(hItem);
	if (ptr == NULL)
		return NULL;

	// GMP3 TRX handle was saved into DATA part of the tree item...
	return ptr->hTrx;
}

void CePosDlg::CTreeCtrlInsertTransactionHandle(HTRX hTrx, bool isBackgroundTrx)
{
	CString interfaceID;
	HTREEITEM hInterface = NULL;
	HTREEITEM hTransaction = NULL;

	// Get the selected item in treectrl
	HTREEITEM hItem = m_treeIterface.GetSelectedItem();

	while (m_treeIterface.GetParentItem(hItem) != NULL)
		hItem = m_treeIterface.GetParentItem(hItem);
	hInterface = hItem;

	uint8 tmp[8];
	memcpy(tmp, (uint8*)&hTrx, 8);
	hTransaction = CTreeCtrlInsertf(&m_treeIterface, hInterface, isBackgroundTrx, "%02X%02X%02X%02X-%02X%02X%02X%02X", tmp[7], tmp[6], tmp[5], tmp[4], tmp[3], tmp[2], tmp[1], tmp[0]);
	if (hTransaction == NULL)
		return;

	// This is interface buffer to keep interface related ECR data....
	DWORD_PTR ptr = (DWORD_PTR)malloc(sizeof(ST_TRANSACTION_DATA));
	if (ptr)
	{
		memset((void*)ptr, 0x00, sizeof(ST_TRANSACTION_DATA));
		((ST_TRANSACTION_DATA*)ptr)->hTrx = hTrx;
		((ST_TRANSACTION_DATA*)ptr)->isBackgroundTrx = isBackgroundTrx;
		m_treeIterface.SetItemData(hTransaction, ptr);
	}
}

HTRX CePosDlg::CTreeCtrlFindFrontScreenHandle(HINT hInt)
{
	HTREEITEM hInterface = m_treeIterface.GetRootItem();

	while (hInterface)
	{
		ST_INTERFACE_DATA* int_ptr = (ST_INTERFACE_DATA*)m_treeIterface.GetItemData(hInterface);
		if (int_ptr)
		{
			if (int_ptr->hInt == hInt)
			{
				HTREEITEM hTransaction = m_treeIterface.GetNextItem(hInterface, TVGN_CHILD);
				while (hTransaction)
				{
					ST_TRANSACTION_DATA* ptr = (ST_TRANSACTION_DATA*)m_treeIterface.GetItemData(hTransaction);
					if (ptr)
					{
						if (ptr->isBackgroundTrx == FALSE)
							return ptr->hTrx;
					}
					hTransaction = m_treeIterface.GetNextItem(hTransaction, TVGN_NEXT);
				}
			}
		}
		hInterface = m_treeIterface.GetNextItem(hInterface, TVGN_NEXT);
	}

	return NULL;
}

bool CePosDlg::CTreeCtrlFindTransactionHandle(HINT hInt, HTRX hTrx, bool bSelect)
{
	HTREEITEM hInterface = m_treeIterface.GetRootItem();

	while (hInterface)
	{
		ST_INTERFACE_DATA* int_ptr = (ST_INTERFACE_DATA*)m_treeIterface.GetItemData(hInterface);
		if (int_ptr)
		{
			if (int_ptr->hInt == hInt)
			{
				HTREEITEM hTransaction = m_treeIterface.GetNextItem(hInterface, TVGN_CHILD);
				while (hTransaction)
				{
					ST_TRANSACTION_DATA* ptr = (ST_TRANSACTION_DATA*)m_treeIterface.GetItemData(hTransaction);
					if (ptr)
					{
						if (ptr->hTrx == hTrx)
						{
							if (bSelect)
								m_treeIterface.SelectItem(hTransaction);
							return TRUE;
						}
					}
					hTransaction = m_treeIterface.GetNextItem(hTransaction, TVGN_NEXT);
				}
			}
		}
		hInterface = m_treeIterface.GetNextItem(hInterface, TVGN_NEXT);
	}

	return FALSE;
}


void CePosDlg::OnRclickTreeInterface(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_treeIterface.m_hWnd, GetMessagePos());
	*pResult = 0;
}


void CePosDlg::OnContextMenu(CWnd* pWnd, CPoint ptMousePos)
{
	CMenu menu;
	CMenu* pPopup;

	int id = pWnd->GetDlgCtrlID();

	switch (id)
	{
	case IDC_TREE_INTERFACE:
//		m_popupMenuActiveControl = id;
		break;
	default:
//		m_popupMenuActiveControl = NULL;
		return;
	}

	// if Shift-F10
	if (ptMousePos.x == -1 && ptMousePos.y == -1)
		ptMousePos = (CPoint) GetMessagePos();

	pWnd->ScreenToClient(&ptMousePos);

	// the font popup is stored in a resource
	menu.LoadMenu(IDR_MENU_INTERFACE_CONTEXT);
	pPopup = menu.GetSubMenu(0);
	pWnd->ClientToScreen(&ptMousePos);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN, ptMousePos.x, ptMousePos.y, this);
}

void CePosDlg::OnInterfacePopupMenuNewBackgroundTransaction()
{
	HTRX hTrx = NULL;
	HINT hInt = GetSelectedInterface();
	ST_INTERFACE_DATA* ptr = GetInterfaceDataPointer(hInt);

	int retcode = TransactionHandle_StartAndInsert(hInt, &hTrx, TRUE, ptr->m_uniqueId, sizeof(ptr->m_uniqueId));
	HandleErrorCode(retcode);
}

void CePosDlg::OnInterfacePopupMenuTransferBackgroundTrxintoFrontScreen()
{
	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	if (hTrx == NULL)
	{
		MessageBox(L"Please SELECT a Transaction Handle", L"No Transaction Handle Found", MB_OK);
		return;
	}

	int retcode = FP3_FunctionLoadBackGroundHandleToFront(hInt, hTrx, TIMEOUT_DEFAULT);

	if (retcode == TRAN_RESULT_OK)
	{
		// change icon
		ST_TRANSACTION_DATA* pData = GetTransactionDataPointer(hInt, hTrx);
		pData->isBackgroundTrx = FALSE;

		HTREEITEM hTransaction = m_treeIterface.GetSelectedItem();
		m_treeIterface.SetItemImage(hTransaction, 1, 1);

		// Find the active (FrontScreen Trx) in Interface TreeCtrl and select it
		CTreeCtrlFindTransactionHandle(hInt, hTrx, TRUE);
		if (ReadTransactionFromECR(hInt, hTrx) == TRAN_RESULT_OK)
			// Display the details of Trx
			DisplayTransaction(hInt, hTrx, FALSE);
	}

	HandleErrorCode(retcode);
}

void CePosDlg::OnBnClickedButtonGetMEcrBGTrxList()
{
	int retcode = TRAN_RESULT_OK;
	ST_MASTERECR_HANDLE_LIST stHandleList;
	uint16 numberOfHandles = 0;

#define MAX_NUMBER_OF_HANDLES	500
	ST_MASTERECR_BACKGROUND_TRX_HANDLE stBGTHandles[MAX_NUMBER_OF_HANDLES];

	HINT hInt = GetSelectedInterface();


	memset(&stHandleList, 0, sizeof(stHandleList));

	stHandleList.pHandle = stBGTHandles;
	stHandleList.maxNumberOfHandles = MAX_NUMBER_OF_HANDLES;

	retcode = FP3_GetListOfBackgroundTransaction(hInt, TRAN_STATUS_FREE, &stHandleList, TIMEOUT_DEFAULT);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

Exit:
	char errorText[128];
	memset(errorText, 0, sizeof(errorText));
	if (retcode)
		GetErrorMessage(retcode, errorText);

	CListBoxPrintf(&m_ListMasterECRMode, "FP3_GetListOfBackgroundTransaction (%04X)", retcode);
	if (strlen(errorText))
		CListBoxPrintf(&m_ListMasterECRMode, "    %s",  errorText);
	CListBoxPrintf(&m_ListMasterECRMode, "    %d Handles", stHandleList.numberOfHandlesInList);

	return;
}

void CePosDlg::OnBnClickedButtonGetMEcrBGTrxData()
{
	int retcode = TRAN_RESULT_OK;
	ST_MASTERECR_TRANSACTION_DATA stTransactionData;
	bool isBackgroundTrx = FALSE;

	uint16 BufferReadLen = 0;
	uint16 BufferTotalLen = 0;

	HINT hInt = GetSelectedInterface();
	HTRX hTrx = GetSelectedTransaction();

	memset(&stTransactionData, 0, sizeof(stTransactionData));
	stTransactionData.sizeOfBuffer = sizeof(stTransactionData.Data);

	retcode = FP3_GetDataOfBackgroundTransaction(hInt, hTrx, &stTransactionData, TIMEOUT_DEFAULT);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	// This is just for tracing needs...
//	decodeTLVTag( 1, 0, stTransactionData.pData, stTransactionData.lenOfData );
Exit:

	char errorText[128];
	memset(errorText, 0, sizeof(errorText));
	if (retcode)
		GetErrorMessage(retcode, errorText);

	CListBoxPrintf(&m_ListMasterECRMode, "FP3_GetDataOfBackgroundTransaction (%04X)",  retcode);
	if (strlen(errorText))
		CListBoxPrintf(&m_ListMasterECRMode, "    %s",  errorText);
	CListBoxPrintf(&m_ListMasterECRMode	, "    %d Commands, Len=%d bytes", stTransactionData.numberOfCommandsInList, stTransactionData.lenOfData);
	return;
}

void CePosDlg::OnBnClickedButtonSetMEcrBGTrxStatus()
{
}

void CePosDlg::OnBnClickedButtonListenMEcr()
{
	if (m_MEcrServerSocket != INVALID_SOCKET)
	{
		closesocket(m_MEcrServerSocket);
		WSACleanup();
		m_MEcrServerSocket = INVALID_SOCKET;
		KillTimer(m_MEcrServerSocketTimer);
		DisplayInfo("Server Socket Closed !!");
		m_ButtonListenMEcr.SetWindowTextW(L"NOT\nListening...");
	}
	else
	{
		ListenServerSocket(&m_MEcrServerSocket, 5500);
		CListBoxPrintf(&m_ListMasterECRMode, "Listening Port %d", 5500);
		m_ButtonListenMEcr.SetWindowTextW(L"Listening...");
		m_MEcrServerSocketTimer = SetTimer(4, 100, NULL);
	}
}
