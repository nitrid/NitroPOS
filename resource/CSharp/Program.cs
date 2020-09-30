using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GmpSampleSim;
using GmpSampleSim.Models;
using Newtonsoft.Json.Linq;

namespace Ingenico
{
    class Program
    {
        static UInt32 CurrentInterface = GetInterface();
        static ST_GMP_PAIR_RESP pairingResp;
        static public UInt64 ActiveTransactionHandle;
        static Dictionary<UInt32, byte[]> TransactionUniqueIdList = new Dictionary<UInt32, byte[]>();
        static byte[] TsmSign = null;
        static List<CommandItem> CommandList = new List<CommandItem>();

        static void Main(string[] args)
        {
            while (true) // Loop indefinitely
            {
                string line = Console.ReadLine();
                string tag = line.Split('|')[0];

                if (tag == "PING")
                {
                    line = Ping();
                    Console.WriteLine(line);
                }
                else if (tag == "PAIRING")
                {
                    line = StartPairing();
                    Console.WriteLine(line);
                }
                else if (tag == "ITEM_SALE")
                {

                    if (line.Split('|').Length > 0)
                    {
                        OpenHandle();
                        TicketHeader();
                        OptionFlag();

                        JObject TmpMaster = JObject.Parse(line.Split('|')[1]);
                        foreach (JProperty MasterItem in TmpMaster.Properties())
                        {
                            if (MasterItem.Name == "SALES")
                            {
                                JArray TmpSales = JArray.Parse(MasterItem.Value.ToString());
                                foreach (JObject SalesItem in TmpSales.Children<JObject>())
                                {
                                    Console.WriteLine(SalesItem.Property("NAME").Value.ToString());
                                    AddItem(SalesItem.Property("NAME").Value.ToString(), (UInt32)SalesItem.Property("QUANTITY").Value, (uint)SalesItem.Property("AMOUNT").Value, (int)SalesItem.Property("TAX").Value);
                                }
                            }
                            else if (MasterItem.Name == "PAYMENT")
                            {
                                JArray TmpPayment = JArray.Parse(MasterItem.Value.ToString());
                                foreach (JObject PaymentItem in TmpPayment.Children<JObject>())
                                {
                                    CashPayment((int)PaymentItem.Property("TYPE").Value, (UInt32)PaymentItem.Property("AMOUNT").Value);
                                }
                            }
                        }

                        TotalPrint();
                        MFPrintBefore();
                        MFPrint();
                        CloseHandle();

                        if (ProcessBatchCommand())
                        {
                            Console.WriteLine("ITEM_SALE|SUCCES");
                        }
                        else
                        {
                            Console.WriteLine("ITEM_SALE|FAULT");
                        }

                        ClearProcessBatchCommand();
                    }
                }
                else if (tag == "TICKET_CLOSE")
                {
                    line = TicketClose();
                    Console.WriteLine(line);
                }
                if (tag == "exit") // Check string
                { 
                    break;
                }
            }
        }
        private static string GenerateUniqueId()
        {
            byte[] szUniqueID = new byte[17];
            GMPSmartDLL.GenerateUniqueID(szUniqueID);
            string uniqueId = GMP_Tools.GetStringFromBytes(szUniqueID);
            return uniqueId;
        }
        private static UInt64 ACTIVE_TRX_HANDLE
        {
            get { return ActiveTransactionHandle; }
            set
            {
                ActiveTransactionHandle = value;
            }
        }
        private static UInt64 GetTransactionHandle(UInt32 InterfaceHandle)
        {
            return ACTIVE_TRX_HANDLE;
        }
        private static byte[] GetUniqueIdByInterface(UInt32 InterfaceHandle)
        {
            byte[] m_uniqueId = new byte[24];

            if (TransactionUniqueIdList.ContainsKey(InterfaceHandle))
                Array.Copy(TransactionUniqueIdList[InterfaceHandle], m_uniqueId, 24);

            return m_uniqueId;
        }
        private static void ClearTransactionUniqueId(UInt32 InterfaceHandle)
        {
            if (TransactionUniqueIdList.ContainsKey(InterfaceHandle))
                Array.Clear(TransactionUniqueIdList[InterfaceHandle], 0, 24);
        }
        private static UInt32 StartTicket(TTicketType ticketType)
        {
            UInt64 TranHandle = 0;
            UInt32 retcode = Defines.TRAN_RESULT_OK;

        start_again:
            if (GetTransactionHandle(CurrentInterface) == 0)
            {
                if (ticketType != TTicketType.TProcessSale)
                    ClearTransactionUniqueId(CurrentInterface);

                byte[] UserData = new byte[] { 0x74, 0x65, 0x73, 0x74, 0x64, 0x61, 0x74, 0x61 };
                retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TranHandle, 0, GetUniqueIdByInterface(CurrentInterface), 24, TsmSign, TsmSign == null ? 0 : TsmSign.Length, UserData, UserData.Length, 10000);

                if (retcode == Defines.APP_ERR_ALREADY_DONE)
                {
                    goto start_again;
                }
                else if (retcode == Defines.TRAN_RESULT_OK)
                    retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), ticketType, Defines.TIMEOUT_DEFAULT);

