// InvoiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "TaxFreeDlg.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(CTaxFreeDlg, CDialogEx)

CTaxFreeDlg::CTaxFreeDlg(CWnd* pParent /*=NULL*/)
		: CDialogEx(CTaxFreeDlg::IDD, pParent)
		, m_csTaxFreeBuyerName(_T(""))
		, m_csTaxFreeBuyerSurname(_T(""))
		, m_csTaxFreeVKN(_T("0010009400"))
		, m_csTaxFreeCity(_T(""))
		, m_csTaxFreeCountry(_T(""))
		//, m_comboCountryCode(_T(""))
		, m_dateTaxFreeOrderDate(COleDateTime::GetCurrentTime())
		, m_csTaxFreeEttn(_T(""))
		, m_csTaxFreeLabel(_T(""))
{

}

CTaxFreeDlg::~CTaxFreeDlg()
{
}

void CTaxFreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_TAXFREE_CUSTOMERNAME, m_csTaxFreeBuyerName);
	DDX_Text(pDX, IDC_EDIT_TAXFREE_CUSTOMERSURNAME, m_csTaxFreeBuyerSurname);
	DDX_Text(pDX, IDC_EDIT_TAXFREE_VKN, m_csTaxFreeVKN);
	DDX_Text(pDX, IDC_EDIT_TAXFREE_CITY, m_csTaxFreeCity);
	DDX_Text(pDX, IDC_EDIT_TAXFREE_COUNTRY, m_csTaxFreeCountry);
	DDX_Control(pDX, IDC_EDIT_TAXFREE_COUNTRYCODE, m_comboCountryCode);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TAXFREE_ORDER_DATE, m_dateTaxFreeOrderDate);
	DDX_Text(pDX, IDC_EDIT_TAXFREE_ETTN, m_csTaxFreeEttn);
	DDX_Text(pDX, IDC_EDIT_TAXFREE_LABEL, m_csTaxFreeLabel);
}


BEGIN_MESSAGE_MAP(CTaxFreeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTaxFreeDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_EDIT_TAXFREE_COUNTRYCODE, &CTaxFreeDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CTaxFreeDlg message handlers

void CTaxFreeDlg::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	m_byteCountryCode = m_comboCountryCode.GetCurSel();
	m_comboCountryCode.GetLBText(m_byteCountryCode, m_CountryCode);
}

