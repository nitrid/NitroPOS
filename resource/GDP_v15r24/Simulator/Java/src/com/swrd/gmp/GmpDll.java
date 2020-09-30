package com.swrd.gmp;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Structure; 
import com.sun.jna.ptr.ByteByReference;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.LongByReference;
import com.swrd.gmp.GmpDll.ST_date.ByReference;

/*
 * Bu interface ile gmpdlle ait fonksiyonlarý ve yapýlarý tanýmlýyoruz.
 * testDll için en aþaðdýdaki örnek kodu inceleyebilirsiniz 
 * 
 * AUTHOR : serhat çaðdaþ
 * 
 * */

public interface GmpDll extends Library 
{	
	
	public final int TIMEOUT_ECHO = 1000;
	public final int MAX_SALE_INFO = 512;
	public final int MAX_PAYMENT = 24;
	public final int MAX_TAX_DETAIL = 8; 
	public final int MAX_PRINTER_COPY = 1024;
	
	////////////////////////////////////////////////
	//        STRUCT TANIMLARI                    //
	////////////////////////////////////////////////
	
	//ST_PAYMENT_APPLICATION_INFO
	public static class ST_PAYMENT_APPLICATION_INFO 
	{  
		public byte[] 	name;
		public byte	    index; 
		public int  	u16BKMId; 
		public short			Status;
		public short			Priority;
		public short			u16AppId;		  
		
        public ST_PAYMENT_APPLICATION_INFO()
        {  
        	name = new byte[20];
        	index = 0;
        	u16BKMId    = 0 ;
        	Status = 0; 
        	Priority     = 0;   
        	u16AppId 	  = 0; 
        } 
        
        public void set(ST_PAYMENT_APPLICATION_INFO inStAppliInfo)
        {
        	name 	  =  inStAppliInfo.name 	;
        	index 	  =  inStAppliInfo.index 	;
        	u16BKMId  =  inStAppliInfo.u16BKMId ;
        	Status 	  =  inStAppliInfo.Status 	;
        	Priority  =  inStAppliInfo.Priority ;
        	u16AppId  =  inStAppliInfo.u16AppId ;        	
        }
	} 

	//ST_Exchange
	public static class ST_Exchange
	{ 
		public int 	code;
		public String 	prefix;
		public String     sign; 
		public byte  	locationOfSign; 
		public byte			tousandSeperator;
		public byte			centSeperator;
		public byte			numberOfCentDigit;		 
		public long			rate;
		
        public ST_Exchange()
        { 
        	code       = 0;
        	prefix             = "";
        	sign               = "";
        	locationOfSign     = 0 ;
        	tousandSeperator   = 0; 
        	centSeperator      = 0;   
        	numberOfCentDigit  = 0;
        	rate 	  = 0;
        }
        
        public void set(ST_Exchange inStExchange)
        {
        	code       			= inStExchange.code       		;			
        	prefix				= inStExchange.prefix			;			
        	sign 				= inStExchange.sign 			;			
        	locationOfSign    	= inStExchange.locationOfSign   ; 			
        	tousandSeperator 	= inStExchange.tousandSeperator ;			
        	centSeperator     	= inStExchange.centSeperator    ; 			
        	numberOfCentDigit 	= inStExchange.numberOfCentDigit; 			
        	rate 	  			= inStExchange.rate 	  		;	
        }
	}
 
	//ST_Department
	public static class ST_Department
	{ 
		  
		public String	szDeptName;
		public byte 	u8TaxIndex;
		public long     iCurrencyType;//GmpDriver.ECurrency
		public long  	iUnitType;//GmpDriver.EItemUnitTypes
		public long			u64Limit;
		public long			u64Price;
		 
        
        public ST_Department()
        { 
        	szDeptName = "";
        	u8TaxIndex    = 0 ;
        	iCurrencyType = 0;//iCurrencyType = GmpDriver.ECurrency.CURRENCY_DOLAR;
        	iUnitType     = 0;//iUnitType     = GmpDriver.EItemUnitTypes.ITEM_NONE;  
        	u64Limit 	  = 0;
        	u64Price 	  = 0;
        }
        
        public void set(ST_Department inStDepartment)
        {
        	szDeptName 	  = inStDepartment.szDeptName 	  ;
        	u8TaxIndex    = inStDepartment.u8TaxIndex     ;
        	iCurrencyType = inStDepartment.iCurrencyType  ;
        	iUnitType     = inStDepartment.iUnitType      ;
        	u64Limit 	  = inStDepartment.u64Limit 	  ;
        	u64Price 	  = inStDepartment.u64Price 	  ;
        }
	} 
	
	//ST_TaxRate
	public static class ST_TaxRate
	{ 
        public int taxRate;  
		 
        
        public ST_TaxRate()
        { 
        	taxRate   = 0;  
        }
        
        public void set(ST_TaxRate inStTaxRate)
        {
        	taxRate = inStTaxRate.taxRate;
        }
	}  
	
	
	//ST_USER_MESSAGE
	public static class ST_USER_MESSAGE
	{   
        public long flag; 
        public byte len; 
        public byte[] message;
		 
        
        public ST_USER_MESSAGE()
        { 
        	flag   = 0;
        	len   = 0;
        	message    = new byte[48+1];
        			
        }
        
        public void set (ST_USER_MESSAGE inStUserMsg)
        {
        	flag   		= inStUserMsg.flag;
        	len   		= inStUserMsg.len;
        	message   	= inStUserMsg.message;
        }       
        
	}  
	
