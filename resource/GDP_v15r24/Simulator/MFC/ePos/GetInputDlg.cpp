// GetInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "GetInputDlg.h"
#include "afxdialogex.h"


// CGetInputDlg dialog

IMPLEMENT_DYNAMIC(CGetInputDlg, CDialogEx)

CGetInputDlg::CGetInputDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CGetInputDlg::IDD, pParent)
		, m_numberOfmultipleFlags(0)
		, m_flagValue(0)
{

}

CGetInputDlg::~CGetInputDlg()
{
}

void CGetInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_EditInput);
	DDX_Control(pDX, IDC_EDIT_LABEL, m_EditLabel);
}

#define IDC_CHECKBOX_START(i) (8000+i)

BEGIN_MESSAGE_MAP(CGetInputDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetInputDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECKBOX_START(1) , &CGetInputDlg::OnBnClickedCheckBox1)
	ON_BN_CLICKED(IDC_CHECKBOX_START(2) , &CGetInputDlg::OnBnClickedCheckBox2)
	ON_BN_CLICKED(IDC_CHECKBOX_START(3) , &CGetInputDlg::OnBnClickedCheckBox3)
	ON_BN_CLICKED(IDC_CHECKBOX_START(4) , &CGetInputDlg::OnBnClickedCheckBox4)
	ON_BN_CLICKED(IDC_CHECKBOX_START(5) , &CGetInputDlg::OnBnClickedCheckBox5)
	ON_BN_CLICKED(IDC_CHECKBOX_START(6) , &CGetInputDlg::OnBnClickedCheckBox6)
	ON_BN_CLICKED(IDC_CHECKBOX_START(7) , &CGetInputDlg::OnBnClickedCheckBox7)
	ON_BN_CLICKED(IDC_CHECKBOX_START(8) , &CGetInputDlg::OnBnClickedCheckBox8)
	ON_BN_CLICKED(IDC_CHECKBOX_START(9) , &CGetInputDlg::OnBnClickedCheckBox9)
	ON_BN_CLICKED(IDC_CHECKBOX_START(10), &CGetInputDlg::OnBnClickedCheckBox10)
	ON_BN_CLICKED(IDC_CHECKBOX_START(11), &CGetInputDlg::OnBnClickedCheckBox11)
	ON_BN_CLICKED(IDC_CHECKBOX_START(12), &CGetInputDlg::OnBnClickedCheckBox12)
	ON_BN_CLICKED(IDC_CHECKBOX_START(13), &CGetInputDlg::OnBnClickedCheckBox13)
	ON_BN_CLICKED(IDC_CHECKBOX_START(14), &CGetInputDlg::OnBnClickedCheckBox14)
	ON_BN_CLICKED(IDC_CHECKBOX_START(15), &CGetInputDlg::OnBnClickedCheckBox15)
	ON_BN_CLICKED(IDC_CHECKBOX_START(16), &CGetInputDlg::OnBnClickedCheckBox16)
	ON_BN_CLICKED(IDC_CHECKBOX_START(17), &CGetInputDlg::OnBnClickedCheckBox17)
	ON_BN_CLICKED(IDC_CHECKBOX_START(18), &CGetInputDlg::OnBnClickedCheckBox18)
	ON_BN_CLICKED(IDC_CHECKBOX_START(19), &CGetInputDlg::OnBnClickedCheckBox19)
	ON_BN_CLICKED(IDC_CHECKBOX_START(20), &CGetInputDlg::OnBnClickedCheckBox20)
	ON_BN_CLICKED(IDC_CHECKBOX_START(21), &CGetInputDlg::OnBnClickedCheckBox21)
	ON_BN_CLICKED(IDC_CHECKBOX_START(22), &CGetInputDlg::OnBnClickedCheckBox22)
	ON_BN_CLICKED(IDC_CHECKBOX_START(23), &CGetInputDlg::OnBnClickedCheckBox23)
	ON_BN_CLICKED(IDC_CHECKBOX_START(24), &CGetInputDlg::OnBnClickedCheckBox24)
	ON_BN_CLICKED(IDC_CHECKBOX_START(25), &CGetInputDlg::OnBnClickedCheckBox25)
	ON_BN_CLICKED(IDC_CHECKBOX_START(26), &CGetInputDlg::OnBnClickedCheckBox26)
	ON_BN_CLICKED(IDC_CHECKBOX_START(27), &CGetInputDlg::OnBnClickedCheckBox27)
	ON_BN_CLICKED(IDC_CHECKBOX_START(28), &CGetInputDlg::OnBnClickedCheckBox28)
	ON_BN_CLICKED(IDC_CHECKBOX_START(29), &CGetInputDlg::OnBnClickedCheckBox29)
	ON_BN_CLICKED(IDC_CHECKBOX_START(30), &CGetInputDlg::OnBnClickedCheckBox30)
	ON_BN_CLICKED(IDC_CHECKBOX_START(31), &CGetInputDlg::OnBnClickedCheckBox31)
	ON_BN_CLICKED(IDC_CHECKBOX_START(32), &CGetInputDlg::OnBnClickedCheckBox32)
END_MESSAGE_MAP()


// CGetInputDlg message handlers
void CGetInputDlg::OnBnClickedOk()
{
	m_EditInput.GetWindowText(m_input);
	CDialogEx::OnOK();
}

void CGetInputDlg::CheckBox(int item)
{
	int i = item - 1;

	if (m_type == 4)
	{
		m_flagValue = 0x00;
		for (int t = 0; t < m_numberOfmultipleFlags; t++)
			m_checkBox[t].SetCheck(false);
	}

	m_checkBox[i].SetCheck(!m_checkBox[i].GetCheck());

	if (m_checkBox[i].GetCheck())
		m_flagValue |= m_multipleFlags[i].flagValue;
	else
		m_flagValue &= ~m_multipleFlags[i].flagValue;
}