void CTaxFreeDlg::OnBnClickedOk()
{
	UpdateData(true);
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
BOOL CTaxFreeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	myFont = new CFont();

	myFont->CreateFont(20, 0, 0, 0, FW_HEAVY, false, false,
					   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					   FIXED_PITCH | FF_MODERN, _T("Raster Fonts"));

	m_comboCountryCode.SetFont(myFont, true);



	m_comboCountryCode.AddString(L"US-AMER�KA B�RLE��K DEVLETLER�");
	m_comboCountryCode.AddString(L"DE-ALMANYA");
	m_comboCountryCode.AddString(L"AZ-AZERBAYCAN");
	m_comboCountryCode.AddString(L"AF-AFGAN�STAN");
	m_comboCountryCode.AddString(L"AT-AVUSTURYA");
	m_comboCountryCode.AddString(L"AU-AVUSTRALYA");
	m_comboCountryCode.AddString(L"AL-ARNAVUTLUK");
	m_comboCountryCode.AddString(L"BH-BAYREYN");
	m_comboCountryCode.AddString(L"BY-BELARUS");
	m_comboCountryCode.AddString(L"BE-BEL��KA");
	m_comboCountryCode.AddString(L"BY-BEYAZ RUSYA");
	m_comboCountryCode.AddString(L"AE-B�RLE��K ARAP EM�RL���");
	m_comboCountryCode.AddString(L"GB-B�RLE��K KRALLIK");
	m_comboCountryCode.AddString(L"BA-BOSNA HERSEK");
	m_comboCountryCode.AddString(L"BR-BRAZ�LYA");
	m_comboCountryCode.AddString(L"BG-BULGAR�STAN");
	m_comboCountryCode.AddString(L"CN-��N");
	m_comboCountryCode.AddString(L"CZ-�EK CUMHUR�YET�");
	m_comboCountryCode.AddString(L"DK-DAN�MARKA");
	m_comboCountryCode.AddString(L"AM-ERMEN�STAN");
	m_comboCountryCode.AddString(L"FI-F�NLAND�YA");
	m_comboCountryCode.AddString(L"FR-FRANSA");
	m_comboCountryCode.AddString(L"GE-G�RC�STAN");
	m_comboCountryCode.AddString(L"HR-HIRVAT�STAN");
	m_comboCountryCode.AddString(L"IN-H�ND�STAN");
	m_comboCountryCode.AddString(L"HK-HONG KONG");
	m_comboCountryCode.AddString(L"IQ-IRAK");
	m_comboCountryCode.AddString(L"IR-�RAN");
	m_comboCountryCode.AddString(L"GB-�NG�LTERE");
	m_comboCountryCode.AddString(L"ES-�SPANYA");
	m_comboCountryCode.AddString(L"CH-�SV��RE");
	m_comboCountryCode.AddString(L"IE-�RLANDA ");
	m_comboCountryCode.AddString(L"IL-�SRA�L");
	m_comboCountryCode.AddString(L"JP-JAPONYA");
	m_comboCountryCode.AddString(L"CA-KANADA");
	m_comboCountryCode.AddString(L"CY-KIBRIS");
	m_comboCountryCode.AddString(L"CU-K�BA");
	m_comboCountryCode.AddString(L"HU-MACAR�STAN");
	m_comboCountryCode.AddString(L"EG-MISIR");
	m_comboCountryCode.AddString(L"RU-RUSYA");
	m_comboCountryCode.AddString(L"UA-UKRAYNA");
	m_comboCountryCode.AddString(L"JO-�RD�N");
	m_comboCountryCode.AddString(L"GR-YUNAN�STAN");
	m_comboCountryCode.AddString(L"AG-ANT�GUA VE BARBUDA");
	m_comboCountryCode.AddString(L"AI-ANGUILLA");
	m_comboCountryCode.AddString(L"AO-ANGOLA");
	m_comboCountryCode.AddString(L"AQ-ANTART�CA");
	m_comboCountryCode.AddString(L"AR-ARJANT�N");
	m_comboCountryCode.AddString(L"AS-AMER�KAN SAMOASI");
	m_comboCountryCode.AddString(L"AW-ARUBA");
	m_comboCountryCode.AddString(L"AX-ALAND");
	m_comboCountryCode.AddString(L"AD-ANDORRA");
	m_comboCountryCode.AddString(L"BB-BARBADOS");
	m_comboCountryCode.AddString(L"BD-BANGLADE�");
	m_comboCountryCode.AddString(L"BF-BURK�NA FASO");
	m_comboCountryCode.AddString(L"BI-BURUND�");
	m_comboCountryCode.AddString(L"BJ-BENIN");
	m_comboCountryCode.AddString(L"BL-SAINT BARTHELEMY");
	m_comboCountryCode.AddString(L"BM-BERMUDA");
	m_comboCountryCode.AddString(L"BN-BRUNE�");
	m_comboCountryCode.AddString(L"BO-BOL�VYA");
	m_comboCountryCode.AddString(L"BQ-BONA�RE");
	m_comboCountryCode.AddString(L"BS-BAHAMALAR");
	m_comboCountryCode.AddString(L"BT-BHUTAN");
	m_comboCountryCode.AddString(L"BV-BOUVET ADDASI");
	m_comboCountryCode.AddString(L"BW-BOTSVANA");
	m_comboCountryCode.AddString(L"BZ-BEL�ZE");
	m_comboCountryCode.AddString(L"CC-COCOS ADALARI");
	m_comboCountryCode.AddString(L"CD-DEMOKRAT�K KONGO CUMHUR�YET");
	m_comboCountryCode.AddString(L"CF-ORTA AFR�KA CUMHUR�YET�");
	m_comboCountryCode.AddString(L"CG-KONGO CUMHUR�YET�");
	m_comboCountryCode.AddString(L"CI-F�LD��� SAH�L�");
	m_comboCountryCode.AddString(L"CK-COOK ADALARI");
	m_comboCountryCode.AddString(L"CL-��L�");
	m_comboCountryCode.AddString(L"CM-KAMERUN");
	m_comboCountryCode.AddString(L"CO-KOLOMB�YA");
	m_comboCountryCode.AddString(L"CR-KOSTA R�KA");
	m_comboCountryCode.AddString(L"CV-YE��L BURUN ADALARI");
	m_comboCountryCode.AddString(L"CW-CURA�AO");
	m_comboCountryCode.AddString(L"CX-CHRISMAS ADALARI");
	m_comboCountryCode.AddString(L"DJ-C�BUT�");
	m_comboCountryCode.AddString(L"DM-DOM�N�KA");
	m_comboCountryCode.AddString(L"DO-DOM�N�K CUMHUR�YET�");
	m_comboCountryCode.AddString(L"DZ-CEZAY�R");
	m_comboCountryCode.AddString(L"EC-EKVATOR");
	m_comboCountryCode.AddString(L"EE-ESTONYA");
	m_comboCountryCode.AddString(L"EH-BATI SAHRA");
	m_comboCountryCode.AddString(L"ER-ER�TRE");
	m_comboCountryCode.AddString(L"ET-ET�YOPYA");
	m_comboCountryCode.AddString(L"FJ-F�J�");
	m_comboCountryCode.AddString(L"FK-FALKLAND ADALARI");
	m_comboCountryCode.AddString(L"FM-M�KRONEZYA FEDERAL DEVLET�");
	m_comboCountryCode.AddString(L"FO-FAROE ADALARI");
	m_comboCountryCode.AddString(L"GA-GABON");
	m_comboCountryCode.AddString(L"GD-GRENADA");
	m_comboCountryCode.AddString(L"GF-FRANSIZ GUYANASI");
	m_comboCountryCode.AddString(L"GG-GUERNSEY");
	m_comboCountryCode.AddString(L"GH-GANA");
	m_comboCountryCode.AddString(L"GI-CEBEL�TARIK");
	m_comboCountryCode.AddString(L"GL-GR�NLAND");
	m_comboCountryCode.AddString(L"GM-GAMB�YA");
	m_comboCountryCode.AddString(L"GN-G�NE");
	m_comboCountryCode.AddString(L"GP-GUADELOUPE");
	m_comboCountryCode.AddString(L"GQ-EKVATOR G�NES�");
	m_comboCountryCode.AddString(L"GT-GUATEMALA");
	m_comboCountryCode.AddString(L"GU-GUAM");
	m_comboCountryCode.AddString(L"GW-G�NE B�SSAU");
	m_comboCountryCode.AddString(L"GY-GUYANA");
	m_comboCountryCode.AddString(L"HN-HONDURAS");
	m_comboCountryCode.AddString(L"HT-HAT�");
	m_comboCountryCode.AddString(L"ID-ENDENOZYA");
	m_comboCountryCode.AddString(L"IM-MAN ADASI");
	m_comboCountryCode.AddString(L"IS-�ZLANDA");
	m_comboCountryCode.AddString(L"IT-�TALYA");
	m_comboCountryCode.AddString(L"JE-JERSEY");
	m_comboCountryCode.AddString(L"JM-JAMA�KA");
	m_comboCountryCode.AddString(L"KE-KENYA");
	m_comboCountryCode.AddString(L"KG-KIRGIZ�STAN");
	m_comboCountryCode.AddString(L"KH-KAMBO�YA");
	m_comboCountryCode.AddString(L"KI-K�R�BAT�");
	m_comboCountryCode.AddString(L"KM-KOMORLAR");
	m_comboCountryCode.AddString(L"KN-SAINT KITTS VE NEVIS");
	m_comboCountryCode.AddString(L"KP-KUZAY KORE");
	m_comboCountryCode.AddString(L"KR-G�NEY KORE");
	m_comboCountryCode.AddString(L"KW-KUVEYT");
	m_comboCountryCode.AddString(L"KY-CAYMAN ADALARI");
	m_comboCountryCode.AddString(L"KZ-KAZAK�STAN");
	m_comboCountryCode.AddString(L"LA-LAOS");
	m_comboCountryCode.AddString(L"LB-L�BNAN");
	m_comboCountryCode.AddString(L"LC-SAINT LUCIA");
	m_comboCountryCode.AddString(L"LI-L�HTEN�TAYN");
	m_comboCountryCode.AddString(L"LK-SR� LANKA");
	m_comboCountryCode.AddString(L"LR-L�BERYA");
	m_comboCountryCode.AddString(L"LS-LESOTHO");
	m_comboCountryCode.AddString(L"LT-L�TVANYA");
	m_comboCountryCode.AddString(L"LU-L�KSEMBURG");
	m_comboCountryCode.AddString(L"LV-LETONYA");
	m_comboCountryCode.AddString(L"LY-L�BYA");
	m_comboCountryCode.AddString(L"MA-FAS");
	m_comboCountryCode.AddString(L"MC-MONAKO");
	m_comboCountryCode.AddString(L"MD-MOLDOVA");
	m_comboCountryCode.AddString(L"ME-KARADA�");
	m_comboCountryCode.AddString(L"MF-SAINT MARTIN");
	m_comboCountryCode.AddString(L"MG-MADAGASKAR");
	m_comboCountryCode.AddString(L"MH-MARSHALL ADALARI");
	m_comboCountryCode.AddString(L"MK-MAKEDONYA CUMHUR�YET�");
	m_comboCountryCode.AddString(L"ML-MAL�");
	m_comboCountryCode.AddString(L"MM-MYANMAR");
	m_comboCountryCode.AddString(L"MN-MO�OL�STAN");
	m_comboCountryCode.AddString(L"MO-MAKAO");
	m_comboCountryCode.AddString(L"MP-KUZEY MAR�ANA ADALARI");
	m_comboCountryCode.AddString(L"MQ-MARTINIQUE");
	m_comboCountryCode.AddString(L"MR-MOR�TANYA");
	m_comboCountryCode.AddString(L"MS-MONTSERRAT");
	m_comboCountryCode.AddString(L"MT-MALTA");
	m_comboCountryCode.AddString(L"MU-MAUR�T�US");
	m_comboCountryCode.AddString(L"MV-MALD�VLER");
	m_comboCountryCode.AddString(L"MW-MALAV�");
	m_comboCountryCode.AddString(L"MX-MEKS�KA");
	m_comboCountryCode.AddString(L"MY-MALEZYA");
	m_comboCountryCode.AddString(L"MZ-MOZAMB�K");
	m_comboCountryCode.AddString(L"NA-NAM�BYA");
	m_comboCountryCode.AddString(L"NC-YEN� KALEDONYA");
	m_comboCountryCode.AddString(L"NE-N�JER");
	m_comboCountryCode.AddString(L"NF-NORFOLK ADASI");
	m_comboCountryCode.AddString(L"NG-N�JERYA");
	m_comboCountryCode.AddString(L"NI-N�KARAGUA");
	m_comboCountryCode.AddString(L"NL-HOLLANDA");
	m_comboCountryCode.AddString(L"NO-NORVE�");
	m_comboCountryCode.AddString(L"NP-NEPAL");
	m_comboCountryCode.AddString(L"NR-NAURU");
	m_comboCountryCode.AddString(L"NU-NIUE");
	m_comboCountryCode.AddString(L"NZ-YEN� ZELANDA");
	m_comboCountryCode.AddString(L"OM-UMMAN");
	m_comboCountryCode.AddString(L"PA-PANAMA");
	m_comboCountryCode.AddString(L"PE-PERU");
	m_comboCountryCode.AddString(L"PF-FRANSIZ POL�NEZYASI");
	m_comboCountryCode.AddString(L"PG-PAPUA YEN� G�NE");
	m_comboCountryCode.AddString(L"PH-F�L�P�NLER");
	m_comboCountryCode.AddString(L"PK-PAK�STAN");
	m_comboCountryCode.AddString(L"PL-POLONYA");
	m_comboCountryCode.AddString(L"PM-SAINT PIERRE VE MIQUELON");
	m_comboCountryCode.AddString(L"PN-PITCAIRN");
	m_comboCountryCode.AddString(L"PR-PORTO R�KO");
	m_comboCountryCode.AddString(L"PS-F�L�ST�N");
	m_comboCountryCode.AddString(L"PT-PORTEK�Z");
	m_comboCountryCode.AddString(L"PW-PALAU");
	m_comboCountryCode.AddString(L"PY-PARAGUAY");
	m_comboCountryCode.AddString(L"QA-KATAR");
	m_comboCountryCode.AddString(L"RE-REUNION");
	m_comboCountryCode.AddString(L"RO-ROMANYA");
	m_comboCountryCode.AddString(L"RS-SIRBISTAN");
	m_comboCountryCode.AddString(L"RW-RUANDA");
	m_comboCountryCode.AddString(L"SA-SUUD� ARAB�STAN");
	m_comboCountryCode.AddString(L"SB-SOLOMON ADALARI");
	m_comboCountryCode.AddString(L"SC-SEY�ELLER");
	m_comboCountryCode.AddString(L"SD-SUDAN");
	m_comboCountryCode.AddString(L"SE-�SVE�");
	m_comboCountryCode.AddString(L"SG-S�NGAPUR");
	m_comboCountryCode.AddString(L"SI-SLOVENYA");
	m_comboCountryCode.AddString(L"SJ-SVALBARD");
	m_comboCountryCode.AddString(L"SK-SLOVAKYA");
	m_comboCountryCode.AddString(L"SL-SIERRA LEONE");
	m_comboCountryCode.AddString(L"SM-SAN MARINO");
	m_comboCountryCode.AddString(L"SN-SENEGAL");
	m_comboCountryCode.AddString(L"SO-SOMAL�");
	m_comboCountryCode.AddString(L"SR-SURINAM");
	m_comboCountryCode.AddString(L"SS-G�NEY SUDAN");
	m_comboCountryCode.AddString(L"SV-EL SALVADOR");
	m_comboCountryCode.AddString(L"SX-SINT MAARTEN");
	m_comboCountryCode.AddString(L"SY-SUR�YE");
	m_comboCountryCode.AddString(L"SZ-SVAZILAND");
	m_comboCountryCode.AddString(L"TC-TURKS VE CAICOS ADALARI");
	m_comboCountryCode.AddString(L"TD-�AD");
	m_comboCountryCode.AddString(L"TG-TOGO");
	m_comboCountryCode.AddString(L"TH-TAYLAND");
	m_comboCountryCode.AddString(L"TJ-TAC�K�STAN");
	m_comboCountryCode.AddString(L"TK-TOKELAU");
	m_comboCountryCode.AddString(L"TL-DO�U T�MOR");
	m_comboCountryCode.AddString(L"TM-T�RKMEN�STAN");
	m_comboCountryCode.AddString(L"TN-TUNUS");
	m_comboCountryCode.AddString(L"TO-TONGA");
	m_comboCountryCode.AddString(L"TR-T�RK�YE");
	m_comboCountryCode.AddString(L"TT-TR�N�DAD VE TOBAGO");
	m_comboCountryCode.AddString(L"TV-TUVALU");
	m_comboCountryCode.AddString(L"TW-TAYVAN");
	m_comboCountryCode.AddString(L"TZ-TANZANYA");
	m_comboCountryCode.AddString(L"UG-UGANDA");
	m_comboCountryCode.AddString(L"UY-URUGUAY");
	m_comboCountryCode.AddString(L"UZ-�ZBEK�STAN");
	m_comboCountryCode.AddString(L"VA-VAT�KAN");
	m_comboCountryCode.AddString(L"VE-VENEZUELA");
	m_comboCountryCode.AddString(L"VG-BR�TANYA V�RJ�N ADALARI");
	m_comboCountryCode.AddString(L"VI-AMER�KA V�RJ�N ADALARI");
	m_comboCountryCode.AddString(L"VN-V�ETNAM");
	m_comboCountryCode.AddString(L"VU-VANUATU");
	m_comboCountryCode.AddString(L"WF-WALLIS VE FUTUNA");
	m_comboCountryCode.AddString(L"WS-SAMOA");
	m_comboCountryCode.AddString(L"YE-YEMEN");
	m_comboCountryCode.AddString(L"YT-MAYOTTE");
	m_comboCountryCode.AddString(L"ZA-G�NEY AFR�KA");
	m_comboCountryCode.AddString(L"ZM-ZAMB�YA");
	m_comboCountryCode.AddString(L"ZW-Z�MBABVE");

	m_comboCountryCode.SetCurSel(0);
	m_comboCountryCode.GetLBText(0, m_CountryCode);

	return TRUE;
}

BOOL CTaxFreeDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	delete myFont;
	return CDialogEx::DestroyWindow();
}



