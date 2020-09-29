
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>

#include "GMPSmartDLL.h"

typedef char *(*T_GetErrorMessage)(int ErrorCode, char *Buffer);
typedef int (*T_GMP_GetDllVersion)(char *version);
typedef void (*T_SetIniFilePath)(const char *path);
typedef int (*T_FP3_Echo)(uint32 hInt, ST_ECHO *pstEcho, int timeoutInMiliseconds);
typedef int (*T_FP3_GMP_StartPairingInit)(uint32 hInt, ST_GMP_PAIR *pstGMPPair, ST_GMP_PAIR_RESP *pstGMPPairResp);

typedef int (*T_FP3_OptionFlags)(uint32 hInt, uint64 hTrx, uint64 *pflagsActive, uint64 flagsToBeSet, uint64 flagsToBeClear, int timeoutInMiliseconds);
typedef int (*T_FP3_Start)(uint32 hInt, uint64 *hTrx, uint8 IsBackground, uint8 *uniqueId, int lengthOfUniqueId, uint8 *uniqueIdSign, int lengthOfUniqueIdSign, uint8 *userData, int lengthOfUserData, int timeoutInMiliseconds);
typedef int (*T_FP3_TicketHeader)(uint32 hInt, uint64 hTrx, TTicketType ticketType, int timeoutInMiliseconds);
typedef int (*T_FP3_ItemSale)(uint32 hInt, uint64 hTrx, ST_ITEM* pstItem, ST_TICKET* pstTicket, int timeoutInMiliseconds);
typedef int (*T_FP3_Payment)(uint32 hInt, uint64 hTrx, ST_PAYMENT_REQUEST* pstPaymentRequest, ST_TICKET* pstTicket, int timeoutInMiliseconds);
typedef int (*T_FP3_PrintBeforeMF)(uint32 hInt, uint64 hTrx, int timeoutInMiliseconds);
typedef int (*T_FP3_PrintTMF)(uint32 hInt, uint64 hTrx, int timeoutInMiliseconds);
typedef int (*T_FP3_Close)(uint32 hInt, uint64 hTrx, int timeoutInMiliseconds);
typedef int (*T_FP3_GetInterfaceHandleList)(uint32 *phInt, int Max);
typedef void (*T_SetXmlFilePath)(const char *path);


T_GetErrorMessage _GetErrorMessage = NULL;
T_GMP_GetDllVersion _GMP_GetDllVersion;
T_FP3_Echo _FP3_Echo;
T_FP3_GMP_StartPairingInit _FP3_GMP_StartPairingInit;
T_SetXmlFilePath _SetXmlFilePath;

T_FP3_OptionFlags _FP3_OptionFlags;
T_FP3_Start _FP3_Start;
T_FP3_TicketHeader _FP3_TicketHeader;
T_FP3_ItemSale _FP3_ItemSale;
T_FP3_Payment _FP3_Payment = NULL;
T_FP3_PrintBeforeMF _FP3_PrintBeforeMF;
T_FP3_PrintTMF _FP3_PrintTMF;
T_FP3_Close _FP3_Close;
T_FP3_GetInterfaceHandleList _FP3_GetInterfaceHandleList;

char ErrorBuf[256];
HTRX TransactionHandle;

