#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "sqlite3.h"
#include "GMPSmartDLL.h"


// CPluConsoleDlg dialog

class CPluConsoleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPluConsoleDlg)

public:
	CPluConsoleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPluConsoleDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PLU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HINT m_hInt;
	char	m_PluDbName[64];
	int		m_PluDbSize;
	void ResizeControls(void);
	CString GetHeaderName(CListCtrl* plist, int col);
	void DisplayError(int retcode);
	CString GetDeleteString(CListCtrl* plist, int nItem);
	CString GetUpdateString(CListCtrl* plistCtrl, int nItem);
	int UpdatePluGrups(CListCtrl* plist, int pluGrupParent);
	int UpdatePluItems(CListCtrl* plist, int pluGrupParent);
	virtual BOOL OnInitDialog();
	CListCtrl m_listECRPluGrups;
	CListCtrl m_listECRPluGrup2;
	afx_msg void OnDblclkListPluGrup(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listECRPluItems;
	afx_msg void OnDblclkListPluGrup2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListPluGrup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnPopupMenuInsertnew();
	char* GetSelectedHostFileName();
	int m_popupMenuActiveControl;
	afx_msg void OnClickListPluGrup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListPluGrup2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListPluItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPopupMenuUpdate();
	afx_msg void OnPopupMenuDelete();
	afx_msg void OnRclickListPluGrup2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListPluItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	CListCtrl m_listHostPluGrups;
	CListCtrl m_listHostPluGrup2;
	CListCtrl m_listHostPluItems;
	CButton m_buttonUploadFull;
	afx_msg void OnBnClickedButtonUploadFull();
	int CreateDatabase(sqlite3* db, char* m_PluDbName);
	int CPluConsoleDlg::UpdateHostDbFiles(void);
	CListBox m_listHostDbFiles;
	CEdit m_EditHostPath;
	afx_msg void OnChangeEditHostPath();
	CButton m_buttonDownloadFull;
	afx_msg void OnBnClickedButtonDownloadFull();
	void RefreshEcrPluDbFileName();
	CListBox m_listEcrPluFileName;
	afx_msg void OnDblclkListEcrDbFile();
	afx_msg void OnDblclkListHostDbFiles();
	int UpdateHostPluGrups(char* FileName, CListCtrl* plist, int pluGrupParent);
	int FillListControlFromHostDB(char* dbName, CListCtrl* plistCtrl, char* swlWord);
	afx_msg void OnDblclkListHostPluGrup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListHostPluGrup2(NMHDR *pNMHDR, LRESULT *pResult);
	int UpdateHostPluItems(char* filename, CListCtrl* plist, int pluGrupParent);
	afx_msg void OnBnClickedButtonRefreshPluDbInfo();
	CButton m_buttonRefreshEcrPluDbInfo;
	uint32 GetMax_LastModified(char* filename, char* TableName);
	afx_msg void OnRclickListHostPluGrup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListHostPluGrup2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListHostPluItem(NMHDR *pNMHDR, LRESULT *pResult);
	int GetSelectedId_ECRGrup();
	int GetSelectedId_ECRGrup2();
	int GetSelectedId_HostGrup();
	int GetSelectedId_HostGrup2();
	afx_msg void OnClickListHostPluGrup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListHostPluGrup2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListHostPluItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeListHostDbFiles();
	afx_msg void OnLbnSelchangeListEcrDbFile();
	afx_msg void OnBnClickedButtonSelectHostDir();
	CButton m_ButtonSelectHostDir;
};
