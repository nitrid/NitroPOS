package com.swrd.gmp;

import java.io.Console;
import java.util.Arrays;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
 

 




import com.sun.jna.Native;
import com.sun.jna.Platform;
import com.sun.jna.ptr.ByteByReference;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.LongByReference;
import com.swrd.gmp.GmpDll.*;
 

public class GmpDriver {
	
	byte[] m_uniqueId;
	
	public final int TIMEOUT_DEFAULT    = 10000;	// 10 seconds
	public final int TIMEOUT_CARD_TRANSACTIONS = 60000;	// 60 seconds
	public final int START_TICKET_AGAIN = -100;	// 10 seconds
	public final int TIMEOUT_ECHO = 1000;	// 1 seconds
	public final int GMP_TICKET_BUFFER = 500000;  
    public final int STANDART_BUFFER = 50000;
	
	public GmpDll gmpDll;
	public GmpDll.ST_Echo gst_echo;
	public GmpDll.stGMPPair gstGMPPair;
	public GmpDll.stGMPPairResp gstGMPPairResp;
	public GmpDll.ST_PAYMENT_REQUEST[] gstPaymentRequest;
	public GmpDll.ST_TICKET gstTicket;
	public ST_ITEM gstItem;
	
	
	public int totalAmount;
	public long remainingAmount;
	
	////////////////////////////////////////////////
	//		 ENUM TANIMLARI						  //
	////////////////////////////////////////////////
	
	// FiscalPrinter_Function için Flaglar
	public enum FunctionFlags
    {
        GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE (0x00000001),
        GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR(0x00000002), 
        GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR(0x00000003),
        GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR(0x00000004),
        GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR(0x00000005),
        GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF(0x00000006),
        GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER(0x00000007),
        GMP_EXT_DEVICE_FUNC_BIT_KASIYER_SEC(0x00000008),
        GMP_EXT_DEVICE_FUNC_BIT_KASIYER_LOGOUT(0x00000009),
        GMP_EXT_DEVICE_FUNC_BIT_AVANS(0x0000000A),
        GMP_EXT_DEVICE_FUNC_BIT_ODEME(0x0000000B),
        GMP_EXT_DEVICE_FUNC_BIT_CEKMECE_ACMA(0x0000000C),
        GMP_EXT_DEVICE_FUNC_READ_CARD(0x0000000D),
        GMP_EXT_DEVICE_FUNC_GET_CARD_PUAN(0x0000000E),
        GMP_EXT_DEVICE_FUNC_BIT_BANKA_GUN_SONU(0x0000000F),
        GMP_EXT_DEVICE_FUNC_BIT_BANKA_PARAM_YUKLE(0x00000010),
        GMP_EXT_DEVICE_FUNC_BIT_EFT_POS_IADE(0x00000011),
        GMP_EXT_DEVICE_FUNC_GET_UNIQUE_ID_LIST(0x00000012);
        
        private int value;
		
		private FunctionFlags(int v)
		{
			this.value = v;
		}
		
		public int getValue()
		{
			return value;
		}
    };
    
	public enum ECurrency 
	{
		CURRENCY_NONE  ((short)0),
		CURRENCY_TL    ((short)949),
		CURRENCY_DOLAR ((short)840),
		CURRENCY_EU    ((short)978),
		CURRENCY_GPR   ((short)826); 
		
		private short value;
		
		private ECurrency(short v)
		{
			this.value = v;
		}
		
		public short getValue()
		{
			return value;
		}
	
	}
	/*
	public enum ECurrency2 
	{
		public static final short CURRENCY_NONE = 0;
		public static final short CURRENCY_TL    = 949;
		public static final short CURRENCY_DOLAR = 997;
		public static final short CURRENCY_EU    = 978;
		public static final short CURRENCY_GPR   = 826; 
		  
	}*/
	
	public enum EPaymentTypes
	{
		PAYMENT_ALL 			(0x000FFFFF),	//  NAKIT  KREDI  OTHER  YCEKI  DOVIZ   MATRAH  MENU(ODEME TIPLERI)
        PAYMENT_CASH_TL			(0x00000001),	// 	++++   xxxx   xxxx   xxxx   xxxx    ++++	xxxx
        PAYMENT_CASH_CURRENCY	(0x00000002),	// 	xxxx   xxxx   xxxx   xxxx   ++++    ++++    xxxx
        PAYMENT_BANK_CARD		(0x00000004),	//	xxxx   ++++   xxxx   xxxx   xxxx    ++++    xxxx
        PAYMENT_YEMEKCEKI		(0x00000008),	//	xxxx   xxxx   xxxx   ++++   xxxx    xxxx    xxxx(Uygulama varsa)
        PAYMENT_MOBILE 			(0x00000010),	// 	xxxx   ++++   xxxx   xxxx   xxxx    ++++    xxxx(Uygulama varsa)
        PAYMENT_HEDIYE_CEKI 	(0x00000020),   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
        PAYMENT_IKRAM 			(0x00000040),   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
        PAYMENT_ODEMESIZ 		(0x00000080),   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
        PAYMENT_KAPORA 			(0x00000100),   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
        PAYMENT_PUAN 			(0x00000200),   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++

        //REVERSE_PAYMENT_ALL = 0xFFF00000,     //aÃ§Ä±lacak
        REVERSE_PAYMENT_CASH 			(0x00100000),
        REVERSE_PAYMENT_BANK_CARD_VOID 	(0x00200000),
        REVERSE_PAYMENT_BANK_CARD_REFUND(0x00400000),
        REVERSE_PAYMENT_YEMEKCEKI 		(0x00800000),
        REVERSE_PAYMENT_MOBILE 			(0x01000000),
        REVERSE_PAYMENT_HEDIYE_CEKI 	(0x02000000);
		
		private int value;
		
		private EPaymentTypes(int v)
		{
			this.value = v;
		}
		
		public int getValue()
		{
			return value;
		}

	}
	
	public enum EPaymentSubtypes
	{
		PAYMENT_SUBTYPE_CREDIT (0x00000001),
		PAYMENT_SUBTYPE_DEBIT  (0x00000002),
		PAYMENT_SUBTYPE_PUAN   (0x00000004);
	
	
		private int value;
		
		private EPaymentSubtypes(int v)
		{
			this.value = v;
		}
		
		public int getValue()
		{
			return value;
		}
	
	}
	
	public enum ETransactionFiscalType
    {
        TRANSACTION_FISCAL_TYPE_SALE  (0),
        TRANSACTION_FISCAL_TYPE_REFUND(1),
        TRANSACTION_FISCAL_TYPE_VOID  (2),
        TRANSACTION_FISCAL_TYPE_NON_FISCAL_SALE(3),
        TRANSACTION_FISCAL_TYPE_INFO(4);
        
        private int value;
		
		private ETransactionFiscalType(int v)
		{
			this.value = v;
		}
		
		public int getValue()
		{
			return value;
		}
    }
    
