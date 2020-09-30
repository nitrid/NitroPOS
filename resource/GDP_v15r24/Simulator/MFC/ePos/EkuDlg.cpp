// EkuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "EkuDlg.h"
#include "afxdialogex.h"
#include "ePosDlg.h"

// CEkuDlg dialog

IMPLEMENT_DYNAMIC(CEkuDlg, CDialogEx)

CEkuDlg::CEkuDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CEkuDlg::IDD, pParent)
		, m_subCommand(0)
		, myFont(NULL)
		, m_ZNoStart(1)
		, m_FNoStart(1)
		, m_DateStart(COleDateTime::GetCurrentTime())
		, m_DateEnd(COleDateTime::GetCurrentTime())
		, m_TimeStart(COleDateTime::GetCurrentTime())
		, m_TimeEnd(COleDateTime::GetCurrentTime())
		, pstEkuModuleInfo(NULL)
		, pstEkuHeader(NULL)
{

}

CEkuDlg::~CEkuDlg()
{
}

void CEkuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ZNO_START, m_ZNoStart);
	DDX_Text(pDX, IDC_EDIT_FNO_START, m_FNoStart);
	DDX_Control(pDX, IDC_LIST_PRINTER, m_listPrinter);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_DateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_DateEnd);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_TimeStart);
	DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_TimeEnd);
	DDX_Control(pDX, IDC_LIST_EKU_HEADER, m_listEkuHeader);
	DDX_Control(pDX, IDC_LIST_EKU_MODULE_INFO, m_listEkuModuleInfo);
}


BEGIN_MESSAGE_MAP(CEkuDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CEkuDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_BY_ZNO_FNO, &CEkuDlg::OnBnClickedButtonSearchByZnoFno)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_BY_DATE_TIME, &CEkuDlg::OnBnClickedButtonSearchByDateTime)
	ON_BN_CLICKED(IDC_BUTTON_READ_MODULE_INFO, &CEkuDlg::OnBnClickedButtonReadModuleInfo)
	ON_BN_CLICKED(IDC_BUTTON_READ_HEADER, &CEkuDlg::OnBnClickedButtonReadHeader)
	ON_BN_CLICKED(IDC_BUTTON_EKU_PING, &CEkuDlg::OnBnClickedButtonEkuPing)
	ON_BN_CLICKED(IDC_BUTTON_EKU_PRESENT, &CEkuDlg::OnBnClickedButtonEkuPresent)
	ON_BN_CLICKED(IDC_BUTTON_EKU_RESET, &CEkuDlg::OnBnClickedButtonEkuReset)
	ON_BN_CLICKED(IDC_BUTTON_READ_DATA_NEXT, &CEkuDlg::OnBnClickedButtonReadDataNext)
END_MESSAGE_MAP()


// CEkuDlg message handlers


BOOL CEkuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	myFont = new CFont();
	myFont->CreateFont(16, 0, 0, 0, FW_HEAVY, false, false,
					   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					   FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));

	m_listPrinter.SetFont(myFont, true);
	m_listEkuModuleInfo.SetFont(myFont, true);
	m_listEkuHeader.SetFont(myFont, true);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CEkuDlg::Print(CListBox* plist, char * buffer, ...)
{
	va_list 		args;
	char tmp[512];
	CString cs;

	va_start(args, buffer);
	vsprintf(tmp, buffer, args);
	va_end(args);
	cs = tmp;

	if (cs.GetLength())
		plist->AddString(cs);
}