	//ST_Cashier
	public static class ST_Cashier
	{  
        public int index; 
        public long flags; 
        public String ticketMsg;
		 
        
        public ST_Cashier()
        { 
        	index   = 0;
        	flags   = 0;
        	ticketMsg    = "";
        } 
		 
	} 
	
	
	
	//ST_Echo
	public static class ST_Echo
	{
		public long retcode;
		public long status;
		public byte[] kvc; 
        public byte ecrMode;
        public int mtuSize;
        public byte[] ecrVersion;
        public ST_Cashier activeCashier;
		 
        
        public ST_Echo()
        {
        	retcode = 0;
        	status  = 0;
        	kvc     = new byte[8];
        	ecrMode = 0;
        	mtuSize = 1024;
        	ecrVersion 		=new byte[16];
        	activeCashier   = new ST_Cashier(); 
        			
        }
        
        public void set(ST_Echo inStEcho)
        {
        	retcode 	  = inStEcho.retcode 	    ;
        	status  	  = inStEcho.status  	    ;
        	kvc     	  = inStEcho.kvc     	    ;
        	ecrMode 	  = inStEcho.ecrMode 	    ;
        	mtuSize 	  = inStEcho.mtuSize 	    ;
        	ecrVersion 	  = inStEcho.ecrVersion 	;
        	activeCashier = inStEcho.activeCashier	; 
        }
		 
	} 
	
	 
	
	//stGMPPair
	public static class stGMPPair 
	{ 
		public byte[] In_ProcOrderNum;
		public byte[] In_ProcDate;
		public byte[] In_ProcTime; 
        public byte[] In_DeviceBrand; 
        public byte[] In_DeviceModel; 
        public byte[] In_DeviceSerialNum; 
        public byte[] In_DeviceEcrRegisterNo;
		
