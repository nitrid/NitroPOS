#pragma once
#include "afxwin.h"
#include "GmpSmartDll.h"


// CUserMessageDlg dialog

class CUserMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserMessageDlg)

public:
	CUserMessageDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserMessageDlg();

// Dialog Data
	enum { IDD = IDD_USER_MESSAGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HINT m_hInt;
	int numberOfUserMessages;
	ST_USER_MESSAGE stUserMeessage[40];
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadioText();
	CButton m_rtext;
	CButton m_rbarcode;
	CButton m_rqrcode;
	afx_msg void OnBnClickedRadioBarcode();
	afx_msg void OnBnClickedRadioQrcode();
	CButton m_f12;
	CButton m_f24;
	CButton m_f32;
	CButton m_f42;
	afx_msg void OnBnClickedRadioFont12();
	afx_msg void OnBnClickedRadioFont24();
	afx_msg void OnBnClickedRadioFont32();
	afx_msg void OnBnClickedRadioFont42();
	CButton m_bold;
	CButton m_inverted;
	CButton m_left;
	CButton m_center;
	CButton m_right;
	afx_msg void OnBnClickedRadioBold();
	afx_msg void OnBnClickedRadioInverted();
	afx_msg void OnBnClickedRadioLeft();
	afx_msg void OnBnClickedRadioCenter();
	afx_msg void OnBnClickedRadioRight();
	CButton m_normal;
	afx_msg void OnBnClickedRadioNormal();
	virtual BOOL OnInitDialog();
	CString m_EditUserMessage;
	CListBox m_listUserMessage;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonFiledirBitmap();
	CButton m_ButtonFiledirBitmap;
	CButton m_graphic;
	afx_msg void OnBnClickedRadioGraphic();
	CListBox m_ListBitmapFiles;
	afx_msg void OnBnClickedButtonDownloadFile();
	char m_FileDirBitmap[128];
	void DownloadBitmapFile(char* hostPathName, char* fileName);
	int ListBitmapFiles(char* FileDirBitmap);
	afx_msg void OnBnClickedButtonRemoveFile();
	CButton m_f16;
	CButton m_f38;
	afx_msg void OnBnClickedRadioFont16();
	afx_msg void OnBnClickedRadioFont38();
};