void CGetInputDlg::OnBnClickedCheckBox1()
{
	CheckBox(1);
}
void CGetInputDlg::OnBnClickedCheckBox2()
{
	CheckBox(2);
}
void CGetInputDlg::OnBnClickedCheckBox3()
{
	CheckBox(3);
}
void CGetInputDlg::OnBnClickedCheckBox4()
{
	CheckBox(4);
}
void CGetInputDlg::OnBnClickedCheckBox5()
{
	CheckBox(5);
}
void CGetInputDlg::OnBnClickedCheckBox6()
{
	CheckBox(6);
}
void CGetInputDlg::OnBnClickedCheckBox7()
{
	CheckBox(7);
}
void CGetInputDlg::OnBnClickedCheckBox8()
{
	CheckBox(8);
}
void CGetInputDlg::OnBnClickedCheckBox9()
{
	CheckBox(9);
}
void CGetInputDlg::OnBnClickedCheckBox10()
{
	CheckBox(10);
}
void CGetInputDlg::OnBnClickedCheckBox11()
{
	CheckBox(11);
}
void CGetInputDlg::OnBnClickedCheckBox12()
{
	CheckBox(12);
}
void CGetInputDlg::OnBnClickedCheckBox13()
{
	CheckBox(13);
}
void CGetInputDlg::OnBnClickedCheckBox14()
{
	CheckBox(14);
}
void CGetInputDlg::OnBnClickedCheckBox15()
{
	CheckBox(15);
}
void CGetInputDlg::OnBnClickedCheckBox16()
{
	CheckBox(16);
}
void CGetInputDlg::OnBnClickedCheckBox17()
{
	CheckBox(17);
}
void CGetInputDlg::OnBnClickedCheckBox18()
{
	CheckBox(18);
}
void CGetInputDlg::OnBnClickedCheckBox19()
{
	CheckBox(19);
}
void CGetInputDlg::OnBnClickedCheckBox20()
{
	CheckBox(20);
}
void CGetInputDlg::OnBnClickedCheckBox21()
{
	CheckBox(21);
}
void CGetInputDlg::OnBnClickedCheckBox22()
{
	CheckBox(22);
}
void CGetInputDlg::OnBnClickedCheckBox23()
{
	CheckBox(23);
}
void CGetInputDlg::OnBnClickedCheckBox24()
{
	CheckBox(24);
}
void CGetInputDlg::OnBnClickedCheckBox25()
{
	CheckBox(25);
}
void CGetInputDlg::OnBnClickedCheckBox26()
{
	CheckBox(26);
}
void CGetInputDlg::OnBnClickedCheckBox27()
{
	CheckBox(27);
}
void CGetInputDlg::OnBnClickedCheckBox28()
{
	CheckBox(28);
}
void CGetInputDlg::OnBnClickedCheckBox29()
{
	CheckBox(29);
}
void CGetInputDlg::OnBnClickedCheckBox30()
{
	CheckBox(30);
}
void CGetInputDlg::OnBnClickedCheckBox31()
{
	CheckBox(31);
}
void CGetInputDlg::OnBnClickedCheckBox32()
{
	CheckBox(32);
}


void CGetInputDlg::InsertFlag(CString caption, unsigned  long long flagValue, bool defaultValue)
{
	if (m_numberOfmultipleFlags >= MAX_NUMBER_OF_FLAG)
		return;

	m_multipleFlags[m_numberOfmultipleFlags].caption = caption;
	m_multipleFlags[m_numberOfmultipleFlags].flagValue = flagValue;
	m_multipleFlags[m_numberOfmultipleFlags].defaultValue = defaultValue;

	m_numberOfmultipleFlags++;
}

INT_PTR CGetInputDlg::DoModal(CString caption, CString Input, int type)
{
	m_caption = caption;
	m_input = Input;
	m_type = type;
	// types...
	// 1: ALPHANUM
	// 2: NUMERIC
	// 3: MULTIBLE SELECTION, SET OF FLAGS, OPTION FLAGS
	// 4: SINGLE SELECTION FLAG
	return CDialogEx::DoModal();
}

BOOL CGetInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	myFont = new CFont();

	myFont->CreateFont(32, 0, 0, 0, FW_HEAVY, false, false,
					   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					   FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));

	m_EditInput.SetFont(myFont, true);
	m_EditLabel.SetFont(myFont, true);

	m_EditInput.SetWindowTextW(m_input);
	m_EditLabel.SetWindowTextW(m_caption);
	SetWindowTextW(m_caption);

#define WIDTH			500
#define HEIGHT			30

#define TOP(i)			40 + (HEIGHT*i)
#define LEFT			40
#define BOTTOM(i)		40 + (HEIGHT*(i+1))
#define RIGHT			40 + WIDTH

	switch (m_type)
	{
	case 2:
		m_EditInput.ModifyStyle(0, ES_NUMBER);
		break;
	case 3:
	case 4:
		m_EditInput.ShowWindow(SW_HIDE);
		m_EditLabel.ShowWindow(SW_HIDE);

		for (int i = 0; i < m_numberOfmultipleFlags; i++)
		{
			m_checkBox[i].Create(m_multipleFlags[i].caption, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, CRect(LEFT, TOP(i), RIGHT, BOTTOM(i)), this, IDC_CHECKBOX_START(i + 1));

			if (m_multipleFlags[i].defaultValue)
			{
				m_checkBox[i].SetCheck(true);
				m_flagValue |= m_multipleFlags[i].flagValue;
			}
		}
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

BOOL CGetInputDlg::DestroyWindow()
{
	delete myFont;

	return CDialogEx::DestroyWindow();
}
