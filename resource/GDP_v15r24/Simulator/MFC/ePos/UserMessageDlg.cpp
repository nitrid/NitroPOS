// UserMessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "UserMessageDlg.h"
#include "afxdialogex.h"


// CUserMessageDlg dialog

IMPLEMENT_DYNAMIC(CUserMessageDlg, CDialogEx)

CUserMessageDlg::CUserMessageDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CUserMessageDlg::IDD, pParent)
		, m_EditUserMessage(_T(""))
{
	numberOfUserMessages = 0;
	for (int i = 0; i < (sizeof(stUserMeessage) / sizeof(ST_USER_MESSAGE)); ++i)
	{
		memset(&stUserMeessage[i], 0x00, sizeof(ST_USER_MESSAGE));
		stUserMeessage[i].StructSize = sizeof(ST_USER_MESSAGE);
	}
}

CUserMessageDlg::~CUserMessageDlg()
{
}

void CUserMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_TEXT, m_rtext);
	DDX_Control(pDX, IDC_RADIO_BARCODE, m_rbarcode);
	DDX_Control(pDX, IDC_RADIO_QRCODE, m_rqrcode);
	DDX_Control(pDX, IDC_RADIO_FONT_12, m_f12);
	DDX_Control(pDX, IDC_RADIO_FONT_24, m_f24);
	DDX_Control(pDX, IDC_RADIO_FONT_32, m_f32);
	DDX_Control(pDX, IDC_RADIO_FONT_42, m_f42);
	DDX_Control(pDX, IDC_RADIO_BOLD, m_bold);
	DDX_Control(pDX, IDC_RADIO_INVERTED, m_inverted);
	DDX_Control(pDX, IDC_RADIO_LEFT, m_left);
	DDX_Control(pDX, IDC_RADIO_CENTER, m_center);
	DDX_Control(pDX, IDC_RADIO_RIGHT, m_right);
	DDX_Control(pDX, IDC_RADIO_NORMAL, m_normal);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_EditUserMessage);
	DDX_Control(pDX, IDC_LIST_USER_MESSAGES, m_listUserMessage);
	DDX_Control(pDX, IDC_BUTTON_FILEDIR_BITMAP, m_ButtonFiledirBitmap);
	DDX_Control(pDX, IDC_RADIO_GRAPHIC, m_graphic);
	DDX_Control(pDX, IDC_LIST_BITMAP_FILES, m_ListBitmapFiles);
	DDX_Control(pDX, IDC_RADIO_FONT_16, m_f16);
	DDX_Control(pDX, IDC_RADIO_FONT_38, m_f38);
}


BEGIN_MESSAGE_MAP(CUserMessageDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserMessageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_TEXT, &CUserMessageDlg::OnBnClickedRadioText)
	ON_BN_CLICKED(IDC_RADIO_BARCODE, &CUserMessageDlg::OnBnClickedRadioBarcode)
	ON_BN_CLICKED(IDC_RADIO_QRCODE, &CUserMessageDlg::OnBnClickedRadioQrcode)
	ON_BN_CLICKED(IDC_RADIO_FONT_12, &CUserMessageDlg::OnBnClickedRadioFont12)
	ON_BN_CLICKED(IDC_RADIO_FONT_24, &CUserMessageDlg::OnBnClickedRadioFont24)
	ON_BN_CLICKED(IDC_RADIO_FONT_32, &CUserMessageDlg::OnBnClickedRadioFont32)
	ON_BN_CLICKED(IDC_RADIO_FONT_42, &CUserMessageDlg::OnBnClickedRadioFont42)
	ON_BN_CLICKED(IDC_RADIO_BOLD, &CUserMessageDlg::OnBnClickedRadioBold)
	ON_BN_CLICKED(IDC_RADIO_INVERTED, &CUserMessageDlg::OnBnClickedRadioInverted)
	ON_BN_CLICKED(IDC_RADIO_LEFT, &CUserMessageDlg::OnBnClickedRadioLeft)
	ON_BN_CLICKED(IDC_RADIO_CENTER, &CUserMessageDlg::OnBnClickedRadioCenter)
	ON_BN_CLICKED(IDC_RADIO_RIGHT, &CUserMessageDlg::OnBnClickedRadioRight)
	ON_BN_CLICKED(IDC_RADIO_NORMAL, &CUserMessageDlg::OnBnClickedRadioNormal)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CUserMessageDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_FILEDIR_BITMAP, &CUserMessageDlg::OnBnClickedButtonFiledirBitmap)
	ON_BN_CLICKED(IDC_RADIO_GRAPHIC, &CUserMessageDlg::OnBnClickedRadioGraphic)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD_FILE, &CUserMessageDlg::OnBnClickedButtonDownloadFile)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_FILE, &CUserMessageDlg::OnBnClickedButtonRemoveFile)
	ON_BN_CLICKED(IDC_RADIO_FONT_16, &CUserMessageDlg::OnBnClickedRadioFont16)
	ON_BN_CLICKED(IDC_RADIO_FONT_38, &CUserMessageDlg::OnBnClickedRadioFont38)
