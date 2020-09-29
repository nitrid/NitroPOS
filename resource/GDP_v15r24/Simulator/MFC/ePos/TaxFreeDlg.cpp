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



	m_comboCountryCode.AddString(L"US-AMERÝKA BÝRLEÞÝK DEVLETLERÝ");
	m_comboCountryCode.AddString(L"DE-ALMANYA");
	m_comboCountryCode.AddString(L"AZ-AZERBAYCAN");
	m_comboCountryCode.AddString(L"AF-AFGANÝSTAN");
	m_comboCountryCode.AddString(L"AT-AVUSTURYA");
	m_comboCountryCode.AddString(L"AU-AVUSTRALYA");
	m_comboCountryCode.AddString(L"AL-ARNAVUTLUK");
	m_comboCountryCode.AddString(L"BH-BAYREYN");
	m_comboCountryCode.AddString(L"BY-BELARUS");
	m_comboCountryCode.AddString(L"BE-BELÇÝKA");
	m_comboCountryCode.AddString(L"BY-BEYAZ RUSYA");
	m_comboCountryCode.AddString(L"AE-BÝRLEÞÝK ARAP EMÝRLÝÐÝ");
	m_comboCountryCode.AddString(L"GB-BÝRLEÞÝK KRALLIK");
	m_comboCountryCode.AddString(L"BA-BOSNA HERSEK");
	m_comboCountryCode.AddString(L"BR-BRAZÝLYA");
	m_comboCountryCode.AddString(L"BG-BULGARÝSTAN");
	m_comboCountryCode.AddString(L"CN-ÇÝN");
	m_comboCountryCode.AddString(L"CZ-ÇEK CUMHURÝYETÝ");
	m_comboCountryCode.AddString(L"DK-DANÝMARKA");
	m_comboCountryCode.AddString(L"AM-ERMENÝSTAN");
	m_comboCountryCode.AddString(L"FI-FÝNLANDÝYA");
	m_comboCountryCode.AddString(L"FR-FRANSA");
	m_comboCountryCode.AddString(L"GE-GÜRCÝSTAN");
	m_comboCountryCode.AddString(L"HR-HIRVATÝSTAN");
	m_comboCountryCode.AddString(L"IN-HÝNDÝSTAN");
	m_comboCountryCode.AddString(L"HK-HONG KONG");
	m_comboCountryCode.AddString(L"IQ-IRAK");
	m_comboCountryCode.AddString(L"IR-ÝRAN");
	m_comboCountryCode.AddString(L"GB-ÝNGÝLTERE");
	m_comboCountryCode.AddString(L"ES-ÝSPANYA");
	m_comboCountryCode.AddString(L"CH-ÝSVÝÇRE");
	m_comboCountryCode.AddString(L"IE-ÝRLANDA ");
	m_comboCountryCode.AddString(L"IL-ÝSRAÝL");
	m_comboCountryCode.AddString(L"JP-JAPONYA");
	m_comboCountryCode.AddString(L"CA-KANADA");
	m_comboCountryCode.AddString(L"CY-KIBRIS");
	m_comboCountryCode.AddString(L"CU-KÜBA");
	m_comboCountryCode.AddString(L"HU-MACARÝSTAN");
	m_comboCountryCode.AddString(L"EG-MISIR");
	m_comboCountryCode.AddString(L"RU-RUSYA");
	m_comboCountryCode.AddString(L"UA-UKRAYNA");
	m_comboCountryCode.AddString(L"JO-ÜRDÜN");
	m_comboCountryCode.AddString(L"GR-YUNANÝSTAN");
	m_comboCountryCode.AddString(L"AG-ANTÝGUA VE BARBUDA");
	m_comboCountryCode.AddString(L"AI-ANGUILLA");
	m_comboCountryCode.AddString(L"AO-ANGOLA");
	m_comboCountryCode.AddString(L"AQ-ANTARTÝCA");
	m_comboCountryCode.AddString(L"AR-ARJANTÝN");
	m_comboCountryCode.AddString(L"AS-AMERÝKAN SAMOASI");
	m_comboCountryCode.AddString(L"AW-ARUBA");
	m_comboCountryCode.AddString(L"AX-ALAND");
	m_comboCountryCode.AddString(L"AD-ANDORRA");
	m_comboCountryCode.AddString(L"BB-BARBADOS");
	m_comboCountryCode.AddString(L"BD-BANGLADEÞ");
	m_comboCountryCode.AddString(L"BF-BURKÝNA FASO");
	m_comboCountryCode.AddString(L"BI-BURUNDÝ");
	m_comboCountryCode.AddString(L"BJ-BENIN");
	m_comboCountryCode.AddString(L"BL-SAINT BARTHELEMY");
	m_comboCountryCode.AddString(L"BM-BERMUDA");
	m_comboCountryCode.AddString(L"BN-BRUNEÝ");
	m_comboCountryCode.AddString(L"BO-BOLÝVYA");
	m_comboCountryCode.AddString(L"BQ-BONAÝRE");
	m_comboCountryCode.AddString(L"BS-BAHAMALAR");
	m_comboCountryCode.AddString(L"BT-BHUTAN");
	m_comboCountryCode.AddString(L"BV-BOUVET ADDASI");
	m_comboCountryCode.AddString(L"BW-BOTSVANA");
	m_comboCountryCode.AddString(L"BZ-BELÝZE");
	m_comboCountryCode.AddString(L"CC-COCOS ADALARI");
	m_comboCountryCode.AddString(L"CD-DEMOKRATÝK KONGO CUMHURÝYET");
	m_comboCountryCode.AddString(L"CF-ORTA AFRÝKA CUMHURÝYETÝ");
	m_comboCountryCode.AddString(L"CG-KONGO CUMHURÝYETÝ");
	m_comboCountryCode.AddString(L"CI-FÝLDÝÞÝ SAHÝLÝ");
	m_comboCountryCode.AddString(L"CK-COOK ADALARI");
	m_comboCountryCode.AddString(L"CL-ÞÝLÝ");
	m_comboCountryCode.AddString(L"CM-KAMERUN");
	m_comboCountryCode.AddString(L"CO-KOLOMBÝYA");
	m_comboCountryCode.AddString(L"CR-KOSTA RÝKA");
	m_comboCountryCode.AddString(L"CV-YEÞÝL BURUN ADALARI");
	m_comboCountryCode.AddString(L"CW-CURAÇAO");
	m_comboCountryCode.AddString(L"CX-CHRISMAS ADALARI");
	m_comboCountryCode.AddString(L"DJ-CÝBUTÝ");
	m_comboCountryCode.AddString(L"DM-DOMÝNÝKA");
	m_comboCountryCode.AddString(L"DO-DOMÝNÝK CUMHURÝYETÝ");
	m_comboCountryCode.AddString(L"DZ-CEZAYÝR");
	m_comboCountryCode.AddString(L"EC-EKVATOR");
	m_comboCountryCode.AddString(L"EE-ESTONYA");
	m_comboCountryCode.AddString(L"EH-BATI SAHRA");
	m_comboCountryCode.AddString(L"ER-ERÝTRE");
	m_comboCountryCode.AddString(L"ET-ETÝYOPYA");
	m_comboCountryCode.AddString(L"FJ-FÝJÝ");
	m_comboCountryCode.AddString(L"FK-FALKLAND ADALARI");
	m_comboCountryCode.AddString(L"FM-MÝKRONEZYA FEDERAL DEVLETÝ");
	m_comboCountryCode.AddString(L"FO-FAROE ADALARI");
	m_comboCountryCode.AddString(L"GA-GABON");
	m_comboCountryCode.AddString(L"GD-GRENADA");
	m_comboCountryCode.AddString(L"GF-FRANSIZ GUYANASI");
	m_comboCountryCode.AddString(L"GG-GUERNSEY");
	m_comboCountryCode.AddString(L"GH-GANA");
	m_comboCountryCode.AddString(L"GI-CEBELÝTARIK");
	m_comboCountryCode.AddString(L"GL-GRÖNLAND");
	m_comboCountryCode.AddString(L"GM-GAMBÝYA");
	m_comboCountryCode.AddString(L"GN-GÝNE");
	m_comboCountryCode.AddString(L"GP-GUADELOUPE");
	m_comboCountryCode.AddString(L"GQ-EKVATOR GÝNESÝ");
	m_comboCountryCode.AddString(L"GT-GUATEMALA");
	m_comboCountryCode.AddString(L"GU-GUAM");
	m_comboCountryCode.AddString(L"GW-GÝNE BÝSSAU");
	m_comboCountryCode.AddString(L"GY-GUYANA");
	m_comboCountryCode.AddString(L"HN-HONDURAS");
	m_comboCountryCode.AddString(L"HT-HATÝ");
	m_comboCountryCode.AddString(L"ID-ENDENOZYA");
	m_comboCountryCode.AddString(L"IM-MAN ADASI");
	m_comboCountryCode.AddString(L"IS-ÝZLANDA");
	m_comboCountryCode.AddString(L"IT-ÝTALYA");
	m_comboCountryCode.AddString(L"JE-JERSEY");
	m_comboCountryCode.AddString(L"JM-JAMAÝKA");
	m_comboCountryCode.AddString(L"KE-KENYA");
	m_comboCountryCode.AddString(L"KG-KIRGIZÝSTAN");
	m_comboCountryCode.AddString(L"KH-KAMBOÇYA");
	m_comboCountryCode.AddString(L"KI-KÝRÝBATÝ");
	m_comboCountryCode.AddString(L"KM-KOMORLAR");
	m_comboCountryCode.AddString(L"KN-SAINT KITTS VE NEVIS");
	m_comboCountryCode.AddString(L"KP-KUZAY KORE");
	m_comboCountryCode.AddString(L"KR-GÜNEY KORE");
	m_comboCountryCode.AddString(L"KW-KUVEYT");
	m_comboCountryCode.AddString(L"KY-CAYMAN ADALARI");
	m_comboCountryCode.AddString(L"KZ-KAZAKÝSTAN");
	m_comboCountryCode.AddString(L"LA-LAOS");
	m_comboCountryCode.AddString(L"LB-LÜBNAN");
	m_comboCountryCode.AddString(L"LC-SAINT LUCIA");
	m_comboCountryCode.AddString(L"LI-LÝHTENÞTAYN");
	m_comboCountryCode.AddString(L"LK-SRÝ LANKA");
	m_comboCountryCode.AddString(L"LR-LÝBERYA");
	m_comboCountryCode.AddString(L"LS-LESOTHO");
	m_comboCountryCode.AddString(L"LT-LÝTVANYA");
	m_comboCountryCode.AddString(L"LU-LÜKSEMBURG");
	m_comboCountryCode.AddString(L"LV-LETONYA");
	m_comboCountryCode.AddString(L"LY-LÝBYA");
	m_comboCountryCode.AddString(L"MA-FAS");
	m_comboCountryCode.AddString(L"MC-MONAKO");
	m_comboCountryCode.AddString(L"MD-MOLDOVA");
	m_comboCountryCode.AddString(L"ME-KARADAÐ");
	m_comboCountryCode.AddString(L"MF-SAINT MARTIN");
	m_comboCountryCode.AddString(L"MG-MADAGASKAR");
	m_comboCountryCode.AddString(L"MH-MARSHALL ADALARI");
	m_comboCountryCode.AddString(L"MK-MAKEDONYA CUMHURÝYETÝ");
	m_comboCountryCode.AddString(L"ML-MALÝ");
	m_comboCountryCode.AddString(L"MM-MYANMAR");
	m_comboCountryCode.AddString(L"MN-MOÐOLÝSTAN");
	m_comboCountryCode.AddString(L"MO-MAKAO");
	m_comboCountryCode.AddString(L"MP-KUZEY MARÝANA ADALARI");
	m_comboCountryCode.AddString(L"MQ-MARTINIQUE");
	m_comboCountryCode.AddString(L"MR-MORÝTANYA");
	m_comboCountryCode.AddString(L"MS-MONTSERRAT");
	m_comboCountryCode.AddString(L"MT-MALTA");
	m_comboCountryCode.AddString(L"MU-MAURÝTÝUS");
	m_comboCountryCode.AddString(L"MV-MALDÝVLER");
	m_comboCountryCode.AddString(L"MW-MALAVÝ");
	m_comboCountryCode.AddString(L"MX-MEKSÝKA");
	m_comboCountryCode.AddString(L"MY-MALEZYA");
	m_comboCountryCode.AddString(L"MZ-MOZAMBÝK");
	m_comboCountryCode.AddString(L"NA-NAMÝBYA");
	m_comboCountryCode.AddString(L"NC-YENÝ KALEDONYA");
	m_comboCountryCode.AddString(L"NE-NÝJER");
	m_comboCountryCode.AddString(L"NF-NORFOLK ADASI");
	m_comboCountryCode.AddString(L"NG-NÝJERYA");
	m_comboCountryCode.AddString(L"NI-NÝKARAGUA");
	m_comboCountryCode.AddString(L"NL-HOLLANDA");
	m_comboCountryCode.AddString(L"NO-NORVEÇ");
	m_comboCountryCode.AddString(L"NP-NEPAL");
	m_comboCountryCode.AddString(L"NR-NAURU");
	m_comboCountryCode.AddString(L"NU-NIUE");
	m_comboCountryCode.AddString(L"NZ-YENÝ ZELANDA");
	m_comboCountryCode.AddString(L"OM-UMMAN");
	m_comboCountryCode.AddString(L"PA-PANAMA");
	m_comboCountryCode.AddString(L"PE-PERU");
	m_comboCountryCode.AddString(L"PF-FRANSIZ POLÝNEZYASI");
	m_comboCountryCode.AddString(L"PG-PAPUA YENÝ GÝNE");
	m_comboCountryCode.AddString(L"PH-FÝLÝPÝNLER");
	m_comboCountryCode.AddString(L"PK-PAKÝSTAN");
	m_comboCountryCode.AddString(L"PL-POLONYA");
	m_comboCountryCode.AddString(L"PM-SAINT PIERRE VE MIQUELON");
	m_comboCountryCode.AddString(L"PN-PITCAIRN");
	m_comboCountryCode.AddString(L"PR-PORTO RÝKO");
	m_comboCountryCode.AddString(L"PS-FÝLÝSTÝN");
	m_comboCountryCode.AddString(L"PT-PORTEKÝZ");
	m_comboCountryCode.AddString(L"PW-PALAU");
	m_comboCountryCode.AddString(L"PY-PARAGUAY");
	m_comboCountryCode.AddString(L"QA-KATAR");
	m_comboCountryCode.AddString(L"RE-REUNION");
	m_comboCountryCode.AddString(L"RO-ROMANYA");
	m_comboCountryCode.AddString(L"RS-SIRBISTAN");
	m_comboCountryCode.AddString(L"RW-RUANDA");
	m_comboCountryCode.AddString(L"SA-SUUDÝ ARABÝSTAN");
	m_comboCountryCode.AddString(L"SB-SOLOMON ADALARI");
	m_comboCountryCode.AddString(L"SC-SEYÞELLER");
	m_comboCountryCode.AddString(L"SD-SUDAN");
	m_comboCountryCode.AddString(L"SE-ÝSVEÇ");
	m_comboCountryCode.AddString(L"SG-SÝNGAPUR");
	m_comboCountryCode.AddString(L"SI-SLOVENYA");
	m_comboCountryCode.AddString(L"SJ-SVALBARD");
	m_comboCountryCode.AddString(L"SK-SLOVAKYA");
	m_comboCountryCode.AddString(L"SL-SIERRA LEONE");
	m_comboCountryCode.AddString(L"SM-SAN MARINO");
	m_comboCountryCode.AddString(L"SN-SENEGAL");
	m_comboCountryCode.AddString(L"SO-SOMALÝ");
	m_comboCountryCode.AddString(L"SR-SURINAM");
	m_comboCountryCode.AddString(L"SS-GÜNEY SUDAN");
	m_comboCountryCode.AddString(L"SV-EL SALVADOR");
	m_comboCountryCode.AddString(L"SX-SINT MAARTEN");
	m_comboCountryCode.AddString(L"SY-SURÝYE");
	m_comboCountryCode.AddString(L"SZ-SVAZILAND");
	m_comboCountryCode.AddString(L"TC-TURKS VE CAICOS ADALARI");
	m_comboCountryCode.AddString(L"TD-ÇAD");
	m_comboCountryCode.AddString(L"TG-TOGO");
	m_comboCountryCode.AddString(L"TH-TAYLAND");
	m_comboCountryCode.AddString(L"TJ-TACÝKÝSTAN");
	m_comboCountryCode.AddString(L"TK-TOKELAU");
	m_comboCountryCode.AddString(L"TL-DOÐU TÝMOR");
	m_comboCountryCode.AddString(L"TM-TÜRKMENÝSTAN");
	m_comboCountryCode.AddString(L"TN-TUNUS");
	m_comboCountryCode.AddString(L"TO-TONGA");
	m_comboCountryCode.AddString(L"TR-TÜRKÝYE");
	m_comboCountryCode.AddString(L"TT-TRÝNÝDAD VE TOBAGO");
	m_comboCountryCode.AddString(L"TV-TUVALU");
	m_comboCountryCode.AddString(L"TW-TAYVAN");
	m_comboCountryCode.AddString(L"TZ-TANZANYA");
	m_comboCountryCode.AddString(L"UG-UGANDA");
	m_comboCountryCode.AddString(L"UY-URUGUAY");
	m_comboCountryCode.AddString(L"UZ-ÖZBEKÝSTAN");
	m_comboCountryCode.AddString(L"VA-VATÝKAN");
	m_comboCountryCode.AddString(L"VE-VENEZUELA");
	m_comboCountryCode.AddString(L"VG-BRÝTANYA VÝRJÝN ADALARI");
	m_comboCountryCode.AddString(L"VI-AMERÝKA VÝRJÝN ADALARI");
	m_comboCountryCode.AddString(L"VN-VÝETNAM");
	m_comboCountryCode.AddString(L"VU-VANUATU");
	m_comboCountryCode.AddString(L"WF-WALLIS VE FUTUNA");
	m_comboCountryCode.AddString(L"WS-SAMOA");
	m_comboCountryCode.AddString(L"YE-YEMEN");
	m_comboCountryCode.AddString(L"YT-MAYOTTE");
	m_comboCountryCode.AddString(L"ZA-GÜNEY AFRÝKA");
	m_comboCountryCode.AddString(L"ZM-ZAMBÝYA");
	m_comboCountryCode.AddString(L"ZW-ZÝMBABVE");

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