int GetInterfaceHandle(void *Lib, HINT *pInterfaceHandle)
{
	HINT	InterfaceList[20];
	uint8	ID[64];
	uint32	InterfaceCount = 0;
	uint32	i;

	memset(InterfaceList, 0, sizeof(InterfaceList));
	memset(ID, 0, sizeof(ID));

	printf("Finding 'FP3_GetInterfaceHandleList' function...\n");
	_FP3_GetInterfaceHandleList = (T_FP3_GetInterfaceHandleList)dlsym(Lib, "FP3_GetInterfaceHandleList");

	if (_FP3_GetInterfaceHandleList == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	InterfaceCount = _FP3_GetInterfaceHandleList(InterfaceList, (int)sizeof(InterfaceList));
	*pInterfaceHandle = InterfaceList[0];

	printf("'FP3_GetInterfaceHandleList' function Found.\n");
	printf("'FP3_GetInterfaceHandleList' = %p\n", (void*)_FP3_GetInterfaceHandleList);
	for (i = 0; i < InterfaceCount; ++i)
		printf("\t - %8X\n", InterfaceList[i]);

	return 0;
}

int SetXmlPath(void *Lib)
{
	char Buf[1024];
//	char *Ptr = NULL;

	printf("Finding 'SetXmlFilePath' function...\n");

	_SetXmlFilePath = (T_SetXmlFilePath)dlsym(Lib, "SetXmlFilePath");

	if (_SetXmlFilePath == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -2;
	}

	printf("'SetXmlFilePath' function Found.\n");
	printf("'SetXmlFilePath' = %p\n", _SetXmlFilePath);

	memset(Buf, 0x00, sizeof(Buf));
//	Ptr = getcwd(Buf, sizeof(Buf));
//	if (Ptr == NULL)
//		Buf[0] = 0;
	strcat(Buf, "/home/swrd/Desktop/");

	printf("Path Setting = %s\n", Buf);

	_SetXmlFilePath(Buf);

	printf("'SetXmlFilePath' finished.\n");

	return 0;
}


char *CallGetErrorMessage(void *Lib, int ErrorCode, char *Buffer)
{
	char *Result;

	if (_GetErrorMessage == NULL)
	{
		printf("Finding 'GetErrorMessage' function...\n");

		_GetErrorMessage = (T_GetErrorMessage)dlsym(Lib, "GetErrorMessage");

		if (_GetErrorMessage == NULL)
		{
			printf("Function couldn't Find.\n");
			printf("dlError = %s\n", dlerror());
			return "";
		}

		printf("'GetErrorMessage' function Found.\n");
		printf("'GetErrorMessage' = %p\n", _GetErrorMessage);
	}

	Result = _GetErrorMessage(ErrorCode, Buffer);

	return Result;
}

int GetDllVersion(void *Lib)
{
	char DllVersion[24];
	int Result;

	printf("Finding 'GMP_GetDllVersion' function...\n");

	_GMP_GetDllVersion = (T_GMP_GetDllVersion)dlsym(Lib, "GMP_GetDllVersion");

	if (_GMP_GetDllVersion == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -2;
	}

	printf("'GMP_GetDllVersion' function Found.\n");
	printf("'GMP_GetDllVersion' = %p\n", _GMP_GetDllVersion);

	memset(DllVersion, 0x00, sizeof(DllVersion));
	Result = _GMP_GetDllVersion(DllVersion);

	printf("'GMP_GetDllVersion' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	if (Result == 0)
		printf("DllVersion = '%s'\n", DllVersion);

	return Result;
}

int CallEcho(void *Lib, HINT InterfaceHandle)
{
	ST_ECHO stEcho;
	int Result;

	printf("Finding 'FP3_Echo' function...\n");

	_FP3_Echo = (T_FP3_Echo)dlsym(Lib, "FP3_Echo");

	if (_FP3_Echo == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	printf("'FP3_Echo' function Found.\n");
	printf("'FP3_Echo' = %p\n", _FP3_Echo);

	memset(&stEcho, 0x00, sizeof(stEcho));

	stEcho.StructSize = sizeof(stEcho);

	Result = _FP3_Echo(InterfaceHandle, &stEcho, TIMEOUT_ECHO);

	printf("'FP3_Echo' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

int CallPairing(void *Lib, HINT InterfaceHandle)
{
	int					Result;
	ST_GMP_PAIR 		stGMPPair;
	ST_GMP_PAIR_RESP	stGMPPairResp;

	printf("Finding 'GMP_StartPairingInit' function...\n");

	_FP3_GMP_StartPairingInit = (T_FP3_GMP_StartPairingInit)dlsym(Lib, "FP3_GMP_StartPairingInit");

	if (_FP3_GMP_StartPairingInit == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	printf("'FP3_GMP_StartPairingInit' function Found.\n");
	printf("'FP3_GMP_StartPairingInit' = %p\n", _FP3_GMP_StartPairingInit);

	// Init Values.
	memset(&stGMPPair, 0x00, sizeof(stGMPPair));
	memset(&stGMPPairResp, 0x00, sizeof(stGMPPairResp));

	stGMPPair.StructSize = sizeof(stGMPPair);
	stGMPPairResp.StructSize = sizeof(stGMPPairResp);

	// Init Yapılabilir
	strcpy(stGMPPair.szProcOrderNumber, "00001");
	sprintf(stGMPPair.szProcDate, "%02d%02d%02d", 10, 10, 17);
	sprintf(stGMPPair.szProcTime, "%02d%02d%02d", 10, 10, 10);
	strcpy(stGMPPair.szExternalDeviceBrand, "FirmBrand");
	strcpy(stGMPPair.szExternalDeviceModel, "FirmModel");
	strcpy(stGMPPair.szExternalDeviceSerialNumber, "0123456789");
	strcpy(stGMPPair.szEcrSerialNumber, "9876543210");

	Result = _FP3_GMP_StartPairingInit(InterfaceHandle, &stGMPPair, &stGMPPairResp);

	printf("'FP3_GMP_StartPairingInit' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

int CallFP3_OptionFlags(void *Lib, HINT InterfaceHandle, HTRX TransactionHandle, uint64 *pflagsActive, uint64 flagsToBeSet, uint64 flagsToBeClear, int timeoutInMiliseconds)
{
	int		Result;

	printf("Finding 'FP3_OptionFlags' function...\n");

	_FP3_OptionFlags = (T_FP3_OptionFlags)dlsym(Lib, "FP3_OptionFlags");

	if (_FP3_OptionFlags == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	printf("'FP3_OptionFlags' function Found.\n");
	printf("'FP3_OptionFlags' = %p\n", _FP3_OptionFlags);

	Result = _FP3_OptionFlags(InterfaceHandle, TransactionHandle, pflagsActive, flagsToBeSet, flagsToBeClear, timeoutInMiliseconds);

	printf("'FP3_OptionFlags' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

int CallFP3_Start(void *Lib, HINT InterfaceHandle, HTRX *pTransactionHandle, uint8 IsBackground, uint8 *uniqueId, int lengthOfUniqueId, uint8 *uniqueIdSign, int lengthOfUniqueIdSign, uint8 *userData, int lengthOfUserData, int timeoutInMiliseconds)
{
	int		Result;

	printf("Finding 'FP3_Start' function...\n");

	_FP3_Start = (T_FP3_Start)dlsym(Lib, "FP3_Start");

	if (_FP3_Start == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	printf("'FP3_Start' function Found.\n");
	printf("'FP3_Start' = %p\n", _FP3_Start);

	Result = _FP3_Start(InterfaceHandle, pTransactionHandle, IsBackground, uniqueId, lengthOfUniqueId, uniqueIdSign, lengthOfUniqueIdSign, userData, lengthOfUserData, timeoutInMiliseconds);

	printf("'FP3_Start' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

int CallFP3_TicketHeader(void *Lib, HINT InterfaceHandle, HTRX TransactionHandle, TTicketType ticketType, int timeoutInMiliseconds)
{
	int		Result;

	printf("Finding 'FP3_TicketHeader' function...\n");

	_FP3_TicketHeader = (T_FP3_TicketHeader)dlsym(Lib, "FP3_TicketHeader");

	if (_FP3_TicketHeader == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	printf("'FP3_TicketHeader' function Found.\n");
	printf("'FP3_TicketHeader' = %p\n", _FP3_TicketHeader);

	Result = _FP3_TicketHeader(InterfaceHandle, TransactionHandle, ticketType, timeoutInMiliseconds);

	printf("'FP3_TicketHeader' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

int CallFP3_ItemSale(void *Lib, HINT InterfaceHandle, HTRX TransactionHandle, ST_ITEM *pstItem, ST_TICKET *pstTicket, int timeoutInMiliseconds)
{
	int		Result;

	printf("Finding 'FP3_ItemSale' function...\n");

	_FP3_ItemSale = (T_FP3_ItemSale)dlsym(Lib, "FP3_ItemSale");

	if (_FP3_ItemSale == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	printf("'FP3_ItemSale' function Found.\n");
	printf("'FP3_ItemSale' = %p\n", _FP3_ItemSale);

	Result = _FP3_ItemSale(InterfaceHandle, TransactionHandle, pstItem, pstTicket, timeoutInMiliseconds);

	printf("'FP3_ItemSale' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

int CallFP3_Payment(void *Lib, HINT InterfaceHandle, HTRX TransactionHandle, ST_PAYMENT_REQUEST *pstPaymentRequest, ST_TICKET *pstTicket, int timeoutInMiliseconds)
{
	int		Result;

	printf("Finding 'FP3_Payment' function...\n");

	if (_FP3_Payment == NULL)
	{
		_FP3_Payment = (T_FP3_Payment)dlsym(Lib, "FP3_Payment");

		if (_FP3_Payment == NULL)
		{
			printf("Function couldn't Find.\n");
			printf("dlError = %s\n", dlerror());
			return -3;
		}

		printf("'FP3_Payment' function Found.\n");
		printf("'FP3_Payment' = %p\n", _FP3_Payment);
	}

	Result = _FP3_Payment(InterfaceHandle, TransactionHandle, pstPaymentRequest, pstTicket, timeoutInMiliseconds);

	printf("'FP3_Payment' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

int CallFP3_PrintBeforeMF(void *Lib, HINT InterfaceHandle, HTRX TransactionHandle, int timeoutInMiliseconds)
{
	int		Result;

	printf("Finding 'FP3_PrintBeforeMF' function...\n");

	_FP3_PrintBeforeMF = (T_FP3_PrintBeforeMF)dlsym(Lib, "FP3_PrintBeforeMF");

	if (_FP3_PrintBeforeMF == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	printf("'FP3_PrintBeforeMF' function Found.\n");
	printf("'FP3_PrintBeforeMF' = %p\n", _FP3_PrintBeforeMF);

	Result = _FP3_PrintBeforeMF(InterfaceHandle, TransactionHandle, timeoutInMiliseconds);

	printf("'FP3_PrintBeforeMF' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

int CallFP3_PrintTMF(void *Lib, HINT InterfaceHandle, HTRX TransactionHandle, int timeoutInMiliseconds)
{
	int		Result;

	printf("Finding 'FP3_PrintTMF' function...\n");

	_FP3_PrintTMF = (T_FP3_PrintTMF)dlsym(Lib, "FP3_PrintMF");

	if (_FP3_PrintTMF == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	printf("'FP3_PrintMF' function Found.\n");
	printf("'FP3_PrintMF' = %p\n", _FP3_PrintTMF);

	Result = _FP3_PrintTMF(InterfaceHandle, TransactionHandle, timeoutInMiliseconds);

	printf("'FP3_PrintMF' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

int CallFP3_Close(void *Lib, HINT InterfaceHandle, HTRX TransactionHandle, int timeoutInMiliseconds)
{
	int		Result;

	printf("Finding 'FP3_Close' function...\n");

	_FP3_Close = (T_FP3_Close)dlsym(Lib, "FP3_Close");

	if (_FP3_Close == NULL)
	{
		printf("Function couldn't Find.\n");
		printf("dlError = %s\n", dlerror());
		return -3;
	}

	printf("'FP3_Close' function Found.\n");
	printf("'FP3_Close' = %p\n", _FP3_Close);

	Result = _FP3_Close(InterfaceHandle, TransactionHandle, timeoutInMiliseconds);

	printf("'FP3_Close' return code = %d (0x%X) : %s\n", Result, Result, CallGetErrorMessage(Lib, Result, ErrorBuf));

	return Result;
}

void DumpTickt(ST_TICKET *pstTicket)
{
	int i;

	printf("\n\n---------------------------------\n");
	printf("ST_TICKET:\n");

	printf("TransactionFlags = %d\n", pstTicket->TransactionFlags);
	printf("OptionFlags = %08X\n", pstTicket->OptionFlags);
	printf("ZNo = %d\n", pstTicket->ZNo);
	printf("FNo = %d\n", pstTicket->FNo);
	printf("EJNo = %d\n", pstTicket->EJNo);
	printf("TotalReceiptAmount = %d\n", pstTicket->TotalReceiptAmount);
	printf("TotalReceiptTax = %d\n", pstTicket->TotalReceiptTax);
	printf("TotalReceiptDiscount = %d\n", pstTicket->TotalReceiptDiscount);
	printf("TotalReceiptIncrement = %d\n", pstTicket->TotalReceiptIncrement);
	printf("CashBackAmount = %d\n", pstTicket->CashBackAmount);
	printf("TotalReceiptItemCancel = %d\n", pstTicket->TotalReceiptItemCancel);
	printf("TotalReceiptPayment = %d\n", pstTicket->TotalReceiptPayment);
	printf("TotalReceiptReversedPayment = %d\n", pstTicket->TotalReceiptReversedPayment);
	printf("KasaAvansAmount = %d\n", pstTicket->KasaAvansAmount);
	printf("KasaPaymentAmount = %d\n", pstTicket->KasaPaymentAmount);
	printf("invoiceAmount = %d\n", pstTicket->invoiceAmount);
	printf("invoiceAmountCurrency = %d\n", pstTicket->invoiceAmountCurrency);
	printf("KatkiPayiAmount = %d\n", pstTicket->KatkiPayiAmount);
	printf("TaxFreeRefund = %d\n", pstTicket->TaxFreeRefund);
	printf("TaxFreeCalculated = %d\n", pstTicket->TaxFreeCalculated);
	printf("szTicketDate = %s\n", pstTicket->szTicketDate);
	printf("szTicketTime = %s\n", pstTicket->szTicketTime);
	printf("ticketType = %d\n", pstTicket->ticketType);
	printf("totalNumberOfItems = %d\n", pstTicket->totalNumberOfItems);
	printf("numberOfItemsInThis = %d\n", pstTicket->numberOfItemsInThis);
	printf("totalNumberOfPayments = %d\n", pstTicket->totalNumberOfPayments);
	printf("numberOfPaymentsInThis = %d\n", pstTicket->numberOfPaymentsInThis);
	printf("TckNo[12] = %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",	pstTicket->TckNo[0], pstTicket->TckNo[1], pstTicket->TckNo[2], pstTicket->TckNo[3],
		   pstTicket->TckNo[4], pstTicket->TckNo[5], pstTicket->TckNo[6], pstTicket->TckNo[7],
		   pstTicket->TckNo[8], pstTicket->TckNo[9], pstTicket->TckNo[10], pstTicket->TckNo[11]);
	printf("invoiceNo = %s\n", pstTicket->invoiceNo);
	printf("invoiceDate = %d\n", pstTicket->invoiceDate);
	printf("invoiceType = %d\n", pstTicket->invoiceType);
	printf("totalNumberOfPrinterLines = %d\n", pstTicket->totalNumberOfPrinterLines);
	printf("numberOfPrinterLinesInThis = %d\n", pstTicket->numberOfPrinterLinesInThis);
	printf("uniqueId = %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
		   pstTicket->uniqueId[0], pstTicket->uniqueId[1], pstTicket->uniqueId[2], pstTicket->uniqueId[3],
		   pstTicket->uniqueId[4], pstTicket->uniqueId[5], pstTicket->uniqueId[6], pstTicket->uniqueId[7],
		   pstTicket->uniqueId[8], pstTicket->uniqueId[9], pstTicket->uniqueId[10], pstTicket->uniqueId[11],
		   pstTicket->uniqueId[12], pstTicket->uniqueId[13], pstTicket->uniqueId[14], pstTicket->uniqueId[15],
		   pstTicket->uniqueId[16], pstTicket->uniqueId[17], pstTicket->uniqueId[18], pstTicket->uniqueId[19],
		   pstTicket->uniqueId[20], pstTicket->uniqueId[21], pstTicket->uniqueId[22], pstTicket->uniqueId[23]);

	printf("Sale Info:\n");
	for (i = pstTicket->totalNumberOfItems - pstTicket->numberOfItemsInThis; i < pstTicket->totalNumberOfItems; ++i)
	{
		printf("\t---------%d-------\n", i);
		printf("\tItemType[%d] : %02X\n", i, pstTicket->SaleInfo[i].ItemType);
		printf("\tItemPrice[%d] : %lld\n", i, pstTicket->SaleInfo[i].ItemPrice);
		printf("\tIncAmount[%d] : %lld\n", i, pstTicket->SaleInfo[i].IncAmount);
		printf("\tDecAmount[%d] : %lld\n", i, pstTicket->SaleInfo[i].DecAmount);
		printf("\tOrigialItemAmount[%d] : %d\n", i, pstTicket->SaleInfo[i].OrigialItemAmount);
		printf("\tOriginalItemAmountCurrency[%d] : %d\n", i, pstTicket->SaleInfo[i].OriginalItemAmountCurrency);
		printf("\tItemVatRate[%d] : %d\n", i, pstTicket->SaleInfo[i].ItemVatRate);
		printf("\tItemCurrencyType[%d] : %d\n", i, pstTicket->SaleInfo[i].ItemCurrencyType);
		printf("\tItemVatIndex[%d] : %d\n", i, pstTicket->SaleInfo[i].ItemVatIndex);
		printf("\tItemCountPrecision[%d] : %d\n", i, pstTicket->SaleInfo[i].ItemCountPrecision);
		printf("\tItemCount[%d] : %d\n", i, pstTicket->SaleInfo[i].ItemCount);
		printf("\tItemUnitType[%d] : %d\n", i, pstTicket->SaleInfo[i].ItemUnitType);
		printf("\tDeptIndex[%d] : %d\n", i, pstTicket->SaleInfo[i].DeptIndex);
		printf("\tFlag[%d] : %08X\n", i, pstTicket->SaleInfo[i].Flag);
		printf("\tName[%d] : %s\n", i, pstTicket->SaleInfo[i].Name);
		printf("\tBarcode[%d] : %s\n", i, pstTicket->SaleInfo[i].Barcode);
	}
	printf("\t----------------\n");

	printf("Payment Info:\n");
	for (i = pstTicket->totalNumberOfPayments - pstTicket->numberOfPaymentsInThis; i < pstTicket->totalNumberOfPayments; ++i)
	{
		printf("\t---------%d-------\n", i);
		printf("\tflags[%d] : %02X\n", i, pstTicket->stPayment[i].flags);
		printf("\tdateOfPayment[%d] : %d\n", i, pstTicket->stPayment[i].dateOfPayment);
		printf("\ttypeOfPayment[%d] : %d\n", i, pstTicket->stPayment[i].typeOfPayment);
		printf("\tsubtypeOfPayment[%d] : %d\n", i, pstTicket->stPayment[i].subtypeOfPayment);
		printf("\torgAmount[%d] : %d\n", i, pstTicket->stPayment[i].orgAmount);
		printf("\torgAmountCurrencyCode[%d] : %d\n", i, pstTicket->stPayment[i].orgAmountCurrencyCode);
		printf("\tpayAmount[%d] : %d\n", i, pstTicket->stPayment[i].payAmount);
		printf("\tpayAmountCurrencyCode[%d] : %d\n", i, pstTicket->stPayment[i].payAmountCurrencyCode);
		printf("\tcashBackAmountInTL[%d] : %d\n", i, pstTicket->stPayment[i].cashBackAmountInTL);
		printf("\tcashBackAmountInDoviz[%d] : %d\n", i, pstTicket->stPayment[i].cashBackAmountInDoviz);

		printf("\tBank Payment Info[%d]:\n", i);
		printf("\t\tbatchNo[%d] : %d\n", i, pstTicket->stPayment[i].stBankPayment.batchNo);
		printf("\t\tstan[%d] : %d\n", i, pstTicket->stPayment[i].stBankPayment.stan);
		printf("\t\tbankBkmId[%d] : %03X\n", i, pstTicket->stPayment[i].stBankPayment.bankBkmId);
		printf("\t\tnumberOfdiscount[%d] : %d\n", i, pstTicket->stPayment[i].stBankPayment.numberOfdiscount);
		printf("\t\tnumberOfbonus[%d] : %d\n", i, pstTicket->stPayment[i].stBankPayment.numberOfbonus);
		printf("\t\tauthorizeCode[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.authorizeCode);
		printf("\t\ttransFlag[%d] : %02X%02X\n", i, pstTicket->stPayment[i].stBankPayment.transFlag[0], pstTicket->stPayment[i].stBankPayment.transFlag[1]);
		printf("\t\tterminalId[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.terminalId);
		printf("\t\tmerchantId[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.merchantId);
		printf("\t\tbankName[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.bankName);

		printf("\t\tCard Info[%d]:\n", i);
		printf("\t\t\tinputType[%d] : %d\n", i, pstTicket->stPayment[i].stBankPayment.stCard.inputType);
		printf("\t\t\tpan[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.stCard.pan);
		printf("\t\t\tholderName[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.stCard.holderName);
		printf("\t\t\ttype[%d] : %02X%02X%02X\n", i,	pstTicket->stPayment[i].stBankPayment.stCard.type[0],
			   pstTicket->stPayment[i].stBankPayment.stCard.type[1],
			   pstTicket->stPayment[i].stBankPayment.stCard.type[2]);


		printf("\t\tPayment Err Message[%d]:\n", i);
		printf("\t\t\tErrorCode[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.stPaymentErrMessage.ErrorCode);
		printf("\t\t\tErrorMsg[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.stPaymentErrMessage.ErrorMsg);
		printf("\t\t\tAppErrorCode[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.stPaymentErrMessage.AppErrorCode);
		printf("\t\t\tAppErrorMsg[%d] : %s\n", i, pstTicket->stPayment[i].stBankPayment.stPaymentErrMessage.AppErrorMsg);
	}
	printf("\t----------------\n");

	printf("VAT Detail:\n");
	for (i = 0; i < MAX_TAX_DETAIL; ++i)
	{
		printf("\t---------%d-------\n", i);
		printf("\tVAT[%d] : %d\n", i, pstTicket->stTaxDetails[i].u32VAT);
		printf("\tAmount[%d] :%d\n", i, pstTicket->stTaxDetails[i].u32Amount);
		printf("\tVAT Percentage[%d] :%d\n", i, pstTicket->stTaxDetails[i].u16VATPercentage);
	}
	printf("\t----------------\n");

	printf("Printer Copy:\n");
	for (i = pstTicket->totalNumberOfPrinterLines - pstTicket->numberOfPrinterLinesInThis; i < pstTicket->totalNumberOfPrinterLines; ++i)
	{
		printf("\t---------%d-------\n", i);
		printf("\tFlag[%d] : %08X\n", i, pstTicket->stPrinterCopy[i].Flag);
		printf("\tlineLen[%d] : %d\n", i, pstTicket->stPrinterCopy[i].lineLen);
		printf("\tline[%d] : %s\n", i, pstTicket->stPrinterCopy[i].line);
	}
	printf("\t----------------\n");

	printf("---------------------------------\n\n");
}

int DoSale(void *Lib)
{
	uint64	ActiveFlags;
	int		RetCode;
	uint8 	UniqueId[24];
	uint32	Amount;
	uint32	ItemAmount;
	uint32	PaymentAmount;
	int		DepartmentIndex;
	int		Type;
	int		ItemIndex;
	int		Result = 0;
	ST_TICKET	stTicket;
	ST_ITEM		stItem;
	ST_PAYMENT_REQUEST stPaymentRequest;
	HINT InterfaceHandle = 0;
	HTRX TransactionHandle = 0;

	RetCode = GetInterfaceHandle(Lib, &InterfaceHandle);
	if (RetCode != 0)
		return RetCode;

	if (RetCode == 0)
		RetCode = CallEcho(Lib, InterfaceHandle);

	if (RetCode == 0)
		RetCode = CallPairing(Lib, InterfaceHandle);

	if (RetCode != 0)
		return RetCode;

	memset(UniqueId, 0x00, sizeof(UniqueId));

	RetCode = CallFP3_Start(Lib, InterfaceHandle, &TransactionHandle, 0, UniqueId, sizeof(UniqueId), NULL, 0, NULL, 0, TIMEOUT_DEFAULT);
	if (RetCode != 0)
		return RetCode;

	RetCode = CallFP3_OptionFlags(Lib, InterfaceHandle, TransactionHandle, &ActiveFlags, GMP3_OPTION_ECHO_PRINTER | GMP3_OPTION_ECHO_ITEM_DETAILS | GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0, TIMEOUT_DEFAULT);
	if (RetCode != 0)
		return RetCode;

	RetCode = CallFP3_TicketHeader(Lib, InterfaceHandle, TransactionHandle, TProcessSale, TIMEOUT_DEFAULT);
	if (RetCode != 0)
		return RetCode;

	memset(&stTicket, 0x00, sizeof(stTicket));
	stTicket.StructSize = sizeof(stTicket);

	memset(&stItem, 0x00, sizeof(stItem));
	stItem.StructSize = sizeof(stItem);

	Amount = 0;

	for (ItemIndex = 1; ; ++ItemIndex)
	{
		if (Amount == 0)
			Type = 1;
		else
		{
			printf("1 - Add New Item:\n");
			printf("2 - Payment:\n");
			Result = scanf("%d", &Type);
		}

		if ((Type != 1) && (Type != 2))
		{
			printf("Payment Type Error %d\n", Result);
			continue;
		}

		if (Type == 2)
			break;

		printf("Item Amount:");
		Result = scanf("%d", &ItemAmount);

		if (ItemAmount == 0)
		{
			printf("Item Amount Error %d\n", Result);
			continue;
		}

		for (;;)
		{
			printf("Department Index: (0 - 11)");
			Result = scanf("%d", &DepartmentIndex);

			if (DepartmentIndex > 11)
			{
				printf("Invalid Department Index %d\n", Result);
				continue;
			}

			break;
		}

		stItem.type				= ITEM_TYPE_DEPARTMENT;
		stItem.subType			= 0;
		stItem.deptIndex		= (uint8) DepartmentIndex;
		stItem.amount			= ItemAmount;
		stItem.currency			= CURRENCY_TL;
		stItem.count			= 0;
		stItem.unitType			= 0;
		stItem.pluPriceIndex	= 0;
		stItem.countPrecition	= 0;
		sprintf(stItem.name, "PRODUCT %d", ItemIndex);

		RetCode = CallFP3_ItemSale(Lib, InterfaceHandle, TransactionHandle, &stItem, &stTicket, TIMEOUT_DEFAULT);
		if (RetCode != 0)
			return RetCode;

		DumpTickt(&stTicket);

		Amount += ItemAmount;
		printf("Total Amount = %d\n", Amount);
	}

	while (Amount > 0)
	{
		printf("1 - Bank Payment:\n");
		printf("2 - Cash Payment:\n");
		Result = scanf("%d", &Type);

		if ((Type != 1) && (Type != 2))
		{
			printf("Payment Type Error %d\n", Result);
			continue;
		}

		printf("Enter Payment Amount: (Remain Amount = %d)", Amount);
		Result = scanf("%d", &PaymentAmount);

		if ((PaymentAmount > Amount) || (PaymentAmount == 0))
		{
			printf("Payment Amount Error %d\n", Result);
			continue;
		}

		memset(&stPaymentRequest, 0x00, sizeof(stPaymentRequest));
		stPaymentRequest.StructSize = sizeof(stPaymentRequest);

		switch (Type)
		{
		case 1:
			stPaymentRequest.typeOfPayment			= PAYMENT_BANK_CARD;
			stPaymentRequest.subtypeOfPayment		= 0;
			stPaymentRequest.payAmount				= PaymentAmount;
			stPaymentRequest.payAmountCurrencyCode	= CURRENCY_TL;
			stPaymentRequest.bankBkmId				= 0;
			stPaymentRequest.numberOfinstallments	= 0;
			break;

		case 2:
			stPaymentRequest.typeOfPayment			= PAYMENT_CASH_TL;
			stPaymentRequest.subtypeOfPayment		= 0;
			stPaymentRequest.payAmount				= PaymentAmount;
			stPaymentRequest.payAmountCurrencyCode	= CURRENCY_TL;
			stPaymentRequest.bankBkmId				= 0;
			stPaymentRequest.numberOfinstallments	= 0;
			break;
		}

		RetCode = CallFP3_Payment(Lib, InterfaceHandle, TransactionHandle, &stPaymentRequest, &stTicket, TIMEOUT_CARD_TRANSACTIONS);
		if (RetCode != 0)
			return RetCode;

		Amount -= PaymentAmount;

		DumpTickt(&stTicket);
	}

	RetCode = CallFP3_PrintBeforeMF(Lib, InterfaceHandle, TransactionHandle, TIMEOUT_DEFAULT);
	if (RetCode != 0)
		return RetCode;

	RetCode = CallFP3_PrintTMF(Lib, InterfaceHandle, TransactionHandle, TIMEOUT_PRINT_MF);
	if (RetCode != 0)
		return RetCode;

	RetCode = CallFP3_Close(Lib, InterfaceHandle, TransactionHandle, TIMEOUT_DEFAULT);
	if (RetCode != 0)
		return RetCode;

	return RetCode;
}

int main()
{
	int RetCode;
	void * lib;
	char LibPtr[256];
	char *Ptr;

	printf("Loading library...\n");

	Ptr = getcwd(LibPtr, sizeof(LibPtr));
	if (Ptr == NULL)
		LibPtr[0] = 0;
	strcat(LibPtr, "/GMPSmartDLL.so");

	printf("DLL Path = %s\n", LibPtr);

	printf("Loading:'%s'\n", LibPtr);
	lib = dlopen(LibPtr, RTLD_LAZY);

	if (!lib)
	{
		printf("Library can't loaded.\n");
		printf("dlError = %s\n", dlerror());
		return -1;
	}

	printf("Library successfully loaded.\n");

	//SetXmlFilePath is must be first called function.
	RetCode = SetXmlPath(lib);

	GetDllVersion(lib);

	if (RetCode == 0)
		RetCode = DoSale(lib);

	printf("Freeing library...\n");
	dlclose(lib);

	printf("Test finished.\n");

	return RetCode;
}