	/*public enum ETransactionFiscalType
    {
        TRANSACTION_FISCAL_TYPE_SALE  ,
        TRANSACTION_FISCAL_TYPE_REFUND,
        TRANSACTION_FISCAL_TYPE_VOID  ;
    }*/
	
 
    public enum TTicketType
    {
        TTasnifDisi(0) ,
        TProcessSale(1),
        TZReport(2),
        TXReport(3),
        TEJReport(4),
        TFiscal2Z(5),
        TFiscal2T(6),
        TFiscalCumm(7),
        TAvans(8),
        TPayment(9),
        TZDonemReport(10),
        TXDonemReport(11),
        TXPluSale(12),
        TInvoice(13),
        TVoidSale(14),
        TRefund(15),
        TYemekceki(16),
        TOtopark(17),
        TZReportForce(18),
        TInfo (19),
        TLAST(20);					// Bu satýr hep sonda kalmalý
        
        private int value;
		
		private TTicketType(int v)
		{
			this.value = v;
		}
		
		public int getValue()
		{
			return value;
		}
    }
	
    
    public enum EItemUnitTypes
    {
    	ITEM_NONE (0),
        ITEM_NUMBER(1),
        ITEM_KILOGRAM(2),
        ITEM_GRAM(3),
        ITEM_LITRE(4),

        // Adetsel Birimler
        ITEM_DUZINE(11),
        ITEM_DEMET(12),
        ITEM_KASA(13), 
        ITEM_BAG(14),

        // Aðýrlýk Birimler
        ITEM_MILIGRAM(31),
        ITEM_TON (32),
        ITEM_ONS(33),
        ITEM_DESIGRAM(34),
        ITEM_SANTIGRAM(35),
        ITEM_POUND(36),
        ITEM_KENTAL(37),

        // Uzunluk Birimler
        ITEM_METRE			(51),
        ITEM_SANTIMETRE		(52),        
        ITEM_MILIMETRE		(53),
        ITEM_DEKAMETRE		(54),
        ITEM_HEKTAMETRE		(55),
        ITEM_KILOMETRE		(56),
        ITEM_DESIMETRE		(57),
        ITEM_MIKRON			(58),
        ITEM_INC			(59),
        ITEM_FOOT			(60),
        ITEM_YARD			(61),
        ITEM_MIL			(62),

        // Hacim Birimler
        ITEM_METREKUP		(71),
        ITEM_DESIMETREKUP	(72),
        ITEM_SANTIMETREKUP	(73),
        ITEM_MILIMETREKUP	(74),
        ITEM_DEKALITRE		(75),
        ITEM_HEKTOLITRE		(76),
        ITEM_KILOLITRE		(77),
        ITEM_DESILITRE		(78),
        ITEM_SANTILITRE		(79),
        ITEM_MILILITRE		(80),
        ITEM_INCKUP			(81),
        ITEM_GALLON			(82),
        ITEM_BUSHEL			(83),

        // Alan Birimler
        ITEM_METREKARE		(91),
        ITEM_DEKAMETREKARE	(92),
        ITEM_AR				(93),
        ITEM_KILOMETREKARE	(94),
        ITEM_DESIMETREKARE	(95),
        ITEM_SANTIMETREKARE	(96),
        ITEM_MILIMETREKARE	(97),
        ITEM_DONUM			(98),
        ITEM_HEKTAR			(99),
        ITEM_INCKARE		(100); 	
    	
        private int value;
		
		private EItemUnitTypes(int v)
		{
			this.value = v;
		}
		
		public int getValue()
		{
			return value;
		}
    }
    
    
    public enum EDiscountType
    {
    	TYPE_AMOUNT_INCREASE  ,
    	TYPE_AMOUNT_DECREASE,
    	TYPE_PERCENTAGE_INCREASE,
    	TYPE_PERCENTAGE_DECREASE;
    }
    
    
	public void initDll()
	{  
		gmpDll = (GmpDll) Native.loadLibrary((Platform.isWindows() ? "GMPSmartDll" : "GMPSmartDll.so"), GmpDll.class);
		gst_echo       = new ST_Echo();
		gstGMPPair     = new stGMPPair();
		gstGMPPairResp = new stGMPPairResp();
		gstTicket	   = new ST_TICKET();
		gstItem		   = new ST_ITEM();
		
		ErrorClass.gmpDll = gmpDll;
	}
	 
    private static void MergeItemStruct(ST_TICKET StTicketDest, ST_TICKET StTicketSrc)
    {
    	if (StTicketDest == null)
    		return;
    	
    	if (StTicketSrc == null)
    		return;

        StTicketDest.bcdTicketDate = StTicketSrc.bcdTicketDate;
        StTicketDest.bcdTicketTime = StTicketSrc.bcdTicketTime;
        StTicketDest.CashBackAmount = StTicketSrc.CashBackAmount;
        StTicketDest.EJNo = StTicketSrc.EJNo;
        StTicketDest.FNo = StTicketSrc.FNo;
        StTicketDest.invoiceAmount = StTicketSrc.invoiceAmount;
        StTicketDest.invoiceAmountCurrency = StTicketSrc.invoiceAmountCurrency;
        StTicketDest.invoiceDate = StTicketSrc.invoiceDate;
        StTicketDest.invoiceNo = StTicketSrc.invoiceNo;
        StTicketDest.invoiceType = StTicketSrc.invoiceType;
        StTicketDest.KasaAvansAmount = StTicketSrc.KasaAvansAmount;
        StTicketDest.KasaPaymentAmount = StTicketSrc.KasaPaymentAmount;
        StTicketDest.KatkiPayiAmount = StTicketSrc.KatkiPayiAmount;
        StTicketDest.numberOfItemsInThis = StTicketSrc.numberOfItemsInThis;
        StTicketDest.numberOfPaymentsInThis = StTicketSrc.numberOfPaymentsInThis;
        StTicketDest.numberOfPrinterLinesInThis = StTicketSrc.numberOfPrinterLinesInThis;
        StTicketDest.OptionFlags = StTicketSrc.OptionFlags;
        StTicketDest.TaxFreeCalculated = StTicketSrc.TaxFreeCalculated;
        StTicketDest.TaxFreeRefund = StTicketSrc.TaxFreeRefund;
        StTicketDest.TckNo = StTicketSrc.TckNo;
        StTicketDest.ticketType = StTicketSrc.ticketType;
        StTicketDest.totalNumberOfItems = StTicketSrc.totalNumberOfItems;
        StTicketDest.totalNumberOfPayments = StTicketSrc.totalNumberOfPayments;
        StTicketDest.totalNumberOfPrinterLines = StTicketSrc.totalNumberOfPrinterLines;
        StTicketDest.TotalReceiptAmount = StTicketSrc.TotalReceiptAmount;
        StTicketDest.TotalReceiptDiscount = StTicketSrc.TotalReceiptDiscount;
        StTicketDest.TotalReceiptIncrement = StTicketSrc.TotalReceiptIncrement;
        StTicketDest.TotalReceiptItemCancel = StTicketSrc.TotalReceiptItemCancel;
        StTicketDest.TotalReceiptPayment = StTicketSrc.TotalReceiptPayment;
        StTicketDest.TotalReceiptReversedPayment = StTicketSrc.TotalReceiptReversedPayment;
        StTicketDest.TotalReceiptTax = StTicketSrc.TotalReceiptTax;
        StTicketDest.TransactionFlags = StTicketSrc.TransactionFlags;
        StTicketDest.uniqueId = StTicketSrc.uniqueId;
        StTicketDest.ZNo = StTicketSrc.ZNo;

        StTicketDest.stPrinterCopy = new ST_printerDataForOneLine[(int) StTicketSrc.totalNumberOfPrinterLines];
        for (int i = 0; i < StTicketDest.stPrinterCopy.length; i++)
        {
            StTicketDest.stPrinterCopy[i] = new ST_printerDataForOneLine();
        }

        for (int i = 0; i < StTicketSrc.totalNumberOfItems; ++i)
        {
            if (StTicketSrc.SaleInfo != null && StTicketSrc.SaleInfo[i] != null)
                StTicketDest.SaleInfo[i] = StTicketSrc.SaleInfo[i];
        }

        for (int i = 0; i < StTicketSrc.totalNumberOfPayments; ++i)
        {
            if (StTicketSrc.stPayment != null && StTicketSrc.stPayment[i] != null)
                StTicketDest.stPayment[i] = StTicketSrc.stPayment[i];
        }

        for (int i = 0; i < StTicketSrc.totalNumberOfPrinterLines; ++i)
        {
            if (StTicketSrc.stPrinterCopy != null && StTicketSrc.stPrinterCopy[i] != null)
                StTicketDest.stPrinterCopy[i] = StTicketSrc.stPrinterCopy[i];
        }
    }
	
	
	public int itemVoid(String m_txtCalcTotalPrice)
	{
		int m_index;
        int retcode; 
        long itemCount = 1;


        m_index = Integer.valueOf(m_txtCalcTotalPrice);
        if (m_index == 0)
        {
        	JOptionPane.showConfirmDialog(null, "Satýþ numarasý giriniz!!");
            return 4 ;
        }
        
        retcode = FiscalPrinter_VoidItem((short)(m_index - 1),itemCount, (byte)0 , gstTicket, TIMEOUT_DEFAULT);
        if (retcode != 0)
        {
            //ErrorClass.HandleErrorCode(retcode);
            return retcode;
        }
 
       // DisplayTransaction(m_stTicket, false); 

        m_txtCalcTotalPrice ="";
		return retcode;
	}
	