		public stGMPPair()
		{
			In_ProcOrderNum     = new byte[]{0x00,0x00,0x01};
			In_ProcDate         = new byte[3];
			In_ProcTime         = new byte[3];
	        In_DeviceBrand      = new byte[]{'I','N','G','E','N','I','C','O',0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//("INGENICO").getBytes().;
	        In_DeviceModel      = new byte[]{'I','D','E','2','8','0',0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//"IWE280";
	        In_DeviceEcrRegisterNo = new byte[]{'1','2','3','4','5','6','7',0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//"12344567"; 
            In_DeviceSerialNum  =  new byte[]{'J','I','D','E','0','0','0','0','0','0','1','6',0x00,0x00,0x00,0x00,0x00};//"JHWE20000079";
		} 
		 
	} 
	 
	
	
	//stGMPPairResp
	public static class stGMPPairResp
	{ 
		public byte[] Out_ProcOrderNum;
		public byte[] Out_ProcDate;
		public byte[] Out_ProcTime; 
	    public byte[] Out_DeviceBrand;  
	    public byte[] Out_DeviceModel;
	    public byte[] Out_DeviceSerialNum;
	    public byte[] Out_OKCCert;			/**< To be defined */
	    public byte[] Out_DHp;				/**< To be defined */
	    public byte[] Out_DHg;				/**< To be defined */
	    public byte[] Out_ErrorRespCode;
	    public byte[] Out_StatusCode;
	    public byte[] Out_VersionNumber;
		 
	    
	    public stGMPPairResp()
	    {
	    	Out_ProcOrderNum = new byte[6];
	    	Out_ProcDate     = new byte[6]; 
	    	Out_ProcTime     = new byte[6];
	    	Out_DeviceBrand  = new byte[16]; 
	    	Out_DeviceModel	 = new byte[16];
	    	Out_DeviceSerialNum	 = new byte[16];
	    	Out_OKCCert 		 = new byte[256];			/**< To be defined */
	    	Out_DHp 			 = new byte[256];			/**< To be defined */
	    	Out_DHg 			 = new byte[2];				/**< To be defined */
	    	Out_ErrorRespCode	 = new byte[4];
	    	Out_StatusCode		 = new byte[4];
	    	Out_VersionNumber	 = new byte[16]; 
	    }
	    
	    public void set(stGMPPairResp inStGMPPairResp)
	    {
	    	Out_ProcOrderNum 	= inStGMPPairResp.Out_ProcOrderNum 	   ;
	    	Out_ProcDate    	= inStGMPPairResp.Out_ProcDate    	   ;
	    	Out_ProcTime     	= inStGMPPairResp.Out_ProcTime     	   ;
	    	Out_DeviceBrand  	= inStGMPPairResp.Out_DeviceBrand  	   ;
	    	Out_DeviceModel		= inStGMPPairResp.Out_DeviceModel		;
	    	Out_DeviceSerialNum	= inStGMPPairResp.Out_DeviceSerialNum	;
	    	Out_OKCCert 		= inStGMPPairResp.Out_OKCCert 		   ;
	    	Out_DHp 			= inStGMPPairResp.Out_DHp 			   ;
	    	Out_DHg 			= inStGMPPairResp.Out_DHg 			   ;
	    	Out_ErrorRespCode	= inStGMPPairResp.Out_ErrorRespCode	   ;
	    	Out_StatusCode		= inStGMPPairResp.Out_StatusCode		;
	    	Out_VersionNumber	= inStGMPPairResp.Out_VersionNumber	   ;  
	    }
		 
	}
	
	
	
	
 
    
  //ST_CARD_INFO
  	public static class ST_CARD_INFO
  	{ 
  		
  		public byte   inputType;
  		public String pan; 
  	    public String holderName;  
  	    public byte[] type;		// Local, international ..
  	    public String expireDate; 
  		 
  	    
  	    public ST_CARD_INFO()
  	    { 
  	    	inputType        = 0; 
  	    	pan			     = "";
  	    	holderName	     = ""; 
  	    	type             = new byte[3];
  	    	expireDate		 = ""; 
  	    } 
  	}
	
  	
	
	//ST_PAYMENT_REQUEST
	public static class ST_PAYMENT_REQUEST
	{ 
		public long typeOfPayment;
		public long subtypeOfPayment;
		public long payAmount; 
		public int payAmountCurrencyCode;
		public int bankBkmId;
		public int numberOfinstallments; 
		
		// Refund 
        public long 	loyaltyTobeRefund; 				        /**< LoyaltyTobeRefund[6];bcd tag 23 */ 
        public long	orginalTransactionAmount;		        /**< tag 21 OrgTransAmount[6] bcd */ 
        public long	orginalLoyaltyAmount;			        /**< tag 23 OrgLoyaltyAmount[6] bcd */ 
        public byte[] 	rrn; 						            /**< ascii tag 46 */
        public byte[]  	referenceCodeOfTransaction;         	/**< ascii tag 75 */
        public byte[]	orginalMerchantId;			            /**< tag 67 ascii */
        public byte  orginalTransactionType; 		            /**< byte tag 70 */ 
        public byte[] 	authorizationCode;			            /**< ascii */ //6 size 
        public byte[]	terminalId; 					        /**< ascii for multimerchant */ //8 size 
        public byte[]	orginalTransactionDate;		            /**< tag 47 OrgTransDate[5] bcd YY- YYMMDDHHMM */ //5 size 
        public long  batchNo;						            /**< Batch number */ 
        public long  stanNo;							        /**< Stan number */
        public short rawDataLen;
        public byte[] rawData;
        

		
	    public ST_CARD_INFO stCard; 
		 
	    
	    public ST_PAYMENT_REQUEST()
	    {
	    	typeOfPayment	 = 0;
	    	subtypeOfPayment = 0; 
	    	payAmount	     = 0;
	    	payAmountCurrencyCode    = 0; 
	    	bankBkmId	             = 0;
	    	numberOfinstallments	 = 0;
	    	
	    	loyaltyTobeRefund		 = 0;
	    	orginalTransactionAmount = 0;
	    	orginalLoyaltyAmount 	 = 0;
	    	rrn						 = new byte[12];
	    	referenceCodeOfTransaction=new byte[16];
	    	orginalMerchantId	      =new byte[15];
	    	orginalTransactionType    = 0; 		            /**< byte tag 70 */ 
	        authorizationCode =new byte[6];;			    /**< ascii */ 
	        terminalId=new byte[8]; 					    /**< ascii for multimerchant */ 
	        orginalTransactionDate=new byte[5];		        /**< tag 47 OrgTransDate[5] bcd YY- YYMMDDHHMM */
	        batchNo	=	0;						            /**< Batch number */ 
	        stanNo 	=	0;							        /**< Stan number */
	        rawDataLen = 0;
	        rawData = new byte[1024];
	    	 
	    	stCard	 = new ST_CARD_INFO(); 
	    } 
	    
	    public void set(ST_PAYMENT_REQUEST inStPaymentRquest)
	    {
	    	typeOfPayment	 	       =  inStPaymentRquest.typeOfPayment	 	        ;
	    	subtypeOfPayment 	       =  inStPaymentRquest.subtypeOfPayment 	        ;
	    	payAmount	     	       =  inStPaymentRquest.payAmount	     	        ;
	    	payAmountCurrencyCode      =  inStPaymentRquest.payAmountCurrencyCode       ;
	    	bankBkmId	               =  inStPaymentRquest.bankBkmId	                ;
	    	numberOfinstallments	   =  inStPaymentRquest.numberOfinstallments	    ;
	    	loyaltyTobeRefund		   =  inStPaymentRquest.loyaltyTobeRefund		    ;
	    	orginalTransactionAmount   =  inStPaymentRquest.orginalTransactionAmount    ;
	    	orginalLoyaltyAmount 	   =  inStPaymentRquest.orginalLoyaltyAmount 	    ;
	    	rrn						   =  inStPaymentRquest.rrn						    ;
	    	referenceCodeOfTransaction =  inStPaymentRquest.referenceCodeOfTransaction  ;
	    	orginalMerchantId	       =  inStPaymentRquest.orginalMerchantId	        ;
	    	orginalTransactionType     =  inStPaymentRquest.orginalTransactionType      ;
	    	authorizationCode 	       =  inStPaymentRquest.authorizationCode 	        ;
	    	terminalId	               =  inStPaymentRquest.terminalId	                ;
	    	orginalTransactionDate     =  inStPaymentRquest.orginalTransactionDate      ;
	    	batchNo		               =  inStPaymentRquest.batchNo		                ;
	    	stanNo 		               =  inStPaymentRquest.stanNo 		                ;
	    	stCard					   =  inStPaymentRquest.stCard					    ;	    	
	    }
	}
	 
	
	//ST_PaymentErrMessage
	public static class ST_PaymentErrMessage 
	{ 
        public String ErrorCode; // bank error code 
        public String ErrorMsg; 
        public String AppErrorCode; // payment application specific error code 
        public String AppErrorMsg;
		 
	    
	    public ST_PaymentErrMessage()
	    {
	    	ErrorCode	     = "";
	    	ErrorMsg		 = "";
	    	AppErrorCode	 = "";
	    	AppErrorMsg		 = "";
	    	  
	    } 
	}

	
	
	//ST_BANK_PAYMENT_INFO
	public static class ST_BANK_PAYMENT_INFO
	{ 

        public long 	 batchNo; 
        public long	 stan; 
        public int bankBkmId;
        public byte  numberOfdiscount; 
        public byte  numberOfbonus; 
        public String authorizeCode; 
        public byte[] transFlag; 
        public String terminalId; 
        public String merchantId;
        public String bankName;
        public ST_CARD_INFO stCard;	
        public ST_PaymentErrMessage stPaymentErrMessage;
		 
	    
	    public ST_BANK_PAYMENT_INFO()
	    {
	    	batchNo	   = 0;
	    	stan       = 0; 
	    	bankBkmId  = 0;
	    	numberOfdiscount    = 0; 
	    	numberOfbonus       = 0;
	    	authorizeCode	    = "";
	    	transFlag		    = new byte[2];
	    	terminalId		    = "";
	    	merchantId		    = "";
	    	bankName		    = "";
	    	stCard	 			= new ST_CARD_INFO();
	    	stPaymentErrMessage = new ST_PaymentErrMessage();
	    }  
	}
		

	
	//ST_PAYMENT
	public static class ST_PAYMENT
	{  
		public byte flags;
		public long  dateOfPayment;
		public long  typeOfPayment; 			// EPaymentTypes
		public byte subtypeOfPayment;		// EPaymentSubtypes
		public long  orgAmount;				// Exp; Currency Amount
		public int orgAmountCurrencyCode;	// as defined in currecyTable from GIB 
		public long  payAmount;					// always TL with precision 2
		public int payAmountCurrencyCode;		// always TL
		public long   cashBackAmountInTL;		// Para üstü, her zaman TL with precision 2
		public long   cashBackAmountInDoviz;		// Para Üstü, döviz satýþ ise döviz karþýlýðý
        public ST_BANK_PAYMENT_INFO stBankPayment;	// Keeps all payment info related with bank
		
	    
	    public ST_PAYMENT()
	    {
	    	flags			 = 0;
	    	dateOfPayment	 = 0; 
	    	typeOfPayment    = 0;
	    	subtypeOfPayment = 0; 
	    	orgAmount        = 0;
	    	orgAmountCurrencyCode	 = 0; 
	    	payAmount        = 0;
	    	payAmountCurrencyCode = 0;
	    	cashBackAmountInTL= 0;
	    	cashBackAmountInDoviz=0;
	    	stBankPayment = new ST_BANK_PAYMENT_INFO();
	    }  
	}

	
	
	//ST_PAYMENT_REQUEST
	public static class SALEINFO
	{ 
		public byte   ItemType;
		public long   ItemPrice;
		public long   IncAmount;
		public long   DecAmount;
		public long 	  OrigialItemAmount; // Eðer kýsým bilgisi TL olarak tanýmlanmamýþsa, kýsým tutarý buraya kaydedilir ve diðer amout yeniden kur bilgisi ile hesaplanýlarak ezilir
		public int  OriginalItemAmountCurrency; 
		public int  ItemVatRate;
		public int  ItemCurrencyType;
		public byte	  ItemVatIndex;
		public byte   ItemCountPrecision;
		public long 	  ItemCount;
		public byte  ItemUnitType;
		public byte  DeptIndex;
		public long 	  Flag;
		public String Name;
		public String Barcode;
		
	    
	    public SALEINFO()
	    {
	    	ItemType         = 0;
	    	ItemPrice		 = 0;
	    	IncAmount		 = 0;
	    	DecAmount		 = 0;
	    	OrigialItemAmount= 0; 
	    	OriginalItemAmountCurrency= 0;
	    	ItemVatRate	     = 0; 
	    	ItemCurrencyType = 0;
	    	ItemVatIndex	 = 0;
	    	ItemCountPrecision= 0;
	    	ItemCount		 = 0;
	    	ItemUnitType	 = 0;
	    	DeptIndex	 	 = 0;
	    	Flag		 	 = 0;
	    	Name			 = "";
	    	Barcode			 = "";
	    } 
		 
	}
	
	//ST_VATDetail
	public static class ST_VATDetail
	{ 
		public long u32VAT;				/**< Total Tax in TL with precition 2 */
		public long u32Amount; 			/**< Total Amount in TL with precition 2 */
		public int u16VATPercentage;	/**< Tax rate, it is 1800 for %18 */
		  
	    public ST_VATDetail()
	    {
	    	u32VAT	     			 = 0;
	    	u32Amount		 		 = 0;
	    	u16VATPercentage		 = 0;  
	    }  
	}
	

	//ST_printerDataForOneLine
	public static class ST_printerDataForOneLine
	{ 
		public long    Flag; 
		public byte   lineLen; 
		public String line; 
		 
	    
	    public ST_printerDataForOneLine()
	    {
	    	Flag	     = 0;
	    	lineLen		 = 0;
	    	line		 = "";  
	    } 
		 
	}
  	
	
	//ST_printerDataForOneLine
	public static class promotion 
	{
		
			public byte   type; 
			public long    amount; 
			public String ticketMsg; 
		 
	    
	    public promotion()
	    {
	    	type	     = 0;
	    	amount		 = 0;
	    	ticketMsg	 = "";
	    }   
	    
	}
	
	//ST_printerDataForOneLine
	public static class ST_ITEM
	{ 
        public byte type;
        public byte subType;
        public byte deptIndex;
        public byte unitType; 
        public long amount; 
        public int currency; 
        public long count; 
        public long flag;
        public byte countPrecition; 
        public byte pluPriceIndex;		// PLU may have multiple prices in Database. This is the index of price to be used 
        public String name; 
        public String barcode;
        public String firm;					
        public String invoiceNo;		
        public String subscriberId;		
        public String tckno;			
    	public long  date;							 
    	public promotion promotion;
		 
	    
	    public ST_ITEM()
	    {
	    	type	     = 0;
	    	subType		 = 0;
	    	deptIndex	 = 0;
	    	unitType	 = 0;
	    	amount		 = 0;
	    	currency	 = 0;
	    	count		 = 0;
	    	flag 		 =0;
	    	countPrecition= 0;
	    	pluPriceIndex = 0;
	    	name		 = "";
	    	barcode		 = "";
	    	firm		 = "";
	    	invoiceNo	 = "";
	    	subscriberId = "";
	    	tckno		 = "";
	    	promotion 	 = new promotion();
	    }
	    
	    public void set(ST_ITEM inStItem)
	    {
	    	type	     	= inStItem.type	     	    ;
	    	subType		 	= inStItem.subType		    ;
	    	deptIndex	 	= inStItem.deptIndex	    ;
	    	unitType	 	= inStItem.unitType	 	    ;
	    	amount		 	= inStItem.amount		    ;
	    	currency	 	= inStItem.currency	 	    ;
	    	count		 	= inStItem.count		    ;
	    	flag 			= inStItem.flag			    ;
	    	countPrecition	= inStItem.countPrecition 	; 	
	    	pluPriceIndex 	= inStItem.pluPriceIndex  	; 	
	    	name		 	= inStItem.name		 		;  
	    	barcode		 	= inStItem.barcode		  	; 
	    	firm		 	= inStItem.firm		 		;  
	    	invoiceNo	 	= inStItem.invoiceNo	  	; 
	    	subscriberId 	= inStItem.subscriberId 	;  	
	    	tckno		 	= inStItem.tckno		  	; 
	    	promotion 	 	= inStItem.promotion 	  	; 	    	
	    }
	}
  	 
	
	//ST_TICKET
	public static class ST_TICKET
	{ 
		public long   TransactionFlags;
		public long   OptionFlags;
		public int ZNo;
		public int FNo; 
		public int EJNo;
		public long   TotalReceiptAmount;
		public long   TotalReceiptTax;
		public long   TotalReceiptDiscount;
		public long   TotalReceiptIncrement;
		public long   CashBackAmount;
		public long   TotalReceiptItemCancel;
		public long   TotalReceiptPayment; 
        public long 	 TotalReceiptReversedPayment; 
        public long 	 KasaAvansAmount; 
        public long 	 KasaPaymentAmount;
		public long   invoiceAmount;
		public long   invoiceAmountCurrency;
		public long   KatkiPayiAmount;
		public long   TaxFreeRefund;
		public long   TaxFreeCalculated;
		public byte[]bcdTicketDate;
		public byte[]bcdTicketTime;
		public byte  ticketType;	
		public int totalNumberOfItems;		// bütün itemlarýn toplam sayýsý (henüz buradaki buffer'a kopyalanmamýþlar dahil)
		public int numberOfItemsInThis;		// itemlarýn toplam sayýsý (sadece buradaki buffera kopyalananlar)
		public int totalNumberOfPayments;
		public int numberOfPaymentsInThis;		// ödemelerin toplam sayýsý (sadece buradaki buffera kopyalananlar)
		public String TckNo;
		public String invoiceNo;
		public long   invoiceDate;
		public byte invoiceType;
		public long   totalNumberOfPrinterLines;  // bütün printer satýrlarýnýn toplam sayýsý (henüz buradaki buffer'a kopyalanmamýþlar dahil)
		public long   numberOfPrinterLinesInThis; // printer satýrlarýnýn toplam sayýsý (sadece buradaki buffera kopyalananlar)
		public byte[]   uniqueId;
		public SALEINFO[] SaleInfo;
		public ST_PAYMENT[] stPayment;
        public ST_VATDetail[]    stTaxDetails;
		public ST_printerDataForOneLine[] stPrinterCopy; 
		
	    public ST_TICKET()
	    {
	    	TransactionFlags	 = 0;
	    	OptionFlags =0;
	    	ZNo 	 = 0; 
	    	FNo	     = 0;
	    	EJNo     = 0; 
	    	TotalReceiptAmount  	= 0;
	    	TotalReceiptTax	 		= 0;
	    	TotalReceiptDiscount	= 0;
	    	TotalReceiptIncrement	= 0;
	    	CashBackAmount	 		= 0;
	    	TotalReceiptItemCancel	= 0;
	    	TotalReceiptPayment 	= 0;
	    	TotalReceiptReversedPayment = 0;
	    	KasaAvansAmount 			= 0;
	    	KasaPaymentAmount			= 0;
	    	invoiceAmount	 		= 0;
	    	KatkiPayiAmount	 		= 0;
	    	invoiceAmountCurrency   = 0;
	    	TaxFreeRefund	 		= 0;
	    	TaxFreeCalculated		= 0;
	    	bcdTicketDate	 		= new byte[3];
	    	bcdTicketTime	 		= new byte[3];
	    	ticketType				= 0;	
	    	totalNumberOfItems	 	= 0;
	    	numberOfItemsInThis     = 0;
	    	totalNumberOfPayments	= 0;
	    	numberOfPaymentsInThis	= 0;
	    	TckNo 					= "";
	    	invoiceNo 				= "";
	    	invoiceDate				= 0;
	    	invoiceType				= 0;
	    	totalNumberOfPrinterLines = 0;
	    	numberOfPrinterLinesInThis= 0;
	    	uniqueId				  = new byte[24];
	    	SaleInfo  = new SALEINFO [MAX_SALE_INFO]; 
	    	stPayment = new ST_PAYMENT [MAX_PAYMENT];  
	    	stTaxDetails = new  ST_VATDetail[MAX_TAX_DETAIL];
	    	stPrinterCopy = new ST_printerDataForOneLine[MAX_PRINTER_COPY];
	    	
	    }
	    
	    public void set(ST_TICKET inStTicket)
	    {
	    	TransactionFlags			  =  inStTicket.TransactionFlags	 		;
	    	OptionFlags 				  =  inStTicket.OptionFlags 				;
	    	ZNo 	 					  =  inStTicket.ZNo 	 					;
	    	FNo	     					  =  inStTicket.FNo	     					;
	    	EJNo     					  =  inStTicket.EJNo     					;
	    	TotalReceiptAmount  		  =  inStTicket.TotalReceiptAmount  		;
	    	TotalReceiptTax	 			  =  inStTicket.TotalReceiptTax	 			;
	    	TotalReceiptDiscount		  =  inStTicket.TotalReceiptDiscount		;
	    	TotalReceiptIncrement		  =  inStTicket.TotalReceiptIncrement		;
	    	CashBackAmount	 			  =  inStTicket.CashBackAmount	 			;
	    	TotalReceiptItemCancel		  =  inStTicket.TotalReceiptItemCancel		;
	    	TotalReceiptPayment 		  =  inStTicket.TotalReceiptPayment 		;
	    	TotalReceiptReversedPayment   =  inStTicket.TotalReceiptReversedPayment ;
	    	KasaAvansAmount 			  =  inStTicket.KasaAvansAmount 			;
	    	KasaPaymentAmount			  =  inStTicket.KasaPaymentAmount			;
	    	invoiceAmount	 			  =  inStTicket.invoiceAmount	 			;
	    	invoiceAmountCurrency		  =  inStTicket.invoiceAmountCurrency	    ;
	    	KatkiPayiAmount	 			  =  inStTicket.KatkiPayiAmount	 			;
	    	TaxFreeRefund	 			  =  inStTicket.TaxFreeRefund	 			;
	    	TaxFreeCalculated			  =  inStTicket.TaxFreeCalculated	 		;
	    	bcdTicketDate	 			  =  inStTicket.bcdTicketDate	 			;
	    	bcdTicketTime	 			  =  inStTicket.bcdTicketTime	 			;
	    	ticketType					  =  inStTicket.ticketType					;
	    	totalNumberOfItems	 		  =  inStTicket.totalNumberOfItems	 		;
	    	numberOfItemsInThis     	  =  inStTicket.numberOfItemsInThis     	;
	    	totalNumberOfPayments		  =  inStTicket.totalNumberOfPayments		;
	    	numberOfPaymentsInThis		  =  inStTicket.numberOfPaymentsInThis		;
	    	TckNo 						  =  inStTicket.TckNo 						;
	    	invoiceNo 					  =  inStTicket.invoiceNo 					;
	    	invoiceDate					  =  inStTicket.invoiceDate					;
	    	invoiceType					  =  inStTicket.invoiceType					;
	    	totalNumberOfPrinterLines     =  inStTicket.totalNumberOfPrinterLines   ;
	    	numberOfPrinterLinesInThis    =  inStTicket.numberOfPrinterLinesInThis  ;
	    	uniqueId				      =  inStTicket.uniqueId				    ;
	    	SaleInfo  					  =  inStTicket.SaleInfo  					;
	    	stPayment 					  =  inStTicket.stPayment 					;
	    	stTaxDetails 				  =  inStTicket.stTaxDetails 				;
	    	stPrinterCopy 				  =  inStTicket.stPrinterCopy 				;	    	
	    }
	    
	}
	
	//ST_date
	public static class ST_date extends Structure 
	{
		public static class ByReference extends ST_date implements Structure.ByReference {}
	 
		public byte day;			// 1-31
		public byte month;		// 1-12
		public int year;		// 0-99
		 
	    
	    public ST_date()
	    { 
	    	day	 = 0x00;
	    	month= 0x00;
	    	year = 0;
	    }
		protected List getFieldOrder() {
			
			return Arrays.asList(new String[] {"day","month","year"}); 
			
		}
		 
	}
	
	//ST_time
	public static class ST_time extends Structure 
	{
		public static class ByReference extends ST_time implements Structure.ByReference {}
	 
		public byte hour;			// 1-31
		public byte minute;		// 1-12
		public byte second;		// 0-99
		 
	    
	    public ST_time()
	    { 
	    	hour	= 0x00;
	    	minute	= 0x00;
	    	second  = 0;
	    }
		protected List getFieldOrder() {
			
			return Arrays.asList(new String[] {"hour","minute","second"}); 
			
		}
		 
	}
	
    //ST_password
	public static class ST_password extends Structure 
	{
		public static class ByReference extends ST_password implements Structure.ByReference {}
	 
			public byte[] supervisor; 
			public byte[] cashier; 
		 
	    
	    public ST_password()
	    { 
	    	supervisor	 = new byte[12+1];
	    	cashier		 = new byte[12+1];  
	    }
		protected List getFieldOrder() {
			
			return Arrays.asList(new String[] {"supervisor","cashier"}); 
			
		}
		 
	}
	
	//ST_funcLimits
	public static class ST_funcLimits extends Structure 
	{
		public static class ByReference extends ST_funcLimits implements Structure.ByReference {}
	 
			public long ZNo;
			public long FNo;
			public ST_date date;
			public ST_time time; 
		 
	    
	    public ST_funcLimits()
	    { 
	    	ZNo	 = 0;
	    	FNo	 = 0;
	    	date = new ST_date.ByReference();
	    	time = new ST_time.ByReference();
	    	
	    }
		protected List getFieldOrder() {
			
			return Arrays.asList(new String[] {"ZNo","FNo","date","time"}); 
			
		}
	}
	
	public static class ST_FunctionParameters extends Structure 
	{
		public static class ByReference extends ST_FunctionParameters implements Structure.ByReference {}
	
			public long EKUNo;
			public ST_password password;
			public ST_funcLimits start; 
			public ST_funcLimits finish;  
	    
	    public ST_FunctionParameters()
	    {
	    	EKUNo        = 0;
	    	password     = new ST_password.ByReference();
	    	start		 = new ST_funcLimits.ByReference();
	    	finish		 = new ST_funcLimits.ByReference();   
	    	
	    }
		protected List getFieldOrder() {
			
			return Arrays.asList(new String[] {"EKUNo","password","start","finish"});  
			
		}
		 
	}
	
	public int Json_FiscalPrinter_Echo(byte[] Out_pstEcho, int Out_pstEchoLen, int timeoutInMiliseconds);
	public int Json_GMP_StartPairingInit(String pstPairing, byte[] Out_pstPairingResp, int Out_pstPairingRespLen);
	public int Json_FiscalPrinter_ItemSale(String pstItem, byte[] Out_pstItem, int Out_pstItemLen, byte[] Out_pstTicket, int Out_pstTicketLen, int timeoutInMiliseconds);
	public int Json_FiscalPrinter_GetTicket(byte[] Out_pstTicket, int Out_pstTicketLen, int timeoutInMiliseconds);
	public int Json_FiscalPrinter_VoidItem(short index, long ItemCount, byte ItemCountPrecision, byte[] Out_pstTicket, int Out_pstTicketLen, int timeoutInMiliseconds);
	public int Json_FiscalPrinter_VoidPayment(short index, byte[] Out_pstTicket, int Out_pstTicketLen, int timeoutInMiliseconds); // TIMEOUT_CARD_TRANSACTIONS
    public int Json_FiscalPrinter_VoidAll(byte[] Out_pstTicket, int Out_pstTicketLen, int timeoutInMiliseconds);
    public int Json_FiscalPrinter_PrintUserMessage(String stUserMessage, byte[] Out_stUserMessage, int Out_stUserMessageLen, short numberOfMessage, byte[] Out_pstTicket, int Out_pstTicketLen, int timeoutInMiliseconds);
    public int Json_FiscalPrinter_Payment(String stPaymentRequest, byte[] Out_stPaymentRequest, int Out_stPaymentRequestLen, byte[] Out_pstTicket, int Out_pstTicketLen, int timeoutInMiliseconds);//TIMEOUT_CARD_TRANSACTIONS

    public int Json_FiscalPrinter_Plus(int amount, byte[] Out_pstTicket, int Out_pstTicketLen, short indexOfItem, int timeoutInMiliseconds);
    public int Json_FiscalPrinter_Minus(int amount, byte[] Out_pstTicket, int Out_pstTicketLen, short indexOfItem, int timeoutInMiliseconds);
    public int Json_FiscalPrinter_Inc(byte rate, byte[] Out_pstTicket, int Out_pstTicketLen, short indexOfItem, IntByReference pchangedAmount, int timeoutInMiliseconds);
    public int Json_FiscalPrinter_Dec(byte rate, byte[] Out_pstTicket, int Out_pstTicketLen, short indexOfItem, IntByReference pchangedAmount, int timeoutInMiliseconds);
    public int Json_FiscalPrinter_GetTaxRates(IntByReference pnumberOfTotalRecords, IntByReference pnumberOfTotalRecordsReceived, String pstTaxRate, byte[] Out_pstTaxRate, int Out_pstTaxRateLen, int numberOfRecordsRequested);
    public int Json_FiscalPrinter_GetDepartments(IntByReference pnumberOfTotalDepartments, IntByReference pnumberOfTotalDepartmentsReceived, String pstDepartments, byte[] Out_pstDepartments, int json_Out_stDepartmentsLen, int numberOfDepartmentRequested);
    public int Json_FiscalPrinter_GetExchangeTable(IntByReference pnumberOfTotalRecords, IntByReference pnumberOfTotalRecordsReceived, String pstExchange, byte[] Out_pstExchange, int Out_pstDepartmentsLen, int numberOfRecordsRequested);
    public int Json_FiscalPrinter_GetPaymentApplicationInfo(ByteByReference pnumberOfTotalRecords, ByteByReference pnumberOfTotalRecordsReceived, String pstExchange, byte[] Out_pstExchange, int Out_pstExchangeLen, byte numberOfRecordsRequested);

    
            
    public int  FiscalPrinter_PaymentCash(int amount, short currency, ST_TICKET pstTicket, int timeoutInMiliseconds);
    public long FiscalPrinter_GetHandle();
    public int  FiscalPrinter_Start(byte[] uniqueId, int lengthOfUniqueId, byte[] uniqueIdSign, int lengthOfUniqueIdSign, byte[] userData, int lengthOfUserData, int timeoutInMiliseconds);
    public int FiscalPrinter_TicketHeader(int ticketType, int timeoutInMiliseconds); 
    //public int FiscalPrinter_GetTicket( ST_TICKET.ByReference pstTicket, int timeoutInMiliseconds);
    public int FiscalPrinter_Close(int timeoutInMiliseconds);
    //public int FiscalPrinter_VoidAll(ST_TICKET pstTicket, int timeoutInMiliseconds);
    //public int FiscalPrinter_ItemSale(ST_ITEM.ByReference pstItem, ST_TICKET.ByReference pstTicket, int timeoutInMiliseconds);
    public int FiscalPrinter_PrintTotalsAndPayments(int timeoutInMiliseconds);
    public int FiscalPrinter_PrintBeforeMF(int timeoutInMiliseconds);
    //public int FiscalPrinter_PrintUserMessage(ST_USER_MESSAGE[] stUserMessage, short numberOfMessage, ST_TICKET pstTicket, int timeoutInMiliseconds);
    public int FiscalPrinter_PrintTMF(int timeoutInMiliseconds);
    
    //public int FiscalPrinter_GetTaxRates( IntByReference pnumberOfTotalRecords, IntByReference pnumberOfTotalRecordsReceived, ST_TaxRate[] pstTaxRate, int numberOfRecordsRequested);
    //public int FiscalPrinter_GetDepartments(IntByReference pnumberOfTotalDepartments, IntByReference pnumberOfTotalDepartmentsReceived, ST_Department[] pstDepartments, int numberOfDepartmentRequested);
    //public int FiscalPrinter_GetExchangeTable(IntByReference pnumberOfTotalRecords, IntByReference pnumberOfTotalRecordsReceived, ST_Exchange[] pstExchange, int numberOfRecordsRequested);
    //public int FiscalPrinter_GetPaymentApplicationInfo(ByteByReference pnumberOfTotalRecords, ByteByReference pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO[] pstExchange, byte numberOfRecordsRequested);
    public int FiscalPrinter_PaymentBankingCard(ST_PAYMENT_REQUEST[] stPaymentRequest, ST_TICKET pstTicket, int timeoutInMiliseconds);
    //public int FiscalPrinter_Payment(ST_PAYMENT_REQUEST[] stPaymentRequest, ST_TICKET pstTicket, int timeoutInMiliseconds);
    //public int FiscalPrinter_VoidItem(short index, ST_TICKET pstTicket, int timeoutInMiliseconds);
    //public int FiscalPrinter_VoidPayment(short index, ST_TICKET pstTicket, int timeoutInMiliseconds);
    /*
    public int FiscalPrinter_Plus (long amount,  ST_TICKET pstTicket, short indexOfItem, int timeoutInMiliseconds);
    public int FiscalPrinter_Minus(long amount,  ST_TICKET pstTicket, short indexOfItem, int timeoutInMiliseconds);
    public int FiscalPrinter_Inc  (byte rate,    ST_TICKET pstTicket, short indexOfItem, IntByReference pchangedAmount, int timeoutInMiliseconds);
    public int FiscalPrinter_Dec  (byte rate,    ST_TICKET pstTicket, short indexOfItem, IntByReference pchangedAmount, int timeoutInMiliseconds);
    */
    public int FiscalPrinter_FunctionOpenDrawer();
    public int FiscalPrinter_FunctionBankingBatch(int timeoutInMiliseconds);
    public int FiscalPrinter_FunctionBankingParameter(int timeoutInMiliseconds);
    public int FiscalPrinter_FunctionEcrParameter(int timeoutInMiliseconds);
    public int FiscalPrinter_FunctionReports(int functionFlags, ST_FunctionParameters.ByReference pstFunctionParameters, int timeoutInMiliseconds);
    // void multTest(multStruct.ByReference mult); 
    public int FiscalPrinter_OptionFlags(LongByReference pflagsActive, long flagsToBeSet, long flagsToBeClear, int timeoutInMiliseconds);
    
    public int prepare_Start(byte[] Buffer, int MaxSize, byte[] uniqueId, int lengthOfUniqueId, byte[] uniqueIdSign, int lengthOfUniqueIdSign, byte[] userData, int lengthOfUserData );
    public int prepare_Payment(byte[] Buffer, int MaxSize, ST_PAYMENT_REQUEST[] stPaymentRequest);
    
    public String GetErrorMessage(int ErrorCode, byte[] Buffer);
    public void SetJavaClassPath(String Path);
}


/* testDll için
public interface GmpDll extends Library 
{	
	public static class multStruct extends Structure 
	{
		public static class ByReference extends multStruct implements Structure.ByReference {}
	
		public int a;
		public int b;
		public int res;
		
		
		protected List getFieldOrder() {
			
			return Arrays.asList(new String[] {"a","b","res"}); 
			
		}
		 
	} 
    
    void multTest(multStruct.ByReference mult); 
}
*/