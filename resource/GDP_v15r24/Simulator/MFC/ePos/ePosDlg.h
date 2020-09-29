
// ePosDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "GmpSmartDll.h"
#include "sqlite3.h"
#include "ButtonCustom.h"

#define GMP_SIM_VERSION "v15r24"

typedef struct
{
	HINT			hInt;
	ST_ECHO			stEcho;
	ST_DEPARTMENT	stDepartments[12];
	ST_TAX_RATE		stTaxRates[8];
	ST_EXCHANGE		stExchangeTable[10];
	ST_EXCHANGE_PROFILE	stExchangeProfileTable[4];
	uint8			numberOfTotalDepartments;
	uint8			numberOfReceivedDepartments;
	uint8			numberOfTotalTaxRates;
	uint8			numberOfReceivedTaxRates;
	uint8			numberOfReceivedExchangeRates;
	uint8			numberOfTotalExchangeRates;
	uint8			m_uniqueId[24];
} ST_INTERFACE_DATA;

typedef struct
{
	HTRX			hTrx;
	bool			isBackgroundTrx;
	ST_TICKET		m_stTicket;
} ST_TRANSACTION_DATA;

// CePosDlg dialog
class CePosDlg : public CDialogEx
{
// Construction
public:
	CePosDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EPOS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	ST_MASTERECR_HANDLE_LIST stHandleList;
	ST_MASTERECR_TRANSACTION_DATA stTransactionData;
	CImageList m_myImageList;
	CTabCtrl m_TabFunctionalControls;
	CTabCtrl m_TabCommandMode;

	CButton m_Button_TestTransaction;
	CButton m_Button_BatchCommand_Send;
	CButton m_Button_BatchCommand_ListenAndSend;
	CButton m_Button_BatchCommand_ClearList;

	CButton m_Button_GetHandleList;
	CButton m_Button_Ping;
	CButton m_Button_Echo;
	CButton m_Button_Pair;
	CButton m_Button_TicketSale;
	CButton m_Button_PLUSale;
	CButton m_Button_ReadTransactionFromECR;

	CButton m_Button_JumpEcr_ForSinglePayment;
	CButton m_Button_JumpEcr_ForCompletePayment;
	CButton m_Button_GetInput;
	CButton m_Button_SetCommScenario;
	CButton m_Button_SetuApplicationCommand;
	CButton m_Button_OpenHandle;
	CButton m_Button_PLUConsole;
	CButton m_Button_Functions;
	CButton m_Button_SelectUniqueId;
	CButton m_Button_GetUniqueId;
	CButton m_Button_GetSetFiscalHeader;
	CButton m_Button_TicketHeader;
	CButton m_Button_CashierConsole;
	CButton m_Button_TaxDepartments;
	CButton m_Button_MoneyCollection;
	CButton m_Button_Taxless;
	CButton m_Button_Vat_Excluded;
	CButton m_Button_YemekCeki;
	CButton m_Button_Loyalty;
	CButton m_Button_TaxfreeSet;
	CButton m_Button_TaxfreeSetTaxrefundAmount;
	CButton m_Button_VoidItem;
	CButton m_Button_PrintTotals;
	CButton m_Button_EKUConsole;
	CButton m_Button_FileSystemConsole;
	CButton m_Button_ExchangeTable;
	CButton m_Button_GetSetCurrencyProfile;
	CButton m_Button_VoidMatrahsiz;
	CButton m_Button_IncreaseAmount;
	CButton m_Button_PrintPreMF;
	CButton m_Button_TransactionConsole;
	CButton m_Button_KasaAvans;
	CButton m_Button_IncreasePercent;
	CButton m_Button_PrintMF;
	CButton m_Button_KasaPayment;
	CButton m_Button_CariHesap;
	CButton m_Button_OtoparkEntryTicket;
	CButton m_Button_ReversePayments;
	CButton m_Button_DecreaseAmount;
	CButton m_Button_CloseHandle;
	CButton m_Button_PaymentCash;
	CButton m_Button_DatabaseConsole;
	CButton m_Button_UserMessage;
	CButton m_Button_ReadCard;
	CButton m_Button_DecreasePercent;
	CButton m_Button_Condition;
	CButton m_Button_OptionFlags;
	CButton m_Button_CheckPairingStatus;

	CButton m_CheckBox_Banking_Opt[8];