	public int paymentVoid(String m_txtCalcTotalPrice)
	{
		int m_index;
        int retcode; 


        m_index = Integer.valueOf(m_txtCalcTotalPrice);
        if (m_index == 0)
        {
        	JOptionPane.showConfirmDialog(null, "Satýþ numarasý giriniz!!");
            return 4 ;
        }
        
        retcode = FiscalPrinter_VoidPayment((short)(m_index - 1), gstTicket, TIMEOUT_DEFAULT);
        if (retcode != 0)
        {
            //ErrorClass.HandleErrorCode(retcode);
            return retcode;
        }

       // DisplayTransaction(m_stTicket, false); 

        m_txtCalcTotalPrice ="";
		return retcode;
	}
	
	
	int ReloadTransaction()
    {
        int retcode; 
        long activeFlags = 0;
        LongByReference activeFlagsRef = new LongByReference();
        
        activeFlagsRef.setValue(activeFlags);
        
        retcode = gmpDll.FiscalPrinter_OptionFlags(activeFlagsRef, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0, TIMEOUT_DEFAULT);
        
        while (true)
        {
            retcode = FiscalPrinter_GetTicket(gstTicket, TIMEOUT_DEFAULT);
            if (retcode != 0)
                return retcode;

            if (gstTicket.totalNumberOfPrinterLines > gstTicket.numberOfPrinterLinesInThis)
                continue;

            if (gstTicket.totalNumberOfItems > gstTicket.numberOfItemsInThis)
                continue;

            if (gstTicket.totalNumberOfPayments > gstTicket.numberOfPaymentsInThis)
                continue;

            // Tüm item ve printer satýrlarý geldi
            break;
        }

        //DisplayTransaction(m_stTicket, true);

        return Defines.TRAN_RESULT_OK;
    }
	
	
	void OnBnClickedButtonVoidAll()
    {
        int retcode;
        retcode = FiscalPrinter_VoidAll( gstTicket, TIMEOUT_DEFAULT);
        if (retcode != 0)
        {
            ErrorClass.HandleErrorCode(retcode);
            return;
        }

        //DisplayTransaction(m_stTicket, false);

        gmpDll.FiscalPrinter_Close(TIMEOUT_DEFAULT); 
    }
	
	public int StartTicket(TTicketType ticketType)
	{
		
		int retcode = Defines.TRAN_RESULT_OK;
		long retcode_handle = gmpDll.FiscalPrinter_GetHandle();
		
		if (retcode_handle == 0)
        {
			byte[] m_uniqueId = new byte[100];
			byte[] uniqueIdSign = new byte[100]; //datalar alýnmak istemediði için size dummy olarak verilmiþtir. 
	        byte[] userData     = new byte[100];
 
			retcode = gmpDll.FiscalPrinter_Start(m_uniqueId, m_uniqueId.length,uniqueIdSign,uniqueIdSign.length,userData,userData.length,TIMEOUT_DEFAULT);
			if( retcode == Defines.APP_ERR_ALREADY_DONE )
	        { 
	        	switch( JOptionPane.showConfirmDialog(null, "ÖKC'de Tamamlanmamýþ Ýþlem Var. Ýþlemi ÝPTAL Etmek için Cancel, Tekrar Yüklemek için OK'e basýn", "Tamamlanmamýþ Ýþlem", JOptionPane.CANCEL_OPTION) )
		        {
                    case JOptionPane.OK_OPTION:
                    	return ReloadTransaction();
		            case  JOptionPane.CANCEL_OPTION:
		            	OnBnClickedButtonVoidAll();
		            	return START_TICKET_AGAIN;
		        }
	        }
	        else if(retcode == Defines.TRAN_RESULT_OK )
	        {
		       retcode = gmpDll.FiscalPrinter_TicketHeader( ticketType.getValue(), TIMEOUT_DEFAULT);
		        
	        } 
			
            if (retcode == Defines.TRAN_RESULT_OK)
            {
            	long activeFlags = 0;
                LongByReference activeFlagsRef = new LongByReference();
                activeFlagsRef.setValue(activeFlags);
                retcode = gmpDll.FiscalPrinter_OptionFlags(activeFlagsRef, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0x00000000, TIMEOUT_DEFAULT);
            }
        }
		
		
		if( retcode != Defines.TRAN_RESULT_OK )
        {
	        ErrorClass.HandleErrorCode(retcode);
	        // Handle Açýk kalmasýn...
	        gmpDll.FiscalPrinter_Close(TIMEOUT_DEFAULT);
        }
		
		
		return retcode;
	}
	