int CEkuDlg::LoadEkuHeader(void)
{
	int retcode = TRAN_RESULT_OK;

	if (pstEkuHeader == NULL)
	{
		pstEkuHeader = new ST_EKU_HEADER;

		memset(pstEkuHeader, 0x00, sizeof(ST_EKU_HEADER));
		retcode = FP3_FunctionEkuReadHeader(m_hInt, 0xFF, pstEkuHeader, TIMEOUT_DEFAULT);
		if (retcode != TRAN_RESULT_OK)
		{
			delete pstEkuHeader;
			pstEkuHeader = NULL;
			return retcode;
		}

		Print(&m_listEkuHeader, "EKU HEADER");
		Print(&m_listEkuHeader, "------------------------");
		Print(&m_listEkuHeader, "SÝCÝL       : %-16.16s"	,	pstEkuHeader->SicilNo);
		Print(&m_listEkuHeader, "TERMINAL S/N: %-16.16s"	,	pstEkuHeader->TerminalSerialNo);
		Print(&m_listEkuHeader, "TERMINAL PC : %-16.16s"	,	pstEkuHeader->TerminalProductCode);
		Print(&m_listEkuHeader, "SW VERS     : %-16.16s"	,	pstEkuHeader->SoftwareVersion);
		Print(&m_listEkuHeader, "ACTIVE      : %d"			,	pstEkuHeader->Active);
		Print(&m_listEkuHeader, "EKU COUNT   : %d"			,	pstEkuHeader->EkuCount);
		Print(&m_listEkuHeader, "HEADER INDEX: %d"			,	pstEkuHeader->HeaderIndex);
		Print(&m_listEkuHeader, "HEADER TOTAL: %d"			,	pstEkuHeader->HeaderTotal);
		Print(&m_listEkuHeader, "INIT");
		Print(&m_listEkuHeader, "  ZNo       : %d"			,	pstEkuHeader->Init.ZNo);
		Print(&m_listEkuHeader, "  FNo       : %d"			,	pstEkuHeader->Init.FNo);
		Print(&m_listEkuHeader, "  DATETIME  : %08X"		,	pstEkuHeader->Init.DateTime);
		Print(&m_listEkuHeader, "CLOSE");
		Print(&m_listEkuHeader, "  ZNo       : %d"			,	pstEkuHeader->Close.ZNo);
		Print(&m_listEkuHeader, "  FNo       : %d"			,	pstEkuHeader->Close.FNo);
		Print(&m_listEkuHeader, "  DATETIME  : %08X"		,	pstEkuHeader->Close.DateTime);

		Print(&m_listEkuHeader, "\n");
		Print(&m_listEkuHeader, "MERCHANT");
		Print(&m_listEkuHeader, "------------------------");
		Print(&m_listEkuHeader, "  NAME      : %-32.32s"	,	&pstEkuHeader->MerchantName[0]);
		Print(&m_listEkuHeader, "            : %-32.32s"	,	&pstEkuHeader->MerchantName[32]);
		Print(&m_listEkuHeader, "  ADDRESS   : %-32.32s"	,	&pstEkuHeader->MerchantAddress[0]);
		Print(&m_listEkuHeader, "            : %-32.32s"	,	&pstEkuHeader->MerchantAddress[32]);
		Print(&m_listEkuHeader, "            : %-32.32s"	,	&pstEkuHeader->MerchantAddress[64]);
		Print(&m_listEkuHeader, "  VAT OFFICE: %-24.24s"	,	&pstEkuHeader->VATOffice[0]);
		Print(&m_listEkuHeader, "  VAT NUMBER: %-12.12s"	,	&pstEkuHeader->VATNumber[0]);
		Print(&m_listEkuHeader, "  MERSIS    : %-20.20s"	,	&pstEkuHeader->MersisNo[0]);
		Print(&m_listEkuHeader, "  TÝCARI S.N: %-16.16s"	,	&pstEkuHeader->TicariSicilNo[0]);
		Print(&m_listEkuHeader, "  WEB       : %-32.32s"	,	&pstEkuHeader->WebAddress[0]);
		Print(&m_listEkuHeader, "            : %-32.32s"	,	&pstEkuHeader->WebAddress[32]);
	}

	return retcode;
}

