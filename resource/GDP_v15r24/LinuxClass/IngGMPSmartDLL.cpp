
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdarg.h>
//#include <unistd.h>

#include "IngGMPSmartDLL.h"

CIngGMPSmartDLL::CIngGMPSmartDLL()
{
	memset(&m_Pointers, 0x00, sizeof(m_Pointers));
	m_Lib = NULL;
}

CIngGMPSmartDLL::~CIngGMPSmartDLL()
{
	if (m_Lib != NULL)
	{
		Trace("Freeing library...");
		dlclose(m_Lib);
	}
}

void CIngGMPSmartDLL::Trace(const char *Format, ...)
{
	char Buffer[1024];
	va_list va;

	va_start(va, Format);
	vsprintf(Buffer, Format, va);

	printf("%s\n", Buffer);

	va_end(va);
}

void *CIngGMPSmartDLL::GetFunction(const char *FunctionName)
{
	void *FuncPtr;

	Trace("Finding '%s' function...", FunctionName);

	if (m_Lib == NULL)
	{
		Trace("Lib not opened.");
		return NULL;
	}

	FuncPtr = (void *)dlsym(m_Lib, FunctionName);

	if (FuncPtr == NULL)
	{
		Trace("'%s' Function couldn't Find.", FunctionName);
		Trace("dlError = %s", dlerror());
		return NULL;
	}

	Trace("'%s' function Found.", FunctionName);
	Trace("'%s' = %p", FunctionName, FuncPtr);

	return FuncPtr;
}