                if (retcode == Defines.TRAN_RESULT_OK)
                {
                    UInt64 activeFlags = 0;
                    retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0x00000000, Defines.TIMEOUT_DEFAULT);
                }
            }

            if (retcode != Defines.TRAN_RESULT_OK)
            {
                // Handle Açık kalmasın...
                UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                uint resp = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                if (resp == Defines.TRAN_RESULT_OK)
                {

                }
                    
            }

            return retcode;
        }
        private static void AddTrxHandles(UInt64 hTrx)
        {
            ACTIVE_TRX_HANDLE = hTrx;
        }
        private static void DeleteTrxHandles(UInt32 hInt, UInt64 hTrx)
        {
            ACTIVE_TRX_HANDLE = 0;
        }
        private static UInt32 ReloadTransaction()
        {
            UInt32 RetCode = 0;
            ST_TICKET m_stTicket = new ST_TICKET();
            UInt64 activeFlags = 0;

            RetCode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0, Defines.TIMEOUT_DEFAULT);
            if (RetCode != Defines.TRAN_RESULT_OK)
                return RetCode;

            RetCode = Json_GMPSmartDLL.FP3_GetTicket(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);
            if (RetCode != Defines.TRAN_RESULT_OK)
                return RetCode;

            return RetCode;
        }
        private static UInt32 GetInterface()
        {
            UInt32[] InterfaceList = new UInt32[20];
            UInt32 InterfaceCount = GMPSmartDLL.FP3_GetInterfaceHandleList(InterfaceList, (UInt32)InterfaceList.Length);
            return InterfaceList[0];
        }
        private static void AddIntoCommandBatch(string commandName, int commandType, byte[] buffer, int bufferLen)
        {
            byte[] dataPtr = new byte[bufferLen + 6];
            byte[] type = new byte[4];
            int typeLen = 0;
            StringToByteArray(commandType.ToString("X2"), type, ref typeLen);
            Buffer.BlockCopy(type, 0, dataPtr, 0, 4);

            byte[] bufLen = new byte[2];
            int bufLenLen = 0;

            String TempLen;
            TempLen = bufferLen.ToString("X2");
            if ((TempLen.Length % 2) == 1)
                TempLen = "0" + TempLen;
            StringToByteArray(TempLen, bufLen, ref bufLenLen);
            Buffer.BlockCopy(bufLen, 0, dataPtr, 4, 2);

            Buffer.BlockCopy(buffer, 0, dataPtr, 6, bufferLen);

            CommandList.Add(new CommandItem() { Name = commandName, Buffer = ByteArrayToString(dataPtr, bufferLen + 6) });
        }
        private static void StringToByteArray(string s, byte[] Out_byteArr, ref int Out_byteArrLen)
        {
            byte[] ba = new byte[s.Length / 2];
            for (int i = 0; i < ba.Length; i++)
            {
                string temp = s.Substring(i * 2, 2);
                ba[(ba.Length - 1) - i] = Convert.ToByte(temp, 16);
            }
            Out_byteArrLen = ba.Length;
            Array.Copy(ba, 0, Out_byteArr, 0, ba.Length);
        }
        private static void StringToByteArray_Rev(string s, byte[] Out_byteArr, ref int Out_byteArrLen)
        {
            byte[] ba = new byte[s.Length / 2];
            for (int i = 0; i < ba.Length; i++)
            {
                string temp = s.Substring(i * 2, 2);
                ba[i] = Convert.ToByte(temp, 16);
            }
            Out_byteArrLen = ba.Length;
            Array.Copy(ba, 0, Out_byteArr, 0, ba.Length);
        }
        private static string ByteArrayToString(byte[] buffer, int bufferLen)
        {
            string str = "";
            for (int i = 0; i < bufferLen; i++)
            {
                str += buffer[i].ToString("X2");
            }
            return str;
        }
        private static int GetBatchCommand(byte[] sendBuffer)
        {
            int numberOfTotalCommands = CommandList.Count;
            UInt32 MessageCommandType = 0;
            int sendBufferLen = 0;
            byte[] MessageBuffer = new byte[1024 * 16];	// this is buffer for just one msg type (exp: GMP_FISCAL_PRINTER_REQ or GMP_EXT_DEVICE_GET ...
            UInt16 MessageBufferLen = 0;

            for (int i = 0; i < numberOfTotalCommands; i++)
            {
                byte[] Data = new byte[1024];
                int DataLen = 0;
                UInt16 Len = 0;
                UInt32 CommandType;
                string RowData = CommandList[i].Buffer;
                StringToByteArray(RowData, Data, ref DataLen);

                if (DataLen == 0) // There is no data to send
                    continue;

                // This is the data to be sent to ECR.
                string TempStr = "";
                for (int j = DataLen - 4; j < DataLen; j++)
                {
                    TempStr += Data[j].ToString("X2");
                }
                CommandType = UInt32.Parse(TempStr, System.Globalization.NumberStyles.HexNumber);

                TempStr = "";
                for (int j = DataLen - 6; j < DataLen - 4; j++)
                {
                    TempStr += Data[j].ToString("X2");
                }
                Len = UInt16.Parse(TempStr, System.Globalization.NumberStyles.HexNumber);

                if (MessageCommandType == 0)
                    MessageCommandType = CommandType;

                if (MessageCommandType != CommandType)
                {

                    // this means that the msgCommandType is changing in the list, so close the previous package..
                    sendBufferLen += GMPSmartDLL.gmpSetTLV_HL(sendBuffer, sendBufferLen, MessageCommandType, MessageBuffer, MessageBufferLen);
                    MessageBufferLen = 0;
                    MessageCommandType = CommandType;
                }

                StringToByteArray_Rev(RowData, Data, ref DataLen);

                Buffer.BlockCopy(Data, 6, MessageBuffer, MessageBufferLen, Len);
                MessageBufferLen += Len;
            }
            if (MessageBufferLen != 0)
            {
                // this means that the msgCommandType is changing in the list, so close the privous package..
                sendBufferLen += GMPSmartDLL.gmpSetTLV_HL(sendBuffer, sendBufferLen, MessageCommandType, MessageBuffer, MessageBufferLen);
                MessageBufferLen = 0;
            }

            return sendBufferLen;
        }
        private static bool ProcessBatchCommand()
        {
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            byte[] sendBuffer = new byte[1024 * 16];
            UInt16 sendBufferLen = 0;
            
            ST_MULTIPLE_RETURN_CODE[] stReturnCodes = new ST_MULTIPLE_RETURN_CODE[1024]; // will return return codes of each subcommand
            ST_TICKET m_stTicket = new ST_TICKET();
            UInt32 msgCommandType = 0;
            byte[] msgBuffer = new byte[1024 * 16];	// this is buffer for just one msg type (exp: GMP_FISCAL_PRINTER_REQ or GMP_EXT_DEVICE_GET ...
            UInt16 msgBufferLen = 0;
            UInt16 numberOfreturnCodes = 512;
            // Prepare Data To Send
            sendBufferLen = (UInt16)GetBatchCommand(sendBuffer);
            if (sendBufferLen == 0)
                // Nothing to send...
                return false;

            UInt16 Len = 0;
            UInt64 TransactionHandle = 0;
            
            while ((Len < sendBufferLen) && (retcode == Defines.TRAN_RESULT_OK))
            {
                Len += GMPSmartDLL.gmpReadTLVtag(ref msgCommandType, sendBuffer, Len);
                Len += GMPSmartDLL.gmpReadTLVlen_HL(ref msgBufferLen, sendBuffer, Len);
                Buffer.BlockCopy(sendBuffer, Len, msgBuffer, 0, msgBufferLen);
                Len += msgBufferLen;
                
                // Preceed received message
                switch (msgCommandType)
                {
                    case Defines.GMP3_FISCAL_PRINTER_MODE_REQ:
                    case Defines.GMP3_FISCAL_PRINTER_MODE_REQ_E:

                        // Send to ECR and wait for the response (one error code for each sub command until one of them is failed !!)
                        TransactionHandle = GetTransactionHandle(CurrentInterface);
                        retcode = Json_GMPSmartDLL.FP3_MultipleCommand(CurrentInterface, ref TransactionHandle, ref stReturnCodes, ref numberOfreturnCodes, msgBuffer, msgBufferLen, ref m_stTicket, 1000 * 100);

                        ACTIVE_TRX_HANDLE = TransactionHandle;

                        break;
                    case Defines.GMP3_EXT_DEVICE_GET_DATA_REQ:
                    case Defines.GMP3_EXT_DEVICE_GET_DATA_REQ_E:
                        // Send to ECR and wait for the response (one error code for each sub command until one of them is failed !!)
                        retcode = 0xFFFF;//GMPSmartDLL.GetDialogInput_MultipleCommand_HL(stReturnCodes, numberOfreturnCodes, ref tempNumberOfreturnCodes, msgBuffer, msgBufferLen, ref m_stTicket, 1000 * 100);
                        //numberOfreturnCodes += tempNumberOfreturnCodes;
                        break;
                }
            }
            
            if (retcode == Defines.TRAN_RESULT_OK)
            {
                try
                {
                    //int indexOnListCtrl = 0;
                    numberOfreturnCodes = (ushort)CommandList.Count;

                    for (int t = 0; t < numberOfreturnCodes; t++)
                    {
                        byte[] returnCodeString = new byte[256];

                        if (stReturnCodes[t] != null)
                        {
                            // This is not a result of subCommand (it is a tag value in Get Response )
                            if (stReturnCodes[t].indexOfSubCommand == 0)
                                continue;

                            // This is not a result of subCommand (it is a tag value in Get Response )
                            if (stReturnCodes[t].subCommand == 0)
                                continue;

                            GMPSmartDLL.GetErrorMessage(stReturnCodes[t].retcode, returnCodeString);
                        }

                        CommandList[t].Buffer = GMP_Tools.SetEncoding(returnCodeString);
                    }
                }
                catch(Exception ex)
                {
                    return false;
                }                
            }

            return true;
        }
        private static void ClearProcessBatchCommand()
        {
            CommandList.Clear();
        }

        static string Ping()
        {
            UInt32 retcode;
            retcode = GMPSmartDLL.FP3_Ping(CurrentInterface, 1100);


            switch (retcode)
            {
                case Defines.TRAN_RESULT_OK:
                    return "PING|CONNECTED";
                case Defines.DLL_RETCODE_RECV_BUSY:
                    return "PING|BUSY";
                case Defines.DLL_RETCODE_TIMEOUT:
                    return "PING|TIMEOUT";
                default:
                    return "PING|ERROR";
            }
        }
        static string StartPairing()
        {
            ST_ECHO stEcho = new ST_ECHO();
            ST_GMP_PAIR pairing = new ST_GMP_PAIR();
            UInt64 TranHandle = 0;
            UInt32 RetCode;

            RetCode = Json_GMPSmartDLL.FP3_Echo(CurrentInterface, ref stEcho, Defines.TIMEOUT_ECHO);
            
            if (RetCode != Defines.TRAN_RESULT_OK)
            {
                return "PAIRING|FAULT";
            }

            pairing.szExternalDeviceBrand = "INGENICO";
            pairing.szExternalDeviceModel = "IWE280";
            pairing.szExternalDeviceSerialNumber = "12344567";
            pairing.szEcrSerialNumber = "JHWE20000079";
            pairing.szProcOrderNumber = "000001";
            pairing.szProcDate = DateTime.Now.Day.ToString().PadLeft(2,'0') + DateTime.Now.Month.ToString().PadLeft(2, '0') + DateTime.Now.Year.ToString().Substring(2,2);
            pairing.szProcTime = DateTime.Now.Hour.ToString().PadLeft(2, '0') + DateTime.Now.Minute.ToString().PadLeft(2, '0') + DateTime.Now.Second.ToString().PadLeft(2, '0');
            
            RetCode = Json_GMPSmartDLL.FP3_StartPairingInit(CurrentInterface, ref pairing, ref pairingResp);

            if (RetCode != Defines.TRAN_RESULT_OK)
            {
                return "PAIRING|FAULT";
            }

            byte[] UniqueId = new byte[24] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };            

            RetCode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TranHandle, 0, UniqueId, UniqueId.Length, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
            AddTrxHandles(TranHandle);

            int flag = 0;

            if (RetCode == Defines.APP_ERR_ALREADY_DONE)
            {
                RetCode = ReloadTransaction();
                flag = 1;
            }

            if (flag != 1)
            {
                UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                RetCode = Defines.TRAN_RESULT_OK;
                if (TransHandle != 0)
                {
                    RetCode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                    if (RetCode == Defines.TRAN_RESULT_OK)
                        DeleteTrxHandles(CurrentInterface, TransHandle);

                    ClearTransactionUniqueId(CurrentInterface);
                }

                flag = 0;
            }

            return "PAIRING|SUCCES";
        }
        static string OpenHandle()
        {
            byte[] buffer = new byte[1024];
            int bufferLen = 0;

            bufferLen = GMPSmartDLL.prepare_Start(buffer, buffer.Length, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0);
            AddIntoCommandBatch("prepare_Start", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            return "OPEN HANDLE";
        }
        static string CloseHandle()
        {
            byte[] buffer = new byte[1024];
            int bufferLen = 0;

            bufferLen = GMPSmartDLL.prepare_Close(buffer, buffer.Length);
            AddIntoCommandBatch("prepare_Close", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            return "CLOSE HANDLE";
        }
        static string TicketHeader()
        {
            byte[] buffer = new byte[1024];
            int bufferLen = 0;

            bufferLen = GMPSmartDLL.prepare_TicketHeader(buffer, buffer.Length, TTicketType.TProcessSale);
            AddIntoCommandBatch("prepare_TicketHeader", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            return "TICKET HEADER";
        }
        static string OptionFlag()
        {
            byte[] buffer = new byte[1024];
            int bufferLen = 0;

            bufferLen = GMPSmartDLL.prepare_OptionFlags(buffer, buffer.Length, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0);
            AddIntoCommandBatch("prepare_OptionFlags", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            return "OPTION FLAG";
        }
        static string AddItem(string pName, UInt32 pQuantity,uint pAmount,int pTax)
        {
            UInt16 currency = 949;
            UInt32 itemCount = pQuantity;
            byte unitType = 0;//(byte)EItemUnitTypes.ITEM_KILOGRAM; 0 adet, 2 kilogram
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_ITEM stItem = new ST_ITEM();

            stItem.type = Defines.ITEM_TYPE_DEPARTMENT;
            stItem.subType = 0;
            stItem.deptIndex = (byte)pTax;
            stItem.amount = pAmount;
            stItem.currency = currency;
            stItem.count = itemCount;
            stItem.unitType = unitType;
            stItem.pluPriceIndex = 0;
            stItem.countPrecition = 0;
            stItem.name = pName;
            stItem.barcode = "";
            Console.WriteLine(itemCount);
            if (PromotionModel.Instance.Amount > 0)
            {
                stItem.promotion.amount = (int)PromotionModel.Instance.Amount;
                stItem.promotion.ticketMsg = PromotionModel.Instance.Message;
                stItem.promotion.type = (byte)PromotionModel.Instance.Type;
                PromotionModel.Instance.Clear();
            }

            byte[] buffer = new byte[1024];
            int bufferLen = 0;

            bufferLen = Json_GMPSmartDLL.prepare_ItemSale(buffer, buffer.Length, ref stItem);
            AddIntoCommandBatch("prepare_ItemSale", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            return "ADD ITEM";
        }
        static string CashPayment(int pType,UInt32 pAmount)
        {
            UInt16 currencyOfPayment = (UInt16)ECurrency.CURRENCY_TL;
            ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];

            for (int i = 0; i < stPaymentRequest.Length; i++)
            {
                stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
            }
            //NAKİT OR KREDİ KARTI TİPLERİ İÇİN
            if(pType == 0)
            {
                stPaymentRequest[0].typeOfPayment = (uint)EPaymentTypes.PAYMENT_CASH_TL;
                stPaymentRequest[0].subtypeOfPayment = 0;
            }
            else if(pType == 1)
            {
                stPaymentRequest[0].BankPaymentUniqueId = GenerateUniqueId();
                stPaymentRequest[0].typeOfPayment = (uint)EPaymentTypes.PAYMENT_BANK_CARD;
                stPaymentRequest[0].subtypeOfPayment = Defines.PAYMENT_SUBTYPE_SALE;
                stPaymentRequest[0].bankBkmId = 0;
                stPaymentRequest[0].transactionFlag = 0x00000000;
                stPaymentRequest[0].numberOfinstallments = 0;
                stPaymentRequest[0].rawData = Encoding.Default.GetBytes("RawData from external application for the payment application");
                stPaymentRequest[0].rawDataLen = (ushort)stPaymentRequest[0].rawData.Length;
            }

            
            stPaymentRequest[0].payAmount = pAmount;
            stPaymentRequest[0].payAmountCurrencyCode = currencyOfPayment;

            byte[] buffer = new byte[1024];
            int bufferLen = 0;

            bufferLen = Json_GMPSmartDLL.prepare_Payment(buffer, buffer.Length, ref stPaymentRequest[0]);
            AddIntoCommandBatch("prepare_Payment", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            return "PAYMENT";
        }
        static string TotalPrint()
        {
            byte[] buffer = new byte[1024];
            int bufferLen = 0;

            bufferLen = GMPSmartDLL.prepare_PrintTotalsAndPayments(buffer, buffer.Length);
            AddIntoCommandBatch("prepare_PrintTotalsAndPayments", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            return "TOTAL PRINT";
        }
        static string MFPrintBefore()
        {
            byte[] buffer = new byte[1024];
            int bufferLen = 0;

            bufferLen = GMPSmartDLL.prepare_PrintBeforeMF(buffer, buffer.Length);
            AddIntoCommandBatch("prepare_PrintBeforeMF", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            return "MF PRINT BEFORE";
        }
        static string MFPrint()
        {
            byte[] buffer = new byte[1024];
            int bufferLen = 0;

            bufferLen = GMPSmartDLL.prepare_PrintMF(buffer, buffer.Length);
            AddIntoCommandBatch("prepare_PrintMF", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            return "MF PRINT";
        }
        static string TicketClose()
        {
            UInt32 RetCode = 0;
            ST_TICKET m_stTicket = new ST_TICKET();

            RetCode = Json_GMPSmartDLL.FP3_VoidAll(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);
            if (RetCode != 0)
            {
                return "TICKET CLOSE|FAULT";
            }

            uint resp = GMPSmartDLL.FP3_Close(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
            if (RetCode != 0)
            {
                return "TICKET CLOSE|FAULT";
            }

            DeleteTrxHandles(CurrentInterface, GetTransactionHandle(CurrentInterface));
            ClearTransactionUniqueId(CurrentInterface);

            return "TICKET CLOSE|SUCCES";
        }

    }
}