int CEkuDlg::LoadEkuModuleInfo(void)
{
	int retcode = TRAN_RESULT_OK;

	if (pstEkuModuleInfo == NULL)
	{
		pstEkuModuleInfo = new ST_EKU_MODULE_INFO;

		memset(pstEkuModuleInfo, 0x00, sizeof(ST_EKU_MODULE_INFO));
		retcode = FP3_FunctionEkuReadInfo(m_hInt, TLV_FUNC_INFO_DEVICE, pstEkuModuleInfo, TIMEOUT_DEFAULT);
		if (retcode != TRAN_RESULT_OK)
		{
			delete pstEkuModuleInfo;
			pstEkuModuleInfo = NULL;
			return retcode;
		}

		retcode = FP3_FunctionEkuReadInfo(m_hInt, TLV_FUNC_INFO_EKU, pstEkuModuleInfo, TIMEOUT_DEFAULT);
		if (retcode != TRAN_RESULT_OK)
		{
			delete pstEkuModuleInfo;
			pstEkuModuleInfo = NULL;
			return retcode;
		}

		Print(&m_listEkuModuleInfo, "EKU MODULE INFO (DEVICE)");
		Print(&m_listEkuModuleInfo, "------------------------");
		Print(&m_listEkuModuleInfo, "SW VERS     : %-16.16s",	pstEkuModuleInfo->Device.szSoftVersion);
		Print(&m_listEkuModuleInfo, "HW VERS     : %-16.16s",	pstEkuModuleInfo->Device.szHardVersion);
		Print(&m_listEkuModuleInfo, "COMPL DATE  : %-16.16s",	pstEkuModuleInfo->Device.szCompileDate);
		Print(&m_listEkuModuleInfo, "DESCRIPTION : %-16.16s",	pstEkuModuleInfo->Device.szDescription);
		Print(&m_listEkuModuleInfo, "HW REF      : %-16.16s",	pstEkuModuleInfo->Device.szHardwareReference);
		Print(&m_listEkuModuleInfo, "HW S/N      : %-16.16s",	pstEkuModuleInfo->Device.szHardwareSerial);
		Print(&m_listEkuModuleInfo, "CPU ID      : %08X%08X%08X"	,	*((uint32*)&pstEkuModuleInfo->Device.szCpuID[0]),	*((uint32*)&pstEkuModuleInfo->Device.szCpuID[4]),	*((uint32*)&pstEkuModuleInfo->Device.szCpuID[8]));
		Print(&m_listEkuModuleInfo, "\n");
		Print(&m_listEkuModuleInfo, "FLASH 1");
		Print(&m_listEkuModuleInfo, "CPU ID      : %08X",	*((uint32*)pstEkuModuleInfo->Device.Flash1.ID));
		Print(&m_listEkuModuleInfo, "SIZE        : %d bytes",	pstEkuModuleInfo->Device.Flash1.Size);
		Print(&m_listEkuModuleInfo, "\n");
		Print(&m_listEkuModuleInfo, "FLASH 2");
		Print(&m_listEkuModuleInfo, "CPU ID      : %08X",	*((uint32*)pstEkuModuleInfo->Device.Flash2.ID));
		Print(&m_listEkuModuleInfo, "SIZE        : %d bytes",	pstEkuModuleInfo->Device.Flash2.Size);

		Print(&m_listEkuModuleInfo,  "\n");
		Print(&m_listEkuModuleInfo, "EKU MODULE INFO (EKU)");
		Print(&m_listEkuModuleInfo, "------------------------");
		Print(&m_listEkuModuleInfo, "LAST RECORD");
		Print(&m_listEkuModuleInfo, "  ZNO       : %04d",	pstEkuModuleInfo->Eku.LastRecord.ZNo);
		Print(&m_listEkuModuleInfo, "  FNO       : %04d",	pstEkuModuleInfo->Eku.LastRecord.FNo);
		Print(&m_listEkuModuleInfo, "  TYPE      : %04d",	pstEkuModuleInfo->Eku.LastRecord.Type);
		Print(&m_listEkuModuleInfo, "  DATETIME  : %08X",	pstEkuModuleInfo->Eku.LastRecord.DateTime);
		Print(&m_listEkuModuleInfo, "  STATUS    : %04X",	pstEkuModuleInfo->Eku.LastRecord.Status);
		Print(&m_listEkuModuleInfo, "\n");
		Print(&m_listEkuModuleInfo, "CAPACITY");
		Print(&m_listEkuModuleInfo, "  DATA USED : %08d bytes"	,	pstEkuModuleInfo->Eku.DataUsedArea);
		Print(&m_listEkuModuleInfo, "  DATA FREE : %08d bytes"	,	pstEkuModuleInfo->Eku.DataFreeArea);
		Print(&m_listEkuModuleInfo, "  HEADR USED: %02d"		,	pstEkuModuleInfo->Eku.HeaderUsed);
		Print(&m_listEkuModuleInfo, "  HEADR FREE: %02d"		,	pstEkuModuleInfo->Eku.HeaderTotal - pstEkuModuleInfo->Eku.HeaderUsed);

	}

	return retcode;
}

