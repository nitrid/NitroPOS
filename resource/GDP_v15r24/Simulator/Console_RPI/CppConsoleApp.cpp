
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "IngGMPSmartDLL.h"


CIngGMPSmartDLL g_IngGMPSmartDLL;

char g_ErrorBuf[256];

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

int GetInterfaceHandle(HINT *pInterfaceHandle)
{
	HINT InterfaceList[20];
	uint8 ID[64];
	HINT InterfaceCount = 0;
	int i = 0;
	int HandleIndex;

	memset(InterfaceList, 0, 20 * sizeof(HINT));
	memset(ID, 0, 64);

	InterfaceCount = g_IngGMPSmartDLL.FP3_GetInterfaceHandleList(InterfaceList, 64);

	printf("'FP3_GetInterfaceHandleList' InterfaceCount = %d \n", InterfaceCount);


	printf("Interface Secimi (0 - %d): \n", InterfaceCount);

	for (i = 0; i < (int)InterfaceCount; i++)
		printf("%d - Interface [%d] : %d\n", i, i, InterfaceList[i]);

	scanf("%d", &HandleIndex);

	*pInterfaceHandle = InterfaceList[HandleIndex];

	if (InterfaceCount > 0)
		return 0;

	return -1;
}

int DoSale(void)
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
	HTRX TransactionHandle = 0;
	HINT InterfaceHandle = 0;

	memset(UniqueId, 0x00, sizeof(UniqueId));

	RetCode = GetInterfaceHandle(&InterfaceHandle);
	if (RetCode != 0)
		return RetCode;

	if (RetCode == 0)
	{
		ST_ECHO stEcho;

		memset(&stEcho, 0x00, sizeof(stEcho));
		stEcho.StructSize = sizeof(stEcho);

		RetCode = g_IngGMPSmartDLL.FP3_Echo(InterfaceHandle, &stEcho, TIMEOUT_ECHO);

		printf("'FP3_Echo' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));
	}

	if (RetCode != 0)
		return RetCode;

	ST_GMP_PAIR 		stGMPPair;
	ST_GMP_PAIR_RESP	stGMPPairResp;

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

	RetCode = g_IngGMPSmartDLL.FP3_GMP_StartPairingInit(InterfaceHandle, &stGMPPair, &stGMPPairResp);

	printf("'GMP_StartPairingInit' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));

	if (RetCode != 0)
		return RetCode;

	RetCode = g_IngGMPSmartDLL.FP3_Start(InterfaceHandle, &TransactionHandle, 0, UniqueId, sizeof(UniqueId), NULL, 0, NULL, 0, TIMEOUT_DEFAULT);
	printf("'FP3_Start' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));
	if (RetCode != 0)
		return RetCode;

	RetCode = g_IngGMPSmartDLL.FP3_OptionFlags(InterfaceHandle, TransactionHandle, &ActiveFlags, GMP3_OPTION_ECHO_PRINTER | GMP3_OPTION_ECHO_ITEM_DETAILS | GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0, TIMEOUT_DEFAULT);
	printf("'FP3_OptionFlags' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));
	if (RetCode != 0)
		return RetCode;

	RetCode = g_IngGMPSmartDLL.FP3_TicketHeader(InterfaceHandle, TransactionHandle, TProcessSale, TIMEOUT_DEFAULT);
	printf("'FP3_TicketHeader' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));
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

		GetInterfaceHandle(&InterfaceHandle);

		RetCode = g_IngGMPSmartDLL.FP3_ItemSale(InterfaceHandle, TransactionHandle, &stItem, &stTicket, TIMEOUT_DEFAULT);
		printf("'FP3_ItemSale' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));
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

		RetCode = g_IngGMPSmartDLL.FP3_Payment(InterfaceHandle, TransactionHandle, &stPaymentRequest, &stTicket, TIMEOUT_CARD_TRANSACTIONS);
		printf("'FP3_Payment' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));
		if (RetCode != 0)
			return RetCode;

		Amount -= PaymentAmount;

		DumpTickt(&stTicket);
	}

	RetCode = g_IngGMPSmartDLL.FP3_PrintBeforeMF(InterfaceHandle, TransactionHandle, TIMEOUT_DEFAULT);
	printf("'FP3_PrintBeforeMF' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));
	if (RetCode != 0)
		return RetCode;

	RetCode = g_IngGMPSmartDLL.FP3_PrintMF(InterfaceHandle, TransactionHandle, TIMEOUT_PRINT_MF);
	printf("'FP3_PrintTMF' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));
	if (RetCode != 0)
		return RetCode;

	RetCode = g_IngGMPSmartDLL.FP3_Close(InterfaceHandle, TransactionHandle, TIMEOUT_DEFAULT);
	printf("'FP3_Close' return code = %d (0x%X) : %s\n", RetCode, RetCode, g_IngGMPSmartDLL.GetErrorMessage(RetCode, g_ErrorBuf));
	if (RetCode != 0)
		return RetCode;

	return RetCode;
}

int main()
{
	int RetCode;
	char Buf[1024];
	char DllVersion[24];
	char *Ptr = NULL;
	char BufferPath[4096];

	printf("Loading library...\n");

	memset(Buf, 0x00, sizeof(Buf));
	Ptr = getcwd(Buf, sizeof(Buf));
	if (Ptr == NULL)
		Buf[0] = 0;
	strcat(Buf, "/GMPSmartDLL.so");

	printf("DLL Path = %s\n", Buf);

	RetCode = g_IngGMPSmartDLL.LoadFunctions(Buf);
	if (RetCode != 0)
	{
		printf("Library can't loaded : %d\n", RetCode);
		return -1;
	}

	printf("Library successfully loaded.\n");

	memset(Buf, 0x00, sizeof(Buf));
	Ptr = getcwd(Buf, sizeof(Buf));
	if (Ptr == NULL)
		Buf[0] = 0;
	strcat(Buf, "/");

	printf("XML Path = %s\n", Buf);

	//SetXmlPath is must be first called function.
	RetCode = g_IngGMPSmartDLL.SetXmlFilePath(Buf);

	printf("Set Xml Path Set : Ret Code : %d\n", RetCode);

	memset(DllVersion, 0x00, sizeof(DllVersion));

	RetCode = g_IngGMPSmartDLL.GMP_GetDllVersion(DllVersion);

	if (RetCode == 0)
		printf("DllVersion = %s\n", DllVersion);

	if (RetCode == 0)
	{
		while (1)
		{
			printf("Devam etmek için 0 a basın...\n");
			scanf("%d", &RetCode);
			if (RetCode == 0)
				RetCode = DoSale();
			else
				break;
		}
	}
	printf("GMP.INI path = %s\n", g_IngGMPSmartDLL.GetIniFilePath(BufferPath));

	printf("Test finished.\n");

	return RetCode;
}