	CButton m_Button_0;
	CButton m_Button_1;
	CButton m_Button_2;
	CButton m_Button_3;
	CButton m_Button_4;
	CButton m_Button_5;
	CButton m_Button_6;
	CButton m_Button_7;
	CButton m_Button_8;
	CButton m_Button_9;
	CButton m_Button_00;
	CButton m_Button_Point;
	CButton m_Button_Multiply;
	CButton m_Button_Backspace;
	CButton m_Button_Subtotal;
	CButton m_Button_PluRead;
	CButton m_Button_Refund;
	CButton m_Button_VoidAllTicket;
	CButton m_Button_Invoice;
	CButton m_Button_PaymentList;
	CButton m_Button_PaymentDoAny;
	CButton m_Button_PaymentDoCredit;
	CButton m_Button_PaymentDoCash;
	CButton m_Button_CloseTicket;
	CButton m_Button_SetOnlineInvoice;
	//CButton m_Button_GetOnlineInvoice;
	CButton m_Button_SetExchangeProfile;

	CButton m_Button_TaxFreeInfo;

	CButton m_ButtonDepartman1;
	CButton m_ButtonDepartman2;
	CButton m_ButtonDepartman3;
	CButton m_ButtonDepartman4;
	CButton m_ButtonDepartman5;
	CButton m_ButtonDepartman6;
	CButton m_ButtonDepartman7;
	CButton m_ButtonDepartman8;
	CButton m_ButtonDepartman9;
	CButton m_ButtonDepartman10;
	CButton m_ButtonDepartman11;
	CButton m_ButtonDepartman12;
	CButton m_ButtonGetMEcrBGTrxList;
	CButton m_ButtonGetMEcrBGTrxData;
	CButton m_ButtonSetMEcrBGTrxStatus;
	CButton m_ButtonListenMEcr;
	CFont *myFont1;
	CFont *myFont2;
	CFont *myFont3;
	CFont *buttonFont;
	CFont *buttonFontBig;
	ST_GMP_PAIR_RESP m_GMPPairResp;
	CBrush* m_pEditBkBrush;
	CString m_csTtemCount;
	CListBox m_listPrinterOutput;
	CListCtrl m_listBatchCommand;
	CEdit m_ListControlMainDisplay;
	CEdit m_EditControlInput;
	CString m_csInput;
	CListBox m_listTransaction;
	CComboBox m_comboBoxCurrency;
	CListBox m_listStatus;
	CTreeCtrl m_treeIterface;
	UINT_PTR m_pingTimer;
	UINT_PTR m_ServerSocketTimer;
	UINT_PTR m_MEcrServerSocketTimer;
	CHAR m_dllVersion[24];
	SOCKET m_MEcrServerSocket;
	SOCKET m_MEcrClientSocket;
	SOCKET m_ServerSocket;
	SOCKET m_ClientSocket;

public:
	void UpdateInterfaceWindow(void);
	void CreateButton(CButton* pbutton, LPCTSTR caption, UINT id, UINT color = NULL, UINT bitmap = NULL);
	void CreateCheckBox(CButton* pButton, LPCTSTR Caption, UINT id, UINT color = NULL, UINT bitmap = NULL);
	int GetPayment(ST_PAYMENT_REQUEST stPaymentRequest[], int numberOfPayments);
	int ReversePayment(ST_PAYMENT_REQUEST* pstReversePayment);
	int ReadTransactionFromECR(HINT hInt, HTRX hTrx);
	void UpdateStatusDisplay(ST_GMP_PAIR_RESP *pGMPPairResp, ST_ECHO *pstEcho);
	void StatusInfo(char * buffer, ...);
	void DisplayItem(ST_TICKET* pstTicket, int i);
	void DisplayTransaction_Item(ST_TICKET* pstTicket, int i);
	void DisplayTransaction_Payment(ST_PAYMENT* pstPayment, int i);
	const char *GetPaymentTypeName(uint32 typeOfPayment);
	const char *GetPaymentSubtypeName(uint32 subtypeOfPayment);
	int StartTicket(HINT hInt, HTRX* phTrx, TTicketType ticketType);
	void DisplayTransaction(HINT hInt, HTRX hTrx, bool itemDetail);
	void DisplayTransaction(ST_TICKET* pstTicket, bool itemDetail);
	void DisplayZReport(ST_Z_REPORT *pZReport);
	char* getHexFormat(uint8* buffer, int len);
	uint32 getAmount(CString m_csInput);
	char* formatCount(uint32 itemCount, byte ItemCountPrecision, uint16 itemUnitType);
	char* formatAmount(uint32 amount, uint16 currency);
	void KeyboardEntry(CString input);
	void DisplayErrorMessage(int errorCode);
	void HandleErrorCode(int errorCode);
	void DepartmentSale(int deptIndex);
	void DisplayInfo(char * buffer, ...);
	void AddIntoCommandBatch(CString commandName, uint32 commandType, uint8* buffer, uint16 bufferLen);
	void CListBoxPrintf(CListBox* pList, char * buffer, ...);
	HTREEITEM CTreeCtrlInsertf(CTreeCtrl* pList, HTREEITEM hParent, bool isBackgroundTrx, char * buffer, ...);
	void PrintInfo(CListBox* plistBox, uint32 flag, char * buffer);
	int ReadDepartmentsAndTaxRatesFromECR(HINT hInt);
	void DisplayDepartmentsAndTaxRates(HINT hInt);
	int ReadCurrencyFromECR(HINT hInt);
	void DisplayCurrency(HINT hInt);
	afx_msg void OnBnClickedButtonPair();
	virtual BOOL DestroyWindow();
	virtual void OnOK();
	afx_msg void OnInterfacePopupMenuNewBackgroundTransaction();
	afx_msg void OnInterfacePopupMenuTransferBackgroundTrxintoFrontScreen();
	afx_msg void OnBnClickedButtonGetMEcrBGTrxList();
	afx_msg void OnBnClickedButtonGetMEcrBGTrxData();
	afx_msg void OnBnClickedButtonSetMEcrBGTrxStatus();
	afx_msg void OnBnClickedButtonListenMEcr();
	afx_msg void OnBnClickedButtonDepartman1();
	afx_msg void OnBnClickedButtonTicketheader();
	afx_msg void OnBnClickedButtonDepartman2();
	afx_msg void OnBnClickedButtonDepartman3();
	afx_msg void OnBnClickedButtonDepartman4();
	afx_msg void OnBnClickedButtonDepartman5();
	afx_msg void OnBnClickedButtonDepartman6();
	afx_msg void OnBnClickedButtonDepartman7();
	afx_msg void OnBnClickedButtonDepartman8();
	afx_msg void OnBnClickedButtonDepartman9();
	afx_msg void OnBnClickedButtonDepartman10();
	afx_msg void OnBnClickedButtonDepartman11();
	afx_msg void OnBnClickedButtonDepartman12();
	afx_msg void OnBnClickedCheckBox1();
	afx_msg void OnBnClickedCheckBox2();
	afx_msg void OnBnClickedCheckBox3();
	afx_msg void OnBnClickedCheckBox4();
	afx_msg void OnBnClickedCheckBox5();
	afx_msg void OnBnClickedCheckBox6();
	afx_msg void OnBnClickedCheckBox7();
	afx_msg void OnBnClickedCheckBox8();
	afx_msg void OnBnClickedButtonNakit();
	afx_msg void OnBnClickedButtonPlu();
	afx_msg void OnBnClickedButtonInvoice();
	afx_msg void OnBnClickedButtonSetOnlineInvoice();
	afx_msg void OnBnClickedButtonSetExchangeProfile();

