
#ifndef __C_ING_GMP_SMART_DLL_H__
#define __C_ING_GMP_SMART_DLL_H__

#include "GMPSmartDLL.h"


class CIngGMPSmartDLL
{
public:
	CIngGMPSmartDLL();
	~CIngGMPSmartDLL();

	int LoadFunctions(const char *LibName);

	int SetXmlFilePath(const char * path)
	{
		if (m_Pointers.SetXmlFilePath != NULL)
			return m_Pointers.SetXmlFilePath(path);

		return -1;
	}

	uint16 gmpReadTLVlen(uint16* plen, uint8* ptr)
	{
		if (m_Pointers.gmpReadTLVlen != NULL)
			return m_Pointers.gmpReadTLVlen(plen, ptr);
		return -1;
	}

	uint16 gmpReadTLVtag(uint32* ptag, uint8* ptr)
	{
		if (m_Pointers.gmpReadTLVtag != NULL)
			return  m_Pointers.gmpReadTLVtag(ptag, ptr);
		return -1;
	}

	uint16 gmpTlvSetLen(uint8* pmsg, uint16 TlvLen)
	{
		if (m_Pointers.gmpTlvSetLen != NULL)
			return  gmpTlvSetLen(pmsg, TlvLen);
		return -1;
	}

	uint16 gmpSetTLV(uint8* pmsg, uint32 Tag, uint8* pdata, uint16 dataLen)
	{
		if (m_Pointers.gmpSetTLV != NULL)
			return  gmpSetTLV(pmsg, Tag, pdata, dataLen);
		return -1;
	}

	uint16 gmpSetTLVbcd(uint8* pmsg, uint32 Tag, uint32 data, uint16 bcdLen)
	{
		if (m_Pointers.gmpSetTLVbcd != NULL)
			return m_Pointers.gmpSetTLVbcd(pmsg, Tag, data, bcdLen);
		return -1;
	}

	uint16 gmpSetTLVbcd_64(uint8* pmsg, uint32 Tag, uint64 data, uint16 bcdLen)
	{
		if (m_Pointers.gmpSetTLVbcd_64 != NULL)
			return m_Pointers.gmpSetTLVbcd_64(pmsg, Tag, data, bcdLen);
		return -1;
	}

	int gmpSearchTLV(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint8* pdata, uint16 dataMaxLe)
	{
		if (m_Pointers.gmpSearchTLV != NULL)
			return m_Pointers.gmpSearchTLV(Tag, ocurience, recvbuffer, recvbufferLen, pdata, dataMaxLe);
		return -1;
	}

	int gmpSearchTLVbcd_8(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint8 *pdata, uint8 bcdLen)
	{
		if (m_Pointers.gmpSearchTLVbcd_8 != NULL)
			return m_Pointers.gmpSearchTLVbcd_8(Tag, ocurience, recvbuffer, recvbufferLen, pdata, bcdLen);
		return -1;
	}
	int gmpSearchTLVbcd_16(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint16 *pdata, uint8 bcdLen)
	{
		if (m_Pointers.gmpSearchTLVbcd_16 != NULL)
			return m_Pointers.gmpSearchTLVbcd_16(Tag, ocurience, recvbuffer, recvbufferLen, pdata, bcdLen);
		return -1;
	}

	int gmpSearchTLVbcd_32(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint32 *pdata, uint8 bcdLen)
	{
		if (m_Pointers.gmpSearchTLVbcd_32 != NULL)
			return m_Pointers.gmpSearchTLVbcd_32(Tag, ocurience, recvbuffer, recvbufferLen, pdata, bcdLen);
		return -1;
	}

	int gmpSearchTLVbcd_64(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint64 *pdata, uint8 bcdLen)
	{
		if (m_Pointers.gmpSearchTLVbcd_64 != NULL)
			return m_Pointers.gmpSearchTLVbcd_64(Tag, ocurience, recvbuffer, recvbufferLen, pdata, bcdLen);
		return -1;
	}

	uint16 gmpSetTLV_HL(uint8* pmsg, uint32 pmsgLen, uint32 Tag, uint8* pdata, uint16 dataLen)
	{
		if (m_Pointers.gmpSetTLV_HL != NULL)
			return m_Pointers.gmpSetTLV_HL(pmsg, pmsgLen, Tag, pdata, dataLen);
		return -1;
	}

	uint16 gmpReadTLVtag_HL(uint32* ptag, uint8* ptr, uint32 startIndex)
	{
		if (m_Pointers.gmpReadTLVtag_HL != NULL)
			return m_Pointers.gmpReadTLVtag_HL(ptag, ptr, startIndex);
		return -1;
	}

	uint16 gmpReadTLVlen_HL(uint16* plen, uint8* ptr, uint32 startIndex)
	{
		if (m_Pointers.gmpReadTLVlen_HL != NULL)
			return m_Pointers.gmpReadTLVlen_HL(plen, ptr, startIndex);
		return -1;
	}

	uint32 FP3_FileSystem_FileRead(HINT hInt, char* FileName, uint32 offset, uint32 whence, uint8* buffer, uint16 maxLen, uint16* pReadLen)
	{
		if (m_Pointers.FP3_FileSystem_FileRead != NULL)
			return m_Pointers.FP3_FileSystem_FileRead(hInt, FileName, offset, whence, buffer, maxLen, pReadLen);
		return -1;
	}

	uint32 FP3_FileSystem_FileRemove(HINT hInt, char* FileName)
	{
		if (m_Pointers.FP3_FileSystem_FileRemove != NULL)
			return m_Pointers.FP3_FileSystem_FileRemove(hInt, FileName);
		return -1;
	}

	uint32 FP3_FileSystem_FileRename(HINT hInt, char* FileNameOld, char* FileNameNew)
	{
		if (m_Pointers.FP3_FileSystem_FileRename != NULL)
			return m_Pointers.FP3_FileSystem_FileRename(hInt, FileNameOld, FileNameNew);
		return -1;
	}

	uint32 FP3_FileSystem_FileWrite(HINT hInt, char* FileName, uint32 offset, uint32 whence, uint8* buffer, uint16 len)
	{
		if (m_Pointers.FP3_FileSystem_FileWrite != NULL)
			return m_Pointers.FP3_FileSystem_FileWrite(hInt, FileName, offset, whence, buffer, len);
		return -1;
	}

	uint32 FP3_FileSystem_DirChange(HINT hInt, char* DirName)
	{
		if (m_Pointers.FP3_FileSystem_DirChange != NULL)
			return m_Pointers.FP3_FileSystem_DirChange(hInt, DirName);
		return -1;
	}

	uint32 FP3_FileSystem_DirListFiles(HINT hInt, char* DirName, ST_FILE stFile[], uint16 maxNumberOfFiles, uint16* pNumberOfFiles)
	{
		if (m_Pointers.FP3_FileSystem_DirListFiles != NULL)
			return m_Pointers.FP3_FileSystem_DirListFiles(hInt, DirName, stFile, maxNumberOfFiles, pNumberOfFiles);
		return -1;
	}

	uint32 FP3_Database_GetHandle(HINT hInt)
	{
		if (m_Pointers.FP3_Database_GetHandle != NULL)
			return m_Pointers.FP3_Database_GetHandle(hInt);
		return -1;
	}

	uint32 FP3_Database_FreeStructure(HINT hInt, ST_DATABASE_RESULT *pst)
	{
		if (m_Pointers.FP3_Database_FreeStructure != NULL)
			return m_Pointers.FP3_Database_FreeStructure(hInt, pst);
		return -1;
	}

	uint32 FP3_Database_Open(HINT hInt, char* name)
	{
		if (m_Pointers.FP3_Database_Open != NULL)
			return m_Pointers.FP3_Database_Open(hInt, name);
		return -1;
	}

	uint32 FP3_Database_Close(HINT hInt)
	{
		if (m_Pointers.FP3_Database_Close != NULL)
			return m_Pointers.FP3_Database_Close(hInt);
		return -1;
	}

	uint32 FP3_Database_Execute(HINT hInt, char* sqlWord, ST_DATABASE_RESULT* pstDatabaseResult)
	{
		if (m_Pointers.FP3_Database_Execute != NULL)
			return m_Pointers.FP3_Database_Execute(hInt, sqlWord, pstDatabaseResult);
		return -1;
	}

	uint32 FP3_Database_Query(HINT hInt, char* sqlWord, uint16* pnumberOfColomns)
	{
		if (m_Pointers.FP3_Database_Query != NULL)
			return m_Pointers.FP3_Database_Query(hInt, sqlWord, pnumberOfColomns);
		return -1;
	}

	uint32 FP3_Database_QueryReadLine(HINT hInt, uint16 numberOfLinesRequested, uint16 numberOfColomnsRequested, ST_DATABASE_RESULT* pstDatabaseResult)
	{
		if (m_Pointers.FP3_Database_QueryReadLine != NULL)
			return m_Pointers.FP3_Database_QueryReadLine(hInt, numberOfLinesRequested, numberOfColomnsRequested, pstDatabaseResult);
		return -1;
	}

	uint32 FP3_Database_QueryColomnCaptions(HINT hInt, ST_DATABASE_RESULT* pstDatabaseResult)
	{
		if (m_Pointers.FP3_Database_QueryColomnCaptions != NULL)
			return m_Pointers.FP3_Database_QueryColomnCaptions(hInt, pstDatabaseResult);
		return -1;
	}

	uint32 FP3_Database_QueryReset(HINT hInt)
	{
		if (m_Pointers.FP3_Database_QueryReset != NULL)
			return m_Pointers.FP3_Database_QueryReset(hInt);
		return -1;
	}

	uint32 FP3_Database_QueryFinish(HINT hInt)
	{
		if (m_Pointers.FP3_Database_QueryFinish != NULL)
			return m_Pointers.FP3_Database_QueryFinish(hInt);
		return -1;
	}

