using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace GmpSampleSim
{
    public partial class Test : Form
    {
        public static GMPForm TestForm;

        public Test()
        {
            InitializeComponent();
        }

        private void Test_Load(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            m_lstSureler.Items.Clear();
            m_lstHatalar.Items.Clear();
            int i, j = 0;
            DateTime start1;
            TimeSpan duration1;

            int FisurunSayisi = Convert.ToInt32(m_txtFisUrunSayisi.Text);
            int IslemTekrarSayisi = Convert.ToInt32(m_txtIslemTekrarSayisi.Text);

            for (i = 0; i < IslemTekrarSayisi; i++)
            {
                for (j = 0; j < FisurunSayisi; j++)
                {
                    start1 = DateTime.Now;
                    int ret = TestForm.DepartmentSaleTest(1);
                    duration1 = DateTime.Now - start1;

                    m_lstSureler.Items.Add(String.Format("{0, 6}. Ürün Satış Süresi : {1, 6} ms", (i + 1) + "-" + (j + 1), duration1.TotalMilliseconds.ToString()));
                    m_lstSureler.SelectedIndex = m_lstSureler.Items.Count - 1;
                    m_lstSureler.Refresh();
                    if (ret != 0)
                    {
                        m_lstHatalar.Items.Add(String.Format("{0, 6} Hata : {1, 3} ", (i + 1) + "-" + (j + 1), ret.ToString("X2")));
                        m_lstHatalar.SelectedIndex = m_lstSureler.Items.Count - 1;
                        m_lstHatalar.Refresh();

                        DialogResult dr = MessageBox.Show("Devam etmek için OK, İşlemi bitirmek için CANCEL", "Hata", MessageBoxButtons.OKCancel);
                        if (dr == System.Windows.Forms.DialogResult.Cancel)
                            return;
                    }
                }

                TestForm.m_btn_Click(TestForm.m_btnPaymentCash, null);  //Nakit 
            }

            if (m_chcZAl.Checked)
            {
                DateTime start = DateTime.Now;

                TestForm.radioButton02.Checked = true;
                TestForm.m_btnFunctionMessage_Click(null, null);

                TimeSpan duration = DateTime.Now - start;

                m_lstSureler.Items.Add("Z Süresi :  " + duration.TotalMilliseconds.ToString() + " ms");
                m_lstSureler.Refresh();
                m_lstSureler.SelectedIndex = m_lstSureler.Items.Count - 1;
            }

            Thread.Sleep(500);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            DateTime start1;
            TimeSpan duration1;
            int echoCount = Convert.ToInt32(m_txtOtoEchoCounter.Text);

            for (int i = 0; i < echoCount; i++)
            {
                start1 = DateTime.Now;
                ST_ECHO stEcho = new ST_ECHO();
                Json_GMPSmartDLL.FP3_Echo(GMPForm.CurrentInterface, ref stEcho, Defines.TIMEOUT_ECHO);
                duration1 = DateTime.Now - start1;

                m_lstSureler.Items.Add(String.Format("{0, 6}. Echo Süresi : {1, 6} ms", (i + 1), duration1.TotalMilliseconds.ToString()));
                m_lstSureler.SelectedIndex = m_lstSureler.Items.Count - 1;
                m_lstSureler.Refresh();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            TestForm.m_btnStartPairing_Click(null, null);

            for (int i = 0; i < Convert.ToInt32(textBox5.Text) - 1; i++)
            {
                uint resp = 0;
                ST_GMP_PAIR pairing = new ST_GMP_PAIR();

                pairing.szExternalDeviceBrand = "INGENICO";
                pairing.szExternalDeviceModel = "IWE280";
                pairing.szExternalDeviceSerialNumber = "12344567";
                pairing.szEcrSerialNumber = "JHWE20000079";
                pairing.szProcOrderNumber = "000001";

                ST_GMP_PAIR_RESP pairingResp = new ST_GMP_PAIR_RESP();

                resp = Json_GMPSmartDLL.FP3_StartPairingInit(GMPForm.CurrentInterface, ref pairing, ref pairingResp);

                ErrorClass.DisplayErrorMessage(resp);
   
                Thread.Sleep(500);
            }
        }

        private void m_btnCreateInterface_Click(object sender, EventArgs e)
        {
            ST_INTERFACE_XML_DATA stXmlInterfaceData = new ST_INTERFACE_XML_DATA();
            stXmlInterfaceData.AckTimeOut = 1;
            stXmlInterfaceData.BaudRate = 115200;
            stXmlInterfaceData.ByteSize = 8;
            stXmlInterfaceData.CommTimeOut = 90000;
            stXmlInterfaceData.fParity = 0;
            stXmlInterfaceData.InterCharacterTimeOut = 100;
            stXmlInterfaceData.IP = "10.12.34.55";
            stXmlInterfaceData.IpRetryCount = 3;
            stXmlInterfaceData.IsTcpConnection = 0;
            stXmlInterfaceData.Parity = 0;
            stXmlInterfaceData.Port = 7500;
            stXmlInterfaceData.PortName = "\\\\.\\COM5";
            stXmlInterfaceData.RetryCounter = 3;
            stXmlInterfaceData.StopBit = 0;

            UInt32 RetCode = Json_GMPSmartDLL.FP3_CreateInterface(ref GMPForm.CurrentInterface, "COM5", 0, stXmlInterfaceData);

            TestForm.HandleErrorCode(RetCode);
        }

        private void m_btnGetTlvData_Click(object sender, EventArgs e)
        {
            // Uçuş Modu için 
            //      -- Defines.GMP_EXT_DEVICE_FLIGHT_MODE 1 : Flight mode ON, 0: Flight mode OFF 
            // Fiş Limiti için
            //      -- Defines.GMP_EXT_DEVICE_FIS_LIMIT 
  
            byte[] arr = new byte[2];
            short len = 0;
            
            UInt32 RetCode = GMPSmartDLL.FP3_GetTlvData(GMPForm.CurrentInterface, Defines.GMP_EXT_DEVICE_TAG_Z_NO, arr, (short)arr.Length, ref len);

            if (len != 0)
            {
                MessageBox.Show("Z No : " + GMPForm.ConvertByteArrayToString(arr, len));
            }
            ErrorClass.DisplayErrorMessage(RetCode);
        }

        private void m_btnSetTlvData_Click(object sender, EventArgs e)
        {
            byte[] arr2 = new byte[100];
            short len2 = 6;

            GMPForm.ConvertStringToHexArray("000010001000", ref arr2, len2);

            UInt32 RetCode = GMPSmartDLL.FP3_SetTlvData(GMPForm.CurrentInterface, Defines.GMP_EXT_DEVICE_FIS_LIMIT, arr2, (UInt16)len2);

            ErrorClass.DisplayErrorMessage(RetCode);
        }

        private void m_btnGetTaxRates_Click(object sender, EventArgs e)
        {
            UInt32 RetCode = 0;
            int numberOfTotalRecordsReceived = 0;
            int numberOfTotalTaxRates = 0;
             
            ST_TAX_RATE[] stTaxRates = new ST_TAX_RATE[8];

            for (int i = 0; i < stTaxRates.Length; i++)
            {
                stTaxRates[i] = new ST_TAX_RATE();
            }

            RetCode = Json_GMPSmartDLL.FP3_GetTaxRates(GMPForm.CurrentInterface, ref numberOfTotalTaxRates, ref numberOfTotalRecordsReceived, ref stTaxRates, 8);

            string str = "";
            for (int i = 0; i < numberOfTotalRecordsReceived; i++)
            {
                str += "Tax [" + (i + 1) + "] : " + stTaxRates[i].taxRate + Environment.NewLine; 
            }
            MessageBox.Show(str);

            ErrorClass.DisplayErrorMessage(RetCode);
        }

        private void m_btnGetDepartment_Click(object sender, EventArgs e)
        {
            UInt32 RetCode = 0;
            int numberOfTotalRecordsReceived = 0;
            int numberOfTotalDepartments = 0;

            ST_DEPARTMENT[] stDepartments = new ST_DEPARTMENT[12];

            for (int i = 0; i < stDepartments.Length; i++)
            {
                stDepartments[i] = new ST_DEPARTMENT();
            }

            RetCode = Json_GMPSmartDLL.FP3_GetDepartments(GMPForm.CurrentInterface, ref numberOfTotalDepartments, ref numberOfTotalRecordsReceived, ref stDepartments, 12);

            string str = "";
            for (int i = 0; i < numberOfTotalRecordsReceived; i++)
            {
                str += String.Format("KISIM [" + (i + 1) + "]  =     Name : {0},     Price : {1},    Limit : {2},    Currency : {3},     Tax Index : {4}", stDepartments[i].szDeptName, stDepartments[i].u64Price, stDepartments[i].u64Limit, stDepartments[i].iCurrencyType, stDepartments[i].u8TaxIndex) + Environment.NewLine;
            }
            MessageBox.Show(str);

            ErrorClass.DisplayErrorMessage(RetCode);
        }

        private void m_btnGetGlobalXmlData_Click(object sender, EventArgs e)
        {
            // Path format : C:\PROJECTS\GMPSmartDLL_p12\DLL_DEBUG\Windows\
            // "path" olmayacak ve sonunda \ olacak
            
            ST_GLOBAL_XML_DATA stGlobalXmlData = new ST_GLOBAL_XML_DATA();
            Json_GMPSmartDLL.FP3_GetGlobalXmlData(ref stGlobalXmlData);

            string str = String.Format("{0}{1}{2}{3}{4}{5}{6}{7}",  ("IsCheckStructVersion : "), stGlobalXmlData.IsCheckStructVersion, Environment.NewLine,
                                                                    ("LogFileSize : "), stGlobalXmlData.LogFileSize, Environment.NewLine,
                                                                    ("LogPath : "), stGlobalXmlData.LogPath);

            MessageBox.Show(str);
        }

        private void m_btnSetGlobalXmlData_Click(object sender, EventArgs e)
        {
            ST_GLOBAL_XML_DATA stGlobalXmlData = new ST_GLOBAL_XML_DATA();

            stGlobalXmlData.IsCheckStructVersion = 1;
            stGlobalXmlData.LogFileSize = 25000000;
            stGlobalXmlData.LogPath = "C:\\PROJECTS\\GMPSmartDLL_p12\\DLL_DEBUG\\Windows\\";

            Json_GMPSmartDLL.FP3_UpdateGlobalXmlData(ref stGlobalXmlData);

            MessageBox.Show("Tamamlandı...");
        }

        private void m_btnGetXmlFilePath_Click(object sender, EventArgs e)
        {
            byte[] szPath = new byte[1024];
            GMPSmartDLL.GetXmlFilePath(szPath);

            MessageBox.Show(GMP_Tools.SetEncoding(szPath));
        }

        public void m_btnSetXmlFilePath_Click(object sender, EventArgs e)
        {
            //XML dosyası okunmadan bu fonksiyon çağırılmalı.
            UInt32 RetCode = GMPSmartDLL.SetXmlFilePath("C:\\PROJECTS\\GMPSmartDLL_p12\\DLL_DEBUG\\Windows\\x86\\GMP.XML");

            TestForm.HandleErrorCode(RetCode);
        }

        private void m_btnRemoveInterface_Click(object sender, EventArgs e)
        {
            UInt32 RetCode = GMPSmartDLL.FP3_RemoveInterfaceByID("COM5");

            TestForm.HandleErrorCode(RetCode);
        }

        private void m_btnGetInterfaceXmlData_Click(object sender, EventArgs e)
        {
            string InterfaceId = "COM5";
            ST_INTERFACE_XML_DATA stInterfaceXmlData = new ST_INTERFACE_XML_DATA();
            UInt32 RetCode = Json_GMPSmartDLL.FP3_GetInterfaceXmlDataByID(InterfaceId, ref stInterfaceXmlData);

            if (RetCode == 0)
            {
                string str = "Interface ID : " + InterfaceId + Environment.NewLine +
                                "AckTimeOut : " + stInterfaceXmlData.AckTimeOut.ToString() + Environment.NewLine +
                                "BaudRate : " + stInterfaceXmlData.BaudRate.ToString() + Environment.NewLine +
                                "ByteSize : " + stInterfaceXmlData.ByteSize.ToString() + Environment.NewLine +
                                "CommTimeOut : " + stInterfaceXmlData.CommTimeOut.ToString() + Environment.NewLine +
                                "fParity : " + stInterfaceXmlData.fParity.ToString() + Environment.NewLine +
                                "InterCharacterTimeOut : " + stInterfaceXmlData.InterCharacterTimeOut.ToString() + Environment.NewLine +
                                "IP : " + stInterfaceXmlData.IP.ToString() + Environment.NewLine +
                                "IpRetryCount : " + stInterfaceXmlData.IpRetryCount.ToString() + Environment.NewLine +
                                "IsTcpConnection : " + stInterfaceXmlData.IsTcpConnection.ToString() + Environment.NewLine +
                                "Parity : " + stInterfaceXmlData.Parity.ToString() + Environment.NewLine +
                                "Port : " + stInterfaceXmlData.Port.ToString() + Environment.NewLine +
                                "PortName : " + stInterfaceXmlData.PortName.ToString() + Environment.NewLine +
                                "RetryCounter : " + stInterfaceXmlData.RetryCounter.ToString() + Environment.NewLine +
                                "StopBit : " + stInterfaceXmlData.StopBit.ToString() + Environment.NewLine;

                MessageBox.Show(str);
            }

            TestForm.HandleErrorCode(RetCode);
        }

        private void m_btnTestTaxDept_Click(object sender, EventArgs e)
        {
            int ret = TestForm.DepartmentSaleForTaxTest(1);
            if (ret != 0)
            {
                m_lstHatalar.Items.Add(String.Format(ret.ToString("X2")));
                m_lstHatalar.Refresh();

                DialogResult dr = MessageBox.Show("Devam etmek için OK, İşlemi bitirmek için CANCEL", "Hata", MessageBoxButtons.OKCancel);
                if (dr == System.Windows.Forms.DialogResult.Cancel)
                    return;
            }
            ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];

            for (int i = 0; i < stPaymentRequest.Length; i++)
            {
                stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
            }

            stPaymentRequest[0].typeOfPayment = (uint)EPaymentTypes.PAYMENT_CASH_TL;
            stPaymentRequest[0].subtypeOfPayment = 0;
            stPaymentRequest[0].payAmount = 100;
            stPaymentRequest[0].payAmountCurrencyCode = 949;

            TestForm.GetPaymentTest(stPaymentRequest, 1);
        }

        private void m_btnTestUserMessage_Click(object sender, EventArgs e)
        {
            ST_USER_MESSAGE[] stUserMessage = new ST_USER_MESSAGE[4];
            ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];

            for (int i = 0; i < 4; i++)
            {
                stUserMessage[i] = new ST_USER_MESSAGE();
            }

            int ret = TestForm.DepartmentSaleTest(1);

            //QR BASILMASI
            ulong flag = 0;
            
            flag |= Defines.PS_QRCODE;//RadioButton3            

            string str = "1234";
            stUserMessage[0].len = 4;
            stUserMessage[0].message = str;
            stUserMessage[0].flag = Convert.ToUInt32(flag);

            ST_TICKET m_stTicket = new ST_TICKET();

            UInt32 retcode = Defines.TRAN_RESULT_OK;

            retcode = Json_GMPSmartDLL.FP3_PrintUserMessage_Ex(GMPForm.CurrentInterface, GMPForm.ActiveTransactionHandle, ref stUserMessage, 1, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

            flag = 0;
            flag |= Defines.PS_BARCODE;           
            stUserMessage[0].len = 4;
            stUserMessage[0].message = str;
            stUserMessage[0].flag = Convert.ToUInt32(flag);

            retcode = Defines.TRAN_RESULT_OK;

            retcode = Json_GMPSmartDLL.FP3_PrintUserMessage(GMPForm.CurrentInterface, GMPForm.ActiveTransactionHandle, ref stUserMessage, 1, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

            stUserMessage[0].len = 4;
            stUserMessage[0].message = str;
            stUserMessage[0].flag = 0;

            retcode = Defines.TRAN_RESULT_OK;

            retcode = Json_GMPSmartDLL.FP3_PrintUserMessage(GMPForm.CurrentInterface, GMPForm.ActiveTransactionHandle, ref stUserMessage, 1, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

            for (int i = 0; i < stPaymentRequest.Length; i++)
            {
                stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
            }
            stPaymentRequest[0].typeOfPayment = (uint)EPaymentTypes.PAYMENT_CASH_TL;
            stPaymentRequest[0].subtypeOfPayment = 0;
            stPaymentRequest[0].payAmount = 100;
            stPaymentRequest[0].payAmountCurrencyCode = 949;

            TestForm.GetPaymentTest(stPaymentRequest, 1);                         
        }
   }
}