	afx_msg void OnBnClickedButtonCheckPairingStatus();
	afx_msg void OnBnClickedButtonTaxFreeInfo();
	afx_msg void OnBnClickedButtonReversePayments();
	afx_msg void OnBnClickedButtonVoidAll();
	afx_msg void OnBnClickedButtonVoidItem();
	afx_msg void OnBnClickedButtonMatrahsiz();
	afx_msg void OnBnClickedButtonTaxExceptionTaxless();
	afx_msg void OnBnClickedButtonTaxExceptionVatExcluded();
	afx_msg void OnBnClickedButtonYemekCeki();
	afx_msg void OnBnClickedButtonLoyalty();
	afx_msg void OnBnClickedButtonXXX2();
	afx_msg void OnBnClickedButtonTaxfreeSet();
	afx_msg void OnBnClickedButtonTaxfreeSetTaxfundAmount();
	afx_msg void OnBnClickedButtonTestTransaction();
	afx_msg void OnBnClickedButtonKasaAvans();
	afx_msg void OnBnClickedButtonCariHesap();
	afx_msg void OnBnClickedButtonKasaOdeme();
	afx_msg void OnBnClickedButtonPretotal();
	afx_msg void OnBnClickedButtonTutarArtirim();
	afx_msg void OnBnClickedButtonTutarIndir();
	afx_msg void OnBnClickedButtonOtoparkEntryTicket();
	afx_msg void OnBnClickedButtonPercentInc();
	afx_msg void OnBnClickedButtonPercentDec();
	afx_msg void OnBnClickedButtonVoidPayment();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonCondition();
	afx_msg void OnBnClickedButtonOptionFlags();
	afx_msg void OnBnClickedButtonGetDepartments();
	afx_msg void OnBnClickedButtonSelectCashier();
	afx_msg void OnBnClickedButtonCurrency();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonJumpEcrForSinglePayment();
	afx_msg void OnBnClickedButtonJumpEcrForCompletePayment();
	afx_msg void OnBnClickedButtonGetInput();
	afx_msg void OnBnClickedButtonSetCommScenario();
	afx_msg void OnBnClickedButtonGetSetCurrencyProfile();
	afx_msg void OnBnClickedButtonSetuApplicationCommand();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton00();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonPaymentCash();
	afx_msg void OnBnClickedButtonPoint();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonGetPlu();
	afx_msg void OnBnClickedButtonStatus();
	afx_msg void OnBnClickedButtonPretotal3();
	afx_msg void OnBnClickedButtonPrintTotalsAndPayments();
	afx_msg void OnBnClickedButtonPrintBeforeMf();
	afx_msg void OnBnClickedButtonPrintMf();
	afx_msg void OnBnClickedButtonEcho();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonCredit();
	afx_msg void OnBnClickedButtonTicket();
	afx_msg void OnBnClickedButtonFiscalPrinterStart();
	afx_msg void OnBnClickedButtonRefund();
	afx_msg void OnBnClickedButtonCloseTicket();
	afx_msg void OnBnClickedButtonPercentDec2();
	afx_msg void OnBnClickedButtonFunction();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPluConsole();
	afx_msg void OnBnClickedButtonEkuConsole();
	afx_msg void OnBnClickedButtonFileSystemConsole();
	afx_msg void OnBnClickedButtonGetHandleList();
	afx_msg void OnBnClickedButtonPing();
	afx_msg void OnBnClickedButtonReadCard();
	afx_msg void OnBnClickedButtonGetUniqueId();
	afx_msg void OnBnClickedButtonGetSetFiscalHeader();
	afx_msg void OnBnClickedButtonSelectUniqueId();
	afx_msg void OnBnClickedButtonPayment();
	afx_msg void OnBnClickedButtonDatabaseConsole();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnSelchangeTabFunctionalControls(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeTabCommandMode(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonBatchCommandSend();
	afx_msg void OnBnClickedButtonBatchCommandListenAndSend();
	afx_msg void OnBnClickedButtonBatchCommandClearList();

	void CheckBox(int item);
	uint16	ingSetTLV(uint8 *pmsg, uint16 Tag, uint8 *pdata, uint16 dataLen);

	bool GetStringInput(CString caption, CString* input);
	bool GetStringInput(CString caption, char* input);
	bool GetStringInputLn(CString caption, char* input, uint16 MaxLen);
	bool GetIntegerInput(CString caption, int* input);
	bool GetIntegerInput(CString caption, char* input);
	int TestTransaction();
	void ListenServerSocket(SOCKET *socket, uint16 port);
	void ProcessBatchCommand(char* sicilNo);
	int GetBatchCommand(uint8* sendBuffer);
	void ResizeControls(void);
	void Move(CWnd* pctrl, long left, long top, long width, long heigth);
	uint16 decodeTLVTag(int level, uint32 tag, uint8* tagData, uint16 tagDataLen);
	uint32 processRequest_GetListOfBackgroundTransaction(uint8* Buffer, uint16* pBufferTotalLen);
	uint16 processECRMessage(SOCKET m_socket, uint8* recvBuffer, uint16 recvLen);
	uint16 sendSocketData(SOCKET m_socket, uint8* tpdu, uint8* sicilNoOfClient, uint32 functionTag, uint8* Buffer, uint16 BufferLen);
	void DecodeuApplicationRequest(char* sicilNo, uint8* recvBuffer, int recvLen);
	CListBox m_ListMasterECRMode;
	bool m_TaxExceptional_Taxless;
	bool m_TaxExceptional_Vat_Excluded;
	void GetTypedAmount(uint32* amount, uint16* currency);
	void GetTypedItemCount(uint32* pItemCount, uint8* pItemCountPrecition);
	afx_msg void OnLbnSelchangeListStatus();
	void OnPaymentByVas(uint32 amount);
	void OnPaymentYemekCeki(uint32 amount);
	void OnTransactionLoyalty(void);
	CListBox m_ListInterfaceSettings;
	afx_msg void OnSelchangedTreeInterface(NMHDR *pNMHDR, LRESULT *pResult);
	HINT GetSelectedInterface(void);
	HTRX GetSelectedTransaction(void);
	void CTreeCtrlInsertTransactionHandle(HTRX hTrx, bool isBackgroundTrx);
	int CTreeCtrlRemoveTransactionHandle(HINT hInt, HTRX hTrx);
	int TransactionHandle_CloseAndRemove(HINT hInt, HTRX hTrx);
	int TransactionHandle_StartAndInsert(HINT hInt, HTRX* phTrx, bool isBackgroundTransaction, byte* uniqueId, int lenOfuniqueId);
	bool CTreeCtrlFindTransactionHandle(HINT hInt, HTRX hTrx, bool bSelect);
	HTRX CTreeCtrlFindFrontScreenHandle(HINT hInt);
	int Echo();
	afx_msg void OnRclickTreeInterface(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	ST_INTERFACE_DATA* GetInterfaceDataPointer(HINT hInt);
	ST_TRANSACTION_DATA* GetTransactionDataPointer(HINT hInt, HTRX hTrx);
	int ReadOpenTransactionHandleListFromECR(HINT hInt);
};