	uint32 GMP_GetDllVersion(char* version)
	{
		if (m_Pointers.GMP_GetDllVersion != NULL)
			return m_Pointers.GMP_GetDllVersion(version);
		return -1;
	}

	char *GetXmlFilePath(char* path)
	{
		if (m_Pointers.GetXmlFilePath != NULL)
			return m_Pointers.GetXmlFilePath(path);
		return path;
	}

	uint32 FP3_GMP_StartPairingInit(HINT hInt, ST_GMP_PAIR *pGMPPair, ST_GMP_PAIR_RESP *pGMPPairResp)
	{
		if (m_Pointers.FP3_GMP_StartPairingInit != NULL)
			return m_Pointers.FP3_GMP_StartPairingInit(hInt, pGMPPair, pGMPPairResp);
		return -1;
	}

	void FP3_ResetHandle(HINT hInt)
	{
		if (m_Pointers.FP3_ResetHandle != NULL)
			m_Pointers.FP3_ResetHandle(hInt);
	}

	uint32 FP3_Start(HINT hInt, HTRX *phTrx, uint8 IsBackground, uint8* uniqueId, int lengthOfUniqueId, uint8* uniqueIdSign, int lengthOfUniqueIdSign, uint8* userData, int lengthOfUserData, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Start != NULL)
			return m_Pointers.FP3_Start(hInt, phTrx, IsBackground, uniqueId, lengthOfUniqueId, uniqueIdSign, lengthOfUniqueIdSign, userData, lengthOfUserData, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Close(HINT hInt, HTRX hTrx, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Close != NULL)
			return m_Pointers.FP3_Close(hInt, hTrx, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Ping(HINT hInt, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Ping != NULL)
			return m_Pointers.FP3_Ping(hInt, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Echo(HINT hInt, ST_ECHO *pstEcho, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Echo != NULL)
			return m_Pointers.FP3_Echo(hInt, pstEcho, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_PrintTotalsAndPayments(HINT hInt, HTRX hTrx, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_PrintTotalsAndPayments != NULL)
			return m_Pointers.FP3_PrintTotalsAndPayments(hInt, hTrx, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_PrintBeforeMF(HINT hInt, HTRX hTrx, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_PrintBeforeMF != NULL)
			return m_Pointers.FP3_PrintBeforeMF(hInt, hTrx, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_PrintMF(HINT hInt, HTRX hTrx, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_PrintMF != NULL)
			return m_Pointers.FP3_PrintMF(hInt, hTrx, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_PrintUserMessage(HINT hInt, HTRX hTrx, ST_USER_MESSAGE stUserMessage[], uint16 numberOfMessage, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_PrintUserMessage != NULL)
			return m_Pointers.FP3_PrintUserMessage(hInt, hTrx, stUserMessage, numberOfMessage, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetTicket(HINT hInt, HTRX hTrx, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetTicket != NULL)
			return m_Pointers.FP3_GetTicket(hInt, hTrx, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetPLU(HINT hInt, HTRX hTrx, char* barcode, ST_PLU_RECORD* pstPluRecord, ST_PLU_GROUP_RECORD stPluGroupRecord[], int maxNumberOfGroupRecords, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetPLU != NULL)
			return m_Pointers.FP3_GetPLU(hInt, hTrx, barcode, pstPluRecord, stPluGroupRecord, maxNumberOfGroupRecords, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Payment(HINT hInt, HTRX hTrx, ST_PAYMENT_REQUEST* pstPaymentRequest, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Payment != NULL)
			return m_Pointers.FP3_Payment(hInt, hTrx, pstPaymentRequest, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_ReversePayment(HINT hInt, HTRX hTrx, ST_PAYMENT_REQUEST stPaymentRequest[], uint16 numberOfPaymentRequests, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_ReversePayment != NULL)
			return m_Pointers.FP3_ReversePayment(hInt, hTrx, stPaymentRequest, numberOfPaymentRequests, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_TicketHeader(HINT hInt, HTRX hTrx, TTicketType ticketType, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_TicketHeader != NULL)
			return m_Pointers.FP3_TicketHeader(hInt, hTrx, ticketType, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_SetInvoice(HINT hInt, HTRX hTrx, ST_INVIOCE_INFO* pstInvoiceInfo, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_SetInvoice != NULL)
			return m_Pointers.FP3_SetInvoice(hInt, hTrx, pstInvoiceInfo, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_SetParkingTicket(HINT hInt, HTRX hTrx, char* carIdentification, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_SetParkingTicket != NULL)
			return m_Pointers.FP3_SetParkingTicket(hInt, hTrx, carIdentification, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_ItemSale(HINT hInt, HTRX hTrx, ST_ITEM* pstItem, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_ItemSale != NULL)
			return m_Pointers.FP3_ItemSale(hInt, hTrx, pstItem, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Matrahsiz(HINT hInt, HTRX hTrx, char* tck, uint16 subtypeOfTaxException, long matrahsizAmount, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Matrahsiz != NULL)
			return m_Pointers.FP3_Matrahsiz(hInt, hTrx, tck, subtypeOfTaxException, matrahsizAmount, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_KasaAvans(HINT hInt, HTRX hTrx, long amount, ST_TICKET* pStTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_KasaAvans != NULL)
			return m_Pointers.FP3_KasaAvans(hInt, hTrx, amount, pStTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_CustomerAvans(HINT hInt, HTRX hTrx, long amount, ST_TICKET* pStTicket, char* pCustomerName, char* pTckn, char* pVkn, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_CustomerAvans != NULL)
			return m_Pointers.FP3_CustomerAvans(hInt, hTrx, amount, pStTicket, pCustomerName, pTckn, pVkn, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_KasaPayment(HINT hInt, HTRX hTrx, long amount, ST_TICKET* pStTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_KasaPayment != NULL)
			return m_Pointers.FP3_KasaPayment(hInt, hTrx, amount, pStTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Pretotal(HINT hInt, HTRX hTrx, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Pretotal != NULL)
			return m_Pointers.FP3_Pretotal(hInt, hTrx, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_DisplayPaymentSummary(HINT hInt, HTRX hTrx, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_DisplayPaymentSummary != NULL)
			return m_Pointers.FP3_DisplayPaymentSummary(hInt, hTrx, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Plus(HINT hInt, HTRX hTrx, long Amount, char *szText, ST_TICKET* pstTicket, uint16 indexOfItem, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Plus != NULL)
			return m_Pointers.FP3_Plus(hInt, hTrx, Amount, szText, pstTicket, indexOfItem, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Minus(HINT hInt, HTRX hTrx, long Amount, char *szText, ST_TICKET* pstTicket, uint16 indexOfItem, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Minus != NULL)
			return m_Pointers.FP3_Minus(hInt, hTrx, Amount, szText, pstTicket, indexOfItem, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Inc(HINT hInt, HTRX hTrx, uint8 Rate, char *szText, ST_TICKET* pstTicket, uint16 indexOfItem, uint32* pchangedAmount, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Inc != NULL)
			return m_Pointers.FP3_Inc(hInt, hTrx, Rate, szText, pstTicket, indexOfItem, pchangedAmount, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_Dec(HINT hInt, HTRX hTrx, uint8 Rate, char *szText, ST_TICKET* pstTicket, uint16 indexOfItem, uint32* pchangedAmount, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_Dec != NULL)
			return m_Pointers.FP3_Dec(hInt, hTrx, Rate, szText, pstTicket, indexOfItem, pchangedAmount, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_VoidPayment(HINT hInt, HTRX hTrx, uint16 index, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_VoidPayment != NULL)
			return m_Pointers.FP3_VoidPayment(hInt, hTrx, index, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_VoidAll(HINT hInt, HTRX hTrx, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_VoidAll != NULL)
			return m_Pointers.FP3_VoidAll(hInt, hTrx, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_VoidItem(HINT hInt, HTRX hTrx, uint16 index, uint64 ItemCount, uint8 ItemCountPrecision, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_VoidItem != NULL)
			return m_Pointers.FP3_VoidItem(hInt, hTrx, index, ItemCount, ItemCountPrecision, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_SetTaxFreeRefundAmount(HINT hInt, HTRX hTrx, uint32 refundAmount, uint16 refundAmountCurrency, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_SetTaxFreeRefundAmount != NULL)
			return m_Pointers.FP3_SetTaxFreeRefundAmount(hInt, hTrx, refundAmount, refundAmountCurrency, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_SetTaxFree(HINT hInt, HTRX hTrx, uint32 flag, char* name, char* surname, char* identificationNo, char* city, char* country, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_SetTaxFree != NULL)
			return m_Pointers.FP3_SetTaxFree(hInt, hTrx, flag, name, surname, identificationNo, city, country, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_MultipleCommand(HINT hInt, HTRX hTrx, ST_MULTIPLE_RETURN_CODE* returnCodes, uint16* pnumberOfReturnCodes, uint8* sendBuffer, uint16 sendBufferLen, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_MultipleCommand != NULL)
			return m_Pointers.FP3_MultipleCommand(hInt, hTrx, returnCodes, pnumberOfReturnCodes, sendBuffer, sendBufferLen, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionGetUniqueIdList(HINT hInt, HTRX hTrx, ST_UNIQUE_ID stUniqueIdList[] , uint16 maxNumberOfitems, uint16 indexOfitemsToStart, uint16* ptotalNumberOfItems, uint16* pNumberOfItemsInThis,  int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionGetUniqueIdList != NULL)
			return m_Pointers.FP3_FunctionGetUniqueIdList(hInt, hTrx, stUniqueIdList, maxNumberOfitems, indexOfitemsToStart, ptotalNumberOfItems, pNumberOfItemsInThis, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetTlvData(HINT hInt, uint32 tag, uint8* pData, uint16 maxBufferLen, uint16* pDataLen)
	{
		if (m_Pointers.FP3_GetTlvData != NULL)
			return m_Pointers.FP3_GetTlvData(hInt, tag, pData, maxBufferLen, pDataLen);
		return -1;
	}

	uint32 FP3_GetCashierTable(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_CASHIER pstCashier[], uint8 numberOfRecordsRequested, uint16* pactiveCashier)
	{
		if (m_Pointers.FP3_GetCashierTable != NULL)
			return m_Pointers.FP3_GetCashierTable(hInt, pnumberOfTotalRecords, pnumberOfTotalRecordsReceived, pstCashier, numberOfRecordsRequested, pactiveCashier);
		return -1;
	}

	uint32 FP3_GetExchangeTable(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_EXCHANGE pstExchange[], uint8 numberOfRecordsRequested)
	{
		if (m_Pointers.FP3_GetExchangeTable != NULL)
			return m_Pointers.FP3_GetExchangeTable(hInt, pnumberOfTotalRecords, pnumberOfTotalRecordsReceived, pstExchange, numberOfRecordsRequested);
		return -1;
	}

	uint32 FP3_GetTaxRates(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_TAX_RATE pstTaxRate[], uint8 numberOfRecordsRequested)
	{
		if (m_Pointers.FP3_GetTaxRates != NULL)
			return m_Pointers.FP3_GetTaxRates(hInt, pnumberOfTotalRecords, pnumberOfTotalRecordsReceived, pstTaxRate, numberOfRecordsRequested);
		return -1;
	}

	uint32 FP3_GetDepartments(HINT hInt, uint8* pnumberOfTotalDepartments, uint8* pnumberOfTotalDepartmentsReceived, ST_DEPARTMENT pstDepartments[], uint8 numberOfDepartmentRequested)
	{
		if (m_Pointers.FP3_GetDepartments != NULL)
			return m_Pointers.FP3_GetDepartments(hInt, pnumberOfTotalDepartments, pnumberOfTotalDepartmentsReceived, pstDepartments, numberOfDepartmentRequested);
		return -1;
	}

	uint32 FP3_GetPaymentApplicationInfo(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO pstExchange[], uint8 numberOfRecordsRequested)
	{
		if (m_Pointers.FP3_GetPaymentApplicationInfo != NULL)
			return m_Pointers.FP3_GetPaymentApplicationInfo(hInt, pnumberOfTotalRecords, pnumberOfTotalRecordsReceived, pstExchange, numberOfRecordsRequested);
		return -1;
	}

	uint32 FP3_GetVasApplicationInfo(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO pstPaymentApplicationInfo[], uint16 vasType)
	{
		if (m_Pointers.FP3_GetVasApplicationInfo != NULL)
			return m_Pointers.FP3_GetVasApplicationInfo(hInt, pnumberOfTotalRecords, pnumberOfTotalRecordsReceived, pstPaymentApplicationInfo, vasType);
		return -1;
	}

	uint32 FP3_GetCurrentFiscalCounters(HINT hInt, uint16* pZNo, uint16* pFNo, uint16* pEKUNo)
	{
		if (m_Pointers.FP3_GetCurrentFiscalCounters != NULL)
			return m_Pointers.FP3_GetCurrentFiscalCounters(hInt, pZNo, pFNo, pEKUNo);
		return -1;
	}

	uint32 FP3_GetPluDatabaseInfo(HINT hInt, char* PluDbName, uint16* pPluDbType, uint32* pPluDbSize, uint32* pPluDbGrupsLastModified, uint32* pPluDbItemsLastModified)
	{
		if (m_Pointers.FP3_GetPluDatabaseInfo != NULL)
			return m_Pointers.FP3_GetPluDatabaseInfo(hInt, PluDbName, pPluDbType, pPluDbSize, pPluDbGrupsLastModified, pPluDbItemsLastModified);
		return -1;
	}

	uint32 FP3_GetTicketHeader(HINT hInt, uint16 indexOfHeader, ST_TICKET_HEADER* pstTicketHeader, uint16* pNumberOfSpaceTotal, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetTicketHeader != NULL)
			return m_Pointers.FP3_GetTicketHeader(hInt, indexOfHeader, pstTicketHeader, pNumberOfSpaceTotal, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_SetPluDatabaseInfo(HINT hInt, char* PluDbName, uint16 PluDbType)
	{
		if (m_Pointers.FP3_SetPluDatabaseInfo != NULL)
			return m_Pointers.FP3_SetPluDatabaseInfo(hInt, PluDbName, PluDbType);
		return -1;
	}

	uint32 FP3_SetDepartments(HINT hInt, ST_DEPARTMENT pstDepartments[], uint8 numberOfDepartmentRequested, char* supervisorPassword)
	{
		if (m_Pointers.FP3_SetDepartments != NULL)
			return m_Pointers.FP3_SetDepartments(hInt, pstDepartments, numberOfDepartmentRequested, supervisorPassword);
		return -1;
	}

	uint32 FP3_SetuApplicationFunction(HINT hInt, uint8* uApplicationName, uint32 uApplicationId, uint8* functionName, uint32 functionId, uint32 functionVersion, uint32 functionFlags, uint8* commandBuffer, uint32 commandLen, char* supervisorPassword)
	{
		if (m_Pointers.FP3_SetuApplicationFunction != NULL)
			return m_Pointers.FP3_SetuApplicationFunction(hInt, uApplicationName, uApplicationId, functionName, functionId, functionVersion, functionFlags, commandBuffer, commandLen, supervisorPassword);
		return -1;
	}

	uint32 FP3_SetTlvData(HINT hInt, uint32 tag, uint8* pData, uint16 Len)
	{
		if (m_Pointers.FP3_SetTlvData != NULL)
			return m_Pointers.FP3_SetTlvData(hInt, tag, pData, Len);
		return -1;
	}

	uint32 FP3_GetDialogInput_MultipleCommand(HINT hInt, ST_MULTIPLE_RETURN_CODE* returnCodes, uint16* pnumberOfreturnCodes, uint8* sendBuffer, uint16 sendBufferLen, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetDialogInput_MultipleCommand != NULL)
			return m_Pointers.FP3_GetDialogInput_MultipleCommand(hInt, returnCodes, pnumberOfreturnCodes, sendBuffer, sendBufferLen, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetDialogInput_Text(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, char* mask, char* value, int maxLenOfValue, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetDialogInput_Text != NULL)
			return m_Pointers.FP3_GetDialogInput_Text(hInt, pGL_Dialog_retcode, tag_id, title, text, mask, value, maxLenOfValue, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetDialogInput_Date(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, char* mask, ST_DATE_TIME* value, int maxLenOfValue, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetDialogInput_Date != NULL)
			return m_Pointers.FP3_GetDialogInput_Date(hInt, pGL_Dialog_retcode, tag_id, title, text, mask, value, maxLenOfValue, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetDialogInput_Amount(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, char* mask, char* value, int maxLenOfValue, char* symbol, uint8 align, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetDialogInput_Amount != NULL)
			return m_Pointers.FP3_GetDialogInput_Amount(hInt, pGL_Dialog_retcode, tag_id, title, text, mask, value, maxLenOfValue, symbol, align, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetDialogInput_Menu(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, uint8 typeOfMenu, char* title, const char * const * menu, uint32* pvalue, uint8 buttons, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetDialogInput_Menu != NULL)
			return m_Pointers.FP3_GetDialogInput_Menu(hInt, pGL_Dialog_retcode, tag_id, typeOfMenu, title, menu, pvalue, buttons, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetDialogInput_MsgBox(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, uint8 icon, uint8 button, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetDialogInput_MsgBox != NULL)
			return m_Pointers.FP3_GetDialogInput_MsgBox(hInt, pGL_Dialog_retcode, tag_id, title, text, icon, button, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetDialogInput_Password(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, char* mask, char* value, int maxLenOfValue, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_GetDialogInput_Password != NULL)
			return m_Pointers.FP3_GetDialogInput_Password(hInt, pGL_Dialog_retcode, tag_id, title, text, mask, value, maxLenOfValue, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_GetDialogBarcode(HINT hInt, uint32* pGL_Dialog_retcode, int Count, uint8* Buffer, int timeOut)
	{
		if (m_Pointers.FP3_GetDialogBarcode != NULL)
			return m_Pointers.FP3_GetDialogBarcode(hInt, pGL_Dialog_retcode, Count, Buffer, timeOut);
		return -1;
	}

	uint32 FP3_FunctionReadZReport(HINT hInt, ST_FUNCTION_PARAMETERS *pstFunctionParameters, ST_Z_REPORT *pstZReport, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionReadZReport != NULL)
			return m_Pointers.FP3_FunctionReadZReport(hInt, pstFunctionParameters, pstZReport, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionReports(HINT hInt, uint32 functionFlags, ST_FUNCTION_PARAMETERS *pstFunctionParameters, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionReports != NULL)
			return m_Pointers.FP3_FunctionReports(hInt, functionFlags, pstFunctionParameters, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionEcrParameter(HINT hInt, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionEcrParameter != NULL)
			return m_Pointers.FP3_FunctionEcrParameter(hInt, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionBankingBatch(HINT hInt, uint16 bkmId, uint16* pnumberOfBankResponse, ST_MULTIPLE_BANK_RESPONSE* pMultipleBankResponse, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionBankingBatch != NULL)
			return m_Pointers.FP3_FunctionBankingBatch(hInt, bkmId, pnumberOfBankResponse, pMultipleBankResponse, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionBankingParameter(HINT hInt, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionBankingParameter != NULL)
			return m_Pointers.FP3_FunctionBankingParameter(hInt, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionCashierLogin(HINT hInt, uint16 cashierIndex, char* cashierPassword)
	{
		if (m_Pointers.FP3_FunctionCashierLogin != NULL)
			return m_Pointers.FP3_FunctionCashierLogin(hInt, cashierIndex, cashierPassword);
		return -1;
	}

	uint32 FP3_FunctionCashierLogout(HINT hInt)
	{
		if (m_Pointers.FP3_FunctionCashierLogout != NULL)
			return m_Pointers.FP3_FunctionCashierLogout(hInt);
		return -1;
	}

	uint32 FP3_FunctionOpenDrawer(HINT hInt)
	{
		if (m_Pointers.FP3_FunctionOpenDrawer != NULL)
			return m_Pointers.FP3_FunctionOpenDrawer(hInt);
		return -1;
	}

	uint32 FP3_FunctionChangeTicketHeader(HINT hInt, char* supervisorPassword, uint16* pNumberOfSpaceTotal, uint16* pNumberOfSpaceUsed, ST_TICKET_HEADER* pstTicketHeader, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionChangeTicketHeader != NULL)
			return m_Pointers.FP3_FunctionChangeTicketHeader(hInt, supervisorPassword, pNumberOfSpaceTotal, pNumberOfSpaceUsed, pstTicketHeader, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionBankingRefund(HINT hInt, ST_PAYMENT_REQUEST *pstReversePayment, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionBankingRefund != NULL)
			return m_Pointers.FP3_FunctionBankingRefund(hInt, pstReversePayment, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionEkuPing(HINT hInt, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionEkuPing != NULL)
			return m_Pointers.FP3_FunctionEkuPing(hInt, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionEkuReadInfo(HINT hInt, uint16 ekuAccessFunction, ST_EKU_MODULE_INFO *pstEkuModuleInfo, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionEkuReadInfo != NULL)
			return m_Pointers.FP3_FunctionEkuReadInfo(hInt, ekuAccessFunction, pstEkuModuleInfo, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionEkuReadHeader(HINT hInt, uint16 index, ST_EKU_HEADER *pstEkuHeader, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionEkuReadHeader != NULL)
			return m_Pointers.FP3_FunctionEkuReadHeader(hInt, index, pstEkuHeader, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionEkuReadData(HINT hInt, uint16* pEkuDataBufferReceivedLen, ST_EKU_APPINF *pstEKUAppInfo, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionEkuReadData != NULL)
			return m_Pointers.FP3_FunctionEkuReadData(hInt, pEkuDataBufferReceivedLen, pstEKUAppInfo, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionEkuSeek(HINT hInt, ST_EKU_APPINF *pstEKUAppInfo, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionEkuSeek != NULL)
			return m_Pointers.FP3_FunctionEkuSeek(hInt, pstEKUAppInfo, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_FunctionReadCard(HINT hInt, uint32 cardReaderTypes, ST_CARD_INFO *pstCardInfo, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_FunctionReadCard != NULL)
			return m_Pointers.FP3_FunctionReadCard(hInt, cardReaderTypes, pstCardInfo, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_OptionFlags(HINT hInt, HTRX hTrx, uint64* pflagsActive, uint64 flagsToBeSet,  uint64 flagsToBeClear, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_OptionFlags != NULL)
			return m_Pointers.FP3_OptionFlags(hInt, hTrx, pflagsActive, flagsToBeSet, flagsToBeClear, timeoutInMiliseconds);
		return -1;
	}

	uint32 FP3_JumpToECR(HINT hInt, HTRX hTrx, uint64 jumpFlags, ST_TICKET* pstTicket, int timeoutInMiliseconds)
	{
		if (m_Pointers.FP3_JumpToECR != NULL)
			return m_Pointers.FP3_JumpToECR(hInt, hTrx, jumpFlags, pstTicket, timeoutInMiliseconds);
		return -1;
	}

	int prepare_Text(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, char* value, int timeout)
	{
		if (m_Pointers.prepare_Text != NULL)
			return m_Pointers.prepare_Text(Buffer, MaxSize, tag_id, title, text, mask, value, timeout);
		return -1;
	}

	int prepare_Amount(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, char* value, int maxLenOfValue, char* symbol, uint8 align, int timeout)
	{
		if (m_Pointers.prepare_Amount != NULL)
			return m_Pointers.prepare_Amount(Buffer, MaxSize, tag_id, title, text, mask, value, maxLenOfValue, symbol, align, timeout);
		return -1;
	}

	int prepare_Menu(uint8* Buffer, int MaxSize, uint32 tag_id, uint8 typeOfMenu, char* title, const char * const * menu, uint32* pvalue, uint8 buttons, int timeout)
	{
		if (m_Pointers.prepare_Menu != NULL)
			return m_Pointers.prepare_Menu(Buffer, MaxSize, tag_id, typeOfMenu, title, menu, pvalue, buttons, timeout);
		return -1;
	}

	int prepare_Date(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, ST_DATE_TIME* value, int timeout)
	{
		if (m_Pointers.prepare_Date != NULL)
			return m_Pointers.prepare_Date(Buffer, MaxSize, tag_id, title, text, mask, value, timeout);
		return -1;
	}

	int prepare_Password(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, char* value, uint16 maxLenOfValue, int timeout)
	{
		if (m_Pointers.prepare_Password != NULL)
			return m_Pointers.prepare_Password(Buffer, MaxSize, tag_id, title, text, mask, value, maxLenOfValue, timeout);
		return -1;
	}

	int prepare_MsgBox(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, uint8 icon, uint8 button, int timeout)
	{
		if (m_Pointers.prepare_MsgBox != NULL)
			return m_Pointers.prepare_MsgBox(Buffer, MaxSize, tag_id, title, text, icon, button, timeout);
		return -1;
	}

	int prepare_JumpToECR(uint8* Buffer, int MaxSize, uint64 jumpFlags)
	{
		if (m_Pointers.prepare_JumpToECR != NULL)
			return m_Pointers.prepare_JumpToECR(Buffer, MaxSize, jumpFlags);
		return -1;
	}

	int prepare_Condition(uint8* Buffer, int MaxSize, ST_CONDITIONAL_IF *pstCondition)
	{
		if (m_Pointers.prepare_Condition != NULL)
			return m_Pointers.prepare_Condition(Buffer, MaxSize, pstCondition);
		return -1;
	}

	int prepare_OptionFlags(uint8* Buffer, int MaxSize, uint64 flagsToBeSet,  uint64 flagsToBeClear)
	{
		if (m_Pointers.prepare_OptionFlags != NULL)
			return m_Pointers.prepare_OptionFlags(Buffer, MaxSize, flagsToBeSet, flagsToBeClear);
		return -1;
	}

	int prepare_Start(uint8* Buffer, int MaxSize, uint8* uniqueId, int lengthOfUniqueId, uint8* uniqueIdSign, int lengthOfUniqueIdSign, uint8* userData, int lengthOfUserData)
	{
		if (m_Pointers.prepare_Start != NULL)
			return m_Pointers.prepare_Start(Buffer, MaxSize, uniqueId, lengthOfUniqueId, uniqueIdSign, lengthOfUniqueIdSign, userData, lengthOfUserData);
		return -1;
	}

	int prepare_Close(uint8* Buffer, int MaxSize)
	{
		if (m_Pointers.prepare_Close != NULL)
			return m_Pointers.prepare_Close(Buffer, MaxSize);
		return -1;
	}

	int prepare_TicketHeader(uint8* Buffer, int MaxSize, TTicketType ticketType)
	{
		if (m_Pointers.prepare_TicketHeader != NULL)
			return m_Pointers.prepare_TicketHeader(Buffer, MaxSize, ticketType);
		return -1;
	}

	int prepare_ItemSale(uint8* Buffer, int MaxSize, ST_ITEM* pstItem)
	{
		if (m_Pointers.prepare_ItemSale != NULL)
			return m_Pointers.prepare_ItemSale(Buffer, MaxSize, pstItem);
		return -1;
	}

	int prepare_SetInvoice(uint8* Buffer, int MaxSize, ST_INVIOCE_INFO* pstInvoiceInfo)
	{
		if (m_Pointers.prepare_SetInvoice != NULL)
			return m_Pointers.prepare_SetInvoice(Buffer, MaxSize, pstInvoiceInfo);
		return -1;
	}

	int prepare_SetParkingTicket(uint8* Buffer, int MaxSize, char* carIdentification)
	{
		if (m_Pointers.prepare_SetParkingTicket != NULL)
			return m_Pointers.prepare_SetParkingTicket(Buffer, MaxSize, carIdentification);
		return -1;
	}

	int prepare_Payment(uint8* Buffer, int MaxSize, ST_PAYMENT_REQUEST* stPaymentRequest)
	{
		if (m_Pointers.prepare_Payment != NULL)
			return m_Pointers.prepare_Payment(Buffer, MaxSize, stPaymentRequest);
		return -1;
	}

	int prepare_ReversePayment(uint8* Buffer, int MaxSize, ST_PAYMENT_REQUEST stPaymentRequest[], uint16 numberOfPaymentRequests)
	{
		if (m_Pointers.prepare_ReversePayment != NULL)
			return m_Pointers.prepare_ReversePayment(Buffer, MaxSize, stPaymentRequest, numberOfPaymentRequests);
		return -1;
	}

	int prepare_PrintUserMessage(uint8* Buffer, int MaxSize, ST_USER_MESSAGE stUserMessage[], uint16 numberOfMessage)
	{
		if (m_Pointers.prepare_PrintUserMessage != NULL)
			return m_Pointers.prepare_PrintUserMessage(Buffer, MaxSize, stUserMessage, numberOfMessage);
		return -1;
	}

	int prepare_PrintTotalsAndPayments(uint8* Buffer, int MaxSize)
	{
		if (m_Pointers.prepare_PrintTotalsAndPayments != NULL)
			return m_Pointers.prepare_PrintTotalsAndPayments(Buffer, MaxSize);
		return -1;
	}

	int prepare_PrintBeforeMF(uint8* Buffer, int MaxSize)
	{
		if (m_Pointers.prepare_PrintBeforeMF != NULL)
			return m_Pointers.prepare_PrintBeforeMF(Buffer, MaxSize);
		return -1;
	}

	int prepare_PrintMF(uint8* Buffer, int MaxSize)
	{
		if (m_Pointers.prepare_PrintMF != NULL)
			return m_Pointers.prepare_PrintMF(Buffer, MaxSize);
		return -1;
	}

	int prepare_VoidItem(uint8* Buffer, int MaxSize, uint16 index, uint64 ItemCount, uint8 ItemCountPrecision)
	{
		if (m_Pointers.prepare_VoidItem != NULL)
			return m_Pointers.prepare_VoidItem(Buffer, MaxSize, index, ItemCount, ItemCountPrecision);
		return -1;
	}

	int prepare_Matrahsiz(uint8* Buffer, int MaxSize, char* tck, uint16 subtypeOfTaxException, long matrahsizAmount)
	{
		if (m_Pointers.prepare_Matrahsiz != NULL)
			return m_Pointers.prepare_Matrahsiz(Buffer, MaxSize, tck, subtypeOfTaxException, matrahsizAmount);
		return -1;
	}

	int prepare_Pretotal(uint8* Buffer, int MaxSize)
	{
		if (m_Pointers.prepare_Pretotal != NULL)
			return m_Pointers.prepare_Pretotal(Buffer, MaxSize);
		return -1;
	}

	int prepare_DisplayPaymentSummary(uint8* Buffer, int MaxSize)
	{
		if (m_Pointers.prepare_DisplayPaymentSummary != NULL)
			return m_Pointers.prepare_DisplayPaymentSummary(Buffer, MaxSize);
		return -1;
	}

	int prepare_Plus(uint8* Buffer, int MaxSize, long amount, uint16 indexOfItem)
	{
		if (m_Pointers.prepare_Plus != NULL)
			return m_Pointers.prepare_Plus(Buffer, MaxSize, amount, indexOfItem);
		return -1;
	}

	int prepare_Plus_Ex(uint8* Buffer, int MaxSize, long amount, char *szText, uint16 indexOfItem)
	{
		if (m_Pointers.prepare_Plus_Ex != NULL)
			return m_Pointers.prepare_Plus_Ex(Buffer, MaxSize, amount, szText, indexOfItem);
		return -1;
	}

	int prepare_Minus(uint8* Buffer, int MaxSize, long amount, uint16 indexOfItem)
	{
		if (m_Pointers.prepare_Minus != NULL)
			return m_Pointers.prepare_Minus(Buffer, MaxSize, amount, indexOfItem);
		return -1;
	}

	int prepare_Minus_Ex(uint8* Buffer, int MaxSize, long amount, char *szText, uint16 indexOfItem)
	{
		if (m_Pointers.prepare_Minus_Ex != NULL)
			return m_Pointers.prepare_Minus_Ex(Buffer, MaxSize, amount, szText, indexOfItem);
		return -1;
	}

	int prepare_Inc(uint8* Buffer, int MaxSize, uint8 rate, uint16 indexOfItem)
	{
		if (m_Pointers.prepare_Inc != NULL)
			return m_Pointers.prepare_Inc(Buffer, MaxSize, rate, indexOfItem);
		return -1;
	}

	int prepare_Inc_Ex(uint8* Buffer, int MaxSize, uint8 rate, char *szText, uint16 indexOfItem)
	{
		if (m_Pointers.prepare_Inc_Ex != NULL)
			return m_Pointers.prepare_Inc_Ex(Buffer, MaxSize, rate, szText, indexOfItem);
		return -1;
	}

	int prepare_Dec(uint8* Buffer, int MaxSize, uint8 rate, uint16 indexOfItem)
	{
		if (m_Pointers.prepare_Dec != NULL)
			return m_Pointers.prepare_Dec(Buffer, MaxSize, rate, indexOfItem);
		return -1;
	}

	int prepare_Dec_Ex(uint8* Buffer, int MaxSize, uint8 rate, char *szText, uint16 indexOfItem)
	{
		if (m_Pointers.prepare_Dec_Ex != NULL)
			return m_Pointers.prepare_Dec_Ex(Buffer, MaxSize, rate, szText, indexOfItem);
		return -1;
	}

	int prepare_VoidPayment(uint8* Buffer, int MaxSize, uint16 index)
	{
		if (m_Pointers.prepare_VoidPayment != NULL)
			return m_Pointers.prepare_VoidPayment(Buffer, MaxSize, index);
		return -1;
	}

	int prepare_VoidAll(uint8* Buffer, int MaxSize)
	{
		if (m_Pointers.prepare_VoidAll != NULL)
			return m_Pointers.prepare_VoidAll(Buffer, MaxSize);
		return -1;
	}

	int prepare_SetTaxFree(uint8* Buffer, int MaxSize, uint32 flag, char* name, char* surname, char* identificationNo, char* city, char* country)
	{
		if (m_Pointers.prepare_SetTaxFree != NULL)
			return m_Pointers.prepare_SetTaxFree(Buffer, MaxSize, flag, name, surname, identificationNo, city, country);
		return -1;
	}

	int prepare_SetTaxFreeRefundAmount(uint8* Buffer, int MaxSize, uint32 refundAmount, uint16 refundAmountCurrency)
	{
		if (m_Pointers.prepare_SetTaxFreeRefundAmount != NULL)
			return m_Pointers.prepare_SetTaxFreeRefundAmount(Buffer, MaxSize, refundAmount, refundAmountCurrency);
		return -1;
	}

	int parse_FP3(HTRX *phTrx, ST_MULTIPLE_RETURN_CODE returnCodes[], uint16* pnumberOfreturnCodes, uint32 recvmsgId,  uint8* recvFullBuffer, uint16 recvFullLen, ST_TICKET* pTicket)
	{
		if (m_Pointers.parse_FP3 != NULL)
			return m_Pointers.parse_FP3(phTrx, returnCodes, pnumberOfreturnCodes, recvmsgId,  recvFullBuffer, recvFullLen, pTicket);
		return -1;
	}

	int parse_GetEcr(ST_MULTIPLE_RETURN_CODE* returnCodes, uint16* pnumberOfreturnCodes,  uint32 recvmsgId,  uint8* recvFullBuffer, uint16 recvFullLen)
	{
		if (m_Pointers.parse_GetEcr != NULL)
			return m_Pointers.parse_GetEcr(returnCodes, pnumberOfreturnCodes, recvmsgId, recvFullBuffer, recvFullLen);
		return -1;
	}

	void ExternalDeviceTrace(const char *Str)
	{
		if (m_Pointers.ExternalDeviceTrace != NULL)
			m_Pointers.ExternalDeviceTrace(Str);
	}

	void ExternalDeviceTraceMemory(const char *Str, const void *Ptr, uint16 Len)
	{
		if (m_Pointers.ExternalDeviceTraceMemory != NULL)
			m_Pointers.ExternalDeviceTraceMemory(Str, Ptr, Len);
	}

	const char * GetTagName(uint32 Tag)
	{
		if (m_Pointers.GetTagName != NULL)
			return m_Pointers.GetTagName(Tag);
		return NULL;
	}

	char * GetErrorMessage(uint32 ErrorCode, char *Buffer)
	{
		if (m_Pointers.GetErrorMessage  != NULL)
			return m_Pointers.GetErrorMessage(ErrorCode, Buffer);

		strcpy(Buffer, "Function Can't Call!");
		return Buffer;
	}

	int FP3_GetInterfaceHandleList(HINT *phInt, int Max)
	{
		if (m_Pointers.FP3_GetInterfaceHandleList != NULL)
			return m_Pointers.FP3_GetInterfaceHandleList(phInt, Max);
		return -1;
	}


private:
	void Trace(const char *Format, ...);
	void *GetFunction(const char *FunctionName);

	typedef int (*T_SetXmlFilePath)(const char * path);

	typedef uint16(*T_gmpReadTLVlen)(uint16* plen, uint8* ptr);
	typedef uint16(*T_gmpReadTLVtag)(uint32* ptag, uint8* ptr);
	typedef uint16(*T_gmpTlvSetLen)(uint8* pmsg, uint16 TlvLen);
	typedef uint16(*T_gmpSetTLV)(uint8* pmsg, uint32 Tag, uint8* pdata, uint16 dataLen);
	typedef uint16(*T_gmpSetTLVbcd)(uint8* pmsg, uint32 Tag, uint32 data, uint16 bcdLen);
	typedef uint16(*T_gmpSetTLVbcd_64)(uint8* pmsg, uint32 Tag, uint64 data, uint16 bcdLen);
	typedef int (*T_gmpSearchTLV)(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint8* pdata, uint16 dataMaxLe);
	typedef int (*T_gmpSearchTLVbcd_8)(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint8* pdata, uint8 bcdLen);
	typedef int (*T_gmpSearchTLVbcd_16)(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint16* pdata, uint8 bcdLen);
	typedef int (*T_gmpSearchTLVbcd_32)(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint32* pdata, uint8 bcdLen);
	typedef int (*T_gmpSearchTLVbcd_64)(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint64* pdata, uint8 bcdLen);

	typedef uint16(*T_gmpSetTLV_HL)(uint8* pmsg, uint32 pmsgLen, uint32 Tag, uint8* pdata, uint16 dataLen);    //HighLevel
	typedef uint16(*T_gmpReadTLVtag_HL)(uint32* ptag, uint8* ptr, uint32 startIndex);
	typedef uint16(*T_gmpReadTLVlen_HL)(uint16* plen, uint8* ptr, uint32 startIndex);

	typedef uint32(*T_FP3_FileSystem_FileRead)(HINT hInt, char* FileName, uint32 offset, uint32 whence, uint8* buffer, uint16 maxLen, uint16* pReadLen);
	typedef uint32(*T_FP3_FileSystem_FileRemove)(HINT hInt, char* FileName);
	typedef uint32(*T_FP3_FileSystem_FileRename)(HINT hInt, char* FileNameOld, char* FileNameNew);
	typedef uint32(*T_FP3_FileSystem_FileWrite)(HINT hInt, char* FileName, uint32 offset, uint32 whence, uint8* buffer, uint16 len);
	typedef uint32(*T_FP3_FileSystem_DirChange)(HINT hInt, char* DirName);
	typedef uint32(*T_FP3_FileSystem_DirListFiles)(HINT hInt, char* DirName, ST_FILE stFile[], uint16 maxNumberOfFiles, uint16* pNumberOfFiles);

	typedef uint32(*T_FP3_Database_GetHandle)(HINT hInt);
	typedef uint32(*T_FP3_Database_FreeStructure)(HINT hInt, ST_DATABASE_RESULT *pst);
	typedef uint32(*T_FP3_Database_Open)(HINT hInt, char* name);
	typedef uint32(*T_FP3_Database_Close)(HINT hInt);
	typedef uint32(*T_FP3_Database_Execute)(HINT hInt, char* sqlWord, ST_DATABASE_RESULT* pstDatabaseResult);
	typedef uint32(*T_FP3_Database_Query)(HINT hInt, char* sqlWord, uint16* pnumberOfColomns);
	typedef uint32(*T_FP3_Database_QueryReadLine)(HINT hInt, uint16 numberOfLinesRequested, uint16 numberOfColomnsRequested, ST_DATABASE_RESULT* pstDatabaseResult);
	typedef uint32(*T_FP3_Database_QueryColomnCaptions)(HINT hInt, ST_DATABASE_RESULT* pstDatabaseResult);
	typedef uint32(*T_FP3_Database_QueryReset)(HINT hInt);
	typedef uint32(*T_FP3_Database_QueryFinish)(HINT hInt);

	typedef int (*T_GMP_GetDllVersion)(char* version);
	typedef int (*T_FP3_GMP_StartPairingInit)(HINT hInt, ST_GMP_PAIR *pGMPPair, ST_GMP_PAIR_RESP *pGMPPairResp);

	typedef uint32(*T_FP3_FunctionGetHandleList)(HINT hInt, ST_HANDLE_LIST pstHandleList[], uint8 StatusFilter, uint16 numberOfItems, uint16 *totalNumberOfItems, uint16 *numberOfItemsInThis, int timeoutInMiliseconds);
	typedef void (*T_FP3_ResetHandle)(HINT hInt);

	typedef uint32(*T_FP3_Start)(HINT hInt, HTRX *HTrx, uint8 IsBackground, uint8* uniqueId, int lengthOfUniqueId, uint8* uniqueIdSign, int lengthOfUniqueIdSign, uint8* userData, int lengthOfUserData, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Close)(HINT hInt, HTRX HTrx, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Ping)(HINT hInt, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Echo)(HINT hInt, ST_ECHO *pstEcho, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_PrintTotalsAndPayments)(HINT hInt, HTRX HTrx, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_PrintBeforeMF)(HINT hInt, HTRX HTrx, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_PrintMF)(HINT hInt, HTRX HTrx, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_PrintUserMessage)(HINT hInt, HTRX HTrx, ST_USER_MESSAGE stUserMessage[], uint16 numberOfMessage, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_GetTicket)(HINT hInt, HTRX HTrx, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_GetPLU)(HINT hInt, HTRX HTrx, char* barcode, ST_PLU_RECORD* pstPluRecord, ST_PLU_GROUP_RECORD stPluGroupRecord[], int maxNumberOfGroupRecords, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Payment)(HINT hInt, HTRX HTrx, ST_PAYMENT_REQUEST* pstPaymentRequest, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_ReversePayment)(HINT hInt, HTRX HTrx, ST_PAYMENT_REQUEST stPaymentRequest[], uint16 numberOfPaymentRequests, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_TicketHeader)(HINT hInt, HTRX HTrx, TTicketType ticketType, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_SetInvoice)(HINT hInt, HTRX HTrx, ST_INVIOCE_INFO* pstInvoiceInfo, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_SetParkingTicket)(HINT hInt, HTRX HTrx, char* carIdentification, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_ItemSale)(HINT hInt, HTRX HTrx, ST_ITEM* pstItem, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Matrahsiz)(HINT hInt, HTRX HTrx, char* tck, uint16 subtypeOfTaxException, long matrahsizAmount, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_KasaAvans)(HINT hInt, HTRX HTrx, long amount, ST_TICKET* pStTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_CustomerAvans)(HINT hInt, HTRX HTrx, long amount, ST_TICKET* pStTicket, char* pCustomerName, char* pTckn, char* pVkn, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_KasaPayment)(HINT hInt, HTRX HTrx, long amount, ST_TICKET* pStTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Pretotal)(HINT hInt, HTRX HTrx, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_DisplayPaymentSummary)(HINT hInt, HTRX HTrx, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Plus)(HINT hInt, HTRX HTrx, long Amount, char *szText, ST_TICKET* pstTicket, uint16 indexOfItem, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Minus)(HINT hInt, HTRX HTrx, long Amount, char *szText, ST_TICKET* pstTicket, uint16 indexOfItem, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Inc)(HINT hInt, HTRX HTrx, uint8 Rate, char *szText, ST_TICKET* pstTicket, uint16 indexOfItem, uint32* pchangedAmount, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_Dec)(HINT hInt, HTRX HTrx, uint8 Rate, char *szText, ST_TICKET* pstTicket, uint16 indexOfItem, uint32* pchangedAmount, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_VoidPayment)(HINT hInt, HTRX HTrx, uint16 index, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_VoidAll)(HINT hInt, HTRX HTrx, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_VoidItem)(HINT hInt, HTRX HTrx, uint16 index, uint64 ItemCount, uint8 ItemCountPrecision, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_SetTaxFreeRefundAmount)(HINT hInt, HTRX HTrx, uint32 refundAmount, uint16 refundAmountCurrency, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_SetTaxFree)(HINT hInt, HTRX HTrx, uint32 flag, char* name, char* surname, char* identificationNo, char* city, char* country, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_MultipleCommand)(HINT hInt, HTRX HTrx, ST_MULTIPLE_RETURN_CODE* returnCodes, uint16* pnumberOfReturnCodes, uint8* sendBuffer, uint16 sendBufferLen, ST_TICKET* pstTicket, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionGetUniqueIdList)(HINT hInt, HTRX HTrx, ST_UNIQUE_ID stUniqueIdList[] , uint16 maxNumberOfitems, uint16 indexOfitemsToStart, uint16* ptotalNumberOfItems, uint16* pNumberOfItemsInThis,  int timeoutInMiliseconds);

	typedef uint32(*T_FP3_GetTlvData)(HINT hInt, uint32 tag, uint8* pData, uint16 maxBufferLen, uint16* pDataLen);
	typedef uint32(*T_FP3_GetCashierTable)(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_CASHIER pstCashier[], uint8 numberOfRecordsRequested, uint16* pactiveCashier);
	typedef uint32(*T_FP3_GetExchangeTable)(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_EXCHANGE pstExchange[], uint8 numberOfRecordsRequested);
	typedef uint32(*T_FP3_GetTaxRates)(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_TAX_RATE pstTaxRate[], uint8 numberOfRecordsRequested);
	typedef uint32(*T_FP3_GetDepartments)(HINT hInt, uint8* pnumberOfTotalDepartments, uint8* pnumberOfTotalDepartmentsReceived, ST_DEPARTMENT pstDepartments[], uint8 numberOfDepartmentRequested);
	typedef uint32(*T_FP3_GetPaymentApplicationInfo)(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO pstExchange[], uint8 numberOfRecordsRequested);
	typedef uint32(*T_FP3_GetVasApplicationInfo)(HINT hInt, uint8* pnumberOfTotalRecords, uint8* pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO pstPaymentApplicationInfo[], uint16 vasType);
	typedef uint32(*T_FP3_GetCurrentFiscalCounters)(HINT hInt, uint16* pZNo, uint16* pFNo, uint16* pEKUNo);
	typedef uint32(*T_FP3_GetPluDatabaseInfo)(HINT hInt, char* PluDbName, uint16* pPluDbType, uint32* pPluDbSize, uint32* pPluDbGrupsLastModified, uint32* pPluDbItemsLastModified);
	typedef uint32(*T_FP3_GetTicketHeader)(HINT hInt, uint16 indexOfHeader, ST_TICKET_HEADER* pstTicketHeader, uint16* pNumberOfSpaceTotal, int timeoutInMiliseconds);

	typedef uint32(*T_FP3_SetPluDatabaseInfo)(HINT hInt, char* PluDbName, uint16 PluDbType);
	typedef uint32(*T_FP3_SetDepartments)(HINT hInt, ST_DEPARTMENT pstDepartments[], uint8 numberOfDepartmentRequested, char* supervisorPassword);
	typedef uint32(*T_FP3_SetuApplicationFunction)(HINT hInt, uint8* uApplicationName, uint32 uApplicationId, uint8* functionName, uint32 functionId, uint32 functionVersion, uint32 functionFlags, uint8* commandBuffer, uint32 commandLen, char* supervisorPassword);
	typedef uint32(*T_FP3_SetTlvData)(HINT hInt, uint32 tag, uint8* pData, uint16 Len);

	typedef uint32(*T_FP3_GetDialogInput_MultipleCommand)(HINT hInt, ST_MULTIPLE_RETURN_CODE* returnCodes, uint16* pnumberOfreturnCodes, uint8* sendBuffer, uint16 sendBufferLen, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_GetDialogInput_Text)(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, char* mask, char* value, int maxLenOfValue, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_GetDialogInput_Date)(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, char* mask, ST_DATE_TIME* value, int maxLenOfValue, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_GetDialogInput_Amount)(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, char* mask, char* value, int maxLenOfValue, char* symbol, uint8 align, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_GetDialogInput_Menu)(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, uint8 typeOfMenu, char* title, const char * const * menu, uint32* pvalue, uint8 buttons, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_GetDialogInput_MsgBox)(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, uint8 icon, uint8 button, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_GetDialogInput_Password)(HINT hInt, uint32* pGL_Dialog_retcode, uint32 tag_id, char* title, char* text, char* mask, char* value, int maxLenOfValue, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_GetDialogBarcode)(HINT hInt, uint32* pGL_Dialog_retcode, int Count, uint8* Buffer, int timeOut);

	typedef uint32(*T_FP3_FunctionReadZReport)(HINT hInt, ST_FUNCTION_PARAMETERS *pstFunctionParameters, ST_Z_REPORT *pstZReport, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionReports)(HINT hInt, uint32 functionFlags, ST_FUNCTION_PARAMETERS *pstFunctionParameters, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionEcrParameter)(HINT hInt, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionBankingBatch)(HINT hInt, uint16 bkmId, uint16* pnumberOfBanlResponse, ST_MULTIPLE_BANK_RESPONSE* pMultipleBankResponse, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionBankingParameter)(HINT hInt, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionCashierLogin)(HINT hInt, uint16 cashierIndex, char* cashierPassword);
	typedef uint32(*T_FP3_FunctionCashierLogout)(HINT hInt);
	typedef uint32(*T_FP3_FunctionOpenDrawer)(HINT hInt);
	typedef uint32(*T_FP3_FunctionChangeTicketHeader)(HINT hInt, char* supervisorPassword, uint16* pNumberOfSpaceTotal, uint16* pNumberOfSpaceUsed, ST_TICKET_HEADER* pstTicketHeader, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionBankingRefund)(HINT hInt, ST_PAYMENT_REQUEST *pstReversePayment, int timeoutInMiliseconds);

	typedef uint32(*T_FP3_FunctionEkuPing)(HINT hInt, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionEkuReadInfo)(HINT hInt, uint16 ekuAccessFunction, ST_EKU_MODULE_INFO *pstEkuModuleInfo, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionEkuReadHeader)(HINT hInt, uint16 index, ST_EKU_HEADER *pstEkuHeader, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionEkuReadData)(HINT hInt, uint16* pEkuDataBufferReceivedLen, ST_EKU_APPINF *pstEKUAppInfo, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionEkuSeek)(HINT hInt, ST_EKU_APPINF *pstEKUAppInfo, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_FunctionReadCard)(HINT hInt, uint32 cardReaderTypes, ST_CARD_INFO *pstCardInfo, int timeoutInMiliseconds);

	typedef uint32(*T_FP3_OptionFlags)(HINT hInt, HTRX hTrx, uint64* pflagsActive, uint64 flagsToBeSet,  uint64 flagsToBeClear, int timeoutInMiliseconds);
	typedef uint32(*T_FP3_JumpToECR)(HINT hInt, HTRX hTrx, uint64 jumpFlags, ST_TICKET* pstTicket, int timeoutInMiliseconds);

	typedef	int (*T_prepare_Text)(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, char* value, int timeout);
	typedef int (*T_prepare_Amount)(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, char* value, int maxLenOfValue, char* symbol, uint8 align, int timeout);
	typedef int (*T_prepare_Menu)(uint8* Buffer, int MaxSize, uint32 tag_id, uint8 typeOfMenu, char* title, const char * const * menu, uint32* pvalue, uint8 buttons, int timeout);
	typedef int (*T_prepare_Date)(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, ST_DATE_TIME* value, int timeout);
	typedef int (*T_prepare_Password)(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, char* value, uint16 maxLenOfValue, int timeout);
	typedef int (*T_prepare_MsgBox)(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, uint8 icon, uint8 button, int timeout);

	typedef int (*T_prepare_JumpToECR)(uint8* Buffer, int MaxSize, uint64 jumpFlags);
	typedef int (*T_prepare_Condition)(uint8* Buffer, int MaxSize, ST_CONDITIONAL_IF *pstCondition);
	typedef int (*T_prepare_OptionFlags)(uint8* Buffer, int MaxSize, uint64 flagsToBeSet,  uint64 flagsToBeClear);
	typedef int (*T_prepare_Start)(uint8* Buffer, int MaxSize, uint8* uniqueId, int lengthOfUniqueId, uint8* uniqueIdSign, int lengthOfUniqueIdSign, uint8* userData, int lengthOfUserData);
	typedef int (*T_prepare_Close)(uint8* Buffer, int MaxSize);
	typedef int (*T_prepare_TicketHeader)(uint8* Buffer, int MaxSize, TTicketType ticketType);
	typedef int (*T_prepare_ItemSale)(uint8* Buffer, int MaxSize, ST_ITEM* pstItem);
	typedef int (*T_prepare_SetInvoice)(uint8* Buffer, int MaxSize, ST_INVIOCE_INFO* pstInvoiceInfo);
	typedef int (*T_prepare_SetParkingTicket)(uint8* Buffer, int MaxSize, char* carIdentification);
	typedef int (*T_prepare_Payment)(uint8* Buffer, int MaxSize, ST_PAYMENT_REQUEST* stPaymentRequest);
	typedef int (*T_prepare_ReversePayment)(uint8* Buffer, int MaxSize, ST_PAYMENT_REQUEST stPaymentRequest[], uint16 numberOfPaymentRequests);
	typedef int (*T_prepare_PrintUserMessage)(uint8* Buffer, int MaxSize, ST_USER_MESSAGE stUserMessage[], uint16 numberOfMessage);
	typedef int (*T_prepare_PrintTotalsAndPayments)(uint8* Buffer, int MaxSize);
	typedef int (*T_prepare_PrintBeforeMF)(uint8* Buffer, int MaxSize);
	typedef int (*T_prepare_PrintMF)(uint8* Buffer, int MaxSize);
	typedef int (*T_prepare_VoidItem)(uint8* Buffer, int MaxSize, uint16 index, uint64 ItemCount, uint8 ItemCountPrecision);
	typedef int (*T_prepare_Matrahsiz)(uint8* Buffer, int MaxSize, char* tck, uint16 subtypeOfTaxException, long matrahsizAmount);
	typedef int (*T_prepare_Pretotal)(uint8* Buffer, int MaxSize);
	typedef int (*T_prepare_DisplayPaymentSummary)(uint8* Buffer, int MaxSize);
	typedef int (*T_prepare_Plus)(uint8* Buffer, int MaxSize, long amount, uint16 indexOfItem);
	typedef int (*T_prepare_Plus_Ex)(uint8* Buffer, int MaxSize, long amount, char *szText, uint16 indexOfItem);
	typedef int (*T_prepare_Minus)(uint8* Buffer, int MaxSize, long amount, uint16 indexOfItem);
	typedef int (*T_prepare_Minus_Ex)(uint8* Buffer, int MaxSize, long amount, char *szText, uint16 indexOfItem);
	typedef int (*T_prepare_Inc)(uint8* Buffer, int MaxSize, uint8 rate, uint16 indexOfItem);
	typedef int (*T_prepare_Inc_Ex)(uint8* Buffer, int MaxSize, uint8 rate, char *szText, uint16 indexOfItem);
	typedef int (*T_prepare_Dec)(uint8* Buffer, int MaxSize, uint8 rate, uint16 indexOfItem);
	typedef int (*T_prepare_Dec_Ex)(uint8* Buffer, int MaxSize, uint8 rate, char *szText, uint16 indexOfItem);
	typedef int (*T_prepare_VoidPayment)(uint8* Buffer, int MaxSize, uint16 index);
	typedef int (*T_prepare_VoidAll)(uint8* Buffer, int MaxSize);
	typedef int (*T_prepare_SetTaxFree)(uint8* Buffer, int MaxSize, uint32 flag, char* name, char* surname, char* identificationNo, char* city, char* country);
	typedef int (*T_prepare_SetTaxFreeRefundAmount)(uint8* Buffer, int MaxSize, uint32 refundAmount, uint16 refundAmountCurrency);

	typedef int (*T_parse_FP3)(HTRX *pHTrx, ST_MULTIPLE_RETURN_CODE returnCodes[], uint16* pnumberOfreturnCodes, uint32 recvmsgId,  uint8* recvFullBuffer, uint16 recvFullLen, ST_TICKET* pTicket);
	typedef int (*T_parse_GetEcr)(ST_MULTIPLE_RETURN_CODE* returnCodes, uint16* pnumberOfreturnCodes,  uint32 recvmsgId,  uint8* recvFullBuffer, uint16 recvFullLen);

	typedef void (*T_ExternalDeviceTrace)(const char *Str);
	typedef void (*T_ExternalDeviceTraceMemory)(const char *Str, const void *Ptr, uint16 Len);

	typedef const char *(*T_GetTagName)(uint32 Tag);
	typedef char *(*T_GetErrorMessage)(uint32 ErrorCode, char *Buffer);
	typedef char *(*T_GetXmlFilePath)(char *Buffer);

	typedef int (*T_FP3_GetInterfaceHandleList)(HINT *phInt, int Max);

	struct
	{
		T_SetXmlFilePath							SetXmlFilePath;

		T_gmpReadTLVlen								gmpReadTLVlen;
		T_gmpReadTLVtag								gmpReadTLVtag;
		T_gmpTlvSetLen								gmpTlvSetLen;
		T_gmpSetTLV									gmpSetTLV;
		T_gmpSetTLVbcd								gmpSetTLVbcd;
		T_gmpSetTLVbcd_64							gmpSetTLVbcd_64;
		T_gmpSearchTLV								gmpSearchTLV;
		T_gmpSearchTLVbcd_8							gmpSearchTLVbcd_8;
		T_gmpSearchTLVbcd_16						gmpSearchTLVbcd_16;
		T_gmpSearchTLVbcd_32						gmpSearchTLVbcd_32;
		T_gmpSearchTLVbcd_64						gmpSearchTLVbcd_64;

		T_gmpSetTLV_HL								gmpSetTLV_HL;
		T_gmpReadTLVtag_HL							gmpReadTLVtag_HL;
		T_gmpReadTLVlen_HL							gmpReadTLVlen_HL;

		T_FP3_FileSystem_FileRead						FP3_FileSystem_FileRead;
		T_FP3_FileSystem_FileRemove						FP3_FileSystem_FileRemove;
		T_FP3_FileSystem_FileRename						FP3_FileSystem_FileRename;
		T_FP3_FileSystem_FileWrite						FP3_FileSystem_FileWrite;
		T_FP3_FileSystem_DirChange						FP3_FileSystem_DirChange;
		T_FP3_FileSystem_DirListFiles						FP3_FileSystem_DirListFiles;

		T_FP3_Database_GetHandle						FP3_Database_GetHandle;
		T_FP3_Database_FreeStructure						FP3_Database_FreeStructure;
		T_FP3_Database_Open							FP3_Database_Open;
		T_FP3_Database_Close							FP3_Database_Close;
		T_FP3_Database_Execute							FP3_Database_Execute;
		T_FP3_Database_Query							FP3_Database_Query;
		T_FP3_Database_QueryReadLine						FP3_Database_QueryReadLine;
		T_FP3_Database_QueryColomnCaptions					FP3_Database_QueryColomnCaptions;
		T_FP3_Database_QueryReset						FP3_Database_QueryReset;
		T_FP3_Database_QueryFinish						FP3_Database_QueryFinish;

		T_GMP_GetDllVersion							GMP_GetDllVersion;
		T_FP3_GMP_StartPairingInit						FP3_GMP_StartPairingInit;

		T_FP3_ResetHandle							FP3_ResetHandle;
		T_FP3_Start								FP3_Start;
		T_FP3_Close								FP3_Close;
		T_FP3_Ping								FP3_Ping;
		T_FP3_Echo								FP3_Echo;
		T_FP3_PrintTotalsAndPayments						FP3_PrintTotalsAndPayments;
		T_FP3_PrintBeforeMF							FP3_PrintBeforeMF;
		T_FP3_PrintMF								FP3_PrintMF;
		T_FP3_PrintUserMessage							FP3_PrintUserMessage;
		T_FP3_GetTicket								FP3_GetTicket;
		T_FP3_GetPLU								FP3_GetPLU;
		T_FP3_Payment								FP3_Payment;
		T_FP3_ReversePayment							FP3_ReversePayment;
		T_FP3_TicketHeader							FP3_TicketHeader;
		T_FP3_SetInvoice							FP3_SetInvoice;
		T_FP3_SetParkingTicket							FP3_SetParkingTicket;
		T_FP3_ItemSale								FP3_ItemSale;
		T_FP3_Matrahsiz								FP3_Matrahsiz;
		T_FP3_KasaAvans								FP3_KasaAvans;
		T_FP3_CustomerAvans							FP3_CustomerAvans;
		T_FP3_KasaPayment							FP3_KasaPayment;
		T_FP3_Pretotal								FP3_Pretotal;
		T_FP3_DisplayPaymentSummary						FP3_DisplayPaymentSummary;
		T_FP3_Plus								FP3_Plus;
		T_FP3_Minus								FP3_Minus;
		T_FP3_Inc								FP3_Inc;
		T_FP3_Dec								FP3_Dec;
		T_FP3_VoidPayment							FP3_VoidPayment;
		T_FP3_VoidAll								FP3_VoidAll;
		T_FP3_VoidItem								FP3_VoidItem;
		T_FP3_SetTaxFreeRefundAmount						FP3_SetTaxFreeRefundAmount;
		T_FP3_SetTaxFree							FP3_SetTaxFree;
		T_FP3_MultipleCommand							FP3_MultipleCommand;
		T_FP3_FunctionGetUniqueIdList						FP3_FunctionGetUniqueIdList;

		T_FP3_GetTlvData							FP3_GetTlvData;
		T_FP3_GetCashierTable							FP3_GetCashierTable;
		T_FP3_GetExchangeTable							FP3_GetExchangeTable;
		T_FP3_GetTaxRates							FP3_GetTaxRates;
		T_FP3_GetDepartments							FP3_GetDepartments;
		T_FP3_GetPaymentApplicationInfo						FP3_GetPaymentApplicationInfo;
		T_FP3_GetVasApplicationInfo						FP3_GetVasApplicationInfo;
		T_FP3_GetCurrentFiscalCounters						FP3_GetCurrentFiscalCounters;
		T_FP3_GetPluDatabaseInfo						FP3_GetPluDatabaseInfo;
		T_FP3_GetTicketHeader							FP3_GetTicketHeader;

		T_FP3_SetPluDatabaseInfo						FP3_SetPluDatabaseInfo;
		T_FP3_SetDepartments							FP3_SetDepartments;
		T_FP3_SetuApplicationFunction						FP3_SetuApplicationFunction;
		T_FP3_SetTlvData							FP3_SetTlvData;

		T_FP3_GetDialogInput_MultipleCommand					FP3_GetDialogInput_MultipleCommand;
		T_FP3_GetDialogInput_Text						FP3_GetDialogInput_Text;
		T_FP3_GetDialogInput_Date						FP3_GetDialogInput_Date;
		T_FP3_GetDialogInput_Amount						FP3_GetDialogInput_Amount;
		T_FP3_GetDialogInput_Menu						FP3_GetDialogInput_Menu;
		T_FP3_GetDialogInput_MsgBox						FP3_GetDialogInput_MsgBox;
		T_FP3_GetDialogInput_Password						FP3_GetDialogInput_Password;
		T_FP3_GetDialogBarcode							FP3_GetDialogBarcode;

		T_FP3_FunctionReadZReport						FP3_FunctionReadZReport;
		T_FP3_FunctionReports							FP3_FunctionReports;
		T_FP3_FunctionEcrParameter						FP3_FunctionEcrParameter;
		T_FP3_FunctionBankingBatch						FP3_FunctionBankingBatch;
		T_FP3_FunctionBankingParameter						FP3_FunctionBankingParameter;
		T_FP3_FunctionCashierLogin						FP3_FunctionCashierLogin;
		T_FP3_FunctionCashierLogout						FP3_FunctionCashierLogout;
		T_FP3_FunctionOpenDrawer						FP3_FunctionOpenDrawer;
		T_FP3_FunctionChangeTicketHeader					FP3_FunctionChangeTicketHeader;
		T_FP3_FunctionBankingRefund						FP3_FunctionBankingRefund;

		T_FP3_FunctionEkuPing							FP3_FunctionEkuPing;
		T_FP3_FunctionEkuReadInfo						FP3_FunctionEkuReadInfo;
		T_FP3_FunctionEkuReadHeader						FP3_FunctionEkuReadHeader;
		T_FP3_FunctionEkuReadData						FP3_FunctionEkuReadData;
		T_FP3_FunctionEkuSeek							FP3_FunctionEkuSeek;
		T_FP3_FunctionReadCard							FP3_FunctionReadCard;

		T_FP3_OptionFlags							FP3_OptionFlags;
		T_FP3_JumpToECR								FP3_JumpToECR;

		T_prepare_Text								prepare_Text;
		T_prepare_Amount							prepare_Amount;
		T_prepare_Menu								prepare_Menu;
		T_prepare_Date								prepare_Date;
		T_prepare_Password							prepare_Password;
		T_prepare_MsgBox							prepare_MsgBox;

		T_prepare_JumpToECR							prepare_JumpToECR;
		T_prepare_Condition							prepare_Condition;
		T_prepare_OptionFlags							prepare_OptionFlags;
		T_prepare_Start								prepare_Start;
		T_prepare_Close								prepare_Close;
		T_prepare_TicketHeader							prepare_TicketHeader;
		T_prepare_ItemSale							prepare_ItemSale;
		T_prepare_SetInvoice							prepare_SetInvoice;
		T_prepare_SetParkingTicket						prepare_SetParkingTicket;
		T_prepare_Payment							prepare_Payment;
		T_prepare_ReversePayment						prepare_ReversePayment;
		T_prepare_PrintUserMessage						prepare_PrintUserMessage;
		T_prepare_PrintTotalsAndPayments					prepare_PrintTotalsAndPayments;
		T_prepare_PrintBeforeMF							prepare_PrintBeforeMF;
		T_prepare_PrintMF							prepare_PrintMF;
		T_prepare_VoidItem							prepare_VoidItem;
		T_prepare_Matrahsiz							prepare_Matrahsiz;
		T_prepare_Pretotal							prepare_Pretotal;
		T_prepare_DisplayPaymentSummary						prepare_DisplayPaymentSummary;
		T_prepare_Plus								prepare_Plus;
		T_prepare_Plus_Ex							prepare_Plus_Ex;
		T_prepare_Minus								prepare_Minus;
		T_prepare_Minus_Ex							prepare_Minus_Ex;
		T_prepare_Inc								prepare_Inc;
		T_prepare_Inc_Ex							prepare_Inc_Ex;
		T_prepare_Dec								prepare_Dec;
		T_prepare_Dec_Ex							prepare_Dec_Ex;
		T_prepare_VoidPayment							prepare_VoidPayment;
		T_prepare_VoidAll							prepare_VoidAll;
		T_prepare_SetTaxFree							prepare_SetTaxFree;
		T_prepare_SetTaxFreeRefundAmount					prepare_SetTaxFreeRefundAmount;
		T_parse_FP3								parse_FP3;
		T_parse_GetEcr								parse_GetEcr;

		T_ExternalDeviceTrace							ExternalDeviceTrace;
		T_ExternalDeviceTraceMemory						ExternalDeviceTraceMemory;

		T_GetTagName								GetTagName;
		T_GetErrorMessage							GetErrorMessage;
		T_GetXmlFilePath							GetXmlFilePath;

		T_FP3_FunctionGetHandleList						FP3_FunctionGetHandleList;
		T_FP3_GetInterfaceHandleList						FP3_GetInterfaceHandleList;
	} m_Pointers;

	void *m_Lib;
};

#endif /*__C_ING_GMP_SMART_DLL_H__*/