END_MESSAGE_MAP()


// CUserMessageDlg message handlers


void CUserMessageDlg::OnBnClickedOk()
{
	memset(&stUserMeessage, 0x00, sizeof(stUserMeessage));

	numberOfUserMessages = m_listUserMessage.GetCount();
	for (int i = 0; i < numberOfUserMessages; i++)
	{
		CString cs ;
		m_listUserMessage.GetText(i, cs);

		stUserMeessage[i].len = cs.GetLength();
		memcpy(stUserMeessage[i].message, CT2A((LPCTSTR)cs), stUserMeessage[i].len);
		stUserMeessage[i].flag = (uint16)m_listUserMessage.GetItemData(i);
	}

	CDialogEx::OnOK();
}

void CUserMessageDlg::OnBnClickedRadioText()
{
	m_rtext.SetCheck(true);
	m_rbarcode.SetCheck(false);
	m_rqrcode.SetCheck(false);
	m_graphic.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioBarcode()
{
	m_rtext.SetCheck(false);
	m_rbarcode.SetCheck(true);
	m_rqrcode.SetCheck(false);
	m_graphic.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioQrcode()
{
	m_rtext.SetCheck(false);
	m_rbarcode.SetCheck(false);
	m_rqrcode.SetCheck(true);
	m_graphic.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioGraphic()
{
	m_rtext.SetCheck(false);
	m_rbarcode.SetCheck(false);
	m_rqrcode.SetCheck(false);
	m_graphic.SetCheck(true);
}

void CUserMessageDlg::OnBnClickedRadioFont12()
{
	m_f12.SetCheck(true);
	m_f16.SetCheck(false);
	m_f24.SetCheck(false);
	m_f32.SetCheck(false);
	m_f38.SetCheck(false);
	m_f42.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioFont16()
{
	m_f12.SetCheck(false);
	m_f16.SetCheck(true);
	m_f24.SetCheck(false);
	m_f32.SetCheck(false);
	m_f38.SetCheck(false);
	m_f42.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioFont24()
{
	m_f12.SetCheck(false);
	m_f16.SetCheck(false);
	m_f24.SetCheck(true);
	m_f32.SetCheck(false);
	m_f38.SetCheck(false);
	m_f42.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioFont32()
{
	m_f12.SetCheck(false);
	m_f16.SetCheck(false);
	m_f24.SetCheck(false);
	m_f32.SetCheck(true);
	m_f38.SetCheck(false);
	m_f42.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioFont38()
{
	m_f12.SetCheck(false);
	m_f16.SetCheck(false);
	m_f24.SetCheck(false);
	m_f32.SetCheck(false);
	m_f38.SetCheck(true);
	m_f42.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioFont42()
{
	m_f12.SetCheck(false);
	m_f16.SetCheck(false);
	m_f24.SetCheck(false);
	m_f32.SetCheck(false);
	m_f38.SetCheck(false);
	m_f42.SetCheck(true);
}

void CUserMessageDlg::OnBnClickedRadioNormal()
{
	m_normal.SetCheck(true);
	m_bold.SetCheck(false);
	m_inverted.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioBold()
{
	m_normal.SetCheck(false);
	m_bold.SetCheck(true);
	m_inverted.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioInverted()
{
	m_normal.SetCheck(false);
	m_bold.SetCheck(false);
	m_inverted.SetCheck(true);
}


void CUserMessageDlg::OnBnClickedRadioLeft()
{
	m_left.SetCheck(true);
	m_center.SetCheck(false);
	m_right.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioCenter()
{
	m_left.SetCheck(false);
	m_center.SetCheck(true);
	m_right.SetCheck(false);
}
void CUserMessageDlg::OnBnClickedRadioRight()
{
	m_left.SetCheck(false);
	m_center.SetCheck(false);
	m_right.SetCheck(true);
}


BOOL CUserMessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_rtext.SetCheck(true);
	m_f24.SetCheck(true);
	m_normal.SetCheck(true);
	m_left.SetCheck(true);

	memset(m_FileDirBitmap, 0x00, sizeof(m_FileDirBitmap));
	memset(stUserMeessage, 0x00, 40 * sizeof(ST_USER_MESSAGE));

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CUserMessageDlg::OnBnClickedButtonAdd()
{

	UpdateData(true);
	unsigned long flag = 0;

	if (m_EditUserMessage.GetLength() > 48)
	{
		MessageBox(L"Mesaj Alaný 48 karakterden fazla olamaz", L"HATA", MB_OK);
		return;
	}

	if (m_rqrcode.GetCheck())
		flag |= GMP3_PS_QRCODE;
	else if (m_rbarcode.GetCheck())
		flag |= GMP3_PS_BARCODE;
	else if (m_graphic.GetCheck())
	{
		int selected = m_ListBitmapFiles.GetCurSel();
		if (m_EditUserMessage.GetLength() > 0)
		{
			flag |= GMP3_PS_GRAPHIC;
		}
		else
		{
			CString csFileName;
			m_ListBitmapFiles.GetText(selected, csFileName);
			csFileName = csFileName.Left(csFileName.Find(' ', 0));

			flag |= GMP3_PS_GRAPHIC;
			m_EditUserMessage.Format(L"%s%c%s", CString(m_FileDirBitmap), 47, csFileName);
		}
	}

	if (m_f12.GetCheck())				flag |= GMP3_PS_12;
	else if (m_f16.GetCheck())			flag |= GMP3_PS_16;
	else if (m_f24.GetCheck())			flag |= GMP3_PS_24;
	else if (m_f32.GetCheck())			flag |= GMP3_PS_32;
	else if (m_f38.GetCheck())			flag |= GMP3_PS_38;
	else if (m_f42.GetCheck())			flag |= GMP3_PS_48;

	if (m_bold.GetCheck())				flag |= GMP3_PS_BOLD;
	else if (m_inverted.GetCheck())	flag |= GMP3_PS_INVERTED;

	if (m_center.GetCheck())			flag |= GMP3_PS_CENTER;
	else if (m_right.GetCheck())		flag |= GMP3_PS_RIGHT;

	int index = m_listUserMessage.AddString(m_EditUserMessage);
	m_listUserMessage.SetItemData(index, flag);
	m_EditUserMessage.Empty();

	UpdateData(false);
}

int CUserMessageDlg::ListBitmapFiles(char* FileDirBitmap)
{
	int retcode = TRAN_RESULT_OK;
	ST_FILE stFiles[64];
	uint16 numberOfFiles;
	memset(stFiles, 0x00, sizeof(stFiles));

	m_ListBitmapFiles.ResetContent();

	retcode = FP3_FileSystem_DirListFiles(m_hInt, FileDirBitmap, stFiles, 64, &numberOfFiles);
	if (retcode != TRAN_RESULT_OK)
		return retcode;

	for (int i = 0; i < numberOfFiles; i++)
	{
		CString cs;
		cs.Format(L"%s %ld", CString(stFiles[i].fileName), stFiles[i].fileSize);
		m_ListBitmapFiles.AddString(cs);
	}

	return retcode;
}

void CUserMessageDlg::OnBnClickedButtonFiledirBitmap()
{
	int retcode;
	uint16 len = 0;

	OnBnClickedRadioGraphic();

	memset(m_FileDirBitmap, 0x00, sizeof(m_FileDirBitmap));

	m_ListBitmapFiles.ResetContent();

	//retcode = FP3_GetTlvData( m_hInt, GMP_EXT_DEVICE_FILEDIR_BITMAP, (uint8*)m_FileDirBitmap, sizeof(m_FileDirBitmap)-1, &len );
	//if( retcode != TRAN_RESULT_OK )
	//	goto Exit;

	strcpy(m_FileDirBitmap, "/HOST");

	m_ButtonFiledirBitmap.SetWindowText(CString(m_FileDirBitmap));

	retcode = FP3_FileSystem_DirChange(m_hInt, m_FileDirBitmap);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	retcode = ListBitmapFiles(m_FileDirBitmap);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

Exit:
	if (retcode != TRAN_RESULT_OK)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox(CString(ErrorString), L"Error", MB_OK);
	}
}

void CUserMessageDlg::OnBnClickedButtonDownloadFile()
{
	int retcode = TRAN_RESULT_OK;
	uint16 len = 0;
	//CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Bitmap Files (*.bmp)|*.bmp|") );

	char hostPath[] = "/HOST";

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Bitmap Files (*)|*|"));

	OnBnClickedRadioGraphic();

	if (!strlen(m_FileDirBitmap))
	{
		//retcode = FP3_GetTlvData( m_hInt, GMP_EXT_DEVICE_FILEDIR_BITMAP, (uint8*)m_FileDirBitmap, sizeof(m_FileDirBitmap)-1, &len );
		//if( retcode != TRAN_RESULT_OK )
		//	goto Exit;
		strcpy(m_FileDirBitmap, hostPath);
		m_ButtonFiledirBitmap.SetWindowText(CString(m_FileDirBitmap));
	}

	if (fileDlg.DoModal() == IDOK)
	{
		retcode = FP3_FileSystem_DirChange(m_hInt, m_FileDirBitmap);
		if (retcode != TRAN_RESULT_OK)
			goto Exit;

		char ecrFullPath[128];
		memset(ecrFullPath, 0x00, sizeof(ecrFullPath));
		strcpy(ecrFullPath, m_FileDirBitmap);
		strcat(ecrFullPath, "/");
		strcat(ecrFullPath, CT2A((LPCTSTR)fileDlg.GetFileName()));
		DownloadBitmapFile(CT2A((LPCTSTR)fileDlg.GetPathName()), ecrFullPath);

		retcode = ListBitmapFiles(m_FileDirBitmap);
		if (retcode != TRAN_RESULT_OK)
			goto Exit;
	}

Exit:
	if (retcode != TRAN_RESULT_OK)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox(CString(ErrorString), L"Error", MB_OK);
	}
}

void CUserMessageDlg::DownloadBitmapFile(char* hostPathName, char* fileName)
{
	int retcode = TRAN_RESULT_OK;

	CString csFileNamePlu;
	FILE* pFileHost = NULL;
	if (!strlen(hostPathName))
		return;

	pFileHost = fopen(hostPathName, "rb");
	if (pFileHost == NULL)
	{
		MessageBox(L"File can not opened in Host Computer", L"fopen", MB_OK);
		goto Exit;
	}

	fseek(pFileHost , 0 , SEEK_END);
	long HostFileSize = ftell(pFileHost);
	fseek(pFileHost , 0 , SEEK_SET);

	retcode = FP3_FileSystem_FileRemove(m_hInt, fileName);
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	int ReadLen = 0;
	byte buffer[1024];
	int offset = 0;
	while (1)
	{
		ReadLen = (int)fread(buffer, 1, sizeof(buffer), pFileHost);
		if (ReadLen == 0)
			goto Exit;

		do
		{
			retcode = FP3_FileSystem_FileWrite(m_hInt, fileName, offset, FS_SEEKSET, buffer, ReadLen);
			if (retcode == DLL_RETCODE_RECV_BUSY)
				Sleep(1000);
		}
		while (retcode == DLL_RETCODE_RECV_BUSY);

		if (retcode != TRAN_RESULT_OK)
			goto Exit;

		offset += ReadLen;

		if (HostFileSize)
		{
			CString cs;
			cs.Format(L"Download Status %%%d", (offset*100) / HostFileSize);
			SetWindowTextW(cs);
		}
	}

Exit:
	SetWindowTextW(L"User Message");

	if (pFileHost)
		fclose(pFileHost);
	pFileHost = NULL;

	if (retcode)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox((CString) ErrorString, L"Return Code", MB_OK);
	}
}

void CUserMessageDlg::OnBnClickedButtonRemoveFile()
{
	int retcode = TRAN_RESULT_OK;
	uint16 len = 0;
	CString fileNameTobeRemoved;
	CString csFileName;

	OnBnClickedRadioGraphic();

	int selected = m_ListBitmapFiles.GetCurSel();
	if (selected < 0)
		return;

	if (!strlen(m_FileDirBitmap))
	{
		retcode = FP3_GetTlvData(m_hInt, GMP_EXT_DEVICE_FILEDIR_BITMAP, (uint8*)m_FileDirBitmap, sizeof(m_FileDirBitmap) - 1, &len);
		if (retcode != TRAN_RESULT_OK)
			goto Exit;
		m_ButtonFiledirBitmap.SetWindowText(CString(m_FileDirBitmap));
	}

	m_ListBitmapFiles.GetText(selected, csFileName);
	csFileName = csFileName.Left(csFileName.Find(' ', 0));

	fileNameTobeRemoved.Format(L"%s%c%s", CString(m_FileDirBitmap), 47, csFileName);

	retcode = FP3_FileSystem_FileRemove(m_hInt, CT2A((LPCTSTR)fileNameTobeRemoved));
	if (retcode != TRAN_RESULT_OK)
		goto Exit;

	ListBitmapFiles(m_FileDirBitmap);

Exit:
	if (retcode != TRAN_RESULT_OK)
	{
		char ErrorString[128];
		GetErrorMessage(retcode, ErrorString);
		MessageBox(CString(ErrorString), L"Error", MB_OK);
	}

}