int CIngGMPSmartDLL::LoadFunctions(const char *LibName)
{
	if (m_Lib != NULL)
	{
		Trace("DLL Already opened.");
		return -1;
	}

	m_Lib = dlopen(LibName, RTLD_LAZY);

	if (m_Lib == NULL)
	{
		Trace("DLL can't opened.");
		return -2;
	}

	m_Pointers.SetXmlFilePath = (T_SetXmlFilePath) GetFunction("SetXmlFilePath");
	m_Pointers.gmpReadTLVlen = (T_gmpReadTLVlen) GetFunction("gmpReadTLVlen");
	m_Pointers.gmpReadTLVtag = (T_gmpReadTLVtag) GetFunction("gmpReadTLVtag");
	m_Pointers.gmpTlvSetLen = (T_gmpTlvSetLen) GetFunction("gmpTlvSetLen");
	m_Pointers.gmpSetTLV = (T_gmpSetTLV) GetFunction("gmpSetTLV");
	m_Pointers.gmpSetTLVbcd = (T_gmpSetTLVbcd) GetFunction("gmpSetTLVbcd");
	m_Pointers.gmpSetTLVbcd_64 = (T_gmpSetTLVbcd_64) GetFunction("gmpSetTLVbcd_64");
	m_Pointers.gmpSearchTLV = (T_gmpSearchTLV) GetFunction("gmpSearchTLV");
	m_Pointers.gmpSearchTLVbcd_8 = (T_gmpSearchTLVbcd_8) GetFunction("gmpSearchTLVbcd_8");
	m_Pointers.gmpSearchTLVbcd_16 = (T_gmpSearchTLVbcd_16) GetFunction("gmpSearchTLVbcd_16");
	m_Pointers.gmpSearchTLVbcd_32 = (T_gmpSearchTLVbcd_32) GetFunction("gmpSearchTLVbcd_32");
	m_Pointers.gmpSearchTLVbcd_64 = (T_gmpSearchTLVbcd_64) GetFunction("gmpSearchTLVbcd_64");
	m_Pointers.gmpSetTLV_HL = (T_gmpSetTLV_HL) GetFunction("gmpSetTLV_HL");
	m_Pointers.gmpReadTLVtag_HL = (T_gmpReadTLVtag_HL) GetFunction("gmpReadTLVtag_HL");
	m_Pointers.gmpReadTLVlen_HL = (T_gmpReadTLVlen_HL) GetFunction("gmpReadTLVlen_HL");

	m_Pointers.FP3_FileSystem_FileRead = (T_FP3_FileSystem_FileRead) GetFunction("FP3_FileSystem_FileRead");
	m_Pointers.FP3_FileSystem_FileRemove = (T_FP3_FileSystem_FileRemove) GetFunction("FP3_FileSystem_FileRemove");
	m_Pointers.FP3_FileSystem_FileRename = (T_FP3_FileSystem_FileRename) GetFunction("FP3_FileSystem_FileRename");
	m_Pointers.FP3_FileSystem_FileWrite = (T_FP3_FileSystem_FileWrite) GetFunction("FP3_FileSystem_FileWrite");
	m_Pointers.FP3_FileSystem_DirChange = (T_FP3_FileSystem_DirChange) GetFunction("FP3_FileSystem_DirChange");
	m_Pointers.FP3_FileSystem_DirListFiles = (T_FP3_FileSystem_DirListFiles) GetFunction("FP3_FileSystem_DirListFiles");
	m_Pointers.FP3_Database_GetHandle = (T_FP3_Database_GetHandle) GetFunction("FP3_Database_GetHandle");
	m_Pointers.FP3_Database_FreeStructure = (T_FP3_Database_FreeStructure) GetFunction("FP3_Database_FreeStructure");
	m_Pointers.FP3_Database_Open = (T_FP3_Database_Open) GetFunction("FP3_Database_Open");
	m_Pointers.FP3_Database_Close = (T_FP3_Database_Close) GetFunction("FP3_Database_Close");
	m_Pointers.FP3_Database_Execute = (T_FP3_Database_Execute) GetFunction("FP3_Database_Execute");
	m_Pointers.FP3_Database_Query = (T_FP3_Database_Query) GetFunction("FP3_Database_Query");
	m_Pointers.FP3_Database_QueryReadLine = (T_FP3_Database_QueryReadLine) GetFunction("FP3_Database_QueryReadLine");
	m_Pointers.FP3_Database_QueryColomnCaptions = (T_FP3_Database_QueryColomnCaptions) GetFunction("FP3_Database_QueryColomnCaptions");
	m_Pointers.FP3_Database_QueryReset = (T_FP3_Database_QueryReset) GetFunction("FP3_Database_QueryReset");
	m_Pointers.FP3_Database_QueryFinish = (T_FP3_Database_QueryFinish) GetFunction("FP3_Database_QueryFinish");
	m_Pointers.GMP_GetDllVersion = (T_GMP_GetDllVersion) GetFunction("GMP_GetDllVersion");
	m_Pointers.FP3_GMP_StartPairingInit = (T_FP3_GMP_StartPairingInit) GetFunction("FP3_GMP_StartPairingInit");
	m_Pointers.FP3_FunctionGetHandleList = (T_FP3_FunctionGetHandleList) GetFunction("FP3_FunctionGetHandleList");

	m_Pointers.FP3_Start = (T_FP3_Start) GetFunction("FP3_Start");
	m_Pointers.FP3_Close = (T_FP3_Close) GetFunction("FP3_Close");
	m_Pointers.FP3_Ping = (T_FP3_Ping) GetFunction("FP3_Ping");
	m_Pointers.FP3_Echo = (T_FP3_Echo) GetFunction("FP3_Echo");
	m_Pointers.FP3_PrintTotalsAndPayments = (T_FP3_PrintTotalsAndPayments) GetFunction("FP3_PrintTotalsAndPayments");
	m_Pointers.FP3_PrintBeforeMF = (T_FP3_PrintBeforeMF) GetFunction("FP3_PrintBeforeMF");
	m_Pointers.FP3_PrintMF = (T_FP3_PrintMF) GetFunction("FP3_PrintMF");
	m_Pointers.FP3_PrintUserMessage = (T_FP3_PrintUserMessage) GetFunction("FP3_PrintUserMessage");
	m_Pointers.FP3_GetTicket = (T_FP3_GetTicket) GetFunction("FP3_GetTicket");
	m_Pointers.FP3_GetPLU = (T_FP3_GetPLU) GetFunction("FP3_GetPLU");
	m_Pointers.FP3_Payment = (T_FP3_Payment) GetFunction("FP3_Payment");
	m_Pointers.FP3_ReversePayment = (T_FP3_ReversePayment) GetFunction("FP3_ReversePayment");
	m_Pointers.FP3_TicketHeader = (T_FP3_TicketHeader) GetFunction("FP3_TicketHeader");
	m_Pointers.FP3_SetInvoice = (T_FP3_SetInvoice) GetFunction("FP3_SetInvoice");
	m_Pointers.FP3_SetParkingTicket = (T_FP3_SetParkingTicket) GetFunction("FP3_SetParkingTicket");
	m_Pointers.FP3_ItemSale = (T_FP3_ItemSale) GetFunction("FP3_ItemSale");
	m_Pointers.FP3_Matrahsiz = (T_FP3_Matrahsiz) GetFunction("FP3_Matrahsiz");
	m_Pointers.FP3_KasaAvans = (T_FP3_KasaAvans) GetFunction("FP3_KasaAvans");
	m_Pointers.FP3_CustomerAvans = (T_FP3_CustomerAvans) GetFunction("FP3_CustomerAvans");
	m_Pointers.FP3_KasaPayment = (T_FP3_KasaPayment) GetFunction("FP3_KasaPayment");
	m_Pointers.FP3_Pretotal = (T_FP3_Pretotal) GetFunction("FP3_Pretotal");
	m_Pointers.FP3_DisplayPaymentSummary = (T_FP3_DisplayPaymentSummary) GetFunction("FP3_DisplayPaymentSummary");
	m_Pointers.FP3_Plus = (T_FP3_Plus) GetFunction("FP3_Plus");
	m_Pointers.FP3_Minus = (T_FP3_Minus) GetFunction("FP3_Minus");
	m_Pointers.FP3_Inc = (T_FP3_Inc) GetFunction("FP3_Inc");
	m_Pointers.FP3_Dec = (T_FP3_Dec) GetFunction("FP3_Dec");
	m_Pointers.FP3_VoidPayment = (T_FP3_VoidPayment) GetFunction("FP3_VoidPayment");
	m_Pointers.FP3_VoidAll = (T_FP3_VoidAll) GetFunction("FP3_VoidAll");
	m_Pointers.FP3_VoidItem = (T_FP3_VoidItem) GetFunction("FP3_VoidItem");
	m_Pointers.FP3_SetTaxFreeRefundAmount = (T_FP3_SetTaxFreeRefundAmount) GetFunction("FP3_SetTaxFreeRefundAmount");
	m_Pointers.FP3_SetTaxFree = (T_FP3_SetTaxFree) GetFunction("FP3_SetTaxFree");
	m_Pointers.FP3_MultipleCommand = (T_FP3_MultipleCommand) GetFunction("FP3_MultipleCommand");
	m_Pointers.FP3_FunctionGetUniqueIdList = (T_FP3_FunctionGetUniqueIdList) GetFunction("FP3_FunctionGetUniqueIdList");
	m_Pointers.FP3_GetTlvData = (T_FP3_GetTlvData) GetFunction("FP3_GetTlvData");
	m_Pointers.FP3_GetCashierTable = (T_FP3_GetCashierTable) GetFunction("FP3_GetCashierTable");
	m_Pointers.FP3_GetExchangeTable = (T_FP3_GetExchangeTable) GetFunction("FP3_GetExchangeTable");
	m_Pointers.FP3_GetTaxRates = (T_FP3_GetTaxRates) GetFunction("FP3_GetTaxRates");
	m_Pointers.FP3_GetDepartments = (T_FP3_GetDepartments) GetFunction("FP3_GetDepartments");
	m_Pointers.FP3_GetPaymentApplicationInfo = (T_FP3_GetPaymentApplicationInfo) GetFunction("FP3_GetPaymentApplicationInfo");
	m_Pointers.FP3_GetVasApplicationInfo = (T_FP3_GetVasApplicationInfo) GetFunction("FP3_GetVasApplicationInfo");
	m_Pointers.FP3_GetCurrentFiscalCounters = (T_FP3_GetCurrentFiscalCounters) GetFunction("FP3_GetCurrentFiscalCounters");
	m_Pointers.FP3_GetPluDatabaseInfo = (T_FP3_GetPluDatabaseInfo) GetFunction("FP3_GetPluDatabaseInfo");
	m_Pointers.FP3_GetTicketHeader = (T_FP3_GetTicketHeader) GetFunction("FP3_GetTicketHeader");
	m_Pointers.FP3_SetPluDatabaseInfo = (T_FP3_SetPluDatabaseInfo) GetFunction("FP3_SetPluDatabaseInfo");
	m_Pointers.FP3_SetDepartments = (T_FP3_SetDepartments) GetFunction("FP3_SetDepartments");
	m_Pointers.FP3_SetuApplicationFunction = (T_FP3_SetuApplicationFunction) GetFunction("FP3_SetuApplicationFunction");
	m_Pointers.FP3_SetTlvData = (T_FP3_SetTlvData) GetFunction("FP3_SetTlvData");

	m_Pointers.FP3_GetDialogInput_MultipleCommand = (T_FP3_GetDialogInput_MultipleCommand) GetFunction("FP3_GetDialogInput_MultipleCommand");
	m_Pointers.FP3_GetDialogInput_Text = (T_FP3_GetDialogInput_Text) GetFunction("FP3_GetDialogInput_Text");
	m_Pointers.FP3_GetDialogInput_Date = (T_FP3_GetDialogInput_Date) GetFunction("FP3_GetDialogInput_Date");
	m_Pointers.FP3_GetDialogInput_Amount = (T_FP3_GetDialogInput_Amount) GetFunction("FP3_GetDialogInput_Amount");
	m_Pointers.FP3_GetDialogInput_Menu = (T_FP3_GetDialogInput_Menu) GetFunction("FP3_GetDialogInput_Menu");
	m_Pointers.FP3_GetDialogInput_MsgBox = (T_FP3_GetDialogInput_MsgBox) GetFunction("FP3_GetDialogInput_MsgBox");
	m_Pointers.FP3_GetDialogInput_Password = (T_FP3_GetDialogInput_Password) GetFunction("FP3_GetDialogInput_Password");

	m_Pointers.FP3_GetDialogBarcode = (T_FP3_GetDialogBarcode) GetFunction("FP3_GetDialogBarcode");
	m_Pointers.FP3_FunctionReadZReport = (T_FP3_FunctionReadZReport) GetFunction("FP3_FunctionReadZReport");
	m_Pointers.FP3_FunctionReports = (T_FP3_FunctionReports) GetFunction("FP3_FunctionReports");
	m_Pointers.FP3_FunctionEcrParameter = (T_FP3_FunctionEcrParameter) GetFunction("FP3_FunctionEcrParameter");
	m_Pointers.FP3_FunctionBankingBatch = (T_FP3_FunctionBankingBatch) GetFunction("FP3_FunctionBankingBatch");
	m_Pointers.FP3_FunctionBankingParameter = (T_FP3_FunctionBankingParameter) GetFunction("FP3_FunctionBankingParameter");
	m_Pointers.FP3_FunctionCashierLogin = (T_FP3_FunctionCashierLogin) GetFunction("FP3_FunctionCashierLogin");
	m_Pointers.FP3_FunctionCashierLogout = (T_FP3_FunctionCashierLogout) GetFunction("FP3_FunctionCashierLogout");
	m_Pointers.FP3_FunctionOpenDrawer = (T_FP3_FunctionOpenDrawer) GetFunction("FP3_FunctionOpenDrawer");
	m_Pointers.FP3_FunctionChangeTicketHeader = (T_FP3_FunctionChangeTicketHeader) GetFunction("FP3_FunctionChangeTicketHeader");
	m_Pointers.FP3_FunctionBankingRefund = (T_FP3_FunctionBankingRefund) GetFunction("FP3_FunctionBankingRefund");
	m_Pointers.FP3_FunctionEkuPing = (T_FP3_FunctionEkuPing) GetFunction("FP3_FunctionEkuPing");
	m_Pointers.FP3_FunctionEkuReadInfo = (T_FP3_FunctionEkuReadInfo) GetFunction("FP3_FunctionEkuReadInfo");
	m_Pointers.FP3_FunctionEkuReadHeader = (T_FP3_FunctionEkuReadHeader) GetFunction("FP3_FunctionEkuReadHeader");
	m_Pointers.FP3_FunctionEkuReadData = (T_FP3_FunctionEkuReadData) GetFunction("FP3_FunctionEkuReadData");
	m_Pointers.FP3_FunctionEkuSeek = (T_FP3_FunctionEkuSeek) GetFunction("FP3_FunctionEkuSeek");
	m_Pointers.FP3_FunctionReadCard = (T_FP3_FunctionReadCard) GetFunction("FP3_FunctionReadCard");
	m_Pointers.FP3_OptionFlags = (T_FP3_OptionFlags) GetFunction("FP3_OptionFlags");
	m_Pointers.FP3_JumpToECR = (T_FP3_JumpToECR) GetFunction("FP3_JumpToECR");

	m_Pointers.prepare_Text = (T_prepare_Text) GetFunction("prepare_Text");
	m_Pointers.prepare_Amount = (T_prepare_Amount) GetFunction("prepare_Amount");
	m_Pointers.prepare_Menu = (T_prepare_Menu) GetFunction("prepare_Menu");
	m_Pointers.prepare_Date = (T_prepare_Date) GetFunction("prepare_Date");
	m_Pointers.prepare_Password = (T_prepare_Password) GetFunction("prepare_Password");
	m_Pointers.prepare_MsgBox = (T_prepare_MsgBox) GetFunction("prepare_MsgBox");
	m_Pointers.prepare_JumpToECR = (T_prepare_JumpToECR) GetFunction("prepare_JumpToECR");
	m_Pointers.prepare_Condition = (T_prepare_Condition) GetFunction("prepare_Condition");
	m_Pointers.prepare_OptionFlags = (T_prepare_OptionFlags) GetFunction("prepare_OptionFlags");
	m_Pointers.prepare_Start = (T_prepare_Start) GetFunction("prepare_Start");
	m_Pointers.prepare_Close = (T_prepare_Close) GetFunction("prepare_Close");
	m_Pointers.prepare_TicketHeader = (T_prepare_TicketHeader) GetFunction("prepare_TicketHeader");
	m_Pointers.prepare_ItemSale = (T_prepare_ItemSale) GetFunction("prepare_ItemSale");
	m_Pointers.prepare_SetInvoice = (T_prepare_SetInvoice) GetFunction("prepare_SetInvoice");
	m_Pointers.prepare_SetParkingTicket = (T_prepare_SetParkingTicket) GetFunction("prepare_SetParkingTicket");
	m_Pointers.prepare_Payment = (T_prepare_Payment) GetFunction("prepare_Payment");
	m_Pointers.prepare_ReversePayment = (T_prepare_ReversePayment) GetFunction("prepare_ReversePayment");
	m_Pointers.prepare_PrintUserMessage = (T_prepare_PrintUserMessage) GetFunction("prepare_PrintUserMessage");
	m_Pointers.prepare_PrintTotalsAndPayments = (T_prepare_PrintTotalsAndPayments) GetFunction("prepare_PrintTotalsAndPayments");
	m_Pointers.prepare_PrintBeforeMF = (T_prepare_PrintBeforeMF) GetFunction("prepare_PrintBeforeMF");
	m_Pointers.prepare_PrintMF = (T_prepare_PrintMF) GetFunction("prepare_PrintMF");
	m_Pointers.prepare_VoidItem = (T_prepare_VoidItem) GetFunction("prepare_VoidItem");
	m_Pointers.prepare_Matrahsiz = (T_prepare_Matrahsiz) GetFunction("prepare_Matrahsiz");
	m_Pointers.prepare_Pretotal = (T_prepare_Pretotal) GetFunction("prepare_Pretotal");
	m_Pointers.prepare_DisplayPaymentSummary = (T_prepare_DisplayPaymentSummary) GetFunction("prepare_DisplayPaymentSummary");
	m_Pointers.prepare_Plus = (T_prepare_Plus) GetFunction("prepare_Plus");
	m_Pointers.prepare_Plus_Ex = (T_prepare_Plus_Ex) GetFunction("prepare_Plus_Ex");
	m_Pointers.prepare_Minus = (T_prepare_Minus) GetFunction("prepare_Minus");
	m_Pointers.prepare_Minus_Ex = (T_prepare_Minus_Ex) GetFunction("prepare_Minus_Ex");
	m_Pointers.prepare_Inc = (T_prepare_Inc) GetFunction("prepare_Inc");
	m_Pointers.prepare_Inc_Ex = (T_prepare_Inc_Ex) GetFunction("prepare_Inc_Ex");
	m_Pointers.prepare_Dec = (T_prepare_Dec) GetFunction("prepare_Dec");
	m_Pointers.prepare_Dec_Ex = (T_prepare_Dec_Ex) GetFunction("prepare_Dec_Ex");
	m_Pointers.prepare_VoidPayment = (T_prepare_VoidPayment) GetFunction("prepare_VoidPayment");
	m_Pointers.prepare_VoidAll = (T_prepare_VoidAll) GetFunction("prepare_VoidAll");
	m_Pointers.prepare_SetTaxFree = (T_prepare_SetTaxFree) GetFunction("prepare_SetTaxFree");
	m_Pointers.prepare_SetTaxFreeRefundAmount = (T_prepare_SetTaxFreeRefundAmount) GetFunction("prepare_SetTaxFreeRefundAmount");
	m_Pointers.parse_FP3 = (T_parse_FP3) GetFunction("parse_FP3");
	m_Pointers.parse_GetEcr = (T_parse_GetEcr) GetFunction("parse_GetEcr");
	m_Pointers.ExternalDeviceTrace = (T_ExternalDeviceTrace) GetFunction("ExternalDeviceTrace");
	m_Pointers.ExternalDeviceTraceMemory = (T_ExternalDeviceTraceMemory) GetFunction("ExternalDeviceTraceMemory");
	m_Pointers.GetTagName = (T_GetTagName) GetFunction("GetTagName");
	m_Pointers.GetErrorMessage = (T_GetErrorMessage) GetFunction("GetErrorMessage");
	m_Pointers.GetXmlFilePath = (T_GetXmlFilePath) GetFunction("GetXmlFilePath");

	m_Pointers.FP3_GetInterfaceHandleList = (T_FP3_GetInterfaceHandleList) GetFunction("FP3_GetInterfaceHandleList");

	return 0;
}