int CEkuDlg::PrintHeader(ST_EKU_APPINF *pstEKUAppInfo)
{
	int retcode = TRAN_RESULT_OK;

	if (pstEkuModuleInfo == NULL)
		retcode = LoadEkuModuleInfo();
	if (retcode != TRAN_RESULT_OK)
		return retcode;

	if (pstEkuHeader == NULL)
		retcode = LoadEkuHeader();
	if (retcode != TRAN_RESULT_OK)
		return retcode;

	CTime time = CTime::GetCurrentTime();
	CString strDate;
	CString strTime;

	strDate.Format(L"TARÝH      : %s", time.Format("%x"));
	strTime.Format(L"SAAT       : %s", time.Format("%X"));

	Print(&m_listPrinter,  "------------------------");
	Print(&m_listPrinter,  "       EKU DÖKÜMÜ       ");
	Print(&m_listPrinter,  "------------------------");
	Print(&m_listPrinter,  "Z RAPOR NO : %d", pstEKUAppInfo->ZNo);
	Print(&m_listPrinter,  "FIS NO     : %d", pstEKUAppInfo->FNo);
	Print(&m_listPrinter, CT2A((LPCTSTR)(strDate)));
	Print(&m_listPrinter, CT2A((LPCTSTR)(strTime)));
	Print(&m_listPrinter,  "FÝÞ TÝPÝ   : %d", pstEKUAppInfo->Type);
	Print(&m_listPrinter,  "------------------------");
	Print(&m_listPrinter,  " ");

	return retcode;
}