	public void DepartmentSale (int deptIndex, String m_txtCalcTotalPrice, JComboBox m_comboBoxCurrency)
	{
		 int retcode;
         String name = "";
         String barcode = "";
         int amount = Integer.valueOf(m_txtCalcTotalPrice);
         short currency = 949;


         String curStr = (String)m_comboBoxCurrency.getSelectedItem();
         if (curStr != null)
        	 currency = Short.valueOf(curStr.substring(0,3));//Convert.ToUInt16(m_comboBoxCurrency.Text.Substring(0, 3));
         
         byte unitType = 0;
         int itemCount = 0;
         if (m_txtCalcTotalPrice.contains("X"))//(m_txtCalcTotalPrice.Text.Contains("X"))
         {
             itemCount = Integer.valueOf(m_txtCalcTotalPrice.substring(0, m_txtCalcTotalPrice.indexOf("X")));
         }
         byte itemCountPrecition = 0;
         int itemcountDotLocation = m_txtCalcTotalPrice.indexOf("."); 
         ST_ITEM stItem = new ST_ITEM();

         retcode = 0;
         
         do
         {
        	 retcode = StartTicket(TTicketType.TProcessSale);        	 
         }
         while(retcode == START_TICKET_AGAIN);
         
         if (retcode != Defines.TRAN_RESULT_OK)
             return;

         if (gmpDll.FiscalPrinter_GetHandle() == 0)
         {
            ;//TODO DisplayTransaction(m_stTicket, false);
             //DisplayItem(m_stTicket, m_stTicket.totalNumberOfItems - 1);
         }


         stItem.type = Defines.ITEM_TYPE_DEPARTMENT;
         stItem.subType = 0;
         stItem.deptIndex = (byte)(deptIndex - 1);
         stItem.amount = amount;
         stItem.currency = currency;
         stItem.count = itemCount;
         stItem.unitType = unitType;
         stItem.pluPriceIndex = 0;
         stItem.countPrecition = itemCountPrecition;
         stItem.name = name;
         stItem.barcode= barcode;

         retcode = FiscalPrinter_ItemSale( stItem, gstTicket, TIMEOUT_DEFAULT);
         if (retcode != 0)
         {
             ErrorClass.HandleErrorCode(retcode);
             return;
         }
 
         //TODO DisplayTransaction(m_stTicket, false);
         ErrorClass.HandleErrorCode(retcode);
         remainingAmount = gstTicket.TotalReceiptAmount-gstTicket.TotalReceiptPayment;
         //DisplayItem(&m_stTicket, m_stTicket.totalNumberOfItems - 1);

         m_txtCalcTotalPrice = ""; 
         //TODO m_comboBoxCurrency.SelectedIndex = 0;
	}
	
	
	public int printAndFinishPayment()
	{
		int retcode;
		retcode = gmpDll.FiscalPrinter_PrintTotalsAndPayments(TIMEOUT_DEFAULT);
        if (retcode != Defines.TRAN_RESULT_OK)
        	return retcode;

        retcode = gmpDll.FiscalPrinter_PrintBeforeMF(TIMEOUT_DEFAULT);
        if (retcode != Defines.TRAN_RESULT_OK)
        	return retcode;
        
          
        GmpDll.ST_USER_MESSAGE[] stUserMessage = new GmpDll.ST_USER_MESSAGE[2];
        for(int i = 0 ; i < stUserMessage.length; i++)
        {
        	stUserMessage[i] = new GmpDll.ST_USER_MESSAGE();        	        	
        }
        
        stUserMessage[0].flag = Defines.PS_32 | Defines.PS_CENTER; 
        stUserMessage[0].message = "We are the world.".getBytes(); 
        stUserMessage[0].len = (byte) stUserMessage[0].message.length;
        retcode = FiscalPrinter_PrintUserMessage(stUserMessage, (short)1, gstTicket, TIMEOUT_DEFAULT); //TODO Yunus exception nullpointer
        if (retcode != Defines.TRAN_RESULT_OK)
            return retcode;
        
 
        retcode = gmpDll.FiscalPrinter_PrintTMF(TIMEOUT_DEFAULT);
        if (retcode != Defines.TRAN_RESULT_OK)
            return retcode;
        
        
        retcode = gmpDll.FiscalPrinter_Close(TIMEOUT_DEFAULT); 
         
		return retcode;
	}
	
	public int cashPaymentTrans(int amount, short currencyOfPayment)
	{
		int retcode = 0;  
		
		
		ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];
        for (int i = 0; i < stPaymentRequest.length; i++)
        {
            stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
        }

        stPaymentRequest[0].typeOfPayment = EPaymentTypes.PAYMENT_CASH_TL.getValue();
        stPaymentRequest[0].subtypeOfPayment = 0;
        stPaymentRequest[0].payAmount = amount;
        stPaymentRequest[0].payAmountCurrencyCode = currencyOfPayment;
        
        retcode = FiscalPrinter_Payment(stPaymentRequest[0], gstTicket, TIMEOUT_CARD_TRANSACTIONS); 
		
		 if (retcode != Defines.TRAN_RESULT_OK)
            return retcode;
		 
		remainingAmount = gstTicket.TotalReceiptAmount-gstTicket.TotalReceiptPayment;
		if(remainingAmount != 0)
			return retcode;
		
