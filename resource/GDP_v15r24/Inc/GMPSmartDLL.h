/**
*
*! \file	GMPSmartDLL.h
* \brief   defines...
* \n
* \date	10 November 2015
* \note definition will be added later on
* \author
* \copyright Ingenico TR (R&D).
**/

#ifndef __GMPSmartDLL_H__
#define __GMPSmartDLL_H__

#if (!defined(__TELIUM2__) && !defined(__TELIUM3__)) || defined(__TELIUM_LIB__)
/** 1 byte unsigned char*/
#ifndef uint8
#define uint8 unsigned char
#endif

/** 1 byte signed char*/
#ifndef int8
#define int8 char
#endif

/** 2 bytes unsigned char*/
#ifndef uint16
#define uint16 unsigned short
#endif

/** 2 bytes signed char*/
#ifndef int16
#define int16 short
#endif

/** 4 bytes unsigned char*/
#ifndef uint32
#define uint32 unsigned int
#endif

/** 4 bytes signed char*/
#ifndef int32
#define int32 int
#endif

/** 8 bytes unsigned char*/
#ifndef uint64
#define uint64 unsigned long long
#endif

/** 8 bytes signed char*/
#ifndef int64
#define int64 long long
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

/** Returns the smaller of two inputs */
#ifndef MINI
#define MINI(x,y)  				( ((x) < (y)) ? (x) : (y) )
#endif

/** Returns the bigger of two inputs */
#ifndef MAXI
#define MAXI(x,y)  				( ((x) > (y)) ? (x) : (y) )
#endif

#ifndef MIN_MAX
#define MIN_MAX(x,xmin,xmax)	(MINI((xmax), MAXI((x), (xmin))))
#endif
#endif /*(!defined(__TELIUM2__) && !defined(__TELIUM3__)) || defined(__TELIUM_LIB__)*/

#define MAX_BUF_LEN							(24 * 1024)	/**< Main communication buffer in which the data will be received. This size defines the maximum communication length */
#define TEMP_BUF_LEN						(3 * 1024)	/**<  */
#define MIN_VALID_DATA_LEN					14			/**<  */
#define EKU_SEEK_MODE_ALL_TYPE				0xFF		/**<  */

#define	TIMEOUT_DEFAULT						10000		/**< Default timeout for external system communications, 10 seconds */
#define	TIMEOUT_CARD_TRANSACTIONS			60000		/**< Card Transaction timeout, 60 seconds */
#define	TIMEOUT_ECHO						1000		/**< Echo Timeout, 1 seconds */
#define	TIMEOUT_PRINT_MF					20000		/**< mF Timeout, 20 seconds */
#define	TIMEOUT_DATABASE_EXECUTE			20000		/**< Database Timeout, 20 seconds */
#define	TIMEOUT_INFINITIVE					0xFFFFFFFF	/**< Infinitive time out */

#define PARTIAL_PAYMENT_FLAG_MERCHANT		0x01		/**<  */
#define PARTIAL_PAYMENT_FLAG_CUSTOMER		0x02		/**<  */
#define PARTIAL_PAYMENT_FLAG_CANCEL			0x04		/**<  */
#define PARTIAL_PAYMENT_FLAG_CANCEL_SENT	0x08		/**<  */
#define PARTIAL_PAYMENT_FLAG_TERMINAL_SAVED	0x10		/**<  */
#define PAYMENT_FLAG_CREDIT_DONE            0x20   		/**<  */
#define PRE_PARTIAL_PAYMENT_FLAG_CANCEL		0x80		/**<  */

#if !defined(__TELIUM2__) && !defined(__TELIUM3__)
#define STX									0x02		/**< Start Of Message */
#define ETX									0x03		/**< End Of Message */
#endif /*!defined(__TELIUM2__) && !defined(__TELIUM3__)*/
#define EOT									0x04		/**< End of Transaction */
#define ENQ									0x05		/**< Enquery */
#define ACK									0x06		/**< Acknowlegment */
#define BUSY								0x11		/**< Busy */
#define NAK									0x15		/**< */
#define PING								0x57		/**< Ping */

#define TOPOS								0x01		/**< Direction To POS Device */
#define FROMPOS								0x02		/**< Direction From POS Device */
#define RECEIVEDDATALENZERO					0x19		/**<  */
#define ACKNOTFOUND							0x21		/**<  */

#define FS_SEEKSET							0			/*!< seek from start of file */
#define FS_SEEKCUR							1			/*!< seek from current position */
#define FS_SEEKEND							2			/*!< seek from end of file */

#if ((!defined(__TELIUM2__) && !defined(__TELIUM3__)) || defined(GMP_LIB_COMPILE))
#define SQLITE_OK							0 //!< Successful result
#define SQLITE_ERR_INTERNAL					2 //!< Internal logic error
#define SQLITE_ERR_PERM						3 //!< Access permission denied
#define SQLITE_ERR_ABORT					4 //!< Callback routine requested an abort
#define SQLITE_ERR_BUSY						5 //!< The database file is locked
#define SQLITE_ERR_LOCKED					6 //!< A table in the database is locked
#define SQLITE_ERR_NOMEM					7 //!< A malloc() failed
#define SQLITE_ERR_READONLY					8 //!< Attempt to write a readonly database
#define SQLITE_ERR_INTERRUPT				9 //!< Operation terminated by sqlite3_interrupt()
#define SQLITE_ERR_IOERR					10 //!< Some kind of disk I/O error occurred
#define SQLITE_ERR_CORRUPT					11 //!< The database disk image is malformed
#define SQLITE_ERR_NOTFOUND					12 //!< Unknown opcode in SQLITE_file_control()
#define SQLITE_ERR_FULL						13 //!< Insertion failed because database is full
#define SQLITE_ERR_CANTOPEN					14 //!< Unable to open the database file
#define SQLITE_ERR_PROTOCOL					15 //!< Database lock protocol error
#define SQLITE_ERR_EMPTY					16 //!< Database is empty
#define SQLITE_ERR_SCHEMA					17 //!< The database schema changed
#define SQLITE_ERR_TOOBIG					18 //!< String or BLOB exceeds size limit
#define SQLITE_ERR_CONSTRAINT				19 //!< Abort due to constraint violation
#define SQLITE_ERR_MISMATCH					20 //!< Data type mismatch
#define SQLITE_ERR_MISUSE					21 //!< Library used incorrectly
#define SQLITE_ERR_NOLFS					22 //!< Uses OS features not supported on host
#define SQLITE_ERR_AUTH						23 //!< Authorization denied
#define SQLITE_ERR_FORMAT					24 //!< Auxiliary database format error
#define SQLITE_ERR_RANGE					25 //!< 2nd parameter to SQLITE_bind out of range/
#define SQLITE_ERR_NOTADB					26 //!< File opened that is not a database file
#define SQLITE_ROW							100	//!< SQLITE_step() has another row ready
#define SQLITE_DONE							101	//!< SQLITE_step() has finished executing
#endif /*((!defined(__TELIUM2__) && !defined(__TELIUM3__)) || defined(GMP_LIB_COMPILE))*/

#define TRAN_STATUS_FREE					1	/**< Transaction is still pending (on this MasterECR) and not transfered to ClientECR yet. */
#define TRAN_STATUS_RESERVED				2   /**< Transaction is transfered to the ClientECR but no SAVE status received yet. The status is set to RESERVED which will expire on TRAN_STATUS_RESERVATION_DATETIME. When it expires, the status is again set to FREE. */
#define TRAN_STATUS_SAVED					3	/**< Transaction is securely saved into the ClientECR. */
#define TRAN_STATUS_VOIDED					4	/**< Transation is VOIDED on ClientECR. */
#define TRAN_STATUS_COMPLETED				5	/**< Transation is completed on ClientECR. */


/**
\brief Set of sub message ids used for FP3_Function
\n
*/
enum
{
	GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE				= 0x00000001,		/**< used for downloading parameter*/
	GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR       			, // 0x00000002		/**< used for performing Z Report */
	GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR					, // 0x00000003		/**< used for performing X Report */
	GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR				, // 0x00000004		/**< used for performing Fiscal Report */
	GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR				, // 0x00000005		/**< used for performing EKU Report */
	GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF			, // 0x00000006		/**< used for performing Fiscal Cumulative Report */
	GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER			, // 0x00000007		/**< used for getting soft copy of Z Report */
	GMP_EXT_DEVICE_FUNC_BIT_KASIYER_SEC				, // 0x00000008		/**< used for selecting cashier */
	GMP_EXT_DEVICE_FUNC_BIT_KASIYER_LOGOUT			, // 0x00000009		/**< used for logging out of cashier */
	GMP_EXT_DEVICE_FUNC_BIT_AVANS					, // 0x0000000A		/**< used for advance */
	GMP_EXT_DEVICE_FUNC_BIT_ODEME					, // 0x0000000B		/**< used for reverse payment */
	GMP_EXT_DEVICE_FUNC_BIT_CEKMECE_ACMA			, // 0x0000000C		/**< used for open drawer */
	GMP_EXT_DEVICE_FUNC_READ_CARD					, // 0x0000000D		/**< used for reading card properties*/
	GMP_EXT_DEVICE_FUNC_GET_CARD_PUAN				, // 0x0000000E		/**< used for getting card point */
	GMP_EXT_DEVICE_FUNC_BIT_BANKA_GUN_SONU			, // 0x0000000F		/**< used for performing banking settlement*/
	GMP_EXT_DEVICE_FUNC_BIT_BANKA_PARAM_YUKLE		, // 0x00000010		/**< used for downloading banking parameter */
	GMP_EXT_DEVICE_FUNC_BANKA_IADE					, // 0x00000011		/**< used for Banking Refund. After that ECR won't print any ticket. Printed ticket will be just banking slip */
	GMP_EXT_DEVICE_FUNC_GET_UNIQUE_ID_LIST			, // 0x00000012		/**< used for getting Unique IDs from ECR*/
	GMP_EXT_DEVICE_FUNC_EKU_RAPOR_SON_FIS_KOPYA     , // 0x00000013		/**< used for getting last copy of ticket in EKU */
	GMP_EXT_DEVICE_FUNC_EKU_RAPOR_SON_KOPYA       	, // 0x00000014		/**< used for getting last copy in EKU */
	GMP_EXT_DEVICE_FUNC_EKU_RAPOR_IKI_Z_ARASI       , // 0x00000015		/**< used for getting EKU report between 2 Z Report*/
	GMP_EXT_DEVICE_FUNC_EKU_RAPOR_IKI_TARIH_ARASI   , // 0x00000016		/**< used for getting EKU report between 2 date */
	GMP_EXT_DEVICE_FUNC_EKU_RAPOR_FISTEN_FISE       , // 0x00000017		/**< used for getting EKU report ticket to ticket */
	GMP_EXT_DEVICE_FUNC_EKU_RAPOR_Z_KOPYA       	, // 0x00000018		/**< used for getting Z Report Copy */
	GMP_EXT_DEVICE_FUNC_EKU_RAPOR_DETAIL       	    , // 0x00000019		/**< used for getting EKU report details */
	GMP_EXT_DEVICE_FUNC_EKU_RAPOR_SUMMARY      	    , // 0x0000001A		/**< used for getting EKU report summary */
	GMP_EXT_DEVICE_FUNC_CHANGE_RECEIPT_HEADER  	    , // 0x0000001B		/**< used for changing receipt header */
	GMP_EXT_DEVICE_FUNC_BANKA_IPTAL		   			, // 0x0000001C		/**< used for Banking Void. After that ECR won't print any ticket. Printed ticket will be just banking slip */
	GMP_EXT_DEVICE_FUNC_KASIYER_TANIMLA             , // 0x0000001D		/**< used for define cashier */
	GMP_EXT_DEVICE_FUNC_TRANS_INQUERY	            , // 0x0000001E		/**< used for transaction inquery */
	GMP_EXT_DEVICE_FUNC_TRANS_STATUS				, // 0x0000001F
	GMP_EXT_DEVICE_FUNC_CREATE_UNIQUE_ID            , // 0x00000020
	GMP_EXT_DEVICE_FUNC_LOAD_BACKGROUND_TO_FRONT    , // 0x00000021
	GMP_EXT_DEVICE_FUNC_LOYALTY_IDENTIFICATION		, // 0x00000022
	GMP_EXT_DEVICE_FUNC_GET_INVOICE_INFO			, // 0x00000023
	GMP_EXT_DEVICE_FUNC_PAYMENT_VAS_IPTAL	    	, // 0x00000024
	GMP_EXT_DEVICE_FUNC_CHECK_PAYMENT_STATUS		, // 0x00000025
	GMP_EXT_DEVICE_FUNC_BIT_AYLIK_RAPOR_GONDER		= 0x000000026,

};

/**
\brief Sub commands which are used to access EKU
\n
*/
#define GMP_EXT_DEVICE_FUNC_EKU_PING			0xEC01
#define GMP_EXT_DEVICE_FUNC_EKU_READ_INFO		0xEC03
#define GMP_EXT_DEVICE_FUNC_EKU_SEEK			0xEF43
#define GMP_EXT_DEVICE_FUNC_EKU_READ_DATA		0xEF44
#define GMP_EXT_DEVICE_FUNC_EKU_READ_HEADER		0xEF47

/** EConditionGoto */
typedef enum
{
	CONDITION_GOTO_NEXT 		= 0,				/**< Goto Next Command */
	CONDITION_GOTO_PRIVOUS		= 0xFFFD,			/**< Goto Privous Command */
	CONDITION_GOTO_LAST			= 0xFFFE,			/**< Goto Last Command */
	CONDITION_GOTO_END 			= 0xFFFF,			/**< Goto End of Command List */
} EConditionGoto;

/** Option Flags for GMP3 */
#define GMP3_OPTION_ECHO_PRINTER									(1 << 0)	/**< ECR will echo each printer line after Ticket header and Ticket Totals. It may be used to show the lines on external system display */
#define GMP3_OPTION_ECHO_PAYMENT_DETAILS							(1 << 1)	/**< ECR will echo payment structure(s) in details */
#define GMP3_OPTION_ECHO_ITEM_DETAILS								(1 << 2)	/**< ECR will echo item structure(s) in details */
#define GMP3_OPTION_NO_RECEIPT_LIMIT_CONTROL_FOR_ITEMS				(1 << 3)	/**< ECR will not control the Receipt amount until payment process */
#define GMP3_OPTION_DONOT_CONTROL_PAYMENTS_FOR_RECEIPT_CANCEL		(1 << 4)	/**< ECR will not control the banking payment before receipt cancellation */
#define GMP3_OPTION_GET_CONFIRMATION_FOR_PAYMENT_CANCEL				(1 << 5)	/**< ECR will sent the confirmation message to the external application to cancel the payment*/
#define GMP3_OPTION_ECHO_LOYALTY_DETAILS							(1 << 6)	/**< ECR will echo loyalty structure(s) in details */
#define GMP3_OPTION_DONT_PRINT_MERCHANT_SLIPS						(1 << 9)	/**< ECR will not allow to print merchant slip if customer signature is not required */

#define GMP3_STATE_BIT_PAIRED					(1 << 0)
#define GMP3_STATE_BIT_KEY_EXPIRED				(1 << 1)
#define GMP3_STATE_BIT_FISCALIZED				(1 << 2)
#define GMP3_STATE_BIT_OKC_MALI_MOD				(1 << 3)
#define GMP3_STATE_BIT_PARAMETRE				(1 << 4)
#define GMP3_STATE_BIT_NO_PAPER					(1 << 5)
#define GMP3_STATE_BIT_ECHO_REQ					(1 << 6)

// Printer option definition
#define GMP3_PS_24                             (     0)
#define GMP3_PS_12                             (1 << 0)
#define GMP3_PS_32                             (1 << 1)
#define GMP3_PS_48                             (1 << 2)
#define GMP3_PS_BOLD                           (1 << 3)
#define GMP3_PS_CENTER                         (1 << 4)
#define GMP3_PS_RIGHT                          (1 << 5)
#define GMP3_PS_INVERTED                       (1 << 6)
#define GMP3_PS_UNIQUE_ID                      (1 << 7)
#define GMP3_PS_BARCODE                        (1 << 8)
#define GMP3_PS_ECR_TICKET_HEADER              (1 << 9)
#define GMP3_PS_GRAPHIC                        (1 << 10)
#define GMP3_PS_QRCODE                         (1 << 11)
#define GMP3_PS_16                             (1 << 12)
#define GMP3_PS_38                             (1 << 13)
//#define GMP3_PS_ECR_TICKET_ITEM              (1 << 14)  // DONT USE
//#define GMP3_PS_NO_BOS                       (1 << 15)
#define GMP3_PS_ECR_TICKET_ITEM                (1 << 16)
#define GMP3_PS_ECR_TICKET_COPY                (1 << 17)	/**< DO NOT use in External Systems !! */
#define GMP3_PS_ECR_USER_MSG_BEFORE_HEADER     (1 << 18)	/**< DO NOT use in External Systems !! */
#define GMP3_PS_ECR_USER_MSG_AFTER_TOTALS      (1 << 19)	/**< DO NOT use in External Systems !! */
#define GMP3_PS_ECR_USER_MSG_BEFORE_MF         (1 << 20)	/**< DO NOT use in External Systems !! */
#define GMP3_PS_ECR_USER_MSG_AFTER_MF          (1 << 21)	/**< DO NOT use in External Systems !! */
#define GMP3_PS_NO_PAPER_CHECK                 (1 << 22)	/**< DO NOT use in External Systems !! */
#define GMP3_PS_FEED_LINE                      (1 << 23)	/**< Option to feed string with '-' characters to fit in one line in the current font */
//#if !defined(__TELIUM2__) && !defined(__TELIUM3__)
//#define PS_24                             		GMP3_PS_24
//#define PS_12                             		GMP3_PS_12
//#define PS_32                             		GMP3_PS_32
//#define PS_48                             		GMP3_PS_48
//#define PS_BOLD                           		GMP3_PS_BOLD
//#define PS_CENTER                         		GMP3_PS_CENTER
//#define PS_RIGHT                          		GMP3_PS_RIGHT
//#define PS_INVERTED                       		GMP3_PS_INVERTED
//#define PS_UNIQUE_ID                      		GMP3_PS_UNIQUE_ID
//#define PS_BARCODE                        		GMP3_PS_BARCODE
//#define PS_ECR_TICKET_HEADER              		GMP3_PS_ECR_TICKET_HEADER
//#define PS_GRAPHIC                        		GMP3_PS_GRAPHIC
//#define PS_QRCODE                         		GMP3_PS_QRCODE
//#define PS_16                             		GMP3_PS_16
//#define PS_38                             		GMP3_PS_38
//#define PS_ECR_TICKET_ITEM                		GMP3_PS_ECR_TICKET_ITEM
//#define PS_ECR_TICKET_COPY                		GMP3_PS_ECR_TICKET_COPY
//#define PS_ECR_USER_MSG_BEFORE_HEADER     		GMP3_PS_ECR_USER_MSG_BEFORE_HEADER
//#define PS_ECR_USER_MSG_AFTER_TOTALS      		GMP3_PS_ECR_USER_MSG_AFTER_TOTALS
//#define PS_ECR_USER_MSG_BEFORE_MF         		GMP3_PS_ECR_USER_MSG_BEFORE_MF
//#define PS_ECR_USER_MSG_AFTER_MF          		GMP3_PS_ECR_USER_MSG_AFTER_MF
//#define PS_NO_PAPER_CHECK                 		GMP3_PS_NO_PAPER_CHECK
//#define PS_FEED_LINE                      		GMP3_PS_FEED_LINE
//#endif /*!defined(__TELIUM2__) && !defined(__TELIUM3__)*/

#define SUPPORT_COMPRESSION_V1					 (1 << 0)		/**< support of compression V1 type */

/** Pairing functions */
#define RESPONSE								0x000400
#define COMPRESSED_V1							0x001000
#define ENCRYPTED								0x000100

#define GMP3_TAG_INIT_MSG_REQ					0xFF8A60												/**< Request Msg Id for INIT */
#define GMP3_TAG_KEY_MSG_REQ					0xFF8A62												/**< Request Msg Id for KEY */
#define GMP3_TAG_CLOSE_MSG_REQ					0xFF8A63												/**< Request Msg Id for CLOSE */
#define GMP3_EXT_DEVICE_ECHO_REQ				0xFF8A64												/**< Request Msg Id for ECHO */
#define GMP3_EXT_DEVICE_GET_DATA_REQ			0xFF8A80												/**< Request Msg Id for GET DATA */
#define GMP3_EXT_DEVICE_SET_DATA_REQ			0xFF8A81												/**< Request Msg Id for SET DATA */
#define GMP3_EXT_DEVICE_FUNC_REQ				0xFF8A83												/**< Request Msg Id for FUNCTION */
#define GMP3_EXT_DEVICE_MASTER_OKC_REQ			0xFF8A84												/**< Request Msg Id for MASTER OKC */
#define GMP3_FISCAL_PRINTER_MODE_REQ 			0xFF8A89												/**< Request Msg Id for FISCAL PRINTER */
#define GMP3_DATABASE_REQ						0xFF8A8A												/**< Request Msg Id for DATABASE */
#define GMP3_FILESYSTEM_REQ						0xFF8A8B												/**< Request Msg Id for FILE SYSTEM */
#define GMP3_TAG_VALIDATE_MSG_REQ				0xFF8A8C												/**< Request Msg Id for VALIDATE */
#define GMP3_EXT_DEVICE_PP_PROCESS_REQ			0xFF8A94												/**< Request Msg Id for PP  */
#define GMP3_EXT_DEVICE_STUNNEL_QUERY_REQ		0xFF8A90												/**< Request Msg Id for STUNNEL */

#define GMP3_TAG_INIT_MSG_RES					(GMP3_TAG_INIT_MSG_REQ|RESPONSE)						/**< Response Msg Id of the relevant REQ messge */
#define GMP3_TAG_KEY_MSG_RES					(GMP3_TAG_KEY_MSG_REQ|RESPONSE)							/**< Response Msg Id of the relevant REQ messge */
#define GMP3_TAG_CLOSE_MSG_RES					(GMP3_TAG_CLOSE_MSG_REQ|RESPONSE)						/**< Response Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_ECHO_RES				(GMP3_EXT_DEVICE_ECHO_REQ|RESPONSE)						/**< Response Msg Id of the relevant REQ messge */
#define GMP3_TAG_VALIDATE_MSG_RES				(GMP3_TAG_VALIDATE_MSG_REQ|RESPONSE)					/**< Response Msg Id of the relevant REQ messge */

#define GMP3_EXT_DEVICE_GET_DATA_REQ_E			(GMP3_EXT_DEVICE_GET_DATA_REQ|ENCRYPTED)				/**< Encrypted Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_GET_DATA_RES			(GMP3_EXT_DEVICE_GET_DATA_REQ|RESPONSE)					/**< Response Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_GET_DATA_RES_E			(GMP3_EXT_DEVICE_GET_DATA_REQ|RESPONSE|ENCRYPTED)		/**< Encrypted Msg Id of the relevant RES messge */

#define GMP3_EXT_DEVICE_SET_DATA_REQ_E			(GMP3_EXT_DEVICE_SET_DATA_REQ|ENCRYPTED)				/**< Encrypted Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_SET_DATA_RES			(GMP3_EXT_DEVICE_SET_DATA_REQ|RESPONSE)					/**< Response Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_SET_DATA_RES_E			(GMP3_EXT_DEVICE_SET_DATA_REQ|RESPONSE|ENCRYPTED)		/**< Encrypted Msg Id of the relevant RES messge */

#define GMP3_EXT_DEVICE_MASTER_OKC_REQ_E		(GMP3_EXT_DEVICE_MASTER_OKC_REQ|ENCRYPTED)				/**< Encrypted Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_MASTER_OKC_RES			(GMP3_EXT_DEVICE_MASTER_OKC_REQ|RESPONSE)					/**< Response Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_MASTER_OKC_RES_E		(GMP3_EXT_DEVICE_MASTER_OKC_REQ|RESPONSE|ENCRYPTED)		/**< Encrypted Msg Id of the relevant RES messge */

#define GMP3_EXT_DEVICE_FUNC_REQ_E				(GMP3_EXT_DEVICE_FUNC_REQ|ENCRYPTED)					/**< Encrypted Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_FUNC_RES				(GMP3_EXT_DEVICE_FUNC_REQ|RESPONSE)						/**< Response Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_FUNC_RES_E				(GMP3_EXT_DEVICE_FUNC_REQ|RESPONSE|ENCRYPTED)			/**< Encrypted Msg Id of the relevant RES messge */

#define GMP3_FISCAL_PRINTER_MODE_REQ_E 			(GMP3_FISCAL_PRINTER_MODE_REQ|ENCRYPTED)				/**< Encrypted Msg Id of the relevant REQ messge */
//#define GMP3_FISCAL_PRINTER_MODE_REQ 			(GMP3_FISCAL_PRINTER_MODE_REQ)							/**< NOT Encrypted Msg Id of the relevant REQ messge */
#define GMP3_FISCAL_PRINTER_MODE_RES			(GMP3_FISCAL_PRINTER_MODE_REQ|RESPONSE)					/**< Response Msg Id of the relevant REQ messge */
#define GMP3_FISCAL_PRINTER_MODE_RES_E			(GMP3_FISCAL_PRINTER_MODE_REQ|RESPONSE|ENCRYPTED)		/**< Encrypted Msg Id of the relevant RES messge */

#define GMP3_DATABASE_REQ_E 					(GMP3_DATABASE_REQ|ENCRYPTED)							/**< Encrypted Msg Id of the relevant REQ messge */
#define GMP3_DATABASE_RES						(GMP3_DATABASE_REQ|RESPONSE)							/**< Response Msg Id of the relevant REQ messge */
#define GMP3_DATABASE_RES_E						(GMP3_DATABASE_REQ|RESPONSE|ENCRYPTED)					/**< Encrypted Msg Id of the relevant RES messge */

#define GMP3_FILESYSTEM_REQ_E 					(GMP3_FILESYSTEM_REQ|ENCRYPTED)							/**< Encrypted Msg Id of the relevant REQ messge */
#define GMP3_FILESYSTEM_RES						(GMP3_FILESYSTEM_REQ|RESPONSE)							/**< Response Msg Id of the relevant REQ messge */
#define GMP3_FILESYSTEM_RES_E					(GMP3_FILESYSTEM_REQ|RESPONSE|ENCRYPTED)				/**< Encrypted Msg Id of the relevant RES messge */

#define GMP3_EXT_DEVICE_PP_PROCESS_REQ_E		(GMP3_EXT_DEVICE_PP_PROCESS_REQ|ENCRYPTED)				/**< Encrypted Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_PP_PROCESS_RES			(GMP3_EXT_DEVICE_PP_PROCESS_REQ|RESPONSE)				/**< Response Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_PP_PROCESS_RES_E		(GMP3_EXT_DEVICE_PP_PROCESS_REQ|RESPONSE|ENCRYPTED)		/**< Encrypted Msg Id of the relevant RES messge */

#define GMP3_EXT_DEVICE_STUNNEL_QUERY_RES		(GMP3_EXT_DEVICE_STUNNEL_QUERY_REQ|ENCRYPTED)			/**< Encrypted Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_STUNNEL_DATA_REQ		(GMP3_EXT_DEVICE_STUNNEL_QUERY_REQ|RESPONSE)			/**< Response Msg Id of the relevant REQ messge */
#define GMP3_EXT_DEVICE_STUNNEL_DATA_RES		(GMP3_EXT_DEVICE_STUNNEL_QUERY_REQ|RESPONSE|ENCRYPTED)	/**< Encrypted Msg Id of the relevant RES messge */


//Invoice Settings...
#define FLAG_SETTING_DISABLE_FATURA     (1<<0)
#define FLAG_SETTING_ENABLE_IRSALIYE    (1<<1)

//Z settings...
#define FLAG_PROCESS_24_HOURS_EVENT     0x01
#define FLAG_AUTO_Z_PROCESSED_THIS_DAY  0x02
#define FLAG_AUTO_Z_DISABLE             0x04

// Jump Flags for GMP3
#define GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT				(1 << 1)	/**< Jump Command will from from ECR after one payment attempt. Payment result may be successfull or not */
#define GMP3_OPTION_RETURN_AFTER_COMPLETE_PAYMENT			(1 << 2)	/**< Jump Command will from from ECR after all payment totals is equal or greater than ticket total */
#define GMP3_OPTION_DONT_ALLOW_NEW_ITEM						(1 << 3)	/**< ECR will not allow new item entry during Jump command */
#define GMP3_OPTION_DONT_ALLOW_VOID_ITEM					(1 << 4)	/**< ECR will not allow to void an item  during Jump command */
#define GMP3_OPTION_DONT_ALLOW_VOID_PAYMENT					(1 << 5)	/**< ECR will not allow to void a payment during Jump command */
#define GMP3_OPTION_CONTINUE_IN_OFFLINE_MODE				(1 << 6)	/**< Valid only for GMP_SOURCE_TYPE_TSM transactions. ECR will break the Comm link to TSM Gateway and the transaction will continue in offline mode. Transaction result will be sent to TSM after it is completed */
#define GMP3_OPTION_DONT_SEND_TRANSACTION_RESULT			(1 << 7)	/**< Valid only for GMP_SOURCE_TYPE_TSM transactions. By default, if the Comm link is broken for any reason, the transaction result will be sent to TSM after it is completed. This option disables this feature  */

#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_TL			(1 << 17)	/**< ECR will not allow new payment (CASH TL) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_EXCHANGE	(1 << 18)	/**< ECR will not allow new payment (CASH EXCHANGE) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_BANKCARD			(1 << 19)	/**< ECR will not allow new payment (BANCCARD) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_YEMEKCEKI		(1 << 20)	/**< ECR will not allow new payment (YEMEKCEKI-TICKETING CARD) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_MOBILE			(1 << 21)	/**< ECR will not allow new payment (MOBILE) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_HEDIYECEKI		(1 << 22)	/**< ECR will not allow new payment (HEDIYECEKI-GIFT CARD) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_IKRAM			(1 << 23)	/**< ECR will not allow new payment (IKRAM-FREE OFFER) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ODEMESIZ			(1 << 24)	/**< ECR will not allow new payment (ODEMESIZ-FROUD) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_KAPORA			(1 << 25)	/**< ECR will not allow new payment (KAPORA-PRE PAYMENT) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_PUAN				(1 << 26)	/**< ECR will not allow new payment (PUAN-BONUS) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CEK				(1 << 27)	/**< ECR will not allow new payment (CEK) entry durung Jump command */
#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ACIK_HESAP		(1 << 27)	/**< ECR will not allow new payment (SALE ON ACCOUNT) entry durung Jump command */

#define GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT					(GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_TL|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_EXCHANGE|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_BANKCARD|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_YEMEKCEKI|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_MOBILE|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_HEDIYECEKI|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_IKRAM|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ACIK_HESAP|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CEK|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ODEMESIZ|GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_KAPORA| GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_PUAN) 	/**< ECR will not allow new payment (ANY) entry durung Jump command */

#define GMP3_STATE_BIT_PAIRED								(1 << 0)	/**< Already Pired Device (Does not mean paired with this particular external system!) */
#define GMP3_STATE_BIT_KEY_EXPIRED							(1 << 1)	/**< Pairing Key Expired, need to re-pair again */
#define GMP3_STATE_BIT_FISCALIZED							(1 << 2)	/**< ECR device is already fiscalized device (Does not mean that ECR in fiscal mode right now. It may be on service mode!) */
#define GMP3_STATE_BIT_OKC_MALI_MOD							(1 << 3)	/**< ECR device is in fiscal mode, ready to fiscal ticket */
#define GMP3_STATE_BIT_PARAMETRE							(1 << 4)	/**< ECR has parameter from TSM */
#define GMP3_STATE_BIT_NO_PAPER								(1 << 5)	/**< ECR has no paper */


/** Fiscal Printer Sub commands */
typedef enum
{
	GMP3_SUBCOMMAND_FISCALPRINTER_STATUS						=   0x0000,
	GMP3_SUBCOMMAND_FISCALPRINTER_START							, //0x0001
	GMP3_SUBCOMMAND_FISCALPRINTER_TICKETHEADER					, //0x0002
	GMP3_SUBCOMMAND_FISCALPRINTER_TICKETITEM					, //0x0003
	GMP3_SUBCOMMAND_FISCALPRINTER_SETINVOICE					, //0x0004
	GMP3_SUBCOMMAND_FISCALPRINTER_PAYMENT						, //0x0005
	GMP3_SUBCOMMAND_FISCALPRINTER_TICKETFOOTER					, //0x0006
	GMP3_SUBCOMMAND_FISCALPRINTER_CLOSE							, //0x0007
	GMP3_SUBCOMMAND_FISCALPRINTER_MATRAHSIZ						, //0x0008
	GMP3_SUBCOMMAND_FISCALPRINTER_ADVANCEPAYMENT				, //0x0009
	GMP3_SUBCOMMAND_FISCALPRINTER_PRETOTAL						, //0x000A
	GMP3_SUBCOMMAND_FISCALPRINTER_DISPLAYPAYMENTSUMMARY 		, //0x000B
	GMP3_SUBCOMMAND_FISCALPRINTER_PLUSMINUS						, //0x000C
	GMP3_SUBCOMMAND_FISCALPRINTER_INCDEC						, //0x000D
	GMP3_SUBCOMMAND_FISCALPRINTER_VOIDPAYMENT					, //0x000E
	GMP3_SUBCOMMAND_FISCALPRINTER_VOIDALL						, //0x000F
	GMP3_SUBCOMMAND_FISCALPRINTER_VOIDMATRAHSIZ_DONT_USE		, //0x0010
	GMP3_SUBCOMMAND_FISCALPRINTER_VOIDITEM						, //0x0011
	GMP3_SUBCOMMAND_FISCALPRINTER_DO_NOT_USE					, //0x0012
	GMP3_SUBCOMMAND_FISCALPRINTER_USER_MESSAGE					, //0x0013
	GMP3_SUBCOMMAND_FISCALPRINTER_PRINT_TOTALS_AND_PAYMENTS		, //0x0014
	GMP3_SUBCOMMAND_FISCALPRINTER_PRINT_BEFORE_MF				, //0x0015
	GMP3_SUBCOMMAND_FISCALPRINTER_PRINT_MF						, //0x0016
	GMP3_SUBCOMMAND_FISCALPRINTER_SETPARKINGTICKET				, //0x0017
	GMP3_SUBCOMMAND_FISCALPRINTER_REVERSE_PAYMENT				, //0x0018
	GMP3_SUBCOMMAND_FISCALPRINTER_OPTION_FLAGS					, //0x0019
	GMP3_SUBCOMMAND_FISCALPRINTER_JUMP_TO_ECR					, //0x001A
	GMP3_SUBCOMMAND_FISCALPRINTER_CONDITION						, //0x001B
	GMP3_SUBCOMMAND_FISCALPRINTER_SET_TAXFREE					, //0x001C
	GMP3_SUBCOMMAND_FISCALPRINTER_SET_TAXREFUND_AMOUNT			, //0x001D
	GMP3_SUBCOMMAND_FISCALPRINTER_PRINT_PAYMENT_TICKET			, //0x001E
	GMP3_SUBCOMMAND_FISCALPRINTER_SEND_FRONT_STATION_PRINT		, //0x001F

	GMP3_SUBCOMMAND_FISCALPRINTER_SET_ONLINE_INVOICE				= 0x0020,
	GMP3_SUBCOMMAND_FISCALPRINTER_SET_BACKGROUND_USER_DEFINITION	= 0x0021,
	GMP3_SUBCOMMAND_FISCALPRINTER_SET_ONLINE_TAXFREE				= 0x0022,
	GMP3_SUBCOMMAND_FISCALPRINTER_SET_CARI_HESAP_TRANSACTION	    = 0x0023,
	GMP3_SUBCOMMAND_FISCALPRINTER_LOYALTY_CUSTOMER_QUERY			= 0x0024,
	GMP3_SUBCOMMAND_FISCALPRINTER_SET_CURRENCY_PROFILE			    = 0x0025,
	GMP3_SUBCOMMAND_FISCALPRINTER_LOYALTY_PROCESS					= 0x0026,
	GMP3_SUBCOMMAND_FISCALPRINTER_SET_SMM							= 0x0027,
	GMP3_SUBCOMMAND_FISCALPRINTER_SET_GIDER_PUSULASI				= 0x0028,
	GMP3_SUBCOMMAND_FISCALPRINTER_GET_MERCHANT_SLIP					= 0x002A,

	GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_TEXT					=   0x0200,
	GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_DATE					,
	GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_AMOUNT				,
	GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_PASSWORD				,
	GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_MENU					,
	GMP3_SUBCOMMAND_FISCALPRINTER_GETINPUT_MSGBOX				,
	GMP3_SUBCOMMAND_FISCALPRINTER_GET_PLU						=   0x0300,
	GMP3_SUBCOMMAND_FISCALPRINTER_GET_BARCODE					,

	GMP3_SUBCOMMAND_FISCALPRINTER_SET_uAPPLICATION_FUNCTION		=   0x0800,
} EFiscalPrinterSubCommands;

/** TAG values of Groups */
typedef enum
{
	GMP_TAG_GROUP_ISLEM_GRUBU									=   0xDF02,		/**< 0xDF02, Grouping Tag for Precess Group */
	GMP_TAG_GIB_OZEL_VERI_GRUBU									=	0xDF40,
	GMP_TAG_GIB_HARICI_VERI_GRUBU								=	0xDF41,
	GMP_TAG_GIB_VERI_GUVENLIGI_GRUBU							=	0xDF42,
	GMP_TAG_KAMPANYA_VERI_GRUBU									=	0xDF50,
	GMP_TAG_GROUP_AYLIK_RAPOR_VERISI							=	0xDF58,  	/**< 0xDF58, Grouping Tag for Monthly Report Details */
	GMP_TAG_ING_PARAM_VERI_GRUBU								=	0xDF61,
	GMP_TAG_ING_TERMINFO_VERI_GRUBU								=	0xDF62,
	GMP_TAG_LOYALITY_VERI_GRUBU									=   0xDF64,
	GMP_TAG_ING_SER_CARD_VERI_GRUBU								=	0xDF66,
	GMP_TAG_ING_SAM_PUBLIC_CERT									=	0xDF67,
	GMP_TAG_DATA_GROUP											=   0xDF69,		/**< 0xDF69, Grouping Tag for General Porpuse */
	GMP_TAG_ING_PARAM_PCOM										=	0xDF6A,
	GMP_TAG_ING_PARAM_APPLICATION								=	0xDF6B,
	GMP_TAG_ING_PARAM_OKC										=	0xDF6C,
	GMP_TAG_ING_PARAM_IDLE										=	0xDF6D,
	GMP_TAG_BANKACILIK_VERI_GRUBU								=	0xDF6E,
	GMP_TAG_VERI_DOGRULAMA_GRUBU								=	0xDF6F,
	GMP_TAG_ESLESME_GRUBU										=	0xDF6F,
	GMP_TAG_GROUP_VERI_GRUBU									=   0xDF6F,		/**< 0xDF6F, Grouping Tag for Data Group */

	GMP_TAG_GROUP_MONEY_COLLECTION_TABLOSU						=   0xDF71, 	/**< 0xDF71, Grouping Tag for Money collection details */
	GMP_TAG_GROUP_COMMON										,				/**< 0xDF72, Grouping Tag for general porpuses */
	GMP_TAG_GROUP_FISBASLIGI_TABLOSU							, 				/**< 0xDF73, Grouping Tag for Ticket Header Info (Merchant Name & Address ) */
	GMP_TAG_GROUP_TICKET_TABLOSU								, 				/**< 0xDF74, Grouping Tag for Ticket Table */
	GMP_TAG_GROUP_PLU_VERISI									, 				/**< 0xDF75, Grouping Tag for PLU Details */
	GMP_TAG_GROUP_DB_COLOMN_VERISI								, 				/**< 0xDF76, Grouping Tag for Database Coloumns */
	GMP_TAG_GROUP_VERGI_TABLOSU									, 				/**< 0xDF77, Grouping Tag for Tax Table */
	GMP_TAG_GROUP_OKC_KISIM_TABLOSU								, 				/**< 0xDF78, Grouping Tag for Department Table */
	GMP_TAG_GROUP_OKC_DOVIZ_TABLOSU								, 				/**< 0xDF79, Grouping Tag for Exchange Currency Table */
	GMP_TAG_GROUP_ITEM_TABLOSU									, 				/**< 0xDF7A, Grouping Tag for Item */
	GMP_TAG_GROUP_OKC_KASIYER_TABLOSU							, 				/**< 0xDF7B, Grouping Tag for Cashier Table */
	GMP_TAG_GROUP_OKC_ODEME_TABLOSU								, 				/**< 0xDF7C, Grouping Tag for Payment Table */
	GMP_TAG_GROUP_OKC_ASSIST_TABLOSU							, 				/**< 0xDF7D,  */
	GMP_TAG_GROUP_KOMUT_TABLOSU									, 				/**< 0xDF7E,  */
	GMP_TAG_GROUP_ZRAPOR_VERISI									, 				/**< 0xDF7F, Grouping Tag for Z Report Details */
} EGroupTagNames;

typedef enum _GMP_TAG_LIST_EXT_DEVICE
{
	GMP_PROCORDERNUM											= 0xDF8208,		/**< 0xDF8208, (bcd[3]) 000001 den baþlamak üzere, her mesaj için 1 arttýrmak sureti ile tekilliði saðlanan iþlem sýra numarasýdýr. 999999 deðerinden sonra tekrar 000001 deðerine dönülecektir.
																									Ýþlem sýra numarasý Harici Cihaz ve ÖKC tarafýndan ayný þekilde tutulacaktýr. ÖKC’ler birden fazla cihaz için ayrý ayrý kayýt tutacaktýr.
																									Eþleþen cihazlarda kayýtlý iþlem sýra numarasýndan küçük deðerlere sahip paketler kabul edilmeyecektir. */
	GMP_LOCALDATE												= 0xDF8209,		/**< 0xDF8209, (bcd[3]) Date of the transaction as bcd YYMMDD */
	GMP_LOCALTIME												= 0xDF820A,		/**< 0xDF820A, (bcd[3]) Time of the transaction as bcd HHMMSS  */
	GMP_PROCRESPCODE											= 0xDF820D,		/**< 0xDF820D,  */
	GMP_SIGN_VALUE												= 0xDF820E,		/**< 0xDF820DE,  */

	GMP_PUBKEYMODULUS											= 0xDFC101,		/**< 0xDFC101,  */
	GMP_EXPOMODUL												= 0xDFC102,		/**< 0xDFC102,  */
	GMP_KCV														= 0xDFC104,		/**< 0xDFC104,  */
	GMP_DEVICEBRAND												= 0xDFC107,		/**< 0xDFC107, (uint8[20]) External Device Brand Name */
	GMP_DEVICEMODEL												= 0xDFC108,		/**< 0xDFC108, (uint8[20]) External Device Model Name */
	GMP_DEVICESERIALNUM											= 0xDFC109,		/**< 0xDFC109, (uint8[16]) External Device Serial Number */
	GMP_ECRBRAND												= 0xDFC10A,		/**< 0xDFC10A, (uint8[20]) ECR Brand Name */
	GMP_ECRMODEL												= 0xDFC10B,		/**< 0xDFC10B, (uint8[20]) ECR Model Name */
	GMP_ECRSERIALNUM											= 0xDFC10C,		/**< 0xDFC10C, (uint8[12]) ECR Serial Number */
	GMP_EXTDEV_RANDNUM											= 0xDFC10D,		/**< 0xDFC10D, (uint8[16]) External Device Randum Number, 128bit */
	GMP_EXTDEVICE_RANDNUM_REQ									= 0xDFC10D,		/**< 0xDFC10D,  */
	GMP_ECR_RANDNUM_RES											= 0xDFC10E,		/**< 0xDFC10E, (uint8[16]) ECR Randum Number */
	GMP_RANDNUM													= 0xDFC10E,		/**< 0xDFC10E,  */
	GMP_FLIGHT_TRANSACTION_ID									= 0xDFC10F,		/**< 0xDFC10F,  (uint8[32])  Flight number for application, it is carried in the Raw data from external device to banking application*/

	// master OKC tag list
	GMP_MASTER_OKC_SICIL_NO                                     = 0xDFC170,     /**< 0xDFC170,  */
	GMP_MASTER_OKC_DEVICE_NAME                                  = 0xDFC171,     /**< 0xDFC171,  */
	GMP_MASTER_OKC_CREATE_TIME						            = 0xDFC172,     /**< 0xDFC172,  */
	GMP_MASTER_OKC_TRANS_EXPIRED_TIME                           = 0xDFC173,     /**< 0xDFC173,  */
	GMP_MASTER_OKC_TRANS_USER_DEFINED_GROUP                     = 0xDFC174,     /**< 0xDFC174,  */
	GMP_MASTER_OKC_TRANS_USER_DEFINITION                        = 0xDFC175,     /**< 0xDFC175,  */
	GMP_MASTER_OKC_TRANS_STATUS_FILTER                          = 0xDFC176,     /**< 0xDFC176,  */
	GMP_MASTER_OKC_TRANS_RECEIPT_AMOUNT                         = 0xDFC177,     /**< 0xDFC177,  */
	GMP_MASTER_OKC_TRANS_COMMAND_INDEX							= 0xDFC178,		/**< 0xDFC178,  */
	GMP_MASTER_OKC_TRANS_COMMAND_SIGN							= 0xDFC179,		/**< 0xDFC179,  */
	GMP_MASTER_OKC_TRANS_CHECK_NO								= 0xDFC17A,		/**< 0xDFC17A,  */

	GMP_MASTER_OKC_NUMBER_OF_BACKGROUND_HANDLE					= 0xDFC180,		/**< 0xDFC180,  */
	GMP_MASTER_OKC_BACKGROUND_HANDLE							= 0xDFC181,		/**< 0xDFC181,  */
	GMP_MASTER_OKC_NUMBER_OF_HANDLE_IN_THIS						= 0xDFC182,		/**< 0xDFC182,  */
	GMP_MASTER_OKC_TOTAL_NUMBER_OF_TRANSACTION_HANDLE			= 0xDFC183,		/**< 0xDFC183,  */
	GMP_MASTER_OKC_DATA_OF_BACKGROUD_TRANSACTION_LIST			= 0xDFC184,		/**< 0xDFC184,  */
	GMP_MASTER_OKC_DATA_OF_BACKGROUD_TRANSACTION				= 0xDFC185,		/**< 0xDFC185,  */
	GMP_MASTER_OKC_SAVE_DATA_OF_BACKGROUD_TRANSACTION			= 0xDFC186,		/**< 0xDFC186,  */
	GMP_MASTER_OKC_GET_BACKGROUND_HANDLE_STATUS					= 0xDFC187,		/**< 0xDFC187,  */
	GMP_MASTER_OKC_SET_BACKGROUND_HANDLE_STATUS					= 0xDFC188,		/**< 0xDFC188,  */
	GMP_MASTER_OKC_BACKGROUD_HANDLE_STATUS						= 0xDFC189,		/**< 0xDFC189,  */

	GMP_TRANSACTION_HANDLE_RECORD								= 0xDFC190,		/**< 0xDFC190,  */
	GMP_TRANSACTION_COMMAND_RECORD								= 0xDFC191,		/**< 0xDFC191,  */
	GMP_TRANSACTION_STATUS_RECORD								= 0xDFC192,		/**< 0xDFC192,  */

	GMP_EXT_DEVICE_TAG_GERI_DONUS_KODU							= 0xDFED00,		/**< 0xDFED00,  */
	GMP_EXT_DEVICE_TAG_ISLEM_SIRA_NO							,				/**< 0xDFED01,  */
	GMP_EXT_DEVICE_TAG_ISLEM_ZAMAN_ASIMI						,				/**< 0xDFED02,  */
	GMP_EXT_DEVICE_TAG_ISLEM_TOPLAM_TUTAR						,				/**< 0xDFED03,  */
	GMP_EXT_DEVICE_TAG_MALI_ISLEM_TARIHI						,				/**< 0xDFED04, (bcd[3]) YYMMDD Date of transaction (ticket) */
	GMP_EXT_DEVICE_TAG_MALI_ISLEM_SAATI							,				/**< 0xDFED05, (bcd[3]) HHMMSS Time of transaction (ticket)  */
	GMP_EXT_DEVICE_TAG_Z_NO										,				/**< 0xDFED06, (bcd[3]) Z No, Batch No Of the ECR */
	GMP_EXT_DEVICE_TAG_FIS_NO									,				/**< 0xDFED07, (bcd[3]) F No, Ticket No  */
	GMP_EXT_DEVICE_TAG_EKU_NO									,				/**< 0xDFED08, (bcd[3]) EJ No  */
	GMP_EXT_DEVICE_TAG_Z_NO_BITIS								,				/**< 0xDFED09,  */
	GMP_EXT_DEVICE_TAG_FIS_NO_BITIS								,				/**< 0xDFED0A,  */
	GMP_EXT_DEVICE_TAG_FATURA_TCK							    ,				/**< 0xDFED0B,  */
	GMP_EXT_DEVICE_TAG_FATURA_VKN							    ,				/**< 0xDFED0C,  */
	GMP_EXT_DEVICE_USER_MESSAGE 								,				/**< 0xDFED0D, (ST_printerDataForOneLine) User mesage Structure (text,barcode,2D barcode) to print on the ticket */
	GMP_EXT_DEVICE_TAG_HATA_KODU								,				/**< 0xDFED0E,  */
	GMP_EXT_DEVICE_TAG_HATA_MSG									,				/**< 0xDFED0F,  */
	GMP_EXT_DEVICE_TAG_FATURA_SOURCE							,				/**< 0xDFED10, (uint8) One of EInvoiceSource */
	GMP_EXT_DEVICE_TAG_RAPOR_BASLANGIC_TARIHI					,				/**< 0xDFED11,  */
	GMP_EXT_DEVICE_TAG_RAPOR_BITIS_TARIHI						,				/**< 0xDFED12,  */
	GMP_EXT_DEVICE_TAG_FONK_FLAGS								,				/**< 0xDFED13,  */
	GMP_EXT_DEVICE_TAG_FATURA_AMOUNT							,				/**< 0xDFED14, (bcd[6]) Total amount of Invoice Ticket.*/
	GMP_EXT_DEVICE_TAG_PLU_SON_GUNCELLEME						,				/**< 0xDFED15,  */
	GMP_EXT_DEVICE_TAG_TRANSACTION_FLAGS						,				/**< 0xDFED16, (uint32) set of flags for the transaction*/
	GMP_EXT_DEVICE_FIS_TOPLAM_INCREASE							,				/**< 0xDFED17, (bcd[6]) Total Increase made on the ticket (Current amount! If ticket is not closed yet, new items or voids may change it) */
	GMP_EXT_DEVICE_FIS_TOPLAM_DISCOUNT							,				/**< 0xDFED18, (bcd[6]) Total Discount made on the ticket (Current amount! If ticket is not closed yet, new items or voids may change it) */
	GMP_EXT_DEVICE_FIS_TOPLAM_CANCEL   							,				/**< 0xDFED19, (bcd[6]) Total Void items made on the ticket (Current amount! If ticket is not closed yet, new voids may change it)  */
	GMP_EXT_DEVICE_TRANSACTION_FISCAL_TYPE						,				/**< 0xDFED1A, (uint8) One Of ETransactionFiscalType */
	GMP_EXT_DEVICE_FIS_PARAUSTU   								,				/**< 0xDFED1B, (bcd[6]) Total Cash back amount after CASH payment. it will always be in CURRENCY_TL */
	GMP_EXT_DEVICE_TRANSACTION_TICKET_TYPE						,				/**< 0xDFED1C, (uint8) One Of TTicketType */
	GMP_EXT_DEVICE_TAG_FATURA_DATE								,				/**< 0xDFED1D, (bcd[3]) Date of the Invoice as YYMMDD */
	GMP_EXT_DEVICE_TAG_FATURA_CURRENCY							,				/**< 0xDFED1E, (bcd[2]) Currency of the invoice amount */
	GMP_EXT_DEVICE_TAG_FATURA_NO								,				/**< 0xDFED1F, (uint8[24]) No of the invoice */

	GMP_EXT_DEVICE_OKC_KISIM_SAYISI								= 0xDFED20,		/**< 0xDFED20,  */
	GMP_EXT_DEVICE_OKC_KISIM_INDEX								,				/**< 0xDFED21,  */
	GMP_EXT_DEVICE_OKC_KISIM_ADI								,				/**< 0xDFED22,  */
	GMP_EXT_DEVICE_OKC_KISIM_BOS_XXXXXXXXXXXX					,				/**< 0xDFED23, Kdv orani kullanýlmayacak. Bunun yerine GMP_EXT_DEVICE_OKC_KISIM_KDV_INDEX gelmeli */
	GMP_EXT_DEVICE_OKC_KISIM_BIRIMI								,				/**< 0xDFED24,  */
	GMP_EXT_DEVICE_OKC_KISIM_TUTARI								,				/**< 0xDFED25,  */
	GMP_EXT_DEVICE_OKC_KISIM_KDV_INDEX							,				/**< 0xDFED26,  */
	GMP_EXT_DEVICE_OKC_KISIM_PARABIRIMI							,				/**< 0xDFED27,  */
	GMP_EXT_DEVICE_OKC_KISIM_LIMIT								,				/**< 0xDFED28,  */
	GMP_EXT_DEVICE_OKC_KISIM_YEMEK_CEKI_FLAG					,				/**< 0xDFED29,  */

	GMP_EXT_DEVICE_VERGI_SAYISI									= 0xDFED2A,		/**< 0xDFED2A,  */
	GMP_EXT_DEVICE_VERGI_INDEX									,				/**< 0xDFED2B,  */
	GMP_EXT_DEVICE_VERGI_ORANI									,				/**< 0xDFED2C,  */

	GMP_EXT_DEVICE_SEND_FRONT_STATION_PRINT						,				/**< 0xDFED2D,  */
	GMP_EXT_DEVICE_FRONT_STATION_RECEIVE_LEN					,				/**< 0xDFED2E,  */
	GMP_EXT_DEVICE_FRONT_STATION_TIMEOUT						,				/**< 0xDFED2F,  */

	GMP_EXT_DEVICE_OKC_DOVIZ_SAYISI								= 0xDFED30,		/**< 0xDFED30,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_INDEX								,				/**< 0xDFED31,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_ADI								,				/**< 0xDFED32,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_ISARET								,				/**< 0xDFED33,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_ISARET_YONU						,				/**< 0xDFED34,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_KURU								,				/**< 0xDFED35,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_KURUS_BASAMAK_SAYISI				,				/**< 0xDFED36,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_KODU								,				/**< 0xDFED37,  */
	GMP_EXT_DEVICE_KASIYER_SAYISI								,				/**< 0xDFED38,  */
	GMP_EXT_DEVICE_KASIYER_INDEX								,				/**< 0xDFED39,  */
	GMP_EXT_DEVICE_KASIYER_ADI									,				/**< 0xDFED3A,  */
	GMP_EXT_DEVICE_KASIYER_SIFRESI								,				/**< 0xDFED3B,  */
	GMP_EXT_DEVICE_KASIYER_FLAGS								,				/**< 0xDFED3C,  */

	GMP_EXT_DEVICE_FIS_ITEM_SAYISI								= 0xDFED40,		/**< 0xDFED40, (uint16) Number of the items */
	GMP_EXT_DEVICE_FIS_ITEM_ISLEM_TIPI							,				/**< 0xDFED41, (uint8) Type of the item. One of EItemTypes */
	GMP_EXT_DEVICE_FIS_ITEM_INDEX								,				/**< 0xDFED42, (uint16) Zero based index of the item in a transaction */
	GMP_EXT_DEVICE_FIS_ITEM_URUN_MIKTAR							,				/**< 0xDFED43, (bcd[6]) count (number) of the item */
	GMP_EXT_DEVICE_FIS_ITEM_URUN_PRECISION						,				/**< 0xDFED44, (bcd[1]) precision of the item count (number). Exp; It is 2, to represent 2,58 kg for GMP_EXT_DEVICE_FIS_ITEM_URUN_MIKTAR = 258 */
	GMP_EXT_DEVICE_FIS_ITEM_TUTAR								,				/**< 0xDFED45,  */
	GMP_EXT_DEVICE_FIS_ITEM_INDIRIM_TUTAR						,				/**< 0xDFED46,  */
	GMP_EXT_DEVICE_FIS_ITEM_ARTIRIM_TUTAR						,				/**< 0xDFED47,  */
	GMP_EXT_DEVICE_FIS_ITEM_INDIRIM_ORANI						,				/**< 0xDFED48,  */
	GMP_EXT_DEVICE_FIS_ITEM_ARTIRIM_ORANI						,				/**< 0xDFED49,  */
	GMP_EXT_DEVICE_FIS_ITEM_IND_ART_TEXT						,				/**< 0xDFED4A,  */
	GMP_EXT_DEVICE_FIS_ITEM_KDV_ORANI							,				/**< 0xDFED4B,  */
	GMP_EXT_DEVICE_FIS_ITEM_ADI									,				/**< 0xDFED4C, (uint8[32]) Item (product) name to print on the ticket. Fully optional and if not provided, Department name (for ITEM_TYPE_DEPT) or PLU name (for ITEM_TYPE_PLU) is used in stead */
	GMP_EXT_DEVICE_FIS_ITEM_BIRIM								,				/**< 0xDFED4D,  */
	GMP_EXT_DEVICE_FIS_TOPLAM_TUTAR								,				/**< 0xDFED4E, (bcd[6]) Total Ticket Amount (Current amount! If ticket is not closed yet, new items or voids may change it) (Tax included and net payment amount */
	GMP_EXT_DEVICE_FIS_TOPLAM_KDV								,				/**< 0xDFED4F, (bcd[6]) Total Tax Amount (Current tax amount! If ticket is not closed yet, new items or voids may change it) */
	GMP_EXT_DEVICE_FIS_INDIRIM_TUTARI							,				/**< 0xDFED50,  */
	GMP_EXT_DEVICE_FIS_INDIRIM_TEXT								,				/**< 0xDFED51,  */
	GMP_EXT_DEVICE_FIS_YUZDE_INDIRIM							,				/**< 0xDFED52, (bcd[1]) Percentage rate to substract */
	GMP_EXT_DEVICE_FIS_DEPT_INDEX								,				/**< 0xDFED53,  */
	GMP_EXT_DEVICE_FIS_LIMIT									,				/**< 0xDFED54,  */
	GMP_EXT_DEVICE_FIS_FLAG										,				/**< 0xDFED55,  */
	GMP_EXT_DEVICE_FIS_ITEM_BARCODE								,				/**< 0xDFED56, (uint8[32]) Item (product) barcode. If this s a ITEM_TYPE_DEPT sale, barcode is just used to print on the ticket and fully optional. If this is a ITEM_TYPE_PLU type item, then barcode is mandotary and must be provided by external system. ECR will search it on PLU DB */
	GMP_EXT_DEVICE_FIS_ITEM_CURRENCY							,				/**< 0xDFED57,  */
	GMP_EXT_DEVICE_FIS_ITEM_ORIGINAL_TUTAR						,				/**< 0xDFED58,  */
	GMP_EXT_DEVICE_FIS_ITEM_ORIGINAL_CURRENCY					,				/**< 0xDFED59,  */
	GMP_EXT_DEVICE_FIS_ITEM_ISLEM_SUBTYPE						,				/**< 0xDFED5A,  */
	GMP_EXT_DEVICE_FIS_ITEM_PLU_FIYAT_INDEX						,				/**< 0xDFED5B,  */
	GMP_EXT_DEVICE_FIS_ITEM_GROUP_V1							,				/**< 0xDFED5C, points a ST_ITEM_GROUP_V1 structure which includes a set of parameters to define an item  */
	GMP_EXT_DEVICE_FIS_TAX_DETAIL								,				/**< 0xDFED5D, points an array of ST_VATDetail[8] as a data. It includes totals of different Tax values on the current ticket */

	GMP_EXT_DEVICE_ODEME_SAYISI									= 0xDFED60,		/**< 0xDFED60, (uint8) Number of Payments */
	GMP_EXT_DEVICE_ODEME_INDEX									,				/**< 0xDFED61, (uint16) Zero based index of the payment in a transaction */
	GMP_EXT_DEVICE_ODEME_TUTAR									,				/**< 0xDFED62, (bcd[6]) Payment amount in bcd format with 2 precisition. Exp; it is 0x000000230050 for the amount of 2300,50 */
	GMP_EXT_DEVICE_ODEME_TIP									,				/**< 0xDFED63, (uint32) Type of the payment, one of EPaymentTypes */
	GMP_EXT_DEVICE_ODEME_TEXT									,				/**< 0xDFED64, (uint8[24] Ascii string to print on the ticket */
	GMP_EXT_DEVICE_ODEME_BKM_ID									,				/**< 0xDFED65, (bcd[2]) BKM ID of the bank in bcd format */
	GMP_EXT_DEVICE_ODEME_KART_PAN								,				/**< 0xDFED66, (uint8[19]) Card No (masked) */
	GMP_EXT_DEVICE_ODEME_PARA_BIRIMI							,				/**< 0xDFED67, (bcd[2]) Currency of the amount in bcd */
	GMP_EXT_DEVICE_ODEME_SECENEKLERI							,				/**< 0xDFED68,  */
	GMP_EXT_DEVICE_ODEME_TEKIL_NO								,				/**< 0xDFED69,  */
	GMP_EXT_DEVICE_ODEME_ONAY_KOD								,				/**< 0xDFED6A, (uint8[6]) Authorization Code coming from bank application (if the payment is done trough a bank application) */
	GMP_EXT_DEVICE_ODEME_TERMINAL_ID							,				/**< 0xDFED6B, (uint8[8]) Terminal Id of the bank application (if the payment is done trough a bank application) */
	GMP_EXT_DEVICE_ODEME_MERCHANT_ID							,				/**< 0xDFED6C, (uint8[15]) Merchant Id of the bank application (if the payment is done trough a bank application) */
	GMP_EXT_DEVICE_ODEME_INFO_FLAGS								,				/**< 0xDFED6D, (uint16) Set of flags for Baking Payments (Card Types ext..) */
	GMP_EXT_DEVICE_ODEME_FLAGS		 	 						,				/**< 0xDFED6E, (uint8) Set of general flags for the payment */
	GMP_EXT_DEVICE_MATRAHSIZ_ODEME_TUTARI						,				/**< 0xDFED6F, (bcd[6]) A part of ticket Amount which is excluded from TAX calculation, called "Matrahsiz" or "Katki Payi" */
	GMP_EXT_DEVICE_TAXFREE_REFUND_TUTARI 						,				/**< 0xDFED70, (bcd[6]) A part of ticket Amount which is marked as TAX FREE */
	GMP_EXT_DEVICE_ODEME_ALT_TIP         						,				/**< 0xDFED71, (uint8) SubType of the payment, Not implemented yet */
	GMP_EXT_DEVICE_ODEME_DATETIME        						,				/**< 0xDFED72, (uint32) Unix type date & time of the payment */
	GMP_EXT_DEVICE_ODEME_BATCH_NO        						,				/**< 0xDFED73, (uint32) Batch No of the bank application (if the payment is done trough a bank application) */
	GMP_EXT_DEVICE_ODEME_STAN        	 						,				/**< 0xDFED74, (uint32) STAN No of the bank application (if the payment is done trough a bank application) */
	GMP_EXT_DEVICE_TUTAR                 						,				/**< 0xDFED75, (bcd[6]) General porpuse amout tag. it is always TL and 2 precision. Exp it is 258 for 2.58TL */
	GMP_EXT_DEVICE_ODEME_BANKNAME      							,				/**< 0xDFED76, Name of the bank (if the payment is done trough a bank application) */
	GMP_EXT_DEVICE_ODEME_ERROR_CODE		 						,				/**< 0xDFED77, (uint8[4]) Error Code as ASCII */
	GMP_EXT_DEVICE_ODEME_ERROR_TEXT		 						,				/**< 0xDFED78, (uint8[40]) Error Message as ASCII  */
	GMP_EXT_DEVICE_ODEME_TAKSIT_SAYISI     						,				/**< 0xDFED79, (uint8) Number of installments */
	GMP_EXT_DEVICE_ODEME_YEMEKCEKI_FIRMASI						,				/**< 0xDFED7A,  */
	GMP_EXT_DEVICE_ODEME_INDIRIM_INDEX							,				/**< 0xDFED7B,  (uint8) Discount Index of Paymnent */
	GMP_EXT_DEVICE_ODEME_INDIRIM_TUTAR							,				/**< 0xDFED7C,  (bcd[6]) Discount amount in bcd format with 2 precisition. Exp; it is 0x000000230050 for the amount of 2300,50 */
	GMP_EXT_DEVICE_ODEME_BONUS_INDEX       						,				/**< 0xDFED7D,  (uint8) Bonus Index of Paymnent */
	GMP_EXT_DEVICE_ODEME_BONUS_TUTAR      						,				/**< 0xDFED7E,  (bcd[6]) Bonus amount in bcd format with 2 precisition. Exp; it is 0x000000230050 for the amount of 2300,50 */
	GMP_EXT_DEVICE_ODEME_INDIRIM_TEXT	  						,				/**< 0xDFED7F,  Discount Text of Paymnent */
	GMP_EXT_DEVICE_ODEME_BONUS_TEXT       						,				/**< 0xDFED80,  Bonus Text of Paymnent */
	GMP_EXT_DEVICE_ODEME_REVERSE_TUTAR     						,				/**< 0xDFED81, (bcd[6]) Amount to be refunded */
	GMP_EXT_DEVICE_ODEME_MATRAHSIZ_TYPE    					    ,				/**< 0xDFED82, (uint8) Type Of the matrahsiz amount. One of ETypeOfMatrahsiz */
	GMP_EXT_DEVICE_ODEME_RAW_DATA								,				/**< 0xDFED83, (uint8) Type Of the TLV data. Filled by external/internal application for payment application */
	GMP_EXT_DEVICE_ODEME_PROVISION_ID							,				/**< 0xDFED84, (char) Provision Id of the payment */
	GMP_EXT_DEVICE_ODEME_BKM_ID_U16								,				/**< 0xDFED85, BKM ID uint16 */


	GMP_TYPE_OF_PERSONEL_ID				  					    = 0xDFED86,		/**< 0xDFED86, (uint16) Type Of the user identification number. One of EPersonelIdTypes */
	GMP_TYPE_OF_UNIQUE_ID										,		        /**< 0xDFED87, Application unique number will be used Payment Appl and External appl.*/
	GMP_EXT_DEVICE_TRANSACTION_FLAGS							= 0xDFED8A,		/**< 0xDFED8A, External Device Transaction Flags-1 */
	GMP_EXT_DEVICE_TRANSACTION_TYPE								,				/**< 0xDFED8B, External Device Trans Type */
	GMP_EXT_DEVICE_TRANSACTION_SUBTYPE							,				/**< 0xDFED8C, External Device Trans SubType */

	GMP_EXT_DEVICE_TRANS_REF_CODE								= 0xDFED90,		/**< 0xDFED90, Refund isleminde gerekli:0x5F RRN varsa kullanilir  */
	GMP_EXT_DEVICE_ORG_TRANS_TYPE								,				/**< 0xDFED91,  */
	GMP_EXT_DEVICE_REFUND_LOYALTY_AMOUNT						,				/**< 0xDFED92,  */
	GMP_EXT_DEVICE_REFUND_RRN									,				/**< 0xDFED93, uint8[12], RRN of the original banking transaction */
	GMP_EXT_DEVICE_REFUND_ORG_TRANS_AMOUNT						,				/**< 0xDFED94,  */
	GMP_EXT_DEVICE_REFUND_ORG_LOYALTY_AMOUNT					,				/**< 0xDFED95,  */
	GMP_EXT_DEVICE_REFUND_ORG_MERCHANT_ID						,				/**< 0xDFED96,  */
	GMP_EXT_DEVICE_REFUND_ORG_TRANS_DATE						,				/**< 0xDFED97,  */
	GMP_EXT_DEVICE_REFUND_ORG_INSTALLMENT_COUNT					,				/**< 0xDFED98,  */

	GMP_TAG_COMPANY_NAME										= 0xDFEDA0,		/**< 0xDFEDA0, (uint8[24]) Name of the Firm/Company  */
	GMP_TAG_SUBSCRIBER_ID										,				/**< 0xDFEDA1, (uint8[24]) Id of the subscriberId, like phone number, ext...  */
	GMP_TAG_DEALER_ID											,				/**< 0xDFEDA2, Bayi Kodu --> Asc(11)  */
	GMP_TAG_FOUNDATION_CODE										,				/**< 0xDFEDA3, Kurum kodu --> Bcd(2)  */
	GMP_TAG_ORDER_NUMBER										,				/**< 0xDFEDA4, Sipariþ Numarasý --> Asc(20)  */
	GMP_TAG_INVOICE_FLAGS										,				/**< 0xDFEDA5, (uint64)    Invoice flags to control the flow like forbidden payment type and mandatory payment application */
	GMP_TAG_INVOICE_COMMISSION_TAX_RATE							,				/**< 0xDFEDA6, (uint8)     Invoice commission tax rate*/
	GMP_TAG_INVOICE_COMMISSION_AMOUNT_RATE						,				/**< 0xDFEDA7, (uint8)     Invoice money collection commission rate*/
	GMP_TAG_INVOICE_COMMISSION_AMOUNT							,				/**< 0xDFEDA8, (bcd[6])    Invoice money collection commission amount*/
	GMP_TAG_MONEY_COLLECTION_DUE_DATE							,				/**< 0xDFEDA9, (bcd[3])    YYMMDD last date of the invoice  */
	GMP_TAG_ONLINE_INVOICE_EXCEPTION_CODE						,				/**< 0xDFEDAA, (uint16)    item tax exception code */
	GMP_TAG_INVOICE_GROUP_MERCHANT_NO							,               /**< 0xDFEDAB, (bcd[5])    Money collection group merchant no */
	GMP_TAG_FOUNDATION_TRANSACTION_UNIQUE_ID					,				/**< 0xDFEDAC   */

	GMP_EXT_DEVICE_URUN_KODU									 = 0xDFEDB0,	/**< 0xDFEDB0,  */
	GMP_EXT_DEVICE_URUN_SICIL_NO								 ,				/**< 0xDFEDB1,  */
	GMP_EXT_DEVICE_URUN_UYGULAMA_VERSIYONU						 ,				/**< 0xDFEDB2,  */
	GMP_EXT_DEVICE_FISCAL_DATE_TIME								 ,				/**< 0xDFEDB3,  */

	GMP_EXT_DEVICE_TAX_FREE_NAME								= 0xDFEDBA,		/**< 0xDFEDBA, Name Of the customer who will benefit Tax Refund. It must written as written on his/her id */
	GMP_EXT_DEVICE_TAX_FREE_SURNAME								,				/**< 0xDFEDBB, Surname Of the customer who will benefit Tax Refund. It must written as written on his/her id */
	GMP_EXT_DEVICE_TAX_FREE_PASSPORT_NO							,				/**< 0xDFEDBC, Id number Of the customer who will benefit Tax Refund. It must written as written on his/her id */
	GMP_EXT_DEVICE_TAX_FREE_CITY								,				/**< 0xDFEDBD, City of the customer */
	GMP_EXT_DEVICE_TAX_FREE_COUNTRY								,				/**< 0xDFEDBE, Country of the customer */
	GMP_EXT_DEVICE_TAX_FREE_FLAG								,				/**< 0xDFEDBF, Future Use Flags for tax free. It is NULL for the moment */

	GMP_DATABASE_NAME											= 0xDFEDC0,		/**< 0xDFEDC0,  */
	GMP_DATABASE_RETURN_CODE									,				/**< 0xDFEDC1,  */
	GMP_DATABASE_RETURN_CODE_MSG								,				/**< 0xDFEDC2,  */
	GMP_DATABASE_HANDLE											,				/**< 0xDFEDC3,  */
	GMP_DATABASE_SQL_WORD										,				/**< 0xDFEDC4,  */
	GMP_DATABASE_NUMBER_OF_COLOMN								,				/**< 0xDFEDC5,  */
	GMP_DATABASE_COLOMN_NAME									,				/**< 0xDFEDC6,  */
	GMP_DATABASE_COLOMN_TYPE									,				/**< 0xDFEDC7,  */
	GMP_DATABASE_COLOMN_DATA									,				/**< 0xDFEDC8,  */
	GMP_DATABASE_NUMBER_OF_RAW									,				/**< 0xDFEDC9,  */
	GMP_DATABASE_INDEX_OF_COLOMN								,				/**< 0xDFEDCA,  */
	GMP_DATABASE_INDEX_OF_ROW									,				/**< 0xDFEDCB,  */

	GMP_EXT_DEVICE_COMMAND_SUB_COMMAND							= 0xDFEDD0,		/**< 0xDFEDD0, (uint16) Sub Command of the requested operation. Value is one of EFiscalPrinterSubCommands */
	GMP_EXT_DEVICE_COMMAND_SOURCE_VAS_APP_ID					= 0xDFEDD5,		/**< 0xDFEDD5, (uint16) Transaction Starter App ID */
	GMP_EXT_DEVICE_COMMAND_PAYMENT_VAS_APP_ID					,				/**< 0xDFEDD6, (uint16) Invoice Payment App ID */
	GMP_EXT_DEVICE_COMMAND_BANK_VAS_APP_ID						,				/**< 0xDFEDD7, (uint16) Loyalty Payment App ID */

	GMP_FISCALPRINTER_MODE_RETURN_CODE     						= 0xDFEDE0,		/**< 0xDFEDE0, (uint16) return code of the SubCommand processed on ECR */
	GMP_FISCALPRINTER_MODE_HANDLE								,				/**< 0xDFEDE1, (uint64) GMP3 Transaction Handle which is provided by ECR during START function. This parameter must be kept and sent back to ECR by external system in all GMP3_FISCAL_PRINTER_MODE_REQ / GMP3_FISCAL_PRINTER_MODE_REQ_E group functions */
	GMP_FISCALPRINTER_MODE_NUMBER_OF_PRINTED_LINES				,				/**< 0xDFEDE2, (uint16) number of printer lines */
	GMP_FISCALPRINTER_MODE_PRINTED_LINES						,				/**< 0xDFEDE3, (ST_printerDataForOneLine) printed line */
	GMP_FISCALPRINTER_MODE_UNIQUE_ID							,				/**< 0xDFEDE4, (uint8[24]) string which keeps Unique Id of the transaction. It may be used on both REQ or RES messages */
	GMP_FISCALPRINTER_MODE_NUMBER_OF_UNIQUE_ID					,				/**< 0xDFEDE5, (uint16) Number of Unique Ids */
	GMP_FISCALPRINTER_MODE_OPTION_FLAGS							,				/**< 0xDFEDE6, (uint64) Set Of Option Flags GMP3_OPTION_xxx (GMP3_OPTION_ECHO_PRINTER, ext ) to manage a ticket on ECR side*/
	GMP_FISCALPRINTER_MODE_CONDITION                            ,				/**< 0xDFEDE7, (ST_CONDITIONAL_IF) Points to ST_CONDITIONAL_IF structure data */
	GMP_FISCALPRINTER_MODE_SUBCOMMAND_INDEX						,				/**< 0xDFEDE8, (uint16) One based index of the subCommand relplied by ECR. ECR counts the index in received Request message and echos it. External system may sent multiple subCommand groups and this index is used by external system to point the correct subCommand */
	GMP_FISCALPRINTER_MODE_USER_DATA                            ,				/**< 0xDFEDE9, (uint8[64]) string (this is max length and can be less) which keeps user data. ECR will echo this data in some RESPONSE messages */
	GMP_FISCALPRINTER_MODE_UNIQUE_ID_SIGN						, 				/**< 0xDFEDEA, (uint8[32]) Signature value of the Unique Id which is created and signed by TSM. This value will be verified in ECR */
	GMP_FISCALPRINTER_MODE_BACK_GROUND_PROCESS					, 				/**< 0xDFEDEB, (uint8) define background process, all fiscal process are handled on background side */
	GMP_FISCALPRINTER_MODE_SOURCE_TYPE							, 				/**< 0xDFEDEC, (uint8) define ticket process of the initialization type as start from internal or external */

	GMP_EXT_DEVICE_TCKNO										= 0xDFEDF0,		/**< 0xDFEDF0, (unit8[15]) Turkish Republic Personel Identification Number, 11 digit unique Id */
	GMP_EXT_DEVICE_KASA_AVANS_ISLEM_TUTARI						,				/**< 0xDFEDF1, (bcd[6]) Avans Transaction Amount */
	GMP_EXT_DEVICE_KASA_ODEME_ISLEM_TUTARI						,				/**< 0xDFEDF2, (bcd[6]) Odeme (Payment) Transaction Amount  */
	GMP_EXT_DEVICE_FIS_ARTIRIM_TUTAR							,				/**< 0xDFEDF3,  */
	GMP_EXT_DEVICE_FIS_INDIRIM_TUTAR							,				/**< 0xDFEDF4,  */
	GMP_EXT_DEVICE_FIS_YUZDE_ARTIRIM							,				/**< 0xDFEDF5, (bcd[1]) Percentage rate to add */
	GMP_EXT_DEVICE_VKNO											,				/**< 0xDFEDF6, (uint8[15]) Turkish Government Tax Identification Number, 15 digit unique Id */
	GMP_EXT_DEVICE_CAR_IDENTIFICATION							,				/**< 0xDFEDF7, (uint8[12]) Car Plate */
	GMP_EXT_DEVICE_FILEDIR_BITMAP								,				/**< 0xDFEDF8,  */
	GMP_EXT_DEVICE_CUSTOMER_NAME								,				/**< 0xDFEDF9,  Customer Name/Surmane or Title of a company*/
	GMP_EXT_DEVICE_CARI_HESAP_TAHSILAT_TUTAR					,				/**< 0xDFEDFA,  Cari Hesap Amount*/
	GMP_EXT_DEVICE_CARI_HESAP_BELGE_NO							,			    /**< 0xDFEDFB,  Cari Hesap Belge/Ekstre No*/
	GMP_EXT_DEVICE_CARI_HESAP_BELGE_DATE						,			    /**< 0xDFEDFC,  Cari Hesap Belge/Ekstre Date*/

	GMP_EXT_PLU_BARCODE											= 0xDFEE00,		/**< 0xDFEE00,  */
	GMP_EXT_PLU_NAME											,				/**< 0xDFEE01,  */
	GMP_EXT_PLU_DEPARTMENT_INDEX								,				/**< 0xDFEE02,  */
	GMP_EXT_PLU_UNIT_TYPE										,				/**< 0xDFEE03,  */
	GMP_EXT_PLU_FLAG											,				/**< 0xDFEE04,  */
	GMP_EXT_PLU_LAST_MODIFIED									,				/**< 0xDFEE05,  */
	GMP_EXT_PLU_PARENT_ID										,				/**< 0xDFEE06,  */
	GMP_EXT_PLU_AMOUNT											,				/**< 0xDFEE07,  */
	GMP_EXT_PLU_CURRENCY										,				/**< 0xDFEE08,  */
	GMP_EXT_PLU_GROUP_NAME										,				/**< 0xDFEE09,  */
	GMP_EXT_PLU_GROUP_ID										,				/**< 0xDFEE0A,  */
	GMP_EXT_PLU_GROUP_FLAG										,				/**< 0xDFEE0B,  */
	GMP_EXT_PLU_BARCODE_COUNT									,				/**< 0xDFEE0C, barcode count to be read*/
	GMP_EXT_PLU_BARCODE_TIMEOUT									,				/**< 0xDFEE0D, barcode read timeout*/

	GMP_EXT_DEVICE_USER_TIMEOUT									= 0xDFEE20,		/**< 0xDFEE20,  */
	GMP_EXT_DIGER_BELGE_ALICI_ADSOYAD = 0xDFEE21,		/**< 0xDFEE21,  */
	GMP_EXT_DIGER_BELGE_ALICI_ADRES = 0xDFEE22,		/**< 0xDFEE22,  */
	GMP_EXT_DIGER_BELGE_ALICI_UNVAN = 0xDFEE23,		/**< 0xDFEE23,  */
	GMP_EXT_DIGER_BELGE_ALICI_VERGI_DAIRESI = 0xDFEE24,		/**< 0xDFEE24,  */
	GMP_EXT_DIGER_BELGE_ALICI_TCKN_VKN = 0xDFEE25,		/**< 0xDFEE25,  */
	GMP_EXT_DIGER_BELGE_STOPAJ_ORANI = 0xDFEE26,		/**< 0xDFEE26,  */
	GMP_EXT_DIGER_BELGE_TEVKIFAT_ORANI = 0xDFEE27,		/**< 0xDFEE27,  */
	GMP_EXT_GIDER_PUSUSULASI_SATICI_ADSOYAD = 0xDFEE28,     /**< 0xDFEE28,  */
	GMP_EXT_GIDER_PUSUSULASI_FATURA_SERI = 0xDFEE29,		/**< 0xDFEE29,  */
	GMP_EXT_GIDER_PUSUSULASI_FATURA_SIRA = 0xDFEE2A,		/**< 0xDFEE2A,  */
	GMP_EXT_GIDER_PUSUSULASI_FATURA_TARIH = 0xDFEE2B,		/**< 0xDFEE2B,  */
	GMP_EXT_GIDER_PUSUSULASI_KDV_DAHIL_HESAPLAMA = 0xDFEE2C,		/**< 0xDFEE2C,  */

	GMP_EXT_DEVICE_CARDINFO_READER_TYPES						= 0xDFEE30,		/**< 0xDFEE30, (uint8) Card Reader Type */
	GMP_EXT_DEVICE_CARDINFO_EXPIREDATE							,				/**< 0xDFEE31, Not implemented */
	GMP_EXT_DEVICE_CARDINFO_CARDHOLDERNAME						,				/**< 0xDFEE32, (uint8[20]) Name of the Card Holder */
	GMP_EXT_DEVICE_CARDINFO_CARDTYPE							,				/**< 0xDFEE33, (uint3[3]) // type[0..2] => bkmId, type[3] =>Kart tipi, bonus, S&M, Vada vs.. */
	GMP_EXT_DEVICE_CARDINFO_FLAG								,				/**< 0xDFEE34,  */

	GMP_FILESYSTEM_RETURN_CODE									= 0xDFEE40,		/**< 0xDFEE40,  */
	GMP_FILESYSTEM_FILENAME										,				/**< 0xDFEE41,  */
	GMP_FILESYSTEM_DATA											,				/**< 0xDFEE42,  */
	GMP_FILESYSTEM_BUFFERLEN									,				/**< 0xDFEE43,  */
	GMP_FILESYSTEM_OFFSET										,				/**< 0xDFEE44,  */
	GMP_FILESYSTEM_WHENCE										,				/**< 0xDFEE45,  */
	GMP_FILESYSTEM_FILESIZE										,				/**< 0xDFEE46,  */
	GMP_FILESYSTEM_DIRNAME										,				/**< 0xDFEE47,  */

	GMP_EXT_DEVICE_TAG_PLU_DB_NAME								= 0xDFEE50,		/**< 0xDFEE50,  */
	GMP_EXT_DEVICE_TAG_PLU_DB_TYPE								,				/**< 0xDFEE51,  */
	GMP_EXT_DEVICE_TAG_PLU_DB_SIZE								,				/**< 0xDFEE52,  */
	GMP_EXT_DEVICE_TAG_PLU_DB_GRUPS_LASTMODIFIED				,				/**< 0xDFEE53,  */
	GMP_EXT_DEVICE_TAG_PLU_DB_ITEMS_LASTMODIFIED				,				/**< 0xDFEE54,  */
	GMP_EXT_DEVICE_TAG_TRAN_DB_NAME								,				/**< 0xDFEE55,  */
	GMP_EXT_DEVICE_TAG_TRAN_DB_SIZE								,				/**< 0xDFEE56,  */
	GMP_EXT_DEVICE_TAG_PLU_DB_STORAGE_SIZE						,				/**< 0xDFEE57,  */

	GMP_EXT_DEVICE_SETTING_PAYMENT_TYPE							= 0xDFEE60,		/**< 0xDFEE60,  */
	GMP_EXT_DEVICE_INVOICE_SETTINGS								,				/**< 0xDFEE61,  */
	GMP_EXT_DEVICE_Z_SETTINGS									,				/**< 0xDFEE62,  */
	GMP_EXT_DEVICE_AUTO_Z_TIME_IN_MINUTE						,				/**< 0xDFEE63,  */
	GMP_EXT_DEVICE_COPY_BUTTON_SECURED							,				/**< 0xDFEE64,  */
	GMP_EXT_DEVICE_BACKLIGHT_TIMEOUT							,				/**< 0xDFEE65,  */
	GMP_EXT_DEVICE_BACKLIGHT_LEVEL								,				/**< 0xDFEE66,  */
	GMP_EXT_DEVICE_TUS_KILIDI_TO								,				/**< 0xDFEE67,  */
	GMP_EXT_DEVICE_FUNCTION_DISABLE_FLAGS						,				/**< 0xDFEE68, Set of flags to control disable activity of some functions */
	GMP_EXT_DEVICE_FLIGHT_MODE									,				/**< 0xDFEE69, Sets the flight mode ON/OFF */
	GMP_EXT_DEVICE_TICKET_TIMEOUT								,				/**< 0xDFEE6A, Timeout between bank tickets*/
	GMP_EXT_DEVICE_COMM_STATUS									,				/**< 0xDFEE6B, Communication Status Gprs,Flight Mode, Ethernet*/
	GMP_EXT_DEVICE_COMM_SCENARIO								,				/**< 0XDFEE6C, Communication Scenario Gprs, Ethernet, Gprs&Ethernet */
	GMP_EXT_DEVICE_STAND_BY_TIME								,				/**< 0xDFEE6D, Set Standby Time */
	GMP_EXT_DEVICE_PRINTER_NAME									,               /**< 0xDFEE6E,  */
	GMP_EXT_DEVICE_IS_PRINTER_EXTERNAL							,               /**< 0xDFEE6F,  */
	GMP_EXT_DEVICE_IS_CARI_HESAP_ENABLED                        ,               /**< 0xDFEE70,  */
	GMP_EXT_DEVICE_IS_CASH_DRAWER_ENABLED      					,               /**< 0xDFEE71,  */
	GMP_EXT_DEVICE_FISCAL_USAGE_INFO							= 0xDFEE75,		/**< 0xDFEE75,  */
	GMP_EXT_DEVICE_EKU_USAGE_INFO								= 0xDFEE76,		/**< 0xDFEE76,  */

	GMP_EXT_DEVICE_BANKA_SAYISI									= 0xDFEE79,		/**< 0xDFEE79,  */
	GMP_EXT_DEVICE_BANKA_INDEX									, 				/**< 0xDFEE7A,  */
	GMP_EXT_DEVICE_BANKA_BKMID									, 				/**< 0xDFEE7B,  */
	GMP_EXT_DEVICE_BANKA_ADI									, 				/**< 0xDFEE7C,  */
	GMP_EXT_DEVICE_BANKA_STATUS									, 				/**< 0xDFEE7D,  */
	GMP_EXT_DEVICE_BANKA_PRIORITY 								, 				/**< 0xDFEE7E,  */
	GMP_EXT_DEVICE_BANKA_APPLICATIONID							, 				/**< 0xDFEE7F,  */
	GMP_EXT_DEVICE_BANKA_GUNSONU_RESP							, 				/**< 0xDFEE80,  bcd[2]:BkmId and uint8[1] response code */

	GMP_EXT_DEVICE_VAS_SAYISI									,	            /**< 0xDFEE81,  */
	GMP_EXT_DEVICE_VAS_APP_TYPE  								, 				/**< 0xDFEE82,  */
	GMP_EXT_DEVICE_VAS_APP_ID									, 				/**< 0xDFEE83,  */
	GMP_EXT_DEVICE_VAS_APP_INDEX 								,               /**< 0xDFEE84,  */
	GMP_EXT_DEVICE_VAS_APP_NAME							        ,               /**< 0xDFEE85,  */
	GMP_EXT_DEVICE_VAS_APP_VERSION					 	        ,               /**< 0xDFEE86,  */
	GMP_EXT_DEVICE_VAS_APP_ACCOUNT_CODE					 	    ,               /**< 0xDFEE87,  */
	GMP_EXT_DEVICE_VAS_APP_STATUS								,               /**< 0xDFEE88,  */
	GMP_EXT_DEVICE_VAS_APP_FLAG									,               /**< 0xDFEE89,  */
	GMP_EXT_DEVICE_VAS_APP_PAYMENT_COUNT				 	    ,               /**< 0xDFEE8A,  */
	GMP_EXT_DEVICE_VAS_APP_PAYMENT_NAME				 	        ,               /**< 0xDFEE8B,  */
	GMP_EXT_DEVICE_VAS_APP_PAYMENT_TYPE				 	        ,               /**< 0xDFEE8C,  */
	GMP_EXT_DEVICE_VAS_APP_ACCOUNT_CODE_DUMMY					,				/**< 0xDFEE8D,  */
	GMP_EXT_DEVICE_BANK_PAYMENT_SLIP_SUPPORTED_FONTS			= 0xDFEFE6,
	GMP_EXT_DEVICE_BANK_PAYMENT_SLIP_READ_INDEX					= 0xDFEFE7,
	GMP_EXT_DEVICE_BANK_PAYMENT_SLIP_LINE						= 0xDFEFE8,
	GMP_EXT_DEVICE_BANK_PAYMENT_SLIP_TOTAL_LEN					= 0xDFEFE9,
	GMP_EXT_DEVICE_DRAWER_ACTIVE_FOR_CASH						= 0xDFEFEA,

	GMP3_SUBCOMMAND_FISCALPRINTER_GET_USER_DATA				    = 0x002B,
	GMP3_SUBCOMMAND_FISCALPRINTER_SET_USER_DATA                 = 0x002C,

	GMP_TAG_PROMOTIN_TYPE										= 0xDFEE90,		/**< 0xDFEE90, One of \ref EItemPromotionType */
	GMP_TAG_PROMOTIN_AMOUNT										,				/**< 0xDFEE91, Amount of the promotion */
	GMP_TAG_PROMOTIN_MESSAGE									,				/**< 0xDFEE92, Message of the promotion to print on the ticket */

	GMP_TAG_GROUP_DOVIZ_PROFIL_TABLOSU							= 0xDFEE98,		/**< 0xDFEE98   */
	GMP_EXT_DEVICE_OKC_DOVIZ_PROFILE_INDEX						,				/**< 0xDFED99,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_PROFILE_COUNT						,				/**< 0xDFED9A,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_PROFILE_NAME						,				/**< 0xDFED9B,  */
	GMP_EXT_DEVICE_OKC_DOVIZ_PROFILE_THOUSAND_SEPERATOR			,				/**< 0xDFED9C	*/
	GMP_EXT_DEVICE_OKC_DOVIZ_PROFILE_CENT_SEPERATOR				,				/**< 0xDFED9D	*/
	GMP_EXT_DEVICE_OKC_DOVIZ_PROFILE_PROCESS_TYPE				, 				/**< 0xDFED9E 1: Update, 2: add, 3:delete*/

	GMP_TAG_ONLINE_INVOICE_CUSTOMER_NAME						= 0xDFEEA0,		/**< 0xDFEEA0, 64 byte char (zorunlu) */
	GMP_TAG_ONLINE_INVOICE_CUSTOMER_VKN										,				/**< 0xDFEEA1, 24 byte char (Z) */
	GMP_TAG_ONLINE_INVOICE_CUSTOMER_ADDRESS_HOME_ADDRESS					,				/**< 0xDFEEA2, 64 byte char (Z) */
	GMP_TAG_ONLINE_INVOICE_CUSTOMER_ADDRESS_DISTRICT						,				/**< 0xDFEEA3, 24 byte char (Z) */
	GMP_TAG_ONLINE_INVOICE_CUSTOMER_ADDRESS_CITY							,				/**< 0xDFEEA4, 24 byte char (Z) */
	GMP_TAG_ONLINE_INVOICE_CUSTOMER_ADDRESS_COUNTRY							,				/**< 0xDFEEA5, 24 byte char (Z) */
	GMP_TAG_ONLINE_INVOICE_CUSTOMER_ADDRESS_MAIL							,				/**< 0xDFEEA6, 64 byte char (Z) */
	GMP_TAG_ONLINE_INVOICE_CUSTOMER_ADDRESS_WEB_SITE						,				/**< 0xDFEEA7, 64 byte char (O) */
	GMP_TAG_ONLINE_INVOICE_CUSTOMER_ADDRESS_PHONE							,				/**< 0xDFEEA8, 20 byte char (O) */
	GMP_TAG_ONLINE_INVOICE_CUSTOMER_ADDRESS_TAX_OFFICE						,				/**< 0xDFEEA9, 24 byte char (Z) */
	GMP_TAG_ONLINE_INVOICE_SELLER_DESC_E_FATURA								,
	GMP_TAG_ONLINE_INVOICE_SELLER_DESC_E_ARSIV								,
	GMP_TAG_ONLINE_INVOICE_RAW_DATA											,


	GMP_TAG_ONLINE_INVOICE_INFO_TYPE                            = 0xDFEEB0,		/**< 0xDFEEB0, 2 byte uint16 (Z) 1: E-Fatura, 2 E-Arþiv EonlineInvoiceType enum ýný kullabilirsiniz. */
	GMP_TAG_ONLINE_INVOICE_INFO_ETTN                            ,				/**< 0xDFEEB1, 36 byte char (Z) */
	GMP_TAG_ONLINE_INVOICE_INFO_ORDER_DATE                      ,				/**< 0xDFEEB2, 6 byte BCD (O) */
	GMP_TAG_ONLINE_INVOICE_INFO_ORDER_NO                        ,				/**< 0xDFEEB3, 24 byte char (O) */
	GMP_TAG_ONLINE_INVOICE_INFO_DESPATCH_DATE                   ,				/**< 0xDFEEB4, 6 byte BCD (O) */
	GMP_TAG_ONLINE_INVOICE_INFO_DESPATCH_NO                     ,				/**< 0xDFEEB5, 24 byte char (O) */
	GMP_TAG_ONLINE_INVOICE_INFO_IDENTIFIER                      ,				/**< 0xDFEEB6, 64 byte char (O) */

	GMP_TAG_ONLINE_TAXFREE_BUYER_NAME                           = 0xDFEEC0,		/**< 0xDFEEC0,*/
	GMP_TAG_ONLINE_TAXFREE_BUYER_SURNAME                        ,				/**< 0xDFEEC1,*/
	GMP_TAG_ONLINE_TAXFREE_BUYER_ID_NO							,				/**< 0xDFEEC2,*/
	GMP_TAG_ONLINE_TAXFREE_BUYER_ID_DATE                        ,				/**< 0xDFEEC3,*/
	GMP_TAG_ONLINE_TAXFREE_BUYER_CITY                           ,				/**< 0xDFEEC4,*/
	GMP_TAG_ONLINE_TAXFREE_BUYER_COUNTRY                        ,				/**< 0xDFEEC5,*/
	GMP_TAG_ONLINE_TAXFREE_BUYER_COUNTRY_CODE                   ,				/**< 0xDFEEC6,*/

	GMP_EXT_DEVICE_VAS_LOYALTY_SERVICE							= 0xDFEED0,     /**< 0xDFEED0,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_SERVICE_INDEX					,				/**< 0xDFEED1, (uint32) define loyalty application service index */
	GMP_EXT_DEVICE_VAS_LOYALITY_SERVICE_ID						, 				/**< 0xDFEED2, (uint32) define loyalty application service id */
	GMP_EXT_DEVICE_VAS_LOYALITY_SERVICE_NAME					, 				/**< 0xDFEED3, (uint8)  loyalty service name */
	GMP_EXT_DEVICE_VAS_LOYALITY_SERVICE_CUSTOMER_ID				, 				/**< 0xDFEED4, (uint8)  customer ID */
	GMP_EXT_DEVICE_VAS_LOYALITY_SAYISI						    , 				/**< 0xDFEED5, (uint8)  Loyatlty service count */
	GMP_EXT_DEVICE_VAS_LOYALITY_SERVICE_CUSTOMER_ID_TYPE		, 				/**< 0xDFEED6, (uint8)  Customer ID Type*/
	GMP_EXT_DEVICE_VAS_LOYALITY_SERVICE_DISCOUNT_AMOUNT 		, 				/**< 0xDFEED7, (bcd)    Total Discount Amount*/
	GMP_EXT_DEVICE_VAS_LOYALITY_BENEFIT_REQUEST	 				, 				/**< 0xDFEED8, (uint8)  Benefit Request*/
	GMP_EXT_DEVICE_VAS_LOYALITY_PROCESS_COMMAND	 				, 				/**< 0xDFEED9, (uint8)  Process Command*/
	GMP_EXT_DEVICE_VAS_LOYALITY_PROCESS_VERSION	 				, 				/**< 0xDFEEDA, (uint8)  Process Type - defines the data structure*/
	GMP_EXT_DEVICE_VAS_LOYALITY_PROCESS_DATA	 				, 				/**< 0xDFEEDB, (uint8)  Process Data [in,out]*/
	GMP_EXT_DEVICE_VAS_LOYALITY_PROCESS_PAY_AMOUNT				,				/**< 0xDFEEDC, (uint8)  Loyalty pay amount*/
	GMP_EXT_DEVICE_VAS_LOYALITY_PROCESS_PAY_INDEX				,				/**< 0xDFEEDD, (uint8)  Loyalty pay index*/
	GMP_EXT_DEVICE_VAS_LOYALITY_RET_CODE						,				/**< 0xDFEEDE,  */

	GMP_EXT_DEVICE_VAS_LOYALITY_BENEFIT_LIST					= 0xDFEEE0,		/**< 0xDFEEE0, (uint8)  Loyalty Benefits*/

	GMP_EXT_DEVICE_VAS_LOYALITY_OFFERS_RECORD					= 0xDFEEE5,		/**< 0xDFEEE5,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_OFFERS_COUNT					,				/**< 0xDFEEE6,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_OFFERS_INDEX					,				/**< 0xDFEEE7,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_OFFERS_TYPE						,				/**< 0xDFEEE8,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_OFFERS_DISCOUNT					,				/**< 0xDFEEE9,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_OFFERS_TEXT						,				/**< 0xDFEEEA,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_OFFERS_TRANS_ID					,				/**< 0xDFEEEB,  */

	GMP_EXT_DEVICE_VAS_LOYALITY_PUAN_RECORD						= 0xDFEEF0,		/**< 0xDFEEF0,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_PUAN_INDEX						,				/**< 0xDFEEF1,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_PUAN_AMOUNT						,				/**< 0xDFEEF2,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_PUAN_NAME						,				/**< 0xDFEEF3,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_PUAN_TYPE						,				/**< 0xDFEEF4,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_PUAN_TEXT						,				/**< 0xDFEEF5,  */
	GMP_EXT_DEVICE_VAS_LOYALITY_PUAN_FLAG						,				/**< 0xDFEEF6,  */

	GMP_EXT_ECR_CERTIFICATE										= 0xDFEF00,		/**< 0xDFEF00,  */
	GMP_TAG_CERTIFICATE											= 0xDFEF01,		/**< 0xDFEF01, (uint8[?]) ECR Certificate, Pecr */
	GMP_TAG_KEY_EXCHANGE_PERIOD									,				/**< 0xDFEF02, (bcd[2]) Key Expaire counter provided by ECR. It is in days and maximum 700 days. When expires, pairing must be done again */
	GMP_TAG_CRIPTOGRAM 											,				/**< 0xDFEF03, (uint8[256]) Cryptogram A= g^a mod(p)  Cryptogram B= g^b mod(p) */
	GMP_TAG_STATUS 												,				/**< 0xDFEF04, (uint8[4]) BIT0: Pairing OK, BIT1: Pairing Expaired, BIT2: Non-Fiscal ECR, BIT3: Fiscal Mode , BIT4: ECR Parameter is Ready */
	GMP_TAG_RESERVED_XX1	 	 	 							,				/**< 0xDFEF05,  */
	GMP_TAG_HATA_KODU 											,				/**< 0xDFEF06, (bcd[2]) Return Code */
	GMP_TAG_URETICI_ALAN 										,				/**< 0xDFEF07,  */
	GMP_TAG_RESERVED_XX2 										,				/**< 0xDFEF08,  */
	GMP_TAG_EFT_POS_INDEX 										,				/**< 0xDFEF09, (uint8) External Device Index */
	GMP_TAG_OKC_IMZA_A											,				/**< 0xDFEF0A, (uint8[256]) ECR Signature Data. Signature of A by S_ECR */
	GMP_TAG_SURUCU_VERSIYON 									,				/**< 0xDFEF0B, (uint8[15]) External Device software driver version */
	GMP_TAG_PRIME_NUMBER										,				/**< 0xDFEF0C, (uint8[256]) Prime number generated by ECR (p)*/
	GMP_TAG_GENERATOR											,				/**< 0xDFEF0D, (bcd[1]) DH Generater (g) */
	GMP_TAG_ANAHTAR_KONTROL										,				/**< 0xDFEF0E, (uint8[32]) Key Verification Control Data, AES (KENC, FF..FF) */
	GMP_TAG_SHA_HMAC_VERIFY_VALUE								,				/**< 0xDFEF0F,  */
	GMP_MTU_SIZE												,				/**< 0xDFEF10, (uint16) MTU Size of the GMP3 comm buffers */
	GMP_TAG_OPTIONS                                             ,               /**< 0xDFEF11, (uint8[30])Generic Options */
	GMP_TAG_VERSION                                             ,               /**< 0xDFEF12, (uint8[30])Generic Version */
	GMP_TAG_GMP_VERSIYON										,               /**< 0xDFEF13, (uint8) GMP3 Version */

	GMP_EXT_DEVICE_MEMORYACCESS_DEVICEID						= 0xDFEF20,		/**< 0xDFEF20,  */
	GMP_EXT_DEVICE_MEMORYACCESS_CHIPID							,				/**< 0xDFEF21,  */
	GMP_EXT_DEVICE_MEMORYACCESS_STARTADDRESS					,				/**< 0xDFEF22,  */
	GMP_EXT_DEVICE_MEMORYACCESS_LEN								,				/**< 0xDFEF23,  */
	GMP_EXT_DEVICE_MEMORYACCESS_DATA							,				/**< 0xDFEF24,  */
	GMP_EXT_DEVICE_MEMORYACCESS_SECTOR							,				/**< 0xDFEF25,  */

	GMP_EXT_DEVICE_PP_ACCESS_SUBCOMMAND							= 0xDFEF30,		/**< 0xDFEF30,  */
	GMP_EXT_DEVICE_PP_ACCESS_FUNC								,				/**< 0xDFEF32,  */

	GMP_EXT_DEVICE_HEADER										= 0xDFEF40,		/**< 0xDFEF40,  */
	GMP_EXT_DEVICE_HEADER_SICIL_KODU							,				/**< 0XDFEF41,  */
	GMP_EXT_DEVICE_HEADER_TERM_SERI_NO							,				/**< 0XDFEF42,  */
	GMP_EXT_DEVICE_HEADER_URUN_KODU								,				/**< 0XDFEF43,  */
	GMP_EXT_DEVICE_HEADER_SW_VERSIYON							,				/**< 0XDFEF44,  */
	GMP_EXT_DEVICE_HEADER_MERCHANT_NAME							,				/**< 0XDFEF45,  */
	GMP_EXT_DEVICE_HEADER_MERCHANT_ADDRESS						,				/**< 0XDFEF46,  */
	GMP_EXT_DEVICE_HEADER_VAT_OFFICE							,				/**< 0XDFEF47,  */
	GMP_EXT_DEVICE_HEADER_VAT_NUMBER							,				/**< 0XDFEF48,  */
	GMP_EXT_DEVICE_HEADER_ACTIVE								,				/**< 0XDFEF49,  */
	GMP_EXT_DEVICE_HEADER_EKU_COUNT								,				/**< 0XDFEF4A,  */
	GMP_EXT_DEVICE_HEADER_INDEX									,				/**< 0XDFEF4B,  */
	GMP_EXT_DEVICE_HEADER_HEADER_TOTAL							,				/**< 0XDFEF4C,  */
	GMP_EXT_DEVICE_HEADER_MERSIS_NO								,				/**< 0XDFEF4D,  */
	GMP_EXT_DEVICE_HEADER_TICARI_SICIL_NO						,				/**< 0XDFEF4E,  */
	GMP_EXT_DEVICE_HEADER_WEB_ADDRESS							,				/**< 0XDFEF4F,  */
	GMP_EXT_DEVICE_HEADER_INIT_DATE_TIME						,				/**< 0XDFEF50,  */
	GMP_EXT_DEVICE_HEADER_INIT_Z_NO								,				/**< 0XDFEF51,  */
	GMP_EXT_DEVICE_HEADER_INIT_F_NO								,				/**< 0XDFEF52,  */
	GMP_EXT_DEVICE_HEADER_CLOSE_DATE_TIME						,				/**< 0XDFEF53,  */
	GMP_EXT_DEVICE_HEADER_CLOSE_Z_NO							,				/**< 0XDFEF54,  */
	GMP_EXT_DEVICE_HEADER_CLOSE_F_NO							,				/**< 0XDFEF55,  */
	GMP_EXT_DEVICE_HEADER_TAXPAYER_ID							,				/**< 0XDFEF56,  */

	GMP_EXT_DEVICE_APPINFO										= 0xDFEF60,		/**< 0xDFEF60,  */
	GMP_EXT_DEVICE_APPINFO_AMOUNT                               ,				/**< 0xDFEF61,  */
	GMP_EXT_DEVICE_APPINFO_VAT									,				/**< 0xDFEF62,  */
	GMP_EXT_DEVICE_APPINFO_DATE_TIME							,				/**< 0xDFEF63,  */
	GMP_EXT_DEVICE_APPINFO_DATE_TIME_DELTA						,				/**< 0xDFEF64,  */
	GMP_EXT_DEVICE_APPINFO_BUFLEN								,				/**< 0xDFEF65,  */
	GMP_EXT_DEVICE_APPINFO_RECLEN								,				/**< 0xDFEF66,  */
	GMP_EXT_DEVICE_APPINFO_REMLEN								,				/**< 0xDFEF67,  */
	GMP_EXT_DEVICE_APPINFO_Z_NO									,				/**< 0xDFEF68,  */
	GMP_EXT_DEVICE_APPINFO_F_NO									,				/**< 0xDFEF69,  */
	GMP_EXT_DEVICE_APPINFO_TYPE									,				/**< 0xDFEF6A,  */
	GMP_EXT_DEVICE_APPINFO_FUNC									,				/**< 0xDFEF6B,  */
	GMP_EXT_DEVICE_APPINFO_DATE_TIME_COUNT						,				/**< 0xDFEF6C,  */
	GMP_EXT_DEVICE_APPINFO_STATUS								,				/**< 0xDFEF6D,  */
	GMP_EXT_DEVICE_APPINFO_DATA 			 					,				/**< 0xDFEF6E,  */
	GMP_EXT_DEVICE_APPINFO_FIRST_TIME							,				/**< 0xDFEF6F,  */
	GMP_EXT_DEVICE_APPINFO_LAST_TIME							,				/**< 0xDFEF70,  */
	GMP_EXT_DEVICE_APPINFO_DATACOUNT_REMAIN						,				/**< 0xDFEF71,  */

	GMP_EXT_DEVICE_MODULE_INFO									= 0xDFEF78,  	/**< 0xDFEF78,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_SW_VERS					,				/**< 0xDFEF79,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_HW_VERS					,				/**< 0xDFEF7A,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_COMPILE_DATE				,				/**< 0xDFEF7B,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_DESPCRIPTION				,				/**< 0xDFEF7C,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_HW_REF					,				/**< 0xDFEF7D,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_HW_SERIAL					,				/**< 0xDFEF7E,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_CPU_ID					,				/**< 0xDFEF7F,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_HASH						,				/**< 0xDFEF80,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_BOOT_VERS					,				/**< 0xDFEF81,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_INTEGRITY					,				/**< 0xDFEF82,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_FLASH1					,				/**< 0xDFEF83,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_FLASH2					,				/**< 0xDFEF84,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_FRAM						,				/**< 0xDFEF85,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_CPU_CRC					,				/**< 0xDFEF86,  */
	GMP_EXT_DEVICE_MODULE_INFO_DEVICE_AUTHENTICATE				,				/**< 0xDFEF87,  */

	GMP_EXT_DEVICE_MODULE_INFO_EKU_LAST_RECORD_DATE_TIME		= 0xDFEF90,		/**< 0xDFEF90,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_LAST_RECORD_AMOUNT			,				/**< 0xDFEF91,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_LAST_RECORD_VAT				,				/**< 0xDFEF92,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_LAST_RECORD_FNO				,				/**< 0xDFEF93,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_LAST_RECORD_ZNO				,				/**< 0xDFEF94,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_LAST_RECORD_TYPE				,				/**< 0xDFEF95,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_LAST_RECORD_STATUS			,				/**< 0xDFEF96,  */
	GMP_EXT_DEVICE_MODULE_INFO_MAP_FREE_AREA					,				/**< 0xDFEF97,  */
	GMP_EXT_DEVICE_MODULE_INFO_MAP_USED_AREA					,				/**< 0xDFEF98,  */
	GMP_EXT_DEVICE_MODULE_INFO_DATA_FREE_AREA					,				/**< 0xDFEF99,  */
	GMP_EXT_DEVICE_MODULE_INFO_DATA_USED_AREA					,				/**< 0xDFEF9A,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_HEADER_USED					,				/**< 0xDFEF9B,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_HEADER_TOTAL					,				/**< 0xDFEF9C,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_STATUS						,				/**< 0xDFEF9D,  */
	GMP_EXT_DEVICE_MODULE_INFO_EKU_CPU_CRC						,				/**< 0xDFEF9E,  */

	GMP_EXT_DEVICE_KEY_EXPIRE_DURATION                          = 0xDFEFA0,		/**< 0xDFEFA0,  */
	GMP_EXT_DEVICE_STATUS_BAGLANTI_SAYISI                       ,				/**< 0xDFEFA1,  */
	GMP_EXT_DEVICE_UYGULAMA_SHA2                                ,				/**< 0xDFEFA2, (uint8[64]) Sum Check HASH (SHA2) value of the external system. This value will be checked by ECR & TSM. */
	GMP_EXT_DEVICE_ECR_MODE                                     ,				/**< 0xDFEFA3,  */
	GMP_EXT_DEVICE_SUPERVISOR_PASSWORD                          ,				/**< 0xDFEFA4,  */
	GMP_EXT_DEVICE_POWER_ON_COUNTER								,				/**< 0xDFEFA5, uint16 (bütün iþlem grubu olan mesajlarda var)*/
	GMP_EXT_DEVICE_PROCESS_TIME									,				/**< 0xDFEFA6, uint32 (ÖKC OK basan versiyonsa bütün iþlem grubu olan mesajlarda var )*/

	GMP_TAG_DATA_TIMEOUT                                        = 0xDFEFB0,		/**< 0xDFEFB0,  */
	GMP_TAG_DATA_TITLE                                          ,				/**< 0xDFEFB1,  */
	GMP_TAG_DATA_MASK                                           ,				/**< 0xDFEFB2,  */
	GMP_TAG_DATA_VALUE                                          ,				/**< 0xDFEFB3,  */
	GMP_TAG_DATA_TAG_ID                                         ,				/**< 0xDFEFB4,  */
	GMP_TAG_DATA_TEXT                                           ,				/**< 0xDFEFB5,  */
	GMP_TAG_DATA_ALIGN                                          ,				/**< 0xDFEFB6,  */
	GMP_TAG_DATA_MAXLEN                                         ,				/**< 0xDFEFB7,  */
	GMP_TAG_DATA_SYMBOL                                         ,				/**< 0xDFEFB8,  */
	GMP_TAG_DATA_BUTTONS                                        ,				/**< 0xDFEFB9,  */
	GMP_TAG_DATA_TYPE											,				/**< 0xDFEFBA,  */
	GMP_TAG_DATA_NAME											,				/**< 0xDFEFBB,  */
	GMP_TAG_DATA_ID												,				/**< 0xDFEFBC,  */
	GMP_TAG_DATA_FLAG											,				/**< 0xDFEFBD,  */
	GMP_TAG_DATA_VERSION                                        ,				/**< 0xDFEFBE,  */
	GMP_TAG_DATA_SUBTYPE                                        ,				/**< 0xDFEFBF,  General porpuse tag used for subType definations */

	GMP_EXT_DEVICE_USER_MESSAGE_EX								= 0xDFEFD0,		/**< 0xDFEFBE,  */
	GMP_EXT_DEVICE_ODEME_UNIQUE_ID								= 0xDFEFE0,		/*16 BYTE CHAR */
	GMP_LAST_ITEM,
} GMP_TAG_LIST_EXT_DEVICE;

/** Error Codes */
typedef enum
{
	TRAN_RESULT_OK												= 0x0000,	/**< 0x0000, Transaction succesful,									GetErrorTurkishDescription() function returns "Ýþlem Baþarýlý sonuçlandý." */
	TRAN_RESULT_NOT_ALLOWED										= 0x0001,	/**< 0x0001, Transaction not allowed,								GetErrorTurkishDescription() function returns "Ýþleme Ýzin Verilmedi." */
	TRAN_RESULT_TIMEOUT											= 0x0002,	/**< 0x0002, Timeout,												GetErrorTurkishDescription() function returns "Zaman Aþýmý." */
	TRAN_RESULT_USER_ABORT										= 0x0004,	/**< 0x0004, User abort,											GetErrorTurkishDescription() function returns "Iþlem Kullanýcý Tarafýndan Sonlandýrýldý." */
	TRAN_RESULT_EKU_PROBLEM										= 0x0008,	/**< 0x0008, Eku Problem,											GetErrorTurkishDescription() function returns "Eku de Sorun Oluþtu." */
	TRAN_RESULT_CONTINUE										= 0x0010,	/**< 0x0010, Transaction Will Continue On ,							GetErrorTurkishDescription() function returns "Ýþlem Devam Ediyor" */
	TRAN_RESULT_NO_PAPER										= 0x0020,	/**< 0x0020, No Paper,												GetErrorTurkishDescription() function returns "Kaðýt Bitti" */

	// FISCAL APPLICATION USER TYPE ERRORS
	APP_ERR_FISCAL_EXCHANGE_RATES_NOT_FOUND 					= 2000,		/**< 2000, EXCHANGE RATES NOT FOUND,								GetErrorTurkishDescription() function returns "Kur Oranlarý Bulunamadý" */
	APP_ERR_FISCAL_ALREADY_CANCELED_ITEM						= 2001,		/**< 2001, ALREADY CANCELED ITEM,									GetErrorTurkishDescription() function returns "Daha Önce Ýptal Edilmiþ Ürün" */
	APP_ERR_FISCAL_INVALID_DISCOUNT_RATE 						= 2002,		/**< 2002, INVALID DISCOUNT RATE,									GetErrorTurkishDescription() function returns "Geçersiz Ýndirim Oraný" */
	APP_ERR_FISCAL_DISCOUNT_RATE_NOT_SET						= 2003,		/**< 2003, DISCOUNT RATE NOT SET,									GetErrorTurkishDescription() function returns "Ýndirim Oraný Set Edilmemiþ" */
	APP_ERR_FISCAL_INVALID_INCREASE_RATE						= 2004,		/**< 2004, INVALID INCREASE RATE,									GetErrorTurkishDescription() function returns "Geçersiz Arttýrým Oraný" */
	APP_ERR_FISCAL_INCREASE_RATE_NOT_SET						= 2005,		/**< 2005, INCREASE RATE NOT SET,									GetErrorTurkishDescription() function returns "Arttýrým Oraný Set Edilmemiþ" */
	APP_ERR_FISCAL_DISCOUNT_ALREADY_DONE						= 2006,		/**< 2006, DISCOUNT ALREADY DONE,									GetErrorTurkishDescription() function returns "Zaten Ýndirim Yapýlmýþ" */
	APP_ERR_FISCAL_INCREASE_ALREADY_DONE						= 2007,		/**< 2007, INCREASE ALREADY DONE,									GetErrorTurkishDescription() function returns "Zaten Arttýrým Yapýlmýþ" */
	APP_ERR_FISCAL_NO_PRETOTAL 									= 2008,		/**< 2008, NOT USED,												GetErrorTurkishDescription() function returns "Kullanýlmýyor" */
	APP_ERR_FISCAL_INVALID_ENTRY 								= 2009,		/**< 2009, INVALID ENTRY,											GetErrorTurkishDescription() function returns "Geçersiz Giriþ" */
	APP_ERR_FISCAL_KDV_RATE_NOT_FOUND							= 2010,		/**< 2010, TAX RATE NOT FOUND,										GetErrorTurkishDescription() function returns "KDV Oraný Bulunamadý" */
	APP_ERR_FISCAL_TICKET_LIMIT_EXCEED							= 2011,		/**< 2011, TICKET LIMIT EXCEED,										GetErrorTurkishDescription() function returns "Fiþ Limiti Aþýldý" */
	APP_ERR_FISCAL_SALE_ITEM_LIMIT_EXCEED						= 2012,		/**< 2012, SALE ITEM LIMIT EXCEED,									GetErrorTurkishDescription() function returns "Ürün Limiti Aþýldý" */
	APP_ERR_FISCAL_CASH_ENTRY_LIMIT_EXCED						= 2013,		/**< 2013, CASH ENTRY LIMIT EXCED,									GetErrorTurkishDescription() function returns "Nakit Ödeme Limiti Aþýldý" */
	APP_ERR_FISCAL_INVALID_CURRENCY								= 2014,		/**< 2014, INVALID CURRENCY,										GetErrorTurkishDescription() function returns "Geçersiz Kur" */
	APP_ERR_NOT_ALLOWED_BEFORE_GIB_CONNECTION					= 2015,		/**< 2015, NOT ALLOWED BEFORE GIB CONNECTION,						GetErrorTurkishDescription() function returns "Ýþlemi Yapabilmek Ýçin Önce GIB e Baðlanýlmalý" */
	APP_ERR_KISIM_FIYAT_LIMITI_ASILAMAZ							= 2016,		/**< 2016, DEPARTMENT AMOUNT LIMIT EXCEED,							GetErrorTurkishDescription() function returns "Kýsým Satýþ Limiti Aþýlamaz" */
	APP_ERR_FISCAL_DEPARTMENT_ENTRY_INCOMPLETE					= 2017, 	/**< 2017, NOT USED,												GetErrorTurkishDescription() function returns "Kullanýlmýyor" */
	APP_ERR_FISCAL_EXCHANGE_RATE_NOT_FOUND						= 2018,		/**< 2018, EXCHANGE RATE NOT FOUND,									GetErrorTurkishDescription() function returns "Kur Oraný Bulunamadý" */
	APP_ERR_APL_CRC_ERROR										= 2019,		/**< 2019, APPLICATION CRC ERROR,									GetErrorTurkishDescription() function returns "Uygulama: CRC Hatasý" */
	APP_ERR_APL_VERS_ERROR										= 2020,		/**< 2020, APPLICATION VERSION ERROR,								GetErrorTurkishDescription() function returns "Uygulama: Versiyon Hatasý" */
	APP_ERR_APL_COMPLETE_PAYMENT								= 2021,		/**< 2021, APPLICATION COMPLETE PAYMENT,							GetErrorTurkishDescription() function returns "Uygulama: Ödeme Bulundu" */
	APP_ERR_APL_CREDIT_CANNOT_BIGGER_THAN_REMAIN_AMOUNT			= 2022,		/**< 2022, APPLICATION CREDIT CANNOT BIGGER THAN REMAIN AMOUNT,		GetErrorTurkishDescription() function returns "Uygulama : Tutar Kalandan Fazla Olamaz" */
	APP_ERR_APL_CREDIT_PAID_AMOUNT_MISSING						= 2023,		/**< 2023, APPLICATION CREDIT PAID AMOUNT MISSING,					GetErrorTurkishDescription() function returns "Uygulama : Ödeme Tutarý Eksik" */
	APP_ERR_APL_CREDIT_PAID_ONLY_ONE_TIME_ALLOWED				= 2024,		/**< 2024, APPLICATION CREDIT PAID ONLY ONE TIME ALLOWED,			GetErrorTurkishDescription() function returns "Uygulama : Ödeme Sadece Bir Kez Kabul Edilir" */
	APP_ERR_FISCAL_INVALID_DATE_TIME							= 2025,		/**< 2025, INVALID DATE TIME,										GetErrorTurkishDescription() function returns "Geçersiz Tarih Zaman" */
	APP_ERR_MAX_RECEIPT_COUNTER_REACHED							= 2026, 	/**< 2026, REACHED TO MAXIMUM RECEIPT COUNTER,						GetErrorTurkishDescription() function returns "En Yüksek Fiþ Sayýsýna Ulaþýldý" */
	APP_ERR_APL_NO_PAPER										= 2027,		/**< 2027, NOT USED,												GetErrorTurkishDescription() function returns "Kullanýlmýyor" */
	APP_ERR_APL_PARAMETRE_NOT_FOUND								= 2028,		/**< 2028, APPLICATION PARAMETRE NOT FOUND,							GetErrorTurkishDescription() function returns "Uygulama : Parametre Bulunamadý" */
	APP_ERR_EKU_SOFTWARE_VERSION								= 2029,		/**< 2029, EKU SOFTWARE VERSION,									GetErrorTurkishDescription() function returns "EKU Yazýlý Versiyonu Hatalý" */
	APP_ERR_FISCAL_SOFTWARE_VERSION								= 2030, 	/**< 2030, FISCAL SOFTWARE VERSION,									GetErrorTurkishDescription() function returns "Mali Yazýlým Verisyonu Hatasý" */
	APP_ERR_CIHAZ_GECICI_OLARAK_KAPATILDI						= 2031,		/**< 2031, DEVICE CLOSED,											GetErrorTurkishDescription() function returns "Cihaz Geçici Olarak Kapatýldý" */
	APP_ERR_CIHAZ_ACIL_MODA_ALINMIS								= 2032,		/**< 2032, CIHAZ ACIL MODA ALINMIS,									GetErrorTurkishDescription() function returns "Cihaz Acil Moda Alýnmýþ" */
	APP_ERR_APL_DAILY_MEMORY_DELETED							= 2033,		/**< 2033, APPLICATION DAILY MEMORY DELETED,						GetErrorTurkishDescription() function returns "Uygulama : Günük Hafýza Silinmiþ" */
	APP_ERR_APL_CUMULATIVE_COUNTER_FULL							= 2034,		/**< 2034, APPLICATION CUMULATIVE COUNTER FULL,						GetErrorTurkishDescription() function returns "Uygulama : Kümülatif Sayacý Dolu" */
	APP_ERR_APL_OUT_OF_SERVICE									= 2035,		/**< 2035, APPLICATION OUT OF SERVICE,								GetErrorTurkishDescription() function returns "Uygulama : Servis Dýþý" */
	APP_ERR_APL_OUT_OF_SERVICE_WARNING							= 2036,		/**< 2036, APPLICATION OUT OF SERVICE WARNING,						GetErrorTurkishDescription() function returns "Uygulama : Servis Dýþý Uyarý" */
	APP_ERR_APL_FONT_FILE_LOAD									= 2037,		/**< 2037, APPLICATION FONT FILE LOAD,								GetErrorTurkishDescription() function returns "Uygulama : Font Dosyasý Yükleme Hatasý" */
	APP_ERR_APL_FONT_POLICY_NOT_FOUND							= 2038,		/**< 2038, APPLICATION FONT POLICY NOT FOUND,						GetErrorTurkishDescription() function returns "Uygulama : "Font Policy Bulunamadý" */
	APP_ERR_APL_CREDIT_PAY_AMOUNT_ZERO							= 2039,		/**< 2039, APPLICATION CREDIT PAY AMOUNT ZERO,						GetErrorTurkishDescription() function returns "Uygulama : Kartlý ödeme tutarý 0" */
	APP_ERR_APL_DB_ERROR										= 2040,		/**< 2040, APPLICATION DB ERROR,									GetErrorTurkishDescription() function returns "Uygulama : Veritabaný Hatasý" */
	APP_ERR_TICKET_SALE_ITEM_LIMIT_EXCEED						= 2041,		/**< 2041, TICKET SALE ITEM LIMIT EXCEED,							GetErrorTurkishDescription() function returns "Urün Satýþ Limiti Aþýldý" */
	APP_ERR_APL_PIN_ERROR										= 2042,		/**< 2042, APPLICATION PIN ERROR,									GetErrorTurkishDescription() function returns "Uygulama : Pin Hatasý" */
	APP_ERR_PAYMENT_APPL_MESSAGE								= 2043,		/**< 2043, PAYMENT APPLICATION MESSAGE,								GetErrorTurkishDescription() function returns "Ödeme Uygulamasý Mesaj Hatasý" */
	APP_ERR_APL_DB_DUBLICATE_RECORD								= 2044,		/**< 2044, APPLICATION DB DUBLICATE RECORD,							GetErrorTurkishDescription() function returns "Uygulama : Veritabaný Ayný Kayýt Hatasý" */
	APP_ERR_APL_TRANSACTION_CORRUPTED							= 2045,		/**< 2045, APPLICATION TRANSACTION CORRUPTED,						GetErrorTurkishDescription() function returns "Uygulama : Ýþlem Bozulmuþ" */
	APP_ERR_APL_PAYMENT_MUST_COMPLETE							= 2046,		/**< 2046, APPLICATION PAYMENT MUST COMPLETE,						GetErrorTurkishDescription() function returns "Uygulama  :Ödeme Tamamlanmalý" */
	APP_ERR_INVOICE_LIMIT_EXCEED								= 2047,		/**< 2047, INVOICE LIMIT EXCEED,									GetErrorTurkishDescription() function returns "Fatura Limiti Aþýldý" */
	APP_ERR_TRANSACTION_NOT_SAVED								= 2048,		/**< 2048, TRANSACTION NOT SAVED,									GetErrorTurkishDescription() function returns "Ýþlem Kaydedilmedi" */
	APP_ERR_INVOICE_NO_ENTRY									= 2049,		/**< 2049, INVOICE NO ENTRY,										GetErrorTurkishDescription() function returns "Fatura : Giriþ Yapýlmamýþ" */
	APP_ERR_INACTIVE_PERIPHERAL									= 2050,		/**< 2050, INACTIVE PERIPHERAL,										GetErrorTurkishDescription() function returns "Aktif Olmayan Donaným" */
	APP_ERR_DEVICE_CLOSED										= 2051,		/**< 2051, DEVICE CLOSED,											GetErrorTurkishDescription() function returns "Cihaz Kapatýldý" */
	APP_ERR_TEST_REQUIRED										= 2052,		/**< 2052, TEST REQUIRED,											GetErrorTurkishDescription() function returns "Test Gerekli" */
	APP_ERR_CASHIER_ENTRY_REQUIRED								= 2053,		/**< 2053, CASHIER ENTRY REQUIRED,									GetErrorTurkishDescription() function returns "Kasiyer Giriþi Gerekli" */
	APP_ERR_FLIGHT_MODE											= 2054,		/**< 2054, FLIGHT MODE,												GetErrorTurkishDescription() function returns "Uçuþ Modu" */
	APP_ERR_NO_PARAM											= 2055,		/**< 2055, ECR PARAMETER IS NOT AVAILABLE,							GetErrorTurkishDescription() function returns "OKC Parametreleri Bulunamadý. Lütfen Parametre Yükleyin" */
	APP_ERR_NOT_FISCAL											= 2056,		/**< 2056, ECR MUST BE FISCALIZED,									GetErrorTurkishDescription() function returns "OKC Malileþtirilmeli" */
	APP_ERR_FISCAL_RECORD_NOT_AVAILABLE							= 2057,		/**< 2057, FISCAL RECORD NOT AVAILABLE,								GetErrorTurkishDescription() function returns "Mali Kayýt Uygun Deðil" */
	APP_ERR_CITIZEN_NUMBER_ENTRY								= 2058,		/**< 2058, CITIZEN NUMBER ENTRY,									GetErrorTurkishDescription() function returns "Kimlik Numarasý Hatasý" */
	APP_ERR_INVALID_USER_MODE									= 2059,		/**< 2059, INVALID USER MODE,										GetErrorTurkishDescription() function returns "Geçersiz Kullanýcý Modu" */
	APP_ERR_PAYMENT_NOT_ALLOWED									= 2060,		/**< 2060, PAYMENT NOT ALLOWED,										GetErrorTurkishDescription() function returns "Ödeme Kabul Edilmedi" */
	APP_ERR_NO_CASH												= 2061,		/**< 2061, CASH IN THE ECR IS NOT AVAILABLE,						GetErrorTurkishDescription() function returns "ECR içindeki Cash Kullanýlamaz." */
	APP_ERR_PARAMETER_DW_ERROR_FOR_TEST							= 2062,		/**< 2062, PARAMETER DW ERROR FOR TEST,								GetErrorTurkishDescription() function returns "Ýnternal testler için ayrýldý" */
	APP_ERR_MAX_TRY_COUNTER_EXCEED								= 2063,		/**< 2063, MAX TRY COUNTER EXCEED,									GetErrorTurkishDescription() function returns "Maksimum Deneme Sayýsý Aþýldý" */
	APP_ERR_NOT_ALLOWED											= 2064,		/**< 2064, NOT ALLOWED,												GetErrorTurkishDescription() function returns "Kabul Edilmedi" */
	APP_ERR_RESOURCE_PROBLEM									= 2065,		/**< 2065, RESOURCE PROBLEM,										GetErrorTurkishDescription() function returns "Kaynak Problemi Oluþtu" */
	APP_ERR_ITEM_PRICE_NOT_EXISTS								= 2066,		/**< 2066, ITEM PRICE NOT EXISTS,									GetErrorTurkishDescription() function returns "Ürün Tutarý Bulunamadý" */
	APP_ERR_FIS_LIMITI_ASILAMAZ									= 2067,		/**< 2067, FIS LIMITI ASILAMAZ,										GetErrorTurkishDescription() function returns "Fiþ Limiti Aþýlamaz" */
	APP_ERR_NO_ITEM												= 2068,		/**< 2068, NO ITEM,													GetErrorTurkishDescription() function returns "Ürün Yok" */
	APP_ERR_PAYMENT_FOUND										= 2069,		/**< 2069, PAYMENT FOUND,											GetErrorTurkishDescription() function returns "Ödeme Bulundu. Cihaz üzerinde bulunan tüm ödemeler iptal edilmeli." */
	APP_ERR_MATRAHSIZ_FOUND										= 2070,		/**< 2070, MATRAHSIZ FOUND,											GetErrorTurkishDescription() function returns "Matrahsýz Bulundu" */
	APP_ERR_NOT_APPROVED										= 2071,		/**< 2071, NOT APPROVED,											GetErrorTurkishDescription() function returns "Uygun Deðil" */
	APP_ERR_ONLY_COUPON											= 2072,		/**< 2072, ONLY COUPON,												GetErrorTurkishDescription() function returns "Sadece Kupon" */
	APP_ERR_NO_AMOUNT											= 2073,		/**< 2073, NO AMOUNT,												GetErrorTurkishDescription() function returns "Tutar Bulunamadý" */
	APP_ERR_CURRENCY_NOT_SUPPORTED								= 2074,		/**< 2074, CURRENCY NOT SUPPORTED,									GetErrorTurkishDescription() function returns "Kur desteklenmiyor" */
	APP_ERR_TICKET_TOTAL_CANNOT_BE_ZERO							= 2075,		/**< 2075, TICKET TOTAL CANNOT BE ZERO,								GetErrorTurkishDescription() function returns "Fiþ Toplamý 0 olamaz" */
	APP_ERR_INVOICE_NOT_ALLOWED									= 2076,		/**< 2076, INVOICE TRANSACTION NOT ALLOWED,							GetErrorTurkishDescription() function returns "Geçersiz Fatura Ýþlemi" */
	APP_ERR_TICKET_HEADER_NOT_PRINTED							= 2077,		/**< 2077, TICKET HEADER NOT PRINTED,								GetErrorTurkishDescription() function returns "Fiþ Baþlýðý Yazdýrýlmadý" */
	APP_ERR_TICKET_HEADER_ALREADY_PRINTED						= 2078,		/**< 2078, TICKET HEADER ALREADY PRINTED,							GetErrorTurkishDescription() function returns "Fiþ Baþlýðý Zaten Yazdýrýldý" */
	APP_ERR_PLU_NOT_FOUND										= 2079,		/**< 2079, PLU NOT FOUND,											GetErrorTurkishDescription() function returns "PLU Barkod Bulunamadý" */
	APP_ERR_ALREADY_DONE										= 2080,		/**< 2080, ALREADY DONE,											GetErrorTurkishDescription() function returns "Zaten Yapýlmýþ Ýþlem" */
	APP_ERR_INVALID_PARAMETER_TAXINDEX							= 2081,		/**< 2081, INVALID PARAMETER TAXINDEX,								GetErrorTurkishDescription() function returns "Geçersiz KDV Index Parametresi" */
	APP_ERR_INVALID_PARAMETER_TAXRATE							= 2082,		/**< 2082, INVALID PARAMETER TAXRATE,								GetErrorTurkishDescription() function returns "Geçersiz KDV Oraný Parametresi" */
	APP_ERR_MISSING_PARAMETER									= 2083,		/**< 2083, MISSING PARAMETER,										GetErrorTurkishDescription() function returns "Parametre Bulunamadý" */
	APP_ERR_MISMATCH_PARAMETER									= 2084,		/**< 2084, MISMATCH PARAMETER,										GetErrorTurkishDescription() function returns "Parametre Uyuþmadý" */
	APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_NO_MORE_ERROR_CODE		= 2085,		/**< 2085, PAYMENT NOT SUCCESSFUL AND NO MORE ERROR CODE,			GetErrorTurkishDescription() function returns "Ödeme Baþarýsýz (Hata Kodu Bulunamadý)" */
	APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_MORE_ERROR_CODE			= 2086,		/**< 2086, PAYMENT NOT SUCCESSFUL AND MORE ERROR CODE,				GetErrorTurkishDescription() function returns "Ödeme Baþarýsýz (Hata Kodu Bulundu)" */
	APP_ERR_INVALID_PAYMENT_TYPE								= 2087,		/**< 2087, INVALID PAYMENT TYPE,									GetErrorTurkishDescription() function returns "Geçersiz Ödeme Tipi" */
	APP_ERR_VAS_NOT_AVAILABLE									= 2088,		/**< 2088, VAS NOT AVAILABLE,										GetErrorTurkishDescription() function returns "VAS Uygulamasý Uygun Deðil" */
	APP_ERR_INVALID_CAR_IDENTIFICATION							= 2089,		/**< 2089, INVALID CARD IDENTIFICATION ,							GetErrorTurkishDescription() function returns "Lütfen Data Uzunluðunu Kontrol Edin" */
	APP_ERR_ALLOCATION											= 2090,		/**< 2090, NOT USED,												GetErrorTurkishDescription() function returns "Kullanýlmýyor" */
	APP_ERR_MISSING_TAXFREE_PARAMETER							= 2091,		/**< 2091, MISSING TAXFREE PARAMETER,								GetErrorTurkishDescription() function returns "TaxFree Parametresi Bulunamadý" */
	APP_ERR_INVALID_TAXREFUND_VALUE								= 2092,		/**< 2092, INVALID TAXREFUND VALUE,									GetErrorTurkishDescription() function returns "Geçersiz TaxRefund Deðeri" */
	APP_ERR_TAXFREE_NOT_STARTED									= 2093,		/**< 2093, TAXFREE NOT STARTED,										GetErrorTurkishDescription() function returns "TaxFree Baþlamadý" */
	APP_ERR_TAXFREE_NOT_COMPLETED								= 2094,		/**< 2094, TAXFREE NOT COMPLETED,									GetErrorTurkishDescription() function returns "TaxFree Tamamlanmadý" */
	APP_ERR_TAXLESS_NOT_SUPPORTED								= 2095,		/**< 2095, TAXLESS NOT SUPPORTED,									GetErrorTurkishDescription() function returns "TaxFree Desteklenmiyor" */
	APP_ERR_INVALID_TICKET_TYPE									= 2096,		/**< 2096, INVALID TICKET TYPE,										GetErrorTurkishDescription() function returns "Geçersiz Fiþ Tipi" */
	APP_ERR_NOT_ALLOWED_AS_GMP3_TRANSACTION_IS_PENDING			= 2097,		/**< 2097, NOT ALLOWED AS GMP3 TRANSACTION IS PENDING,				GetErrorTurkishDescription() function returns "Cihazda Tamamlanmamýþ GMP3 Ýþlemi Olduðundan Bu Ýþlem Yapýlamaz" */
	APP_ERR_DEVICE_REASSIGNED									= 2098,		/**< 2098, DEVICE REASSIGNED,										GetErrorTurkishDescription() function returns "Cihaz Devredilmis" */
	APP_ERR_DEPT_FOOD_RECEIPT_ITEM_NOT_ENABLE					= 2099,		/**< 2098, DEPT_FOOD_RECEIPT_ITEM_NOT_ENABLE,						GetErrorTurkishDescription() function returns "Item bulunamadi" */
	APP_ERR_CHECK_IP_ADDRES_FORMAT								= 2100,		/**< 2100, CHECK IP ADDRES FORMAT,									GetErrorTurkishDescription() function returns "IP Adres Format Hatasý" */
	APP_ERR_WRONG_SERVICE_CARD_PIN								= 2101,		/**< 2101, WRONG SERVICE CARD PIN,									GetErrorTurkishDescription() function returns "Yanlýþ Servis Kart Þifresi" */
	APP_ERR_UNDEFINED_COM_INTERFACE								= 2102,		/**< 2102, UNDEFINED COM INTERFACE,									GetErrorTurkishDescription() function returns "Tanýmlý Olmayan COM Arayüzü" */
	APP_ERR_BASE_NOT_FOUND										= 2103,		/**< 2103, BASE NOT FOUND,											GetErrorTurkishDescription() function returns "BASE Bulunamadý" */
	APP_ERR_ETHERNET_MODUL_CALISMIYOR							= 2104,		/**< 2104, ETHERNET MODUL NOT WORKING,								GetErrorTurkishDescription() function returns "Ethernet Modülü Çalýþmýyor" */
	APP_ERR_ETHERNET_NOT_PLUGGED								= 2105,		/**< 2105, ETHERNET NOT PLUGGED,									GetErrorTurkishDescription() function returns "Ethernet kablosu Takýlý Deðil" */
	APP_ERR_ETHERNET_BASE_NOT_READY								= 2106,		/**< 2106, ETHERNET BASE NOT READY,									GetErrorTurkishDescription() function returns "Ethernet Base Hazýr Deðil" */
	APP_ERR_ETHERNET_OUT_OF_BASE								= 2107,		/**< 2107, ETHERNET OUT OF BASE,									GetErrorTurkishDescription() function returns "Ethernet Base Takýlý Deðil" */
	APP_ERR_GPRS_ERROR_NO_SIM									= 2108,		/**< 2108, GPRS ERROR NO SIM,										GetErrorTurkishDescription() function returns "GPRS hatasý : Sim Kart Yok" */
	APP_ERR_GPRS_APN											= 2109,		/**< 2109, GPRS APN,												GetErrorTurkishDescription() function returns "GPRS hatasý : APN Hatasý" */
	APP_ERR_GPRS_BAD_PIN										= 2110,		/**< 2110, GPRS BAD PIN,											GetErrorTurkishDescription() function returns "GPRS hatasý : Geçersiz Þifre" */
	APP_ERR_GPRS_SIM_LOCK										= 2111,		/**< 2111, GPRS SIM LOCK,											GetErrorTurkishDescription() function returns "GPRS hatasý : Sim Kartý Blokelendi" */
	APP_ERR_GPRS_NO_SIGNAL										= 2112,		/**< 2112, GPRS NO SIGNAL,											GetErrorTurkishDescription() function returns "GPRS hatasý : Sinyal Yok" */
	APP_ERR_GPRS_DISCONNCTED									= 2113,		/**< 2113, GPRS DISCONNCTED,										GetErrorTurkishDescription() function returns "GPRS hatasý : Baðlantý Hatasý" */
	APP_ERR_GPRS_UNDEFINED										= 2114,		/**< 2114, GPRS UNDEFINED,											GetErrorTurkishDescription() function returns "GPRS hatasý : Tanýmsýz" */
	APP_ERR_SSL_PROFILE											= 2115,		/**< 2115, SSL PROFILE,												GetErrorTurkishDescription() function returns "SSL Profil Hatasý " */
	APP_ERR_WRONG_SERVICE_CARD									= 2116,		/**< 2116, WRONG SERVICE CARD,										GetErrorTurkishDescription() function returns "Hatalý Servis Kartý" */
	APP_ERR_COMMUNICATION_CHANNEL_NOT_DEFINED					= 2117,		/**< 2117, COMMUNICATION CHANNEL NOT DEFINED,						GetErrorTurkishDescription() function returns "Haberleþme Kanalý Tanýmlý Deðil" */
	APP_ERR_EXCEPTION_CODE_NOT_FOUND							= 2118,
	APP_ERR_YEMEKCEKI_PAYMENT									= 2119,
	APP_ERR_VAS_VERSION_MISMATCH								= 2120,
	APP_ERR_VAS_SERVICE_NOT_AVAILABLE							= 2121,
	APP_ERR_VAS_CUSTOMER_IDENTIFICATION							= 2122,
	APP_ERR_INVALID_EXCEPTION_CODE_TYPE							= 2123,
	APP_ERR_INVALID_EXCEPTION_CODE								= 2124,
	APP_ERR_VAS_LOYALTY_PROCESS									= 2125,
	APP_ERR_INVALID_INVOICE_ENTRY								= 2126,

	APP_ERR_GIB_ROOT_CERT_NOT_FOUND 							= 2200,		/**< 2200, GIB ROOT CERT NOT FOUND,									GetErrorTurkishDescription() function returns "GIB Kök Sertifikasý Bulunamadý" */
	APP_ERR_GIB_SUB_ROOT_CERT_NOT_FOUND							= 2201,		/**< 2201, GIB SUB ROOT CERT NOT FOUND,								GetErrorTurkishDescription() function returns "GIB Alt Kök Sertifikasý Bulunamadý" */
	APP_ERR_TSM_ROOT_CERT_NOT_FOUND								= 2202,		/**< 2202, TSM ROOT CERT NOT FOUND,									GetErrorTurkishDescription() function returns "TSM Kök Sertifikasý Bulunamadý" */
	APP_ERR_TSM_SUB_ROOT_CERT_NOT_FOUND							= 2203,		/**< 2203, TSM SUB ROOT CERT NOT FOUND,								GetErrorTurkishDescription() function returns "TSM Alt Kök Sertifikasý Bulunamadý" */
	APP_ERR_OKTEM_CERT_NOT_FOUND								= 2204,		/**< 2204, OKTEM CERT NOT FOUND,									GetErrorTurkishDescription() function returns "OKTEM Sertifikasý Bulunamadý" */
	APP_ERR_GIB_SIGN_CERT_NOT_FOUND								= 2205,		/**< 2205, GIB SIGN CERT NOT FOUND,									GetErrorTurkishDescription() function returns "GIB Ýmza Sertifikasý Bulunamadý" */
	APP_ERR_GIB_SIFRE_CERT_NOT_FOUND							= 2206,		/**< 2206, GIB SIFRE CERT NOT FOUND,								GetErrorTurkishDescription() function returns "GIB Þifre Sertifikasý Bulunamadý" */
	APP_ERR_TSM_SIGN_CERT_NOT_FOUND								= 2207,		/**< 2207, TSM SIGN CERT NOT FOUND,									GetErrorTurkishDescription() function returns "TSM Ýmza Sertifikasý Bulunamadý" */
	APP_ERR_PACK_GIB											= 2208,		/**< 2208, PACK GIB,												GetErrorTurkishDescription() function returns "GIB Paketinde Sorun Bulundu" */
	APP_ERR_GIB_CERT											= 2209,		/**< 2209, GIB CERT,												GetErrorTurkishDescription() function returns "GIB Sertifika Hatasý" */
	APP_ERR_DATABASE_SILINMIS									= 2210,		/**< 2210, DATABASE REMOVED,										GetErrorTurkishDescription() function returns "Veritabaný Silinmiþ" */
	APP_ERR_OKTEM_CERT_VERIFICATION								= 2211,

	APP_ERR_FILE_COPY											= 2220,		/**< 2220, FILE COPY,												GetErrorTurkishDescription() function returns "Dosya Kopyalama Hatasý" */
	APP_ERR_FILE_OPEN											= 2221,		/**< 2221, FILE OPEN,												GetErrorTurkishDescription() function returns "Dosya Açma Hatasý" */
	APP_ERR_FILE_READ											= 2222,		/**< 2222, FILE READ,												GetErrorTurkishDescription() function returns "Dosya Okuma Hatasý" */
	APP_ERR_FILE_WRITE											= 2223,		/**< 2223, FILE WRITE,												GetErrorTurkishDescription() function returns "Dosya Yazma Hatasý" */
	APP_ERR_BUFFER_MALLOC										= 2224,		/**< 2224, BUFFER MALLOC,											GetErrorTurkishDescription() function returns "Buffer Malloc Hatasý" */
	APP_ERR_FILE_SEEK											= 2225,		/**< 2225, FILE SEEK,												GetErrorTurkishDescription() function returns "Dosya Seek Hatasý" */
	APP_ERR_FILE_EOF											= 2226,		/**< 2226, FILE EOF,												GetErrorTurkishDescription() function returns "Dosya EOF Hatasý" */
	APP_ERR_FILE_MOUNT											= 2227,		/**< 2227, FILE MOUNT,												GetErrorTurkishDescription() function returns "Volume Mount Hatasý" */

	APP_ERR_GMP_PROTOCOL										= 2230,		/**< 2230, GMP PROTOCOL,											GetErrorTurkishDescription() function returns "GMP Protokol Hatasý" */
	APP_ERR_GMP_VERIFICATION									= 2231,		/**< 2231, GMP VERIFICATION,										GetErrorTurkishDescription() function returns "GMP Doðrulama Hatasý" */
	APP_ERR_GMP_LRC												= 2232,		/**< 2232, GMP LRC,													GetErrorTurkishDescription() function returns "GMP LRC Hatasý" */
	APP_ERR_COMPONENT_ABSENT									= 2233,		/**< 2233, COMPONENT ABSENT,										GetErrorTurkishDescription() function returns "Komponent Bulunamadý" */
	APP_ERR_SQL													= 2234,		/**< 2234, SQL,														GetErrorTurkishDescription() function returns "SQL Hatasý" */
	APP_ERR_GMP_RESPONSE_CODE_ERROR								= 2235,		/**< 2235, GMP RESPONSE CODE ERROR,									GetErrorTurkishDescription() function returns "GMP Hata Kodu Hatasý" */
	APP_ERR_FRAM_Z_REPORT_UPDATE								= 2236,		/**< 2236, FRAM Z REPORT UPDATE,									GetErrorTurkishDescription() function returns "FRAM Z Raporu Güncelleme Hatasý" */
	APP_ERR_DAILY_WRITE											= 2237,		/**< 2237, DAILY WRITE,												GetErrorTurkishDescription() function returns "Günlük Hafýza Yazma Hatasý" */
	APP_ERR_FISCAL_CUMULATIVE_WRITE								= 2238,		/**< 2238, FISCAL CUMULATIVE WRITE,									GetErrorTurkishDescription() function returns "Mali Kümülatif Yazma Hatasý" */
	APP_ERR_GMP_PROTOCOL_CANNOT_RECEIVED_FULL_MESSAGE			= 2239,		/**< 2239, GMP PROTOCOL CANNOT RECEIVED FULL MESSAGE,				GetErrorTurkishDescription() function returns "GMP Tüm Mesaj Alýnamadý" */
	APP_ERR_GMP_PROTOCOL_TPDU_NOT_RECEIVED						= 2240,		/**< 2240, GMP PROTOCOL TPDU NOT RECEIVED,							GetErrorTurkishDescription() function returns "GMP TPDU Alýnamadý" */
	APP_ERR_GMP_AUTO_FICAL_FAILED								= 2241,		/**< 2241, GMP AUTO FICAL FAILED,									GetErrorTurkishDescription() function returns "" */
	APP_ERR_GMP_EFTPOS_BAGLANTISI_BULUNAMADI					= 2242,		/**< 2242, GMP EFTPOS BAGLANTISI BULUNAMADI,						GetErrorTurkishDescription() function returns "EFTPOS Baðlantýsý Bulunamadý" */
	APP_ERR_GMP_GIB_KEY_IMZA_VERIFICATION						= 2243,		/**< 2243, GMP GIB KEY IMZA VERIFICATION,							GetErrorTurkishDescription() function returns "GMP GIB Key Ýmza Doðrulama Hatasý" */
	APP_ERR_GMP_GIB_SHA2_IDENTIFIER								= 2244,		/**< 2244, GMP GIB SHA2 IDENTIFIER,									GetErrorTurkishDescription() function returns "GMP GIB SHA2 Identifier" */
	APP_ERR_GMP_MISSING_GROUP									= 2245,		/**< 2245, GMP MISSING GROUP,										GetErrorTurkishDescription() function returns "GMP Eksik Grup Hatasý" */
	APP_ERR_GMP_BUFFER_ERROR									= 2246,		/**< 2246, GMP BUFFER ERROR,										GetErrorTurkishDescription() function returns "GMP Buffer Hatasý" */
	APP_ERR_GMP_PADDING_ERROR									= 2247,		/**< 2247, GMP PADDING ERROR,										GetErrorTurkishDescription() function returns "GMP Padding Hatasý" */
	APP_ERR_GMP_TREK_TRAK_MISMATCH								= 2248,		/**< 2248, GMP TREK TRAK MISMATCH,									GetErrorTurkishDescription() function returns "GMP TRAK/TREK Uyuþmazlýðý" */
	APP_ERR_GMP_TSM_KEY_IMZA_VERIFICATION						= 2249,		/**< 2249, GMP TSM KEY IMZA VERIFICATION,							GetErrorTurkishDescription() function returns "GMP TSM Key Ýmza Doðrulama Hatasý" */
	APP_ERR_GMP_NEGATIVE_TRANSACTION							= 2250,		/**< 2250, GMP NEGATIVE TRANSACTION,								GetErrorTurkishDescription() function returns "GMP Negatif Ýþlem" */
	APP_ERR_GMP_UNEXPECTED_RESULT								= 2251,		/**< 2251, GMP UNEXPECTED RESULT,									GetErrorTurkishDescription() function returns "GMP Beklenmeyen Sonuç" */

	APP_ERR_GMP3_UNDEFINED_OKC_MODEL							= 2301,		/**< 2301, GMP3 UNDEFINED OKC MODEL,								GetErrorTurkishDescription() function returns "Tanýmsýz OKC Modeli" */
	APP_ERR_GMP3_UNDEFINED_OKC_VENDOR							= 2302,		/**< 2302, GMP3 UNDEFINED OKC VENDOR,								GetErrorTurkishDescription() function returns "Tanýmsýz OKC Vendor" */
	APP_ERR_GMP3_UNDEFINED_OKC_SICILNO							= 2303,		/**< 2303, GMP3 UNDEFINED OKC SICILNO,								GetErrorTurkishDescription() function returns "Tanýmsýz OKC Sicil No" */
	APP_ERR_GMP3_UNDEFINED_CIHAZ_MODEL							= 2304,		/**< 2304, GMP3 UNDEFINED CIHAZ MODEL,								GetErrorTurkishDescription() function returns "Tanýmsýz Cihaz Modeli" */
	APP_ERR_GMP3_UNDEFINED_CIHAZ_VENDOR							= 2305,		/**< 2305, GMP3 UNDEFINED CIHAZ VENDOR,								GetErrorTurkishDescription() function returns "Tanýmsýz Cihaz Vendor" */
	APP_ERR_GMP3_UNDEFINED_CIHAZ_SERINO							= 2306,		/**< 2306, GMP3 UNDEFINED CIHAZ SERINO,								GetErrorTurkishDescription() function returns "Tanýmsýz Cihaz Seri No" */
	APP_ERR_GMP3_UNDEFINED_MSG_TYPE								= 2307,		/**< 2307, GMP3 UNDEFINED MSG TYPE,									GetErrorTurkishDescription() function returns "Tanýmsýz Mesaj Tipi" */
	APP_ERR_GMP3_UNDEFINED_MISSING_PARAMETER					= 2308,		/**< 2308, GMP3 UNDEFINED MISSING PARAMETER,						GetErrorTurkishDescription() function returns "Tanýmsýz Eksik Parametre" */
	APP_ERR_GMP3_INVALID_SEQUENCE_NUMBER						= 2309,		/**< 2309, GMP3 INVALID SEQUENCE NUMBER,							GetErrorTurkishDescription() function returns "Geçersiz Sýra Numarasý" */
	APP_ERR_GMP3_INVALID_DATE_TIME								= 2310,		/**< 2310, GMP3 INVALID DATE TIME,									GetErrorTurkishDescription() function returns "Geçersiz Tarih/Zaman" */
	APP_ERR_GMP3_MISSING_TDES_KEY								= 2311,		/**< 2311, GMP3 MISSING TDES KEY,									GetErrorTurkishDescription() function returns "TDES Key Bulunamadý" */
	APP_ERR_GMP3_INVALID_KCV									= 2312,		/**< 2312, GMP3 INVALID KCV,										GetErrorTurkishDescription() function returns "Geçersiz KCV" */
	APP_ERR_GMP3_UNDEFINED_STATUS								= 2313,		/**< 2313, GMP3 UNDEFINED STATUS,									GetErrorTurkishDescription() function returns "Tanýmsýz Status" */
	APP_ERR_GMP3_TIMEOUT										= 2314,		/**< 2314, GMP3 TIMEOUT,											GetErrorTurkishDescription() function returns "Zaman Aþýmý" */
	APP_ERR_GMP3_CERTIFICATE									= 2315,		/**< 2315, GMP3 CERTIFICATE,										GetErrorTurkishDescription() function returns "Sertifika Hatasý" */
	APP_ERR_GMP3_VERIFY											= 2316,		/**< 2316, GMP3 VERIFY,												GetErrorTurkishDescription() function returns "Doðrulama Hatasý" */
	APP_ERR_GMP3_INVALID_HANDLE									= 2317,		/**< 2317, GMP3 INVALID HANDLE,										GetErrorTurkishDescription() function returns "Geçersiz Handle Deðeri" */
	APP_ERR_GMP3_CRC											= 2318,		/**< 2318, GMP3 CRC,												GetErrorTurkishDescription() function returns "CRC Hatasý" */
	APP_ERR_GMP3_LEN											= 2319,		/**< 2319, GMP3 LEN,												GetErrorTurkishDescription() function returns "Uzunluk Hatasý" */
	APP_ERR_GMP3_STX											= 2320,		/**< 2320, GMP3 STX,												GetErrorTurkishDescription() function returns "STX Hatasý" */
	APP_ERR_GMP3_ETX											= 2321,		/**< 2321, GMP3 ETX,												GetErrorTurkishDescription() function returns "ETX Hatasý" */
	APP_ERR_GMP3_NACK											= 2322,		/**< 2322, GMP3 NACK,												GetErrorTurkishDescription() function returns "NACK Hatasý" */
	APP_ERR_GMP3_ACK											= 2323,		/**< 2323, GMP3 ACK,												GetErrorTurkishDescription() function returns "ACK Hatasý" */
	APP_ERR_GMP3_RECEIVE										= 2324,		/**< 2324, GMP3 RECEIVE,											GetErrorTurkishDescription() function returns "Mesaj Alma Hatasý" */
	APP_ERR_GMP3_SEND											= 2325,		/**< 2325, GMP3 SEND,												GetErrorTurkishDescription() function returns "Mesaj Gönderim Hatasý" */
	APP_ERR_GMP3_PARSE											= 2326,		/**< 2326, GMP3 PARSE,												GetErrorTurkishDescription() function returns "Parse Hatasý" */
	APP_ERR_GMP3_USER_BREAK										= 2327,		/**< 2327, GMP3 USER BREAK,											GetErrorTurkishDescription() function returns "Kullanýcý Kesintisi" */
	APP_ERR_GMP3_PROTOCOL										= 2328,		/**< 2328, GMP3 PROTOCOL,											GetErrorTurkishDescription() function returns "Protokol Hatasý" */
	APP_ERR_GMP3_PAIRING_REQUIRED								= 2329,		/**< 2329, GMP3 PAIRING REQUIRED,									GetErrorTurkishDescription() function returns "Eþleþme Yapýlmasý Gerekli" */
	APP_ERR_GMP3_UNKNOWN_DEVICE									= 2330,		/**< 2330, GMP3 UNKNOWN DEVICE,										GetErrorTurkishDescription() function returns "Bilinmeyen Cihaz" */
	APP_ERR_GMP3_VERSION_MISMATCH								= 2331,		/**< 2331, GMP3 VERSION MISMATCH,									GetErrorTurkishDescription() function returns "Versiyon Uyuþmazlýðý" */
	APP_ERR_GMP3_NO_PRIME_NUMBER								= 2332,		/**< 2332, GMP3 NO PRIME NUMBER,									GetErrorTurkishDescription() function returns "Prime Number Bulunamadý" */
	APP_ERR_GMP3_PERMISSION										= 2333,		/**< 2333, GMP3 PERMISSION,											GetErrorTurkishDescription() function returns "Yetki Hatasý" */
	APP_ERR_GMP3_INCORRECT_DEVICE								= 2334,		/**< 2334, GMP3 INCORRECT DEVICE,									GetErrorTurkishDescription() function returns "Yanlýþ Cihaz" */
	APP_ERR_GMP3_MEMORY_READ_ERROR								= 2335,		/**< 2335, GMP3 MEMORY READ ERROR,									GetErrorTurkishDescription() function returns "Bellek Okuma Hatasý" */
	APP_ERR_GMP3_MEMORY_WRITE_ERROR								= 2336,		/**< 2336, GMP3 MEMORY WRITE ERROR,									GetErrorTurkishDescription() function returns "Belleðe Yazma Hatasý" */
	APP_ERR_GMP3_MEMORY_ERASE_ERROR								= 2337,		/**< 2337, GMP3 MEMORY ERASE ERROR,									GetErrorTurkishDescription() function returns "Bellek Silme Hatasý" */
	APP_ERR_GMP3_APP_CHECKSUM_MISMATCH							= 2338,		/**< 2338, GMP3 APP CHECKSUM MISMATCH,								GetErrorTurkishDescription() function returns "Hash Deðerleri Uyuþmadý" */
	APP_ERR_GMP3_APP_DATE_EXPIRED								= 2339,		/**< 2339, GMP3 APP DATE EXPIRED,									GetErrorTurkishDescription() function returns "Uygulama Tarihi Geçmiþ" */
	APP_ERR_GMP3_TCP_RECEIVE_ERROR								= 2340,		/**< 2340, GMP3 TCP RECEIVE ERROR,									GetErrorTurkishDescription() function returns "TCP Mesaj Alma Hatasý" */
	APP_ERR_GMP3_NO_HANDLE										= 2341,		/**< 2341, GMP3 NO HANDLE,											GetErrorTurkishDescription() function returns "Handle Bulunamadý" */
	APP_ERR_GMP3_PING											= 2342,		/**< 2342, GMP3 PING,												GetErrorTurkishDescription() function returns "Ping Hatasý" */
	APP_ERR_GMP3_TCP_NO_DATA									= 2343,		/**< 2343, GMP3 TCP NO DATA,										GetErrorTurkishDescription() function returns "TCP Mesaj Alýnamadý" */
	APP_ERR_GMP3_EOT											= 2344,		/**< 2344, GMP3 EOT,												GetErrorTurkishDescription() function returns "EOT Hatasý" */
	APP_ERR_GMP3_TAG_NOT_AVAILABLE								= 2345,		/**< 2345, GMP3 TAG NOT AVAILABLE,									GetErrorTurkishDescription() function returns "Uygun Olmayan Tag" */
	APP_ERR_GMP3_ENCRYPT_DECRYPT								= 2346,		/**< 2346, GMP3 ENCRYPT DECRYPT,									GetErrorTurkishDescription() function returns "Þifreleme Hatasý" */
	APP_ERR_GMP3_MESSAGE_TYPE									= 2347,		/**< 2347, GMP3 MESSAGE TYPE,										GetErrorTurkishDescription() function returns "Mesaj Tipi Hatalý" */
	APP_ERR_GMP3_DECOMPRESS										= 2348,		/**< 2348, GMP3 DECOMPRESS,											GetErrorTurkishDescription() function returns "Sýkýþtýrma Hatasý" */
	APP_ERR_GMP3_INVALID_MERCHANT_UNIQUE_ID						= 2349,		/**< 2349, GMP3 INVALID MERCHANT UNIQUE ID,							GetErrorTurkishDescription() function returns "Geçersiz Merchant Eþsiz Numarasý" */
	APP_ERR_GMP3_INVALID_BRANCH_UNIQUE_ID						= 2350,		/**< 2350, GMP3 INVALID BRANCH UNIQUE ID,							GetErrorTurkishDescription() function returns "Geçersiz Þube Eþsiz Numarasý" */
	APP_ERR_GMP3_DATA_GROUP_NOT_FOUND							= 2351,		/**< 2351, GMP3 DATA GROUP NOT FOUND,								GetErrorTurkishDescription() function returns "GMP3 Veri Grubu Bulunamadý" */
	APP_ERR_GMP3_VERIFY_GROUP_NOT_FOUND							= 2352,		/**< 2352, GMP3 VERIFY GROUP NOT FOUND,								GetErrorTurkishDescription() function returns "GMP3 Onay Grubu bulunamadý" */
	APP_ERR_GMP3_VERIFY_GROUP_MISMATCH							= 2353,		/**< 2353, GMP3 VERIFY GROUP MISMATCH								GetErrorTurkishDescription() function returns "GMP3 Onay Grubu uyumsuz" */
	APP_ERR_GMP3_RECEIPT_CAN_NOT_VOID							= 2354,		/**< 2354, GMP3 RECEIPT CAN NOT VOID								GetErrorTurkishDescription() function returns "GMP3 Fiþi iptal edilemez" */
	APP_ERR_GMP3_BITMAP_NOT_EXIST								= 2355,		/**< 2355, GMP3 BITMAP NOT EXIST									GetErrorTurkishDescription() function returns "Bitmap yok" */
	APP_ERR_GMP3_LRC											= 2356,		/**< 2356, GMP3 LRC		                                       		GetErrorTurkishDescription() function returns "GMP3 LRC hatasý" */
	APP_ERR_GMP3_PAYMENT_CAN_NOT_VOID							= 2357,		/**< 2356, GMP3 PAYMENT CANNOT VOID		                            GetErrorTurkishDescription() function returns "GMP3 Ödeme iptal edilemez" */
	APP_ERR_GMP3_NO_TICKET_TO_VOID								= 2358,		/**< 2356, GMP3 NO TICKET TO VOID		                            GetErrorTurkishDescription() function returns "Fiþ baþlatýlmamýþ" */

	APP_ERR_GMP3_PAYMENT_KDV_NOT_AVAILABLE						= 2400,		/**< 2400, GMP3 PAYMENT KDV NOT AVAILABLE,							GetErrorTurkishDescription() function returns "Odeme KDV Oraný Geçersiz" */
	APP_ERR_GMP3_ITEM_NOT_AVAILABLE								= 2401,		/**< 2401, GMP3 ITEM NOT AVAILABLE,									GetErrorTurkishDescription() function returns "Geçersiz Ürün" */
	APP_ERR_GMP3_OKC_KISIM_UNKNOWN 								= 2402,		/**< 2402, GMP3 OKC KISIM UNKNOWN,									GetErrorTurkishDescription() function returns "Bilinmeye Kýsým" */
	APP_ERR_GMP3_DOVIZ_UNKNOWN									= 2403, 	/**< 2403, GMP3 DOVIZ UNKNOWN,										GetErrorTurkishDescription() function returns "Bilinmeyen Döviz" */
	APP_ERR_GMP3_KASIYER_UNKNOWN								= 2404, 	/**< 2404, GMP3 KASIYER UNKNOWN,									GetErrorTurkishDescription() function returns "Biinmeyen Kasiyer" */
	APP_ERR_GMP3_FUNC_OKC_PARAMETRE								= 2405,		/**< 2405, PARAMETER DOWNLOAD FAILED,								GetErrorTurkishDescription() function returns "Parametre Yükleme Baþarýsýz" */
	APP_ERR_GMP3_FATURA_ODEME_PARAMETRE							= 2406, 	/**< 2406, GMP3 FATURA ODEME PARAMETRE,								GetErrorTurkishDescription() function returns "Fatura Ödeme Parametre Hatasý" */
	APP_ERR_GMP3_Z_RAPOR										= 2407,		/**< 2407, GMP3 Z RAPOR,											GetErrorTurkishDescription() function returns "Z Raporu Hatasý" */
	APP_ERR_GMP3_X_RAPOR										= 2408,		/**< 2408, GMP3 X RAPOR,											GetErrorTurkishDescription() function returns "X Raporu Hatasý" */
	APP_ERR_GMP3_BATTERY_LEVEL									= 2409,		/**< 2409, GMP3 BATTERY LEVEL,										GetErrorTurkishDescription() function returns "Pil Seviyesi" */
	APP_ERR_GMP3_EKU_RAPOR_TYPE									= 2410,		/**< 2410, GMP3 EKU RAPOR TYPE,										GetErrorTurkishDescription() function returns "EKU Rapor Tipi Hatalý" */
	APP_ERR_GMP3_EKU_STATE										= 2411,		/**< 2411, GMP3 EKU STATE,											GetErrorTurkishDescription() function returns "EKU Durum Hatasý" */
	APP_ERR_GMP3_ECR_NOT_FISCAL									= 2412, 	/**< 2412, GMP3 ECR NOT FISCAL,										GetErrorTurkishDescription() function returns "Mali Olmayan OKC" */
	APP_ERR_GMP3_NO_FUNCTION									= 2413,		/**< 2413, GMP3 NO FUNCTION,										GetErrorTurkishDescription() function returns "Fonkisyon Bulunamadý" */
	APP_ERR_GMP3_MALI_KUMULATIF_RAPOR							= 2414,		/**< 2414, GMP3 MALI KUMULATIF RAPOR,								GetErrorTurkishDescription() function returns "Mali Kümülatif Rapor Hatasý" */
	APP_ERR_GMP3_SINEMA_BILET_DESTEGI							= 2415, 	/**< 2415, GMP3 SINEMA BILET DESTEGI,								GetErrorTurkishDescription() function returns "Sinema Bilet Desteklenmiyor" */
	APP_ERR_GMP3_PARAMETRE_HATASI								= 2416,		/**< 2416, GMP3 PARAMETRE HATASI,									GetErrorTurkishDescription() function returns "Parametre Hatasý" */
	APP_ERR_GMP3_Z_REQUIRED										= 2417,		/**< 2417, GMP3 Z REQUIRED,											GetErrorTurkishDescription() function returns "Z Alýnmalý" */
	APP_ERR_GMP3_UNSUPPORTED									= 2418,		/**< 2418, GMP3 UNSUPPORTED,										GetErrorTurkishDescription() function returns "GMP3 Desteklenmiyor" */
	APP_ERR_GMP3_SINEMA_URUN_SAYISI								= 2419, 	/**< 2419, GMP3 SINEMA URUN SAYISI,									GetErrorTurkishDescription() function returns "Sinema Ürün Sayýsý Hatalý" */
	APP_ERR_GMP3_PAYMENT_CANCELLED								= 2420,		/**< 2420, GMP3 PAYMENT CANCELLED,									GetErrorTurkishDescription() function returns "Ödeme Ýptal Hatasý" */
	APP_ERR_GMP3_ITEM_URUN_SAYISI								= 2421,		/**< 2421, GMP3 ITEM URUN SAYISI,									GetErrorTurkishDescription() function returns "Ürün Sayýsý Hatalý" */
	APP_ERR_GMP3_RESOURCE_PROBLEM								= 2422,		/**< 2422, GMP3 RESOURCE PROBLEM,									GetErrorTurkishDescription() function returns "GMP3 Kaynak Problemi Oluþtu" */
	APP_ERR_GMP3_PLU_NOT_FOUND									= 2423,		/**< 2423, GMP3 PLU NOT FOUND,										GetErrorTurkishDescription() function returns "PLU Barkodu Bulunamadý" */
	APP_ERR_GMP3_NOT_PROPER_DISCOUNT							= 2424,		/**< 2424, GMP3 NOT PROPER DISCOUNT,								GetErrorTurkishDescription() function returns "GMP3 Uygun olmayan Ýndirim" */
	APP_ERR_GMP3_BIRIM_NOT_FOUND								= 2425,		/**< 2425, GMP3 BIRIM NOT FOUND,									GetErrorTurkishDescription() function returns "GMP3 Birim Bulunamadý" */
	APP_ERR_GMP3_MIKTAR_NOT_FOUND								= 2426,		/**< 2426, GMP3 MIKTAR NOT FOUND,									GetErrorTurkishDescription() function returns "Miktar Bulunamadý" */
	APP_ERR_GMP3_URUN_ADI_NOT_FOUND								= 2427,		/**< 2427, GMP3 URUN ADI NOT FOUND,									GetErrorTurkishDescription() function returns "Ürün Adý Bulunamadý" */
	APP_ERR_GMP3_TUTAR_NOT_FOUND								= 2428,		/**< 2428, GMP3 TUTAR NOT FOUND,									GetErrorTurkishDescription() function returns "Tutar Bulunamadý" */
	APP_ERR_GMP3_UNKNOWN_ISLEM_TIPI								= 2429,		/**< 2429, GMP3 UNKNOWN ISLEM TIPI,									GetErrorTurkishDescription() function returns "Bilinmeyen Ýþlem Tipi" */
	APP_ERR_GMP3_VERGI_NOT_AVAILABLE							= 2430, 	/**< 2430, GMP3 VERGI NOT AVAILABLE,								GetErrorTurkishDescription() function returns "Geçersiz Vergi Oraný" */
	APP_ERR_GMP3_ISLEM_NOT_ALLOWED								= 2431,		/**< 2431, GMP3 ISLEM NOT ALLOWED,									GetErrorTurkishDescription() function returns "Geçersiz Ýþlem" */
	APP_ERR_GMP3_CURRENCY_NOT_AVAILABLE							= 2432,		/**< 2432, GMP3 CURRENCY NOT AVAILABLE,								GetErrorTurkishDescription() function returns "Geçersiz Kur Bilgisi" */
	APP_ERR_GMP3_FIS_ITEM_NOT_ALLOWED							= 2433, 	/**< 2433, GMP3 FIS ITEM NOT ALLOWED,								GetErrorTurkishDescription() function returns "Geçersiz Ürün" */
	APP_ERR_GMP3_FATURA_PARAMETER_MISSING						= 2434, 	/**< 2434, GMP3 FATURA PARAMETER MISSING,							GetErrorTurkishDescription() function returns "Eksik Fatura Parametresi" */
	APP_ERR_GMP3_FATURA_TARIHI_MISSING							= 2435, 	/**< 2435, GMP3 FATURA TARIHI MISSING,								GetErrorTurkishDescription() function returns "Eksik Fatura Tarihi" */
	APP_ERR_GMP3_TUTAR_NOT_REQUIRED								= 2436, 	/**< 2436, GMP3 TUTAR NOT REQUIRED,									GetErrorTurkishDescription() function returns "Tutar Gerekmez" */
	APP_ERR_GMP3_TUTAR_REQUIRED									= 2437, 	/**< 2437, GMP3 TUTAR REQUIRED,										GetErrorTurkishDescription() function returns "Tutar Gerekli" */
	APP_ERR_GMP3_INCORRECT_PASSWORD								= 2438, 	/**< 2438, GMP3 INCORRECT PASSWORD,									GetErrorTurkishDescription() function returns "Yanlýþ Þifre" */
	APP_ERR_GMP3_INACTIVE_CASHIER_INDEX							= 2439,		/**< 2439, GMP3 INACTIVE CASHIER INDEX,								GetErrorTurkishDescription() function returns "Ýnaktif Kasiyer Ýndex" */
	APP_ERR_GMP3_APPLICATION_NOT_FOUND			          		= 2440, 	/**< 2440, GMP3 APPLICATION NOT FOUND,								GetErrorTurkishDescription() function returns "Uygulama Bulunamadý" */
	APP_ERR_GMP3_UNDEFINED_TAG									= 2441,		/**< 2441, GMP3 UNDEFINED TAG,										GetErrorTurkishDescription() function returns "Tanýmsýz Tag" */
	APP_ERR_GMP3_SAVE_ECR_HEADER								= 2442, 	/**< 2442, GMP3 SAVE ECR HEADER,									GetErrorTurkishDescription() function returns "OKC Baþlýk Kaydetme Hatasý" */
	APP_ERR_GMP3_INVALID_RECIPT_LIMIT							= 2443, 	/**< 2443, GMP3 INVALID RECIPT LIMIT,								GetErrorTurkishDescription() function returns "Geçersiz Fiþ Limiti" */
	APP_ERR_GMP3_ADVANCE										= 2444,		/**< 2444, GMP3 ADVANCE,											GetErrorTurkishDescription() function returns "Avans Hatasý" */
	APP_ERR_GMP3_PAYMENT										= 2445,		/**< 2445, GMP3 PAYMENT,											GetErrorTurkishDescription() function returns "Ödeme Hatasý" */
	APP_ERR_GMP3_TRANSACTION_IS_ACTIVE							= 2446,		/**< 2446, GMP3 TRANSACTION IS ACTIVE,								GetErrorTurkishDescription() function returns "Ýþlem Aktif" */
	APP_ERR_GMP3_FATURA_TYPE_NOT_AVAILABLE						= 2447,		/**< 2447, GMP3 FATURA TYPE NOT AVAILABLE,							GetErrorTurkishDescription() function returns "Fatura Tipi Geçersiz" */
	APP_ERR_GMP3_FATURA_INVALID_TCK								= 2448,		/**< 2448, GMP3 FATURA INVALID TCK,									GetErrorTurkishDescription() function returns "Fatura TCK Geçersiz" */
	APP_ERR_INVALID_UNIQUE_ID									= 2449,		/**< 2449, INVALID UNIQUE ID,										GetErrorTurkishDescription() function returns "Geçersiz Eþsiz Numara" */
	APP_ERR_GMP3_TICKET_TYPE									= 2450,		/**< 2450, GMP3 TICKET TYPE,										GetErrorTurkishDescription() function returns "Geçersiz Fiþ Tipi" */
	APP_ERR_GMP3_SETTINGS										= 2451,		/**< 2451, GMP3 SETTINGS,											GetErrorTurkishDescription() function returns "GMP3 Ayar Hatasý" */
	APP_ERR_GMP3_BITMAP											= 2452,		/**< 2452, GMP3 BITMAP,												GetErrorTurkishDescription() function returns "Bitmap Hatasý" */
	APP_ERR_GMP3_FILE								     		= 2453,		/**< 2453, GMP3 FILE,												GetErrorTurkishDescription() function returns "Dosya Hatasý" */
	APP_ERR_GMP3_ADMIN_PASSWORD_BLOCKED							= 2454,		/**< 2454, GMP3 ADMIN PASSWORD BLOCKED,								GetErrorTurkishDescription() function returns "Yönetici Þifre Blokelendi" */
	APP_ERR_GMP3_CASHIER_PASSWORD_BLOCKED						= 2455,		/**< 2455, GMP3 CASHIER PASSWORD BLOCKED,							GetErrorTurkishDescription() function returns "Kasiyer Þifresi Blokelendi" */
	APP_ERR_GMP3_CASHIER_PASSWORD_INCORRECT						= 2456,		/**< 2456, GMP3 CASHIER PASSWORD INCORRECT,							GetErrorTurkishDescription() function returns "Kasiyer Þifresi Yalnýþ" */
	APP_ERR_GMP3_VAS_SUPPORT									= 2457,		/**< 2457, GMP3 VAS SUPPORT,										GetErrorTurkishDescription() function returns "VAS Uygulama Destekleme Hatasý" */
	APP_ERR_GMP3_OTOPARK_PARAMETER       						= 2458,		/**< 2458, GMP3 OTOPARK PARAMETER,									GetErrorTurkishDescription() function returns "Otopark Parametre Hatasý" */
	APP_ERR_GMP3_CUSTOMER_INFO									= 2459,		/**< 2459, GMP3 CUSTOMER INFO,										GetErrorTurkishDescription() function returns "Müþteri Bilgisi Hatasý" */
	APP_ERR_GMP3_FISEKU_PING_ERROR								= 2460,		/**< 2460, GMP3 FISEKU PING ERROR,									GetErrorTurkishDescription() function returns "FISEKU Ping Hatasý" */
	APP_ERR_GMP3_TICKET_SALE_NOT_ALLOWED						= 2461,		/**< 2461, GMP3 TICKET SALE NOT ALLOWED,							GetErrorTurkishDescription() function returns "Bilet Satýþ Yapýlamaz" */
	APP_ERR_GMP3_INVALID_CASHIER_PASSWORD						= 2462,		/**< 2462, GMP3 INVALID CASHIER PASSWORD,							GetErrorTurkishDescription() function returns "Geçersiz Kasiyer Þifresi" */
	APP_ERR_GMP3_INVALID_CASHIER_NAME							= 2463,		/**< 2463, GMP3 INVALID CASHIER NAME,								GetErrorTurkishDescription() function returns "Geçersiz Kaziyer Adý" */
	APP_ERR_GMP3_ITEM_NOT_ALLOWED_TO_INC_DEC					= 2464,		/**< 2464, GMP3 ITEM NOT ALLOWED TO INCREASE DECREASE,				GetErrorTurkishDescription() function returns "Ýndirim, Arttýrým Yapýlamaz" */
	APP_ERR_GMP3_NO_ZERO_TAXRATE_ON_TAX_TABLE					= 2465,		/**< 2465, APP_ERR_GMP3_NO_ZERO_TAXRATE_ON_TAX_TABLE				*/
	APP_ERR_GMP3_NO_PERMISSION_OF_USER							= 2466,		/**< 2466, APP_ERR_GMP3_NO_PERMISSION_OF_USER						*/
	APP_ERR_GMP3_NO_PERMISSION_OF_TSM							= 2467,		/**< 2467, APP_ERR_GMP3_NO_PERMISSION_OF_TSM						*/
	APP_ERR_GMP3_MISSING_INVOICE_PARAMETER						= 2468,		/**< 2468, APP_ERR_GMP3_MISSING_INVOICE_PARAMETER					*/
	APP_ERR_GMP3_ETTN_COULD_NOT_DOWNLOAD						= 2469,		/**< 2469, APP_ERR_GMP3_ETTN_COULD_NOT_DOWNLOAD						*/
	APP_ERR_GMP3_INTEGRATOR_COMMUNICATION						= 2470,		/**< 2470, APP_ERR_GMP3_INTEGRATOR_COMMUNICATION					*/
	APP_ERR_GMP3_INVALID_ONLINE_INVOICE_TYPE					= 2471,		/**< 2471, APP_ERR_GMP3_INVALID_ONLINE_INVOICE_TYPE					*/
	APP_ERR_GMP3_NOT_ALLOWED_PROCESS_IN_ONLINE_INVOICE			= 2472,
	APP_ERR_GMP3_EXCEPTION_CODE_REQUIRED						= 2473,
	APP_ERR_GMP3_FORCED_VOID									= 2474,
	APP_ERR_GMP3_PROFILE_INDEX_CANNOT_SELECTED					= 2475,
	APP_ERR_GMP3_PROFILE_INDEX_NOT_SELECTED						= 2476,
	APP_ERR_GMP3_PDM_APP_ACTIVE									= 2477,
	APP_ERR_GMP3_PDM_INVALID_MODE								= 2478,
	APP_ERR_GMP3_INVALID_FILE_NAME								= 2479,

	APP_ERR_GMP3_MONTHLY_REPORT									= 2480,		/**< 2480, 	APP_ERR_GMP3_MONTHLY_REPORT								GetErrorTurkishDescription() function returns "Aylýk Rapor Hatasý" */
	APP_ERR_GMP3_MONTHLY_REPORT_WRITE_ERROR						= 2481,		/**< 2481,	APP_ERR_GMP3_MONTHLY_REPORT_WRITE_ERROR					GetErrorTurkishDescription() function returns "Aylýk Rapor Yazma Hatasý" */
	APP_ERR_GMP3_MONTHLY_REPORT_READ_ERROR						= 2482,		/**< 2482,	APP_ERR_GMP3_MONTHLY_REPORT_READ_ERROR					GetErrorTurkishDescription() function returns "Aylýk Rapor Okuma Hatasý" */
	APP_ERR_GMP3_MONTHLY_REPORT_SEND_ERROR						= 2483,		/**< 2483,	APP_ERR_GMP3_MONTHLY_REPORT_SEND_ERROR					GetErrorTurkishDescription() function returns "Aylýk Rapor Gönderme Hatasý" */
	APP_ERR_GMP3_MONTHLY_REPORT_FRAM_READ_ERROR					= 2484,		/**< 2484,	APP_ERR_GMP3_MONTHLY_REPORT_FRAM_READ_ERROR				GetErrorTurkishDescription() function returns "Aylýk Rapor FRAM Okuma Hatasý" */
	APP_ERR_GMP3_MONTHLY_REPORT_FRAM_WRITE_ERROR				= 2485,		/**< 2485,	APP_ERR_GMP3_MONTHLY_REPORT_FRAM_WRITE_ERROR			GetErrorTurkishDescription() function returns "Aylýk Rapor FRAM Yazma Hatasý" */
	APP_ERR_GMP3_DAILY_REPORT_FRAM_READ_ERROR					= 2486,		/**< 2486,	APP_ERR_GMP3_DAILY_REPORT_FRAM_READ_ERROR				GetErrorTurkishDescription() function returns "Günlük Rapor FRAM Okuma Hatasý" */
	APP_ERR_GMP3_DAILY_REPORT_FRAM_WRITE_ERROR					= 2487,		/**< 2487,	APP_ERR_GMP3_DAILY_REPORT_FRAM_WRITE_ERROR				GetErrorTurkishDescription() function returns "Günlük Rapor FRAM Yazma Hatasý" */
	APP_ERR_GMP3_MONTHLY_REPORT_FISCAL_CUMULATIVE				= 2488,		/**< 2488,	APP_ERR_GMP3_MONTHLY_REPORT_FISCAL_CUMULATIVE			GetErrorTurkishDescription() function returns "Aylýk Rapor Fiscal Kumulatif Hatasý" */
	APP_ERR_GMP3_MONTHLY_NO_RECORD								= 2489,		/**< 2489,	APP_ERR_GMP3_MONTHLY_NO_RECORD							GetErrorTurkishDescription() function returns "Aylýk Rapor Kaydý Bulunamadý" */
	APP_ERR_GMP3_TERMINAL_NOT_FISCAL							= 2490,		/**< 2490,	APP_ERR_GMP3_TERMINAL_NOT_FISCAL						GetErrorTurkishDescription() function returns "Terminal Mali Deðil" */

	// MasterOKC Hata kodlari
	APP_ERR_BACKGROUND_LOADING_NOT_ALLOWED						= 2550,
	APP_ERR_BACKGROUND_TICKETHEADER_NOT_FOUND					,
	APP_ERR_BACKGROUND_DB_READ_ERROR							,
	APP_ERR_BACKGROUND_DB_READ_LENGTH_ERROR						,
	APP_ERR_NOT_ALLOWED_IN_BACKGROUND_MODE						,
	APP_ERR_SIGN_NOT_VALIDATED									,
	APP_ERR_TRANSACTION_ALREADY_COMPLATED						,
	APP_ERR_INVALID_HANDLE_STATUS								,
	APP_ERR_BACKGROUND_HANDLE_NOT_FOUND							,

	APP_ERR_GMP3_NO_EMPTY_KEY_SLOT								= 3000,		/**< 3000, APP ERR GMP3 NO EMPTY KEY SLOT,							GetErrorTurkishDescription() function returns "Çok Sayýda Haberleþme Kanalý Tanýmlý" */

	ING_PRN_RET_NO_PAPER										= 0xE001,    /**< Out of paper														*/
	ING_PRN_RET_PORT_NOT_OPENED									= 0xE002,    /**< Port for printer is not opened.									*/
	ING_PRN_RET_PORT_NOT_CONNECT								= 0xE003,    /**< Connection can not established between ECR and external printer port to print.		*/
	ING_PRN_RET_PORT_DATA_NOT_SENT								= 0xE004,    /**< Data is not sent to the external printer port.										*/
	ING_PRN_RET_PORT_DATA_NOT_RECEIVED							= 0xE005,    /**< Data is not received from the external printer port.				*/
	ING_PRN_RET_DRIVER_NOT_INIT									= 0xE006,    /**< Driver is not initiated.											*/
	ING_PRN_RET_INVALID_LENGTH									= 0xE007,    /**< Lenght of printer is not suitable for printout.					*/
	ING_PRN_RET_INVALID_SIZE									= 0xE008,    /**< Invalid command size.												*/
	ING_PRN_RET_LENGTH_IS_ZERO									= 0xE009,    /**< Width of line is zero.											*/
	ING_PRN_RET_LEN_IS_ZERO										= 0xE00A,	 /**< Length zero error													*/
	ING_PRN_RET_POINTER_IS_NULL									= 0xE00B,    /**< Null pointer error.												*/
	ING_PRN_RET_INVALID_LIMITS									= 0xE00C,    /**< Limit error for hardware driver definitions						*/
	ING_PRN_RET_IDLE_COMMINICATION_ERROR						= 0xE00D,	 /**< External printer communication error.								*/
	ING_PRN_RET_INTERNAL_PRINTER_ACQUIRE_ERROR					= 0xE00E,    /**< External printer is not acquired on IDLE							*/
	ING_PRN_RET_UNKNOWN											= 0xE00F,    /**< Unknown error occured.											*/
	ING_PRN_RET_FUNCTION_NOT_FOUND								= 0xE010,    /**< Callback function is not found									*/
	ING_PRN_RET_HANDLE_ERROR									= 0xE011,    /**< External error handle error										*/
	ING_PRN_RET_FONT_IS_NOT_IN_FONT_FILE						= 0xE012,    /**< The font is not in the font file : nothing is printed.			*/
	ING_PRN_RET_CHAR_IS_NOT_IN_FONT								= 0xE013,    /**< A character of the message is not in the font. Message is printed without missing characters.		*/
	ING_PRN_RET_MARGINS_ARE_TOO_BIG								= 0xE014,    /**< Margins are too big : nothing is printed.							*/
	ING_PRN_RET_BARCODE_MESSAGE_TOO_LONG						= 0xE015,    /**< Barcode data is too long.											*/
	ING_PRN_RET_BARCODE_INVALID_CHAR							= 0xE016,    /**< Barcode contains incalid characters								*/
	ING_PRN_RET_BARCODE_INVALID_PARAMETER						= 0xE017,    /**< Invalid barcode parameter											*/
	ING_PRN_RET_TYPE_NOT_SUPPORTED								= 0xE018,    /**< Type of barcode/QR is not supported								*/
	ING_PRN_RET_IDLE_NOT_SUPPORT_COMMAND						= 0xE019,    /**< Print command is not supported by IDLE.							*/
	ING_PRN_RET_MEMORY_ERROR									= 0xE01A,	 /**< Memory Error occured												*/
	ING_PRN_RET_BITMAP_FORMAT_ERROR								= 0xE01B,    /**< Memory Error occured												*/
	ING_PRN_RET_NO_CURRENT_OUTPUT								= 0xE01C,    /**< Current output is not found.										*/
	ING_PRN_RET_PRINTER_CLOSED									= 0xE01D,	 /**< Print process has been closed.									*/
	ING_PRN_RET_NO_IMG_DATA										= 0xE01E,    /**< Image data was not found.											*/
	ING_PRN_RET_EKU_SEND_ERROR									= 0xE01F,    /**< Message is not sent to ECR by IDLE								*/
	ING_PRN_RET_EKU_FUNCTION_NOT_SUPPORTED						= 0xE020,    /**< ECR function is not supported										*/
	ING_PRN_RET_QR_NOT_GENERATED								= 0xE021,    /**< QR Code is not generated.											*/
	ING_PRN_RET_QR_CONVERT_ERROR								= 0xE022,    /**< QR Code is not conterted.											*/
	ING_PRN_RET_FILE_WRITE_ERROR								= 0xE023,    /**< Write error on filesystem											*/
	ING_PRN_RET_EXTERNAL_PRINTER_NOT_RESPOND					= 0xE024,    /**< External printer is not responding								*/
	ING_PRN_RET_EXTERNAL_PRINTER_TO								= 0xE025,    /**< External printer timeout											*/
	ING_PRN_RET_PORTABLE_TERMINAL_NOT_ON_BASE					= 0xE026,    /**< Print error, put the device on cradle								*/
	ING_PRN_RET_NO_TSM_AUTHORITY								= 0xE027,    /**< External printer is not authorized on TSM							*/
	ING_PRN_RET_ECR_NOT_SUPPORT_EXTERNAL_PRINTER				= 0xE028,    /**< External printer is not supported by ECR application				*/
	ING_PRN_RET_ECR_NOT_FOUND_PRINTER							= 0xE029,	/**< Yazýcý bulunamadý.													*/
	ING_PRN_RET_EXTERNAL_NOT_SUPPORTED_FOR_TERMINAL				= 0xE02A,	/**< Bu cihaz modelinde harici cihaz desteklenmiyor.					*/
	ING_PRN_RET_PRINT_HANDLE_CANT_OPEN_FOR_CLESS				= 0xE02B,	/**< Cless driver açýk olduðu için handle açýlamadý.					*/
	ING_PRN_RET_IMAGE_WIDTH_INVALID								= 0xE02C,	/**< Yazdýrýlmak istenilen resmin geniþliði yazdýrýlamayacak kadar büyük.*/
	ING_PRN_RET_VOLITE_WRITE_ERROR								= 0xE02D,	/**< Yazýcýnýn Volitile memory sine yazýlamadý.							*/
	ING_PRN_RET_EXTERNAL_PRINTER_CHANGED						= 0xE02E,	/**< Harici yazýcý deðiþmiþ.											*/
	ING_PRN_RET_ALREADY_USED_EXTERNAL_PRINTER					= 0xE02F,	/**< Zaten bu yazýcý kullanýlmakta.										*/
	ING_PRN_RET_INVALID_VOLUME_NAME								= 0xE030,	/**< Yadýrýlmak istenen dosyanýn volum ismi geçersiz.					*/
	ING_PRN_RET_FILE_CAN_NOT_OPEN								= 0xE031,	/**< Yadýrýlmak istenen dosya açýlamadý.								*/
	ING_PRN_RET_FILE_CAN_NOT_READ								= 0xE032,	/**< Yadýrýlmak istenen dosya okunamadý.								*/
	ING_PRN_RET_COMMAND_NOT_SUPPORTED							= 0xE033,	/**< Belirtilen yazýcý için komut desteklenmiyor.						*/
	ING_PRN_RET_COMMAND_NOT_FOR_FRONT_STATION					= 0xE034,	/**< Sadece FrontStation için komut kabul ediliyor.						*/

	// Gmp3SmartDll Return Codes
	DLL_RETCODE_PORT_NOT_OPEN									= 0xF000,	/**< , PORT NOT OPEN,												GetErrorTurkishDescription() function returns "Port Açýlamadý" */
	DLL_RETCODE_ECR_DATA_ERR									= 0xF001,	/**< , ECR DATA ERR,												GetErrorTurkishDescription() function returns "OKC Data Hatasý" */
	DLL_RETCODE_POS_DATA_ERR									= 0xF002,	/**< , POS DATA ERR,												GetErrorTurkishDescription() function returns "POS Data Hatasý" */
	DLL_RETCODE_TIMEOUT											= 0xF003,	/**< , TIMEOUT,														GetErrorTurkishDescription() function returns "Zaman Aþýmý" */
	DLL_RETCODE_DATA_SEND_ERR									= 0xF004,	/**< , DATA SEND ERR,												GetErrorTurkishDescription() function returns "Data Gönderim Hatasý" */
	DLL_RETCODE_LENGHT_ERR										= 0xF005,	/**< , LENGHT ERR,													GetErrorTurkishDescription() function returns "Uzunluk Hatasý" */
	DLL_RETCODE_SESSIONID_ERR									= 0xF006,	/**< , SESSIONID ERR,												GetErrorTurkishDescription() function returns "Oturum ID Hatasý" */
	DLL_RETCODE_DATA_RECV_ERR									= 0xF007,	/**< , DATA RECV ERR,												GetErrorTurkishDescription() function returns "Data Alým Hatasý" */
	DLL_RETCODE_RETRY_ERR										= 0xF008,	/**< , RETRY ERR,													GetErrorTurkishDescription() function returns "Tekrar Deneme Hatasý" */
	DLL_RETCODE_RECV_EOT										= 0xF009,	/**< , RECV EOT,													GetErrorTurkishDescription() function returns "EOT Alýnamadý" */
	DLL_RETCODE_LEN_TOO_LONG									= 0xF00A,	/**< , LEN TOO LONG,												GetErrorTurkishDescription() function returns "Uzunluk Çok Büyük" */
	DLL_RETCODE_FAIL											= 0xF00B,	/**< , FAIL,														GetErrorTurkishDescription() function returns "Baþarýsýz Ýþlem" */
	DLL_RETCODE_ERROR_STX										= 0xF00C,	/**< , ERROR STX,													GetErrorTurkishDescription() function returns "STX Hatasý" */
	DLL_RETCODE_ERROR_ETX										= 0xF00D,	/**< , ERROR ETX,													GetErrorTurkishDescription() function returns "ETX Hatasý" */
	DLL_RETCODE_ERROR_CRC										= 0xF00E,	/**< , ERROR CRC,													GetErrorTurkishDescription() function returns "CRC Hatasý" */
	DLL_RETCODE_ERROR_MSGTYPE									= 0xF00F,	/**< , ERROR MSGTYPE,												GetErrorTurkishDescription() function returns "Mesaj Tipi Hatasý" */
	DLL_RETCODE_ERROR_ERR										= 0xF010,	/**< , ERROR ERR,													GetErrorTurkishDescription() function returns "ERR Hatasý" */
	DLL_RETCODE_ERROR_SID										= 0xF011,	/**< , ERROR SID,													GetErrorTurkishDescription() function returns "SID Hatasý" */
	DLL_RETCODE_ERROR_EOT										= 0xF012,	/**< , ERROR EOT,													GetErrorTurkishDescription() function returns "EOT Hatasý" */
	DLL_RETCODE_STATUS_CODE_ERR									= 0xF013,	/**< , STATUS CODE ERR,												GetErrorTurkishDescription() function returns "Status Kodu Hatasý" */
	DLL_RETCODE_LEN_TOO_SHORT									= 0xF014,	/**< , LEN TOO SHORT,												GetErrorTurkishDescription() function returns "Uzunluk Çok Küçük" */
	DLL_RETCODE_DEMO_VERSION									= 0xF015,	/**< , DEMO VERSION,												GetErrorTurkishDescription() function returns "Demo Versiyon Hatasý" */
	DLL_RETCODE_FILE_OPEN_ERR									= 0xF016,	/**< , FILE OPEN ERR,												GetErrorTurkishDescription() function returns "Dosya Açma Hatasý" */
	DLL_RETCODE_KEY_ERROR										= 0xF017,	/**< , KEY ERROR,													GetErrorTurkishDescription() function returns "Key hatasý" */
	DLL_RETCODE_TERMSN_ERROR									= 0xF018,	/**< , TERMSN ERROR,												GetErrorTurkishDescription() function returns "Terminal Seri No Hatasý" */
	DLL_RETCODE_ERROR_LRC										= 0xF019,	/**< , ERROR LRC,													GetErrorTurkishDescription() function returns "LRC Hatasý" */
	DLL_RETCODE_REC_EOT_OK										= 0xF01A,	/**< , REC EOT OK,													GetErrorTurkishDescription() function returns "EOT Alýnamadý" */
	DLL_RETCODE_ACK_NOT_RECEIVED								= 0xF01B,	/**< , ACK NOT RECEIVED,											GetErrorTurkishDescription() function returns "ACK Alýnamadý" */
	DLL_RETCODE_RECV_BUSY										= 0xF01C,	/**< , RECV BUSY,													GetErrorTurkishDescription() function returns "Terminal Meþgul" */
	DLL_RETCODE_RECV_ACK										= 0xF01D,	/**< , RECV ACK,													GetErrorTurkishDescription() function returns "ACK Hatasý" */
	DLL_RETCODE_RECV_NAK										= 0xF01E,	/**< , RECV NAK,													GetErrorTurkishDescription() function returns "NACK Hatasý" */
	DLL_RETCODE_INTERCHAR_TIMEOUT								= 0xF01F,	/**< , INTERCHAR TIMEOUT,											GetErrorTurkishDescription() function returns "Intercharacter Timeout" */
	DLL_RETCODE_PAIRING_REQUIRED								= 0xF020,	/**< , PAIRING REQUIRED,											GetErrorTurkishDescription() function returns "Eþleþme Yapýlmalý" */
	DLL_RETCODE_WORG_PING_RETURN								= 0xF021,	/**< , WORG PING RETURN,											GetErrorTurkishDescription() function returns "Yalnýþ Ping Cevabý" */
	DLL_RETCODE_MEMORY_ERROR									= 0xF022,	/**< , MEMORY ERROR,												GetErrorTurkishDescription() function returns "Bellek Hatasý" */
	DLL_RETCODE_ECR_VALUE_ERROR									= 0xF023,	/**< , ECR VALUE ERROR,												GetErrorTurkishDescription() function returns "OKC Deðer Hatasý" */
	DLL_RETCODE_PORT_OPEN_ERROR									= 0xF024,	/**< , PORT OPEN ERROR,												GetErrorTurkishDescription() function returns "Port Açma Hatasý" */
	DLL_RETCODE_JSON_ERROR										= 0xF025,	/**< , JSON ERROR,													GetErrorTurkishDescription() function returns "Json Hatasý" */
	DLL_RETCODE_ECR_VERSION_TOO_OLD								= 0xF026,	/**< , ECR VERSION TOO OLD,											GetErrorTurkishDescription() function returns "OKC Verisyonu Çok Eski" */
	DLL_RETCODE_PROCESSING_NUMBER_MISMATCH						= 0xF027,	/**< , PROCESSING NUMBER MISMATCH,									GetErrorTurkishDescription() function returns "Ýþlem Sýra Numarasý Uyuþmazlýðý" */
	DLL_RETCODE_DECRYPTION_ERR									= 0xF028,	/**< , DECRYPTION ERR,												GetErrorTurkishDescription() function returns "Þifre Çözme Hatasý" */
	DLL_RETCODE_HASH_CALCULATE_ERROR							= 0xF029,	/**< , HASH CALCULATE ERROR,										GetErrorTurkishDescription() function returns "Hash Hesap Hatasý" */
	DLL_RETCODE_INVALID_STRUCT_SIZE								= 0xF02A,	/**< , INVALID STRUCT SIZE,											GetErrorTurkishDescription() function returns "Geçersiz Yapý Uzunluðu" */
	DLL_RETCODE_COMPRESSION_ERR									= 0xF02B,	/**< , COMPRESSION ERR,												GetErrorTurkishDescription() function returns "Sýkýþtýrma Hatasý" */
	DLL_RETCODE_DECOMPRESSION_ERR								= 0xF02C,	/**< , DECOMPRESSION ERR,											GetErrorTurkishDescription() function returns "Paket Açma Hatasý" */
	DLL_RETCODE_PRIME_NUMBER_ERR								= 0xF02D,	/**< , PRIME NUMBER ERR,											GetErrorTurkishDescription() function returns "Prime Number Hatasý" */
	DLL_RETCODE_ENCRYPTION_ERR									= 0xF02E,	/**< , ENCRYPTION ERR,												GetErrorTurkishDescription() function returns "Þifreleme Hatasý" */
	DLL_RETCODE_PADDING_ERROR									= 0xF02F,	/**< , PADDING ERROR,												GetErrorTurkishDescription() function returns "Padding Hatasý" */
	DLL_RETCODE_ENC_DEC_MISTMATCH_ERROR							= 0xF030,	/**< , ENC DEC MISTMATCH ERROR,										GetErrorTurkishDescription() function returns "Þifreli Paket ile Þifresiz Paket Uyuþmazlýðý" */
	DLL_RETCODE_INVALID_AMOUNT									= 0xF031,	/**< , INVALID AMOUNT,												GetErrorTurkishDescription() function returns "Girilen tutar veya puan iþlem tipine uygun deðil" */
	DLL_RETCODE_OLD_STYLE_FUNCTION_CALL_ERROR					= 0xF032,	/**< , OLD STYLE FUNCTION CALL ERROR								GetErrorTurkishDescription() function returns "Eski tip konksiyon çaðýrýlmasý hatasý" */
	DLL_RETCODE_NEW_STYLE_FUNCTION_CALL_ERROR					= 0xF033,	/**< , NEW STYLE FUNCTION CALL ERROR								GetErrorTurkishDescription() function returns "Yeni tip konksiyon çaðýrýlmasý hatasý" */
	DLL_RETCODE_INTERFACE_HANDLE_ERROR							= 0xF034,	/**< , INTERFACE HANDLE	ERROR										GetErrorTurkishDescription() function returns "Interface Handlle Hatasý" */
	DLL_RETCODE_INVALID_INTERFACE_HANDLE						= 0xF035,	/**< , INVALID INTERFACE HANDLE										GetErrorTurkishDescription() function returns "Geçersiz Interface Handle" */
	DLL_RETCODE_XML_FILE_ERROR									= 0xF036,	/**< , XML FILE ERROR												GetErrorTurkishDescription() function returns "Xml Dosya Hatasý" */
	DLL_RETCODE_INTERFACE_ID_ALREADY_EXIST						= 0xF037,	/**< , INTERFACE ID ALREADY EXIST									GetErrorTurkishDescription() function returns "Interface IDsi Zaten mevcut" */
	DLL_RETCODE_PRINTER_FRONT_STATION_BUFFER_ERROR				= 0xF038,	/**< , PRINTER FRONT STATION BUFFER ERROR							GetErrorTurkishDescription() function returns "Ön Printera gönderilen datanýn boyutu 2000 byte'i geçemez" */
	DLL_RETCODE_INVALID_CERTIFICATE_DLL							= 0xF039,
	DLL_RETCODE_INVALID_CERTIFICATE_ECR							= 0xF03A,
	DLL_RETCODE_INVALID_SIGN_DLL								= 0xF03B,
	DLL_RETCODE_INVALID_KCV										= 0xF03C,
	DLL_RETCODE_INVALID_SIGN_ECR								= 0xF03D,
	DLL_RETCODE_MAX_BUFFER_OVERFLOW								= 0xF03E

} EGlobalReturnCodes;

/** Types of the payment */
typedef enum
{
	PAYMENT_ALL				= 0x000FFFFF,	//  NAKIT  KREDI  OTHER  YCEKI  DOVIZ   MATRAH  MENU(ODEME TIPLERI)
	PAYMENT_CASH_TL			= 0x00000001,	// 	++++   xxxx   xxxx   xxxx   xxxx    ++++	xxxx
	PAYMENT_CASH_CURRENCY	= 0x00000002,	// 	xxxx   xxxx   xxxx   xxxx   ++++    ++++    xxxx
	PAYMENT_BANK_CARD		= 0x00000004,	//	xxxx   ++++   xxxx   xxxx   xxxx    ++++    xxxx
	PAYMENT_YEMEKCEKI		= 0x00000008,	//	xxxx   xxxx   xxxx   ++++   xxxx    xxxx    xxxx(Uygulama varsa)
	PAYMENT_MOBILE			= 0x00000010,	// 	xxxx   ++++   xxxx   xxxx   xxxx    ++++    xxxx(Uygulama varsa)
	PAYMENT_HEDIYE_CEKI		= 0x00000020,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
	PAYMENT_IKRAM			= 0x00000040,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
	PAYMENT_ODEMESIZ		= 0x00000080,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
	PAYMENT_KAPORA          = 0x00000100,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
	PAYMENT_PUAN            = 0x00000200,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
	PAYMENT_GIDER_PUSULASI  = 0x00000400,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
	PAYMENT_BANKA_TRANSFERI = 0x00000800,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
	PAYMENT_CEK 			= 0x00001000,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
	PAYMENT_ACIK_HESAP      = 0x00002000,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++
	PAYMENT_DIGER			= 0x00004000,   // 	xxxx   xxxx   ++++   xxxx   xxxx    ++++    ++++

	REVERSE_PAYMENT_ALL					= 0xFFF00000,
	REVERSE_PAYMENT_CASH				= 0x00100000,
	REVERSE_PAYMENT_BANK_CARD_VOID		= 0x00200000,
	REVERSE_PAYMENT_BANK_CARD_REFUND	= 0x00400000,
	REVERSE_PAYMENT_YEMEKCEKI			= 0x00800000,
	REVERSE_PAYMENT_MOBILE				= 0x01000000,
	REVERSE_PAYMENT_HEDIYE_CEKI			= 0x02000000,
	REVERSE_PAYMENT_PUAN				= 0x04000000,
	REVERSE_PAYMENT_ACIK_HESAP          = 0x08000000,
	REVERSE_PAYMENT_KAPORA              = 0x10000000,
	REVERSE_PAYMENT_GIDER_PUSULASI      = 0x20000000,
	REVERSE_PAYMENT_BANKA_TRANSFERI     = 0x40000000,
	REVERSE_PAYMENT_CEK 			    = 0x80000000

} EPaymentTypes;

#define PAYMENT_OTHER_ALL     (PAYMENT_YEMEKCEKI         | PAYMENT_MOBILE                 | PAYMENT_HEDIYE_CEKI         | PAYMENT_IKRAM        | PAYMENT_ODEMESIZ | PAYMENT_KAPORA | PAYMENT_GIDER_PUSULASI | PAYMENT_PUAN | PAYMENT_BANKA_TRANSFERI | PAYMENT_CEK | PAYMENT_ACIK_HESAP | PAYMENT_DIGER)
#define PAYMENT_OTHER_REVERSE (REVERSE_PAYMENT_YEMEKCEKI | REVERSE_PAYMENT_MOBILE         | REVERSE_PAYMENT_HEDIYE_CEKI | REVERSE_PAYMENT_PUAN | REVERSE_PAYMENT_ACIK_HESAP)
#define PAYMENT_VAS_ALL		  (PAYMENT_OTHER_ALL         | PAYMENT_OTHER_REVERSE)
#define PAYMENT_BANK_ALL	  (PAYMENT_BANK_CARD         | REVERSE_PAYMENT_BANK_CARD_VOID | REVERSE_PAYMENT_BANK_CARD_REFUND)

/** Sub types of the sub payment for PAYMENT_TYPE_BANKING_CARD */
typedef enum _ESubPaymentInfoTypes
{
	PAYMENT_SUBTYPE_INFO_CREDIT_PUAN                 = 0x00000004,
	PAYMENT_SUBTYPE_INFO_LOYALTY_PUAN                = 0x00000008,
} ESubPaymentInfoTypes;

/** Sub types of the payment for ST_PAYMENT_REQUEST */
typedef enum _EPaymentSubtypes
{
	PAYMENT_SUBTYPE_PROCESS_ON_POS						= 0x00000000,			/**< 0x00000000  */
	PAYMENT_SUBTYPE_SALE								= 0x00000001,			/**< 0x00000001  Sale									*/
	PAYMENT_SUBTYPE_INSTALMENT_SALE						= 0x00000002,			/**< 0x00000002  Installment sale						*/
	PAYMENT_SUBTYPE_LOYALTY_PUAN					    = 0x00000003,			/**< 0x00000003  Sale using Loyalty Point				*/
	PAYMENT_SUBTYPE_ADVANCE_REFUND						= 0x00000004,			/**< 0x00000004	 Advance refund							*/
	PAYMENT_SUBTYPE_INSTALLMENT_REFUND					= 0x00000005,			/**< 0x00000005  Count of number of Installment			*/
	PAYMENT_SUBTYPE_REFERENCED_REFUND					= 0x00000006,			/**< 0x00000006  Refund using reference					*/
	PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD			= 0x00000007,			/**< 0x00000007  Refund with card using reference		*/
	PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD	    = 0x00000008,			/**< 0x00000008  Refund without card using reference	*/
	PAYMENT_SUBTYPE_FORWARD_SALE						= 0x00000009,			/**< 0x00000009  Forward sale							*/
} EPaymentSubtypes;

/** Sub types of the discount for Bank, VAS aplication or ticket discount process.*/
typedef enum _DiscountSubtypes
{
	DISCOUNT_SUBTYPE_BANKING_INDIRIM				= 0x0001,
	DISCOUNT_SUBTYPE_RECEIPT_INDIRIM				= 0x0002,
	DISCOUNT_SUBTYPE_BANKING_INDIRIM_MATRAHSIZ		= 0x0003,
	DISCOUNT_SUBTYPE_VAS_INDIRIM					= 0x0004,
	DISCOUNT_SUBTYPE_VAS_MOBILE_INDIRIM				= 0x0005,
	DISCOUNT_SUBTYPE_ING_MOBILE_INDIRIM				= 0x0006,
	DISCOUNT_SUBTYPE_LOYALTY_INDIRIM				= 0x0007,
} DiscountSubtypes;

/** Transaction Fiscal Type. It is the major type of the ticket to catogorize in Transaction Database and reporting */
typedef enum
{
	TRANSACTION_FISCAL_TYPE_SALE 	= 0,
	TRANSACTION_FISCAL_TYPE_REFUND	,
	TRANSACTION_FISCAL_TYPE_VOID	,
	TRANSACTION_FISCAL_TYPE_NON_FISCAL_SALE,
	TRANSACTION_FISCAL_TYPE_INFO,
} ETransactionFiscalType;

/** Subtype of the MATRAHSIZ transaction in TaxExceptioan  */
typedef enum
{
	MATRAHSIZ_TYPE_ILAC = 1,
	MATRAHSIZ_TYPE_MUAYANE,
	MATRAHSIZ_TYPE_MUAYANE_RECETE,
	MATRAHSIZ_TYPE_INVOICE_COLLECTION,
	MATRAHSIZ_TYPE_DIGER,
} ETypeOfMatrahsiz;

/** Subtype of the TAXLESS transaction in TaxExceptioan  */
typedef enum
{
	TAXLESS_TYPE_DIPLOMATIC = 1,
} ETypeOfTaxless;

/** Ticket Type. It is the major type of the ticket to catogorize in Transaction Database and reporting */
typedef enum
{
	TTasnifDisi = 0,				//Unused
	TProcessSale,					//Fiscal Ticket
	TZReport,						//Unused
	TXReport,						//Unused
	TEJReport,						//Unused
	TFiscal2Z,						//Unused
	TFiscal2T,						//Unused
	TFiscalCumm,					//Unused
	TAvans,							//Non_Fiscal Ticket
	TPayment,						//Non_Fiscal Ticket
	TZDonemReport,   // 10			//Unused
	TXDonemReport,					//Unused
	TXPluSale,						//Unused
	TInvoice,						//Non_Fiscal Ticket
	TVoidSale,						//Non_Fiscal Ticket
	TRefund,						//Non_Fiscal Ticket
	TYemekceki,						//Non_Fiscal Ticket
	TOtopark,						//Non_Fiscal Ticket
	TZReportForce,  // 18			//Unused
	TInfo,							//Non_Fiscal Ticket
	TTaxFree,						//Fiscal Ticket
	TDailyMemory,					//Unused
	TKasaAvans,						//Non_Fiscal Ticket
	TCariHesap,						//Non_Fiscal Ticket
	TUniqueId	= 127,				//Unused
	TLAST,							// Bu satir hep sonda kalmali
} TTicketType;

typedef enum
{
	ONLINE_INVOICE_TYPE_E_FATURA = 1,
	ONLINE_INVOICE_TYPE_E_ARSIV = 2,
	ONLINE_INVOICE_TYPE_TAX_FREE = 3,
	ONLINE_INVOICE_TYPE_MUSTAHSIL = 4,
} EOnlineInvoiceType;

/** International Currency Codes that are supported in ECR & TSM.
Note : CURRENCY_TL is the build in currency and always supported
Note : Other than build in currency, if currency is not activated on TSM, it will not be functional on ECR!
*/
typedef enum
{
	CURRENCY_NONE 	= 0,
	CURRENCY_TL 	= 949,
	CURRENCY_DOLAR 	= 997,
	CURRENCY_EU		= 978,
	CURRENCY_GPR	= 826,
} ECurrency;

/** Types of the Invoice */
typedef enum
{
	INVOICE_TYPE_PAPER 	= 0,
	INVOICE_TYPE_E_FATURA,
	INVOICE_TYPE_E_ARSIV ,
} EInvoiceSource;

/** Types of the Card Reader on ECR */
typedef enum
{
	READER_TYPE_MCR 		= 0x01,
	READER_TYPE_SCR 		= 0x02,
	READER_TYPE_CLESS 		= 0x04,
} ECardReaderTypes;

/** Type of Item on the ticket */
typedef enum
{
	ITEM_TYPE_FREE			= 0,	/**< Kept for backward compatibility. Please DON'T use it*/
	ITEM_TYPE_DEPARTMENT	= 1,	/**< Tax value will be provided from Department Table in ECR by the provided department index in ST_ITEM. Item name, barcode, unit type  can be optionally provided from external system. Otherwise, default values will be used from Department Table*/
	ITEM_TYPE_PLU			= 2,	/**< Tax value will be provided from department index of the PLU record saved in PLU Table. With this type of item, a barcode must be provided with ST_ITEM structure. ECR will search this barcode in ECR PLU DB, if found, item details will be provided from this record*/
	ITEM_TYPE_TICKET		= 3,	/**< Special item type used for Cinema tickiting only. it includes department index, same as ITEM_TYPE_DEPARTMENT, bu there are special messages and flows on the ticket special to this type*/
	ITEM_TYPE_MONEYCOLLECTION 	= 9,	/**< Item is excluded from tax calculation but included during payment ("Matrahsiz", "Fatura Tahsilat", ext... ) */
} EItemTypes;

/** Type of Unit on the ticket */
typedef enum
{
	ITEM_NONE,
	ITEM_NUMBER 			= 1,
	ITEM_KILOGRAM		= 2,
	ITEM_GRAM 			= 3,
	ITEM_LITRE 			= 4,

	// Adetsel Birimler
	ITEM_DUZINE			=    11,
	ITEM_DEMET			, // 12
	ITEM_KASA			, // 13
	ITEM_BAG				, // 14

	// Agirlik Birimler
	ITEM_MILIGRAM		=    31,
	ITEM_TON				, // 32
	ITEM_ONS				, // 33
	ITEM_DESIGRAM		, // 34
	ITEM_SANTIGRAM		, // 35
	ITEM_POUND			, // 36
	ITEM_KENTAL			, // 37

	// Uzunluk Birimler
	ITEM_METRE			=    51,
	ITEM_SANTIMETRE		, // 52
	ITEM_MILIMETRE		, // 53
	ITEM_DEKAMETRE		, // 54
	ITEM_HEKTAMETRE		, // 55
	ITEM_KILOMETRE		, // 56
	ITEM_DESIMETRE		, // 57
	ITEM_MIKRON			, // 58
	ITEM_INC				, // 59
	ITEM_FOOT			, // 60
	ITEM_YARD			, // 61
	ITEM_MIL				, // 62

	// Hacim Birimler
	ITEM_METREKUP		=    71,
	ITEM_DESIMETREKUP	, // 72
	ITEM_SANTIMETREKUP	, // 73
	ITEM_MILIMETREKUP	, // 74
	ITEM_DEKALITRE		, // 75
	ITEM_HEKTOLITRE		, // 76
	ITEM_KILOLITRE		, // 77
	ITEM_DESILITRE		, // 78
	ITEM_SANTILITRE		, // 79
	ITEM_MILILITRE		, // 80
	ITEM_INCKUP			, // 81
	ITEM_GALLON			, // 82
	ITEM_BUSHEL			, // 83

	// Alan Birimler
	ITEM_METREKARE		=    91,
	ITEM_DEKAMETREKARE	, // 92
	ITEM_AR				, // 93
	ITEM_KILOMETREKARE	, // 94
	ITEM_DESIMETREKARE	, // 95
	ITEM_SANTIMETREKARE	, // 96
	ITEM_MILIMETREKARE	, // 97
	ITEM_DONUM			, // 98
	ITEM_HEKTAR			, // 99
	ITEM_INCKARE			, // 100
} EItemUnitTypes;


/** Eku status */
typedef enum
{
	EKU_STATUS_VIRGIN,
	EKU_STATUS_ACTIVE,
	EKU_STATUS_CLOSED,
	EKU_STATUS_UNDEFINED
} EKU_STATUS_t;

/** Eku record status */
typedef enum
{
	EKU_RECORD_STATUS_UNDEFINED,
	EKU_RECORD_STATUS_VIRGIN,
	EKU_RECORD_STATUS_OPEN,
	EKU_RECORD_STATUS_CLOSED,
	EKU_RECORD_STATUS_DESTROYED
} EKU_RECORD_STATUS_t;

/** INFO Function type */
enum
{
	TLV_FUNC_INFO_DEVICE = 0xEF10,     			   // 00 Info device
	TLV_FUNC_INFO_FISCAL,                          // 01 Info fiscal
	TLV_FUNC_INFO_FRAM,                            // 02 Info fram
	TLV_FUNC_INFO_DB,                              // 03 Info DB
	TLV_FUNC_INFO_DAILY,                           // 04 Info daily
	TLV_FUNC_INFO_EVENT,                           // 05 Info event
	TLV_FUNC_INFO_EKU,                             // 06 Info eku
};


/** Bank Aplication transaction flags*/
typedef enum
{
	BANK_TRAN_FLAG_DO_NOT_ASK_FOR_MISSING_LOYALTY_POINT			= 0x04000000,	/**< 0x04000000 Do not ask for missing loyalty point           */
	BANK_TRAN_FLAG_ALL_INPUT_FROM_EXTERNAL_SYSTEM				= 0x08000000,	/**< 0x08000000 All Input from EXTERNAL SYSTEM				   */
	BANK_TRAN_FLAG_ASK_FOR_MISSING_REFUND_INPUTS				= 0x10000000,	/**< 0x10000000 Ask for Missing Refund Inputs                  */
	BANK_TRAN_FLAG_LOYALTY_POINT_NOT_SUPPORTED_FOR_TRANS		= 0x20000000,	/**< 0x20000000 Loyalty point not supported for transaction.   */
	BANK_TRAN_FLAG_ONLINE_FORCED_TRANSACTION					= 0x40000000,	/**< 0x40000000 Reserved for internal use.                     */
	BANK_TRAN_FLAG_MANUAL_PAN_ENTRY_NOT_ALLOWED					= 0x80000000,	/**< 0x80000000 Manual pan entry not allowed for transaction.  */
	BANK_TRAN_FLAG_AUTHORISATION_FOR_INVOICE_PAYMENT			= 0x02000000,	/**< 0x02000000 Authorization for Invoice payments.  */
	BANK_TRAN_FLAG_SALE_WITHOUT_CAMPAIGN						= 0x01000000,	/**< 0x01000000 Sale without campaign.  */
} BANK_APLICATION_TRANSACTION_FLAGS_t;

/** Unique id */
typedef struct
{
	uint32		StructSize;		/**< Sizeof this structure */
	uint8		uniqueId[24];	/**< Unique id */
	uint16      reserved1;		/**< Reserved */
	uint32      reserved2;		/**< Reserved */
} ST_UNIQUE_ID;

/** EKU record information */
typedef struct
{
	uint32 		   		DateTime;		/**< Date and Time in Unix date & time format */
	uint32 		   		Amount;			/**< Total amount of the ticket */
	uint32 		   		Vat;			/**< Total tax of the ticket */
	uint16 		   		FNo;			/**< F No */
	uint16 		   		ZNo;			/**< Z No */
	uint16         		Type;			/**< Type of the ticket, 2 bytes for alignment, 1 byte written to FLASH */
	uint16	       		Status;			/**< Status of the record */
} EKU_RECORD_t;

/** EKU Info structure to read details from EKU */
typedef struct
{
	EKU_RECORD_t  		LastRecord;		/**< Last saved record in EKU */
	uint32         		MapFreeArea;	/**< Free area on the map, TLV_PARAM_INFO_EKU_MAP_FREE */
	uint32         		MapUsedArea;	/**< Used area on the map, TLV_PARAM_INFO_EKU_MAP_USED */
	uint32         		DataFreeArea;	/**< Free area on the Data,TLV_PARAM_INFO_EKU_DATA_FREE */
	uint32         		DataUsedArea;	/**< Used area on the Data, TLV_PARAM_INFO_EKU_DATA_USED */
	uint16         		HeaderUsed;		/**< Total Header area used, TLV_PARAM_INFO_EKU_HEADER_USED */
	uint16         		HeaderTotal;	/**< Total Header area, TLV_PARAM_INFO_EKU_HEADER_TOTAL */
	EKU_STATUS_t   		Status;         /**< Status, TLV_FUNC_INFO_EKU */
	uint16				CpuCRC;			/**< Crc */
} EKU_INFO_t;

/** Interity control structure for Fiscal module */
typedef struct
{
	uint8 			Fiscal;			/**< boolen represent integrity test result of the module */
	uint8 			Event;			/**< boolen represent integrity test result of the module */
	uint8 			Daily;			/**< boolen represent integrity test result of the module */
	uint8 			RFU;			/**< RFU */
} FISCAL_INTEGRITY_t;

/** Physical Memory Info structure for fiscal module */
typedef struct _MEMORY_INFO_t
{
	uint8 		   		ID[4];			/**< id of the physical memory chip */
	uint16 			Size;			/**< size of the memory in bytes */
} MEMORY_INFO_t;

typedef struct
{
	uint8 InvoiceSettings;
	uint8 ZSettings;
	uint16 Z_Time_In_Minute;
	uint8 Copy_Button_Secured;
	uint16 Backlight_Timeout;
	uint16 Backlight_Level;
	uint16 Keylock_Timeout;
} ST_EcrSettings;

/** Device Info structure which is used to retrive data from fiscal module & EKU */
typedef struct
{
	char          		szSoftVersion[16 + 1];			/**< version of the device software as alphanumeric string */
	char          		szHardVersion[16 + 1];			/**< version of the device hardware as alphanumeric string */
	char          		szCompileDate[16 + 1];			/**< compile date & time of the device software */
	char          		szDescription[16 + 1];			/**< decriptin about device */
	char				szHardwareReference[16 + 1];	/**<  */
	char				szHardwareSerial[16 + 1];		/**< serial number of the device */
	char          		szCpuID[12 + 1];				/**< Unique CPU id of the device */
	char		   		szHash[64 + 1];					/**<  */
	char				szBootVersion[32 + 1];			/**<  */
	FISCAL_INTEGRITY_t  Integrity;						/**< Integrity control result */
	MEMORY_INFO_t		Flash1;							/**< first flash information on the device (if exists) */
	MEMORY_INFO_t 		Flash2;							/**< second flash information on the device (if exists) */
	MEMORY_INFO_t   	Fram;							/**< fram information on the device (if exists) */
	uint16				CpuCRC;							/**<  */
	uint8 				Authentication;					/**<  */
} DEVICE_INFO_t;

/** INIT and/or CLOSE structure which is used for EKU activation and close */
typedef struct
{
	uint32				DateTime;						/**< Data & Time in Unix date and time format */
	uint16   			ZNo;							/**< Z No */
	uint16   			FNo;							/**< F No */
} EKU_INI_CLS_t;

/** EKU Header structure which is used for EKU header information */
typedef struct _ST_EKU_HEADER
{
	uint32				StructSize;						/**< Sizeof this structure */
	uint8       		SicilNo[16];					/**< Unique sicil no of the ECR, JHWE123456, JI123456, ... */
	uint8       		TerminalSerialNo[16];			/**< Serial number of the tellium termnial, 12315WE12345678 */
	uint8       		TerminalProductCode[16];		/**< Product code of the ECR */
	uint8       		SoftwareVersion[16];			/**< ECR application software versiton */
	uint8       		MerchantName[64];				/**< Name of the merchant as 2 lines, 32 characters each. Strings are not quarantied for NULL termination, user must manage NULL termination */
	uint8       		MerchantAddress[96];			/**< Address of the merchant as 3 lines, 32 characters each. Strings are not quarantied for NULL termination, user must manage NULL termination */
	uint8       		VATOffice [24];					/**< VAT office of the merchant, NULL termination is not quaranteed for the string*/
	uint8       		VATNumber[12];					/**< VAT number of the merchant */
	EKU_INI_CLS_t   	Init;							/**< INIT time Parameters of EKU */
	EKU_INI_CLS_t   	Close; 							/**< CLOSE time parameters for EKU */
	uint16      		Active;							/**< boolean represent if the EKU is active or not */
	uint16      		EkuCount;						/**< Number of EKU for ECR. initial value is 1 and it increases when a new EKU is activated for this ECR */
	uint16          	HeaderIndex;					/**< Index of the header on a particular EKU. There are maximum 64 places to be used for each EKU */
	uint16          	HeaderTotal;  					/**< Total number of Headers in EKU which are already used */
	uint8               MersisNo[20];					/**< Mersis no of the Merchant */
	uint8               TicariSicilNo[16]; 				/**< TicariSicilNo of the merchant */
	uint8               WebAddress[64]; 				/**< WEB address of the merchant as 2 lines, 32 characters each. Strings are not quarantied for NULL termination, user must manage NULL termination */
	uint8               ApplicationUse[512-384];		/**< Reserved */
} ST_EKU_HEADER;

/** TICKET Header structure which is used for TICKET header SET */
typedef struct _ST_TICKET_HEADER
{
	uint32				StructSize;						/**< Sizeof this structure */
	char				szMerchName1[32+1];				/**< Name of the merchant as 2 lines, 32 characters each. User must manage NULL termination after each line*/
	char				szMerchName2[32+1];				/**< Name of the merchant as 2 lines, 32 characters each. User must manage NULL termination after each line*/
	char				szMerchAddr1[32+1];				/**< Address of the merchant as 3 lines, 32 characters each. User must manage NULL termination after each line */
	char				szMerchAddr2[32+1];				/**< Address of the merchant as 3 lines, 32 characters each. User must manage NULL termination after each line */
	char				szMerchAddr3[32+1];				/**< Address of the merchant as 3 lines, 32 characters each. User must manage NULL termination after each line */
	char             	VATOffice [24+1];				/**< VAT office of the merchant, NULL terminated string*/
	char             	VATNumber[12+1];				/**< VAT number of the merchant, NULL terminated string */
	char 				MersisNo[20+1];					/**< Mersis no of the Merchant, NULL terminated string */
	char 				TicariSicilNo[16+1];			/**< TicariSicilNo of the merchant, NULL terminated string */
	char				WebAddress[64+1];               /**< WEB address of the merchant as 2 lines, 32 characters each. Strings are NULL terminated */
	uint32              initDateTime;					/**< Unix time format Date & Time of the Fiscal header when it is first initiated */
	uint16				index;							/**< Index of the header */
	uint16				EJNo;							/**< EJNo  */
} ST_TICKET_HEADER;

/** EKU Module structure which is used for EKU module information */
typedef struct _ST_EKU_MODULE_INFO
{
	uint32				StructSize;						/**< Sizeof this structure */
	DEVICE_INFO_t       Device;							/**< EKU Device Data set */
	EKU_INFO_t          Eku;							/**< EKU info set */
} ST_EKU_MODULE_INFO;

/** Module structure which is used for EKU and FISCAL module information */
typedef struct _ST_MODULE_USAGE_INFO
{
	uint32				StructSize;						/**< Sizeof this structure */
	char				szHardwareReference[16 + 1];	/**<  */
	char				szHardwareSerial[16 + 1];		/**< serial number of the device */
	uint32         		MapFreeArea;					/**< Free area on the map,  */
	uint32         		MapUsedArea;					/**< Used area on the map,  */
	uint32         		DataFreeArea;					/**< Free area on the Data, */
	uint32         		DataUsedArea;					/**< Used area on the Data,  */
} ST_MODULE_USAGE_INFO;

/** Banking functions may return different return codes for each bank  */
typedef struct _ST_MULTIPLE_BANK_RESPONSE
{
	uint32	StructSize;									/**< Sizeof this structure */
	uint16	bkmId;										/**< Unique id of the local Turkish Bank */
	uint16	rescode;									/**< return code of the operation coming from banking application */
} ST_MULTIPLE_BANK_RESPONSE;

/** EKU Application info structure which is used to read data from EKU */
typedef struct _ST_EKU_APPINF
{
	uint32				StructSize;						/**< Sizeof this structure */
	uint8				*Buffer;						/**< pointer to application buffer which the data will be read in */
	uint32           	Amount;							/**< Total amount of the transaction which is saved in EKU*/
	uint32           	Vat;							/**< Total tax of the transaction which is saved in EKU*/
	uint8				DateTime[6];					/**< YMDHMS */
	uint8				DateTimeDelta[6];				/**< YMDHMS */
	uint16 				BufLen;							/**< maximum length of the buffer which is provided from application*/
	uint16				RecLen;							/**< Received length, length of the data copied in buffer */
	uint16           	RemLen;							/**< Remaining length, length of the buffer which remains in EKU and not yet copied into buffer */
	uint16           	ZNo;							/**< Z No */
	uint16           	FNo;							/**< F No */
	uint16           	Type;                       	/**< 2 bytes for alignment, 1 byte written to FLASH */
	uint16           	Func;							/**<  */
	uint16				DateTimeCount;					/**<  */
	uint16           	RecordStatus;					/**<  */
} ST_EKU_APPINF;

/** Cashier info structure which is used for cashier operations */
typedef struct _ST_CASHIER
{
	uint32		StructSize;					/**< Sizeof this structure */
	uint16		index;						/**< zero based index of the cashier, Unique */
	uint32		flags;						/**< set of flags */
	char		name[24+1];					/**< name of the cashier, non unique */
} ST_CASHIER;

/** Structure which is used for file functions */
typedef struct
{
	uint32	StructSize;						/**< Sizeof this structure */
	char	fileName[64];					/**< Name of the file */
	uint32	fileSize;						/**< Size of the file in bytes */
} ST_FILE;

/** Date */
typedef struct ST_DATE
{
	uint8			day;		/**< 1-31 */
	uint8			month;		/**< 1-12 */
	uint16			year;		/**< 0-99 */
} ST_DATE;

/** Time */
typedef struct _ST_TIME
{
	uint8			hour;		/**< 0-23 */
	uint8			minute;		/**< 0-59 */
	uint8			second;		/**< 0-59 */
} ST_TIME;

/** Echo structure which returns some data from ECR for ECHO */
typedef struct _ST_ECHO
{
	uint32		StructSize;						/**< Sizeof this structure */
	uint32		retcode;						/**< Return code of the function, 0 if successful */
	uint32		status;							/**< status of ECR
												\n\t	[\ref GMP3_STATE_BIT_PAIRED]
												\n	[\ref GMP3_STATE_BIT_KEY_EXPIRED]
												\n	[\ref GMP3_STATE_BIT_FISCALIZED]
												\n	[\ref GMP3_STATE_BIT_OKC_MALI_MOD]
												\n	[\ref GMP3_STATE_BIT_PARAMETRE]
												\n	[\ref GMP3_STATE_BIT_NO_PAPER]
												*/
	uint8		kvc[8];							/**< KVC */
	uint8		ecrMode;						/**< ECR Mode */
	uint16		mtuSize;						/**< Maximum Size of buffer which ECR can accept */
	uint8		ecrVersion[16];					/**< ECR SW Version */
	ST_DATE		date;							/**< Date */
	ST_TIME		time;							/**< Time */
	ST_CASHIER	activeCashier;					/**< Active cashier information */
} ST_ECHO;

/** Structure which is used to pass input parameters for PAIRING operation */
typedef struct _ST_GMP_PAIR
{
	uint32		StructSize;								/**< Sizeof this structure */
	char		szProcOrderNumber[6 + 1];				/**< Please see \ref GMP_PROCORDERNUM */
	char		szProcDate[6 + 1];						/**< Date in the format of "YYMMDD" */
	char		szProcTime[6 + 1];						/**< Time in the format of "HHMMSS" */
	char		szExternalDeviceBrand[15 + 1];			/**< Brand Name of the external device. It's optional */
	char		szExternalDeviceModel[15 + 1];			/**< Model Name of the external device. It's optional */
	char		szExternalDeviceSerialNumber[15 + 1];	/**< Serial Number of the external device. It's optional */
	char		szEcrSerialNumber[15 + 1];				/**< Not implemented yet */
} ST_GMP_PAIR;

/** To be defined */
typedef struct _ST_GMP_PAIR_RESP
{
	uint32		StructSize;					/**< Sizeof this structure */
	uint32		ErrorCode;					/**< Pairing Responce error code */
	char		szEcrBrand[15 + 1];			/**< Paired ECR Brand */
	char		szEcrModel[15 + 1];			/**< Paired ECR Model */
	char		szEcrSerialNumber[15 + 1];	/**< Paired ECR Serial Number */
	char		szVersionNumber[8 + 1];		/**< ECR Version Number */
} ST_GMP_PAIR_RESP;

/** To be defined */
typedef struct _GMPEchoMesg
{
	char  ProcOrderNum[3];			/**< To be defined */
	char  localDate[3];				/**< To be defined */
	char  localTime[3];				/**< To be defined */
	char  driverVersion[16];		/**< To be defined */
	char  kcv[64];					/**< To be defined */
	char  status[4];				/**< To be defined */
} GMPEchoMesg;

/** To be defined */
typedef struct _InitStruct
{
	char ecr_procOrderNum[3];			/**< To be defined */
	char ecr_localDate[3];				/**< To be defined */
	char ecr_localHour[3];				/**< To be defined */
	char ecr_ecrBrand[16];				/**< Brand name of ECR, INGENICO */
	char ecr_ecrModel[16];				/**< Model name of ECR */
	char ecr_ecrSerialNum[16];			/**< Sicil (NOT Serial) number of ECR */
	char ecr_driverVersion[16];			/**< Software versiton of ECR */
	char ecr_extDeviceRandNumReq[16];	/**< To be defined */
	char ecr_primeNum[256];				/**< To be defined */
	char ecr_generator[1];				/**< To be defined */
	char ecr_okcRandNumReq[16];			/**< To be defined */
	char ecr_certificate[1338];			/**< To be defined */
	char ecr_errorCode[2];				/**< To be defined */
	char ecr_eftPosIndex[1];			/**< To be defined */
} InitStruct;

/** Structure which is used to define a colomn in a sqlite database query result set */
typedef struct
{
	int  typeOfData;						/**< type of the data */
	char data[1024];						/**< data */
} ST_DATABASE_COLOMN;

/** Structure which is used to define a row in a sqlite database query result set */
typedef struct
{
	int indexOfLine;						/**< index */
	int numberOfColomns;					/**< number of colomns in  the array */
	ST_DATABASE_COLOMN* pstColomnArray;		/**< pointer to the first ST_DATABASE_COLOMN on the array */
} ST_DATABASE_LINE;

/** Database Execute / Query result set */
typedef struct
{
	uint32	StructSize;						/**< Sizeof this structure */
	int numberOfLines;						/**< number of the lines */
	ST_DATABASE_LINE* pstCaptionArray;		/**< pointer to the first ST_DATABASE_LINE array which keeps Caption (colomn) names */
	ST_DATABASE_LINE* pstLineArray;			/**< pointer to the first ST_DATABASE_LINE array which keeps Line (raw) datas */
} ST_DATABASE_RESULT;

typedef enum
{
	ITEM_OPTION_TAX_EXCEPTION_TAXLESS				= (1 << 12),
	ITEM_TAX_EXCEPTION_VAT_INCLUDED_TO_PRICE		= (1 << 12),
	ITEM_TAX_EXCEPTION_VAT_NOT_INCLUDED_TO_PRICE	= (1 << 15),
} EItemOptions;

typedef enum
{
	GMP_EXT_DEVICE_COMM_SCENARIO_NONE =  0,
	GMP_EXT_DEVICE_COMM_SCENARIO_ONLY_ETHERNET,
	GMP_EXT_DEVICE_COMM_SCENARIO_ONLY_GPRS,
	GMP_EXT_DEVICE_COMM_SCENARIO_ETHERNET_AND_GPRS,
} GMP_EXT_DEVICE_SCENARIO_LIST;

typedef enum
{
	ITEM_PROMOTION_DISCOUNT = 1,
	ITEM_PROMOTION_INCREASE = 2,

} EItemPromotionType;

/** Represents a set of parameters for the item sale */
typedef struct _ST_ITEM
{
	uint32	StructSize;				/**< Sizeof this structure */
	uint8	type;					/**< One of the types defined in EItemTypes */
	uint8	subType;				/**< Depends on the type of the item, subType may be needed. For today only use case is ITEM_TYPE_TICKET sub types for the type of the ticket*/
	uint8	deptIndex;				/**< Zero based index of the department table on ECR which will be used to get tax table index. It's mandotary except ITEM_TYPE_PLU*/
	uint8	unitType;				/**< One of the types defined in EItemUnitTypes which represnts unit value to print on the ticket. It's provided from Department Table or PLU DB if not provided. Default value is 0 means "Adet(number)"*/
	uint32	amount;					/**< Unit Amount of the item in 2 precition. Exp: 2TL must be provided as 200*/
	uint16	currency;				/**< One of the International currency codes, ECurrency */
	uint32	count;					/**< Number of items to sale. It's printed on the ticket if it's different than 1*/
	uint32	flag;					/**< Set of flags used to define optional settigs for items. One of EItemOptions */
	uint8	countPrecition;			/**< Precition of the count value. Default value is zero and no precition. Exp: Precition should be 3 and count should be 5600 to print 5,600 on the ticket.*/
	uint8	pluPriceIndex;			/**< PLU records may have multiple prices in PLU Database. This is the index of price to be used. Default value is zero and represents the default amount */
	char	name[32+1];				/**< Optional name of the item to print on the ticket. if not provided Department default name or PLU record name is used to print on ticket */
	char	barcode[32+1];			/**< Optional barcode of the item (it is mandotary for ITEM_TYPE_PLU) */
	char	firm[24+1];				/**< Name of the company, currenct ony used by ITEM_TYPE_MONEYCOLLECTION */
	char	invoiceNo[24+1];		/**< no the invoice, currenct ony used by ITEM_TYPE_MONEYCOLLECTION */
	char	subscriberId[24+1];		/**< Subscriber id of the invoice, currenct ony used by ITEM_TYPE_MONEYCOLLECTION */
	char	tckno[11+1];			/**< TCK No of the customer, currenct ony used by ITEM_TYPE_MONEYCOLLECTION */
	uint32  Reserved;				/**< it  */
	uint8	Date[3];				/**< Date in unix format which is used on ITEM_TYPE_MONEYCOLLECTION types to print on the ticket in FATURA TAHSILAT transaction, currenct ony used by ITEM_TYPE_MONEYCOLLECTION */
	struct
	{
		uint8	type;				/**< One of \ref EItemPromotionType	*/
		uint32	amount;				/**< Amount of the Decrease/Increase amount which is done by the external system for this item. If there is more then one item (count & countPrecition), this amount is the total promotion amount for all unit count, not the unit price. */
		char	ticketMsg[32+1];	/**< Optional message text of the action to print on the ticket. if not provided, default messages ("INDIRIM" / "ARTTIRIM" will be used on ECR) */
	} promotion;
	uint16 OnlineInvoiceItemExceptionCode;
} ST_ITEM;

/** Structure which is used to pass someparameters into FP3_Funcion function */
typedef struct _ST_FUNCTION_PARAMETERS
{
	uint32			StructSize;				/**< Sizeof this structure */
	uint32			EKUNo;					/**< EKU number */
	struct
	{
		char		supervisor[12 + 1];		/**< password of supervisor, required in some reports */
		char		cashier[12 + 1];		/**< password of cashier, required in some actions */
	}				Password;				/**< password */
	struct
	{
		uint32		ZNo;					/**< Z No */
		uint32		FNo;					/**< Ticket No */
		ST_DATE		date;					/**< Date */
		ST_TIME		time;					/**< Time */
	} start;						/**< start */
	struct
	{
		uint32		ZNo;					/**< Z No */
		uint32		FNo;					/**< Ticket No */
		ST_DATE		date;					/**< Date */
		ST_TIME		time;					/**< Time */
	} finish;					/**< finish */
} ST_FUNCTION_PARAMETERS;

/** Structure which is used to define an item in department table */
typedef struct _ST_DEPARTMENT
{
	uint32			StructSize;			/**< Sizeof this structure */
	char         	szDeptName[24];		/**< Name Of the department given by Merchant */
	uint8         	u8TaxIndex;			/**< Zero based index on the TAX table provided by GIB & TSM */
	ECurrency		iCurrencyType;		/**< Default currency of the department */
	EItemUnitTypes	iUnitType;			/**< Default unit type of the department */
	uint64			u64Limit;			/**< maximum amount that can be sold from this department (in one item sale) */
	uint64			u64Price;			/**< Default unit amount of the department. It can be overttien by setting another item value */
	uint8			bLuchVoucher;		/**< Enables/disables a department if payment is done by lunch voucher */
} ST_DEPARTMENT;

/** Structure which is used to define an item in tax table */
typedef struct _ST_TAX_RATE
{
	uint32	StructSize;					/**< Sizeof this structure */
	uint16 taxRate;						/**< Tax rate provided by GIB & TSM. It's "1800 for %18" and "850 for %8,5" !! */
} ST_TAX_RATE;

/** Set of variables to keep different information for one currency. It's download one for eac hdifferent currency (other than TL which is default one) from TSM & GIB */
typedef struct _ST_EXCHANGE
{
	uint32	StructSize;					/**< Sizeof this structure */
	uint16	code;						/**< currency code which is one of ECurrency */
	char	prefix[3];					/**< currency prefix */
	char	sign[3];					/**< currency sign */
	uint8	locationOfSign;				/**< locatin of sign */
	uint8	tousandSeperator;			/**< Alphanumeric character used to show tousand seperator, it may be '.' or ',' for example*/
	uint8	centSeperator;				/**< Alphanumeric character used to show decimal seperator, it may be '.' or ',' for example*/
	uint8	numberOfCentDigit;			/**< it is the precition number used for decimal, it's 2 most of the cases*/
	uint64	rate;						/**< currency convertion rate */
} ST_EXCHANGE;

typedef struct _ST_EXCHANGE_PROFILE
{
	uint32	StructSize;
	char	ProfileName[12];
	uint8   NumberOfCurrency;
	ST_EXCHANGE ExchangeRecords[6];
} ST_EXCHANGE_PROFILE;

/** Set of variables to keep PLU Records */
typedef struct
{
	uint32	StructSize;			/**< Sizeof this structure */
	char 	deptIndex;			/**< A zero based index on the Department Table of the ECR. Each PLU record has to point a valid department index */
	char 	unitType;			/**< One of the types defined in EItemUnitTypes which represnts unit value to print on the ticket. It's provided from Department Table or PLU DB if not provided. Default value is 0 means "Adet(number)"*/
	uint32	flag;				/**< set of flags */
	uint32	lastModified;		/**< unix format date and time which represents the last modification date of the record on ECR PLU DB */
	uint16	currency[3];		/**< One of ECurrency types. There could be 3 different PLU amount and currency and application may use it for differet reasons */
	uint32	amount[3];			/**< Amount of the PLU. There could be 3 different PLU amount and currency and application may use it for differet reasons */
	char 	barcode[32+1];		/**< Barcode of the PLU */
	char 	name[32+1];			/**< Name of the PLU to print on the ticket */
	uint32	groupParentId;		/**< Id of the group (as in ST_PLU_GROUP_RECORD) that this PLU is owned by*/
} ST_PLU_RECORD;

/** Set of variables to keep PLU Group Records */
typedef struct
{
	uint32	StructSize;			/**< Sizeof this structure */
	uint32 	groupId;			/**< Id of the group */
	uint32	groupFlag;			/**< Set of flags  */
	char 	name[32+1];			/**< Name of the group */
} ST_PLU_GROUP_RECORD;

/** Structure which is used to define an item in ticket table */
typedef struct _ST_SALEINFO
{
	uint8	ItemType;					/**< One of the types defined in EItemTypes */
	uint64	ItemPrice;					/**< Unit Amount of the item in 2 precition. Exp: 2TL must be provided as 200*/
	uint64  IncAmount;					/**< Increased amount, always in TL */
	uint64  DecAmount;					/**< Decreased amount, always in TL */
	uint32	OrigialItemAmount;			/**< Original item amount */
	uint16 	OriginalItemAmountCurrency;	/**< Original item amount currency */
	uint16 	ItemVatRate;				/**< Tax rate of the item. It is 1800 for %18 */
	uint16	ItemCurrencyType;			/**< One of the International currency codes, ECurrency */
	uint8 	ItemVatIndex;				/**< Zero based index on Tax rate table */
	uint8	ItemCountPrecision;			/**< Precition of the count value. Default value is zero and no precition. Exp: Precition should be 3 and count should be 5600 to print 5,600 on the ticket.*/
	uint32	ItemCount;					/**< Number of items to sale. It's printed on the ticket if it's different than 1*/
	uint8	ItemUnitType;				/**< One of the types defined in EItemUnitTypes which represnts unit value to print on the ticket. It's provided from Department Table or PLU DB if not provided. Default value is 0 means "Adet(number)"*/
	uint8	DeptIndex;					/**< Zero based index of the department table on ECR which will be used to get tax table index. It's mandotary except ITEM_TYPE_PLU*/
	int  	Flag;						/**<  */
	char	Name[32+1];					/**< Optional name of the item to print on the ticket. if not provided Department default name or PLU record name is used to print on ticket */
	char	Barcode[32+1];				/**< Optional barcode of the item (it is mandotary for ITEM_TYPE_PLU) */
} ST_SALEINFO;


/** Structure which is used to define a printed line */
typedef struct
{
	uint32 	Flag;						/**< One of GMP3_PS_ flags, Exp; PS_24 */
	uint8 	lineLen;					/**< Length of the line */
	char  	line[48+1];					/**< Buffer to print on ticket */
} ST_printerDataForOneLine;

/** Structure which is used to define a card information */
typedef struct _ST_CARD_INFO
{
	uint32	StructSize;				/**< Sizeof this structure */
	uint8   inputType;				/**< Type of the card input
									\n	READER_TYPE_MCR    : Magnatic Card Reader
									\n	READER_TYPE_SCR    : Smart Card Reader
									\n	READER_TYPE_CLESS  : Contactless Card Reader
									*/
	char    pan[19+1];				/**< Card Number which is NULL terminated string. Card number may be masked like 5400********1234 */
	char    holderName[20 + 1];		/**< Card Holder name which is NULL terminated string. Card holder name may be masked like AH*** ***IR  */
	uint8   type[3];				/**< type[0..2] => bkmId, type[3] =>Kart tipi, bonus, S&M, Vada vs.. */
	char    Reserved1[4 + 8];		/**< Reserved1 Do Not Use. */
} ST_CARD_INFO;

/** Structure which is used to define an error coming from payment appllication (or bank servers) */
typedef struct
{
	char   ErrorCode[4+1];				/**< Error code sent by Bank Servers */
	char   ErrorMsg[40+1];				/**< Error message sent by Bank Servers */
	char   AppErrorCode[4+1];			/**< Error code sent by Payment application */
	char   AppErrorMsg[40+1];			/**< Error message sent by Payment Application */
} ST_PaymentErrMessage;

/** Structure which is used to define bonus/merchant loyality/ discount message coming from payment application (or bank servers) */
typedef struct _ST_BankSubPaymentInfo
{
	uint16		type; 				// EPaymentSubType
	uint32		amount;
	char		name[11 + 1];
} ST_BankSubPaymentInfo;

/** Structure which is used to define a bank payment info */
typedef struct _ST_BANK_PAYMENT_INFO
{
	uint32  batchNo;					/**< Batch No of the payment application */
	uint32  stan;						/**< Stan No of the payment application */
	uint32	balance;					/**< Remain value of the prepayment card */
	uint16  bankBkmId;					/**< BKM ID of the payment application */
	uint8	numberOfdiscount;			/**< No use */
	uint8	numberOfbonus;				/**< No use */
	uint8	authorizeCode[6 + 1];		/**< Authorization code */
	uint8   transFlag[2]; 				/**< Set of Flags
										\nbyte[0]
										\n
										\n IMP_APP_TRANS_INFO_FLAG_DEBIT_CARD									0x80
										\n IMP_APP_TRANS_INFO_FLAG_INTERNATIONAL_CARD							0x40
										\n IMP_APP_TRANS_INFO_FLAG_CARD_IN_CHIP_READER							0x20
										\n IMP_APP_TRANS_INFO_FLAG_VALIDATOR_AKTARMA_ISLEM						0x10
										\n IMP_APP_TRANS_INFO_FLAG_VALIDATOR_NO_CONNECTTION_FOR_SETTLEMENT		0x08
										\n IMP_APP_TRANS_INFO_FLAG_FALLBACK_TO_MAGSTIPE							0x04
										\n IMP_APP_TRANS_INFO_FLAG_ONUS_CARD									0x01
										\n
										\nbyte[1]
										\n IMP_APP_TRANS_INFO_FLAG_APPROVED_OFFLINE								0x80
										\n IMP_APP_TRANS_INFO_FLAG_APPROVED										0x40    // Kasa tarafý bu bayraða bakarak onaylanýp onaylanmadýðýný kontrol edecek.
										\n IMP_APP_TRANS_INFO_FLAG_TRANSACTION_VOIDED							0x20     // Only for Transaction Inquiry
										\n IMP_APP_TRANS_INFO_FLAG_PIN_USED										0x10
										\n IMP_APP_TRANS_INFO_FLAG_SIGNATURE_REQUIRED							0x08
										\n
										*/
	uint8	terminalId[8 + 1];			/**< Terminal Id of Payment Application */
	uint8	rrn[12 + 1];				/**< Reference Number of Payment Application */
	uint8	referenceCodeOfTransaction[16 + 1];		/**< Transfer Reference Code */
	uint8	merchantId[15 + 1];			/**< Merchant Id of Payment Application */
	char	bankName[21];				/**< Name of of Payment Application */
	uint8	numberOfInstallments;		/**< Number of installment */
	uint8	numberOfsubPayment;			/**< Number of subpayment
										\n
										= 1
										\n	PAYMENT_SUBTYPE_DEBIT						= 2
										\n	PAYMENT_SUBTYPE_CREDIT_PUAN					= 3
										\n	PAYMENT_SUBTYPE_LOYALTY_PUAN				= 4
										\n	PAYMENT_SUBTYPE_BANKING_INDIRIM				= 5
										\n	PAYMENT_SUBTYPE_RECEIPT_INDIRIM             = 6
										\n	PAYMENT_SUBTYPE_BANKING_INDIRIM_MATRAHSIZ	= 7
										\n	PAYMENT_SUBTYPE_VAS_INDIRIM                 = 8
										*/
	uint8	numberOferrorMessage;		/**< No use */
	char    LoyaltyCustomerId[32];			/**< Payment request process for Loyalty Customer ID*/
	char    PaymentProvisionId[24];  		/**< Payment Provision ID used by VAS application */
	uint16	LoyaltyServiceId;				/**< Payment request process for Service registered application as loyalty */
	uint8	Dummy[2];						/*Dumy for VersionKontrol! BankPaymentUniqueId deðiþikliðinde sizeof farklý çýkmasý için (v15r13)*/
	char	BankPaymentUniqueId[16 + 1];	/**< Payment Unique ID for checking transaction. */
	ST_BankSubPaymentInfo stBankSubPaymentInfo[12]; /**< Sub Payment Info */
	ST_CARD_INFO	stCard;				/**< Card data */
	ST_PaymentErrMessage stPaymentErrMessage;	/**< Payment application error codes */
} ST_BANK_PAYMENT_INFO;

/** Structure which is used to define a payment
	This structure is also used for a response in refund and payment check functions because of having same return items.
*/
typedef struct _ST_PAYMENT
{
	uint8 	flags;						/**< Set of flags */
	uint32  dateOfPayment;				/**< Date & Time of the payment in unix date format */
	uint32 	typeOfPayment;				/**< One of EPaymentTypes */
	uint8	subtypeOfPayment;			/**< One of EPaymentSubtypes */
	uint32	orgAmount;					/**< Original amount of payment (can be non TL) */
	uint16	orgAmountCurrencyCode;		/**< One of ECurrency which is original amount currency code */
	uint32	payAmount;					/**< always TL with precision 2, it is 200 for 2TL */
	uint16	payAmountCurrencyCode;		/**< always CURRENCY_TL */
	uint32  cashBackAmountInTL;			/**< Cashback amount with precision 2, it is 200 for 2TL */
	uint32  cashBackAmountInDoviz;		/**< Cashback amount in exchage with precision 2, it is 230 for 2,30â‚¬ */
	char 	paymentName[24];			/**< Payment name written on the ticket */
	char 	paymentInfo[24];			/**< Payment sub message acording to the payment type */
	ST_BANK_PAYMENT_INFO stBankPayment;	/**< Bank payment info */
} ST_PAYMENT;

/** Structure which is used to define a payment
	This structure is also used for a response in refund and payment check functions because of having same return items.
*/
typedef struct _ST_PAYMENT_RESPONSE
{
	uint32	StructSize;					/**< Sizeof this structure */
	uint8 	flags;						/**< Set of flags */
	uint32  dateOfPayment;				/**< Date & Time of the payment in unix date format */
	uint32 	typeOfPayment;				/**< One of EPaymentTypes */
	uint8	subtypeOfPayment;			/**< One of EPaymentSubtypes */
	uint32	orgAmount;					/**< Original amount of payment (can be non TL) */
	uint16	orgAmountCurrencyCode;		/**< One of ECurrency which is original amount currency code */
	uint32	payAmount;					/**< always TL with precision 2, it is 200 for 2TL */
	uint16	payAmountCurrencyCode;		/**< always CURRENCY_TL */
	uint32  cashBackAmountInTL;			/**< Cashback amount with precision 2, it is 200 for 2TL */
	uint32  cashBackAmountInDoviz;		/**< Cashback amount in exchage with precision 2, it is 230 for 2,30â‚¬ */
	char 	paymentName[24];			/**< Payment name written on the ticket */
	char 	paymentInfo[24];			/**< Payment sub message acording to the payment type */
	ST_BANK_PAYMENT_INFO stBankPayment;	/**< Bank payment info */
} ST_PAYMENT_RESPONSE;

/** Structure which is used to define a payment request from external system to ECR */
typedef struct _ST_PAYMENT_REQUEST
{
	uint32	StructSize;						/**< Sizeof this structure */
	uint32 	typeOfPayment;					/**< One of EPaymentTypes */
	uint32	subtypeOfPayment;				/**< One of EPaymentSubtypes */
	uint32	payAmount;						/**< Payment amount */
	uint32	payAmountBonus;					/**< Payment bonus amount */
	uint16	payAmountCurrencyCode;			/**< Payment amount currency Code */
	uint16  bankBkmId;						/**< BKM Id of the payment application, Zero if not used */
	uint16	numberOfinstallments;			/**< Number of installments, Zero if not used */

	// Refund
	uint32	Reserved11;		 				/**< Reserved11 Do not use it. */
	uint32	Reserved3;						/**< Reserved3 Do not use it. */
	uint32	Reserved4;						/**< Reserved4 Do not use it. */
	uint8 	Reserved5[12]; 					/**< Reserved5 Do not use it. */
	uint8  	Reserved6[16];					/**< Reserved6 Do not use it. */
	uint8	Reserved7[15];					/**< Reserved7 Do not use it. */
	uint8   Reserved8; 						/**< Reserved8 Do not use it. */
	uint8 	Reserved9[6];					/**< Reserved9 Do not use it. */
	uint8 	terminalId[8]; 					/**< ascii for multimerchant */
	uint8 	Reserved10[5];					/**< Reserved10 Do not use it. */

	struct _ST_PAYMENT_REQUEST_ORGINAL_DATA
	{
		uint32	TransactionAmount;				/**< tag 21 OrgTransAmount[6] bcd */
		uint32	LoyaltyAmount;					/**< tag 25 OrgLoyaltyAmount[6] bcd */
		uint16	NumberOfinstallments;			/**< tag 22 Number of installments, Zero if not used */
		uint8 	AuthorizationCode[6];			/**< tag 45 ascii */
		uint8 	rrn[12]; 						/**< tag 46 ascii */
		uint8 	TransactionDate[5];				/**< tag 47 OrgTransDate[5] bcd YY- YYMMDDHHMM */
		uint8	MerchantId[15];					/**< tag 67 ascii */
		uint8   TransactionType; 				/**< tag 70 byte */
		uint8  	referenceCodeOfTransaction[16];	/**< tag 75 ascii */
	} OrgTransData;

	uint32  batchNo;						/**< Batch number */
	uint32  stanNo;							/**< Stan number */
	uint16	rawDataLen;                     /**< raw data length for payment application */
	uint8	rawData[512];                   /**< rawData exchange between two application */
	char	paymentName[23 + 1];			/**< Payment name written on the ticket */
	char	paymentInfo[23 + 1];			/**< Payment sub message acording to the payment type */
	uint8	Reserved12[55 + 8];				/**< Reserved12 Do not use it. */
	uint32	transactionFlag;				/**< External Device Transaction Flags - 1 */
	uint8	Reserved1;						/**< Reserved1 Do not use it.*/
	uint8	Reserved2;						/**< Reserved2 Do not use it.*/
	uint32	flags;							/**< Payment request process flags */
	char    LoyaltyCustomerId[32];			/**< Payment request process for Loyalty Customer ID*/
	char    PaymentProvisionId[24];  		/**< Payment Provision ID used by VAS application */
	uint16	LoyaltyServiceId;				/**< Payment request process for Service registered application as loyalty */
	char	BankPaymentUniqueId[16 + 1];		/**< Payment Unique ID for checking transaction. */
} ST_PAYMENT_REQUEST;

typedef struct _ST_TRANS_PAYMENT_PRINT
{
	uint32	StructSize;					/**< Sizeof this structure */
	uint16	bankBkmId;					/**< BKM Id of the payment application, Zero if not used */			// GMP_EXT_DEVICE_ODEME_BKM_ID
	uint8	terminalId[8 + 1];			/**< ascii for terminal ID */										// GMP_EXT_DEVICE_ODEME_TERMINAL_ID
	uint32	batchNo;					/**< Batch number */												// GMP_EXT_DEVICE_ODEME_BATCH_NO
	uint32	stanNo;						/**< Stan number */													// GMP_EXT_DEVICE_ODEME_STAN
	uint16	retcode;					/**< return code of the process */									// GMP_TAG_HATA_KODU
} ST_TRANS_PAYMENT_PRINT;

typedef struct _ST_TRANS_INQUIRY
{
	uint32	StructSize;													/**< Sizeof this structure */
	uint16	BankBkmId;													/**< BKM Id of the payment application, Zero if not used */				// GMP_EXT_DEVICE_ODEME_BKM_ID
	uint8	szTerminalId[8 + 1];										/**< ascii for terminal ID */											// GMP_EXT_DEVICE_ODEME_TERMINAL_ID
	uint32	Batch;														/**< Batch number */													// GMP_EXT_DEVICE_ODEME_BATCH_NO
	uint32	Stan;															/**< Stan number */														// GMP_EXT_DEVICE_ODEME_STAN
	uint8	TransactionType;											/**< Transaction Type */												// GMP_EXT_DEVICE_ODEME_TIP
	uint16	ECROptions;													/**< ECR Options  */													// GMP_TAG_OPTIONS
	uint32	ECROptions2;												/**< ECR Options2 */													// GMP_TAG_OPTIONS
	uint16	MessageResponseCode;										/**< Message Response Code  */											// GMP_EXT_DEVICE_TAG_HATA_KODU
	uint16	AuthorisedBank;												/**< Authorised Bank BCD[3] */											// GMP_EXT_DEVICE_ODEME_BANKNAME
	uint8	szResponseCode[2 + 1];										/**< Response Code ASCII[2] */											// GMP_EXT_DEVICE_TAG_HATA_KODU
	uint8	szTransactionDateTime[12 + 1];								/**< Transaction Date & Time BCD[6] */									// GMP_EXT_DEVICE_ODEME_DATETIME
	uint16	TransactionInformationFlags;								/**< Transaction Information Flags
																		\n
																		\n IMP_APP_TRANS_INFO_FLAG_DEBIT_CARD									0x8000
																		\n IMP_APP_TRANS_INFO_FLAG_INTERNATIONAL_CARD							0x4000
																		\n IMP_APP_TRANS_INFO_FLAG_CARD_IN_CHIP_READER							0x2000
																		\n IMP_APP_TRANS_INFO_FLAG_VALIDATOR_AKTARMA_ISLEM						0x1000
																		\n IMP_APP_TRANS_INFO_FLAG_VALIDATOR_NO_CONNECTTION_FOR_SETTLEMENT		0x0800
																		\n IMP_APP_TRANS_INFO_FLAG_FALLBACK_TO_MAGSTIPE							0x0400
																		\n IMP_APP_TRANS_INFO_FLAG_ONUS_CARD									0x0100
																		\n IMP_APP_TRANS_INFO_FLAG_APPROVED_OFFLINE								0x0080
																		\n IMP_APP_TRANS_INFO_FLAG_APPROVED										0x0040    // Kasa tarafý bu bayraða bakarak onaylanýp onaylanmadýðýný kontrol edecek.
																		\n IMP_APP_TRANS_INFO_FLAG_TRANSACTION_VOIDED							0x0020     // Only for Transaction Inquiry
																		\n IMP_APP_TRANS_INFO_FLAG_PIN_USED										0x0010
																		\n IMP_APP_TRANS_INFO_FLAG_SIGNATURE_REQUIRED							0x0008
																		\n
																		*/									// GMP_EXT_DEVICE_ODEME_FLAGS
	uint16	ApplicationInformationFlags;								/**< Application Information Flags  */									// GMP_EXT_DEVICE_ODEME_INFO_FLAGS
	uint8	szPAN[19 + 1];												/**< PAN number min:13 max:19 bytes */									// GMP_EXT_DEVICE_ODEME_KART_PAN
	uint32	AuthorisedAmount;											/**< Authorised Amount BCD[6]   */										// GMP_EXT_DEVICE_ODEME_TUTAR
	uint8	szAuthorisationNumber[6 + 1];								/**< Authorised Number ASCII[6] */										// GMP_EXT_DEVICE_ODEME_ONAY_KOD
	uint8	szBankHostResponseCode[4 + 1];								/**< Authorised Number ASCII[4] */										// GMP_EXT_DEVICE_TAG_HATA_KODU
	uint8	szAdditionalResponseDescriptionForDisplay[40 + 1];			/**< AdditionalResponseDescriptionForDisplay ASCII[40] */				// GMP_EXT_DEVICE_TAG_HATA_MSG
	uint8	szBankApplicationSpecificInternalErrorDescription[60 + 1];	/**< Bank Application Specific Internal Error Description  ASCII[60] */	// GMP_EXT_DEVICE_ODEME_ERROR_TEXT
	uint16	BankSpecificErrorCode;										/**< Bank specific error code  */										// GMP_EXT_DEVICE_TAG_HATA_KODU
	uint8	szPOSApplicationBankVersion[30 + 1];						/**< POS Application Bank Version ASCII[30] */							// GMP_TAG_VERSION
	uint8	szPOSApplicationInternalVersion[30 + 1];					/**< POS Application Internal Version ASCII[30] */						// GMP_TAG_VERSION
} ST_TRANS_INQUIRY;

typedef struct
{
	uint32	StructSize;
	uint8 AdiSoyadi[32];
	uint8 Unvan[32];
	uint8 Adres[128];
	uint8 VergiDairesi[32];
	uint8 VknTckn[12];
	uint16	StopajOrani;
	uint16	TevkifatOrani;
} ST_SMM_DATA;

typedef struct
{
	uint32	StructSize;
	uint8 AliciAdiSoyadi[32];
	uint8 AliciAdres[128];
	uint8 AliciUnvan[32];
	uint8 SaticiAdiSoyadi[32];
	uint8 FaturaSeri[16];
	uint8 FaturaSira[16];
	uint8 FaturaTarih[16];
	uint16	StopajOrani;
	int KDVDahil;
} ST_GIDER_PUSULASI;

/** Structure which is used to define one tax total*/
typedef struct
{
	uint32		u32VAT;						/**< Total Tax in TL with precition 2 */
	uint32		u32Amount;					/**< Total Amount in TL with precition 2 */
	uint16		u16VATPercentage;			/**< Tax rate, it is 1800 for %18 */
} ST_VATDetail;

#define MAX_SALE_INFO				512		/**< ST_TICKET MAX SALE INFO COUNT */
#define MAX_PAYMENT					24		/**< ST_TICKET MAX PAYMENT COUNT */
#define MAX_TAX_DETAIL				8		/**< ST_TICKET MAX TAX DETAIL COUNT */
#define MAX_PRINTER_COPY			1024	/**< ST_TICKET MAX PRINTER DETAIL COUNT */
#define MAX_LOYALITY_TRANS_NUMBER	8		/**< ST_TICKET MAX LOYALTY CUSTOMER COUNT */
#define MAX_VAS_PAYMENT_NAME		16		/**< ST_VAS_PAYMENT_INFO MAX PAYMENT NAME CHAR COUNT */
#define MAX_VAS_PAYMENT_COUNT		4		/**< ST_VAS_PAYMENT_INFO MAX SUPPORTED PAYMENT COUNT */

/** Structure which is used to define loyalty service parameters */
typedef struct
{
	uint32	StructSize;							/**< Sizeof this structure */
	uint8	name[24];							/**< Name of the Service */
	char	CustomerId[32];						/**< Customer ID*/
	uint16  ServiceId;							/**< Service ID*/
	uint16 	u16AppId;							/**< VAS app ID*/
	uint16  CustomerIdType;						/**< Type of entry: MOB:1, CUSTOMER ID:2, OTHER:3 */
	uint32  TotalDiscountAmount;				/**< Total Discount Amount*/
} ST_LOYALTY_SERVICE_INFO;

/** Structure which is used to define loyalty service parameters */
typedef struct
{
	uint32	StructSize;							/**< Sizeof this structure */
	uint8	name[24];							/**< Name of the Service */
	char	CustomerId[32];						/**< Customer ID*/
	uint16  ServiceId;							/**< Service ID*/
	uint16 	u16AppId;							/**< VAS app ID*/
	uint16  CustomerIdType;						/**< Type of entry: MOB:1, CUSTOMER ID:2, OTHER:3 */
	uint32  Amount;								/**< Amount*/
	uint8   rawData[512];						/**< 512 byte buffer to transmit or receive data to/from loyaltu application*/
	uint16  rawDataLen;							/**< Raw data length */
	uint8   IsBenefit;							/**< Benefit request from Service*/
} ST_LOYALTY_SERVICE_REQ;

#define LOYALTY_CUSTOMER_ID_TYPE_MOBILE_TEL		1
#define LOYALTY_CUSTOMER_ID_TYPE_MUSTERI_NO 	2
#define LOYALTY_CUSTOMER_ID_TYPE_DIGER			3

/** Structure which is used to keep one ticket data coming from ECR */
typedef struct _ST_TICKET
{
	uint32	StructSize;											/**< Sizeof this structure */
	uint32	TransactionFlags;									/**< Set of Flags which are replied from ECR and represents the status of ticket */
	uint32	OptionFlags;										/**< One of Option Flags for GMP3. ext GMP3_OPTION_ECHO_PRINTER */
	uint16 	ZNo;												/**< Z No of the ticket */
	uint16 	FNo;												/**< F No of the ticket */
	uint16 	EJNo;												/**< EKU No of the ticket */
	uint32  TotalReceiptAmount;									/**< Total net amount of the items on the ticket */
	uint32  TotalReceiptTax;									/**< Total net tax of the items on the ticket */
	uint32	TotalReceiptDiscount;								/**< Total net discount made on the ticket */
	uint32	TotalReceiptIncrement;								/**< Total net increase made on the ticket */
	uint32  CashBackAmount;										/**< Cashback amount */
	uint32	TotalReceiptItemCancel;								/**< Total net cancels made on the ticket */
	uint32  TotalReceiptPayment;								/**< Total net payments made for the ticket */
	uint32	TotalReceiptReversedPayment;						/**< Total net reverse payments made for the ticket */
	uint32	KasaAvansAmount;									/**< Total Avans amount */
	uint32	KasaPaymentAmount;									/**< Total Payment amount */
	uint32	invoiceAmount;										/**< Total amount subject to Invoice ticket */
	uint32	invoiceAmountCurrency;								/**< Currency of invoice amount subject to Invoice ticket */
	uint32	KatkiPayiAmount;									/**< Total KatkÄ±PayÄ± amount */
	uint32	TaxFreeRefund;										/**< TotalTaxFree amount */
	uint32	TaxFreeCalculated;									/**< Tax Free Refund Amount which is calculated on ECR based on GIB Refund table (if the transaction is set as TaxFree Transaction ) */
	uint8   szTicketDate[6 + 1];								/**< Date of the ticket as ASCII YYMMDD */
	uint8   szTicketTime[6 + 1];								/**< Time of the ticket as ASCII HHMMSS */
	uint16	SourceVasAppID;										/**< Transaction Starter App ID */
	uint16	PaymentVasAppID;									/**< Invoice Payment App ID  */
	uint16	BankVasAppID;										/**< Loyalty Payment App ID */
	uint8 	ticketType;											/**< One of TTicketType */
	uint16  totalNumberOfItems;									/**< Total number of items on the ECR ticket including canceled ones */
	uint16  numberOfItemsInThis;								/**< Number of items received in this structure including canceled ones */
	uint16  totalNumberOfPayments;								/**< Total number of payments on the ECR ticket including canceled ones */
	uint16  numberOfPaymentsInThis;								/**< Number of payments received in this structure including canceled ones */
	uint16  numberOfLoyaltyInThis;								/**< Number of loyalty received in this structure */
	char	TckNo[12];											/**< TCK No, Turkish Citizien ID used for Matrahsiz (KatkiPayi) entries */
	char	invoiceNo[24 + 1];									/**< Number of Invoice, it is alphanumeric */
	uint32	invoiceDate;										/**< Date of the Invoice in Unix Date & Time format */
	uint8	invoiceType;										/**< Type of the Invoice */
	int		totalNumberOfPrinterLines;							/**< Total number of printer lines on the ECR ticket already printed */
	int		numberOfPrinterLinesInThis;							/**< Number of printer lines received in this structure, it is a part of already printed lines */
	uint8   uniqueId[24];										/**< Unique Id of the transaction */
	uint8   rawData[512];									    /**< Raw Data */
	uint16  rawDataLen;											/**< Raw Data Length*/
	uint8	UserData[64];										/**< User Data which is given at start function */
	uint8	CurrencyProfileIndex;								/**< Used Currency Profile Index */
	char	LastPaymentErrorCode[4 + 1];						/**< This shows the payment error code which is not added to payment list */
	char	LastPaymentErrorMsg[40 + 1];						/**< This shows the payment error message which is not added to payment list */
	char	BankPaymentUniqueId[16 + 1];						/**< Payment Unique ID for checking transaction. */
	char	InvoiceETTN[36 + 1];								/**< Online invoice ETTN info is filled only in online invoice transaction*/
	ST_SALEINFO		SaleInfo[MAX_SALE_INFO];					/**< Details of items on ECR ticket */
	ST_PAYMENT		stPayment[MAX_PAYMENT];						/**< Details of payments on ECR ticket */
	ST_VATDetail    stTaxDetails[MAX_TAX_DETAIL];				/**< Details of tax totals on ECR ticket */
	ST_printerDataForOneLine stPrinterCopy[MAX_PRINTER_COPY];	/**< Printer lines which are already printed on the printer and echo to external system for information */
	ST_LOYALTY_SERVICE_INFO stLoyaltyService[MAX_LOYALITY_TRANS_NUMBER]; /**< User Data which is given at start function */
} ST_TICKET;

/**   */
typedef struct
{
	uint32 StructSize;											/**< Sizeof this structure */
	uint16 u16AppId;
	uint16 ServiceId;
	uint8  CustomerId[32];
	uint16 Command;
	uint16 Version;
	uint8  LoyaltyData[512];
	uint16 LoyaltyDataLen;
} ST_LOYALTY_PROCESS;/**   */

/**   */
typedef struct
{
	uint64	hTrx;
	uint8  sicilNoOfMasterEcr[12+1];
	char   userDefination[16+1];
	char   userDefinedGroup[16+1];
	uint8  totalAmount;
} ST_MASTERECR_BACKGROUND_TRX_HANDLE;/**   */

typedef struct
{
	uint16 maxNumberOfHandles;
	uint16 numberOfHandlesInList;
	uint8  sicilNoOfMasterEcr[24+1];
	uint8  nameOfMasterEcr[24+1];
	uint32 creationDateOfList;
	ST_MASTERECR_BACKGROUND_TRX_HANDLE* pHandle;
} ST_MASTERECR_HANDLE_LIST;

/**   */
typedef struct
{
	uint16 sizeOfBuffer;
	uint16 lenOfData;
	uint16 numberOfCommandsInList;
	uint8  sicilNoOfMasterEcr[12+1];
	uint8  nameOfMasterEcr[24+1];
	uint8  signOfMasterEcr[32];
	uint32 dateOfMasterEcr;
	uint64 transactionHandle;
	uint8  Data[64000];
} ST_MASTERECR_TRANSACTION_DATA;

/** Structure which is used to define a user message */
typedef struct
{
	uint32	StructSize;							/**< Sizeof this structure */
	uint32 flag;								/**< One of GMP3_PS_ flags*/
	uint8  len;									/**< length of the message */
	uint8  message[48+1];						/**< message */
} ST_USER_MESSAGE;

typedef struct
{
	uint32	StructSize;							/**< Sizeof this structure */
	uint32 flag;								/**< One of GMP3_PS_ flags*/
	uint16  len;								/**< length of the message */
	uint8  message[1024];						/**< message */
} ST_USER_MESSAGE_EX;

/** Structure which is used to define an invoice parameters */
typedef struct
{
	uint32	StructSize;							/**< Sizeof this structure */
	uint8	source;								/**< One of EInvoiceSource */
	uint8	no[24+1];							/**< Invoice No */
	uint8	date[3];							/**< Date of Invoice as bcd YYMMDD */
	uint8	tck_no[11+1];						/**< TCK No, Turkish Citizien No */
	uint8	vk_no[11+1];						/**< VK No, Taxation No, Vergi Kimlik No */
	uint64	amount;								/**< Amount of the invoice with 2 precision. it is 258 for 2.58 */
	uint16	currency;							/**< Currency code of invoice amount. One of \ref ECurrency. Use CURRENCY_TL as a default */
	uint32	flag;								/**< One of EInvoiceFlags */
} ST_INVIOCE_INFO;

/** Structure which is used to define an invoice parameters */
typedef struct
{
	uint32	StructSize;										/**< Sizeof this structure */
	uint8	CustomerName[64 + 1];							/**< Invoice Customer Name */
	uint8	VKN[24 + 1];									/**< Invoice No */
	uint8	HomeAddress[64 + 1];							/**< Customer Home Address */
	uint8	District[24 + 1];								/**< Customer District */
	uint8	City[24 + 1];									/**< City */
	uint8	Country[24 + 1];								/**< Country */
	uint8	Mail[64 + 1];									/**< Customer Mail */
	uint8	WebSite[64 + 1];								/**< Customer WebSite */
	uint8	Phone[20 + 1];									/**< Customer Phone */
	uint8	TaxOffice[24 + 1];								/**< Tax Office */
	uint8	DespatchNo[24 + 1];								/**< Invoice Despatch No */
	uint8	Identifier[64 + 1];								/**< Invoice Identifier */
	uint8	OrderNo[24 + 1];								/**< Invoice Order No */
	uint8	Ettn[36 + 1];									/**< Invoice Ettn */
	uint8	Type[2];										/**< Invoice Type 1: E-Fatura, 2 E-Arþiv EonlineInvoiceType enum*/
	uint8	OrderDate[7];									/**< Invoice Order Date */
	uint8	DespatchDate[7];								/**< Invoice Despatch Date */
	uint8	SellerIdentifier_OnlineInvoice[64 + 1];
	uint8	SellerIdentifier_OnlineArchive[64 + 1];
	uint16	rawDataLen;										/**< raw data length for payment application */
	uint8	rawData[512];									/**< rawData exchange between two application */

} ST_ONLINE_INVIOCE_INFO;

typedef struct
{
	uint32	StructSize;							/**< Sizeof this structure */
	uint8	BuyerName[64 + 1];					/**< Tax Free Customer Name */
	uint8	BuyerSurname[64 + 1];				/**< Tax Free Customer SurName */
	uint8	ID[24 + 1];							/**< Tax Free VKN No */
	uint8	IDDate[7];							/**< Tax Free Order Date */
	uint8	City[24 + 1];						/**< City */
	uint8	Country[24 + 1];					/**< Country */
	uint8	CountryCode[24 + 1];				/**< Country */
	uint8	OrderDate[7];						/**< Invoice Order Date */
	uint8	Ettn[36 + 1];						/**< Tax Free Ettn */
	uint8	Identifier[64 + 1];					/**< Tax Free Identifier */
} ST_TAXFREE_INFO;


/** Structure which is used to define an payment application info */
typedef struct
{
	uint32	StructSize;							/**< Sizeof this structure */
	uint8	name[24];							/**< Name of the payment application */
	uint8	index;								/**< index of the payment application */
	uint16  u16BKMId;							/**< BKM Id of the payment application */
	uint16  Status;								/**< Status of the payment application */
	uint16  Priority;							/**< Priority of the payment application */
	uint16  u16AppId;							/**< Telium Id of the payment application */
	uint16  AppType;							/**< Application Type */
	uint16  AppFlag;							/**< Application Flag */
} ST_PAYMENT_APPLICATION_INFO;

/** Structure which is used to define an payment application info */
typedef struct
{
	uint32				StructSize;							 /**< Sizeof this structure */
	uint8   			nbPaymentCount;						 /**< Number of supported payment type*/
	struct
	{
		char 			PaymentName[MAX_VAS_PAYMENT_NAME];	 /**< Payment Name*/
		uint32			PaymentType;						 /**< Payment Type*/
	} List[MAX_VAS_PAYMENT_COUNT];
} ST_VAS_PAYMENT_INFO;

/** Structure which is used to keep Multiple return codes */
typedef struct
{
	uint32 StructSize;						/**< Sizeof this structure */
	uint32 subCommand;						/**< subCommand which this result is produced for. If it is zero, then there is no subCommand and the data is produced automaticly by uApplication */
	uint32 retcode;							/**< subCommand return code (result of the subCommand on ECR) */
	uint32 tag;								/**< tag value provided by External Application (or one of GMP tag if it is automatic response from uApplcation) to mark the output data */
	uint16 indexOfSubCommand;				/**< order of the subCommand in the request message package. It is started by one and increased in each subcommand. if it is zero then there is no subCommand and the response is automatic from uApplication */
	uint16 lengthOfData;					/**< [IN] Maximum data buffer size [OUT] Length of the subCommand data returned*/
	uint8* pData;							/**< pointer to the returned data of the subCommand. It must be allocated by External Application. If it is NULL, data will not be copied even if returned from ECR */
} ST_MULTIPLE_RETURN_CODE;

typedef struct _ST_HANDLE_LIST
{
	uint32	StructSize;								/**< Size of this structure */
	uint64	Handle;									/**< Transaction Handle (it could be bacground handle or foreground handle.) */
	uint32	ReceiptAmount;							/**< Transaction Total Amount for given transactionhandle */
	uint8	szMasterOkcSicilNo[15 + 1];				/**< Master ECR Fiscal Number */
	uint8	szUserDefinedTranGroup[15 + 1];			/**< it is Group Name which is defined by merchant */
	uint8	szUserDefinedTranSubGroup[15 + 1];		/**< it is Sub Group Name which is defined by merchant */
	uint8	Status;									/**< Handle status */
} ST_HANDLE_LIST;

typedef struct _ST_INTERFACE_XML_DATA
{
	uint32		StructSize;						/**< Sizeof this structure */
	uint8		RetryCounter;
	uint8		IpRetryCount;
	uint32		AckTimeOut;
	uint32		CommTimeOut;
	uint32		InterCharacterTimeOut;

	char		PortName[260];
	int			BaudRate;
	int			ByteSize;
	int			fParity;
	int			Parity;
	int			StopBit;
	uint8		IsTcpConnection;
	char		IP[16];
	int			Port;
} ST_INTERFACE_XML_DATA;

typedef struct _ST_GLOBAL_XML_DATA
{
	uint32		StructSize;						/**< Sizeof this structure */
	uint8		IsCheckStructVersion;
	int			LogFileSize;
	char		LogPath[260];
} ST_GLOBAL_XML_DATA;

typedef struct _ST_INI_PARAM
{
	uint32	StructSize;						/**< Sizeof this structure */
	uint8	IsCheckStructVersion;
	uint8	RetryCounter;
	uint8	IpRetryCount;
	uint32	AckTimeOut;
	uint32	CommTimeOut;
	uint32	InterCharacterTimeOut;

	char	PortName[12];
	uint32	BaudRate;
	uint8	ByteSize;
	uint8	fParity;
	uint8	Parity;
	uint8	StopBit;
	uint8	IsTcpConnection;
	char	IP[20];
	uint32	Port;

	char	LogPath[260];
	int		LogFileSize;
	uint8	LogPrintToFileOpen;
	uint8	LogPrintToConsoleOpen;
	uint8	LogGeneralOpen;
	uint8	LogFunctionOpen;
	uint8	LogSecurityOpen;
	uint8	LogPrivateSecurityOpen ;
	uint8	LogCommOpen;
	uint8	LogExtDevOpen;
	uint8	LogJsonOpen;
	uint8	LogJsonDataOpen;
	uint8	LogGmp3TagsOpen;
	uint8	LogPrintSerialNumOpen;
	uint8	LogPrintDateOpen;
	uint8	LogPrintTimeOpen;
	uint8	LogPrintTypeOpen;
	uint8	LogPrintVersionOpen;
	uint8	LogPrintSourceFileOpen;
	uint8	LogPrintSourceLineOpen;
} ST_INI_PARAM;

/** Data & Time structure */
typedef struct _ST_DATE_TIME
{
	uint16 year;		/**< Year (1900..2100)*/
	uint8 month;		/**< Month (1..12)*/
	uint8 day;			/**< Day (1..31)*/
	uint8 hour;			/**< Hour (0..23)*/
	uint8 minute;		/**< Minute (0..59)*/
	uint8 second;		/**< Second (0..59)*/
} ST_DATE_TIME;

/** Data & Time structure */
typedef struct _ST_DATE_TIME_EX
{
	uint16		Year;			/**< Year (1900..2100)*/
	uint8		Month;			/**< Month (1..12)*/
	uint8		Day;			/**< Day (1..31)*/
	uint8		Hour;			/**< Hour (0..23)*/
	uint8		Minute;			/**< Minute (0..59)*/
	uint8		Second;			/**< Second (0..59)*/
	uint16		Milisecond;		/**< MiliSecond (0..999)*/
} ST_DATE_TIME_EX;

/** Set of flags to define invoice options */
typedef enum
{
	INVOICE_FLAG_IRSALIYE  = 0x00000001,
} EInvoiceFlags;

/** EConditionIds */
typedef enum
{
	GMP3_CONTITION_ID_PAYMENT_TOTAL_AMOUNT 			= 1,	/**< UINT32, Total Payment Amount value */
	GMP3_CONTITION_ID_IS_TICKET_PAYMENT_COMPLETED	,		/**< BOOLEAN, Is All Ticket Payment completed */
} EConditionIds;

/** EConditionTest */
typedef enum
{
	EIsEqual 				= 0,			/**< "==" */
	EIsBigger				,				/**< ">" */
	EIsEqualOrBigger		,				/**< "=>" */
	EIsSmaller				,				/**< "<" */
	EIsEqualOrSmaller		,				/**< "<=" */
} EConditionTest;

/** Structure which is used to define a conditional case */
typedef struct
{
	uint32			StructSize;						/**< Sizeof this structure */
	EConditionIds	id;								/**< One of EConditionIds */
	EConditionTest 	eTestFormule;					/**< One of EConditionTest */
	uint64			ui64TestValue;					/**< A value to test  */
	uint16			IfTrue_GOTO;					/**< One of EConditionGoto OR index on subCommands list */
	uint16			IfFalse_GOTO;					/**< One of EConditionGoto OR index on subCommands list */
} ST_CONDITIONAL_IF;


/** ETaxExceptionTypes */
typedef enum
{
	TAX_EXCEPTION_TYPE_MATRAHSIZ						= 1,	/**< The item amount is taxless and it will not be included in Fiscal Cumulatives. But it will be included in the payment amount. Exp; KatkiPayi */
	TAX_EXCEPTION_TYPE_TAXLESS_IN_TAXINCLUDED_AMOUNT	,		/**< The item total amount is tax included BUT the tax amount will be substracted from item amount in ticket totals. Exp; Diplomatic Sales.. */
} ETaxExceptionTypes;

/** EPersonelIdTypes */
typedef enum
{
	PERSONEL_ID_TYPE_TCK						= 1,			/**< Turkish republic identification no */
	PERSONEL_ID_TYPE_VKN						,				/**< Turkish Ministry Of Finance identification no (for both persons and companies)*/
	PERSONEL_ID_TYPE_PASSPORT					,				/**< Passport Number */
	PERSONEL_ID_TYPE_OTHER						= 0xFF			/**< Other types */
} EPersonelIdTypes;

/** ST_TAX_EXCEPTION_PARAMETERS */
typedef struct
{
	uint16	typeOfTaxException;									/**< One Of ETaxExceptionTypes */
	//uint16	subtypeOfTaxException;							/**< One Of ETypeOfMatrahsiz OR ETypeOfTaxless dependes on typeOfTaxException */
	uint16	typeOfId;											/**< One Of EPersonelIdTypes */
	uint8	id[24+1];											/**< Id which is defined in typeOfId. It may be mandotary for some tax exceptional transactions */
	struct
	{
		uint64	minimum;										/**< Minimum amount (item amount with tax) in which the tax exception will be valid. if not used, leave it 0 */
		uint64	maximum;										/**< Maximum amount (item amount with tax) in which the tax exception will be valid. if not used, leave it 0 */
	} itemAmount;												/**< itemAmount */
	struct
	{
		uint64	minimum;										/**< Minimum amount (ticket amount with tax) in which the tax exception will be valid. if not used, leave it 0 */
		uint64	maximum;										/**< Maximum amount (ticket amount with tax) in which the tax exception will be valid. if not used, leave it 0 */
	} ticketAmount;												/**< ticketAmount */
} ST_TAX_EXCEPTION_PARAMETERS;

/** ETransactionFlags */
typedef enum
{
	FLG_XTRANS_GMP3									= (1 << 1),
	FLG_XTRANS_FROM_FILE							= (1 << 2),
	FLG_XTRANS_BACKGROUND_PROCESS					= (1 << 3),
	FLG_XTRANS_FROM_MASTER_OKC						= (1 << 4),
	FLG_XTRANS_BANK_MONEY_COLLECTION_CASH			= (1 << 5),
	FLG_XTRANS_BANK_MONEY_COLLECTION				= (1 << 6),
	FLG_XTRANS_ONLY_BANK_REFUND_TICKET				= (1 << 7),
	FLG_XTRANS_TAXFREE_PARAMETERS_SET				= (1 << 8),
	FLG_XTRANS_TICKETTING_EXISTS					= (1 << 9),
	FLG_XTRANS_FULL_RCPT_CANCEL						= (1 << 12),
	FLG_XTRANS_NONEY_COLLECTION_EXISTS				= (1 << 13),
	FLG_XTRANS_TAXLESS_ITEM_EXISTS					= (1 << 14),
	FLG_XTRANS_INVOICE_PARAMETERS_SET				= (1 << 15),
	FLG_XTRANS_TICKET_HEADER_PRINTED				= (1 << 17),
	FLG_XTRANS_TICKET_TOTALS_AND_PAYMENTS_PRINTED	= (1 << 18),
	FLG_XTRANS_TICKET_FOOTER_BEFORE_MF_PRINTED		= (1 << 19),
	FLG_XTRANS_TICKET_FOOTER_MF_PRINTED				= (1 << 20),
	FLG_XTRANS_ONLINE_INVOICE_PARAMETERS_SET		= (1 << 21),
	FLG_XTRANS_EXTERNAL_EFT_POS						= (1 << 30),
	FLG_XTRANS_TICKET_SAVED_SUCCESSFULLY			= (1 << 31),
} ETransactionFlags;


#define MAX_TAXRATE_COUNT				8
#define MAX_DEPARTMENT_COUNT			12
#define MAX_EXCHANGE_COUNT				6
#define MAX_CASHIER_COUNT				4
#define MAX_CINEMA_DEPARTMENT_COUNT		8
#define MAX_EXCHANGE_PROFILE_COUNT		4

#define TAG_IKASA_OKC_ZREPORT_DEPARTMENT_RECORD				0x808B
#define TAG_IKASA_OKC_ZREPORT_EXCHANGE_RECORD				0x808C
#define TAG_IKASA_OKC_ZREPORT_CASHIER_RECORD				0x808D
#define TAG_IKASA_OKC_ZREPORT_TAX_RECORD					0x808E
#define TAG_IKASA_OKC_ZREPORT_MATRAHSIZ_RECORD				0x808F
#define TAG_IKASA_OKC_ZREPORT_BILET_RECORD					0x8091

#define TAG_IKASA_OKC_Z_SAYAC_NO                            0xF400
#define TAG_IKASA_OKC_FIS_SIRA_NO                           0xF401
#define TAG_IKASA_OKC_EKU_NO                                0xF402
#define TAG_IKASA_OKC_ZREPORT_DATE							0xA150
#define TAG_IKASA_OKC_ZREPORT_TIME							0xA151
#define TAG_IKASA_OKC_ZREPORT_INC_TOTAL_COUNT				0xA152
#define TAG_IKASA_OKC_ZREPORT_DEC_TOTAL_COUNT				0xA153
#define TAG_IKASA_OKC_ZREPORT_CORRECTION_TOTAL_COUNT		0xA155
#define TAG_IKASA_OKC_ZREPORT_FISCAL_RECEIPT_COUNT			0xA156
#define TAG_IKASA_OKC_ZREPORT_NON_FISCAL_RECEIPT_COUNT		0xA157
#define TAG_IKASA_OKC_ZREPORT_CUSTOMER_RECEIPT_COUNT		0xA158
#define TAG_IKASA_OKC_ZREPORT_SALE_RECEIPT_VOID_COUNT		0xA15A
#define TAG_IKASA_OKC_ZREPORT_INVOICE_SALE_COUNT			0xA15C
#define TAG_IKASA_OKC_ZREPORT_AVANS_COUNT		            0xA15D
#define TAG_IKASA_OKC_ZREPORT_DEPARTMENT_TOTAL_AMOUNT		0xA15E
#define TAG_IKASA_OKC_ZREPORT_DEPARTMENT_NAME				0xA15F
#define TAG_IKASA_OKC_ZREPORT_DEPARTMENT_TOTAL_QUANTITY		0xA160
#define TAG_IKASA_OKC_ZREPORT_INC_TOTAL_AMOUNT				0xA161
#define TAG_IKASA_OKC_ZREPORT_DEC_TOTAL_AMOUNT				0xA162
#define TAG_IKASA_OKC_ZREPORT_CASH_TOTAL_AMOUNT				0xA164
#define TAG_IKASA_OKC_ZREPORT_CREDIT_TOTAL_AMOUNT			0xA165
#define TAG_IKASA_OKC_ZREPORT_EXCHANGE_TOTAL_AMOUNT			0xA168
#define TAG_IKASA_OKC_ZREPORT_EXCHANGE_NAME					0xA169
#define TAG_IKASA_OKC_ZREPORT_EXCHANGE_TL_AMOUNT			0xA16A
#define TAG_IKASA_OKC_ZREPORT_SALE_VOID_TOTAL_AMOUNT		0xA16C
#define TAG_IKASA_OKC_ZREPORT_CORRECTION_TOTAL_AMOUNT		0xA16D
#define TAG_IKASA_OKC_ZREPORT_INVOICE_SALE_TOTAL_AMOUNT		0xA16E
#define TAG_IKASA_OKC_ZREPORT_SERVICE_MODE					0xA16F
#define TAG_IKASA_OKC_ZREPORT_CASHIER_TOTAL_AMOUNT			0xA170
#define TAG_IKASA_OKC_ZREPORT_TAX_TOTAL_AMOUNT				0xA171
#define TAG_IKASA_OKC_ZREPORT_TAX_RATES						0xA172
#define TAG_IKASA_OKC_ZREPORT_TAX_TOTAL_TAX					0xA173
#define TAG_IKASA_OKC_ZREPORT_DAILY_TOTAL_AMOUNT			0xA174
#define TAG_IKASA_OKC_ZREPORT_DAILY_TOTAL_TAX				0xA175
#define TAG_IKASA_OKC_ZREPORT_CUMULATIVE_TOTAL_AMOUNT		0xA176
#define TAG_IKASA_OKC_ZREPORT_CUMULATIVE_TOTAL_TAX			0xA177
#define TAG_IKASA_OKC_ZREPORT_CASHIER_NAME					0xA178
#define TAG_IKASA_OKC_ZRAPOR_YEMEK_CEKI_ADEDI				0xA179
#define TAG_IKASA_OKC_ZRAPOR_OTOPARK_GIRIS_SAYISI			0xA17A
#define TAG_IKASA_OKC_ZRAPOR_DIGER_ODEME_TOPLAMLARI			0xA17B
#define TAG_IKASA_OKC_ZRAPOR_YEMEK_CEKI_TOPLAM_AMOUNT		0xA17C
#define TAG_IKASA_OKC_ZRAPOR_OKC_SHA						0xA17D
#define TAG_IKASA_OKC_ZREPORT_CARI_HESAP_COUNT		        0xA17E
#define TAG_IKASA_OKC_ZREPORT_CASHIER_INDEX			        0xA17F

#define TAG_IKASA_OKC_ZREPORT_BILET_DEPT_INDEX				0xA18A
#define TAG_IKASA_OKC_ZREPORT_BILET_KOLTUK_SATIS_AMOUNT		0xA18B
#define TAG_IKASA_OKC_ZREPORT_BILET_KOLTUK_SATIS_KDV		0xA18C
#define TAG_IKASA_OKC_ZREPORT_BILET_KOLTUK_SATIS_COUNT		0xA18D
#define TAG_IKASA_OKC_ZREPORT_BILET_FATURALI_AMOUNT			0xA18E
#define TAG_IKASA_OKC_ZREPORT_BILET_FATURALI_KDV			0xA18F
#define TAG_IKASA_OKC_ZREPORT_BILET_FATURALI_COUNT			0xA190
#define TAG_IKASA_OKC_ZREPORT_BILET_IADE_AMOUNT				0xA191
#define TAG_IKASA_OKC_ZREPORT_BILET_IADE_KDV				0xA192
#define TAG_IKASA_OKC_ZREPORT_BILET_IADE_COUNT				0xA193
#define TAG_IKASA_OKC_ZREPORT_MATRAHSIZ_AMOUNT				0xA194
#define TAG_IKASA_OKC_ZREPORT_MATRAHSIZ_COUNT				0xA195
#define TAG_IKASA_OKC_ZREPORT_AVANS							0xA198
#define TAG_IKASA_OKC_ZREPORT_ODEME							0xA199
#define TAG_IKASA_OKC_ZREPORT_FISCAL_RAPOR_SAYISI			0xA19B
#define TAG_IKASA_OKC_ZREPORT_NONFISCAL_FIS_SAYISI			0xA19C
#define TAG_IKASA_OKC_ZREPORT_FATURALI_SATIS_SAYISI			0xA19D
#define TAG_IKASA_OKC_ZREPORT_MOBIL_ODEME_TUTAR				0xA19E
#define TAG_IKASA_OKC_ZREPORT_NAKIT_FATURALI_SATIS			0xA19F
#define TAG_IKASA_OKC_ZREPORT_TAX_REFUND					0xA1A0
#define TAG_IKASA_OKC_ZREPORT_KREDI_FATURALI_SATIS			0xA1A1
#define TAG_IKASA_OKC_ZREPORT_OTHER_PAYMENT_HEDIYE_CEKI		0xA1A2
#define TAG_IKASA_OKC_ZREPORT_OTHER_PAYMENT_IKRAM			0xA1A3
#define TAG_IKASA_OKC_ZREPORT_OTHER_PAYMENT_ODEMESIZ		0xA1A4
#define TAG_IKASA_OKC_ZREPORT_OTHER_PAYMENT_KAPORA			0xA1A5
#define TAG_IKASA_OKC_ZREPORT_OTHER_PAYMENT_PUAN			0xA1A6
#define TAG_IKASA_OKC_ZREPORT_OTHER_PAYMENT_GIDER_PUSULASI	0xA1A7
#define TAG_IKASA_OKC_ZREPORT_FATURA_TOPLAM					0xA1A8
#define TAG_IKASA_OKC_ZREPORT_E_FATURA_TOPLAM				0xA1A9
#define TAG_IKASA_OKC_ZREPORT_E_ARSIV_FATURA_TOPLAM			0xA1AA
#define TAG_IKASA_OKC_ZREPORT_OTHER_PAYMENT_BANKA_TRANSFERI	0XA1AB
#define TAG_IKASA_OKC_ZREPORT_OTHER_CEK						0XA1AC
#define TAG_IKASA_OKC_ZREPORT_OTHER_ACIK_HESAP				0XA1AD
#define TAG_IKASA_OKC_ZREPORT_CARI_HESAP_AMOUNT				0xA1AE
#define TAG_IKASA_OKC_ZREPORT_DIGER_ODEME_FATURALI_SATIS	0xA1AF

// AYLIK RAPOR
#define TAG_IKASA_OKC_DM_REPORT_RECORD										0xD001
#define TAG_IKASA_OKC_DM_REPORT_VERSION										0xD002
#define TAG_IKASA_OKC_DM_REPORT_REPORT_TYPE									0xD003
#define TAG_IKASA_OKC_DM_REPORT_CREATE_DATE									0xD004
#define TAG_IKASA_OKC_DM_REPORT_CREATE_TIME									0xD005
#define TAG_IKASA_OKC_DM_REPORT_MONTHLY_NO									0xD006
#define TAG_IKASA_OKC_DM_REPORT_DAILY_NO									0xD007
#define TAG_IKASA_OKC_DM_REPORT_START_DATE									0xD008
#define TAG_IKASA_OKC_DM_REPORT_END_DATE									0xD009
#define TAG_IKASA_OKC_DM_REPORT_EJU_NO										0xD00A
#define TAG_IKASA_OKC_DM_REPORT_VAT_NUMBER									0xD00B

#define TAG_IKASA_OKC_DM_REPORT_VAT_RECORD_COUNT 							0xD010
#define TAG_IKASA_OKC_DM_REPORT_VAT_RECORD									0xD011
#define TAG_IKASA_OKC_DM_REPORT_VAT_RECORD_SALE_AMOUNT						0xD012
#define TAG_IKASA_OKC_DM_REPORT_VAT_RECORD_TAX_AMOUNT						0xD013
#define TAG_IKASA_OKC_DM_REPORT_VAT_RECORD_TAX_RATE							0xD014

#define TAG_IKASA_OKC_DM_REPORT_TOTAL_TAX_AMOUNT 							0xD020
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_SALE_AMOUNT							0xD021
#define TAG_IKASA_OKC_DM_REPORT_CALCULATED_TAX_AMOUNT						0xD022
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_DICREASE_AMOUNT						0xD023
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_INCREASE_AMOUNT						0xD024
#define TAG_IKASA_OKC_DM_REPORT_CUMULATIVE_TOTAL_AMOUNT						0xD025
#define TAG_IKASA_OKC_DM_REPORT_CUMULATIVE_TOTAL_TAX						0xD026
#define TAG_IKASA_OKC_DM_REPORT_VOID_RECEIPT_COUNT							0xD027
#define TAG_IKASA_OKC_DM_REPORT_VOID_RECEIPT_TOTAL_AMOUNT					0xD028

#define TAG_IKASA_OKC_DM_REPORT_ECR_RECEIPT_TOTAL_SALE						0xD030
#define TAG_IKASA_OKC_DM_REPORT_ECR_RECEIPT_TOTAL_TAX						0xD031
#define TAG_IKASA_OKC_DM_REPORT_ECR_RECEIPT_TOTAL_COUNT						0xD032

#define TAG_IKASA_OKC_DM_REPORT_INVOICE_TOTAL_SALE							0xD033
#define TAG_IKASA_OKC_DM_REPORT_INVOICE_TOTAL_TAX							0xD034
#define TAG_IKASA_OKC_DM_REPORT_INVOICE_TOTAL_COUNT							0xD035

#define TAG_IKASA_OKC_DM_REPORT_SMM_TOTAL_SALE								0xD036
#define TAG_IKASA_OKC_DM_REPORT_SMM_TOTAL_TAX								0xD037
#define TAG_IKASA_OKC_DM_REPORT_SMM_TOTAL_COUNT								0xD038

#define TAG_IKASA_OKC_DM_REPORT_MM_TOTAL_SALE								0xD039
#define TAG_IKASA_OKC_DM_REPORT_MM_TOTAL_TAX								0xD03A
#define TAG_IKASA_OKC_DM_REPORT_MM_TOTAL_COUNT								0xD03B

#define TAG_IKASA_OKC_DM_REPORT_EXPENSE_RECEIPT_TOTAL_SALE					0xD03C
#define TAG_IKASA_OKC_DM_REPORT_EXPENSE_RECEIPT_TOTAL_TAX					0xD03D
#define TAG_IKASA_OKC_DM_REPORT_EXPENSE_RECEIPT_TOTAL_COUNT					0xD03E

#define TAG_IKASA_OKC_DM_REPORT_TICKET_TOTAL_SALE							0xD03F
#define TAG_IKASA_OKC_DM_REPORT_TICKET_TOTAL_TAX							0xD040
#define TAG_IKASA_OKC_DM_REPORT_TICKET_TOTAL_COUNT							0xD041

#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_INVOICE_TOTAL_SALE				0xD050
#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_INVOICE_TOTAL_COUNT			0xD051

#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_FOOD_CARD_TOTAL_SALE			0xD052
#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_FOOD_CARD_TOTAL_COUNT			0xD053

#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_ADVANCE_TOTAL_SALE				0xD054
#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_ADVANCE_TOTAL_COUNT			0xD055

#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_INVOICE_COLLECTION_TOTAL_SALE	0xD056
#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_INVOICE_COLLECTION_TOTAL_COUNT	0xD057

#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_CURRENT_ACCOUNT_TOTAL_SALE		0xD058
#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_CURRENT_ACCOUNT_TOTAL_COUNT	0xD059

#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_OTHER_TOTAL_SALE				0xD05A
#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_OTHER_TOTAL_COUNT				0xD05B

#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_PARKING_TICKET_COUNT			0xD05C

#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_GENERAL_TOTAL_SALE				0xD05D
#define TAG_IKASA_OKC_DM_REPORT_INFO_RECEIPT_GENERAL_TOTAL_COUNT			0xD05E

#define TAG_IKASA_OKC_DM_REPORT_ECR_RECEIPT_FOOD_CARD_TOTAL_SALE			0xD05F
#define TAG_IKASA_OKC_DM_REPORT_ECR_RECEIPT_INVOICE_COLLECTION_TOTAL_SALE	0xD060
#define TAG_IKASA_OKC_DM_REPORT_ECR_RECEIPT_OTHER_TAXLESS_TOTAL_SALE		0xD061

#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_CASH							0xD070
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_CREDIT_CARD					0xD071
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_VIRTUAL_POS					0xD072
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_GIFT_CARD						0xD073
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_EFT_AND_BANK_TRANSFER			0xD074
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_E_MONEY_AND_FAST_PAY			0xD075
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_CHECK_AND_BILL				0xD076
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_OPENED_ACCOUNT				0xD077
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_FOOD_CARD						0xD078
#define TAG_IKASA_OKC_DM_REPORT_TOTAL_PAYMENT_OTHER							0xD079

/** VAS TYPES*/
enum
{
	TLV_OKC_ASSIST_VAS_TYPE_ADISYON     = 0x0001,   // Adisyon
	TLV_OKC_ASSIST_VAS_TYPE_IN_FLIGHT,              // INFLIGHT -->
	TLV_OKC_ASSIST_VAS_TYPE_INGENICO,               // ICIRO, FIND MY KASA
	TLV_OKC_ASSIST_VAS_TYPE_OTHER,                  // OTHER
	TLV_OKC_ASSIST_VAS_TYPE_AKTIFNOKTA,             // AKTIF NOKTA
	TLV_OKC_ASSIST_VAS_TYPE_MOBIL_ODEME,            // MOBIL ODEME
	TLV_OKC_ASSIST_VAS_TYPE_OTOPARK,             	// OTOPARK
	TLV_OKC_ASSIST_VAS_TYPE_YEMEKCEKI,             	// YEMEK KARTI
	TLV_OKC_ASSIST_VAS_TYPE_LOYALTY,             	// SADAKAT UYGULAMASI
	TLV_OKC_ASSIST_VAS_TYPE_PAYMENT,                // ODEME UYGULAMASI
	TLV_OKC_ASSIST_VAS_TYPE_ALL         = 0x0100    // ALL
};

typedef struct _ST_Z_REPORT
{
	uint32			StructSize;								/**< Sizeof this structure */
	uint8			Date[3]; 								/**< BCD(3) YYAAGG	, Date of the Z Report */
	uint8			Time[2]; 								/**< BCD(2) SSDD    , Time of the Z Report */
	uint32			FNo;									/**< uint32 012345	, F No of the Ticket */
	uint32			ZNo; 									/**< uint32 9999    , Z No of the ticket */
	uint32			EJNo; 									/**< uint32 9999    , EJ No of the ticket */

	struct													/**< Counters based data*/
	{
		uint32 increaments;									/**< uint32 999999  , Total number of increases */
		uint32 decreases; 									/**< uint32 999999  , Total number of decreases */
		uint32 corrections; 								/**< uint32 999999  , Total number of corrections */
		uint32 fiscalReceipts; 								/**< uint32 999999  , Total number of Fiscal Tickets */
		uint32 nonfiscalReceipts; 							/**< uint32 999999  , Total number of non Fiscal Tickets */
		uint32 customerReceipts; 							/**< uint32 999999	, Total number of Tickets */
		uint32 voidReceipts; 								/**< uint32 999999 	, Total number of Void Tickets */
		uint32 invoiceSaleReceipts; 						/**< uint32 999999 	, Total number of Invoice Tickets */
		uint32 yemekcekiReceipts; 							/**< uint32 999999 	, Total number of YemekCeki Tickets */
		uint32 carParkingEntryReceipts;						/**< uint32 999999 	, Total number of CarParking Tickets */
		uint32 fiscalReportReceipts;						/**< uint32 999999  , Total number of FiscalReport Ticket counts */
		uint32 tasnifDisiReceipts; 							/**< uint32 999999  , Total number of info Ticket counts */
		uint32 invoiceReceipts; 							/**< uint32 999999  , Total number of Invoice Ticket counts */
		uint32 matrahsizReceipts; 							/**< uint32 999999  , Total number of Matrahsiz Ticket counts */
		uint32 serviceModeEntry; 							/**< uint32 999999  , Total number of entries into Service Menu of ECR */
		uint32 advanceReceipts;	 							/**< uint32 999999  , Total number of Advance transactions */
		uint32 openAccountReceipts;							/**< uint32 999999  , Total number of Open Account transaction */
	} countOf;

	uint64 IncTotAmount; 									/**< uint64 999999999999 , Total amount of increaments */
	uint64 DecTotAmount;									/**< uint64 999999999999 , Total amount of discounts */
	uint64 SaleVoidTotAmount; 								/**< uint64 999999999999 , Total amount of Voids */
	uint64 CorrectionTotAmount; 							/**< uint64 999999999999 , Total amount of Corrections */
	uint64 InvoiceSaleTotAmount; 							/**< uint64 999999999999 , Total amount of Invoices */
	uint64 FoodRcptTotAmount;								/**< uint64 999999999999 , Total amount of YemekCeki Tickets */
	uint64 DailyTotAmount; 									/**< uint64 999999999999 , Total amount of Tickets within this Z Repord period*/
	uint64 DailyTotTax; 									/**< uint64 999999999999 , Total amount of Taxes within this Z Repord period */
	uint64 CumulativeTotAmount; 							/**< uint64 999999999999 , Total cumulative amount of Tickets in ECR when the Z Repord was produced (not now, Z Report date date) */
	uint64 CumulativeTotTax; 								/**< uint64 999999999999 , Total cumulative amount of Taxes in ECR when the Z Repord was produced (not now, Z Report date date) */
	uint64 AvansTotalAmount;								/**< uint64 999999999999 , Total Amount of AVANS transactions within this Z report period */
	uint64 OdemeTotalAmount;								/**< uint64 999999999999 , Total Amount of ODEME (PAYMENT) transactions within this Z report period */
	uint64 TaxRefundTotalAmount;							/**< uint64 999999999999 , Total Amount of TAX FREE REFUND transactions within this Z report period */
	uint64 MatrahsizTotalAmount;							/**< uint64 999999999999 , Total Amount of MATRAHSIZ transactions within this Z report period */
	uint64 OpenAccountTotalAmount;							/**< uint64 999999999999 , Total Amount of Open Account transaction */

	struct													/**< Department based data*/
	{
		uint64 totalAmount;									/**< uint64 999999999999 	, Total amount of sales in this department */
		uint64 totalQuantity;								/**< uint64 999999999999 	, Total quantitiy of sales in this department */
		uint8 name[24+1];									/**< uint8[24+1] Name of the department */
	} department[MAX_DEPARTMENT_COUNT];

	struct													/**< Exchange currency based data*/
	{
		uint64 totalAmount;									/**< uint64 999999999999 	, Total amount of exchange currencies im original currency */
		uint64 totalAmountInTL;								/**< uint64 999999999999 	, Total amount of exchange currencies in TL */
		uint8 name[12+1];									/**< uint8[12+1] Name of the exchange currency */
	} exchange[MAX_EXCHANGE_COUNT];

	struct													/**< Exchange currency based data*/
	{
		uint64 totalAmount;									/**< uint64 999999999999 	, Total Ticket Amount of this tax rate */
		uint64 totalTax;									/**< uint64 999999999999 	, Total Tax Amount of this tax rate  */
		uint16 taxRate;										/**< uint16 Rate of the tax, it is 1800 for %18 */
	} tax[MAX_TAXRATE_COUNT];

	struct													/**< Exchange currency based data*/
	{
		uint64 totalAmount;									/**< uint64 999999999999 	, Total Amount of this cashier */
		uint8  name[11+1];									/**< uint8 name of the cashier */
	} cashier[MAX_CASHIER_COUNT];

	struct													/**< Invoice based data*/
	{
		uint64 TotalAmount;									/**< uint64 999999999999 	, Total Amount of types of invoices */
		uint64 classicTotalAmount;							/**< uint64 999999999999 	, Total Amount of Classic paper invoices */
		uint64 e_invoiceTotalAmount;						/**< uint64 999999999999 	, Total Amount of E Invoice invoices (E Fatura)*/
		uint64 e_archiveTotalAmount;						/**< uint64 999999999999 	, Total Amount of E Archive invoices (E Arsiv)*/

		uint64 creditTotalAmount;							/**< uint64 999999999999 	, Total Amount of invoices payed with Credit */
		uint64 cashTotalAmount;								/**< uint64 999999999999 	, Total Amount of invoices payed with Cash */
	} invoice;

	struct
	{
		uint64 cashTotal; 										/**< uint64 999999999999 , Total amount of Cash Payments */
		uint64 creditTotal;										/**< uint64 999999999999 , Total amount of Credit Payments */
		uint64 otherTotal;										/**< uint64 999999999999 , Total amount of Other type Payments */

		struct
		{
			uint64 mobil;
			uint64 hediyeCeki;
			uint64 ikram;
			uint64 odemesiz;
			uint64 kapora;
			uint64 puan;
			uint64 giderPusulasi;
			uint64 cek;
			uint64 bankaTransfer;
			uint64 acikHesap;
		} other;
	} payment;

	struct
	{
		struct
		{
			struct
			{
				uint16	KoltukSayisi;						/**< uint16 9999 , Total unit count */
				uint16	reserved;							/**< uint16 9999 , Reserved */
				uint64	totalAmount; 						/**< uint64 999999999999 , Total amount of sales in this category */
				uint64	totalTax; 							/**< uint64 999999999999 , Total amount of taxes in this category */
			} sale;
			struct
			{
				uint16	KoltukSayisi;						/**< uint16 9999 , Total unit count */
				uint16	reserved;							/**< uint16 9999 , Reserved */
				uint64	totalAmount; 						/**< uint64 999999999999 , Total amount of sales in this category */
				uint64	totalTax; 							/**< uint64 999999999999 , Total amount of taxes in this category */
			} refund;
			struct
			{
				uint16	KoltukSayisi;						/**< uint16 9999 , Total unit count */
				uint16	reserved;							/**< uint16 9999 , Reserved */
				uint64	totalAmount; 						/**< uint64 999999999999 , Total amount of sales in this category */
				uint64	totalTax; 							/**< uint64 999999999999 , Total amount of taxes in this category */
			} invoiceSale;
		} cinema[MAX_CINEMA_DEPARTMENT_COUNT];				/**<  [YERLÝ,YABANCI]x[TAM,ÖGRENCÝ,ÝNDÝRÝMLÝ,DAVETÝYE] */
	} sectorData;
} ST_Z_REPORT;


typedef  struct _ST_BilgiFisi
{
	uint32 Adedi;
	uint64 ToplamTutari;
} ST_BilgiFisi;

typedef	struct _ST_OKC_BelgeTipi
{
	uint32 ToplamAdedi;
	uint64 KDV_Toplami;
	uint64 SatisTutariToplami;
} ST_OKC_BelgeTipi;

typedef struct _ST_DM_REPORT
{
	uint32 StructSize;								/**< Sizeof this structure */
	uint16 Versiyon;
	char IsyeriVKN[24+1];
	char RaporUretilmeTarihi[8+1];
	char RaporUretilmeSaati[6+1];
	uint32 AylikRaporNo;
	uint32 GunlukRaporNo;
	char RaporDonemiBaslangicTarihi[8+1];
	char RaporDonemiBitisTarihi[8+1];
	uint32 KDV_GrupAdedi;
	struct
	{
		uint64 VergiToplamTutari;
		uint32 VergiOrani;
		uint64 VergiToplamKDV;
	} stKDV_Grubu[MAX_TAXRATE_COUNT];

	uint64 ToplamKDV_Tutari;
	uint64 ToplamSatisTutari;
	uint64 BeyanEdilecekKDV_Tutari;
	uint64 IndirimToplamTutari;
	uint64 ArtirimToplamTutari;
	uint64 KumulatifToplamKDV_Tutari;
	uint64 KumulatifToplamSatisTutari;
	uint32 IptalEdilenBelgeAdedi;
	uint64 IptalEdilenBelgeToplamTutari;

	struct
	{
		ST_OKC_BelgeTipi	stOKCFisi;
		struct
		{
			ST_BilgiFisi	stFaturaBilgi;
			ST_BilgiFisi	stYemekKarti;
			ST_BilgiFisi	stAvans;
			ST_BilgiFisi	stFaturaTahsilati;
			ST_BilgiFisi	stCariHesap;
			ST_BilgiFisi	stDiger;
			ST_BilgiFisi	stGenelToplam;
			uint32 			OtoparkFisiAdedi;
			uint64			MaliFisYemekKartiTutari;
			uint64			MaliFisFaturaTahsilatTutari;
			uint64			MaliFisDigerMatrahsiz;
		} stBilgiFisleri;
		struct
		{
			ST_OKC_BelgeTipi	stFatura;
			ST_OKC_BelgeTipi	stSMM;
			ST_OKC_BelgeTipi	stGiderPusulasi;
			ST_OKC_BelgeTipi	stMM;
			ST_OKC_BelgeTipi	stBilet;
		} stDiger;
	} stOKC_Belge;

	struct
	{
		uint64 Nakit;
		uint64 KrediKarti;
		uint64 SanalPos;
		uint64 HediyeKarti;
		uint64 HavaleEFT;
		uint64 E_ParaHizliPara;
		uint64 SenetCek;
		uint64 KrediliVadeliAcikHesap;
		uint64 YemekKarti;
		uint64 Diger;
	} stOdemeToplami;

	uint32 EkuNo;
} ST_DM_REPORT;

#ifndef EXTERN_C_BEGIN
#if __cplusplus
#define EXTERN_C_FUNC		extern "C"
#define EXTERN_C_BEGIN		extern "C" {
#define EXTERN_C_END		}
#else /*__cplusplus*/
#define EXTERN_C_FUNC		extern
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif /*__cplusplus*/
#endif /*EXTERN_C_BEGIN*/

#ifdef WIN32
#define GMP_EXTERN				EXTERN_C_FUNC __declspec(dllexport)
#define GMP_CALL_TYPE			__cdecl

#elif defined(__TELIUM2__) || defined(__TELIUM3__)

#define GMP_EXTERN				EXTERN_C_FUNC
#define GMP_CALL_TYPE
#else /*WIN32 - defined(__TELIUM2__) - defined(__TELIUM3__)*/
#define GMP_EXTERN				EXTERN_C_FUNC __attribute__((visibility("default")))
#define GMP_CALL_TYPE			/*__attribute__((cdecl))*/
#endif /*WIN32 - defined(__TELIUM2__) - defined(__TELIUM3__)*/


#if __cplusplus
#define DEFAULT_PARAM_TIMEOUT_ECHO					= TIMEOUT_ECHO
#define DEFAULT_PARAM_TIMEOUT_DEFAULT				= TIMEOUT_DEFAULT
#define DEFAULT_PARAM_TIMEOUT_PRINT_MF				= TIMEOUT_PRINT_MF
#define DEFAULT_PARAM_TIMEOUT_CARD_TRANSACTIONS		= TIMEOUT_CARD_TRANSACTIONS
#else /*__cplusplus*/
#define DEFAULT_PARAM_TIMEOUT_ECHO
#define DEFAULT_PARAM_TIMEOUT_DEFAULT
#define DEFAULT_PARAM_TIMEOUT_PRINT_MF
#define DEFAULT_PARAM_TIMEOUT_CARD_TRANSACTIONS
#endif /*__cplusplus*/

typedef uint32 HINT;
typedef uint64 HTRX;

GMP_EXTERN uint32 GenerateUniqueID(char *szTransUniqueID);

GMP_EXTERN uint32 GMP_CALL_TYPE SetXmlFilePath(const char *szPath);
GMP_EXTERN char *GMP_CALL_TYPE GetXmlFilePath(char *szPath);
GMP_EXTERN uint32 GMP_CALL_TYPE SetIniParameters(ST_INI_PARAM *pstIniParameters);
GMP_EXTERN uint32 GMP_CALL_TYPE GetIniParameters(ST_INI_PARAM *pstIniParameters);
GMP_EXTERN void GMP_CALL_TYPE SetJavaClassPath(char *Path);

#define SetIniFilePath(szPath)			SetXmlFilePath(szPath)
#define GetIniFilePath(szPath)			GetXmlFilePath(szPath)

GMP_EXTERN uint32 GMP_CALL_TYPE FP3_CreateInterface(HINT *phInt, const char *szID, uint8 IsDefault, ST_INTERFACE_XML_DATA *pstInterfaceXmlData);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetInterfaceHandleList(HINT *phInt, uint32 Max);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetInterfaceID(HINT hInt, char *szID, uint32 Max);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetInterfaceHandleByID(HINT *phInt, const char *szID);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_RemoveInterfaceByID(const char *szID);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_RemoveInterfaceByHandle(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetInterfaceXmlDataByID(const char *szID, ST_INTERFACE_XML_DATA *pstInterfaceXmlData);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetInterfaceXmlDataByHandle(HINT hInt, ST_INTERFACE_XML_DATA *pstInterfaceXmlData);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_UpdateInterfaceXmlDataByID(const char *szID, ST_INTERFACE_XML_DATA *pstInterfaceXmlData);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_UpdateInterfaceXmlDataByHandle(HINT hInt, ST_INTERFACE_XML_DATA *pstInterfaceXmlData);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetDefaultInterfaceByID(const char *szID);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetInterfaceDefaultByHandle(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetGlobalXmlData(ST_GLOBAL_XML_DATA *pstGlobalXmlData);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_UpdateGlobalXmlData(ST_GLOBAL_XML_DATA *pstGlobalXmlData);

GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_CreateInterface(HINT *phInt, char *szID, uint8 IsDefault, char* szJsonXmlData);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetInterfaceXmlDataByID(const char *szID, char* pstInterfaceXmlData, int JsonMaxLen);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetInterfaceXmlDataByHandle(HINT hInt, char* pstInterfaceXmlData, int JsonMaxLen);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_UpdateInterfaceXmlDataByID(char *szID, char* pstInterfaceXmlData);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_UpdateInterfaceXmlDataByHandle(HINT hInt, char* pstInterfaceXmlData);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetGlobalXmlData(char* pstGlobalXmlData, int JsonMaxLen);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_UpdateGlobalXmlData(char* pstGlobalXmlData);

GMP_EXTERN uint16	GMP_CALL_TYPE gmpReadTLVlen(uint16 *plen, uint8 *ptr);
GMP_EXTERN uint16	GMP_CALL_TYPE gmpReadTLVtag(uint32 *ptag, uint8 *ptr);
GMP_EXTERN uint16	GMP_CALL_TYPE gmpTlvSetLen(uint8* pmsg, uint16 TlvLen);
GMP_EXTERN uint16	GMP_CALL_TYPE gmpSetTLV(uint8 *pmsg, uint32 Tag, uint8 *pdata, uint16 dataLen);
GMP_EXTERN uint16	GMP_CALL_TYPE gmpSetTLVbcd(uint8 *pmsg, uint32 Tag, uint32 data, uint16 bcdLen);
GMP_EXTERN uint16	GMP_CALL_TYPE gmpSetTLVbcd_64(uint8 *pmsg, uint32 Tag, uint64 data, uint16 bcdLen);
GMP_EXTERN uint16	GMP_CALL_TYPE gmpReadTlv(uint8 *Source, uint32 *Tag, uint16 *Len, uint8 **Value);
GMP_EXTERN int		GMP_CALL_TYPE gmpSearchTLV(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint8* pdata, uint16 dataMaxLe);
GMP_EXTERN int		GMP_CALL_TYPE gmpSearchTLVbcd_8(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint8* pdata, uint8 bcdLen);
GMP_EXTERN int		GMP_CALL_TYPE gmpSearchTLVbcd_16(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint16* pdata, uint8 bcdLen);
GMP_EXTERN int		GMP_CALL_TYPE gmpSearchTLVbcd_32(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint32* pdata, uint8 bcdLen);
GMP_EXTERN int		GMP_CALL_TYPE gmpSearchTLVbcd_64(uint32 Tag, int ocurience, uint8* recvbuffer, uint16 recvbufferLen, uint64* pdata, uint8 bcdLen);
#define gmpSearchTLVbcd		gmpSearchTLVbcd_32

GMP_EXTERN uint16	GMP_CALL_TYPE gmpSetTLV_HL(uint8* pmsg, uint32 pmsgLen, uint32 Tag, uint8* pdata, uint16 dataLen);  //HighLevel
GMP_EXTERN uint16	GMP_CALL_TYPE gmpReadTLVtag_HL(uint32 *ptag, uint8* ptr, uint32 startIndex);
GMP_EXTERN uint16	GMP_CALL_TYPE gmpReadTLVlen_HL(uint16 *plen, uint8 *ptr, uint32 startIndex);

GMP_EXTERN uint32	GMP_CALL_TYPE FileSystem_FileRead(char *FileName, uint32 offset, uint32 whence, uint8 *buffer, uint16 maxLen, uint16 *pReadLen);
GMP_EXTERN uint32	GMP_CALL_TYPE FileSystem_FileRemove(char *FileName);
GMP_EXTERN uint32	GMP_CALL_TYPE FileSystem_FileRename(char *FileNameOld, char *FileNameNew);
GMP_EXTERN uint32	GMP_CALL_TYPE FileSystem_FileWrite(char *FileName, uint32 offset, uint32 whence, uint8 *buffer, uint16 len);
GMP_EXTERN uint32	GMP_CALL_TYPE FileSystem_DirChange(char *DirName);
GMP_EXTERN uint32	GMP_CALL_TYPE FileSystem_DirListFiles(char *DirName, ST_FILE stFile[], uint16 maxNumberOfFiles, uint16 *pNumberOfFiles);

GMP_EXTERN uint32	GMP_CALL_TYPE Database_GetHandle(void);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_FreeStructure(ST_DATABASE_RESULT *pst);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_Open(char *name);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_Close(void);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_Execute(char *sqlWord, ST_DATABASE_RESULT *pstDatabaseResult);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_Query(char *sqlWord, uint16 *pnumberOfColomns);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_QueryReadLine(uint16 numberOfLinesRequested, uint16 numberOfColomnsRequested, ST_DATABASE_RESULT *pstDatabaseResult);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_QueryColomnCaptions(ST_DATABASE_RESULT *pstDatabaseResult);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_QueryReset(void);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_QueryFinish(void);
GMP_EXTERN uint32	GMP_CALL_TYPE Database_InitPluDatabase(void);

typedef int (*GMP_CallbackSend)(uint8 *buffer, int len);

GMP_EXTERN void GMP_CALL_TYPE GMP_SetCallbackFunction(GMP_CallbackSend func);  //cengiz sil : tamamlanacak !!!
GMP_EXTERN uint32 GMP_CALL_TYPE GMP_GetDllVersion(char* version);
GMP_EXTERN uint32 GMP_CALL_TYPE GMP_StartPairingInit(ST_GMP_PAIR *pGMPPair, ST_GMP_PAIR_RESP *pGMPPairResp);
GMP_EXTERN uint32 GMP_CALL_TYPE ExchangeEcrMessage(int msgType, char *In_sendDataBuff, unsigned int dataLen, char * Out_receiveDataBuff, uint32 *pOut_dataLen, int timeoutInMiliseconds);

#if !defined(__TELIUM2__) && !defined(__TELIUM3__)
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetTaxRates(uint8* pNumberOfTotalRecords, uint8* pNumberOfTotalRecordsReceived, char* szJsonTaxRates, char* szJsonTaxRate_Out, int JsonTaxRateLen_Out, uint8 NumberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetDepartments(uint8* pNumberOfTotalDepartments, uint8* pNumberOfTotalDepartmentsReceived, char* szJsonDepartments, char* szJsonDepartments_Out, int JsonDepartmentsLen_Out, uint8 NumberOfDepartmentRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetExchangeTable(uint8* pNumberOfTotalRecords, uint8* pNumberOfTotalRecordsReceived, char* szJsonExchanges, char* szJsonExchanges_Out, int JsonExchangesLen_Out, uint8 NumberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_SetDepartments(char* szJsonDepartments, char* szJsonDepartments_Out, int JsonDepartmentsLen_Out, uint8 NumberOfDepartmentRequested, char* szPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetTicket(char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Payment(char* szJsonPaymentRequest, char* JsonPaymentRequest_Out, int JsonPaymentRequestLen_Out, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Plus(int Amount, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem , int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Plus_Ex(int Amount, char *szText, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem , int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Minus(int Amount, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Minus_Ex(int Amount, char *szText, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Inc(uint8 Rate, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem, uint32* pChangedAmount, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Inc_Ex(uint8 Rate, char *szText, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem, uint32* pChangedAmount, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Dec(uint8 Rate, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem, uint32* pChangedAmount, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Dec_Ex(uint8 Rate, char *szText, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem, uint32* pChangedAmount, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_VoidAll(char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Pretotal(char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Matrahsiz(char* szTck, uint16 SubtypeOfTaxException, int MatrahsizAmount, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_VoidPayment(uint16 Index, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_VoidItem(uint16 Index, uint64 ItemCount, uint8 ItemCountPrecision, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_ItemSale(char* szJsonItem, char* szJsonItem_Out, int szJsonItemLen_Out, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_PrintUserMessage(char* szJsonUserMessage, char* szJsonUserMessage_Out, int JsonUserMessageLen_Out, uint16 NumberOfMessage, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_PrintUserMessage_Ex(char* szJsonUserMessage, char* szJsonUserMessage_Out, int JsonUserMessageLen_Out, uint16 NumberOfMessage, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionGetUniqueIdList(char* szJsonUniqueIdList, char* szJsonUniqueIdList_Out, int JsonUniqueIdListLen_Out, uint16 MaxNumberOfitems, uint16 IndexOfitemsToStart, uint16* pTotalNumberOfItems, uint16* pNumberOfItemsInThis,  int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionReadCard(uint32 CardReaderTypes, char* szJsonCardInfo, char* szJsonCardInfo_Out, int JsonCardInfoLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_KasaPayment(int Amount, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_KasaAvans(int Amount, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetCashierTable(uint8* pNumberOfTotalRecords, uint8* pNumberOfTotalRecordsReceived, char* szJsonCashier, char * szJsonCashier_Out, int JsonCashierLen_Out, uint8 NumberOfRecordsRequested, uint16* pActiveCashier);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_parse_FiscalPrinter(char* szJsonReturnCodes_Out, int JsonReturnCodesLen_Out, uint16* pNumberOfreturnCodes, uint32 RecvMsgId, uint8* pRecvFullBuffer, uint16 RecvFullLen, char* szJsonTicket_Out, int JsonTicketLen_Out, int MaxNumberOfReturnCode, int MaxReturnCodeDataLen);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_parse_GetEcr(char* szJsonReturnCodes_Out, int JsonReturnCodesLen_Out,  uint16* pNumberOfreturnCodes,  uint32 RecvMsgId,  uint8* pRecvFullBuffer, uint16 RecvFullLen, int MaxNumberOfReturnCode, int MaxReturnCodeDataLen);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_Echo(char* szJsonEcho_Out, int szJsonEchoLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_GMP_StartPairingInit(char* szJsonPair, char * szJsonPairResp_Out, int JsonPairRespLen_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetPaymentApplicationInfo(uint8* pNumberOfTotalRecords, uint8* pNumberOfTotalRecordsReceived, char* szJsonPaymentApplicationInfo, char* szJsonPaymentApplicationInfo_Out, int JsonPaymentApplicationInfoLen_Out, uint8 NumberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_SetInvoice(char* szJsonInvoiceInfo, char* szJsonInvoiceInfo_Out, int szJsonInvoiceInfoLen_Out, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionReports(uint32 FunctionFlags, char* szJsonFunctionParameters, char * szJsonFunctionParameters_Out, int JsonFunctionParametersLen_Out, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionReadZReport(char* szJsonFunctionParameters, char* szJsonZReport_Out, int JsonZReportLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_MultipleCommand(char* szJsonReturnCodes_Out, int JsonReturnCodesLen_Out, uint16* pNumberOfReturnCodes, uint8* pSendBuffer, uint16 SendBufferLen, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN int GMP_CALL_TYPE Json_prepare_Payment(uint8* Buffer, int MaxSize, char* szJsonPaymentRequest, char * szJsonPaymentRequest_Out, int szJsonPaymentRequestLen_Out);
GMP_EXTERN int GMP_CALL_TYPE Json_prepare_ItemSale(uint8* Buffer, int MaxSize, char* szJsonItem, char * szJsonItem_Out, int szJsonItemLen_Out);
GMP_EXTERN int GMP_CALL_TYPE Json_prepare_SetInvoice(uint8* Buffer, int MaxSize, char* szJsonInvoiceInfo, char* szJsonInvoiceInfo_Out, int JsonInvoiceInfoLen_Out);
GMP_EXTERN int GMP_CALL_TYPE Json_prepare_ReversePayment(uint8* Buffer, int MaxSize, char* szJsonPaymentRequest, char* szJsonPaymentRequest_Out, int JsonPaymentRequestLen_Out, uint16 NumberOfPaymentRequests);
GMP_EXTERN int GMP_CALL_TYPE Json_prepare_Date(uint8* Buffer, int MaxSize, uint32 TagId, char* szTitle, char* szText, char* szMask, char* szJsonValue, char* szJsonValue_Out, int szJsonValueLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN int GMP_CALL_TYPE Json_prepare_PrintUserMessage(uint8* Buffer, int MaxSize, char * szJsonUserMessage, char * szJsonUserMessage_Out, int szJsonUserMessageLen_Out, uint16 NumberOfMessage);
GMP_EXTERN int GMP_CALL_TYPE Json_prepare_PrintUserMessage_Ex(uint8* Buffer, int MaxSize, char * szJsonUserMessage, char * szJsonUserMessage_Out, int szJsonUserMessageLen_Out, uint16 NumberOfMessage);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetCurrencyProfile(char *szJsonExchangeProfileTable_In, char * szJsonExchangeProfileTable_Out, int JsonExchangeProfileLen_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_SetCurrencyProfile(char *supervisorPassword, uint8 profileIndex, uint8 ProfileProcessType, char *szJsonExchangeProfileTable_In);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_SetCurrencyProfileIndex(uint8 profileIndex, char * pstTicket, int timeoutInMiliseconds);

GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetPLU(char* szBarcode, char* szJsonPluRecord, char* szJsonPluRecord_Out, int JsonPluRecordLen_Out,  char* szPluGroupRecord, char* szPluGroupRecord_Out, int PluGroupRecordLen_Out, int MaxNumberOfGroupRecords, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_ReversePayment(char* szJsonPaymentRequest, char * szJsonPaymentRequest_Out, int JsonPaymentRequestLen_Out, uint16 NumberOfPaymentRequests, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_SetTaxFree(uint32 Flag, char* szName, char* szSurname, char* szIdentificationNo, char* szCity, char* szCountry, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_SetParkingTicket(char* szCarIdentification, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_SetTaxFreeRefundAmount(uint32 RefundAmount, uint16 RefundAmountCurrency, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionChangeTicketHeader(char* szSupervisorPassword, uint16* pNumberOfSpaceTotal, uint16* pNumberOfSpaceUsed, char* szJsonTicketHeader,  char* szJsonTicketHeader_Out, int szJsonTicketHeaderLen_Out, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_JumpToECR(uint64 JumpFlags, char* szJsonTicket_Out, int szJsonTicketLen_Out,  int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetTicketHeader(uint16 IndexOfHeader, char *szJsonTicketHeader,  char * szJsonTicketHeader_Out, int JsonTicketHeaderLen_Out, uint16* pNumberOfSpaceTotal, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_CustomerAvans(int Amount, char* szJsonTicket_Out, int szJsonTicketLen_Out, char* szCustomerName, char* szTckn, char* szVkn, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_Database_QueryColomnCaptions(char* szJsonDatabaseResult_Out, int JsonDatabaseResult_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_Database_QueryReadLine(uint16 NumberOfLinesRequested, uint16 NumberOfColomnsRequested, char* szJsonDatabaseResult_Out, int JsonDatabaseResult_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_Database_Execute(char* sqlWord, char* szJsonDatabaseResult_Out, int JsonDatabaseResult_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionEkuSeek(char* szJsonEKUAppInfo, char* szJsonEKUAppInfo_Out, int JsonEKUAppInfoLen_Out,  int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FileSystem_DirListFiles(char* szDirName, char* szJsonStFile, char* szJsonStFile_Out, int JsonStFileLen_Out, short MaxNumberOfFiles, short* pNumberOfFiles);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionEkuReadHeader(uint16 index, char* szJsonEkuHeader, char* szJsonEkuHeader_Out, int JsonEkuHeaderLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionEkuReadData(uint16* pEkuDataBufferReceivedLen, char* szJsonEKUAppInfo, char* szJsonEKUAppInfo_Out, int JsonEKUAppInfoLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionEkuReadInfo(uint16 ekuAccessFunction, char* szJsonEkuModuleInfo, char* szJsonEkuModuleInfo_Out, int JsonEkuModuleInfoLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionBankingRefund(char* szJsonPaymentRequest, char* JsonPaymentRequest_Out, int JsonPaymentRequestLen_Out, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_FunctionBankingBatch(uint16 bkmId, uint16* pnumberOfBankResponse, char* JsonMultipleBankResponse_Out, int JsonMultipleBankResponseLen_Out, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_SetIniParameters(char *szJsonIniParameters);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_GetIniParameters(char *szJsonStFile_Out, int JsonStFileLen_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetVasApplicationInfo(uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, char* szJsonPaymentApplicationInfo_Out, int JsonPaymentApplicationInfoLen_Out, uint16 vasType);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_PrintPaymentTicket(char* szJsonPaymentPrint, int timeoutInMiliseconds);

#endif /*!defined(__TELIUM2__) && !defined(__TELIUM3__)*/


GMP_EXTERN uint64 GMP_CALL_TYPE FiscalPrinter_GetHandle(void);
GMP_EXTERN void GMP_CALL_TYPE FiscalPrinter_ResetHandle(void);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Start(uint8* uniqueId, int lengthOfUniqueId, uint8* uniqueIdSign, int lengthOfUniqueIdSign, uint8* userData, int lengthOfUserData, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Close(int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Ping(int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Echo(ST_ECHO *pstEcho, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_ECHO);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_PrintTotalsAndPayments(int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_PrintBeforeMF(int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_PrintMF(int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_PRINT_MF);
#define FiscalPrinter_PrintTMF				FiscalPrinter_PrintMF
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_PrintUserMessage(ST_USER_MESSAGE stUserMessage[], uint16 numberOfMessage, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_PrintUserMessage_Ex(ST_USER_MESSAGE_EX stUserMessage[], uint16 numberOfMessage, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetTicket(ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetPLU(char *barcode, ST_PLU_RECORD *pstPluRecord, ST_PLU_GROUP_RECORD stPluGroupRecord[], int maxNumberOfGroupRecords, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Payment(ST_PAYMENT_REQUEST* pstPaymentRequest, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_CARD_TRANSACTIONS);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_ReversePayment(ST_PAYMENT_REQUEST pstPaymentRequest[], uint16 numberOfPaymentRequests, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_CARD_TRANSACTIONS);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_TicketHeader(TTicketType ticketType, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetInvoice(ST_INVIOCE_INFO* pstInvoiceInfo, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetOnlineInvoice(ST_ONLINE_INVIOCE_INFO* pstOnlineInvoiceInfo, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetTaxFreeInfo(ST_TAXFREE_INFO* pstTaxFreeInfo, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetParkingTicket(char* carIdentification, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_ItemSale(ST_ITEM* pstItem, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Matrahsiz(char *tck, uint16 subtypeOfTaxException, long matrahsizAmount, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_KasaAvans(int Amount, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_CustomerAvans(int Amount, ST_TICKET* pstTicket, char* pCustomerName, char* pTckn, char* pVkn, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_KasaPayment(int Amount, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Pretotal(ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_DisplayPaymentSummary(int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Plus(int Amount, ST_TICKET *pstTicket, uint16 indexOfItem, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Plus_Ex(int Amount, char *szText, ST_TICKET *pstTicket, uint16 indexOfItem, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Minus(int Amount, ST_TICKET *pstTicket, uint16 indexOfItem, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Minus_Ex(int Amount, char *szText, ST_TICKET *pstTicket, uint16 indexOfItem, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Inc(uint8 Rate, ST_TICKET *pstTicket, uint16 indexOfItem, uint32 *pchangedAmount, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Inc_Ex(uint8 Rate, char *szText, ST_TICKET *pstTicket, uint16 indexOfItem, uint32 *pchangedAmount, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Dec(uint8 Rate, ST_TICKET *pstTicket, uint16 indexOfItem, uint32 *pchangedAmount, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_Dec_Ex(uint8 Rate, char *szText, ST_TICKET *pstTicket, uint16 indexOfItem, uint32 *pchangedAmount, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_VoidPayment(uint16 index, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_CARD_TRANSACTIONS);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_VoidAll(ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_VoidItem(uint16 index, uint64 ItemCount, uint8 ItemCountPrecision, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetTaxFreeRefundAmount(uint32 refundAmount, uint16 refundAmountCurrency, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetTaxFree(uint32 flag, char *name, char *surname, char *identificationNo, char *city, char *country, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_MultipleCommand(ST_MULTIPLE_RETURN_CODE *returnCodes, uint16 *pnumberOfReturnCodes, uint8 *sendBuffer, uint16 sendBufferLen, ST_TICKET *pstTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionGetUniqueIdList(ST_UNIQUE_ID stUniqueIdList[] , uint16 maxNumberOfitems, uint16 indexOfitemsToStart, uint16 *ptotalNumberOfItems, uint16 *pNumberOfItemsInThis, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionTransactionInquiry(ST_TRANS_INQUIRY *pstTransInquiry, int timeoutInMiliseconds);

GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetTlvData(uint32 tag, uint8 *pData, uint16 maxBufferLen, uint16 *pDataLen);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetCashierTable(uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_CASHIER pstCashier[], uint8 numberOfRecordsRequested, uint16 *pactiveCashier);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetExchangeTable(uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_EXCHANGE pstExchange[], uint8 numberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetTaxRates(uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_TAX_RATE pstTaxRate[], uint8 numberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetDepartments(uint8 *pnumberOfTotalDepartments, uint8 *pnumberOfTotalDepartmentsReceived, ST_DEPARTMENT pstDepartments[], uint8 numberOfDepartmentRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetPaymentApplicationInfo(uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO pstExchange[], uint8 numberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetVasApplicationInfo(uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO pstPaymentApplicationInfo[], uint16 vasType);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetCurrentFiscalCounters(uint16 *pZNo, uint16 *pFNo, uint16 *pEKUNo);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetPluDatabaseInfo(char *PluDbName, uint16 *pPluDbType, uint32 *pPluDbSize, uint32 *pPluDbGrupsLastModified, uint32 *pPluDbItemsLastModified);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetTicketHeader(uint16 indexOfHeader, ST_TICKET_HEADER *pstTicketHeader, uint16 *pNumberOfSpaceTotal, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);

GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetPluDatabaseInfo(char* PluDbName, uint16 PluDbType);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetDepartments(ST_DEPARTMENT pstDepartments[], uint8 numberOfDepartmentRequested, char *supervisorPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetuApplicationFunction(uint8 *uApplicationName, uint32 uApplicationId, uint8 *functionName, uint32 functionId, uint32 functionVersion, uint32 functionFlags, uint8 *commandBuffer, uint32 commandLen, char *supervisorPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetTlvData(uint32 tag, uint8 *pData, uint16 Len);

GMP_EXTERN uint32 GMP_CALL_TYPE GetDialogInput_MultipleCommand(ST_MULTIPLE_RETURN_CODE *returnCodes, uint16 *pnumberOfreturnCodes, uint8 *sendBuffer, uint16 sendBufferLen, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE GetDialogInput_Text(uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, char *mask, char *value, int maxLenOfValue, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE GetDialogInput_Date(uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, char *mask, ST_DATE_TIME *value, int maxLenOfValue, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE GetDialogInput_Amount(uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, char *mask, char *value, int maxLenOfValue, char *symbol, uint8 align, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE GetDialogInput_Menu(uint32 *pGL_Dialog_retcode, uint32 tag_id, uint8 typeOfMenu, char* title, const char * const * menu, uint32* pvalue, uint8 buttons, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE GetDialogInput_MsgBox(uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, uint8 icon, uint8 button, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE GetDialogInput_Password(uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, char *mask, char *value, int maxLenOfValue, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE GetDialogBarcode(uint32 *pGL_Dialog_retcode, int Count, uint8 *Buffer, int timeOut);

// F_unctions O Terminal
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionReadZReport(ST_FUNCTION_PARAMETERS *pstFunctionParameters, ST_Z_REPORT *pstZReport, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionReports(uint32 functionFlags, ST_FUNCTION_PARAMETERS *pstFunctionParameters, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionEcrParameter(int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionBankingBatch(uint16 bkmId, uint16 *pnumberOfBankResponse, ST_MULTIPLE_BANK_RESPONSE *pMultipleBankResponse, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionBankingParameter(int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionCashierLogin(uint16 cashierIndex, char *cashierPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionCashierLogout(void);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionAddCashier(uint16 CashierIndex, char *szCashierName, char *szCashierPassword, char *szSupervisorPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionOpenDrawer(void);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionChangeTicketHeader(char *supervisorPassword, uint16 *pNumberOfSpaceTotal, uint16 *pNumberOfSpaceUsed, ST_TICKET_HEADER *pstTicketHeader, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionBankingRefund(ST_PAYMENT_REQUEST *pstReversePayment, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionTransactionInquiry(ST_TRANS_INQUIRY *pstTransInquiry, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_PrintPaymentTicket(ST_TRANS_PAYMENT_PRINT *pstPaymentTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetCurrencyProfile(ST_EXCHANGE_PROFILE pstExchangeProfile[]);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetCurrencyProfile(char *supervisorPassword, uint8 profileIndex, uint8 ProfileProcessType, ST_EXCHANGE_PROFILE pstExchangeProfileTable[]);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_GetCurrencyProfile(char *szJsonExchangeProfileTable_In, char * szJsonExchangeProfileTable_Out, int JsonExchangeProfileLen_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FiscalPrinter_SetCurrencyProfile(char *supervisorPassword, uint8 profileIndex, uint8 ProfileProcessType, char *szJsonExchangeProfileTable_In);
// E_KU AccessFunctions
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionEkuPing(int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionEkuReadInfo(uint16 ekuAccessFunction, ST_EKU_MODULE_INFO *pstEkuModuleInfo, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionEkuReadHeader(uint16 index, ST_EKU_HEADER *pstEkuHeader, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionEkuReadData(uint16 *pEkuDataBufferReceivedLen, ST_EKU_APPINF *pstEKUAppInfo, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionEkuSeek(ST_EKU_APPINF *pstEKUAppInfo, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_FunctionReadCard(uint32 cardReaderTypes, ST_CARD_INFO *pstCardInfo, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_OptionFlags(uint64* pflagsActive, uint64 flagsToBeSet, uint64 flagsToBeClear, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_JumpToECR(uint64 jumpFlags, ST_TICKET* pstTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_GetCurrencyProfile(ST_EXCHANGE_PROFILE pstExchangeProfile[]);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetCurrencyProfile(char *supervisorPassword, uint8 profileIndex, uint8 ProfileProcessType, ST_EXCHANGE_PROFILE pstExchangeProfileTable[]);
GMP_EXTERN uint32 GMP_CALL_TYPE FiscalPrinter_SetCurrencyProfileIndex(uint8 profileIndex, ST_TICKET *pstTicket, int timeoutInMiliseconds);

GMP_EXTERN int GMP_CALL_TYPE prepare_Text(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, char* value, int timeout);
GMP_EXTERN int GMP_CALL_TYPE prepare_Amount(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, char* value, int maxLenOfValue, char* symbol, uint8 align, int timeout);
GMP_EXTERN int GMP_CALL_TYPE prepare_Menu(uint8* Buffer, int MaxSize, uint32 tag_id, uint8 typeOfMenu, char* title, const char * const * menu, uint32* pvalue, uint8 buttons, int timeout);
GMP_EXTERN int GMP_CALL_TYPE prepare_Date(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, ST_DATE_TIME* value, int timeout);
GMP_EXTERN int GMP_CALL_TYPE prepare_Password(uint8* Buffer, int MaxSize, uint32 tag_id, char* title, char* text, char* mask, char* value, uint16 maxLenOfValue, int timeout);
GMP_EXTERN int GMP_CALL_TYPE prepare_MsgBox(uint8 *Buffer, int MaxSize, uint32 tag_id, char *title, char *text, uint8 icon, uint8 button, int timeout);

GMP_EXTERN int GMP_CALL_TYPE prepare_JumpToECR(uint8* Buffer, int MaxSize, uint64 jumpFlags);
GMP_EXTERN int GMP_CALL_TYPE prepare_Condition(uint8* Buffer, int MaxSize, ST_CONDITIONAL_IF *pstCondition);
GMP_EXTERN int GMP_CALL_TYPE prepare_OptionFlags(uint8* Buffer, int MaxSize, uint64 flagsToBeSet,  uint64 flagsToBeClear);
GMP_EXTERN int GMP_CALL_TYPE prepare_Start(uint8* Buffer, int MaxSize, uint8* uniqueId, int lengthOfUniqueId, uint8* uniqueIdSign, int lengthOfUniqueIdSign, uint8* userData, int lengthOfUserData);
GMP_EXTERN int GMP_CALL_TYPE prepare_Close(uint8* Buffer, int MaxSize);
GMP_EXTERN int GMP_CALL_TYPE prepare_TicketHeader(uint8* Buffer, int MaxSize, TTicketType ticketType);
GMP_EXTERN int GMP_CALL_TYPE prepare_ItemSale(uint8* Buffer, int MaxSize, ST_ITEM* pstItem);
GMP_EXTERN int GMP_CALL_TYPE prepare_SetInvoice(uint8* Buffer, int MaxSize, ST_INVIOCE_INFO* pstInvoiceInfo);
GMP_EXTERN int GMP_CALL_TYPE prepare_SendSMMData(uint8* Buffer, int MaxSize, ST_SMM_DATA* pstSMMData);
GMP_EXTERN int GMP_CALL_TYPE prepare_SetOnlineInvoice(uint8* Buffer, int MaxSize, ST_ONLINE_INVIOCE_INFO* pstOnlineInvoiceInfo);
GMP_EXTERN int GMP_CALL_TYPE prepare_SetTaxFreeInfo(uint8* Buffer, int MaxSize, ST_TAXFREE_INFO* pstTaxFreeInfo);
GMP_EXTERN int GMP_CALL_TYPE prepare_SetParkingTicket(uint8* Buffer, int MaxSize, char* carIdentification);
GMP_EXTERN int GMP_CALL_TYPE prepare_Payment(uint8* Buffer, int MaxSize, ST_PAYMENT_REQUEST* stPaymentRequest);
GMP_EXTERN int GMP_CALL_TYPE prepare_ReversePayment(uint8* Buffer, int MaxSize, ST_PAYMENT_REQUEST pstPaymentRequest[], uint16 numberOfPaymentRequests);
GMP_EXTERN int GMP_CALL_TYPE prepare_PrintUserMessage(uint8* Buffer, int MaxSize, ST_USER_MESSAGE stUserMessage[], uint16 numberOfMessage);
GMP_EXTERN int GMP_CALL_TYPE prepare_PrintUserMessage_Ex(uint8* Buffer, int MaxSize, ST_USER_MESSAGE_EX stUserMessage[], uint16 numberOfMessage);
GMP_EXTERN int GMP_CALL_TYPE prepare_PrintTotalsAndPayments(uint8* Buffer, int MaxSize);
GMP_EXTERN int GMP_CALL_TYPE prepare_PrintBeforeMF(uint8* Buffer, int MaxSize);
GMP_EXTERN int GMP_CALL_TYPE prepare_PrintMF(uint8* Buffer, int MaxSize);
GMP_EXTERN int GMP_CALL_TYPE prepare_VoidItem(uint8* Buffer, int MaxSize, uint16 index, uint64 ItemCount, uint8 ItemCountPrecision);
GMP_EXTERN int GMP_CALL_TYPE prepare_Matrahsiz(uint8* Buffer, int MaxSize, char* tck, uint16 subtypeOfTaxException, long matrahsizAmount);
GMP_EXTERN int GMP_CALL_TYPE prepare_Pretotal(uint8* Buffer, int MaxSize);
GMP_EXTERN int GMP_CALL_TYPE prepare_DisplayPaymentSummary(uint8* Buffer, int MaxSize);
GMP_EXTERN int GMP_CALL_TYPE prepare_Plus(uint8 *Buffer, int MaxSize, int Amount, uint16 indexOfItem);
GMP_EXTERN int GMP_CALL_TYPE prepare_Plus_Ex(uint8 *Buffer, int MaxSize, int Amount, char *szText, uint16 indexOfItem);
GMP_EXTERN int GMP_CALL_TYPE prepare_Minus(uint8 *Buffer, int MaxSize, int Amount, uint16 indexOfItem);
GMP_EXTERN int GMP_CALL_TYPE prepare_Minus_Ex(uint8 *Buffer, int MaxSize, int Amount, char *szText, uint16 indexOfItem);
GMP_EXTERN int GMP_CALL_TYPE prepare_Inc(uint8 *Buffer, int MaxSize, uint8 Rate, uint16 indexOfItem);
GMP_EXTERN int GMP_CALL_TYPE prepare_Inc_Ex(uint8 *Buffer, int MaxSize, uint8 Rate, char *szText, uint16 indexOfItem);
GMP_EXTERN int GMP_CALL_TYPE prepare_Dec(uint8 *Buffer, int MaxSize, uint8 Rate, uint16 indexOfItem);
GMP_EXTERN int GMP_CALL_TYPE prepare_Dec_Ex(uint8 *Buffer, int MaxSize, uint8 Rate, char *szText, uint16 indexOfItem);
GMP_EXTERN int GMP_CALL_TYPE prepare_VoidPayment(uint8* Buffer, int MaxSize, uint16 index);
GMP_EXTERN int GMP_CALL_TYPE prepare_VoidAll(uint8* Buffer, int MaxSize);
GMP_EXTERN int GMP_CALL_TYPE prepare_SetTaxFree(uint8* Buffer, int MaxSize, uint32 flag, char* name, char* surname, char* identificationNo, char* city, char* country);
GMP_EXTERN int GMP_CALL_TYPE prepare_SetTaxFreeRefundAmount(uint8* Buffer, int MaxSize, uint32 refundAmount, uint16 refundAmountCurrency);
GMP_EXTERN int GMP_CALL_TYPE prepare_KasaAvans(uint8* Buffer, int MaxSize, long amount, char* pCustomerName, char* pTckn, char* pVkn);
GMP_EXTERN int GMP_CALL_TYPE prepare_PrintPaymentTicket(uint8 *Buffer, int MaxSize, uint16 RetCode);
GMP_EXTERN int GMP_CALL_TYPE prepare_SendFrontStationPrint(uint8 *Buffer, int MaxSize, uint8 *pSendBuffer, uint16 SendBufferLen, uint16 MaxLen, int PrintTimeOut);
GMP_EXTERN int GMP_CALL_TYPE prepare_GetTicket(uint8* Buffer, int MaxSize, uint16 indexOfItemsToStart, uint16 indexOfPaymentsToStart, int indexOfPrinterLinesToStart);
GMP_EXTERN int GMP_CALL_TYPE prepare_GetPLU(uint8 *Buffer, int MaxSize, char *barcode);
GMP_EXTERN int GMP_CALL_TYPE prepare_KasaPayment(uint8* Buffer, int MaxSize, long amount);
GMP_EXTERN int GMP_CALL_TYPE prepare_SendUserData(uint8* buffer,  int MaxSize, uint8 *userData, int userDataLen);

GMP_EXTERN uint32 GMP_CALL_TYPE parse_FiscalPrinter(ST_MULTIPLE_RETURN_CODE returnCodes[], uint16 *pnumberOfreturnCodes, uint32 recvmsgId, uint8 *recvFullBuffer, uint16 recvFullLen, ST_TICKET *pstTicket);
GMP_EXTERN uint32 GMP_CALL_TYPE parse_GetEcr(ST_MULTIPLE_RETURN_CODE *returnCodes, uint16 *pnumberOfreturnCodes, uint32 recvmsgId, uint8 *recvFullBuffer, uint16 recvFullLen);

GMP_EXTERN void GMP_CALL_TYPE ExternalDeviceTrace(const char *Str);
GMP_EXTERN void GMP_CALL_TYPE ExternalDeviceTraceMemory(const char *Str, const void *Ptr, uint16 Len);

GMP_EXTERN const char * GMP_CALL_TYPE GetTagName(uint32 Tag);
GMP_EXTERN char * GMP_CALL_TYPE GetErrorMessage(uint32 ErrorCode, char *Buffer);
GMP_EXTERN char * GMP_CALL_TYPE GetErrorTurkishDescription(uint32 ErrorCode, char *Buffer);


//////////////////////////////////////////
GMP_EXTERN int GMP_CALL_TYPE FP3_prepare_Start(uint8* Buffer, int MaxSize, uint8 IsBackground, uint8* uniqueId, int lengthOfUniqueId, uint8* uniqueIdSign, int lengthOfUniqueIdSign, uint8* userData, int lengthOfUserData);

GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Ping(HINT hInt, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Echo(HINT hInt, ST_ECHO *pstEcho, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_ECHO);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetPLU(HINT hInt, char *barcode, ST_PLU_RECORD *pstPluRecord, ST_PLU_GROUP_RECORD stPluGroupRecord[], int maxNumberOfGroupRecords, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
//GMP_EXTERN uint64 GMP_CALL_TYPE FP3_GetHandle(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetTlvData(HINT hInt, uint32 tag, uint8 *pData, uint16 maxBufferLen, uint16 *pDataLen);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetTlvData(HINT hInt, uint32 tag, uint8 *pData, uint16 Len);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetTaxRates(HINT hInt, uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_TAX_RATE pstTaxRate[], uint8 numberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetTaxRates_Ex(HINT hInt, uint8 indexOfDepartments, uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_TAX_RATE pstTaxRate[], uint8 numberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDepartments(HINT hInt, uint8 *pnumberOfTotalDepartments, uint8 *pnumberOfTotalDepartmentsReceived, ST_DEPARTMENT pstDepartments[], uint8 numberOfDepartmentRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDepartments_Ex(HINT hInt, uint8 indexOfDepartments, uint8 *pnumberOfTotalDepartments, uint8 *pnumberOfTotalDepartmentsReceived, ST_DEPARTMENT pstDepartments[], uint8 numberOfDepartmentRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetDepartments(HINT hInt, ST_DEPARTMENT pstDepartments[], uint8 numberOfDepartmentRequested, char *supervisorPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionEkuPing(HINT hInt, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetTicketHeader(HINT hInt, uint16 indexOfHeader, ST_TICKET_HEADER *pstTicketHeader, uint16 *pNumberOfSpaceTotal, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetOnlineInvoiceInfo(HINT hInt, uint8 *szInvoiceIdNo, uint16 InvoiceIdLen, ST_ONLINE_INVIOCE_INFO *pstOnlineInvoiceInfo, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetCashierTable(HINT hInt, uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_CASHIER pstCashier[], uint8 numberOfRecordsRequested, uint16 *pactiveCashier);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionEkuSeek(HINT hInt, ST_EKU_APPINF *pstEKUAppInfo, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionReadCard(HINT hInt, uint32 cardReaderTypes, ST_CARD_INFO *pstCardInfo, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetCurrencyProfile(HINT hInt, ST_EXCHANGE_PROFILE pstExchangeProfile[]);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetCurrencyProfile(HINT hInt, char *supervisorPassword, uint8 profileIndex, uint8 ProfileProcessType, ST_EXCHANGE_PROFILE pstExchangeProfileTable[]);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetCurrencyProfileIndex(HINT hInt, HTRX hTrx, uint8 profileIndex, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDialogBarcode(HINT hInt, uint32 *pGL_Dialog_retcode, int Count, uint8 *Buffer, int timeOut);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetPluDatabaseInfo(HINT hInt, char *PluDbName, uint16 *pPluDbType, uint32 *pPluDbSize, uint32 *pPluDbGrupsLastModified, uint32 *pPluDbItemsLastModified);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetPluDatabaseInfo(HINT hInt, char* PluDbName, uint16 PluDbType);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionEkuReadInfo(HINT hInt, uint16 ekuAccessFunction, ST_EKU_MODULE_INFO *pstEkuModuleInfo, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionEkuReadData(HINT hInt, uint16 *pEkuDataBufferReceivedLen, ST_EKU_APPINF *pstEKUAppInfo, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionModuleReadInfo(HINT hInt, int AccessFunction, ST_MODULE_USAGE_INFO *pstModuleInfo, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GMP_StartPairingInit(HINT hInt, ST_GMP_PAIR *pstGMPPair, ST_GMP_PAIR_RESP *pstGMPPairResp);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetVasApplicationInfo(HINT hInt, uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO pstPaymentApplicationInfo[], uint16 vasType);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetVasLoyaltyServiceInfo(HINT hInt, uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, uint16 VasAppID, ST_LOYALTY_SERVICE_INFO pstLoyaltyServiceInfo[]);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetVasPaymentServiceInfo(HINT hInt, uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, uint16 VasAppID, ST_VAS_PAYMENT_INFO pstVasPaymentInfo[]);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionEkuReadHeader(HINT hInt, uint16 index, ST_EKU_HEADER *pstEkuHeader, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetuApplicationFunction(HINT hInt, uint8 *uApplicationName, uint32 uApplicationId, uint8 *functionName, uint32 functionId, uint32 functionVersion, uint32 functionFlags, uint8 *commandBuffer, uint32 commandLen, char *supervisorPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetPaymentApplicationInfo(HINT hInt, uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO pstExchange[], uint8 numberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionGetUniqueIdList(HINT hInt, ST_UNIQUE_ID stUniqueIdList[] , uint16 maxNumberOfitems, uint16 indexOfitemsToStart, uint16 *ptotalNumberOfItems, uint16 *pNumberOfItemsInThis, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetDefaultInterfaceByID(const char *szID);

GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionReports(HINT hInt, uint32 functionFlags, ST_FUNCTION_PARAMETERS *pstFunctionParameters, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionAddCashier(HINT hInt, uint16 CashierIndex, char *szCashierName, char *szCashierPassword, char *szSupervisorPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionOpenDrawer(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionReadZReport(HINT hInt, ST_FUNCTION_PARAMETERS *pstFunctionParameters, ST_Z_REPORT *pstZReport, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionReadDM_Report(HINT hInt, ST_FUNCTION_PARAMETERS *pstFunctionParameters, ST_DM_REPORT *pstDM_Report, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionBankingBatch(HINT hInt, uint16 bkmId, uint16 *pnumberOfBankResponse, ST_MULTIPLE_BANK_RESPONSE *pMultipleBankResponse, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionEcrParameter(HINT hInt, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionPaymentCheck(HINT hInt, char *uniqueId, ST_PAYMENT_RESPONSE *pstPaymentCheckResponse, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionCashierLogin(HINT hInt, uint16 cashierIndex, char *cashierPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionBankingRefund(HINT hInt, ST_PAYMENT_REQUEST *pstReversePayment, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionBankingRefundExt(HINT hInt, ST_PAYMENT_REQUEST *pstReversePayment, ST_PAYMENT_RESPONSE *refundResponse, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionVasPaymentRefund(HINT hInt, ST_PAYMENT_REQUEST *pstReversePayment, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionCashierLogout(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetCurrentFiscalCounters(HINT hInt, uint16 *pZNo, uint16 *pFNo, uint16 *pEKUNo);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionBankingParameter(HINT hInt, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionChangeTicketHeader(HINT hInt, char *supervisorPassword, uint16 *pNumberOfSpaceTotal, uint16 *pNumberOfSpaceUsed, ST_TICKET_HEADER *pstTicketHeader, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionTransactionInquiry(HINT hInt, ST_TRANS_INQUIRY *pstTransInquiry, int timeoutInMiliseconds);

GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDialogInput_Text(HINT hInt, uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, char *mask, char *value, int maxLenOfValue, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDialogInput_Date(HINT hInt, uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, char *mask, ST_DATE_TIME *value, int maxLenOfValue, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDialogInput_Menu(HINT hInt, uint32 *pGL_Dialog_retcode, uint32 tag_id, uint8 typeOfMenu, char* title, const char * const * menu, uint32* pvalue, uint8 buttons, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDialogInput_MsgBox(HINT hInt, uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, uint8 icon, uint8 button, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDialogInput_Amount(HINT hInt, uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, char *mask, char *value, int maxLenOfValue, char *symbol, uint8 align, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDialogInput_Password(HINT hInt, uint32 *pGL_Dialog_retcode, uint32 tag_id, char *title, char *text, char *mask, char *value, int maxLenOfValue, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDialogInput_MultipleCommand(HINT hInt, ST_MULTIPLE_RETURN_CODE *returnCodes, uint16 *pnumberOfreturnCodes, uint8 *sendBuffer, uint16 sendBufferLen, int timeoutInMiliseconds);

GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FileSystem_FileRead(HINT hInt, char *FileName, uint32 offset, uint32 whence, uint8 *buffer, uint16 maxLen, uint16 *pReadLen);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FileSystem_FileWrite(HINT hInt, char *FileName, uint32 offset, uint32 whence, uint8 *buffer, uint16 len);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FileSystem_DirChange(HINT hInt, char *DirName);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FileSystem_FileRemove(HINT hInt, char *FileName);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FileSystem_FileRename(HINT hInt, char *FileNameOld, char *FileNameNew);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FileSystem_DirListFiles(HINT hInt, char *DirName, ST_FILE stFile[], uint16 maxNumberOfFiles, uint16 *pNumberOfFiles);

GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_Open(HINT hInt, char *name);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_Query(HINT hInt, char *sqlWord, uint16 *pnumberOfColomns);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_Close(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_Execute(HINT hInt, char *sqlWord, ST_DATABASE_RESULT *pstDatabaseResult);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_GetHandle(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_QueryReset(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_QueryFinish(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_FreeStructure(HINT hInt, ST_DATABASE_RESULT *pst);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_QueryReadLine(HINT hInt, uint16 numberOfLinesRequested, uint16 numberOfColomnsRequested, ST_DATABASE_RESULT *pstDatabaseResult);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Database_QueryColomnCaptions(HINT hInt, ST_DATABASE_RESULT *pstDatabaseResult);

GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Echo(HINT hInt, char* szJsonEcho_Out, int szJsonEchoLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetPLU(HINT hInt, char* szBarcode, char* szJsonPluRecord, char* szJsonPluRecord_Out, int JsonPluRecordLen_Out,  char* szPluGroupRecord, char* szPluGroupRecord_Out, int PluGroupRecordLen_Out, int MaxNumberOfGroupRecords, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetTaxRates(HINT hInt, uint8* pNumberOfTotalRecords, uint8* pNumberOfTotalRecordsReceived, char* szJsonTaxRates, char* szJsonTaxRate_Out, int JsonTaxRateLen_Out, uint8 NumberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetTaxRates_Ex(HINT hInt, uint8 indexOfTaxRates, uint8* pNumberOfTotalRecords, uint8* pNumberOfTotalRecordsReceived, char* szJsonTaxRates, char* szJsonTaxRate_Out, int JsonTaxRateLen_Out, uint8 NumberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SetDepartments(HINT hInt, char* szJsonDepartments, char* szJsonDepartments_Out, int JsonDepartmentsLen_Out, uint8 NumberOfDepartmentRequested, char* szPassword);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetDepartments(HINT hInt, uint8* pNumberOfTotalDepartments, uint8* pNumberOfTotalDepartmentsReceived, char* szJsonDepartments, char* szJsonDepartments_Out, int JsonDepartmentsLen_Out, uint8 NumberOfDepartmentRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetDepartments_Ex(HINT hInt, uint8 indexOfDepartments, uint8* pNumberOfTotalDepartments, uint8* pNumberOfTotalDepartmentsReceived, char* szJsonDepartments, char* szJsonDepartments_Out, int JsonDepartmentsLen_Out, uint8 NumberOfDepartmentRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionEkuSeek(HINT hInt, char* szJsonEKUAppInfo, char* szJsonEKUAppInfo_Out, int JsonEKUAppInfoLen_Out,  int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetCashierTable(HINT hInt, uint8* pNumberOfTotalRecords, uint8* pNumberOfTotalRecordsReceived, char* szJsonCashier, char * szJsonCashier_Out, int JsonCashierLen_Out, uint8 NumberOfRecordsRequested, uint16* pActiveCashier);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetTicketHeader(HINT hInt, uint16 IndexOfHeader, char *szJsonTicketHeader,  char * szJsonTicketHeader_Out, int JsonTicketHeaderLen_Out, uint16* pNumberOfSpaceTotal, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetOnlineInvoiceInfo(HINT hInt, uint8 *szInvoiceId, uint16 InvoiceIdLen, char * szJsonOnlineInvoiceInfo_Out, int JsonOnlineInvoiceInfoLen_Out, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionReports(HINT hInt, uint32 FunctionFlags, char* szJsonFunctionParameters, char * szJsonFunctionParameters_Out, int JsonFunctionParametersLen_Out, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionReadCard(HINT hInt, uint32 CardReaderTypes, char* szJsonCardInfo, char* szJsonCardInfo_Out, int JsonCardInfoLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetCurrencyProfile(HINT hInt, char *szJsonExchangeProfileTable_In, char * szJsonExchangeProfileTable_Out, int JsonExchangeProfileLen_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SetCurrencyProfile(HINT hInt, char *supervisorPassword, uint8 profileIndex, uint8 ProfileProcessType, char *szJsonExchangeProfileTable_In);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SetCurrencyProfileIndex(HINT hInt, HTRX hTrx, uint8 profileIndex, char * pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_StartPairingInit(HINT hInt, char* szJsonPair, char * szJsonPairResp_Out, int JsonPairRespLen_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Database_Execute(HINT hInt, char* sqlWord, char* szJsonDatabaseResult_Out, int JsonDatabaseResult_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionReadZReport(HINT hInt, char* szJsonFunctionParameters, char* szJsonZReport_Out, int JsonZReportLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionReadDM_Report(HINT hInt, char* szJsonFunctionParameters, char* szJsonDM_Report_Out, int JsonDM_ReportLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionPaymentCheck(HINT hInt, char * szJsonCheckResponse_In, char * szJsonCheckResponse_Out, int szJsonCheckResponseLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionEkuReadInfo(HINT hInt, uint16 ekuAccessFunction, char* szJsonEkuModuleInfo, char* szJsonEkuModuleInfo_Out, int JsonEkuModuleInfoLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionEkuReadData(HINT hInt, uint16* pEkuDataBufferReceivedLen, char* szJsonEKUAppInfo, char* szJsonEKUAppInfo_Out, int JsonEKUAppInfoLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionModuleReadInfo(HINT hInt, int AccessFunction, char* szJsonModuleInfo, char* szJsonModuleInfo_Out, int JsonModuleInfoLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionBankingBatch(HINT hInt, uint16 bkmId, uint16* pnumberOfBankResponse, char* JsonMultipleBankResponse_Out, int JsonMultipleBankResponseLen_Out, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionBankingRefund(HINT hInt, char* szJsonPaymentRequest, char* JsonPaymentRequest_Out, int JsonPaymentRequestLen_Out, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionBankingRefundExt(HINT hInt, char* szJsonPaymentRequest, char* JsonPaymentRequest_Out, int JsonPaymentRequestLen_Out, char *JsonRefundResponse, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetVasApplicationInfo(HINT hInt, uint8 *pnumberOfTotalRecords, uint8 *pnumberOfTotalRecordsReceived, char* szJsonPaymentApplicationInfo_Out, int JsonPaymentApplicationInfoLen_Out, uint16 vasType);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetVasLoyaltyServiceInfo(HINT hInt, uint8 *pNumberOfTotalRecords, uint8 *pNumberOfTotalRecordsReceived, char* szJsonPaymentApplicationInfo_Out, int JsonPaymentApplicationInfoLen_Out, uint16 vasType);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionEkuReadHeader(HINT hInt, uint16 index, char* szJsonEkuHeader, char* szJsonEkuHeader_Out, int JsonEkuHeaderLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Database_FreeStructure(HINT hInt, char* szJsonDatabaseResult, char* szJsonDatabaseResult_Out, int JsonDatabaseResult_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Database_QueryReadLine(HINT hInt, uint16 NumberOfLinesRequested, uint16 NumberOfColomnsRequested, char* szJsonDatabaseResult_Out, int JsonDatabaseResult_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionGetUniqueIdList(HINT hInt, char* szJsonUniqueIdList, char* szJsonUniqueIdList_Out, int JsonUniqueIdListLen_Out, uint16 MaxNumberOfitems, uint16 IndexOfitemsToStart, uint16* pTotalNumberOfItems, uint16* pNumberOfItemsInThis,  int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FileSystem_DirListFiles(HINT hInt, char* szDirName, char* szJsonStFile, char* szJsonStFile_Out, int JsonStFileLen_Out, short MaxNumberOfFiles, short* pNumberOfFiles);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetPaymentApplicationInfo(HINT hInt, uint8* pNumberOfTotalRecords, uint8* pNumberOfTotalRecordsReceived, char* szJsonPaymentApplicationInfo, char* szJsonPaymentApplicationInfo_Out, int JsonPaymentApplicationInfoLen_Out, uint8 NumberOfRecordsRequested);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionChangeTicketHeader(HINT hInt, char* szSupervisorPassword, uint16* pNumberOfSpaceTotal, uint16* pNumberOfSpaceUsed, char* szJsonTicketHeader,  char* szJsonTicketHeader_Out, int szJsonTicketHeaderLen_Out, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Database_QueryColomnCaptions(HINT hInt, char* szJsonDatabaseResult_Out, int JsonDatabaseResult_Out);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_LoyaltyCustomerQuery(HINT hInt, HTRX hTrx, char* szJsonLoyaltyServiceReq, char* szJsonLoyaltyServiceReq_Out, int JsonLoyaltyServiceReqLen_Out, char * szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_LoyaltyDiscount(HINT hInt, HTRX hTrx, uint8 isRate, int Amount, uint8 Rate, char *szLoyaltyCustomerId, char *szText, uint16 indexOfItem, uint32 *pchangedAmount, char * szJsonTicket_Out, int JsonTicketLen_Out, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionVasPaymentRefund(HINT hInt, char* szJsonPaymentRequest, char* szJsonPaymentRequest_Out, int JsonPaymentRequestLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionTransactionInquiry(HINT hInt, char* szJsonTransInquiry, char* szJsonTransInquiry_Out, int JsonTransInquiryLen_Out, int TimeoutInMiliseconds);

//FP3_Plus_Ex aslýnda
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Plus(HINT hInt, HTRX hTrx, int Amount, char *szText, ST_TICKET *pstTicket, uint16 indexOfItem, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
//FP3_Minus_Ex aslýnda
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Minus(HINT hInt, HTRX hTrx, int Amount, char *szText, ST_TICKET *pstTicket, uint16 indexOfItem, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Start(HINT hInt, HTRX *HTrx, uint8 IsBackground, uint8* uniqueId, int lengthOfUniqueId, uint8* uniqueIdSign, int lengthOfUniqueIdSign, uint8* userData, int lengthOfUserData, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Close(HINT hInt, HTRX hTrx, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Inc(HINT hInt, HTRX hTrx, uint8 Rate, char *szText, ST_TICKET *pstTicket, uint16 indexOfItem, uint32 *pchangedAmount, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Dec(HINT hInt, HTRX hTrx, uint8 Rate, char *szText, ST_TICKET *pstTicket, uint16 indexOfItem, uint32 *pchangedAmount, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_PrintMF(HINT hInt, HTRX hTrx, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_PRINT_MF);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_VoidAll(HINT hInt, HTRX hTrx, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Payment(HINT hInt, HTRX hTrx, ST_PAYMENT_REQUEST* pstPaymentRequest, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_CARD_TRANSACTIONS);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_VoidItem(HINT hInt, HTRX hTrx, uint16 index, uint64 ItemCount, uint8 ItemCountPrecision, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Pretotal(HINT hInt, HTRX hTrx, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_ItemSale(HINT hInt, HTRX hTrx, ST_ITEM* pstItem, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetTicket(HINT hInt, HTRX hTrx, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_IsGmpPairingDone(HINT hInt);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_JumpToECR(HINT hInt, HTRX hTrx, uint64 jumpFlags, ST_TICKET* pstTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_Matrahsiz(HINT hInt, HTRX hTrx, char *tck, uint16 subtypeOfTaxException, long matrahsizAmount, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_KasaAvans(HINT hInt, HTRX hTrx, int Amount, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetTaxFree(HINT hInt, HTRX hTrx, uint32 flag, char *name, char *surname, char *identificationNo, char *city, char *country, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetInvoice(HINT hInt, HTRX hTrx, ST_INVIOCE_INFO* pstInvoiceInfo, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SendSMMData(HINT hInt, HTRX hTrx, ST_SMM_DATA *pstSMMData, ST_TICKET* pstTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SendGiderPusulasi(HINT hInt, HTRX hTrx, ST_GIDER_PUSULASI *pstGiderPusulasi, ST_TICKET* pstTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetOnlineInvoice(HINT hInt, HTRX hTrx, ST_ONLINE_INVIOCE_INFO* pstOnlineInvoiceInfo, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetTaxFreeInfo(HINT hInt, HTRX hTrx, ST_TAXFREE_INFO* pstTaxFreeInfo, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_VoidPayment(HINT hInt, HTRX hTrx, uint16 index, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_CARD_TRANSACTIONS);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_KasaPayment(HINT hInt, HTRX hTrx, int Amount, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_OptionFlags(HINT hInt, HTRX hTrx, uint64* pflagsActive, uint64 flagsToBeSet, uint64 flagsToBeClear, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_TicketHeader(HINT hInt, HTRX hTrx, TTicketType ticketType, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_PrintBeforeMF(HINT hInt, HTRX hTrx, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_CustomerAvans(HINT hInt, HTRX hTrx, int Amount, ST_TICKET* pstTicket, char* pCustomerName, char* pTckn, char* pVkn, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_CariHesap(HINT hInt, HTRX hTrx, int Amount, ST_TICKET* pstTicket, char* pCustomerName, char* pTckn, char* pVkn, char* pBelgeNo, char* pBelgeDate, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_ReversePayment(HINT hInt, HTRX hTrx, ST_PAYMENT_REQUEST pstPaymentRequest[], uint16 numberOfPaymentRequests, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_CARD_TRANSACTIONS);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_MultipleCommand(HINT hInt, HTRX *phTrx, ST_MULTIPLE_RETURN_CODE *returnCodes, uint16 *pnumberOfReturnCodes, uint8 *sendBuffer, uint16 sendBufferLen, ST_TICKET *pstTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetParkingTicket(HINT hInt, HTRX hTrx, char* carIdentification, ST_TICKET* pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_PrintUserMessage(HINT hInt, HTRX hTrx, ST_USER_MESSAGE stUserMessage[], uint16 numberOfMessage, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_PrintPaymentTicket(HINT hInt, HTRX hTrx, ST_TRANS_PAYMENT_PRINT *pstPaymentTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_PrintUserMessage_Ex(HINT hInt, HTRX hTrx, ST_USER_MESSAGE_EX stUserMessage[], uint16 numberOfMessage, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_DisplayPaymentSummary(HINT hInt, HTRX hTrx, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_PrintTotalsAndPayments(HINT hInt, HTRX hTrx, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetTaxFreeRefundAmount(HINT hInt, HTRX hTrx, uint32 refundAmount, uint16 refundAmountCurrency, ST_TICKET *pstTicket, int timeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SendFrontStationPrint(HINT hInt, HTRX hTrx, uint8 *pSendBuffer, uint16 SendLen, uint8 *pReceiveBuffer, uint16 *pReceiveLen, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SendFrontStationPrintEx(HINT hInt, HTRX hTrx, uint8 *pSendBuffer, uint16 SendLen, uint8 *pReceiveBuffer, uint16 *pReceiveLen, int ReceiveTimeOut, int PrinterTimeOut);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_LoyaltyCustomerQuery(HINT hInt, HTRX hTrx, ST_LOYALTY_SERVICE_REQ *pstLoyaltyServiceInfo, ST_TICKET *pstTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_LoyaltyDiscount(HINT hInt, HTRX hTrx, uint8 isRate, int Amount, uint8 Rate, char *szLoyaltyCustomerId, char *szText, uint16 indexOfItem, uint32 *pchangedAmount, ST_TICKET *pstTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_LoyaltyProcess(HINT hInt, HTRX hTrx, ST_LOYALTY_PROCESS *pstLoyaltyProcess, ST_TICKET *pstTicket, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetMerchantSlip(HINT hInt, HTRX hTrx, int odemeIndex, unsigned int supportedFonts, uint8 *slip, int *slipLen, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SendUserData(HINT hInt, HTRX hTrx, uint8 *userData, int userDataLen, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetUserData(HINT hInt, HTRX hTrx, uint8 *userData, int *userDataLen, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetDrawerState(HINT hInt, int state, int timeoutInMiliseconds);

GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Plus(HINT hInt, HTRX hTrx, int Amount, char *szText, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem , int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Minus(HINT hInt, HTRX hTrx, int Amount, char *szText, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Dec(HINT hInt, HTRX hTrx, uint8 Rate, char *szText, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem, uint32* pChangedAmount, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Inc(HINT hInt, HTRX hTrx, uint8 Rate, char *szText, char *szJsonTicket_Out, int JsonTicketLen_Out, uint16 IndexOfItem, uint32* pChangedAmount, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_VoidAll(HINT hInt, HTRX hTrx, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Payment(HINT hInt, HTRX hTrx, char* szJsonPaymentRequest, char* JsonPaymentRequest_Out, int JsonPaymentRequestLen_Out, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_VoidItem(HINT hInt, HTRX hTrx, uint16 Index, uint64 ItemCount, uint8 ItemCountPrecision, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_ItemSale(HINT hInt, HTRX hTrx, char* szJsonItem, char* szJsonItem_Out, int szJsonItemLen_Out, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Pretotal(HINT hInt, HTRX hTrx, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_JumpToECR(HINT hInt, HTRX hTrx, uint64 JumpFlags, char* szJsonTicket_Out, int szJsonTicketLen_Out,  int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_KasaAvans(HINT hInt, HTRX hTrx, int Amount, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_GetTicket(HINT hInt, HTRX hTrx, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_Matrahsiz(HINT hInt, HTRX hTrx, char* szTck, uint16 SubtypeOfTaxException, int MatrahsizAmount, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SetTaxFree(HINT hInt, HTRX hTrx, uint32 Flag, char* szName, char* szSurname, char* szIdentificationNo, char* szCity, char* szCountry, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SetInvoice(HINT hInt, HTRX hTrx, char* szJsonInvoiceInfo, char* szJsonInvoiceInfo_Out, int szJsonInvoiceInfoLen_Out, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SendSMMData(HINT hInt, HTRX hTrx, char* szJsonSMMData, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SendGiderPusulasi(HINT hInt, HTRX hTrx, char* szJsonGiderPusulasi, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SetOnlineInvoice(HINT hInt, HTRX hTrx, char * szJsonOnlineInvoiceInfo, char * szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_KasaPayment(HINT hInt, HTRX hTrx, int Amount, char* szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_VoidPayment(HINT hInt, HTRX hTrx, uint16 Index, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_CustomerAvans(HINT hInt, HTRX hTrx, int Amount, char* szJsonTicket_Out, int szJsonTicketLen_Out, char* szCustomerName, char* szTckn, char* szVkn, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_CariHesap(HINT hInt, HTRX hTrx, int Amount, char* szJsonTicket_Out, int szJsonTicketLen_Out, char* szCustomerName, char* szTckn, char* szVkn, char* szBelgeNo, char* szBelgeDate, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_ReversePayment(HINT hInt, HTRX hTrx, char* szJsonPaymentRequest, char * szJsonPaymentRequest_Out, int JsonPaymentRequestLen_Out, uint16 NumberOfPaymentRequests, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_MultipleCommand(HINT hInt, HTRX *phTrx, char * szJsonReturnCodes_Out, int JsonReturnCodesLen_Out, uint16* pNumberOfreturnCodes,  uint8* pSendBuffer, uint16 SendBufferLen,  char * szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SetParkingTicket(HINT hInt, HTRX hTrx, char* szCarIdentification, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_PrintPaymentTicket(HINT hInt, HTRX hTrx, char* szJsonPaymentPrint, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_PrintUserMessage(HINT hInt, HTRX hTrx, char* szJsonUserMessage, char* szJsonUserMessage_Out, int JsonUserMessageLen_Out, uint16 NumberOfMessage, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_PrintUserMessage_Ex(HINT hInt, HTRX hTrx, char* szJsonUserMessage, char* szJsonUserMessage_Out, int JsonUserMessageLen_Out, uint16 NumberOfMessage, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SetTaxFreeRefundAmount(HINT hInt, HTRX hTrx, uint32 RefundAmount, uint16 RefundAmountCurrency, char* szJsonTicket_Out, int szJsonTicketLen_Out, int TimeoutInMiliseconds DEFAULT_PARAM_TIMEOUT_DEFAULT);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_SetTaxFreeInfo(HINT hInt, HTRX hTrx, char * szJsonTaxFreeInfo, char * szJsonTicket_Out, int JsonTicketLen_Out, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE Json_parse_FP3(HTRX hTrx, char * szJsonReturnCodes_Out, int JsonReturnCodesLen_Out, uint16* pNumberOfreturnCodes, uint32 RecvMsgId, uint8* RecvFullBuffer, uint16 RecvFullLen, char * szJsonTicket_Out, int JsonTicketLen_Out, int MaxNumberOfReturnCode, int MaxReturnCodeDataLen);

GMP_EXTERN uint32 GMP_CALL_TYPE parse_FP3(HTRX *phTrx, ST_MULTIPLE_RETURN_CODE returnCodes[], uint16 *pnumberOfreturnCodes, uint32 recvmsgId, uint8 *recvFullBuffer, uint16 recvFullLen, ST_TICKET *pstTicket);

GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetListOfBackgroundTransaction(HINT hInt, uint8 StatusFilter, ST_MASTERECR_HANDLE_LIST* pstHandleList, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_GetDataOfBackgroundTransaction(HINT hInt, uint64 TransactionHandle, ST_MASTERECR_TRANSACTION_DATA* pstTransactionData, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionGetHandleList(HINT hInt, ST_HANDLE_LIST pstHandleList[], uint8 StatusFilter, uint16 StartIndexOfHandle, uint16 HandleListSize, uint16 *pTotalNumberOfHandlesInEcr, uint16 *pReceivedNumberOfHandleInList, int TimeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionCreateUniqueId(HINT hInt, uint8 *UniqueId, int TimeoutInMiliseconds);

GMP_EXTERN uint32 GMP_CALL_TYPE FP3_SetBackGroundUserDefinition(HINT hInt, HTRX hTrx, uint8 *szUserDefinedTranGroup, uint8 *szUserDefinedTranDefination, int timeoutInMiliseconds);
GMP_EXTERN uint32 GMP_CALL_TYPE FP3_FunctionLoadBackGroundHandleToFront(HINT hInt, HTRX hTrx, int timeoutInMiliseconds);

GMP_EXTERN uint32 GMP_CALL_TYPE Json_FP3_FunctionGetHandleList(HINT hInt, char *szJsonHandleList_Out, int JsonHandleListLen_Out, uint8 StatusFilter, uint16 StartIndexOfHandle, uint16 HandleListSize, uint16 *pTotalNumberOfHandlesInEcr, uint16 *pReceivedNumberOfHandleInList, int TimeoutInMiliseconds);


#if defined(__TELIUM2__) || defined(__TELIUM3__)
// Telium App Shuld be implemented this functions!!!
void DllTracePrintInterface(uint8 Type, const char *Buffer);
uint8 DllTraceCheckType(uint8 Type);
#define TELIUM_INTERFACE_HANDLE						0x26DF345A
#endif /*defined(__TELIUM2__) || defined(__TELIUM3__)*/

#endif /*__GMPSmartDLL_H__*/