int CEkuDlg::ReadData(void)
{
	int retcode = TRAN_RESULT_OK;
	uint8 EkuDataBuffer[32*1024];		// Gelen fiþ çok büyük olabilir!!!
	uint16 EkuDataBufferLen = 0;
	uint16 EkuDataSavedLen = 0;
	int index;

	memset(EkuDataBuffer, 0x00, sizeof(EkuDataBuffer));

	do
	{
		stEKUAppInfo.Buffer = &EkuDataBuffer[EkuDataSavedLen];
		stEKUAppInfo.BufLen = sizeof(EkuDataBuffer) - EkuDataSavedLen;

		retcode = FP3_FunctionEkuReadData(m_hInt, &EkuDataBufferLen, &stEKUAppInfo, TIMEOUT_DEFAULT);
		EkuDataSavedLen += EkuDataBufferLen;

		if (stEKUAppInfo.RemLen > 0xF000)
		{
			retcode = stEKUAppInfo.RemLen;
			break;
		}

	}
	while (stEKUAppInfo.RemLen && (retcode == TRAN_RESULT_OK) && (EkuDataSavedLen < sizeof(EkuDataBuffer)));

	if (retcode == TRAN_RESULT_OK)
	{
		PrintHeader(&stEKUAppInfo);

		for (index = 0; index < EkuDataSavedLen;)
		{
			char data[64+1];
			uint8 data2[65];
			uint16 flag;

			// flag
			memcpy(&flag, &EkuDataBuffer[index], 2);
			index += 2;

			// linelen
			int linelen = EkuDataBuffer[index++];
			if (linelen > sizeof(data) - 1)
				// hata...
				break;

			memset(data, 0, sizeof(data));
			memcpy(data, &EkuDataBuffer[index], linelen);
			index += linelen;

			if (flag & GMP3_PS_ECR_TICKET_HEADER)
			{
				char tmp[64];

				memset(tmp, 0x00, sizeof(tmp));
				memcpy(tmp,  &pstEkuHeader->MerchantName[0], 32);
				((CePosDlg*)GetParent())->PrintInfo(&m_listPrinter, GMP3_PS_CENTER | GMP3_PS_BOLD, tmp);
				memset(tmp, 0x00, sizeof(tmp));
				memcpy(tmp,  &pstEkuHeader->MerchantName[32], 32);
				((CePosDlg*)GetParent())->PrintInfo(&m_listPrinter, GMP3_PS_CENTER | GMP3_PS_BOLD, tmp);
				memset(tmp, 0x00, sizeof(tmp));
				memcpy(tmp,  &pstEkuHeader->MerchantAddress[0], 32);
				((CePosDlg*)GetParent())->PrintInfo(&m_listPrinter, GMP3_PS_CENTER | GMP3_PS_BOLD, tmp);
				memset(tmp, 0x00, sizeof(tmp));
				memcpy(tmp,  &pstEkuHeader->MerchantAddress[32], 32);
				((CePosDlg*)GetParent())->PrintInfo(&m_listPrinter, GMP3_PS_CENTER | GMP3_PS_BOLD, tmp);
				memset(tmp, 0x00, sizeof(tmp));
				memcpy(tmp,  &pstEkuHeader->MerchantAddress[64], 32);
				((CePosDlg*)GetParent())->PrintInfo(&m_listPrinter, GMP3_PS_CENTER | GMP3_PS_BOLD, tmp);
				memset(tmp, 0x00, sizeof(tmp));
				sprintf(tmp, "%s %s"	 , pstEkuHeader->VATOffice, pstEkuHeader->VATNumber);
				((CePosDlg*)GetParent())->PrintInfo(&m_listPrinter, GMP3_PS_CENTER | GMP3_PS_BOLD, tmp);
			}
			else if (flag & GMP3_PS_BARCODE)
			{
				;
			}
			else if (flag & GMP3_PS_GRAPHIC)
			{
				;
			}
			else if (flag & GMP3_PS_UNIQUE_ID)
			{
				char UniqueID[100];
				int i;
				memset(UniqueID, 0, 100);
				memcpy(data2, data, 65);

				for (i = 0; i < 32; i++)
				{
					sprintf(&UniqueID[2*i], "%02X", data2[i]);

				}

				((CePosDlg*)GetParent())->PrintInfo(&m_listPrinter, GMP3_PS_BOLD | GMP3_PS_32, UniqueID);
			}
			else
			{
				((CePosDlg*)GetParent())->PrintInfo(&m_listPrinter, flag, data);
			}
		}
	}
	return retcode;
}

BOOL CEkuDlg::DestroyWindow()
{
	delete myFont;

	if (pstEkuModuleInfo)
		delete pstEkuModuleInfo;

	if (pstEkuHeader)
		delete pstEkuHeader;

	return CDialogEx::DestroyWindow();
}


void CEkuDlg::OnBnClickedButtonClear()
{
	m_listPrinter.ResetContent();
}


void CEkuDlg::OnBnClickedButtonSearchByZnoFno()
{
	UpdateData(true);

	int retcode = TRAN_RESULT_OK;

	memset(&stEKUAppInfo, 0x00, sizeof(stEKUAppInfo));

	stEKUAppInfo.ZNo	= (unsigned short)m_ZNoStart;
	stEKUAppInfo.FNo	= (unsigned short)m_FNoStart;
	stEKUAppInfo.Type	= EKU_SEEK_MODE_ALL_TYPE;

	retcode = FP3_FunctionEkuSeek(m_hInt, &stEKUAppInfo, TIMEOUT_DEFAULT);
	if (retcode == TRAN_RESULT_OK)
		retcode = ReadData();

	if (retcode != TRAN_RESULT_OK)
		DisplayError(retcode);
}