		return printAndFinishPayment();
	}
	
	
	
	public int creditPaymnet(JComboBox m_comboBoxCurrency, String m_txtCalcTotalPrice)
	{
		byte numberOfTotalRecords = 0;
        byte numberOfTotalRecordsReceived = 0;
        ST_PAYMENT_APPLICATION_INFO[] stPaymentApplicationInfo = new ST_PAYMENT_APPLICATION_INFO[24];
        for(int i = 0 ; i < 24;i++)
        {
        	stPaymentApplicationInfo[i] = new ST_PAYMENT_APPLICATION_INFO();
        }
        
        int amount=0;
        if (m_comboBoxCurrency.getSelectedItem() == null)
        {
            m_comboBoxCurrency.setSelectedIndex(0);
        }
        short currencyOfPayment = Short.valueOf(((String)m_comboBoxCurrency.getSelectedItem()).substring(0, 3));

        
        ByteByReference numberOfTotalRecordsReceivedRef = new ByteByReference();
        ByteByReference numberOfTotalRecordsRef = new ByteByReference();
        
        int retcode = FiscalPrinter_GetPaymentApplicationInfo(numberOfTotalRecordsRef, numberOfTotalRecordsReceivedRef, stPaymentApplicationInfo, (byte)24);
        
        numberOfTotalRecords         = numberOfTotalRecordsRef.getValue();
        numberOfTotalRecordsReceived = numberOfTotalRecordsReceivedRef.getValue();
        
        if(retcode != Defines.TRAN_RESULT_OK)
            ErrorClass.HandleErrorCode(retcode);
        else if(numberOfTotalRecordsReceived == 0 )
        	JOptionPane.showConfirmDialog(null, "ÖKC Üzerinde Ödeme Uygulanamasý Bulunamadý", "HATA", JOptionPane.OK_OPTION);
        else
        {
        	BankList paf = new BankList(numberOfTotalRecordsReceived, stPaymentApplicationInfo);
        	int selectedBankInd = paf.start();
        	
        	if(selectedBankInd == -1)
        		selectedBankInd = 0;
        	  
        	
        	if( currencyOfPayment == ECurrency.CURRENCY_NONE.getValue() )
                currencyOfPayment = ECurrency.CURRENCY_TL.getValue();
        	
        	if(m_txtCalcTotalPrice.length() != 0)
            {
                amount = Integer.valueOf(m_txtCalcTotalPrice);  
                //TODO amount datasýný 0la
            }
        	
        	int numberOfinstallments = Integer.valueOf(paf.strInstallment); 
        	 
        	 GmpDll.ST_PAYMENT_REQUEST[] stPaymentRequest =  new GmpDll.ST_PAYMENT_REQUEST[1];
        	 stPaymentRequest[0] = new ST_PAYMENT_REQUEST();
        	 
             stPaymentRequest[0].typeOfPayment			= EPaymentTypes.PAYMENT_BANK_CARD.getValue();
             stPaymentRequest[0].subtypeOfPayment       = (EPaymentSubtypes.PAYMENT_SUBTYPE_CREDIT.getValue() | EPaymentSubtypes.PAYMENT_SUBTYPE_DEBIT.getValue() | EPaymentSubtypes.PAYMENT_SUBTYPE_PUAN.getValue());
             stPaymentRequest[0].payAmount				= amount;
             stPaymentRequest[0].payAmountCurrencyCode	= currencyOfPayment;
             stPaymentRequest[0].bankBkmId              = stPaymentApplicationInfo[selectedBankInd].u16BKMId; 
             stPaymentRequest[0].numberOfinstallments	= (short)numberOfinstallments;	
             
             
             byte[] buffer = new byte[1024];
             int bufferLen = 0;
             retcode = FiscalPrinter_Payment(stPaymentRequest[0], gstTicket, TIMEOUT_CARD_TRANSACTIONS);
             
            remainingAmount = gstTicket.TotalReceiptAmount-gstTicket.TotalReceiptPayment;
     		if(remainingAmount != 0)
     			return retcode;
     		
             return printAndFinishPayment();
             
        }
       /* else
        {
            PaymentAppForm paf = new PaymentAppForm(numberOfTotalRecordsReceived, stPaymentApplicationInfo);
            DialogResult dr = paf.ShowDialog();
            if( dr != System.Windows.Forms.DialogResult.OK )
                return;

            if( currencyOfPayment == (UInt16)ECurrency.CURRENCY_NONE )
                currencyOfPayment = (UInt16)ECurrency.CURRENCY_TL;

            if(m_txtCalcTotalPrice.Text.Length != 0)
            {
                amount = (uint)getAmount(m_txtCalcTotalPrice.Text);
                m_txtCalcTotalPrice.Text = "";

            }

            int numberOfinstallments = 0;
            GetInputForm gif;
            do
            {
                gif = new GetInputForm("TAKSÝT SAYISI", "0", 2); 
                DialogResult dr2 = gif.ShowDialog();
                if( dr2 != System.Windows.Forms.DialogResult.OK )
                    return;
                numberOfinstallments = Convert.ToInt32(gif.textBox1.Text);
            }while ( numberOfinstallments > 9 );


            ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];

            stPaymentRequest[0].typeOfPayment			= (uint)EPaymentTypes.PAYMENT_BANKING_CARD;
            stPaymentRequest[0].subtypeOfPayment = (uint)(EPaymentSubtypes.PAYMENT_SUBTYPE_CREDIT | EPaymentSubtypes.PAYMENT_SUBTYPE_DEBIT | EPaymentSubtypes.PAYMENT_SUBTYPE_PUAN);
            stPaymentRequest[0].payAmount				= amount;
            stPaymentRequest[0].payAmountCurrencyCode	= currencyOfPayment;
            stPaymentRequest[0].bankBkmId = paf.pstPaymentApplicationInfoSelected.u16BKMId;
            stPaymentRequest[0].numberOfinstallments	= (ushort)numberOfinstallments;	

            GetPayment( stPaymentRequest, 1 );
        }
		*/
        return retcode;
	}
	
	
	
	public int RaiseAndDiscount(short m_itemNo, int m_type, String m_txtCalcTotalPrice)
    {
        int retcode = -1; 
        int changedAmount = Integer.valueOf(m_txtCalcTotalPrice);

        IntByReference changedAmountRef = new IntByReference();
    	changedAmountRef.setValue(changedAmount);
    	
        String str1 = "";
        if (m_type == GmpDriver.EDiscountType.TYPE_AMOUNT_INCREASE.ordinal())    //amount Increase{
        { 
            retcode = FiscalPrinter_Plus(changedAmount, gstTicket , (short)(m_itemNo - 1), TIMEOUT_DEFAULT);
            str1 = "TUTAR ARTTIRIM";
        }
        else if (m_type == GmpDriver.EDiscountType.TYPE_AMOUNT_DECREASE.ordinal())//amount Decrease
        {
            retcode = FiscalPrinter_Minus(changedAmount,  gstTicket, (short)(m_itemNo - 1), TIMEOUT_DEFAULT);
        }
        else if (m_type == GmpDriver.EDiscountType.TYPE_PERCENTAGE_INCREASE.ordinal())//percent Increase
        { 
            if (m_txtCalcTotalPrice == "")
            {
               retcode = FiscalPrinter_Inc((byte)0x00, gstTicket, (short)(m_itemNo - 1), changedAmountRef, TIMEOUT_DEFAULT);
            }
            else
            retcode = FiscalPrinter_Inc(Byte.valueOf(m_txtCalcTotalPrice), gstTicket, (short)(m_itemNo - 1), changedAmountRef, TIMEOUT_DEFAULT);
        }
        else if (m_type == GmpDriver.EDiscountType.TYPE_PERCENTAGE_DECREASE.ordinal())//percent Decrease
        { 
            if (m_txtCalcTotalPrice == "")
            {
               retcode = FiscalPrinter_Dec((byte)0x00,  gstTicket, (short)(m_itemNo - 1), changedAmountRef, TIMEOUT_DEFAULT);
            }
            else
                retcode = FiscalPrinter_Dec(Byte.valueOf(m_txtCalcTotalPrice), gstTicket, (short)(m_itemNo - 1), changedAmountRef, TIMEOUT_DEFAULT);

        }
        if (retcode != 0)
        {
            return retcode;
        }

        //DisplayTransaction(m_stTicket, false);

        return retcode;

        //m_txtCalcTotalPrice = "";
    }
	
	int GetDepartments(JButton[] idDepartmenButtons)
    {

        int retcode = 0;
        IntByReference numberOfTotalRecordsReceived = new IntByReference();
        IntByReference numberOfTotalTaxRates =  new IntByReference();
        IntByReference numberOfTotalDepartments =  new IntByReference();
        
        ST_TaxRate[] stTaxRates = new ST_TaxRate[8];
        for (int i = 0 ; i < 8; i++) 
        {
        	stTaxRates[i] = new ST_TaxRate();
		}
        
        ST_Department[] stDepartments = new ST_Department[12];
        for (int i = 0 ; i < 12; i++) 
        {
        	stDepartments[i] = new ST_Department();
		}
        
        numberOfTotalTaxRates.setValue(0);
        numberOfTotalRecordsReceived.setValue(0);
        numberOfTotalDepartments.setValue(0);
        
        retcode = FiscalPrinter_GetTaxRates(numberOfTotalTaxRates, numberOfTotalRecordsReceived, stTaxRates, 8);


        if (retcode != 0)
        {
            ErrorClass.HandleErrorCode(retcode);
            return retcode;
        }
        
       retcode = FiscalPrinter_GetDepartments(numberOfTotalDepartments, numberOfTotalRecordsReceived, stDepartments, 12);

        if (retcode != 0)
        {
            ErrorClass.HandleErrorCode(retcode);
            return retcode;
        }
 
        for (int i = 0; i < numberOfTotalDepartments.getValue(); i++)  //daha fazla gelebilir biz 8 adet K deðeri alýyoruz
        {
            if (stDepartments[i].u8TaxIndex >= numberOfTotalTaxRates.getValue() || i > 7)
                continue;
            idDepartmenButtons[i].setText(new String(stDepartments[i].szDeptName).trim() + "  %"+ Integer.toString((stTaxRates[stDepartments[i].u8TaxIndex].taxRate / 100))+"."+ Integer.toString(stTaxRates[stDepartments[i].u8TaxIndex].taxRate % 100)); //= String.Format("{0}" + System.Environment.NewLine + "%{1}.{2}", stDepartments[i].szDeptName, stTaxRates[stDepartments[i].u8TaxIndex].taxRate / 100, stTaxRates[stDepartments[i].u8TaxIndex].taxRate % 100);

        }

        return retcode;
    }
	
	
	
	
	int GetCurrency(JComboBox m_comboBoxCurrency)
    {
        int retcode;
        int numberOfTotalRecordsReceived = 0; 
        int numberOfTotalExchangeRates = 0;
        ST_Exchange[] stExchangeTable = new ST_Exchange[10];
        for (int i = 0 ; i < 10; i++) 
        {
        	stExchangeTable[i] = new ST_Exchange();
		}
        
        IntByReference numberOfTotalRecordsReceivedRef = new IntByReference();
        IntByReference numberOfTotalExchangeRatesRef = new IntByReference();

        retcode = FiscalPrinter_GetExchangeTable(numberOfTotalExchangeRatesRef, numberOfTotalRecordsReceivedRef, stExchangeTable, 10);
        if (retcode != 0)
        {
            ErrorClass.HandleErrorCode(retcode);
            return retcode;
        }

        numberOfTotalExchangeRates = numberOfTotalExchangeRatesRef.getValue();
        numberOfTotalRecordsReceived = numberOfTotalRecordsReceivedRef.getValue();
 
        
        m_comboBoxCurrency.addItem("949 > " + "TL 1TRL  = 1.00TL");

        for (int i = 0; i < numberOfTotalRecordsReceived; i++)
        {
    	  	String currValue = Long.toString(stExchangeTable[i].rate / 100) + "." + Long.toString(stExchangeTable[i].rate % 100) + " TL";
            String str = Integer.toString(stExchangeTable[i].code) + " > " + new String(stExchangeTable[i].prefix) + " 1 " + new String(stExchangeTable[i].prefix)+ " = " + currValue; 
            m_comboBoxCurrency.addItem(str);
             
        } 
        return retcode;
    }
	
	
	public int PairingTransaction (JButton[] idDepartmenButtons,JComboBox m_comboBoxCurrency)
	{
		int resp = 0;
		
		resp = GMP_StartPairingInit(gstGMPPair, gstGMPPairResp);
		
		if (resp != Defines.TRAN_RESULT_OK)
           return resp;


        resp = GetDepartments(idDepartmenButtons);
        if (resp != Defines.TRAN_RESULT_OK)
        {
            ErrorClass.HandleErrorCode(resp);
            return resp;
        }


        resp = GetCurrency(m_comboBoxCurrency);
        if (resp != Defines.TRAN_RESULT_OK)
        {
            ErrorClass.HandleErrorCode(resp);
            return resp;
        }



        
        byte[] m_uniqueId = new byte[100];
        byte[] uniqueIdSign = new byte[100]; //datalar alýnmak istemediði için size dummy olarak verilmiþtir. 
        byte[] userData     = new byte[100];

        resp = gmpDll.FiscalPrinter_Start(m_uniqueId, m_uniqueId.length,uniqueIdSign,uniqueIdSign.length,userData,userData.length,TIMEOUT_DEFAULT);/**/
        
        if( resp == Defines.APP_ERR_ALREADY_DONE )
        { 
        	switch( JOptionPane.showConfirmDialog(null, "ÖKC'de Tamamlanmamýþ Ýþlem Var. Ýþlemi ÝPTAL Etmek için Cancel, Tekrar Yüklemek için OK'e basýn", "Tamamlanmamýþ Ýþlem", JOptionPane.CANCEL_OPTION) )
	        {
                case JOptionPane.OK_OPTION:
                	 resp = ReloadTransaction();
                	 if (resp != 0)
                     {
                         ErrorClass.HandleErrorCode(resp); 
                     }
                	 break;
	            case  JOptionPane.CANCEL_OPTION:
	            	OnBnClickedButtonVoidAll();
	            	break;
	        }
        } 
        
         

        resp = gmpDll.FiscalPrinter_Close(TIMEOUT_DEFAULT);
        m_uniqueId = new byte[10];
		
		return resp;
	}
	
	
	/* testDlli init etmek için
	public GmpDll.multStruct mult;
	
	public void initDll()
	{
		
		mult = new GmpDll.multStruct.ByReference();
		gmpDll = (GmpDll) Native.loadLibrary((Platform.isWindows() ? "testDll" : "c"),GmpDll.class);	
			
	}
	*/

	
	  
	public int FiscalPrinter_Echo(ST_Echo pstEcho, int timeoutInMiliseconds)
	{
		int retcode = 0;  
		byte[] Out_pstEcho = new byte[GMP_TICKET_BUFFER];
		  
		retcode = gmpDll.Json_FiscalPrinter_Echo(Out_pstEcho, Out_pstEcho.length, TIMEOUT_DEFAULT);
		
		if(retcode == 0)
		{
			String jsonString = new String(Out_pstEcho);  
			pstEcho.set(GsonHelper.customGson.fromJson(jsonString.trim(), ST_Echo.class)); 
		}
		return retcode;
	}
	
	public int GMP_StartPairingInit(stGMPPair pGMPPair, stGMPPairResp pGMPPairResp)
	{
		int retcode = 0;
		byte[] json_Out_stPairingResp = new byte[GMP_TICKET_BUFFER];
		String json_In_stPairing = GsonHelper.customGson.toJson(pGMPPair);
		
		gmpDll.SetJavaClassPath("C:\\PROJECTS\\GMPSmartDLL_03022016\\DLL_DEBUG\\Windows\\x86\\test.jar");
		
		retcode = gmpDll.Json_GMP_StartPairingInit(json_In_stPairing.trim(), json_Out_stPairingResp, json_Out_stPairingResp.length);
		
		if(retcode == 0)
		{
			String jsonString = new String(json_Out_stPairingResp);  
			pGMPPairResp.set(GsonHelper.customGson.fromJson(jsonString.trim(), stGMPPairResp.class)); 
		}
		return retcode;
	}
	
	public int FiscalPrinter_GetTicket( ST_TICKET pstTicket, int timeoutInMiliseconds)
	{
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];

        int retcode = gmpDll.Json_FiscalPrinter_GetTicket(json_Out_stTicket, json_Out_stTicket.length, timeoutInMiliseconds);
        if (retcode == 0)
        {
        	String jsonString = new String(json_Out_stTicket);
            ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
            MergeItemStruct(pstTicket, stTicketTemp);
        }
        return retcode;
    }
	
	public int FiscalPrinter_VoidItem(short index, long ItemCount, byte ItemCountPrecision, ST_TICKET pstTicket, int timeoutInMiliseconds)
	{
		 byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];

         int retcode = gmpDll.Json_FiscalPrinter_VoidItem(index, ItemCount, ItemCountPrecision, json_Out_stTicket, json_Out_stTicket.length, timeoutInMiliseconds);
         if (retcode == 0)
         {
        	 String jsonString = new String(json_Out_stTicket);  
             ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
             MergeItemStruct(pstTicket, stTicketTemp);
         }
         return retcode;
		
	}
	
	public int FiscalPrinter_VoidPayment(short index, ST_TICKET pstTicket, int timeoutInMiliseconds)
	{
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];

        int retcode = gmpDll.Json_FiscalPrinter_VoidPayment(index, json_Out_stTicket, json_Out_stTicket.length, timeoutInMiliseconds);
        if (retcode == 0)
        {
        	 String jsonString = new String(json_Out_stTicket);  
             ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
             MergeItemStruct(pstTicket, stTicketTemp);
        }
        return retcode;	
	}
	
	public int FiscalPrinter_VoidAll(ST_TICKET pstTicket, int timeoutInMiliseconds)
	{
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];

        int retcode = gmpDll.Json_FiscalPrinter_VoidAll(json_Out_stTicket, json_Out_stTicket.length, timeoutInMiliseconds);
        if (retcode == 0)
        {
        	 String jsonString = new String(json_Out_stTicket);  
             ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
             MergeItemStruct(pstTicket, stTicketTemp);
        }
        return retcode;	  
	}
	
	public int FiscalPrinter_ItemSale(ST_ITEM pstItem, ST_TICKET pstTicket, int timeoutInMiliseconds)
	{
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER]; 
        String json_In_stItem = GsonHelper.customGson.toJson(pstItem);
        byte[] json_Out_stItem = new byte[GMP_TICKET_BUFFER];

        int retcode = gmpDll.Json_FiscalPrinter_ItemSale(json_In_stItem, json_Out_stItem, json_Out_stItem.length, json_Out_stTicket, json_Out_stTicket.length, TIMEOUT_DEFAULT);
        if (retcode == 0)
        {

            String retJsonString = new String(json_Out_stItem);
            pstItem.set(GsonHelper.customGson.fromJson(retJsonString.trim(), ST_ITEM.class));
            String jsonString = new String(json_Out_stTicket);
            ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
            MergeItemStruct(pstTicket, stTicketTemp);
        }
        return retcode; 
	}
	
	public int FiscalPrinter_GetPaymentApplicationInfo(ByteByReference pnumberOfTotalRecords, ByteByReference pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO[] pstAppInfo, byte numberOfRecordsRequested)
    {
        String json_In_stAppInfo = GsonHelper.customGson.toJson(pstAppInfo);
        byte[] json_Out_stAppInfo = new byte[STANDART_BUFFER];

        int retcode = gmpDll.Json_FiscalPrinter_GetPaymentApplicationInfo(pnumberOfTotalRecords, pnumberOfTotalRecordsReceived, json_In_stAppInfo, json_Out_stAppInfo, json_Out_stAppInfo.length, numberOfRecordsRequested);
        if (retcode == 0)
        {
            String retJsonString = new String(json_Out_stAppInfo);
            ST_PAYMENT_APPLICATION_INFO[] pstAppInfoTemp =  GsonHelper.customGson.fromJson(retJsonString.trim(),ST_PAYMENT_APPLICATION_INFO[].class);
            for(int i = 0 ; i < pnumberOfTotalRecordsReceived.getValue() ; i++)
            {
            	pstAppInfo[i].set(pstAppInfoTemp[i]);
            }
        }
        return retcode;
    }
	
	public int FiscalPrinter_PrintUserMessage(ST_USER_MESSAGE[] stUserMessage, short numberOfMessage, ST_TICKET pstTicket, int timeoutInMiliseconds)
	{
		 byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];
         String json_In_stUser =GsonHelper.customGson.toJson(stUserMessage);
         byte[] json_Out_stUser = new byte[GMP_TICKET_BUFFER];

         int retcode = gmpDll.Json_FiscalPrinter_PrintUserMessage(json_In_stUser, json_Out_stUser, json_Out_stUser.length, numberOfMessage, json_Out_stTicket, json_Out_stTicket.length, TIMEOUT_DEFAULT);
         if (retcode == 0)
         {
             String retJsonString = new String(json_Out_stUser);
             ST_USER_MESSAGE[] stUserMessageTemp = GsonHelper.customGson.fromJson(retJsonString.trim(),ST_USER_MESSAGE[].class);
             for(int i = 0 ; i < stUserMessageTemp.length ; i++)
             {
            	 stUserMessage[i].set(stUserMessageTemp[i]);
             }
             String jsonString = new String(json_Out_stTicket);  
             // Boþ geldiði için kapatýldý.
             // ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class);
             // MergeItemStruct(pstTicket, stTicketTemp);
         }
         return retcode; 
	}
	
	public int FiscalPrinter_Payment(ST_PAYMENT_REQUEST[] stPaymentRequest, ST_TICKET pstTicket, int timeoutInMiliseconds)
	{
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];
        String json_In_stPaymentRequest = GsonHelper.customGson.toJson(stPaymentRequest);
        byte[] json_Out_stPaymentRequest = new byte[GMP_TICKET_BUFFER];

        int retcode = gmpDll.Json_FiscalPrinter_Payment(json_In_stPaymentRequest, json_Out_stPaymentRequest, json_Out_stPaymentRequest.length, json_Out_stTicket, json_Out_stTicket.length, TIMEOUT_DEFAULT);
        if (retcode == 0)
        {
            String retJsonString  = new String(json_Out_stPaymentRequest);
            ST_PAYMENT_REQUEST[] stPaymentRequestTemp = GsonHelper.customGson.fromJson(retJsonString.trim(),ST_PAYMENT_REQUEST[].class);
            for(int i = 0; i < stPaymentRequest.length; i++)
            {
            	stPaymentRequest[i].set(stPaymentRequestTemp[i]);
            }
            String jsonString = new String(json_Out_stTicket);  
            ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
            MergeItemStruct(pstTicket, stTicketTemp);
        }
        return retcode; 
	}
	
	public int FiscalPrinter_Payment(ST_PAYMENT_REQUEST stPaymentRequest, ST_TICKET pstTicket, int timeoutInMiliseconds)
	{
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];
        String json_In_stPaymentRequest = GsonHelper.customGson.toJson(stPaymentRequest);
        byte[] json_Out_stPaymentRequest = new byte[GMP_TICKET_BUFFER]; 
        
        int retcode = gmpDll.Json_FiscalPrinter_Payment(json_In_stPaymentRequest, json_Out_stPaymentRequest, json_Out_stPaymentRequest.length, json_Out_stTicket, json_Out_stTicket.length, TIMEOUT_DEFAULT);
        if (retcode == 0)
        {
            String retJsonString  = new String(json_Out_stPaymentRequest);
            stPaymentRequest.set(GsonHelper.customGson.fromJson(retJsonString.trim(),ST_PAYMENT_REQUEST.class));
            String jsonString = new String(json_Out_stTicket);   
            ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
            MergeItemStruct(pstTicket, stTicketTemp);
        }
        return retcode; 
	}
	
	public int FiscalPrinter_Plus (int amount,  ST_TICKET pstTicket, short indexOfItem, int timeoutInMiliseconds)
	{
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];

        int retcode = gmpDll.Json_FiscalPrinter_Plus(amount, json_Out_stTicket, json_Out_stTicket.length, indexOfItem, timeoutInMiliseconds);
        if (retcode == 0)
        {
        	 String jsonString = new String(json_Out_stTicket);  
             ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
             MergeItemStruct(pstTicket, stTicketTemp);
        }
        return retcode;
	}
    
	public int FiscalPrinter_Minus(int amount,  ST_TICKET pstTicket, short indexOfItem, int timeoutInMiliseconds)
	{
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];

        int retcode = gmpDll.Json_FiscalPrinter_Minus(amount, json_Out_stTicket, json_Out_stTicket.length, indexOfItem, timeoutInMiliseconds);
        if (retcode == 0)
        {
        	 String jsonString = new String(json_Out_stTicket);  
             ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
             MergeItemStruct(pstTicket, stTicketTemp);
        }
        return retcode;
		
	}
    public int FiscalPrinter_Inc  (byte rate,    ST_TICKET pstTicket, short indexOfItem, IntByReference pchangedAmount, int timeoutInMiliseconds)
    {
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];

		int retcode = gmpDll.Json_FiscalPrinter_Inc(rate, json_Out_stTicket, json_Out_stTicket.length, indexOfItem, pchangedAmount, timeoutInMiliseconds);
		if (retcode == 0)
		{
			String jsonString = new String(json_Out_stTicket);  
            ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
            MergeItemStruct(pstTicket, stTicketTemp);
		}
  return retcode; 
    }
    
    public int FiscalPrinter_Dec  (byte rate,    ST_TICKET pstTicket, short indexOfItem, IntByReference pchangedAmount, int timeoutInMiliseconds)
    {
		byte[] json_Out_stTicket = new byte[GMP_TICKET_BUFFER];

        int retcode = gmpDll.Json_FiscalPrinter_Dec(rate, json_Out_stTicket, json_Out_stTicket.length, indexOfItem, pchangedAmount, timeoutInMiliseconds);
        if (retcode == 0)
        {
        	String jsonString = new String(json_Out_stTicket);  
            ST_TICKET stTicketTemp = GsonHelper.customGson.fromJson(jsonString.trim(), ST_TICKET.class); 
            MergeItemStruct(pstTicket, stTicketTemp);
        }
        return retcode; 
    }
    
    public int FiscalPrinter_GetTaxRates( IntByReference pnumberOfTotalRecords, IntByReference pnumberOfTotalRecordsReceived, ST_TaxRate[] pstTaxRate, int numberOfRecordsRequested)
    {
       String json_In_stTaxRates =GsonHelper.customGson.toJson(pstTaxRate);
	   byte[] json_Out_stTaxRates = new byte[STANDART_BUFFER];

       int retcode = gmpDll.Json_FiscalPrinter_GetTaxRates(pnumberOfTotalRecords, pnumberOfTotalRecordsReceived, json_In_stTaxRates, json_Out_stTaxRates, json_Out_stTaxRates.length, numberOfRecordsRequested);
       if (retcode == 0)
       {
           String retJsonString = new String(json_Out_stTaxRates);
           ST_TaxRate[] pstTaxRateTemp = GsonHelper.customGson.fromJson(retJsonString.trim(),ST_TaxRate[].class);
           
           for(int i = 0 ; i < pnumberOfTotalRecordsReceived.getValue();i++)
           {
        	   pstTaxRate[i].set(pstTaxRateTemp[i]);
           }
       }
       return retcode;
   }
   
   public int FiscalPrinter_GetDepartments(IntByReference pnumberOfTotalDepartments, IntByReference pnumberOfTotalDepartmentsReceived, ST_Department[] pstDepartments, int numberOfDepartmentRequested)
   { 
	   String json_stDepartments =GsonHelper.customGson.toJson(pstDepartments);
       byte[] json_Out_stDepartments = new byte[STANDART_BUFFER];

       int retcode = gmpDll.Json_FiscalPrinter_GetDepartments(pnumberOfTotalDepartments, pnumberOfTotalDepartmentsReceived, json_stDepartments, json_Out_stDepartments, json_Out_stDepartments.length, numberOfDepartmentRequested);
       if (retcode == 0)
       {
           String retJsonString = new String(json_Out_stDepartments);
           ST_Department[] pstDepartmentsTemp = GsonHelper.customGson.fromJson(retJsonString.trim(),ST_Department[].class);
           
           for(int i = 0 ; i < pnumberOfTotalDepartmentsReceived.getValue();i++)
           {
        	   pstDepartments[i].set(pstDepartmentsTemp[i]);
           }
       }
       return retcode;
   }
   

	public int FiscalPrinter_GetExchangeTable(IntByReference pnumberOfTotalRecords, IntByReference pnumberOfTotalRecordsReceived, ST_Exchange[] pstExchange, int numberOfRecordsRequested)
	{
		 String json_In_stExchangeTable = GsonHelper.customGson.toJson(pstExchange);
         byte[] json_Out_stExchangeTable = new byte[STANDART_BUFFER];


         int retcode = gmpDll.Json_FiscalPrinter_GetExchangeTable(pnumberOfTotalRecords, pnumberOfTotalRecordsReceived, json_In_stExchangeTable, json_Out_stExchangeTable, json_Out_stExchangeTable.length, numberOfRecordsRequested);

         if (retcode == 0)
         {
             String retJsonString = new String(json_Out_stExchangeTable);
             ST_Exchange[] pstExchangeTemp = GsonHelper.customGson.fromJson(retJsonString.trim(), ST_Exchange[].class);
             for(int i = 0 ; i < pnumberOfTotalRecordsReceived.getValue();i++)
             {
            	 pstExchange[i].set(pstExchangeTemp[i]);
             }
         }
         return retcode;
	}
    
	
	public void test ( )
	{
		 
		GmpDll.ST_USER_MESSAGE[] stUserMessage = new GmpDll.ST_USER_MESSAGE[2]; 
		stUserMessage[0].flag = Defines.PS_32 | Defines.PS_CENTER; 
		stUserMessage[0].message =  "Teþekkür Ederiz".getBytes(); 
		stUserMessage[0].len = (byte) stUserMessage[0].message.length;
		FiscalPrinter_PrintUserMessage(stUserMessage, (short)1, gstTicket, TIMEOUT_DEFAULT); 
 
	}
}