void CEkuDlg::OnBnClickedButtonSearchByDateTime()
{
	UpdateData(true);

	int retcode = TRAN_RESULT_OK;
	int i;

	memset(&stEKUAppInfo, 0x00, sizeof(stEKUAppInfo));

	stEKUAppInfo.Type	= EKU_SEEK_MODE_ALL_TYPE;

	// YMDHMS as bcd
	i = 0;
	LongToBcd(m_DateStart.GetYear() - 2000	, &stEKUAppInfo.DateTime[i++], 1);
	LongToBcd(m_DateStart.GetMonth()		, &stEKUAppInfo.DateTime[i++], 1);
	LongToBcd(m_DateStart.GetDay()			, &stEKUAppInfo.DateTime[i++], 1);
	LongToBcd(m_TimeStart.GetHour()		, &stEKUAppInfo.DateTime[i++], 1);
	LongToBcd(m_TimeStart.GetMinute()		, &stEKUAppInfo.DateTime[i++], 1);
	LongToBcd(m_TimeStart.GetSecond()		, &stEKUAppInfo.DateTime[i++], 1);

	// YMDHMS as bcd
	i = 0;
	LongToBcd(m_DateEnd.GetYear() - 2000		, &stEKUAppInfo.DateTimeDelta[i++], 1);
	LongToBcd(m_DateEnd.GetMonth()			, &stEKUAppInfo.DateTimeDelta[i++], 1);
	LongToBcd(m_DateEnd.GetDay()			, &stEKUAppInfo.DateTimeDelta[i++], 1);
	LongToBcd(m_TimeEnd.GetHour()			, &stEKUAppInfo.DateTimeDelta[i++], 1);
	LongToBcd(m_TimeEnd.GetMinute()		, &stEKUAppInfo.DateTimeDelta[i++], 1);
	LongToBcd(m_TimeEnd.GetSecond()		, &stEKUAppInfo.DateTimeDelta[i++], 1);

	retcode = FP3_FunctionEkuSeek(m_hInt, &stEKUAppInfo, TIMEOUT_DEFAULT);
	if (retcode == TRAN_RESULT_OK)
		retcode = ReadData();

	if (retcode != TRAN_RESULT_OK)
		DisplayError(retcode);
}

void CEkuDlg::DisplayError(int retcode)
{
	char ErrorString[128];
	GetErrorMessage(retcode, ErrorString);
	CString cs = CString(ErrorString);
	MessageBox(cs, L"Return Code", MB_OK);
}


void CEkuDlg::OnBnClickedButtonReadModuleInfo()
{
	int retcode = TRAN_RESULT_OK;

	if (pstEkuModuleInfo == NULL)
		retcode = LoadEkuModuleInfo();
	if (retcode != TRAN_RESULT_OK)
		DisplayError(retcode);
}


void CEkuDlg::OnBnClickedButtonReadHeader()
{
	int retcode = TRAN_RESULT_OK;

	if (pstEkuHeader == NULL)
		retcode = LoadEkuHeader();
	if (retcode != TRAN_RESULT_OK)
		DisplayError(retcode);
}

void CEkuDlg::OnBnClickedButtonEkuPing()
{
	int retcode = TRAN_RESULT_OK;
	retcode = FP3_FunctionEkuPing(m_hInt, TIMEOUT_DEFAULT);
	DisplayError(retcode);
}

void CEkuDlg::OnBnClickedButtonEkuPresent()
{
}

void CEkuDlg::OnBnClickedButtonEkuReset()
{
}


void CEkuDlg::OnBnClickedButtonReadDataNext()
{
	m_listPrinter.ResetContent();

	int retcode = TRAN_RESULT_OK;
	retcode = ReadData();
	if (retcode != TRAN_RESULT_OK)
		DisplayError(retcode);
}
