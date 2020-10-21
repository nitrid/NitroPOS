using System;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Globalization;
using System.Diagnostics;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Drawing;
using GmpSampleSim.Models;
using System.Linq;
using System.Data.SQLite;

namespace GmpSampleSim
{
    public partial class GMPForm : Form
    {
        public static DateTime ApplicationTime { get; set; }
        static public UInt32 CurrentInterface;
        static public UInt64 ActiveTransactionHandle;

        static public ST_TAX_RATE[] stTaxRatesForStart = new ST_TAX_RATE[8];
        static public ST_TAX_RATE[] stTaxRatesTmp = new ST_TAX_RATE[8];
        static public ST_DEPARTMENT[] stDepartmentsForStart = new ST_DEPARTMENT[12];
        static public ST_DEPARTMENT[] stDepartmentsTmp = new ST_DEPARTMENT[12];

        SQLiteConnection m_dbConnection;
        public static string GMP_SIM_VERSION = "v15r24";

        public UInt64 ACTIVE_TRX_HANDLE 
        {
            get { return ActiveTransactionHandle; }
            set 
            { 
                ActiveTransactionHandle = value;
                m_lblCurrentTransactionHandle.Text = value.ToString("X2");
            }
        }

        Dictionary<UInt32, byte[]> TransactionUniqueIdList;
        Dictionary<UInt32, ST_DEPARTMENT[]> TransactionDepartmentList;
        Dictionary<UInt32, ST_TAX_RATE[]> TransactionTaxRateList;
        Dictionary<UInt32, ST_EXCHANGE[]> TransactionExchangeList;

        private string KampanyaName;
        private string KampanyaBkmId;
        private string KampanyaCustomerId;
        private string KampanyaServiceId;

        public byte isBackground;

        ParserClass parsClass;
        DisplayClass dispClass;
        ErrorClass errClass;

        bool ACTIVATE_PING = false;

        int numberOfTotalDepartments;
        int numberOfTotalTaxRates;
        int numberOfTotalRecordsReceived = 0;
        ST_DEPARTMENT[] stDepartments;
        ST_TAX_RATE[] stTaxRates;
        ST_GMP_PAIR_RESP pairingResp;

        public byte[] m_dllVersion = new byte[24];
        byte[] TsmSign = null;

        EPaymentTypes m_PaymentType = 0;
        System.Collections.Generic.List<ST_ITEM> stItemList = new System.Collections.Generic.List<ST_ITEM>();

        DataTable m_dataTable;
        DataTable table { get { return m_dataTable; } set { m_dataTable = value; } }

        MenuItem myMenuItem1 = new MenuItem("Start Background Transaction");
        MenuItem myMenuItem2 = new MenuItem("Switch Background To Foreground");
        ContextMenu mnu = new ContextMenu();

        public GMPForm()
        {
            InitializeComponent();
            timer1.Interval = 1000;
            ApplicationTime = DateTime.Now;
            m_lblProcTime.Text = DateTime.Now.ToString("HH:mm:ss");
            m_lblProcDate.Text = ApplicationTime.ToString("dd.MM.yy");
            

            TransactionUniqueIdList = new Dictionary<UInt32, byte[]>();
            TransactionDepartmentList = new Dictionary<UInt32, ST_DEPARTMENT[]>();
            TransactionTaxRateList = new Dictionary<UInt32, ST_TAX_RATE[]>();
            TransactionExchangeList = new Dictionary<uint, ST_EXCHANGE[]>();
            pairingResp = new ST_GMP_PAIR_RESP();
            isBackground = 0;
            //string xmlPATH = "C:\\Users\\cdurgun\\Desktop";
            //GMPSmartDLL.SetIniFilePath("../");
            //GMPSmartDLL.SetXmlFilePath("d:\\TEMP");
        }

        private void ChangeCurrentInterface(UInt32 NewInterface)
        {
            CurrentInterface = NewInterface;

            ST_DEPARTMENT[] stDepartments = new ST_DEPARTMENT[8];
            TransactionDepartmentList.TryGetValue(CurrentInterface, out stDepartments);

            ST_TAX_RATE[] stTaxRates = new ST_TAX_RATE[12];
            TransactionTaxRateList.TryGetValue(CurrentInterface, out stTaxRates);

            ST_EXCHANGE[] stExchangeTable = new ST_EXCHANGE[10];
            TransactionExchangeList.TryGetValue(CurrentInterface, out stExchangeTable);

            if (stDepartments != null && stTaxRates != null)
            {
                Button[] idDepartmenButtons = { m_btnK_017, m_btnK_018, m_btnK_019, m_btnK_020, m_btnK_021, m_btnK_022, m_btnK_023, m_btnK_024 };

                for (int i = 0; i < 8; i++)
                {
                    if (i > 7)
                        continue;
                    idDepartmenButtons[i].Text = String.Format("{0}" + System.Environment.NewLine + "%{1}.{2}", stDepartments[i].szDeptName, stTaxRates[stDepartments[i].u8TaxIndex].taxRate / 100, stTaxRates[stDepartments[i].u8TaxIndex].taxRate % 100);
                }
            }

            if (stExchangeTable != null)
            {
                m_comboBoxCurrency.Items.Clear();
                m_comboBoxCurrency.Items.Add("949 > " + "TL 1TRL  = 1.00TL");

                for (int i = 0; stExchangeTable[i].code != 0; i++)
                {
                    string str = "";

                    switch (stExchangeTable[i].prefix)
                    {
                        case "USD":
                            str += "840 > ";
                            break;
                        case "EUR":
                            str += "978 > ";
                            break;
                        case "JPY":
                            str += "826 > ";
                            break;
                        default:
                            str += "000 > ";
                            break;
                    }

                    str += String.Format("{0} 1{1}  = {2}.{3}TL", stExchangeTable[i].prefix
                                                    , stExchangeTable[i].sign
                                                    , stExchangeTable[i].rate / 100
                                                    , (stExchangeTable[i].rate % 100).ToString().PadLeft(2, '0')
                                                    );

                    m_comboBoxCurrency.Items.Add(str);
                }

                m_comboBoxCurrency.SelectedIndex = 0;
            }

            GetInterfaceInfo(CurrentInterface);
        }

        void StartBackgroundTransaction_Click(object sender, EventArgs e)
        {
            UInt64 TransactionHandle = 0;
            byte IsBackground = 1; /* foreground = 0, background = 1 */

            UInt32 retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TransactionHandle, IsBackground, GetUniqueIdByInterface(CurrentInterface), 24, TsmSign, TsmSign == null ? 0 : TsmSign.Length, null, 0, 10000);

            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return;
            }

            AddTrxHandles(CurrentInterface, TransactionHandle, IsBackground);
        }

        void SwitchBackgroundToForeground_Click(object sender, EventArgs e)
        {
            UInt64 TransactionHandle = GetTransactionHandle(CurrentInterface);
            UInt32 retcode = GMPSmartDLL.FP3_FunctionLoadBackGroundHandleToFront(CurrentInterface, TransactionHandle, Defines.TIMEOUT_DEFAULT);

            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return;
            }

            ReloadTransaction();
        }

        private void CreateDbFile()
        {
            bool IsCreated = false;
            if (!File.Exists("GMPSimulatorDb_" + GMP_SIM_VERSION + ".sqlite"))
            {
                SQLiteConnection.CreateFile("GMPSimulatorDb_" + GMP_SIM_VERSION + ".sqlite");
                IsCreated = true;
            }
            m_dbConnection = new SQLiteConnection("Data Source=GMPSimulatorDb_" + GMP_SIM_VERSION + ".sqlite;Version=3;");
            m_dbConnection.Open();

            if (IsCreated == true)
            {
                string sql = "CREATE TABLE [UniqueIdData] ('Id' INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, 'UniqueId' VARCHAR NOT NULL, 'RecordTime' DateTime NOT NULL )";
                
                SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
                command.ExecuteNonQuery();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            CheckForIllegalCrossThreadCalls = false;
            m_rbSingleMode.Checked = true;

            mnu.MenuItems.Add(myMenuItem1);
            mnu.MenuItems.Add(myMenuItem2);
            myMenuItem1.Click += new EventHandler(StartBackgroundTransaction_Click);
            myMenuItem2.Click += new EventHandler(SwitchBackgroundToForeground_Click);

            toolTip2.ToolTipIcon = ToolTipIcon.Info;
            toolTip2.IsBalloon = true;
            toolTip2.ShowAlways = true;

            toolTip2.SetToolTip(m_lblCurrentTransactionHandle, "Double-Click for switch background to foreground");

            m_Date_Start.Format = m_Date_Finish.Format = DateTimePickerFormat.Custom;
            m_Date_Start.CustomFormat = m_Date_Finish.CustomFormat = "dd/MM/yyyy HH:mm:ss";

            m_lblVersion.Text = GMP_SIM_VERSION;

            CreateDbFile();

            parsClass = new ParserClass();
            dispClass = new DisplayClass();
            errClass = new ErrorClass();

#if (DEBUG)
            m_btnTest.Visible = true;
#else
            m_btnTest.Visible = false;
#endif

            DisplayClass.dispCls = this;
            ParserClass.MainControls = this;
            ErrorClass.errCls = this;
            Test.TestForm = this;

            Localization.Culture = new CultureInfo(GmpSampleSim.Properties.Settings.Default.DefaultCulture);

            LocalizationClass.gmpUI = this;
            LocalizationClass locClass = new LocalizationClass();
            locClass.SetDefault();

            m_cmbInvoiceType.SelectedIndex = 0;

            radioButton1.Checked = true;
            radioButton10.Checked = true;
            radioButton6.Checked = true;
            radioButton13.Checked = true;

            tabControl1.SelectedTab = tabPage11;
            groupBox16.Visible = false;
            groupBox17.Visible = false;

            Array.Clear(m_dllVersion, 0, m_dllVersion.Length);

            UInt32 ret = GMPSmartDLL.GMP_GetDllVersion(m_dllVersion);
            if (ret != 0)
            {
                MessageBox.Show("Uncompatible DLL Version.\nDll Version Expected (minimum): " + Defines.DLL_VERSION_MIN + "\nDll Version Found : " + GMP_Tools.SetEncoding(m_dllVersion), "ERROR", MessageBoxButtons.OK);
            }
            else if (String.Compare(GMP_Tools.SetEncoding(m_dllVersion), Defines.DLL_VERSION_MIN) < 0)
            {
                MessageBox.Show("Uncompatible DLL Version.\nDll Version Expected (minimum): " + Defines.DLL_VERSION_MIN + "\nDll Version Found : " + GMP_Tools.SetEncoding(m_dllVersion), "ERROR", MessageBoxButtons.OK);
            }

            UInt32[] InterfaceList = new UInt32[20];
            UInt32 InterfaceCount = GMPSmartDLL.FP3_GetInterfaceHandleList(InterfaceList, (UInt32)InterfaceList.Length);

            for (UInt32 Index = 0; Index < InterfaceCount; ++Index)
            {
                byte[] ID = new byte[64];
                GMPSmartDLL.FP3_GetInterfaceID(InterfaceList[Index], ID, (UInt32)ID.Length);
                string Handle = InterfaceList[Index].ToString("X8") + "-" + GMP_Tools.SetEncoding(ID);

                TreeNode HandleTree = new TreeNode(Handle);
                HandleTree.Tag = InterfaceList[Index];
                m_treeHandleList.Nodes.Add(HandleTree);
            }

            m_treeHandleList.SelectedNode = m_treeHandleList.Nodes[0];
        }

        private void AddTrxHandles(UInt32 hInt, UInt64 hTrx, byte IsBackGround)
        {
            ACTIVE_TRX_HANDLE = hTrx;

            foreach (TreeNode Node in m_treeHandleList.Nodes)
            {
                if ((UInt32)Node.Tag == hInt)
                {
                    if (IsBackGround == 0)
                    {
                        TreeNode Tmp = Node.Nodes.Add(hTrx.ToString("X2") + " FG");
                        Tmp.Tag = hTrx;
                    }
                    else
                    {
                        TreeNode Tmp = Node.Nodes.Add(hTrx.ToString("X2") + " BG");
                        Tmp.Tag = hTrx;
                    }
                    break;
                }
            }
        }

        private void DeleteTrxHandles(UInt32 hInt, UInt64 hTrx)
        {
            foreach (TreeNode Node in m_treeHandleList.Nodes)
            {
                if ((UInt32)Node.Tag == hInt)
                {
                    foreach (TreeNode Node2 in Node.Nodes)
                    {
                        if ((UInt64)Node2.Tag == hTrx)
                        {
                            Node.Nodes.Remove(Node2);
                            if (CurrentInterface == hInt)
                            {
                                if (ACTIVE_TRX_HANDLE == hTrx)
                                    ACTIVE_TRX_HANDLE = 0;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }

        private void InterfaceRadioButonChanged(object sender, EventArgs e)
        {
            RadioButton rd = (RadioButton)sender;
            ChangeCurrentInterface((UInt32)rd.Tag);
        }

        void clearGroupBox()
        {
            foreach (GroupBox i in tabPage5.Controls)
            {
                if (i is GroupBox)
                {
                    i.Visible = false;
                }
            }
        }

        public void HandleErrorCode(UInt32 errorCode)
        {
            UInt64 TranHandle = 0;
            ErrorClass.DisplayErrorMessage(errorCode);

            if (errorCode == Defines.APP_ERR_GMP3_INVALID_HANDLE)
            {
                if (MessageBox.Show("ÖKC Fisi Yenilenmis. Yüklemek ister misiniz?", "UYARI", MessageBoxButtons.YesNo) != System.Windows.Forms.DialogResult.Yes)
                    return;

                // OKC'deki fis bir sebepten yeniden baslamis ve handle degismis
                // Start fonksiyonu guncel handle'i alabilir.
                UInt32 retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TranHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, TsmSign, TsmSign == null ? 0 : TsmSign.Length, null, 0, 10000);
                AddTrxHandles(CurrentInterface, TranHandle, isBackground);

                if (retcode == Defines.APP_ERR_ALREADY_DONE)
                    retcode = ReloadTransaction();

                ErrorClass.DisplayErrorMessage(retcode);
            }
        }

        private void m_langOpt_trTR_Click(object sender, EventArgs e)
        {
            if (GmpSampleSim.Properties.Settings.Default.DefaultCulture == "en-GB")
            {
                GmpSampleSim.Properties.Settings.Default.DefaultCulture = "tr-TR";
                GmpSampleSim.Properties.Settings.Default.Save();
                DialogResult dr = MessageBox.Show("Program will be restarted", "Warning!", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
                if (dr == System.Windows.Forms.DialogResult.OK)
                {
                    Application.Exit();
                    Process.Start("GmpSampleSim.exe");
                }
            }
            else
            {
                MessageBox.Show("Dil Zaten Turkce", "Warning!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void m_langOpt_enGB_Click(object sender, EventArgs e)
        {
            if (GmpSampleSim.Properties.Settings.Default.DefaultCulture == "tr-TR")
            {
                GmpSampleSim.Properties.Settings.Default.DefaultCulture = "en-GB";
                GmpSampleSim.Properties.Settings.Default.Save();
                DialogResult dr = MessageBox.Show("Program Tekrar Başlatılacak", "Uyarı!", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
                if (dr == System.Windows.Forms.DialogResult.OK)
                {
                    Application.Exit();
                    Process.Start("GmpSampleSim.exe");
                }
            }
            else
            {
                MessageBox.Show("System language is already English", "Warning!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        UInt32 GetCurrency()
        {
            UInt32 retcode;
            ST_EXCHANGE_PROFILE[] pStExchangeProfile = new ST_EXCHANGE_PROFILE[4];
            retcode = Json_GMPSmartDLL.FP3_GetCurrencyProfile(CurrentInterface, ref pStExchangeProfile);
            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return retcode;
            }

            m_comboBoxCurrency.Items.Clear();
            m_comboBoxCurrency.Items.Add("949 > " + "TL 1TRL  = 1.00TL");
            foreach (var profile in pStExchangeProfile)
            {
                foreach (var exchange in profile.ExchangeRecords)
                {
                    m_comboBoxCurrency.Items.Add(exchange.code + " > " + exchange.prefix + " 1" + exchange.sign + " = " + ((double)exchange.rate)/Math.Pow(10, exchange.numberOfCentDigit) + " TL " + " Profile : " + profile.ProfileName);
                }
            }
            /* SERTEN END */
            //if (retcode != 0)
            //{
            //    HandleErrorCode(retcode);
            //    return retcode;
            //}

            //m_comboBoxCurrency.Items.Clear();
            //m_comboBoxCurrency.Items.Add("949 > " + "TL 1TRL  = 1.00TL");

            //for (int i = 0; i < numberOfTotalRecordsReceived; i++)
            //{
            //    string str = "";

            //    switch (stExchangeTable[i].prefix)
            //    {
            //        case "USD":
            //            str += "840 > ";
            //            break;
            //        case "EUR":
            //            str += "978 > ";
            //            break;
            //        case "JPY":
            //            str += "826 > ";
            //            break;
            //        default:
            //            str += "000 > ";
            //            break;
            //    }

            //    str += String.Format("{0} 1{1}  = {2}.{3}TL", stExchangeTable[i].prefix
            //                                    , stExchangeTable[i].sign
            //                                    , stExchangeTable[i].rate / 100
            //                                    , (stExchangeTable[i].rate % 100).ToString().PadLeft(2, '0')
            //                                    );

            //    m_comboBoxCurrency.Items.Add(str);
            //}

            m_comboBoxCurrency.SelectedIndex = 0;


            return retcode;
        }

        UInt32 GetDepartments()
        {
            Button[] idDepartmenButtons = { m_btnK_017, m_btnK_018, m_btnK_019, m_btnK_020, m_btnK_021, m_btnK_022, m_btnK_023, m_btnK_024 };

            UInt32 RetCode = 0;
            byte indexOfTaxRates = 0;
            byte indexOfDepartments = 0;
            numberOfTotalRecordsReceived = 0;
            stTaxRates = new ST_TAX_RATE[8];
            stDepartments = new ST_DEPARTMENT[12];

            for (int i = 0; i < stDepartments.Length; i++)
            {
                stDepartments[i] = new ST_DEPARTMENT();
            }

            do
            {
                RetCode = Json_GMPSmartDLL.FP3_GetTaxRates_Ex(CurrentInterface, indexOfTaxRates, ref numberOfTotalTaxRates, ref numberOfTotalRecordsReceived, ref stTaxRates, 8 - indexOfTaxRates);

                if (RetCode != 0)
                    return RetCode;

                indexOfTaxRates += (byte)numberOfTotalRecordsReceived;

            } while (8 - indexOfTaxRates != 0);

            do
            {
                RetCode = Json_GMPSmartDLL.FP3_GetDepartments_Ex(CurrentInterface, indexOfDepartments, ref numberOfTotalDepartments, ref numberOfTotalRecordsReceived, ref stDepartments, 12 - indexOfDepartments);

                if (RetCode != 0)
                    return RetCode;

                indexOfDepartments += (byte)numberOfTotalRecordsReceived;

            } while (12 - indexOfDepartments != 0);

            for (int i = 0; i < indexOfTaxRates; i++)
            {
                if (i > 7)
                    continue;
                idDepartmenButtons[i].Text = String.Format("{0}" + System.Environment.NewLine + "%{1}.{2}", stDepartments[i].szDeptName, stTaxRates[stDepartments[i].u8TaxIndex].taxRate / 100, stTaxRates[stDepartments[i].u8TaxIndex].taxRate % 100);
            }

            if (!TransactionTaxRateList.ContainsKey(CurrentInterface))
                TransactionTaxRateList.Add(CurrentInterface, stTaxRates);

            if (!TransactionDepartmentList.ContainsKey(CurrentInterface))
                TransactionDepartmentList.Add(CurrentInterface, stDepartments);

            return RetCode;
        }

        UInt32 OnBnClickedButtonVoidAll()
        {
            UInt32 RetCode = 0;
            ST_TICKET m_stTicket = new ST_TICKET();

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_VoidAll(buffer, buffer.Length);
                AddIntoCommandBatch("prepare_VoidAll", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                Array.Clear(buffer, 0, buffer.Length);
                bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_Close(buffer, buffer.Length);
                AddIntoCommandBatch("prepare_Close", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                RetCode = Json_GMPSmartDLL.FP3_VoidAll(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                if (RetCode != 0)
                {
                    HandleErrorCode(RetCode);
                    return RetCode;
                }

                uint resp = GMPSmartDLL.FP3_Close(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                if (RetCode != 0)
                {
                    HandleErrorCode(RetCode);
                    return RetCode;
                }

                DeleteTrxHandles(CurrentInterface, GetTransactionHandle(CurrentInterface));
                ClearTransactionUniqueId(CurrentInterface);

                textBox1.Text = "";
                m_txtInputData.Text = "";
                m_comboBoxCurrency.SelectedIndex = 0;
            }

            HandleErrorCode(RetCode);
            return RetCode;
        }

        private void m_pingMenuItem_Click(object sender, EventArgs e)
        {
            this.Text = "Ingenico GMP3 Simulator";
            ACTIVATE_PING = !ACTIVATE_PING;
        }

        UInt64 GetTransactionHandle(UInt32 InterfaceHandle)
        {
            return ACTIVE_TRX_HANDLE;
        }

        byte[] GetUniqueIdByInterface(UInt32 InterfaceHandle)
        {
            byte[] m_uniqueId = new byte[24];

            if (TransactionUniqueIdList.ContainsKey(InterfaceHandle))
                Array.Copy(TransactionUniqueIdList[InterfaceHandle], m_uniqueId, 24);

            return m_uniqueId;
        }

        void SetUniqueIdByInterface(UInt32 InterfaceHandle, byte[] UniqueId)
        {
            if (TransactionUniqueIdList.ContainsKey(InterfaceHandle))
            {
                TransactionUniqueIdList[InterfaceHandle] = UniqueId;
            }
            else
            {
                TransactionUniqueIdList.Add(InterfaceHandle, UniqueId);
            }
        }

        void ClearTransactionUniqueId(UInt32 InterfaceHandle)
        {
            if (TransactionUniqueIdList.ContainsKey(InterfaceHandle))
                Array.Clear(TransactionUniqueIdList[InterfaceHandle], 0, 24);
        }

        void GetInterfaceHandleByIDExample(bool Exec)
        {
            GMPSmartDLL.FP3_GetInterfaceHandleByID(ref CurrentInterface, new byte[] { 0x31 });
        }

        public void m_echoTestMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 resp = Defines.DLL_RETCODE_RECV_BUSY;

            while (resp == Defines.DLL_RETCODE_RECV_BUSY)
            {
                ST_ECHO stEcho = new ST_ECHO();

                resp = Json_GMPSmartDLL.FP3_Echo(CurrentInterface, ref stEcho, Defines.TIMEOUT_ECHO);
                if (resp == 0)
                    ParserClass.DisplayEcrStatus(pairingResp, stEcho);
                HandleErrorCode(resp);

                if (resp == Defines.DLL_RETCODE_RECV_BUSY)
                    Thread.Sleep(1000);
            }
        }

        int getAmount(string textAmount)
        {
            int amount = 0;

            if (textAmount != "")
            {
                if (textAmount.Contains("X"))
                {
                    int count = Convert.ToInt32(textAmount.Substring(0, textAmount.IndexOf('X')));
                    int index = textAmount.IndexOf('X');
                    int price = Convert.ToInt32(textAmount.Substring(index + 1));

                    amount = price;
                }
                else
                {
                    int price = Convert.ToInt32(textAmount);
                    amount = price;
                }
            }

            return amount;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //m_lblProcTime.Text = DateTime.Now.ToString("HH:mm:ss");
            //m_lblProcDate.Text = DateTime.Now.ToString("dd.MM.yy");

   //         string[] dateParse = m_lblProcDate.Text.Split('.');
   //         string[] timeParse = m_lblProcTime.Text.Split(':');

  //          DateTime time = new DateTime(Convert.ToInt32(dateParse[2]), Convert.ToInt32(dateParse[1]), Convert.ToInt32(dateParse[0]),
  //              Convert.ToInt32(timeParse[0]), Convert.ToInt32(timeParse[1]), Convert.ToInt32(timeParse[2]));
//            time = time.AddSeconds(1);
            ApplicationTime = ApplicationTime.AddSeconds(1);
            m_lblProcTime.Text = ApplicationTime.ToString("HH:mm:ss");
            m_lblProcDate.Text = ApplicationTime.ToString("dd.MM.yy");

            if (ACTIVATE_PING)
            {
                UInt32 retcode;
                retcode = GMPSmartDLL.FP3_Ping(CurrentInterface, 1100);

                switch (retcode)
                {
                    case Defines.TRAN_RESULT_OK:
                        this.Text = "CONNECTED";
                        break;
                    case Defines.DLL_RETCODE_RECV_BUSY:
                        this.Text = "BUSY";
                        break;
                    case Defines.DLL_RETCODE_TIMEOUT:
                        this.Text = "TIMEOUT";
                        break;
                    default:
                        this.Text = "ERROR";
                        HandleErrorCode(retcode);
                        ACTIVATE_PING = false;
                        break;
                }
            }
        }

        UInt32 GetReceiptOptionFlags(UInt32 CurrentInterface)
        {
            UInt32 RetCode;
            UInt64 activeFlags = 0;
            ST_TICKET m_stTicket = new ST_TICKET();

            RetCode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0, Defines.TIMEOUT_DEFAULT);
            if (RetCode != Defines.TRAN_RESULT_OK)
                return RetCode;

            RetCode = Json_GMPSmartDLL.FP3_GetTicket(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);

            if(RetCode == Defines.TRAN_RESULT_OK)
                return m_stTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_ONLINE_INVOICE_PARAMETERS_SET;

            return 0;
        }

        UInt32 ReloadTransaction()
        {
            UInt32 RetCode = 0;
            ST_TICKET m_stTicket = new ST_TICKET();
            UInt64 activeFlags = 0;

            RetCode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0, Defines.TIMEOUT_DEFAULT);
            if (RetCode != Defines.TRAN_RESULT_OK)
                return RetCode;

            RetCode = Json_GMPSmartDLL.FP3_GetTicket(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);
            if (RetCode != Defines.TRAN_RESULT_OK)
                return RetCode;

            m_lstBankErrorMessage.Items.Clear();

            for (int i = 0; i < m_stTicket.numberOfPaymentsInThis; i++)
                m_lstBankErrorMessage.Items.Add(m_stTicket.stPayment[i].stBankPayment.stPaymentErrMessage.ErrorMsg);

            DisplayTransaction(m_stTicket, true);

            return RetCode;
        }

        public string formatAmount(uint amount, ECurrency currency)
        {
            string amountStr = String.Format("{0}.{1:00}", amount / 100, amount % 100);

            switch (currency)
            {
                case ECurrency.CURRENCY_NONE:
                    break;
                case ECurrency.CURRENCY_DOLAR:
                    amountStr += " $";
                    break;
                case ECurrency.CURRENCY_EU:
                    amountStr += " €";
                    break;
                case ECurrency.CURRENCY_TL:
                    amountStr += " TL";
                    break;
                default:
                    amountStr += " ?";
                    break;
            }

            return amountStr;
        }

        void DisplayTransaction(ST_TICKET pstTicket, bool itemDetail)
        {
            try
            {
                tabControl1.SelectedTab = tabPage1;

                m_listTransaction.Items.Clear();

                string str_uniqueID = "";
                for (int i = 0; i < 24; i++)
                {
                    str_uniqueID += pstTicket.uniqueId[i].ToString("X2");
                }

                TransactionInfo(m_listTransaction, String.Format("UNIQUE ID        : " + str_uniqueID));
                TransactionInfo(m_listTransaction, String.Format("TICKET TYPE      : " + pstTicket.ticketType));
                TransactionInfo(m_listTransaction, String.Format("Z NO             : " + pstTicket.ZNo));
                TransactionInfo(m_listTransaction, String.Format("F NO             : " + pstTicket.FNo));
                TransactionInfo(m_listTransaction, String.Format("EJNO             : " + pstTicket.EJNo));
                TransactionInfo(m_listTransaction, String.Format("TRANSACTION FLAG : " + pstTicket.TransactionFlags.ToString().PadLeft(8, '0')));

                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_GMP3) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_GMP3"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_TICKET_HEADER_PRINTED) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_TICKET_HEADER_PRINTED"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_TICKET_TOTALS_AND_PAYMENTS_PRINTED) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_TICKET_TOTALS_AND_PAYMENTS_PRINTED"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_TICKET_FOOTER_BEFORE_MF_PRINTED) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_TICKET_FOOTER_BEFORE_MF_PRINTED"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_TICKET_FOOTER_MF_PRINTED) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_TICKET_FOOTER_MF_PRINTED"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_ONLINE_INVOICE_PARAMETERS_SET) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_ONLINE_INVOICE_PARAMETERS_SET"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_TAXFREE_PARAMETERS_SET) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_TAXFREE_PARAMETERS_SET"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_INVOICE_PARAMETERS_SET) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_INVOICE_PARAMETERS_SET"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_FULL_RCPT_CANCEL) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_FULL_RCPT_CANCEL"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_NONEY_COLLECTION_EXISTS) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_NONEY_COLLECTION_EXISTS"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_TAXLESS_ITEM_EXISTS) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_TAXLESS_ITEM_EXISTS"));
                if ((pstTicket.TransactionFlags & (uint)ETransactionFlags.FLG_XTRANS_TICKETTING_EXISTS) != 0) TransactionInfo(m_listTransaction, String.Format("                : FLG_XTRANS_TICKETTING_EXISTS"));

                TransactionInfo(m_listTransaction, String.Format("OPTION FLAG      : " + pstTicket.OptionFlags.ToString().PadLeft(8, '0')));
                TransactionInfo(m_listTransaction, String.Format(Localization.ProcDate.PadRight(30) + " : {0}/{1}/20{2}", pstTicket.szTicketDate.Substring(4, 2), pstTicket.szTicketDate.Substring(2, 2), pstTicket.szTicketDate.Substring(0, 2)));
                TransactionInfo(m_listTransaction, String.Format(Localization.ProcTime.PadRight(30) + " : {0}:{1}:{2}", pstTicket.szTicketTime.Substring(0, 2), pstTicket.szTicketTime.Substring(2, 2), pstTicket.szTicketTime.Substring(4, 2)));
                TransactionInfo(m_listTransaction, String.Format(Localization.Total.PadRight(30) + " : {0}.{1}", (pstTicket.TotalReceiptAmount / 100).ToString(), (pstTicket.TotalReceiptAmount % 100).ToString().PadLeft(2, '0')));
                if (pstTicket.KatkiPayiAmount != 0)
                    TransactionInfo(m_listTransaction, String.Format("MATRAHSZ        : {0}.{1}", pstTicket.KatkiPayiAmount / 100, pstTicket.KatkiPayiAmount % 100));

                TransactionInfo(m_listTransaction, String.Format(Localization.TotalTax.PadRight(30) + " : {0}.{1}", pstTicket.TotalReceiptTax / 100, (pstTicket.TotalReceiptTax % 100).ToString().PadLeft(2, '0')));
                TransactionInfo(m_listTransaction, Localization.ItemTable.PadRight(30) + " : " + pstTicket.totalNumberOfItems);

                if (pstTicket.TotalReceiptDiscount != 0)
                    TransactionInfo(m_listTransaction, String.Format("TOTAL DISCOUNT  : {0}.{1}", pstTicket.TotalReceiptDiscount / 100, pstTicket.TotalReceiptDiscount % 100));

                if (pstTicket.TotalReceiptIncrement != 0)
                    TransactionInfo(m_listTransaction, String.Format("TOTAL INCREAE   : {0}.{1}", pstTicket.TotalReceiptIncrement / 100, pstTicket.TotalReceiptIncrement % 100));

                if (pstTicket.TotalReceiptItemCancel != 0)
                    TransactionInfo(m_listTransaction, String.Format("TOTAL VOID      : {0}.{1}", pstTicket.TotalReceiptItemCancel / 100, pstTicket.TotalReceiptItemCancel % 100));

                if (pstTicket.KasaAvansAmount != 0)
                    TransactionInfo(m_listTransaction, String.Format("KASA AVANS      : {0}.{1}", pstTicket.KasaAvansAmount / 100, pstTicket.KasaAvansAmount % 100));

                if (pstTicket.KasaPaymentAmount != 0)
                    TransactionInfo(m_listTransaction, String.Format("KASA PAYMENT    : {0}.{1}", pstTicket.KasaPaymentAmount / 100, pstTicket.KasaPaymentAmount % 100));

                if (pstTicket.CashBackAmount != 0)
                    TransactionInfo(m_listTransaction, String.Format("CASHBACK        : {0}.{1}", pstTicket.CashBackAmount / 100, pstTicket.CashBackAmount % 100));

                if (pstTicket.invoiceAmount != 0)
                    TransactionInfo(m_listTransaction, String.Format("INVOICE         : {0}.{1}", pstTicket.invoiceAmount / 100, pstTicket.invoiceAmount % 100));

                if (pstTicket.TaxFreeCalculated != 0)
                    TransactionInfo(m_listTransaction, String.Format("TAXFREE CALCULA : {0}.{1}", pstTicket.TaxFreeCalculated / 100, pstTicket.TaxFreeCalculated % 100));

                if (pstTicket.TaxFreeRefund != 0)
                    TransactionInfo(m_listTransaction, String.Format("TAXFREE REFUND  : {0}.{1}", pstTicket.TaxFreeRefund / 100, pstTicket.TaxFreeRefund % 100));

                if (pstTicket.TotalReceiptReversedPayment != 0)
                    TransactionInfo(m_listTransaction, String.Format("REVERSE PAYMENTS: {0} ", formatAmount(pstTicket.TotalReceiptReversedPayment, ECurrency.CURRENCY_NONE)));

                if (pstTicket.TotalReceiptIncrement != 0)
                    TransactionInfo(m_listTransaction, String.Format("INSTALLMENT COUNT   : {0}.{1}", pstTicket.TotalReceiptIncrement / 100, pstTicket.TotalReceiptIncrement % 100));

                if (pstTicket.TotalReceiptPayment != 0)
                    TransactionInfo(m_listTransaction, String.Format("PAYMENTS        : {0} ", formatAmount(pstTicket.TotalReceiptPayment, ECurrency.CURRENCY_NONE)));

                if (!string.IsNullOrEmpty(pstTicket.LastPaymentErrorCode))
                {
                    TransactionInfo(m_listTransaction, String.Format("Error Code        : {0} ", pstTicket.LastPaymentErrorCode));
                    TransactionInfo(m_listTransaction, String.Format("Error Message     : {0} ", pstTicket.LastPaymentErrorMsg));
                }

                for (int i = 0; i < pstTicket.stPayment.Length; i++)
                {
                    if (pstTicket.stPayment[i] != null)
                    {
                        for (int j = 0; j < pstTicket.stPayment[i].stBankPayment.numberOfsubPayment; j++)
                        {
                            if (pstTicket.stPayment[i].stBankPayment.stBankSubPaymentInfo[j].amount != 0)
                            {
                                TransactionInfo(m_listTransaction, String.Format("BONUS NAME      : {0} ", pstTicket.stPayment[i].stBankPayment.stBankSubPaymentInfo[j].name));
                                TransactionInfo(m_listTransaction, String.Format("BONUS TYPE      : {0} ", pstTicket.stPayment[i].stBankPayment.stBankSubPaymentInfo[j].type));
                                TransactionInfo(m_listTransaction, String.Format("BONUS AMOUNT    : {0} ", pstTicket.stPayment[i].stBankPayment.stBankSubPaymentInfo[j].amount));
                            }
                        }

                        if (pstTicket.stPayment[i].stBankPayment.numberOfInstallments != 0)
                            TransactionInfo(m_listTransaction, String.Format("INSTALLMENT COUNT      : {0} ", pstTicket.stPayment[i].stBankPayment.numberOfInstallments));

                    }
                }

                TransactionInfo(m_listTransaction, "Kampanya Tablosu" + " : " + pstTicket.numberOfLoyaltyInThis);

                for (int i = 0; i < pstTicket.stLoyaltyService.Length; i++)
                {
                    if (pstTicket.stLoyaltyService[i] != null)
                    {
                        TransactionInfo(m_listTransaction, "------------");

                        TransactionInfo(m_listTransaction, String.Format("  " + "CUSTOMER ID".PadRight(20) +        " : {0} ", pstTicket.stLoyaltyService[i].CustomerId));
                        TransactionInfo(m_listTransaction, String.Format("  " + "CUSTOMER ID TYPE".PadRight(20) +   " : {0} ", pstTicket.stLoyaltyService[i].CustomerIdType));
                        TransactionInfo(m_listTransaction, String.Format("  " + "NAME".PadRight(20) +               " : {0} ", (GMP_Tools.SetEncoding(pstTicket.stLoyaltyService[i].name))));
                        TransactionInfo(m_listTransaction, String.Format("  " + "SERVICE ID".PadRight(20) +         " : {0} ", pstTicket.stLoyaltyService[i].ServiceId));
                        TransactionInfo(m_listTransaction, String.Format("  " + "DISCOUNT AMOUNT".PadRight(20) +    " : {0} ", pstTicket.stLoyaltyService[i].TotalDiscountAmount));
                        TransactionInfo(m_listTransaction, String.Format("  " + "APP ID".PadRight(20) +             " : {0} ", pstTicket.stLoyaltyService[i].u16AppId.ToString("X2")));
                    }
                }

                if (pstTicket.totalNumberOfPrinterLines == pstTicket.numberOfPrinterLinesInThis)
                    m_listPayment.Items.Clear();

                for (int i = 0; i < pstTicket.numberOfPrinterLinesInThis; i++)
                    TransactionInfo(m_listPayment, String.Format("{0}", pstTicket.stPrinterCopy[i].line));
                //m_listPayment.Items.Add(item27.Text);

                //for (int i = pstTicket.totalNumberOfPrinterLines - pstTicket.numberOfPrinterLinesInThis; i < pstTicket.totalNumberOfPrinterLines; i++)
                //{
                //    ListViewItem item27 = new ListViewItem(String.Format("{0}", pstTicket.stPrinterCopy[i].line));
                //    m_listPayment.Items.Add(item27.Text);
                //}


                if (itemDetail)
                    for (int i = pstTicket.totalNumberOfItems - pstTicket.numberOfItemsInThis; i < pstTicket.totalNumberOfItems; i++)
                    {
                        TransactionInfo(m_listTransaction, Localization.Item + (i + 1));
                        TransactionInfo(m_listTransaction, String.Format("  " + Localization.Name.PadRight(20) + " : {0}", pstTicket.SaleInfo[i].Name));
                        TransactionInfo(m_listTransaction, String.Format("  " + Localization.Barcode.PadRight(20) + " : {0}", pstTicket.SaleInfo[i].Barcode));
                        TransactionInfo(m_listTransaction, String.Format("  " + Localization.Amount.PadRight(20) + " : {0}", formatAmount((uint)pstTicket.SaleInfo[i].ItemPrice, (ECurrency)pstTicket.SaleInfo[i].ItemCurrencyType)));
                        TransactionInfo(m_listTransaction, String.Format("  " + Localization.OriginalAmount.PadRight(20) + " : {0}", formatAmount(pstTicket.SaleInfo[i].OrigialItemAmount, (ECurrency)pstTicket.SaleInfo[i].OriginalItemAmountCurrency)));
                        TransactionInfo(m_listTransaction, String.Format("  " + Localization.Discount.PadRight(20) + " : {0}", formatAmount((uint)pstTicket.SaleInfo[i].DecAmount, ECurrency.CURRENCY_TL)));
                        TransactionInfo(m_listTransaction, String.Format("  " + Localization.Save.PadRight(20) + " : {0}", formatAmount((uint)pstTicket.SaleInfo[i].IncAmount, ECurrency.CURRENCY_TL)));
                        TransactionInfo(m_listTransaction, String.Format("  " + Localization.Count.PadRight(20) + " : {0}", formatCount(pstTicket.SaleInfo[i].ItemCount, pstTicket.SaleInfo[i].ItemCountPrecision, (EItemUnitTypes)pstTicket.SaleInfo[i].ItemUnitType)));
                    }

                TransactionInfo(m_listTransaction, Localization.PaymentTable.PadRight(30) + " : " + pstTicket.totalNumberOfPayments);

            }
            catch
            {

            }
        }

        void TransactionInfo(ListBox lst, string Item)
        {
            ListViewItem item = new ListViewItem(Item);
            lst.Items.Add(item.Text);
        }

        string formatCount(int itemCount, byte ItemCountPrecision, EItemUnitTypes itemUnitType)
        {
            //formatCountStr += "%%ld.%%0%dd", ItemCountPrecision);
            //sprintf( cs[index], tmpFormat		
            //                            , itemCount / (long)pow((double)10, ItemCountPrecision)
            //                            , itemCount % (long)pow((double)10, ItemCountPrecision) 
            //                            );

            //switch(itemUnitType)
            //{
            //case EItemUnitTypes.ITEM_NONE:
            //    break;
            //case EItemUnitTypes.ITEM_NUMBER:
            //    strcat( cs[index], " Adt");
            //    break;
            //case EItemUnitTypes.ITEM_KILOGRAM:
            //    strcat( cs[index], " Kg");
            //    break;
            //case EItemUnitTypes.ITEM_GRAM:
            //    strcat( cs[index], " gr");
            //    break;
            //case EItemUnitTypes.ITEM_LITRE:
            //    strcat( cs[index], " lt");
            //    break;
            //}

            return itemCount.ToString();
        }

        UInt32 StartTicket(TTicketType ticketType)
        {
            UInt64 TranHandle = 0;
            UInt32 retcode = Defines.TRAN_RESULT_OK;

        start_again:
            if (GetTransactionHandle(CurrentInterface) == 0)
            {
                if (ticketType != TTicketType.TProcessSale)
                ClearTransactionUniqueId(CurrentInterface);

                byte[] UserData = new byte[] { 0x74, 0x65, 0x73, 0x74, 0x64, 0x61, 0x74, 0x61 };
                retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TranHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, TsmSign, TsmSign == null ? 0 : TsmSign.Length, UserData, UserData.Length, 10000);
                AddTrxHandles(CurrentInterface, TranHandle, isBackground);
                if (retcode == Defines.APP_ERR_ALREADY_DONE)
                {
                    switch (MessageBox.Show(Localization.IncompleteTransactionDesc, Localization.IncompleteTransaction, MessageBoxButtons.OKCancel))
                    {
                        case DialogResult.OK:
                            return ReloadTransaction();
                        case DialogResult.Cancel:
                            OnBnClickedButtonVoidAll();
                            goto start_again;
                    }
                }
                else if (retcode == Defines.TRAN_RESULT_OK)
                     retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), ticketType, Defines.TIMEOUT_DEFAULT);

                if (retcode == Defines.TRAN_RESULT_OK)
                {
                    UInt64 activeFlags = 0;
                    retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0x00000000, Defines.TIMEOUT_DEFAULT);
                }
            }

            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                // Handle Açık kalmasın...
                UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                uint resp = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                if (resp == Defines.TRAN_RESULT_OK)
					DeleteTrxHandles(CurrentInterface, TransHandle);
            }

            return retcode;
        }

        private void DepartmentSale(int deptIndex)
        {
            UInt32 retcode;
            UInt16 currency = 949;
            bool IsVatIncludedToPrice = false;
            bool IsVatNotIncludedToPrice = false;
            UInt32 itemCount = 1;
            byte unitType = 0;//(byte)EItemUnitTypes.ITEM_KILOGRAM; 0 adet, 2 kilogram
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_ITEM stItem = new ST_ITEM();
            

            if (m_comboBoxCurrency.Text != "")
                currency = Convert.ToUInt16(m_comboBoxCurrency.Text.Substring(0, 3));
            
            if (m_txtInputData.Text.Contains("X"))
                itemCount = Convert.ToUInt32(m_txtInputData.Text.Substring(0, m_txtInputData.Text.IndexOf('X')));

            if (m_txtPluBarcode.Text == "")
                stItem.type = Defines.ITEM_TYPE_DEPARTMENT;
            else
                stItem.type = Defines.ITEM_TYPE_PLU;
            stItem.subType = 0;
            stItem.deptIndex = (byte)(deptIndex - 1);
            stItem.amount = (uint)getAmount(m_txtInputData.Text);
            stItem.currency = currency;
            stItem.count = itemCount;
            stItem.unitType = unitType;
            stItem.pluPriceIndex = 0;
            stItem.countPrecition = 0;
            stItem.name = "";
            stItem.barcode = m_txtPluBarcode.Text;
            MessageBox.Show(stItem.count.ToString());
            if (PromotionModel.Instance.Amount > 0)
            {
                stItem.promotion.amount = (int)PromotionModel.Instance.Amount;
                stItem.promotion.ticketMsg = PromotionModel.Instance.Message;
                stItem.promotion.type = (byte)PromotionModel.Instance.Type;
                PromotionModel.Instance.Clear();
            }
            

            if (m_chcTaxFreeActive.Checked)
            {
                stItem.flag |= (uint)EItemOptions.ITEM_TAX_EXCEPTION_VAT_INCLUDED_TO_PRICE;
                IsVatIncludedToPrice = true;
            }
            m_chcTaxFreeActive.Checked = false;

            if (m_chcTaxFreeActive2.Checked)
            {
                stItem.flag |= (uint)EItemOptions.ITEM_TAX_EXCEPTION_VAT_NOT_INCLUDED_TO_PRICE;
                IsVatNotIncludedToPrice = true;
            }
            m_chcTaxFreeActive2.Checked = false;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_ItemSale(buffer, buffer.Length, ref stItem);
                AddIntoCommandBatch("prepare_ItemSale", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
            Start:
                retcode = StartTicket(TTicketType.TProcessSale);
                if (retcode != Defines.TRAN_RESULT_OK)
                    return;

                if (IsVatIncludedToPrice == true || IsVatNotIncludedToPrice == true)
                {
                    int TaxValue = stTaxRates[stDepartments[deptIndex - 1].u8TaxIndex].taxRate / 100 + stTaxRates[stDepartments[deptIndex - 1].u8TaxIndex].taxRate % 100;

                    if ((TaxValue == 0) && (GetReceiptOptionFlags(CurrentInterface) != 0))
                    {
                        GetInputForm gif = new GetInputForm("Exception Code", "", 2);
                        DialogResult dr2 = gif.ShowDialog();
                        if (dr2 == System.Windows.Forms.DialogResult.OK)
                            stItem.OnlineInvoiceItemExceptionCode = Convert.ToUInt16(gif.textBox1.Text);
                    }
                }


                m_stTicket.SaleInfo[0] = new ST_SALEINFO();
                retcode = Json_GMPSmartDLL.FP3_ItemSale(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stItem, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                if (retcode == Defines.APP_ERR_FIS_LIMITI_ASILAMAZ)
                {

                    DialogResult dr = GmpSampleSim.Properties.Settings.Default.DefaultCulture == "en-GB" ?
                        MessageBox.Show("Receipt limit has been exceeded. Convert to Invoice?", "Warning!", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning)
                            : MessageBox.Show("Fiş limiti aşıldı. Faturalı işleme geçmek ister misiniz?", "Warning!", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);

                    if (dr == System.Windows.Forms.DialogResult.OK)
                    {
                        ST_TICKET imageOfTicket = new ST_TICKET();
                        ST_ITEM imageOfItem = new ST_ITEM();
                        ST_INVIOCE_INFO stInvoiceInfo = new ST_INVIOCE_INFO();

                        retcode = Json_GMPSmartDLL.FP3_GetTicket(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                        if (retcode != Defines.TRAN_RESULT_OK)
                        {
                            HandleErrorCode(retcode);
                            stItemList.Clear();
                            return;
                        }

                        imageOfTicket = m_stTicket;

                        OnBnClickedButtonVoidAll();
                        ClearTransactionUniqueId(CurrentInterface);

                        UInt64 activeFlags = 0;

                        stInvoiceInfo.source = 0;
                        stInvoiceInfo.amount = m_txtInvoiceAmount.Text == "" ? 0 : Convert.ToUInt64(m_txtInvoiceAmount.Text);
                        stInvoiceInfo.currency = 949;
                        if (m_comboBoxCurrency.Text != "")
                            stInvoiceInfo.currency = Convert.ToUInt16(m_comboBoxCurrency.Text.Substring(0, 3));

                        stInvoiceInfo.no = new byte[25];
                        ConvertAscToBcdArray("123123123", ref stInvoiceInfo.no, stInvoiceInfo.no.Length);
                        stInvoiceInfo.tck_no = new byte[12];
                        ConvertAscToBcdArray("987987897", ref stInvoiceInfo.tck_no, stInvoiceInfo.tck_no.Length);
                        stInvoiceInfo.vk_no = new byte[12];
                        ConvertAscToBcdArray(m_txtVKN.Text, ref stInvoiceInfo.vk_no, stInvoiceInfo.vk_no.Length);

                        stInvoiceInfo.date = new byte[3];
                        string dateStr = m_dateInvoiceDate.Value.Day.ToString().PadLeft(2, '0') + m_dateInvoiceDate.Value.Month.ToString().PadLeft(2, '0') + m_dateInvoiceDate.Value.Year.ToString().Substring(2, 2).PadLeft(2, '0');

                        ConvertStringToHexArray(dateStr, ref stInvoiceInfo.date, 3);
                        Array.Reverse(stInvoiceInfo.date);

                        if (m_chcIrsaliye.Checked)
                            stInvoiceInfo.flag |= (uint)EInvoiceFlags.INVOICE_FLAG_IRSALIYE;

                        if (GetTransactionHandle(CurrentInterface) == 0)
                        {
                            UInt64 TranHandle = 0;
                            retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TranHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
                            AddTrxHandles(CurrentInterface, TranHandle, isBackground);

                            if (retcode != Defines.TRAN_RESULT_OK)
                                HandleErrorCode(retcode);

                            retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, (Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS), 0x00000000, Defines.TIMEOUT_DEFAULT);
                            if (retcode != Defines.TRAN_RESULT_OK)
                                HandleErrorCode(retcode);
                        }

                        retcode = Json_GMPSmartDLL.FP3_SetInvoice(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stInvoiceInfo, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                        if (retcode != 0)
                        {
                            HandleErrorCode(retcode);
                            return;
                        }

                        retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), TTicketType.TInvoice, Defines.TIMEOUT_DEFAULT);
                        if ((retcode != Defines.TRAN_RESULT_OK) && (retcode != Defines.APP_ERR_TICKET_HEADER_ALREADY_PRINTED))
                        {
                            HandleErrorCode(retcode);
                            return;
                        }

                        for (var i = 0; i < stItemList.Count; i++)
                        {
                            ST_ITEM stItemObject = stItemList[i];
                            retcode = Json_GMPSmartDLL.FP3_ItemSale(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stItemObject, ref imageOfTicket, Defines.TIMEOUT_DEFAULT);
                            if (retcode != Defines.TRAN_RESULT_OK)
                            {
                                HandleErrorCode(retcode);
                                return;
                            }
                        }
                        stItemList.Clear();

                        HandleErrorCode(retcode);
                        DisplayTransaction(m_stTicket, false);
                    }
                }

                if (retcode == Defines.APP_ERR_TICKET_HEADER_NOT_PRINTED)
                {
                    ClearTransactionUniqueId(CurrentInterface);
                    UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                    uint resp = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                    if (resp == Defines.TRAN_RESULT_OK)
						DeleteTrxHandles(CurrentInterface, TransHandle);

                    goto Start;
                }
                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                DisplayTransaction(m_stTicket, false);
                HandleErrorCode(retcode);
            }

            textBox1.Text = "";
            m_txtInputData.Text = "";
            m_comboBoxCurrency.SelectedIndex = 0;
        }

        public void m_btn_Click(object sender, EventArgs e)
        {
            Button btn = (Button)sender;

            int index = Convert.ToInt32(btn.Name.Substring(btn.Name.Length - 3));

            switch (index)
            {

                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 11:
                case 12:
                    m_txtInputData.Text += btn.Text;
                    break;
                case 13:
                    m_txtInputData.Text = "";
                    break;
                case 14: //back
                    if (m_txtInputData.Text.Length > 0)
                        m_txtInputData.Text = m_txtInputData.Text.Substring(0, m_txtInputData.Text.Length - 1);
                    break;

                case 17: DepartmentSale(1); break;  //K1
                case 18: DepartmentSale(2); break;  //K2
                case 19: DepartmentSale(3); break;  //K3
                case 20: DepartmentSale(4); break;  //K4
                case 21: DepartmentSale(5); break;  //K5
                case 22: DepartmentSale(6); break;  //K6
                case 23: DepartmentSale(7); break;  //K7
                case 24: DepartmentSale(8); break;  //K8
                case 25: DepartmentSale(9); break;  //K9
                case 26: DepartmentSale(10); break; //K10
                case 27: DepartmentSale(11); break; //K11
                case 28: DepartmentSale(12); break; //K12

                case 30:        //Function Message
                    tabControl1.SelectedTab = tabPage9;

                    break;


                case 31:        //Close Ticket
                    {
                        UInt32 retcode;

                        if (GetTransactionHandle(CurrentInterface) == 0)
                            return;

                        retcode = GMPSmartDLL.FP3_PrintTotalsAndPayments(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                        if (retcode != Defines.TRAN_RESULT_OK)
                            goto Exit;

                        retcode = GMPSmartDLL.FP3_PrintBeforeMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                        if (retcode != Defines.TRAN_RESULT_OK)
                            goto Exit;

                        retcode = GMPSmartDLL.FP3_PrintMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                        if (retcode != Defines.TRAN_RESULT_OK)
                            goto Exit;

                        ClearTransactionUniqueId(CurrentInterface);

                        UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                        retcode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                        if (retcode == Defines.TRAN_RESULT_OK)
                            DeleteTrxHandles(CurrentInterface, TransHandle);

                        HandleErrorCode(retcode);

                    Exit:
                        HandleErrorCode(retcode);
                        break;
                    }

                case 32:    //Sub Total
                    {
                        UInt32 retcode;

                        if (m_rbBatchMode.Checked)
                        {
                            byte[] buffer = new byte[1024];
                            int bufferLen = 0;

                            bufferLen = GMPSmartDLL.prepare_Pretotal(buffer, buffer.Length);
                            AddIntoCommandBatch("prepare_Pretotal", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                        }
                        else
                        {
                            ST_TICKET m_stTicket = new ST_TICKET();

                            retcode = Json_GMPSmartDLL.FP3_Pretotal(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                            if (retcode != 0)
                            {
                                HandleErrorCode(retcode);
                                return;
                            }

                            textBox1.Text = String.Format("ARATOPLAM {0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));

                            DisplayTransaction(m_stTicket, false);
                            HandleErrorCode(retcode);
                        }

                    }
                    break;

                case 33:    //Reverse Payment
                    {
                        groupBox16.Visible = true;
                        groupBox17.Visible = false;
                        tabControl1.SelectedTab = tabPage3;
                    }
                    break;

                case 34:    //Other Payment
                    {
                        groupBox16.Visible = false;
                        groupBox17.Visible = true;
                        tabControl1.SelectedTab = tabPage3;

                    }
                    break;

                case 43:    //credit
                    {

                        byte numberOfTotalRecords = 0;
                        byte numberOfTotalRecordsReceived = 0;
                        ST_PAYMENT_APPLICATION_INFO[] stPaymentApplicationInfo = new ST_PAYMENT_APPLICATION_INFO[24];
                        UInt32 amount = 0;
                        if (m_comboBoxCurrency.SelectedIndex == -1)
                        {
                            if (m_comboBoxCurrency.Items.Count > 0)
                                m_comboBoxCurrency.SelectedIndex = 0;
                            else
                                break;
                        }
                        UInt16 currencyOfPayment = (UInt16)m_comboBoxCurrency.SelectedIndex;

                        UInt32 retcode = Json_GMPSmartDLL.FP3_GetPaymentApplicationInfo(CurrentInterface, ref numberOfTotalRecords, ref numberOfTotalRecordsReceived, ref stPaymentApplicationInfo, 24);

                        if (retcode != Defines.TRAN_RESULT_OK)
                            HandleErrorCode(retcode);
                        else if (numberOfTotalRecordsReceived == 0)
                            MessageBox.Show(Localization.PaymentAppNotFound, Localization.Error, MessageBoxButtons.OK);
                        else
                        {
                            ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];
                            for (int i = 0; i < stPaymentRequest.Length; i++)
                            {
                                stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
                            }

                            PaymentAppForm paf = new PaymentAppForm(numberOfTotalRecordsReceived, stPaymentApplicationInfo);
                            DialogResult dr = paf.ShowDialog();
                            if (dr != System.Windows.Forms.DialogResult.OK)
                                return;

                            if (currencyOfPayment == (UInt16)ECurrency.CURRENCY_NONE)
                                currencyOfPayment = (UInt16)ECurrency.CURRENCY_TL;

                            if (m_txtInputData.Text.Length != 0)
                            {
                                amount = (uint)getAmount(m_txtInputData.Text);
                                m_txtInputData.Text = "";

                            }

                            PaymentTypeForm ptf = new PaymentTypeForm();
                            DialogResult ptfDr = ptf.ShowDialog();
                            if (ptfDr != System.Windows.Forms.DialogResult.OK)
                                return;
                            stPaymentRequest[0].BankPaymentUniqueId = GenerateUniqueId();
                            switch (PaymentTypeForm.PaymentTypeIndex)
                            {
                                case 0:
                                    stPaymentRequest[0].subtypeOfPayment = Defines.PAYMENT_SUBTYPE_PROCESS_ON_POS;
                                    break;
                                case 1:
                                    stPaymentRequest[0].subtypeOfPayment = Defines.PAYMENT_SUBTYPE_SALE;
                                    break;
                                case 2:
                                    stPaymentRequest[0].subtypeOfPayment = Defines.PAYMENT_SUBTYPE_INSTALMENT_SALE;
                                    break;
                                case 3:
                                    stPaymentRequest[0].subtypeOfPayment = Defines.PAYMENT_SUBTYPE_LOYALTY_PUAN;
                                    break;
                                default:
                                    return;
                            }

                            int numberOfinstallments = 0;
                            int bonusAmount = 0;
                            GetInputForm gif;

                            if ((stPaymentRequest[0].subtypeOfPayment == Defines.PAYMENT_SUBTYPE_PROCESS_ON_POS) || (stPaymentRequest[0].subtypeOfPayment == Defines.PAYMENT_SUBTYPE_INSTALMENT_SALE))
                            {
                                do
                                {

                                    gif = new GetInputForm(Localization.InstalmentCount, "0", 2);
                                    DialogResult dr2 = gif.ShowDialog();
                                    if (dr2 != System.Windows.Forms.DialogResult.OK)
                                        return;

                                    Int32.TryParse(gif.textBox1.Text, out numberOfinstallments);
                                } while (numberOfinstallments > 9);
                            }


                            if (stPaymentRequest[0].subtypeOfPayment == Defines.PAYMENT_SUBTYPE_LOYALTY_PUAN)
                            {
                                // partial bonus is not supported. If payment has been started as Loyalty, bonusAmount must equal to Amount.
                                bonusAmount = (int)amount;
                                //do
                                //{
                                //    gif = new GetInputForm(Localization.BonusAmount, amount.ToString(), 2);
                                //    DialogResult dr3 = gif.ShowDialog();
                                //    if (dr3 != System.Windows.Forms.DialogResult.OK)
                                //        return;
                                //    Int32.TryParse(gif.textBox1.Text, out bonusAmount);
                                //} while (amount != bonusAmount);
                            }

                            stPaymentRequest[0].typeOfPayment = (uint)EPaymentTypes.PAYMENT_BANK_CARD;
                            stPaymentRequest[0].payAmount = amount;
                            stPaymentRequest[0].payAmountBonus = (uint)bonusAmount;

                            stPaymentRequest[0].payAmountCurrencyCode = currencyOfPayment;
                            //if (paf.pstPaymentApplicationInfoSelected.u16BKMId.Equals(null))
                            //    stPaymentRequest[0].bankBkmId = 0;
                            if (paf.pstPaymentApplicationInfoSelected == null)
                                stPaymentRequest[0].bankBkmId = 0;
                            else
                                stPaymentRequest[0].bankBkmId = paf.pstPaymentApplicationInfoSelected.u16BKMId;
                            stPaymentRequest[0].numberOfinstallments = (ushort)numberOfinstallments;

                            stPaymentRequest[0].transactionFlag = 0x00000000;
                            if (m_chcManualPanEntryNotAllowed.Checked)
                                stPaymentRequest[0].transactionFlag |= Defines.BANK_TRAN_FLAG_MANUAL_PAN_ENTRY_NOT_ALLOWED;
                            if (m_chcLoyaltyPointNotSupported.Checked)
                                stPaymentRequest[0].transactionFlag |= Defines.BANK_TRAN_FLAG_LOYALTY_POINT_NOT_SUPPORTED_FOR_TRANS;
                            if (m_chcAllInputFromEcr.Checked)
                                stPaymentRequest[0].transactionFlag |= Defines.BANK_TRAN_FLAG_ALL_INPUT_FROM_EXTERNAL_SYSTEM;
                            if (m_chcDoNotAskForMissingLoyaltyPoint.Checked)
                                stPaymentRequest[0].transactionFlag |= Defines.BANK_TRAN_FLAG_DO_NOT_ASK_FOR_MISSING_LOYALTY_POINT;
                            if (m_chcAuthorisationForInvoicePayment.Checked)
                                stPaymentRequest[0].transactionFlag |= Defines.BANK_TRAN_FLAG_AUTHORISATION_FOR_INVOICE_PAYMENT;
                            if (m_chcSaleWithoutCampaign.Checked)
                                stPaymentRequest[0].transactionFlag |= Defines.BANK_TRAN_FLAG_SALE_WITHOUT_CAMPAIGN;

                            stPaymentRequest[0].rawData = Encoding.Default.GetBytes("RawData from external application for the payment application");
                            stPaymentRequest[0].rawDataLen = (ushort)stPaymentRequest[0].rawData.Length;

                            GetPayment(stPaymentRequest, 1);
                        }
                    }
                    break;

                case 46:    //Payment Cancel
                    {
                        UInt32 retcode;
                        UInt16 indexOfPayment;
                        ST_TICKET m_stTicket = new ST_TICKET();
                        string display = "";

                        if (m_rbBatchMode.Checked)
                        {
                            byte[] buffer = new byte[1024];
                            int bufferLen = 0;

                            bufferLen = GMPSmartDLL.prepare_VoidPayment(buffer, bufferLen, 0);
                            AddIntoCommandBatch("prepare_VoidPayment", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                        }
                        else
                        {
                            if (m_txtInputData.Text == "")
                            {
                                while (true)
                                {

                                    retcode = Json_GMPSmartDLL.FP3_GetTicket(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                                    if (retcode != 0)
                                        break;

                                    if (m_stTicket.totalNumberOfPrinterLines > m_stTicket.numberOfPrinterLinesInThis)
                                        continue;

                                    if (m_stTicket.totalNumberOfItems > m_stTicket.numberOfItemsInThis)
                                        continue;

                                    if (m_stTicket.totalNumberOfPayments > m_stTicket.numberOfPaymentsInThis)
                                        continue;

                                    // Tüm item ve printer satırları geldi
                                    break;
                                }

                                if (retcode != Defines.TRAN_RESULT_OK)
                                {
                                    HandleErrorCode(retcode);
                                    return;
                                }

                                PaymentForm pf = new PaymentForm(m_stTicket.stPayment, m_stTicket.totalNumberOfPayments);
                                pf.ShowDialog();
                                if (pf.DialogResult != System.Windows.Forms.DialogResult.OK)
                                    return;

                                indexOfPayment = (ushort)(pf.selectedIndex + 1);
                            }
                            else
                            {
                                if (m_txtInputData.Text == "")
                                {
                                    MessageBox.Show("Index giriniz...");
                                    return;
                                }

                                indexOfPayment = Convert.ToUInt16(m_txtInputData.Text);
                                // less than 99 in order to prevent 
                                if (indexOfPayment == 0)
                                {
                                    MessageBox.Show("Index degeri 1 den başlamalı...");
                                    return;
                                }
                            }

                            retcode = Json_GMPSmartDLL.FP3_VoidPayment(CurrentInterface, GetTransactionHandle(CurrentInterface), (ushort)(indexOfPayment - 1), ref m_stTicket, Defines.TIMEOUT_CARD_TRANSACTIONS);
                            if (retcode == (uint)Defines.APP_ERR_FISCAL_INVALID_ENTRY)
                                MessageBox.Show("Out of Payment Index range...");

                            if (retcode != 0)
                            {
                                HandleErrorCode(retcode);
                                return;
                            }

                            UInt32 TicketAmount = m_stTicket.TotalReceiptAmount;
                            UInt32 PaymentAmount = m_stTicket.TotalReceiptPayment;

                            switch ((TTicketType)m_stTicket.ticketType)
                            {
                                case TTicketType.TAvans:
                                    display = String.Format("KASA AVANS TOTAL: {0}", formatAmount(m_stTicket.KasaAvansAmount, ECurrency.CURRENCY_TL));
                                    TicketAmount = m_stTicket.KasaAvansAmount;
                                    break;
                                case TTicketType.TPayment:
                                    display = String.Format("KASA PAYMENT TOTAL: {0}", formatAmount(m_stTicket.KasaPaymentAmount, ECurrency.CURRENCY_TL));
                                    TicketAmount = m_stTicket.KasaPaymentAmount;
                                    PaymentAmount = m_stTicket.TotalReceiptReversedPayment;
                                    break;
                                case TTicketType.TInvoice:
                                    display = String.Format("INVOICE TOTAL : {0}", formatAmount(m_stTicket.invoiceAmount, ECurrency.CURRENCY_TL));
                                    TicketAmount = m_stTicket.invoiceAmount;
                                    break;
                                case TTicketType.TRefund:
                                    display = String.Format("REFUND TOTAL :{0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));
                                    TicketAmount = m_stTicket.TotalReceiptAmount;
                                    PaymentAmount = m_stTicket.TotalReceiptReversedPayment;
                                    break;
                                case TTicketType.TCariHesap:
                                    display = String.Format("TOTAL : {0}", formatAmount(m_stTicket.stPayment[0].payAmount, ECurrency.CURRENCY_TL));
                                    
                                    break;
                                default:
                                    display = String.Format("TOTAL : {0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));
                                    TicketAmount = m_stTicket.TotalReceiptAmount;
                                    break;
                            }


                            if (m_stTicket.CashBackAmount != 0)
                                display += String.Format(Environment.NewLine + "CASHBACK : {0}", formatAmount(m_stTicket.CashBackAmount, ECurrency.CURRENCY_TL));
                            else
                            {
                                if ((TTicketType)m_stTicket.ticketType == TTicketType.TCariHesap)
                                    display += String.Format(Environment.NewLine + "REMAIN : {0}", formatAmount(m_stTicket.KasaPaymentAmount, ECurrency.CURRENCY_TL));
                                else
                                display += String.Format(Environment.NewLine + "REMAIN : {0}", formatAmount(m_stTicket.KasaPaymentAmount != 0 ? m_stTicket.KasaPaymentAmount - m_stTicket.stPayment[0].payAmount : TicketAmount - m_stTicket.TotalReceiptPayment, ECurrency.CURRENCY_TL));
                            }

                            if (display.Length != 0)
                                textBox1.Text = display;

                            DisplayTransaction(m_stTicket, false);
                            //	DisplayTransaction_Payment( &m_stTicket.stPayment[indexOfPayment-1], indexOfPayment-1 );
                            HandleErrorCode(retcode);
                        }
                    }
                    break;

                case 47:    //Item Cancel
                    {
                        int m_index;
                        UInt32 retcode;
                        UInt64 itemCount = 1;
                        ST_TICKET m_stTicket = new ST_TICKET();

                        if (m_txtInputData.Text == "")
                        {
                            MessageBox.Show("Urün Index girin...");
                            return;
                        }
                        m_index = Convert.ToInt32(m_txtInputData.Text);
                        if (m_index == 0)
                        {
                            MessageBox.Show("Index degeri 1 den baslamalı...");
                            return;
                        }

                        if (m_rbBatchMode.Checked)
                        {
                            byte[] buffer = new byte[1024];
                            int bufferLen = 0;

                            bufferLen = GMPSmartDLL.prepare_VoidItem(buffer, buffer.Length, (ushort)(m_index - 1), 1, 0);
                            AddIntoCommandBatch("prepare_VoidItem", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                        }
                        else
                        {
                            retcode = Json_GMPSmartDLL.FP3_VoidItem(CurrentInterface, GetTransactionHandle(CurrentInterface), (ushort)(m_index - 1), itemCount, 0, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                            if (retcode != 0)
                            {
                                HandleErrorCode(retcode);
                                return;
                            }

                            DisplayTransaction(m_stTicket, false);
                            // Show last item
                            //DisplayItem(&m_stTicket, index - 1);

                            m_txtInputData.Text = "";
                        }
                    }
                    break;

                case 48:    //Refund
                    {
                        UInt32 retcode = StartTicket(TTicketType.TRefund);
                        if (retcode != 0)
                            return;
                    }
                    break;

                case 49:    //Invoice
                    {
                        clearGroupBox();
                        tabControl1.SelectedTab = tabPage5;
                        groupBox15.Visible = true;
                    }
                    break;

                case 51:    //Ticket Sale
                    {
                        clearGroupBox();
                        tabControl1.SelectedTab = tabPage5;
                        groupBox11.Visible = true;
                        m_cmbSectionType.Items.Clear();

                        for (int i = 0; i < numberOfTotalDepartments; i++)
                        {
                            m_cmbSectionType.Items.Add(stDepartments[i].szDeptName);
                        }

                        m_cmbTicketType.SelectedIndex = 0;
                        m_cmbMovieType.SelectedIndex = 0;
                        if (m_cmbSectionType.Items.Count != 0)
                        {
                            m_cmbSectionType.SelectedIndex = 0;
                        }

                    }
                    break;

                case 52:    //amount increase
                    {
                        clearGroupBox();

                        tabControl1.SelectedTab = tabPage5;
                        m_type = 0;
                        groupBox12.Visible = true;
                    }
                    break;

                case 53:    //amount decrease
                    {
                        clearGroupBox();
                        tabControl1.SelectedTab = tabPage5;
                        m_type = 1;
                        groupBox12.Visible = true;
                    }
                    break;

                case 54:    //percent increase
                    {
                        clearGroupBox();
                        tabControl1.SelectedTab = tabPage5;
                        groupBox12.Visible = true;
                        m_type = 2;
                    }
                    break;

                case 55:    //percent decrease
                    {
                        clearGroupBox();
                        tabControl1.SelectedTab = tabPage5;
                        groupBox12.Visible = true;
                        m_type = 3;
                    }
                    break;

                case 59: //voidAll
                    OnBnClickedButtonVoidAll();
                    ClearTransactionUniqueId(CurrentInterface);
                    break;
                default:
                    break;
            }
        }

        private void SaveUniqueId(string BankPaymentUniqueId)
        {
            try
            {
                CreateDbFile();

                string sql = "insert into [UniqueIdData] (UniqueID, RecordTime) values ('" + BankPaymentUniqueId + "','" + DateTime.Now + "')";

                SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
                command.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, "Database insert hatası : " + ex.Message);
            }
            finally
            {
                if (m_dbConnection != null)
                {
                    m_dbConnection.Close();
                    m_dbConnection = null;
                    GC.Collect();
                }
            }
        }

        private string GenerateUniqueId()
        {
            byte[] szUniqueID = new byte[17];
            GMPSmartDLL.GenerateUniqueID(szUniqueID);
            string uniqueId = GMP_Tools.GetStringFromBytes(szUniqueID);
            SaveUniqueId(uniqueId);
            return uniqueId;
        }

        public string GetPaymentTypeName(int typeOfPayment)
        {
            switch ((EPaymentTypes)typeOfPayment)
            {
                case 0: return "NULL";
                case EPaymentTypes.PAYMENT_ALL: return "PAYMENT_ALL";
                case EPaymentTypes.PAYMENT_CASH_TL: return "PAYMENT_CASH_TL";
                case EPaymentTypes.PAYMENT_CASH_CURRENCY: return "PAYMENT_CASH_TL";
                case EPaymentTypes.PAYMENT_BANK_CARD: return "PAYMENT_CASH_TL";
                case EPaymentTypes.PAYMENT_YEMEKCEKI: return "PAYMENT_CASH_TL";
                case EPaymentTypes.PAYMENT_MOBILE: return "PAYMENT_CASH_TL";
                case EPaymentTypes.PAYMENT_HEDIYE_CEKI: return "PAYMENT_CASH_TL";
                case EPaymentTypes.PAYMENT_IKRAM: return "PAYMENT_CASH_TL";
                case EPaymentTypes.PAYMENT_KAPORA: return "PAYMENT_CASH_TL";
                case EPaymentTypes.PAYMENT_PUAN: return "PAYMENT_CASH_TL";
            }

            return "PAYMENT_UNDEFINED";
        }

        public string GetPaymentSubtypeName(int subtypeOfPayment)
        {
            switch ((EPaymentSubtypes)subtypeOfPayment)
            {
                case EPaymentSubtypes.PAYMENT_SUBTYPE_PROCESS_ON_POS:
                    return "PAYMENT_SUBTYPE_PROCESS_ON_POS";
                case EPaymentSubtypes.PAYMENT_SUBTYPE_SALE:
                    return "PAYMENT_SUBTYPE_SALE";
                case EPaymentSubtypes.PAYMENT_SUBTYPE_INSTALMENT_SALE:
                    return "PAYMENT_SUBTYPE_INSTALMENT_SALE";
                case EPaymentSubtypes.PAYMENT_SUBTYPE_LOYALTY_PUAN:
                    return "PAYMENT_SUBTYPE_LOYALTY_PUAN";
                case EPaymentSubtypes.PAYMENT_SUBTYPE_ADVANCE_REFUND:
                    return "PAYMENT_SUBTYPE_ADVANCE_REFUND";
                case EPaymentSubtypes.PAYMENT_SUBTYPE_INSTALLMENT_REFUND:
                    return "PAYMENT_SUBTYPE_INSTALLMENT_REFUND";
                case EPaymentSubtypes.PAYMENT_SUBTYPE_REFERENCED_REFUND:
                    return "PAYMENT_SUBTYPE_REFERENCED_REFUND";
                case EPaymentSubtypes.PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD:
                    return "PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD";
                case EPaymentSubtypes.PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD:
                    return "PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD";
            }

            return "PAYMENT_SUBTYPE_UNDEFINED";
        }

        UInt32 GetPayment(ST_PAYMENT_REQUEST[] stPaymentRequest, int numberOfPayments)
        {
            UInt32 retcode;
            ST_TICKET m_stTicket = new ST_TICKET();

            //char display[256];
            string display = "";


            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_Payment(buffer, buffer.Length, ref stPaymentRequest[0]);
                AddIntoCommandBatch("prepare_Payment", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                return Defines.TRAN_RESULT_OK;
            }
            else
            {
                m_lstBankErrorMessage.Items.Clear();

                retcode = Json_GMPSmartDLL.FP3_Payment(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stPaymentRequest[0], ref m_stTicket, 30000);

                for (int i = 0; i < m_stTicket.stPayment.Length; i++)
                {
                    if (m_stTicket.stPayment[i] != null)
                    {
                        if (m_stTicket.stPayment[i].stBankPayment.bankName != "")
                        {
                            m_lstBankErrorMessage.Items.Add(m_stTicket.stPayment[i].stBankPayment.bankName);
                            m_lstBankErrorMessage.Items.Add("Banking Error : " + m_stTicket.stPayment[i].stBankPayment.stPaymentErrMessage.ErrorCode + " " + m_stTicket.stPayment[i].stBankPayment.stPaymentErrMessage.ErrorMsg);
                            m_lstBankErrorMessage.Items.Add("Application Error : " + m_stTicket.stPayment[i].stBankPayment.stPaymentErrMessage.AppErrorCode + " " + m_stTicket.stPayment[i].stBankPayment.stPaymentErrMessage.AppErrorMsg);
                            m_lstBankErrorMessage.Items.Add("----------------------------------------------");
                        }
                    }
                }

                UInt32 TicketAmount = m_stTicket.TotalReceiptAmount + m_stTicket.KatkiPayiAmount;

                switch (retcode)
                {
                    case Defines.TRAN_RESULT_OK:

                        if (stPaymentRequest[0].numberOfinstallments != 0)
                            display += String.Format("TAKSIT SAYISI : {0}", stPaymentRequest[0].numberOfinstallments);

                        if (m_stTicket.KasaAvansAmount != 0)
                        {
                            MessageBox.Show("10");
                            MessageBox.Show(formatAmount(m_stTicket.KasaAvansAmount, ECurrency.CURRENCY_TL).ToString());
                            display += String.Format("KASA AVANS TOTAL: {0}", formatAmount(m_stTicket.KasaAvansAmount, ECurrency.CURRENCY_TL));
                            TicketAmount = m_stTicket.KasaAvansAmount;
                        }
                        else if (m_stTicket.invoiceAmount != 0)
                        {
                            MessageBox.Show("11");
                            display += String.Format("INVOICE TOTAL : {0}", formatAmount(m_stTicket.invoiceAmount, ECurrency.CURRENCY_TL));
                            TicketAmount = m_stTicket.invoiceAmount;
                        }
                        else if ((TTicketType)m_stTicket.ticketType == TTicketType.TCariHesap)
                        { 
                            MessageBox.Show("12");
                            display += String.Format("TOTAL : {0}", formatAmount(m_stTicket.stPayment[0].payAmount, ECurrency.CURRENCY_TL));
                        }
                        else
                        { 
                            MessageBox.Show("13");
                            display += String.Format("TOTAL : {0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));
                        }

                        if (m_stTicket.CashBackAmount != 0)
                        { 
                            display += String.Format(Environment.NewLine + "CASHBACK : {0}", formatAmount(m_stTicket.CashBackAmount, ECurrency.CURRENCY_TL));
                            MessageBox.Show("14");
                        }
                        else
                        {
                            MessageBox.Show("15");
                            if ((TTicketType)m_stTicket.ticketType == TTicketType.TCariHesap)
                            {
                                MessageBox.Show("16");
                                display += String.Format(Environment.NewLine + "REMAIN : {0}", formatAmount(m_stTicket.KasaPaymentAmount, ECurrency.CURRENCY_TL));
                            }
                            else
                            {
                                MessageBox.Show("17");
                                display += String.Format(Environment.NewLine + "REMAIN : {0}", formatAmount(m_stTicket.KasaPaymentAmount != 0 ? m_stTicket.KasaPaymentAmount - m_stTicket.stPayment[0].payAmount : TicketAmount - m_stTicket.TotalReceiptPayment, ECurrency.CURRENCY_TL));
                            }
                        }

                        if ((stPaymentRequest[0].typeOfPayment == (uint)EPaymentTypes.PAYMENT_BANK_CARD) || (stPaymentRequest[0].typeOfPayment == (uint)EPaymentTypes.PAYMENT_MOBILE))
                        {
                            MessageBox.Show("18");
                            display += String.Format(Environment.NewLine + "{0}", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.bankName);
                            display += String.Format(Environment.NewLine + "ONAY KODU : {0}", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.authorizeCode);
                            display += String.Format(Environment.NewLine + "{0}", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stCard.pan);
                        }

                        if (m_stTicket.TotalReceiptPayment >= TicketAmount)
                        {
                            MessageBox.Show("19");
                            retcode = GMPSmartDLL.FP3_PrintTotalsAndPayments(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                            if (retcode != Defines.TRAN_RESULT_OK && retcode != Defines.APP_ERR_ALREADY_DONE)
                                break;

                            retcode = GMPSmartDLL.FP3_PrintBeforeMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                            if (retcode != Defines.TRAN_RESULT_OK && retcode != Defines.APP_ERR_ALREADY_DONE)
                                break;

                            ST_USER_MESSAGE[] stUserMessage = new ST_USER_MESSAGE[1];
                            for (int i = 0; i < stUserMessage.Length; i++)
                            {
                                stUserMessage[i] = new ST_USER_MESSAGE();
                            }

                            stUserMessage[0].flag = Defines.PS_38 | Defines.PS_CENTER;
                            stUserMessage[0].message = Localization.ThankYou;
                            stUserMessage[0].len = (byte)Localization.ThankYou.Length;

                            retcode = Json_GMPSmartDLL.FP3_PrintUserMessage(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stUserMessage, (ushort)stUserMessage.Length, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                            retcode = GMPSmartDLL.FP3_PrintMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_CARD_TRANSACTIONS);
                            if (retcode != Defines.TRAN_RESULT_OK && retcode != Defines.APP_ERR_ALREADY_DONE)
                                break;

                            ClearTransactionUniqueId(CurrentInterface);
                            UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                            retcode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                            if (retcode == Defines.TRAN_RESULT_OK)
                                DeleteTrxHandles(CurrentInterface, TransHandle);
                        }

                        DisplayTransaction(m_stTicket, false);
                        break;

                    case Defines.APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_NO_MORE_ERROR_CODE:
                        DisplayTransaction(m_stTicket, false);
                        break;

                    case Defines.APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_MORE_ERROR_CODE:
                        DisplayTransaction(m_stTicket, false);

                        if (m_stTicket.totalNumberOfPayments != 0 && m_stTicket.stPayment[0] != null)
                        {
                            if ((stPaymentRequest[0].typeOfPayment == (uint)EPaymentTypes.PAYMENT_BANK_CARD) || (stPaymentRequest[0].typeOfPayment == (uint)EPaymentTypes.PAYMENT_MOBILE))
                            {
                                display += String.Format(Environment.NewLine + "{0}({1})", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.ErrorMsg
                                                                                    , m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.ErrorCode
                                                                                    );
                                display += String.Format(Environment.NewLine + "{0}({1})", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.AppErrorMsg
                                                                                    , m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.AppErrorCode
                                                                                    );
                            }
                        }

                        break;

                    default:
                        break;
                }

                if (display.Length != 0)
                    textBox1.Text = display;

                HandleErrorCode(retcode);

                m_comboBoxCurrency.SelectedIndex = 0;

            }
            return retcode;
        }

        private void m_openHandleMenuItem_Click(object sender, EventArgs e)
        {

            UInt32 retcode = Defines.TRAN_RESULT_OK;
        start_again:
            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_Start(buffer, buffer.Length, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0);
                AddIntoCommandBatch("prepare_Start", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {

                if (GetTransactionHandle(CurrentInterface) == 0)
                {
                    UInt64 TransactionHandle = 0;
                    retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TransactionHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
                    AddTrxHandles(CurrentInterface, TransactionHandle, isBackground);

                    if (retcode == Defines.APP_ERR_ALREADY_DONE)
                    {
                        DialogResult dr = MessageBox.Show(Localization.IncompleteTransactionDesc, Localization.IncompleteTransaction, MessageBoxButtons.OKCancel);
                        switch (dr)
                        {
                            case DialogResult.OK:
                                ReloadTransaction();
                                return;
                            case DialogResult.Cancel:
                                OnBnClickedButtonVoidAll();
                                goto start_again;
                        }
                    }
                }

                if (retcode != Defines.TRAN_RESULT_OK)
                {
                    HandleErrorCode(retcode);
                    // Handle Acik kalmasin...
                    UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                    uint resp = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                    if (resp == Defines.TRAN_RESULT_OK)
                        DeleteTrxHandles(CurrentInterface, TransHandle);
                }

                HandleErrorCode(retcode);
            }
        }

        private void m_closeHandleMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.DLL_RETCODE_FAIL;


            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_Close(buffer, buffer.Length);
                AddIntoCommandBatch("prepare_Close", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                retcode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                if (retcode == Defines.TRAN_RESULT_OK)
                    DeleteTrxHandles(CurrentInterface, TransHandle);
            }

            if (retcode == Defines.TRAN_RESULT_OK)
                ClearTransactionUniqueId(CurrentInterface);

            HandleErrorCode(retcode);

        }

        private void m_printTotalMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.DLL_RETCODE_FAIL;
            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_PrintTotalsAndPayments(buffer, buffer.Length);
                AddIntoCommandBatch("prepare_PrintTotalsAndPayments", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                retcode = GMPSmartDLL.FP3_PrintTotalsAndPayments(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
            }

            HandleErrorCode(retcode);
        }

        private void m_printBeforeMfMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.DLL_RETCODE_FAIL;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_PrintBeforeMF(buffer, buffer.Length);
                AddIntoCommandBatch("prepare_PrintBeforeMF", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                retcode = GMPSmartDLL.FP3_PrintBeforeMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
            }

            HandleErrorCode(retcode);

        }

        private void m_printMfMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.DLL_RETCODE_FAIL;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_PrintMF(buffer, buffer.Length);
                AddIntoCommandBatch("prepare_PrintMF", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                retcode = GMPSmartDLL.FP3_PrintMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_CARD_TRANSACTIONS);
            }

            HandleErrorCode(retcode);

        }

        private void m_btnSendInvoice_Click(object sender, EventArgs e)
        {
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_INVIOCE_INFO stInvoiceInfo = new ST_INVIOCE_INFO();

            UInt64 activeFlags = 0;

            stInvoiceInfo.source = (byte)m_cmbInvoiceType.SelectedIndex;
            stInvoiceInfo.amount = m_txtInvoiceAmount.Text == "" ? 0 : Convert.ToUInt64(m_txtInvoiceAmount.Text);
            stInvoiceInfo.currency = 949;
            if (m_comboBoxCurrency.Text != "")
                stInvoiceInfo.currency = Convert.ToUInt16(m_comboBoxCurrency.Text.Substring(0, 3));

            stInvoiceInfo.no = new byte[25];
            ConvertAscToBcdArray(m_txtInvoiceNo.Text, ref stInvoiceInfo.no, stInvoiceInfo.no.Length);
            stInvoiceInfo.tck_no = new byte[12];
            ConvertAscToBcdArray(m_txtTCK_No.Text, ref stInvoiceInfo.tck_no, stInvoiceInfo.tck_no.Length);
            stInvoiceInfo.vk_no = new byte[12];
            ConvertAscToBcdArray(m_txtVKN.Text, ref stInvoiceInfo.vk_no, stInvoiceInfo.vk_no.Length);

            stInvoiceInfo.date = new byte[3];
            string dateStr = m_dateInvoiceDate.Value.Day.ToString().PadLeft(2, '0') + m_dateInvoiceDate.Value.Month.ToString().PadLeft(2, '0') + m_dateInvoiceDate.Value.Year.ToString().Substring(2, 2).PadLeft(2, '0');

            ConvertStringToHexArray(dateStr, ref stInvoiceInfo.date, 3);
            Array.Reverse(stInvoiceInfo.date);

            if (m_chcIrsaliye.Checked)
                stInvoiceInfo.flag |= (uint)EInvoiceFlags.INVOICE_FLAG_IRSALIYE;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_SetInvoice(buffer, buffer.Length, ref stInvoiceInfo);
                AddIntoCommandBatch("prepare_SetInvoice", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                Array.Clear(buffer, 0, buffer.Length);
                bufferLen = 0;
                bufferLen = GMPSmartDLL.prepare_TicketHeader(buffer, buffer.Length, TTicketType.TInvoice);
                AddIntoCommandBatch("prepare_TicketHeader", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                tabControl1.SelectedTab = tabPage6;
            }
            else
            {
                UInt32 retcode = 0;
                if (GetTransactionHandle(CurrentInterface) == 0)
                {
                    UInt64 TransactionHandle = 0;
                    retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TransactionHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
                    AddTrxHandles(CurrentInterface, TransactionHandle, isBackground);

                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);

                    retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, (Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS), 0x00000000, Defines.TIMEOUT_DEFAULT);
                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);
                }

                retcode = Json_GMPSmartDLL.FP3_SetInvoice(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stInvoiceInfo, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), TTicketType.TInvoice, Defines.TIMEOUT_DEFAULT);
                if ((retcode != Defines.TRAN_RESULT_OK) && (retcode != Defines.APP_ERR_TICKET_HEADER_ALREADY_PRINTED))
                {
                    HandleErrorCode(retcode);
                    return;
                }

                HandleErrorCode(retcode);
                DisplayTransaction(m_stTicket, false);
            }
        }

        //input  : byte arr[0]=0x12
        //input  : byte arr[0]=0x34
        //output : "12 34"
        public static string ConvertByteArrayToString(byte[] byteArray, int byteArrayLen)
        {
            string str = "";

            try
            {
                StringBuilder sb = new StringBuilder();

                for (int i = 0; i < byteArrayLen; i++)
                {
                    sb.Append(byteArray[i].ToString("X2"));
                }
                return str = sb.ToString();
            }
            catch
            {
                return "0";
            }
        }

        //input  : "1234"
        //output : byte arr[0]=0x12
        //output : byte arr[0]=0x34
        public static void ConvertStringToHexArray(string s, ref byte[] Out_byteArr, int byteArrLen)
        {

            byte[] ba = new byte[s.Length / 2];
            for (int i = 0; i < ba.Length; i++)
            {
                string temp = s.Substring(i * 2, 2);
                ba[i] = Convert.ToByte(temp, 16);
            }
            byteArrLen = ba.Length;
            Array.Copy(ba, 0, Out_byteArr, 0, ba.Length);
        }

        //input  : "123"
        //output : 0x31, 0x32, 0x33
        public static void ConvertAscToBcdArray(string str, ref byte[] arr, int arrLen)
        {
            arrLen = str.Length;
            Array.Copy(Encoding.Default.GetBytes(str), 0, arr, 0, str.Length);
        }

        private void m_txtTCK_No_TextChanged(object sender, EventArgs e)
        {
            m_txtVKN.Text = "";
        }

        private void m_txtVKN_TextChanged(object sender, EventArgs e)
        {
            m_txtTCK_No.Text = "";
        }

        private void m_lstUniqueID_SelectedIndexChanged(object sender, EventArgs e)
        {
            byte[] m_uniqueId = new byte[24];

            ConvertStringToHexArray(m_lstUniqueID.SelectedItem.ToString(), ref m_uniqueId, m_uniqueId.Length);

            SetUniqueIdByInterface(CurrentInterface, m_uniqueId);

            string str = "";

            for (int j = 0; j < m_uniqueId.Length; j++)
            {
                str += m_uniqueId[j].ToString("X2");
            }

            textBox1.Text = str;
        }

        private void m_btn_TicketSale_Click(object sender, EventArgs e)
        {
            UInt32 retcode;
            string name = "";
            string barcode = "";
            int amount = getAmount(m_txtInputData.Text);
            UInt16 currency = 949;

            m_lblErrorCode.Text = "";

            if (m_comboBoxCurrency.Text != "")
                currency = Convert.ToUInt16(m_comboBoxCurrency.Text.Substring(0, 3));

            byte unitType = 0;
            UInt32 itemCount = 0;

            if (m_txtInputData.Text.Contains("X"))
            {
                itemCount = Convert.ToUInt32(m_txtInputData.Text.Substring(0, m_txtInputData.Text.IndexOf('X')));
            }
            byte itemCountPrecition = 0;
            int itemcountDotLocation = m_txtInputData.Text.IndexOf('.');
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_ITEM stItem = new ST_ITEM();


            stItem.type = Defines.ITEM_TYPE_TICKET;
            stItem.subType = (byte)((m_cmbMovieType.SelectedIndex * 4) + m_cmbTicketType.SelectedIndex);
            stItem.deptIndex = (byte)(m_cmbSectionType.SelectedIndex);
            stItem.amount = (uint)amount;
            stItem.currency = currency;
            stItem.count = itemCount;
            stItem.unitType = unitType;
            stItem.pluPriceIndex = 0;
            stItem.countPrecition = itemCountPrecition;
            stItem.name = name;
            stItem.barcode = barcode;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_ItemSale(buffer, buffer.Length, ref stItem);
                AddIntoCommandBatch("prepare_ItemSale", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {

                retcode = StartTicket(TTicketType.TProcessSale);
                if (retcode != Defines.TRAN_RESULT_OK)
                    return;

                if (GetTransactionHandle(CurrentInterface) == 0)
                {
                    DisplayTransaction(m_stTicket, false);
                    //DisplayItem(m_stTicket, m_stTicket.totalNumberOfItems - 1);
                }

                retcode = Json_GMPSmartDLL.FP3_ItemSale(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stItem, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                DisplayTransaction(m_stTicket, false);
                HandleErrorCode(retcode);

                //DisplayItem(&m_stTicket, m_stTicket.totalNumberOfItems - 1);

                m_txtInputData.Text = "";
                m_comboBoxCurrency.SelectedIndex = 0;
            }
        }

        private void m_btnAllTicket_Click(object sender, EventArgs e)
        {
            UInt16 m_itemNo = 0xFFFF;
            ItemProc(m_itemNo);
        }

        private void m_btnJustOneItem_Click(object sender, EventArgs e)
        {
            UInt16 m_itemNo = Convert.ToUInt16(m_txtItemOrderNo.Text);
            ItemProc(m_itemNo);
        }

        int m_type = 0;
        void ItemProc(UInt16 m_itemNo)
        {
            UInt32 retcode = Defines.DLL_RETCODE_FAIL;
            ST_TICKET m_stTicket = new ST_TICKET();
            if (m_txtInputData.Text == "")
            {
                MessageBox.Show("Lütfen Bir Oran veya Tutar Girin...");
                return;
            }
            int changedAmount = (int)getAmount(m_txtInputData.Text);

            if (m_itemNo != 0xFFFF)
                m_itemNo--;

            string str1 = "";

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                if (m_type == 0)    //amount Increase{
                {
                    bufferLen = GMPSmartDLL.prepare_Plus(buffer, buffer.Length, changedAmount, m_itemNo);
                    AddIntoCommandBatch("prepare_Plus", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                    str1 = Localization.AmountIncrease;
                }
                else if (m_type == 1)//amount Decrease
                {
                    bufferLen = GMPSmartDLL.prepare_Minus(buffer, buffer.Length, changedAmount, m_itemNo);
                    AddIntoCommandBatch("prepare_Minus", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                }
                else if (m_type == 2)//percent Increase
                {
                    bufferLen = GMPSmartDLL.prepare_Inc(buffer, buffer.Length, Convert.ToByte(m_txtInputData.Text), m_itemNo);
                    AddIntoCommandBatch("prepare_Inc", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                }
                else if (m_type == 3)//percent Decrease
                {
                    bufferLen = GMPSmartDLL.prepare_Dec(buffer, buffer.Length, Convert.ToByte(m_txtInputData.Text), m_itemNo);
                    AddIntoCommandBatch("prepare_Dec", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                }
            }
            else
            {
                GetInputForm gif = new GetInputForm("Kullanici Mesaji", "", 1);
                gif.ShowDialog();

                if (m_type == 0)    //amount Increase{
                {
                    retcode = Json_GMPSmartDLL.FP3_Plus(CurrentInterface, GetTransactionHandle(CurrentInterface), changedAmount, gif.textBox1.Text, ref m_stTicket, m_itemNo, Defines.TIMEOUT_DEFAULT);
                    str1 = Localization.AmountIncrease;
                }
                else if (m_type == 1)//amount Decrease
                {
                    retcode = Json_GMPSmartDLL.FP3_Minus(CurrentInterface, GetTransactionHandle(CurrentInterface), changedAmount, gif.textBox1.Text, ref m_stTicket, m_itemNo, Defines.TIMEOUT_DEFAULT);
                }
                else if (m_type == 2)//percent Increase
                {

                    retcode = Json_GMPSmartDLL.FP3_Inc(CurrentInterface, GetTransactionHandle(CurrentInterface), Convert.ToByte(m_txtInputData.Text), gif.textBox1.Text, ref m_stTicket, m_itemNo, ref changedAmount, Defines.TIMEOUT_DEFAULT);
                }
                else if (m_type == 3)//percent Decrease
                {
                    retcode = Json_GMPSmartDLL.FP3_Dec(CurrentInterface, GetTransactionHandle(CurrentInterface), Convert.ToByte(m_txtInputData.Text), gif.textBox1.Text, ref m_stTicket, m_itemNo, ref changedAmount, Defines.TIMEOUT_DEFAULT);
                }

                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                DisplayTransaction(m_stTicket, false);

                if (m_itemNo == 0xFFFF)
                {
                    textBox1.Text = String.Format("{0} ({1})" + Environment.NewLine + "{2}" + Environment.NewLine + "{3} {4}"
                                                    , str1
                                                    , Localization.AllTicket
                                                    , formatAmount((uint)changedAmount, ECurrency.CURRENCY_TL)
                                                    , Localization.SubTotal
                                                    , formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL)
                                                    );
                }
                else
                {
                    textBox1.Text = String.Format("{0} ({1} {2})" + Environment.NewLine + "+{3}" + Environment.NewLine + "{4} X {5} {6}"
                                                    , str1
                                                    , Localization.Item
                                                    , m_itemNo
                                                    , formatAmount((uint)changedAmount, ECurrency.CURRENCY_TL)
                                                    , formatCount(m_stTicket.SaleInfo[m_itemNo].ItemCount, m_stTicket.SaleInfo[m_itemNo].ItemCountPrecision, (EItemUnitTypes)m_stTicket.SaleInfo[m_itemNo].ItemUnitType)
                                                    , m_stTicket.SaleInfo[m_itemNo].Name
                                                    , formatAmount((uint)m_stTicket.SaleInfo[m_itemNo].ItemPrice, (ECurrency)m_stTicket.SaleInfo[m_itemNo].ItemCurrencyType)
                                                    );
                }

                m_txtInputData.Text = "";
                HandleErrorCode(retcode);

            }
        }

        uint[] userMessageFlags = new uint[40];

        private void m_btnCompleteUserMessage_Click(object sender, EventArgs e)
        {
            ST_USER_MESSAGE[] stUserMessage = new ST_USER_MESSAGE[1024];
            for (int i = 0; i < stUserMessage.Length; i++)
            {
                stUserMessage[i] = new ST_USER_MESSAGE();
            }
            int numberOfUserMessages = 0;

            numberOfUserMessages = m_lstUserMessage.Items.Count;
            for (int i = 0; i < numberOfUserMessages; i++)
            {
                string str = m_lstUserMessage.Items[i].ToString().Substring(0, m_lstUserMessage.Items[i].ToString().IndexOf('|'));
                stUserMessage[i].len = (UInt16)str.Length;
                stUserMessage[i].message = str;
                stUserMessage[i].flag = Convert.ToUInt32(m_lstUserMessage.Items[i].ToString().Substring(m_lstUserMessage.Items[i].ToString().IndexOf('|') + 1));
            }

            ST_TICKET m_stTicket = new ST_TICKET();

            UInt32 retcode = Defines.TRAN_RESULT_OK;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                //radioButton3 refers to QR Code, Use FP3_PrintUserMessage for QR.
                //For the rest use FP3_PrintUserMessage.
                if (radioButton3.Checked)
                {
                    bufferLen = Json_GMPSmartDLL.prepare_PrintUserMessage_Ex(buffer, buffer.Length, ref stUserMessage, (ushort)numberOfUserMessages);
                    AddIntoCommandBatch("prepare_PrintUserMessage_Ex", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                    tabControl1.SelectedTab = tabPage6;
                }
                else
                {
                    bufferLen = Json_GMPSmartDLL.prepare_PrintUserMessage(buffer, buffer.Length, ref stUserMessage, (ushort)numberOfUserMessages);
                    AddIntoCommandBatch("prepare_PrintUserMessage", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                    tabControl1.SelectedTab = tabPage6;
                }
            }
            else
            {
                if (radioButton3.Checked)
                    retcode = Json_GMPSmartDLL.FP3_PrintUserMessage_Ex(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stUserMessage, (ushort)numberOfUserMessages, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                else retcode = Json_GMPSmartDLL.FP3_PrintUserMessage(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stUserMessage, (ushort)numberOfUserMessages, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                HandleErrorCode(retcode);
            }
        }

        private void m_btnAddUserMessage_Click(object sender, EventArgs e)
        {
            ulong flag = 0;

            if (m_txtUserMessage.Text.Length > 1024)
            {
                MessageBox.Show(Localization.MessageField);
                return;
            }

            if (radioButton3.Checked) flag |= Defines.PS_QRCODE;
            else if (radioButton2.Checked) flag |= Defines.PS_BARCODE;
            else if (radioButton17.Checked)
            {
                flag |= Defines.PS_GRAPHIC;

                int pos = m_ListBitmapFiles.SelectedItem.ToString().IndexOf(" ");
                String dirName = GMP_Tools.SetEncoding(m_FileDirBitmap);
                int pos2 = dirName.IndexOf("\0");

                //m_txtUserMessage.Text = GMP_Tools.SetEncoding(m_FileDirBitmap) + "//" + m_ListBitmapFiles.SelectedItem.ToString().Substring(0, pos);
                m_txtUserMessage.Text = dirName.Substring(0, pos2) + "/" + m_ListBitmapFiles.SelectedItem.ToString().Substring(0, pos);

                //string new = m_ListBitmapFiles.SelectedItem.Substring(0, pos);
            }

            if (radioButton6.Checked) flag |= Defines.PS_12; //Defines.PS_MULT2
            if (radioButton18.Checked) flag |= Defines.PS_16;
            else if (radioButton5.Checked) flag |= Defines.PS_24;
            else if (radioButton4.Checked) flag |= Defines.PS_32;  //Defines.PS_MULT4
            else if (radioButton19.Checked) flag |= Defines.PS_38;
            else if (radioButton7.Checked) flag |= Defines.PS_48;   //Defines.PS_MULT8

            if (radioButton9.Checked) flag |= Defines.PS_BOLD;
            else if (radioButton8.Checked) flag |= Defines.PS_INVERTED;

            if (radioButton12.Checked)
                flag |= Defines.PS_CENTER;
            else if (radioButton11.Checked)
                flag |= Defines.PS_RIGHT;

            m_lstUserMessage.Items.Add(m_txtUserMessage.Text + "|" + flag.ToString());
            m_txtUserMessage.Text = "";
        }

       
        public void m_btnFunctionMessage_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.TRAN_RESULT_OK;

            ST_FUNCTION_PARAMETERS stFunctionParameters = new ST_FUNCTION_PARAMETERS();


            ST_PAYMENT_REQUEST StPaymentRequest = new ST_PAYMENT_REQUEST();
            byte NumberOfTotalRecords = 0;
            byte NumberOfTotalRecordsReceived = 0;
            ST_PAYMENT_APPLICATION_INFO[] StPaymentApplicationInfo = new ST_PAYMENT_APPLICATION_INFO[24];
            uint Amount = 0;
            DialogResult dr;
            GetInputForm gif;
            PaymentAppForm paf;
            BankRefundParameters brp = new BankRefundParameters();
            BankAppParams bp = new BankAppParams();
            byte NumberOfTotalRecord = 24;
            byte NumberOfTotalRecordReceived = 0;

            UInt16 currencyOfPayment = 949;
            if (m_comboBoxCurrency.Text != "")
                currencyOfPayment = Convert.ToUInt16(m_comboBoxCurrency.Text.Substring(0, 3));

            ST_LOYALTY_SERVICE_INFO[] stLoyaltyServiceInfo = new ST_LOYALTY_SERVICE_INFO[32];
            for (int i = 0; i < stLoyaltyServiceInfo.Length; i++)
            {
                stLoyaltyServiceInfo[i] = new ST_LOYALTY_SERVICE_INFO();
            }

            int funcFlag = 0;
            foreach (Control item in groupBox8.Controls)
            {
                RadioButton rb = (RadioButton)item;
                if (rb.Checked)
                {
                    funcFlag = Convert.ToInt32(rb.Name.Substring(rb.Name.Length - 2));
                }
            }

            FunctionFlags eFunc = (FunctionFlags)funcFlag;
            
            switch (eFunc)
            {
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_PAYMENT_VAS_IPTAL:
                    
                    if (m_txtInputData.Text != "")
                    {
                        Amount = Convert.ToUInt32(m_txtInputData.Text);
                    }
                    else
                    {
                        MessageBox.Show("Tutar Girin...");
                        return;
                    }

                    for (int i = 0; i < StPaymentApplicationInfo.Length; i++)
                    {
                        StPaymentApplicationInfo[i] = new ST_PAYMENT_APPLICATION_INFO();
                    }

                    retcode = Json_GMPSmartDLL.FP3_GetVasApplicationInfo(CurrentInterface, ref NumberOfTotalRecord, ref NumberOfTotalRecordReceived, ref StPaymentApplicationInfo, (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_LOYALTY);
                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);
                    else if (NumberOfTotalRecordReceived == 0)
                        MessageBox.Show("ÖKC Üzerinde Ödeme Uygulanaması Bulunamadı", "HATA", MessageBoxButtons.OK);
                    else
                    {
                        paf = new PaymentAppForm(NumberOfTotalRecordReceived, StPaymentApplicationInfo);
                        dr = paf.ShowDialog();
                        if (dr != System.Windows.Forms.DialogResult.OK)
                            return;

                        if (paf.pstPaymentApplicationInfoSelected == null)
                        {
                            MessageBox.Show("Lütfen UYGULAMA Seçiniz");
                            return;
                        }

                        if (paf.pstPaymentApplicationInfoSelected.u16BKMId.Equals(null))
                        {
                            MessageBox.Show("UYGULAMA ID = 0");
                            return;
                        }

                        if (paf.pstPaymentApplicationInfoSelected.AppType == (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_LOYALTY)
                        {
                            NumberOfTotalRecords = 5;
                            NumberOfTotalRecordsReceived = 0;
                            retcode = Json_GMPSmartDLL.FP3_GetVasLoyaltyServiceInfo(CurrentInterface, ref NumberOfTotalRecords, ref NumberOfTotalRecordsReceived, ref stLoyaltyServiceInfo, paf.pstPaymentApplicationInfoSelected.u16AppId);
                            if (retcode != Defines.TRAN_RESULT_OK)
                                HandleErrorCode(retcode);
                            else if (NumberOfTotalRecordsReceived == 0)
                                MessageBox.Show("ÖKC Üzerinde Servis Listesi Bulunamadı", "HATA", MessageBoxButtons.OK);
                            else
                            {
                                paf = new PaymentAppForm(NumberOfTotalRecordsReceived, stLoyaltyServiceInfo);
                                dr = paf.ShowDialog();
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;

                                if (paf.m_stLoyaltyServiceInfo == null)
                                {
                                    MessageBox.Show("Lütfen Servis Seçiniz");
                                    return;
                                }


                                gif = new GetInputForm("PROVISION ID", "", 2);
                                DialogResult dr2 = gif.ShowDialog();
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;

                                PaymentAppForm paf2 = new PaymentAppForm(1);
                                dr = paf2.ShowDialog();
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;

                                StPaymentRequest.PaymentProvisionId = gif.textBox1.Text;
                                StPaymentRequest.typeOfPayment = paf2.m_paymentType;
                                StPaymentRequest.payAmountCurrencyCode = currencyOfPayment;
                                StPaymentRequest.payAmount = Amount;
                                StPaymentRequest.bankBkmId = paf.pstLoyaltyServiceInfoSelected.u16AppId;
                                StPaymentRequest.LoyaltyServiceId = paf.pstLoyaltyServiceInfoSelected.ServiceId;
                            }
                        }
                        else if (paf.pstPaymentApplicationInfoSelected.AppType == (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_YEMEKCEKI)
                        {
                            gif = new GetInputForm("PROVISION ID", "", 2);
                            DialogResult dr2 = gif.ShowDialog();
                            if (dr != System.Windows.Forms.DialogResult.OK)
                                return;

                            StPaymentRequest.PaymentProvisionId = gif.textBox1.Text;
                            StPaymentRequest.typeOfPayment = (ushort)EPaymentTypes.PAYMENT_YEMEKCEKI;
                            StPaymentRequest.payAmountCurrencyCode = currencyOfPayment;
                            StPaymentRequest.payAmount = Amount;
                            StPaymentRequest.bankBkmId = paf.pstLoyaltyServiceInfoSelected.u16AppId;
                        }
                        else if (paf.pstPaymentApplicationInfoSelected.AppType == (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_PAYMENT)
                        {
                            gif = new GetInputForm("PROVISION ID", "", 2);
                            DialogResult dr2 = gif.ShowDialog();
                            if (dr != System.Windows.Forms.DialogResult.OK)
                                return;

                            PaymentAppForm paf2 = new PaymentAppForm(1);
                            dr = paf2.ShowDialog();
                            if (dr != System.Windows.Forms.DialogResult.OK)
                                return;

                            StPaymentRequest.PaymentProvisionId = gif.textBox1.Text;
                            StPaymentRequest.typeOfPayment = paf2.m_paymentType;
                            StPaymentRequest.payAmountCurrencyCode = currencyOfPayment;
                            StPaymentRequest.payAmount = Amount;
                            StPaymentRequest.bankBkmId = paf.pstLoyaltyServiceInfoSelected.u16AppId;
                        }
                        retcode = Json_GMPSmartDLL.FP3_FunctionVasPaymentRefund(CurrentInterface, ref StPaymentRequest, 120 * 1000);
                    }

                    break;

                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BANKA_IADE:

                    if (m_txtInputData.Text != "")
                    {
                        Amount = Convert.ToUInt32(m_txtInputData.Text);
                    }
                    else
                    {
                        MessageBox.Show("Tutar Girin...");
                        return;
                    }

                    retcode = Json_GMPSmartDLL.FP3_GetPaymentApplicationInfo(CurrentInterface, ref NumberOfTotalRecords, ref NumberOfTotalRecordsReceived, ref StPaymentApplicationInfo, 24);
                    if (retcode != Defines.TRAN_RESULT_OK)
                    {
                        HandleErrorCode(retcode);
                        return;
                    }
                    else if (NumberOfTotalRecordsReceived == 0)
                    {
                        MessageBox.Show("ÖKC Üzerinde Ödeme Uygulaması Bulunamadı", "HATA", MessageBoxButtons.OK);
                        return;
                    }

                    paf = new PaymentAppForm(NumberOfTotalRecordsReceived, StPaymentApplicationInfo);
                    dr = paf.ShowDialog();
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;
                    if (paf.pstPaymentApplicationInfoSelected == null)
                    {
                        MessageBox.Show("Select BANK first...");
                        return;
                    }
                    if (paf.pstPaymentApplicationInfoSelected.u16BKMId.Equals(null))
                        StPaymentRequest.bankBkmId = 0;
                    else
                    {
                        StPaymentRequest.bankBkmId = paf.pstPaymentApplicationInfoSelected.u16BKMId;
                    }

                    StPaymentRequest.typeOfPayment = (uint)FunctionFlags.GMP_EXT_DEVICE_FUNC_BANKA_IADE;
                    StPaymentRequest.payAmount = Amount;
                    StPaymentRequest.payAmountCurrencyCode = (ushort)ECurrency.CURRENCY_TL;

                    bp = new BankAppParams(true);
                    dr = bp.ShowDialog();
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    // if ASK_FOR_MISSING_INPUTS is true, set the flag
                    if (bp.missingInput == true)
                        StPaymentRequest.transactionFlag |= (uint)Defines.BANK_TRAN_FLAG_ASK_FOR_MISSING_REFUND_INPUTS;

                    PaymentRefundForm redundForm = new PaymentRefundForm();
                    dr = redundForm.ShowDialog();
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    StPaymentRequest.subtypeOfPayment = Defines.PAYMENT_SUBTYPE_PROCESS_ON_POS;

                    switch (PaymentRefundForm.PaymentRefundIndex)
                    {
                        case 0:
                            StPaymentRequest.subtypeOfPayment = Defines.PAYMENT_SUBTYPE_REFERENCED_REFUND;
                            break;
                        case 1:
                            StPaymentRequest.subtypeOfPayment = Defines.PAYMENT_SUBTYPE_ADVANCE_REFUND;
                            break;
                        case 2:
                            StPaymentRequest.subtypeOfPayment = Defines.PAYMENT_SUBTYPE_INSTALLMENT_REFUND;
                            break;
                        case 3:
                            StPaymentRequest.subtypeOfPayment = Defines.PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD;
                            break;
                        case 4:
                            StPaymentRequest.subtypeOfPayment = Defines.PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD;
                            break;
                        default:
                            break;
                    }

                    // nakit iade
                    if (StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_ADVANCE_REFUND)
                    {
                        gif = new GetInputForm("LOYALTY AMOUNT TO REFUND", "0", 2);
                        dr = gif.ShowDialog();
                        StPaymentRequest.payAmountBonus = Convert.ToUInt32(gif.textBox1.Text);
                        if (dr != System.Windows.Forms.DialogResult.OK)
                            return;
                    }

                    // taksitli iade
                    if (StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_INSTALLMENT_REFUND)
                    {
                        StPaymentRequest.numberOfinstallments = 1;
                        gif = new GetInputForm(Localization.InstalmentCount, "0-9", 2);
                        dr = gif.ShowDialog();
                        if (dr != System.Windows.Forms.DialogResult.OK)
                            return;

                        if (gif.Text == null || gif.Text == "")
                        {
                            MessageBox.Show("Enter number of installment count...");
                            return;
                        }
                        StPaymentRequest.numberOfinstallments = Convert.ToUInt16(gif.textBox1.Text);

                        gif = new GetInputForm("LOYALTY AMOUNT TO REFUND", "0", 2);
                        dr = gif.ShowDialog();
                        StPaymentRequest.payAmountBonus = Convert.ToUInt32(gif.textBox1.Text);
                        if (dr != System.Windows.Forms.DialogResult.OK)
                            return;
                    }

                    // taksitli ve nakit iade dışındaki iadeler :)
                    if (StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_REFERENCED_REFUND ||
                        StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_PROCESS_ON_POS ||
                        StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD ||
                        StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD)
                    {

                        brp = new BankRefundParameters(StPaymentRequest.bankBkmId);
                        dr = brp.ShowDialog();
                        if (dr != System.Windows.Forms.DialogResult.OK)
                            return;

                        if (StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_ADVANCE_REFUND)
                        {
                            gif = new GetInputForm(Localization.LoyaltyAmountToRefund, "", 2);
                            dr = gif.ShowDialog();
                            if (dr != System.Windows.Forms.DialogResult.OK)
                                return;
                            StPaymentRequest.payAmountBonus = Convert.ToUInt32(gif.textBox1.Text);
                        }

                        else if (StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_INSTALLMENT_REFUND)
                        {
                            //if (brp._OriginalInstallmentCount == true)
                            //{
                            StPaymentRequest.numberOfinstallments = 1;
                            gif = new GetInputForm(Localization.InstalmentCount, "0-9", 2);
                            dr = gif.ShowDialog();
                            if (dr != System.Windows.Forms.DialogResult.OK)
                                return;
                            StPaymentRequest.numberOfinstallments = Convert.ToUInt16(gif.textBox1.Text);
                            //}

                            //if (StPaymentRequest.payAmountBonus == 0)
                            //{
                            gif = new GetInputForm("LOYALTY AMOUNT TO REFUND", "0", 2);
                            dr = gif.ShowDialog();
                            StPaymentRequest.payAmountBonus = Convert.ToUInt32(gif.textBox1.Text);
                            if (dr != System.Windows.Forms.DialogResult.OK)
                                return;
                            //}
                        }
                        else if ((StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_REFERENCED_REFUND) ||
                                 (StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_PROCESS_ON_POS) ||
                                 (StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_REFERENCED_REFUND_WITH_CARD) ||
                                 (StPaymentRequest.subtypeOfPayment == Defines.PAYMENT_SUBTYPE_REFERENCED_REFUND_WITHOUT_CARD))
                        {
                            if (StPaymentRequest.payAmount == 0)
                            {
                                gif = new GetInputForm("AMOUNT TO BE REFUNDED", "0", 2);
                                dr = gif.ShowDialog();
                                UInt32.TryParse(gif.textBox1.Text, out StPaymentRequest.payAmount);
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;
                            }

                            if (brp._LoyaltyPointToRefund == true)
                            {
                                if (StPaymentRequest.payAmountBonus == 0)
                                {
                                    gif = new GetInputForm("LOYALTY AMOUNT TO REFUND", "0", 2);
                                    dr = gif.ShowDialog();
                                    StPaymentRequest.payAmountBonus = Convert.ToUInt32(gif.textBox1.Text);
                                    if (dr != System.Windows.Forms.DialogResult.OK)
                                        return;
                                }
                            }

                            //CurrencyCode
                            if (brp._CurrencyCodeOfAmountToRefund == true)
                            {
                                if (StPaymentRequest.payAmountCurrencyCode == 0)
                                {
                                    gif = new GetInputForm("CURRENCY CODE", "0", 2);
                                    dr = gif.ShowDialog();
                                    StPaymentRequest.payAmountCurrencyCode = Convert.ToByte(gif.textBox1.Text);
                                    if (dr != System.Windows.Forms.DialogResult.OK)
                                        return;
                                }
                            }

                            if (brp._RRN == true)
                            {
                                gif = new GetInputForm("REFRRN (max 12)", "123456789012", 2);
                                dr = gif.ShowDialog();
                                StPaymentRequest.OrgTransData.rrn = Encoding.Default.GetBytes(gif.textBox1.Text);
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;
                            }

                            if (brp._OriginalMerchantId == true)
                            {
                                gif = new GetInputForm("MERCHANT ID (max 15)", "123456789012345", 2);
                                dr = gif.ShowDialog();
                                StPaymentRequest.OrgTransData.MerchantId = Encoding.Default.GetBytes(gif.textBox1.Text);
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;
                            }

                            if (brp._AuthorizationNumber == true)
                            {
                                gif = new GetInputForm("AUTHORIZATION NUMBER (max 6)", "ABC123", 2);
                                dr = gif.ShowDialog();
                                StPaymentRequest.OrgTransData.AuthorizationCode = Encoding.Default.GetBytes(gif.textBox1.Text);
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;
                            }

                            if (brp._TransactionReferenceCode == true)
                            {
                                gif = new GetInputForm("REF CODE OF TRANSACTION (max 10)", "1234567890", 2);
                                dr = gif.ShowDialog();
                                StPaymentRequest.OrgTransData.referenceCodeOfTransaction = Encoding.Default.GetBytes(gif.textBox1.Text);
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;
                            }

                            if (brp._OriginalTransactionType)
                            {
                                gif = new GetInputForm("TYPE 1:SALE 2:INSTALMENT 3:POINT SALE", "1", 2);
                                dr = gif.ShowDialog();
                                Byte.TryParse(gif.textBox1.Text, out StPaymentRequest.OrgTransData.TransactionType);
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;
                            }

                            if (brp._OriginalTransactionAmount == true)
                            {
                                gif = new GetInputForm("ORG TRANSACTION AMOUNT", "0", 2);
                                dr = gif.ShowDialog();
                                UInt32.TryParse(gif.textBox1.Text, out StPaymentRequest.OrgTransData.TransactionAmount);
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;
                            }

                            if (brp._OriginalInstallmentCount == true)
                            {
                                if (StPaymentRequest.OrgTransData.TransactionType == 2)
                                {
                                    gif = new GetInputForm("INSTALMENT NUMBER (1-9)", "0", 2);
                                    dr = gif.ShowDialog();
                                    UInt16.TryParse(gif.textBox1.Text, out StPaymentRequest.OrgTransData.NumberOfinstallments);
                                    if (dr != System.Windows.Forms.DialogResult.OK)
                                        return;
                                    StPaymentRequest.OrgTransData.NumberOfinstallments = Convert.ToUInt16(gif.textBox1.Text);
                                }
                            }

                            if (brp._OriginalLoyaltyAmount == true)
                            {
                                gif = new GetInputForm("ORG LOYALTY AMOUNT", "0", 2);
                                dr = gif.ShowDialog();
                                StPaymentRequest.OrgTransData.LoyaltyAmount = Convert.ToUInt32(gif.textBox1.Text);
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;
                            }

                            //"1510221350"
                            //Kontrol et.
                            if (brp._OriginalTransactionDate == true)
                            {
                                gif = new GetInputForm("ORGINAL DATE YYMMDDHHMM", "1510221350", 2);
                                dr = gif.ShowDialog();
                                StPaymentRequest.OrgTransData.TransactionDate = new byte[5];
                                ConvertStringToHexArray(gif.textBox1.Text, ref StPaymentRequest.OrgTransData.TransactionDate, 5);
                                //StPaymentRequest.OrgTransData.TransactionDate = Encoding.Default.GetBytes(gif.textBox1.Text);
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;
                            }
                        }
                    }

                    ////////////////// Termina ID //////////////////////////
                    //if (brp._terminalId == true)
                    //{
                    gif = new GetInputForm("TERMINAL ID (max 8)", "12345678", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.terminalId = Encoding.Default.GetBytes(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;
                    //}

                    StPaymentRequest.rawData = Encoding.Default.GetBytes("RawData from external application for the payment application");
                    StPaymentRequest.rawDataLen = (ushort)StPaymentRequest.rawData.Length;
                    StPaymentRequest.BankPaymentUniqueId = GenerateUniqueId();
                    //    ST_PAYMENT_RESPONSE paymentResponse = new ST_PAYMENT_RESPONSE();
                    ST_PAYMENT_RESPONSE paymentResponse = new ST_PAYMENT_RESPONSE();
                    retcode = Json_GMPSmartDLL.FP3_FunctionBankingRefundExt(CurrentInterface, ref StPaymentRequest, ref paymentResponse, 120 * 1000);
                    DisplayPaymentResponse(paymentResponse);
                    break;
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BANKA_IPTAL:

                    if (m_txtInputData.Text != "")
                    {
                        Amount = Convert.ToUInt32(m_txtInputData.Text);
                    }
                    else
                    {
                        MessageBox.Show("Tutar Girin...");
                        return;
                    }

                    StPaymentRequest.typeOfPayment = (uint)FunctionFlags.GMP_EXT_DEVICE_FUNC_BANKA_IPTAL;
                    StPaymentRequest.subtypeOfPayment = 0;
                    StPaymentRequest.payAmount = Amount;
                    StPaymentRequest.payAmountCurrencyCode = (ushort)ECurrency.CURRENCY_TL;
                    StPaymentRequest.BankPaymentUniqueId = GenerateUniqueId();
                    retcode = Json_GMPSmartDLL.FP3_GetPaymentApplicationInfo(CurrentInterface, ref NumberOfTotalRecords, ref NumberOfTotalRecordsReceived, ref StPaymentApplicationInfo, 24);

                    if (retcode != Defines.TRAN_RESULT_OK)
                    {
                        HandleErrorCode(retcode);
                        return;
                    }
                    else if (NumberOfTotalRecordsReceived == 0)
                    {
                        MessageBox.Show("ÖKC Üzerinde Ödeme Uygulanaması Bulunamadı", "HATA", MessageBoxButtons.OK);
                        return;
                    }

                    paf = new PaymentAppForm(NumberOfTotalRecordsReceived, StPaymentApplicationInfo);
                    dr = paf.ShowDialog();
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    if (paf.pstPaymentApplicationInfoSelected.u16BKMId.Equals(null))
                        StPaymentRequest.bankBkmId = 0;
                    else
                        StPaymentRequest.bankBkmId = paf.pstPaymentApplicationInfoSelected.u16BKMId;

                    ////////////////// Termina ID //////////////////////////

                    gif = new GetInputForm("TERMINAL ID (max 8)", "12345678", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.terminalId = Encoding.Default.GetBytes(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("BATCH NO", "0", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.batchNo = Convert.ToUInt32(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("STAN NO", "0", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.stanNo = Convert.ToUInt32(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    StPaymentRequest.rawData = Encoding.Default.GetBytes("RawData from external application for the payment application");
                    StPaymentRequest.rawDataLen = (ushort)StPaymentRequest.rawData.Length;
                    StPaymentRequest.BankPaymentUniqueId = GenerateUniqueId();
                    retcode = Json_GMPSmartDLL.FP3_FunctionBankingRefund(CurrentInterface, ref StPaymentRequest, 120 * 1000);
                    break;
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_CEKMECE_ACMA:
                    retcode = GMPSmartDLL.FP3_FunctionOpenDrawer(CurrentInterface);
                    break;
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_BANKA_GUN_SONU:
                    ushort BkmID = 0;
                    ushort NumberOfBankResponse = 0;
                    gif = new GetInputForm("BKM ID", "0", 2);
                    dr = gif.ShowDialog();
                    BkmID = Convert.ToUInt16(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    ST_MULTIPLE_BANK_RESPONSE[] StMultipleBankResponse = new ST_MULTIPLE_BANK_RESPONSE[24];
                    retcode = Json_GMPSmartDLL.FP3_FunctionBankingBatch(CurrentInterface, BkmID, ref NumberOfBankResponse, ref StMultipleBankResponse, 120 * 1000);

                    break;
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_BANKA_PARAM_YUKLE:
                    retcode = GMPSmartDLL.FP3_FunctionBankingParameter(CurrentInterface, 120 * 1000);
                    break;
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_PARAM_YUKLE:
                    retcode = GMPSmartDLL.FP3_FunctionEcrParameter(CurrentInterface, 120 * 1000);
                    break;
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_CHECK_PAYMENT_STATUS:
                    ST_PAYMENT_RESPONSE paymentCheckResponse = new ST_PAYMENT_RESPONSE();
                    retcode = Json_GMPSmartDLL.FP3_FunctionPaymentCheck(CurrentInterface, comboBoxUniquId.Text.Trim().ToCharArray(), ref paymentCheckResponse, 120 * 1000);
                    DisplayPaymentResponse(paymentCheckResponse);
                    break;
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_EKU_RAPOR_DETAIL:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_EKU_RAPOR_IKI_TARIH_ARASI:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_EKU_RAPOR_SON_KOPYA:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_EKU_RAPOR_SON_FIS_KOPYA:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_EKU_RAPOR_FISTEN_FISE:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_AYLIK_RAPOR_GONDER:
                case FunctionFlags.GMP_EXT_DEVICE_FUNC_EKU_RAPOR_SUMMARY:

                    if (m_ZNo_Start.Text != "")
                        stFunctionParameters.start.ZNo = Convert.ToUInt32(m_ZNo_Start.Text);
                    if (m_ZNo_Finish.Text != "")
                        stFunctionParameters.finish.ZNo = Convert.ToUInt32(m_ZNo_Finish.Text);
                    if (m_FNo_Start.Text != "")
                        stFunctionParameters.start.FNo = Convert.ToUInt32(m_FNo_Start.Text);
                    if (m_FNo_Finish.Text != "")
                        stFunctionParameters.finish.FNo = Convert.ToUInt32(m_FNo_Finish.Text);
                    if (m_EkuNo.Text != "")
                        stFunctionParameters.EKUNo = Convert.ToUInt32(m_EkuNo.Text);
                    stFunctionParameters.Password.supervisor = "";

                    PassForm pf = new PassForm();
                    pf.ShowDialog();

                    if (pf.m_PASS != "")
                        stFunctionParameters.Password.supervisor = pf.m_PASS;

                    if (checkBox1.Checked)
                    {
                        stFunctionParameters.start.date.day = (byte)m_Date_Start.Value.Day;
                        stFunctionParameters.start.date.month = (byte)m_Date_Start.Value.Month;
                        stFunctionParameters.start.date.year = Convert.ToByte(m_Date_Start.Value.Year.ToString().Substring(2, 2));
                        stFunctionParameters.start.time.hour = (byte)m_Date_Start.Value.Hour;
                        stFunctionParameters.start.time.minute = (byte)m_Date_Start.Value.Minute;
                        stFunctionParameters.start.time.second = (byte)m_Date_Start.Value.Second;
                        stFunctionParameters.finish.date.day = (byte)m_Date_Finish.Value.Day;
                        stFunctionParameters.finish.date.month = (byte)m_Date_Finish.Value.Month;
                        stFunctionParameters.finish.date.year = Convert.ToByte(m_Date_Finish.Value.Year.ToString().Substring(2, 2));
                        stFunctionParameters.finish.time.hour = (byte)m_Date_Finish.Value.Hour;
                        stFunctionParameters.finish.time.minute = (byte)m_Date_Finish.Value.Minute;
                        stFunctionParameters.finish.time.second = (byte)m_Date_Finish.Value.Second;
                    }

                    if (eFunc == FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER)
                    {
                        ST_Z_REPORT stZReport = new ST_Z_REPORT();
                        retcode = Json_GMPSmartDLL.FP3_FunctionReadZReport(CurrentInterface, ref stFunctionParameters, ref stZReport, 120 * 1000);

                        if (retcode == Defines.TRAN_RESULT_OK)
                            DisplayZReport(stZReport);
                    }
                    else if(eFunc == FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_AYLIK_RAPOR_GONDER)
                    {
                        ST_DM_REPORT stDM_Report = new ST_DM_REPORT();
                        retcode = Json_GMPSmartDLL.FP3_FunctionReadDM_Report(CurrentInterface, ref stFunctionParameters, ref stDM_Report, 120 * 1000);

                        if (retcode == Defines.TRAN_RESULT_OK)
                            DisplayDM_Report(stDM_Report);
                    }
                    else
                    {
                        if (pf.m_PASS != "")
                            MessageBox.Show(CurrentInterface.ToString());
                        MessageBox.Show(stFunctionParameters.ToString());
                            retcode = Json_GMPSmartDLL.FP3_FunctionReports(CurrentInterface, (int)eFunc, ref stFunctionParameters, 120 * 1000);
                    }
                    break;
            }

            HandleErrorCode(retcode);
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            m_Date_Start.Enabled = true;
            m_Date_Finish.Enabled = true;
        }

        private void TransactionInfo(string str)
        {
            ListViewItem item1 = new ListViewItem(str);
            m_listTransaction.Items.Add(item1.Text);
        }

        void DisplayDM_Report(ST_DM_REPORT pDM_Report)
        {
            tabControl1.SelectedTab = tabPage1;

            m_listTransaction.Items.Clear();

            TransactionInfo("*** AYLIK RAPOR ***");

            TransactionInfo(String.Format("versiyon                     : {0}", pDM_Report.versiyon));
            TransactionInfo(String.Format("IsyeriVKN                    : {0}", pDM_Report.IsyeriVKN));

            TransactionInfo("***********************");

            TransactionInfo(String.Format("AylikRaporNo                 : {0}", pDM_Report.AylikRaporNo));
            TransactionInfo(String.Format("GunlukRaporNo                : {0}", pDM_Report.GunlukRaporNo));
            TransactionInfo(String.Format("RaporUretilmeTarihi          : {0}", pDM_Report.RaporUretilmeTarihi));
            TransactionInfo(String.Format("RaporUretilmeSaati           : {0}", pDM_Report.RaporUretilmeSaati));
            TransactionInfo(String.Format("RaporDonemiBaslangicTarihi   : {0}", pDM_Report.RaporDonemiBaslangicTarihi));
            TransactionInfo(String.Format("RaporDonemiBitisTarihi       : {0}", pDM_Report.RaporDonemiBitisTarihi));

            TransactionInfo("***********************");

            TransactionInfo(String.Format("ToplamSatisTutari            : {0}", pDM_Report.ToplamSatisTutari));
            TransactionInfo(String.Format("ToplamKDV_Tutari             : {0}", pDM_Report.ToplamKDV_Tutari));
            TransactionInfo(String.Format("BeyanEdilecekKDV_Tutari      : {0}", pDM_Report.BeyanEdilecekKDV_Tutari));
            TransactionInfo(String.Format("IndirimToplamTutari          : {0}", pDM_Report.IndirimToplamTutari));
            TransactionInfo(String.Format("ArtirimToplamTutari          : {0}", pDM_Report.ArtirimToplamTutari));
            TransactionInfo(String.Format("IptalEdilenBelgeToplamTutari : {0}", pDM_Report.IptalEdilenBelgeToplamTutari));
            TransactionInfo(String.Format("IptalEdilenBelgeAdedi        : {0}", pDM_Report.IptalEdilenBelgeAdedi));

            TransactionInfo("*** KÜMÜLATİFLER ***");

            TransactionInfo(String.Format("KumulatifToplamSatisTutari   : {0}", pDM_Report.KumulatifToplamSatisTutari));
            TransactionInfo(String.Format("KumulatifToplamKDV_Tutari    : {0}", pDM_Report.KumulatifToplamKDV_Tutari));

            TransactionInfo("*** KDV GRUPLARI ***");

            TransactionInfo(String.Format("KDV_GrupAdedi                : {0}", pDM_Report.KDV_GrupAdedi));

            for (int i = 0; i < Convert.ToInt32(pDM_Report.KDV_GrupAdedi); ++i)
            {
                TransactionInfo(String.Format(" Kısım {0} ", (i + 1)));
                TransactionInfo(String.Format("     VergiToplamTutari   : {0} ", formatAmount(Convert.ToUInt32(pDM_Report.stKDV_Grubu[i].VergiToplamTutari), ECurrency.CURRENCY_NONE)));
                TransactionInfo(String.Format("     VergiToplamKDV      : {0} ", pDM_Report.stKDV_Grubu[i].VergiToplamKDV));
                TransactionInfo(String.Format("     VergiOrani          : {0} ", pDM_Report.stKDV_Grubu[i].VergiOrani));
            }

            TransactionInfo("*** MALİ FİŞLER ***");

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stOKCFisi.ToplamAdedi) > 0)
            {
                TransactionInfo(String.Format("OKC Fişi "));
                TransactionInfo(String.Format("     SatisTutariToplami      : {0}", pDM_Report.stOKC_Belge.stOKCFisi.SatisTutariToplami));
                TransactionInfo(String.Format("     KDV_Toplami             : {0}", pDM_Report.stOKC_Belge.stOKCFisi.KDV_Toplami));
                TransactionInfo(String.Format("     ToplamAdedi             : {0}", pDM_Report.stOKC_Belge.stOKCFisi.ToplamAdedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stDiger.stFatura.ToplamAdedi) > 0)
            {
                TransactionInfo(String.Format("Fatura "));
                TransactionInfo(String.Format("     SatisTutariToplami      : {0}", pDM_Report.stOKC_Belge.stDiger.stFatura.SatisTutariToplami));
                TransactionInfo(String.Format("     KDV_Toplami             : {0}", pDM_Report.stOKC_Belge.stDiger.stFatura.KDV_Toplami));
                TransactionInfo(String.Format("     ToplamAdedi             : {0}", pDM_Report.stOKC_Belge.stDiger.stFatura.ToplamAdedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stDiger.stSMM.ToplamAdedi) > 0)
            {
                TransactionInfo(String.Format("Serbest Meslek Makbuzu "));
                TransactionInfo(String.Format("     SatisTutariToplami      : {0}", pDM_Report.stOKC_Belge.stDiger.stSMM.SatisTutariToplami));
                TransactionInfo(String.Format("     KDV_Toplami             : {0}", pDM_Report.stOKC_Belge.stDiger.stSMM.KDV_Toplami));
                TransactionInfo(String.Format("     ToplamAdedi             : {0}", pDM_Report.stOKC_Belge.stDiger.stSMM.ToplamAdedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stDiger.stGiderPusulasi.ToplamAdedi) > 0)
            {
                TransactionInfo(String.Format("Gider Pusulası "));
                TransactionInfo(String.Format("     SatisTutariToplami      : {0}", pDM_Report.stOKC_Belge.stDiger.stGiderPusulasi.SatisTutariToplami));
                TransactionInfo(String.Format("     KDV_Toplami             : {0}", pDM_Report.stOKC_Belge.stDiger.stGiderPusulasi.KDV_Toplami));
                TransactionInfo(String.Format("     ToplamAdedi             : {0}", pDM_Report.stOKC_Belge.stDiger.stGiderPusulasi.ToplamAdedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stDiger.stMM.ToplamAdedi) > 0)
            {
                TransactionInfo(String.Format("Müstahsil Makbuzu "));
                TransactionInfo(String.Format("     SatisTutariToplami      : {0}", pDM_Report.stOKC_Belge.stDiger.stMM.SatisTutariToplami));
                TransactionInfo(String.Format("     KDV_Toplami             : {0}", pDM_Report.stOKC_Belge.stDiger.stMM.KDV_Toplami));
                TransactionInfo(String.Format("     ToplamAdedi             : {0}", pDM_Report.stOKC_Belge.stDiger.stMM.ToplamAdedi));
            }
            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stDiger.stBilet.ToplamAdedi) > 0)
            {
                TransactionInfo(String.Format("Bilet "));
                TransactionInfo(String.Format("     SatisTutariToplami      : {0}", pDM_Report.stOKC_Belge.stDiger.stBilet.SatisTutariToplami));
                TransactionInfo(String.Format("     KDV_Toplami             : {0}", pDM_Report.stOKC_Belge.stDiger.stBilet.KDV_Toplami));
                TransactionInfo(String.Format("     ToplamAdedi             : {0}", pDM_Report.stOKC_Belge.stDiger.stBilet.ToplamAdedi));
            }

            TransactionInfo("*** BİLGİ FİŞLERİ ***");

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.stFaturaBilgi.Adedi) > 0)
            {
                TransactionInfo(String.Format("Fatura"));
                TransactionInfo(String.Format("     ToplamTutari            : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stFaturaBilgi.ToplamTutari));
                TransactionInfo(String.Format("     Adedi                   : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stFaturaBilgi.Adedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.stFaturaTahsilati.Adedi) > 0)
            {
                TransactionInfo(String.Format("Fatura Tahsilatı"));
                TransactionInfo(String.Format("     ToplamTutari            : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stFaturaTahsilati.ToplamTutari));
                TransactionInfo(String.Format("     Adedi                   : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stFaturaTahsilati.Adedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.stYemekKarti.Adedi) > 0)
            {
                TransactionInfo(String.Format("Yemek Kartı"));
                TransactionInfo(String.Format("     ToplamTutari            : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stYemekKarti.ToplamTutari));
                TransactionInfo(String.Format("     Adedi                   : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stYemekKarti.Adedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.stAvans.Adedi) > 0)
            {
                TransactionInfo(String.Format("Avans"));
                TransactionInfo(String.Format("     ToplamTutari            : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stAvans.ToplamTutari));
                TransactionInfo(String.Format("     Adedi                   : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stAvans.Adedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.stCariHesap.Adedi) > 0)
            {
                TransactionInfo(String.Format("Cari Hesap"));
                TransactionInfo(String.Format("     ToplamTutari            : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stCariHesap.ToplamTutari));
                TransactionInfo(String.Format("     Adedi                   : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stCariHesap.Adedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.stDiger.Adedi) > 0)
            {
                TransactionInfo(String.Format("Diğer"));
                TransactionInfo(String.Format("     ToplamTutari            : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stDiger.ToplamTutari));
                TransactionInfo(String.Format("     Adedi                   : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stDiger.Adedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.stGenelToplam.Adedi) > 0)
            {
                TransactionInfo(String.Format("Genel Toplam"));
                TransactionInfo(String.Format("     ToplamTutari            : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stGenelToplam.ToplamTutari));
                TransactionInfo(String.Format("     Adedi                   : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.stGenelToplam.Adedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.OtoparkFisiAdedi) > 0)
            {
                TransactionInfo(String.Format("Otopark"));
                TransactionInfo(String.Format("     Adedi                   : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.OtoparkFisiAdedi));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.MaliFisYemekKartiTutari) > 0)
            {
                TransactionInfo(String.Format("Mali Yemek Kartı"));
                TransactionInfo(String.Format("     Tutari                  : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.MaliFisYemekKartiTutari));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.MaliFisFaturaTahsilatTutari) > 0)
            {
                TransactionInfo(String.Format("Mali Fatura Tahsilatı"));
                TransactionInfo(String.Format("     Tutari                  : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.MaliFisFaturaTahsilatTutari));
            }

            if (Convert.ToInt32(pDM_Report.stOKC_Belge.stBilgiFisleri.MaliFisDigerMatrahsiz) > 0)
            {
                TransactionInfo(String.Format("Mali Diğer Matrahsız"));
                TransactionInfo(String.Format("     Tutari                  : {0}", pDM_Report.stOKC_Belge.stBilgiFisleri.MaliFisDigerMatrahsiz));
            }

            TransactionInfo("*** ÖDEME BİLGİLERİ ***");

            TransactionInfo(String.Format("Nakit                        : {0}", pDM_Report.stOdemeToplami.Nakit));
            TransactionInfo(String.Format("KrediKarti                   : {0}", pDM_Report.stOdemeToplami.KrediKarti));
            TransactionInfo(String.Format("YemekKarti                   : {0}", pDM_Report.stOdemeToplami.YemekKarti));
            TransactionInfo(String.Format("SanalPos                     : {0}", pDM_Report.stOdemeToplami.SanalPos));
            TransactionInfo(String.Format("HediyeKarti                  : {0}", pDM_Report.stOdemeToplami.HediyeKarti));
            TransactionInfo(String.Format("HavaleEFT                    : {0}", pDM_Report.stOdemeToplami.HavaleEFT));
            TransactionInfo(String.Format("E_ParaHizliPara              : {0}", pDM_Report.stOdemeToplami.E_ParaHizliPara));
            TransactionInfo(String.Format("SenetCek                     : {0}", pDM_Report.stOdemeToplami.SenetCek));
            TransactionInfo(String.Format("KrediliVadeliAcikHesap       : {0}", pDM_Report.stOdemeToplami.KrediliVadeliAcikHesap));            
            TransactionInfo(String.Format("Diger                        : {0}", pDM_Report.stOdemeToplami.Diger));

            TransactionInfo("***********************");

            TransactionInfo(String.Format("EJNO                         : {0}", pDM_Report.EkuNo));
        }

        void DisplayPaymentResponse(ST_PAYMENT_RESPONSE response)
        {
            tabControl1.SelectedTab = tabPage1;
            m_listTransaction.Items.Clear();
            TransactionInfo("*** REFUND Response ***");
            TransactionInfo(String.Format("Tutar                    : {0}", response.payAmount));
            TransactionInfo(String.Format("Taksit Sayısı            : {0}", response.stBankPayment.numberOfInstallments));
            TransactionInfo(String.Format("Flags                    : {0}", response.flags));
            TransactionInfo(String.Format("Ödeme Tipi               : {0}", response.typeOfPayment));
            TransactionInfo(String.Format("Bank Name                : {0}", response.stBankPayment.bankName));
            TransactionInfo(String.Format("Batch No                 : {0}", response.stBankPayment.batchNo));
            TransactionInfo(String.Format("STAN                     : {0}", response.stBankPayment.stan));
            TransactionInfo(String.Format("Merchant Id              : {0}", response.stBankPayment.merchantId));
            TransactionInfo(String.Format("Terminal Id              : {0}", response.stBankPayment.terminalId));
            TransactionInfo(String.Format("RRN                      : {0}", response.stBankPayment.rrn));
            TransactionInfo(String.Format("referenceCodeOfTransaction             : {0}", response.stBankPayment.referenceCodeOfTransaction));
            TransactionInfo(String.Format("Onay Kod                 : {0}", response.stBankPayment.authorizeCode));
            TransactionInfo(String.Format("PAN                      : {0}", response.stBankPayment.stCard.pan));
            TransactionInfo(String.Format("Kart Sahibi              : {0}", response.stBankPayment.stCard.holderName));
            TransactionInfo(String.Format("Hata Kodu                : {0}", response.stBankPayment.stPaymentErrMessage.ErrorCode));
            TransactionInfo(String.Format("Hata Mesajı              : {0}", response.stBankPayment.stPaymentErrMessage.ErrorMsg));
            TransactionInfo(String.Format("Uygulama Hata Kodu       : {0}", response.stBankPayment.stPaymentErrMessage.AppErrorCode));
            TransactionInfo(String.Format("Uygulama Hata Mesajı     : {0}", response.stBankPayment.stPaymentErrMessage.AppErrorMsg));
        }

        void DisplayZReport(ST_Z_REPORT pZReport)
        {
            tabControl1.SelectedTab = tabPage1;

            m_listTransaction.Items.Clear();

            TransactionInfo("*** Z REPORT ***");

            TransactionInfo(String.Format("Z NO   : {0}", pZReport.ZNo));
            TransactionInfo(String.Format("F NO   : {0}", pZReport.FNo));
            TransactionInfo(String.Format("EJNO   : {0}", pZReport.EJNo));
            TransactionInfo(String.Format("DATE   : {0}/{1}/{2}", pZReport.Date[2], pZReport.Date[1], pZReport.Date[0]));
            TransactionInfo(String.Format("HOUR   : {0}:{1}", pZReport.Time[0], pZReport.Time[1]));

            TransactionInfo("*** COUNTERS ***");
            TransactionInfo(String.Format("increaments            : {0}", pZReport.countOf.increaments));
            TransactionInfo(String.Format("decreases              : {0}", pZReport.countOf.decreases));
            TransactionInfo(String.Format("corrections            : {0}", pZReport.countOf.corrections));
            TransactionInfo(String.Format("fiscalReceipts         : {0}", pZReport.countOf.fiscalReceipts));
            TransactionInfo(String.Format("nonfiscalReceipts      : {0}", pZReport.countOf.nonfiscalReceipts));
            TransactionInfo(String.Format("customerReceipts       : {0}", pZReport.countOf.customerReceipts));
            TransactionInfo(String.Format("voidReceipts           : {0}", pZReport.countOf.voidReceipts));
            TransactionInfo(String.Format("invoiceSaleReceipts    : {0}", pZReport.countOf.invoiceSaleReceipts));
            TransactionInfo(String.Format("yemekcekiReceipts      : {0}", pZReport.countOf.yemekcekiReceipts));
            TransactionInfo(String.Format("carParkingEntryReceipts: {0}", pZReport.countOf.carParkingEntryReceipts));
            TransactionInfo(String.Format("fiscalReportReceipts   : {0}", pZReport.countOf.fiscalReportReceipts));
            TransactionInfo(String.Format("tasnifDisiReceipts     : {0}", pZReport.countOf.tasnifDisiReceipts));
            TransactionInfo(String.Format("invoiceReceipts        : {0}", pZReport.countOf.invoiceReceipts));
            TransactionInfo(String.Format("matrahsizReceipts      : {0}", pZReport.countOf.matrahsizReceipts));
            TransactionInfo(String.Format("serviceModeEntry       : {0}", pZReport.countOf.serviceModeEntry));
            TransactionInfo(String.Format("advanceReceipts        : {0}", pZReport.countOf.advanceReceipts));
            TransactionInfo(String.Format("openAccountReceipts    : {0}", pZReport.countOf.openAccountReceipts));

            TransactionInfo("*** TICKET TOTALS ***");
            TransactionInfo(String.Format("IncTotAmount        : {0}", formatAmount((uint)pZReport.IncTotAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("DecTotAmount        : {0}", formatAmount((uint)pZReport.DecTotAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("SaleVoidTotAmount   : {0}", formatAmount((uint)pZReport.SaleVoidTotAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("CorrectionTotAmount : {0}", formatAmount((uint)pZReport.CorrectionTotAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("DailyTotAmount      : {0}", formatAmount((uint)pZReport.DailyTotAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("DailyTotTax         : {0}", formatAmount((uint)pZReport.DailyTotTax, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("CumulativeTotAmount : {0}", formatAmount((uint)pZReport.CumulativeTotAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("CumulativeTotTax    : {0}", formatAmount((uint)pZReport.CumulativeTotTax, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("AvansTotalAmount    : {0}", formatAmount((uint)pZReport.AvansTotalAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("OdemeTotalAmount    : {0}", formatAmount((uint)pZReport.OdemeTotalAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("TaxRefundTotalAmount: {0}", formatAmount((uint)pZReport.TaxRefundTotalAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("MatrahsizTotalAmount: {0}", formatAmount((uint)pZReport.MatrahsizTotalAmount, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("OpenAccountTotalAmount: {0}", formatAmount((uint)pZReport.OpenAccountTotalAmount, ECurrency.CURRENCY_NONE)));


            TransactionInfo("*** PAYMENT TOTALS ***");
            TransactionInfo(String.Format("cashTotal           : {0}", formatAmount((uint)pZReport.payment.cashTotal, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("creditTotal         : {0}", formatAmount((uint)pZReport.payment.creditTotal, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("otherTotal          : {0}", formatAmount((uint)pZReport.payment.otherTotal, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("other.mobil         : {0}", formatAmount((uint)pZReport.payment.other.mobil, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("other.hediyeCeki    : {0}", formatAmount((uint)pZReport.payment.other.hediyeCeki, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("other.ikram         : {0}", formatAmount((uint)pZReport.payment.other.ikram, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("other.odemesiz      : {0}", formatAmount((uint)pZReport.payment.other.odemesiz, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("other.kapora        : {0}", formatAmount((uint)pZReport.payment.other.kapora, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("other.puan          : {0}", formatAmount((uint)pZReport.payment.other.puan, ECurrency.CURRENCY_NONE)));
            TransactionInfo(String.Format("other.giderPusulasi : {0}", formatAmount((uint)pZReport.payment.other.giderPusulasi, ECurrency.CURRENCY_NONE)));


            TransactionInfo("*** DEPARTMENT TOTALS ***");
            for (int i = 0; i < Defines.MAX_DEPARTMENT_COUNT; ++i)
            {
                TransactionInfo(String.Format("    DEPARTMEN {0}, {1}", (i + 1), GMP_Tools.SetEncoding(pZReport.department[i].name)));
                TransactionInfo(String.Format("    totalAmount   = {0}", formatAmount((uint)pZReport.department[i].totalAmount, ECurrency.CURRENCY_NONE)));
                TransactionInfo(String.Format("    totalQuantity = {0}", pZReport.department[i].totalQuantity));
            }
        }

        private void m_TaxAndDeptMenuItem_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = tabPage10;

            m_listTax.Items.Clear();

            ST_TAX_RATE[] stTaxRates = new ST_TAX_RATE[8];
            ST_DEPARTMENT[] stDepartments = new ST_DEPARTMENT[12];

            int numberOfTotalTaxratesReceived = 0;
            int numberOfTotalDepartmentsReceived = 0;

            UInt32 retcode = Json_GMPSmartDLL.FP3_GetTaxRates(CurrentInterface, ref numberOfTotalTaxRates, ref numberOfTotalTaxratesReceived, ref stTaxRates, 8);

            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return;
            }

            retcode = Json_GMPSmartDLL.FP3_GetDepartments(CurrentInterface, ref numberOfTotalDepartments, ref numberOfTotalDepartmentsReceived, ref stDepartments, 12);

            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return;
            }

            m_listTax.Items.Clear();

            for (int i = 0; i < numberOfTotalTaxratesReceived; i++)
            {
                ListViewItem item1 = new ListViewItem(i.ToString());
                item1.SubItems.Add(String.Format("%{0}.{1}", stTaxRates[i].taxRate / 100, (stTaxRates[i].taxRate % 100).ToString().PadLeft(2, '0')));

                m_listTax.Items.Add(item1);

            }
            dataGridView1.DataSource = null;
            dataGridView1.Rows.Clear();
            dataGridView1.Refresh();


            table = new DataTable();
            table.Columns.Add(Defines.m_taxIndCol);
            table.Columns.Add(Defines.m_nameCol);
            table.Columns.Add(Defines.m_unitCol);
            table.Columns.Add(Defines.m_amountCol);
            table.Columns.Add(Defines.m_currencyCol);
            table.Columns.Add(Defines.m_limitAmountCol);
            table.Columns.Add(Defines.m_lunchCardCol);

            for (int i = 0; i < numberOfTotalDepartmentsReceived; i++)
            {
                DataRow workRow = table.NewRow();
                workRow[0] = (stDepartments[i].u8TaxIndex).ToString();
                workRow[1] = (stDepartments[i].szDeptName).ToString();
                workRow[2] = (stDepartments[i].iUnitType).ToString();
                workRow[3] = (stDepartments[i].u64Price).ToString();
                workRow[4] = (stDepartments[i].iCurrencyType).ToString();
                workRow[5] = (stDepartments[i].u64Limit).ToString();
                workRow[6] = (stDepartments[i].bLuchVoucher).ToString();

                table.Rows.Add(workRow);
            }

            dataGridView1.DataSource = table;
            HandleErrorCode(retcode);
        }

        private void m_functionMessageMenuItem_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = tabPage9;
        }

        private void m_btnTaxAndDeptComplete_Click(object sender, EventArgs e)
        {
            ST_DEPARTMENT[] stDepartments = new ST_DEPARTMENT[12];

            for (int i = 0; i < stDepartments.Length; i++)
            {
                stDepartments[i] = new ST_DEPARTMENT();
            }

            for (int i = 0; i < 12; i++)
            {
                stDepartments[11 - i].u8TaxIndex = Convert.ToByte(dataGridView1.Rows[11 - i].Cells[0].Value);
                stDepartments[11 - i].szDeptName = dataGridView1.Rows[11 - i].Cells[1].Value.ToString();
                stDepartments[11 - i].iUnitType = (EItemUnitTypes)Enum.Parse(typeof(EItemUnitTypes), dataGridView1.Rows[11 - i].Cells[2].Value.ToString(), true);
                stDepartments[11 - i].u64Price = Convert.ToUInt64(dataGridView1.Rows[11 - i].Cells[3].Value);
                stDepartments[11 - i].iCurrencyType = (ECurrency)Enum.Parse(typeof(ECurrency), dataGridView1.Rows[11 - i].Cells[4].Value.ToString(), true);
                stDepartments[11 - i].u64Limit = Convert.ToUInt64(dataGridView1.Rows[11 - i].Cells[5].Value);
                stDepartments[11 - i].bLuchVoucher = Convert.ToByte(dataGridView1.Rows[11 - i].Cells[6].Value);
            }

            PassForm pf = new PassForm();
            pf.ShowDialog();

            UInt32 retcode = Defines.DLL_RETCODE_FAIL;
            if (pf.m_PASS != "")
            {
                retcode = Json_GMPSmartDLL.FP3_SetDepartments(CurrentInterface, ref stDepartments, 12, pf.m_PASS);
            }
            if (retcode == Defines.TRAN_RESULT_OK)
                retcode = GetDepartments();

            HandleErrorCode(retcode);
        }

        private void m_userMessageMenuItem_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = tabPage8;
        }

        private void m_setUniqueIDMenuItem_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = tabPage4;
            m_lstUniqueID.Items.Clear();

            UInt32 retcode;
            UInt16 totalNumberOfItems = 0;
            UInt16 numberOfItemsInThis = 0;

            ST_UNIQUE_ID[] stUniqueIdList = new ST_UNIQUE_ID[Defines.MAX_UNIQUE_ID];
            for (int i = 0; i < stUniqueIdList.Length; i++)
            {
                stUniqueIdList[i] = new ST_UNIQUE_ID();
            }

            UInt16 numberOfItems = 0;
            do
            {
                retcode = Json_GMPSmartDLL.FP3_FunctionGetUniqueIdList(CurrentInterface, ref stUniqueIdList, (ushort)(Defines.MAX_UNIQUE_ID - numberOfItems), numberOfItems, ref totalNumberOfItems, ref numberOfItemsInThis, 50000);
                if (retcode != Defines.TRAN_RESULT_OK)
                    break;
                else
                {
                    for (int i = 0; i < numberOfItemsInThis; i++)
                    {
                        string str = "";

                        for (int j = 0; j < 24; j++)
                        {
                            str += stUniqueIdList[i].uniqueId[j].ToString("X2");
                        }
                        ListViewItem item1 = new ListViewItem(str);


                        m_lstUniqueID.Items.Add(item1.Text);
                    }
                }

                numberOfItems += numberOfItemsInThis;

            } while (numberOfItems < totalNumberOfItems);

            HandleErrorCode(retcode);
        }

        private void m_getUniqueIDMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode;

            if (GetTransactionHandle(CurrentInterface) == 0)
            {
                UInt64 TransactionHandle = 0;
                ClearTransactionUniqueId(CurrentInterface);
                byte[] m_uniqueId;
                m_uniqueId = GetUniqueIdByInterface(CurrentInterface);

                retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TransactionHandle, isBackground, m_uniqueId, 24, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
                if (retcode == 0)
                {
                    SetUniqueIdByInterface(CurrentInterface, m_uniqueId);
                }
                AddTrxHandles(CurrentInterface, TransactionHandle, isBackground);

                if (retcode == Defines.TRAN_RESULT_OK)
                {
                    textBox1.Text = "UNIQUE ID: ";
                    m_uniqueId = GetUniqueIdByInterface(CurrentInterface);
                    for (int i = 0; i < m_uniqueId.Length; i++)
                    {
                        textBox1.Text += m_uniqueId[i].ToString("X2");
                    }

                    UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                    retcode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                    if (retcode == Defines.TRAN_RESULT_OK)
                        DeleteTrxHandles(CurrentInterface, TransHandle);
                }

                HandleErrorCode(retcode);
            }
        }

        private void m_currencyTableMenuItem_Click(object sender, EventArgs e)
        {
            CurrencyProfileForm form = new CurrencyProfileForm();
            if (form.retcode == 0)
                form.ShowDialog();
            else
                form.Dispose();
        }

        private void m_cashierTableMenuItem_Click(object sender, EventArgs e)
        {
            CashierForm cf = new CashierForm();
            cf.ShowDialog();
        }

        private void m_pluReadMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode;
            ulong m_handle = 0;
            // işlem başladıktan sonra izin verilmez;
            m_handle = GetTransactionHandle(CurrentInterface);
            if (m_handle != 0)
                return;

            if (m_txtInputData.Text.Length == 0)
                return;
            ST_PLU_RECORD StPluRecord = new ST_PLU_RECORD();
            ST_PLU_GROUP_RECORD[] StPluGroupRecord = new ST_PLU_GROUP_RECORD[4];
            int NumberOfGroups = 4;

            m_listTransaction.Items.Clear();

            byte[] inputBarcode = new byte[20];
            ConvertAscToBcdArray(m_txtInputData.Text, ref inputBarcode, 20);

            retcode = Json_GMPSmartDLL.FP3_GetPLU(CurrentInterface, m_txtInputData.Text, ref StPluRecord, ref StPluGroupRecord, NumberOfGroups, Defines.TIMEOUT_DEFAULT);

            if (retcode == Defines.TRAN_RESULT_OK)
            {
                tabControl1.SelectedIndex = 0;

                m_listTransaction.Items.Add("     " + Localization.PluItemSearch + "     ");
                m_listTransaction.Items.Add("________________________");
                m_listTransaction.Items.Add(String.Format(Localization.Barcode.PadRight(30) + ": {0}", StPluRecord.barcode));
                m_listTransaction.Items.Add((String.Format(Localization.Name.PadRight(30) + ": {0}", StPluRecord.name)));
                m_listTransaction.Items.Add((String.Format(Localization.DepartmentIndex.PadRight(30) + ": {0}", StPluRecord.deptIndex)));
                m_listTransaction.Items.Add((String.Format(Localization.UnitType.PadRight(30) + ": {0}", StPluRecord.unitType)));
                m_listTransaction.Items.Add((String.Format(Localization.Changing.PadRight(30) + ": {0}", StPluRecord.lastModified.ToString("X8"))));
                m_listTransaction.Items.Add((String.Format("FLAG       ".PadRight(30) + ": {0}", StPluRecord.flag.ToString("X8"))));
                m_listTransaction.Items.Add((String.Format("FIYAT({0}) ".PadRight(30) + ": {1}.{2}", StPluRecord.currency[0], StPluRecord.amount[0] / 100, StPluRecord.amount[0] % 100)));
                m_listTransaction.Items.Add((String.Format("FIYAT({0}) ".PadRight(30) + ": {1}.{2}", StPluRecord.currency[1], StPluRecord.amount[1] / 100, StPluRecord.amount[1] % 100)));
                m_listTransaction.Items.Add((String.Format("FIYAT({0}) ".PadRight(30) + ": {1}.{2}", StPluRecord.currency[2], StPluRecord.amount[2] / 100, StPluRecord.amount[2] % 100)));

                for (int i = 0; i < NumberOfGroups; i++)
                {
                    if (StPluGroupRecord[i].groupId == 0)
                        continue;

                    m_listTransaction.Items.Add(" ");
                    m_listTransaction.Items.Add((String.Format("GRUP {0}", i)));
                    m_listTransaction.Items.Add((String.Format("ID  : {0}", StPluGroupRecord[i].groupId)));
                    m_listTransaction.Items.Add((String.Format("ADI : {0}", StPluGroupRecord[i].name)));
                    m_listTransaction.Items.Add((String.Format("FLAG: {0}", StPluGroupRecord[i].groupFlag.ToString("X8"))));
                }
            }

            HandleErrorCode(retcode);
            m_txtInputData.Clear();
            //m_csTtemCount.Empty();
            m_comboBoxCurrency.SelectedIndex = 0;
        }

        private void m_SalePluToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode;
            string name = "";
            string barcode = m_txtInputData.Text;
            int amount = 0;
            UInt16 currency = 0;
            //if (m_comboBoxCurrency.Text != "")
            //    currency = Convert.ToUInt16(m_comboBoxCurrency.Text.Substring(0, 3));

            byte unitType = 0;
            UInt32 itemCount = 0;


            if (m_txtInputData.Text.Contains("X"))
            {
                itemCount = Convert.ToUInt32(m_txtInputData.Text.Substring(0, m_txtInputData.Text.IndexOf('X')));
            }
            byte itemCountPrecition = 0;
            int itemcountDotLocation = m_txtInputData.Text.IndexOf('.');
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_ITEM stItem = new ST_ITEM();

            if (m_txtInputData.Text.Length == 0)
                return;

            retcode = StartTicket(TTicketType.TProcessSale);
            if (retcode != Defines.TRAN_RESULT_OK)
                return;

            stItem.type = Defines.ITEM_TYPE_PLU;
            stItem.subType = 0;
            stItem.deptIndex = 0;
            stItem.amount = (uint)amount;
            stItem.currency = currency;
            stItem.count = itemCount;
            stItem.unitType = unitType;
            stItem.pluPriceIndex = 0;
            stItem.countPrecition = itemCountPrecition;
            stItem.name = name;
            stItem.barcode = barcode;

            // @ECR package 10 taxless flags are changed. ITEM_OPTION_TAX_EXCEPTION_TAXLESS still supported @ Package 9
            if (m_chcTaxFreeActive.Checked)
                stItem.flag |= (uint)EItemOptions.ITEM_TAX_EXCEPTION_VAT_INCLUDED_TO_PRICE;
            m_chcTaxFreeActive.Checked = false;

            if (m_chcTaxFreeActive2.Checked)
                stItem.flag |= (uint)EItemOptions.ITEM_TAX_EXCEPTION_VAT_NOT_INCLUDED_TO_PRICE;
            m_chcTaxFreeActive2.Checked = false;

            retcode = Json_GMPSmartDLL.FP3_ItemSale(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stItem, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return;
            }

            DisplayTransaction(m_stTicket, false);
            HandleErrorCode(retcode);

            textBox1.Text = "";
            m_txtInputData.Text = "";
            m_comboBoxCurrency.SelectedIndex = 0;
        }

        private void m_transactionsMenuItem_Click(object sender, EventArgs e)
        {
            DBForm dbf = new DBForm();
            dbf.ShowDialog();
        }

        private void m_readCardMenuItem_Click(object sender, EventArgs e)
        {
            byte READER_TYPE_MCR = 0x01;
            byte READER_TYPE_SCR = 0x02;
            byte READER_TYPE_CLESS = 0x04;

            ST_CARD_INFO stCardInfo = new ST_CARD_INFO();

            UInt32 retcode = Json_GMPSmartDLL.FP3_FunctionReadCard(CurrentInterface, (READER_TYPE_MCR | READER_TYPE_SCR | READER_TYPE_CLESS), ref stCardInfo, (60 * 1000));

            if (retcode == Defines.TRAN_RESULT_OK)
            {
                textBox1.Text = String.Format("CARD NO : {0}" + Environment.NewLine + "CARD HOLDER NAME : {2}" + Environment.NewLine, stCardInfo.pan, stCardInfo.holderName);
            }


            HandleErrorCode(retcode);
        }

        private void m_cashAdvantageMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode;
            ST_TICKET m_stTicket = new ST_TICKET();

            if (GetTransactionHandle(CurrentInterface) != 0)
            {
                MessageBox.Show("A Transaction has already started. Multiple sessions can not be managed", "Error", MessageBoxButtons.OK);
                return;
            }

            if (m_txtInputData.Text == "")
            {
                MessageBox.Show("Enter an Amount!", "Error", MessageBoxButtons.OK);
                return;
            }

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_KasaAvans(buffer, buffer.Length, getAmount(m_txtInputData.Text), "", "", "");
                AddIntoCommandBatch("prepare_KasaAvans", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                return;
            }
            else
            {
                retcode = StartTicket(TTicketType.TKasaAvans);
                if (retcode != Defines.TRAN_RESULT_OK)
                {
                    return;
                }

                retcode = Json_GMPSmartDLL.FP3_KasaAvans(CurrentInterface, GetTransactionHandle(CurrentInterface), getAmount(m_txtInputData.Text), ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }
                DisplayTransaction(m_stTicket, false);
                HandleErrorCode(retcode);
            }
        }

        private void m_cashPaymentMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode;
            ST_TICKET m_stTicket = new ST_TICKET();


            if (GetTransactionHandle(CurrentInterface) != 0)
            {
                MessageBox.Show("A Transaction has already started. Multiple sessions can not be managed", "Error", MessageBoxButtons.OK);
                return;
            }

            if (m_txtInputData.Text == "")
            {
                MessageBox.Show("Enter an Amount!", "Error", MessageBoxButtons.OK);
                return;
            }

            retcode = StartTicket(TTicketType.TPayment);
            if (retcode != Defines.TRAN_RESULT_OK)
                return;

            retcode = Json_GMPSmartDLL.FP3_KasaPayment(CurrentInterface, GetTransactionHandle(CurrentInterface), getAmount(m_txtInputData.Text), ref m_stTicket, Defines.TIMEOUT_DEFAULT);

            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return;
            }

            DisplayTransaction(m_stTicket, false);
            HandleErrorCode(retcode);
        }

        private void m_matrahsizMenuItem_Click(object sender, EventArgs e)
        {
            clearGroupBox();
            groupBox9.Visible = true;
            tabControl1.SelectedTab = tabPage5;
        }

        public void m_btnStartPairing_Click(object sender, EventArgs e)
        {

            ST_ECHO stEcho = new ST_ECHO();
            ST_GMP_PAIR pairing = new ST_GMP_PAIR();
            UInt64 TranHandle = 0;
            UInt32 RetCode;

            m_lblErrorCode.Text = "";

            RetCode = Json_GMPSmartDLL.FP3_Echo(CurrentInterface, ref stEcho, Defines.TIMEOUT_ECHO);

            if (RetCode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(RetCode);
                return;
            }

            pairing.szExternalDeviceBrand = "INGENICO";
            pairing.szExternalDeviceModel = "IWE280";
            pairing.szExternalDeviceSerialNumber = "12344567";
            pairing.szEcrSerialNumber = "JHWE20000079";
            pairing.szProcOrderNumber = "000001";
            pairing.szProcDate = m_lblProcDate.Text.Substring(0, 2) + m_lblProcDate.Text.Substring(3, 2) + m_lblProcDate.Text.Substring(6, 2);
            pairing.szProcTime = m_lblProcTime.Text.Substring(0, 2) + m_lblProcTime.Text.Substring(3, 2) + m_lblProcTime.Text.Substring(6, 2);

            RetCode = Json_GMPSmartDLL.FP3_StartPairingInit(CurrentInterface, ref pairing, ref pairingResp);

            if (RetCode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(RetCode);
                return;
            }

            ParserClass.DisplayEcrStatus(pairingResp, stEcho);

            RetCode = GetDepartments();
            if (RetCode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(RetCode);
                return;
            }

            RetCode = GetCurrency();
            if (RetCode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(RetCode);
                return;
            }

            // ÖKC'ye bir bağlantı yapıp, içinde tamamlanmamış işlem var mı diye bakılır
            // ÖKC'de gereksiz Unique ID oluşmaması için Unique ID aşağıdaki gibi verilmeli

            byte[] UniqueId = new byte[24] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

            RetCode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TranHandle, isBackground, UniqueId, UniqueId.Length, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
            AddTrxHandles(CurrentInterface, TranHandle, isBackground);

            int flag = 0;
            if (RetCode == Defines.APP_ERR_ALREADY_DONE)
            {
                DialogResult dr = MessageBox.Show(Localization.IncompleteTransactionDesc, Localization.IncompleteTransactionDesc, MessageBoxButtons.OKCancel);
                switch (dr)
                {
                    case DialogResult.OK:
                        RetCode = ReloadTransaction();
                        flag = 1;
                        break;
                    case DialogResult.Cancel:
                        OnBnClickedButtonVoidAll();
                        break;
                }
            }

            if (flag != 1)
            {
                UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                RetCode = Defines.TRAN_RESULT_OK;
                if (TransHandle != 0)
                {
                    RetCode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                    if (RetCode == Defines.TRAN_RESULT_OK)
                        DeleteTrxHandles(CurrentInterface, TransHandle);

                    ClearTransactionUniqueId(CurrentInterface);
                }

                flag = 0;
            }

            HandleErrorCode(RetCode);

            m_txtPluBarcode.Focus();
        }

        private void m_lstUserMessage_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListBox.SelectedObjectCollection selectedItems = new ListBox.SelectedObjectCollection(m_lstUserMessage);
            selectedItems = m_lstUserMessage.SelectedItems;

            if (m_lstUserMessage.SelectedIndex != -1)
            {
                for (int i = selectedItems.Count - 1; i >= 0; i--)
                    m_lstUserMessage.Items.Remove(selectedItems[i]);
            }
        }

        byte[] m_FileDirBitmap = new byte[128];
        private void m_btnGetBitmapFiles_Click(object sender, EventArgs e)
        {

            UInt32 retcode;
            //short len = 0;

            radioButton17.Checked = true;

            m_ListBitmapFiles.Items.Clear();
           //short maxBufferLen = 127;


            //retcode = GMPSmartDLL.FP3_GetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_FILEDIR_BITMAP, m_FileDirBitmap, maxBufferLen, ref len);
            //if (retcode != Defines.TRAN_RESULT_OK)
            //    goto Exit;
            string str = "/HOST";
            
            ConvertAscToBcdArray(str, ref m_FileDirBitmap, m_FileDirBitmap.Length);
            //System.Buffer.BlockCopy(str.ToCharArray(), 0, m_FileDirBitmap, 0, m_FileDirBitmap.Length);
                       
            m_btnGetBitmapFiles.Text = GMP_Tools.SetEncoding(m_FileDirBitmap);

            retcode = GMPSmartDLL.FP3_FileSystem_DirChange(CurrentInterface, GMP_Tools.SetEncoding(m_FileDirBitmap));
            if (retcode != Defines.TRAN_RESULT_OK)
                goto Exit;

            retcode = ListBitmapFiles(m_btnGetBitmapFiles.Text);
            if (retcode != Defines.TRAN_RESULT_OK)
                goto Exit;

        Exit:
            HandleErrorCode(retcode);
        }

        UInt32 ListBitmapFiles(string FileDirBitmap)
        {
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            ST_FILE[] stFiles = new ST_FILE[64];
            short numberOfFiles = 0;
            short maxNumberOfFiles = 64;


            m_ListBitmapFiles.Items.Clear();

            retcode = Json_GMPSmartDLL.FP3_FileSystem_DirListFiles(CurrentInterface, FileDirBitmap, ref stFiles, maxNumberOfFiles, ref numberOfFiles);
            if (retcode != Defines.TRAN_RESULT_OK)
                return retcode;

            for (int i = 0; i < numberOfFiles; i++)
            {
                string cs = "";
                //cs = String.Format("{0} {1}", GMP_Tools.SetEncoding(stFiles[i].fileName), stFiles[i].fileSize);
                cs = String.Format("{0} {1}", stFiles[i].fileName, stFiles[i].fileSize);
                m_ListBitmapFiles.Items.Add(cs);
            }

            return retcode;
        }

        private void m_btnDownloadBitmapFiles_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            short len = 0;

            OpenFileDialog file = new OpenFileDialog();
            file.Filter = "Bitmap Files (*.bmp)|*.bmp";
            file.FilterIndex = 2;
            file.RestoreDirectory = true;
            file.CheckFileExists = false;
            file.Title = "Bitmap Dosyası Seçiniz..";
            DialogResult dr = file.ShowDialog();

            radioButton17.Checked = true;
            //short maxBufferLen = 127;
            string name = GMP_Tools.SetEncoding(m_FileDirBitmap);
            if (string.IsNullOrWhiteSpace(name))
            {
                //retcode = GMPSmartDLL.FP3_GetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_FILEDIR_BITMAP, m_FileDirBitmap, maxBufferLen, ref len);
                //if (retcode != Defines.TRAN_RESULT_OK)
                //    goto Exit;
                string str = "/HOST";
                ConvertAscToBcdArray(str, ref m_FileDirBitmap, m_FileDirBitmap.Length);

                m_btnGetBitmapFiles.Text = GMP_Tools.SetEncoding(m_FileDirBitmap, 0, len);

            }

            if (dr == DialogResult.OK)
            {
                //retcode = GMPSmartDLL.FP3_FileSystem_DirChange(CurrentInterface, GMP_Tools.SetEncoding(Encoding.GetEncoding(65001).GetBytes(name)));
                //if (retcode != Defines.TRAN_RESULT_OK)
                //    goto Exit;

                //byte[] ecrFullPath = new byte[128];
                //Array.Copy(m_FileDirBitmap, 0, ecrFullPath, 0, len);
                //ecrFullPath[len] = (byte)'/';
              
                int startIndex = file.FileName.LastIndexOf('\\') + 1;
                string imageName = file.FileName.Substring(file.FileName.LastIndexOf('\\') + 1);
                //Array.Copy(Encoding.Default.GetBytes(file.FileName), startIndex, ecrFullPath, len + 1, copyLen);


                DownloadBitmapFile(file.FileName, Encoding.GetEncoding(65001).GetBytes("/HOST/"+imageName));

                retcode = ListBitmapFiles(GMP_Tools.SetEncoding(m_FileDirBitmap));
                if (retcode != Defines.TRAN_RESULT_OK)
                    goto Exit;
            }

        Exit:
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);

            }
        }

        void DownloadBitmapFile(string hostPathName, byte[] fileName)
        {
            UInt32 retcode = Defines.TRAN_RESULT_OK;

            if (hostPathName == "")
                return;

            using (BinaryReader b = new BinaryReader(File.Open(hostPathName, FileMode.Open)))
            {
                long HostFileSize = (long)b.BaseStream.Length;  //HostFileSize is the entire length of the file we are reading from. 

                //retcode = GMPSmartDLL.FP3_FileSystem_FileRemove(CurrentInterface, fileName);

                //if (retcode != defines.tran_result_ok)
                //    goto exit;

                byte[] buffer = new byte[1024];
                int offset = 0;

                short counter = 0;
                for (int i = 0; i < HostFileSize; i++)
                {
                    if (counter == 1024)
                    {
                        do
                        {
                            retcode = GMPSmartDLL.FP3_FileSystem_FileWrite(CurrentInterface, fileName, offset, 0, buffer, counter);
                            if (retcode == Defines.DLL_RETCODE_RECV_BUSY)
                                Thread.Sleep(1000);
                        } while (retcode == Defines.DLL_RETCODE_RECV_BUSY);
                        offset += counter;
                        counter = 0;
                    }
                    buffer[counter++] = b.ReadByte();
                }

                if (counter != 0)
                {
                    do
                    {
                        retcode = GMPSmartDLL.FP3_FileSystem_FileWrite(CurrentInterface, fileName, offset, 0, buffer, counter);
                        if (retcode == Defines.DLL_RETCODE_RECV_BUSY)
                            Thread.Sleep(1000);
                        else if (retcode != Defines.TRAN_RESULT_OK)
                        {
                            goto Exit;
                        }
                    } while (retcode == Defines.DLL_RETCODE_RECV_BUSY);
                }
            }

        Exit:

            HandleErrorCode(retcode);
        }

        private void m_btnRemoveBitmapFiles_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            //short len = 0;

            radioButton17.Checked = true;

            //short maxBufferLen = 127;
            int selected = m_ListBitmapFiles.SelectedIndex;
            if (selected < 0)
                return;

            string name = GMP_Tools.SetEncoding(m_FileDirBitmap);
            if (name[0] == '\0')
            {
                //retcode = GMPSmartDLL.FP3_GetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_FILEDIR_BITMAP, m_FileDirBitmap, maxBufferLen, ref len);

                //if (retcode != Defines.TRAN_RESULT_OK)
                //    goto Exit;

                string str = "/HOST";
                ConvertAscToBcdArray(str, ref m_FileDirBitmap, m_FileDirBitmap.Length);
                m_btnGetBitmapFiles.Text = GMP_Tools.SetEncoding(m_FileDirBitmap);
            }

            ListBitmapFiles(name);

        //Exit:
            HandleErrorCode(retcode);
        }

        private void radioButton20_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = new RadioButton();
            foreach (Control item in groupBox16.Controls)
            {
                if (item is RadioButton)
                {
                    rb = (RadioButton)item;
                    if (rb.Checked)
                    {
                        break;
                    }
                }
            }

            foreach (Control item in groupBox17.Controls)
            {
                if (item is RadioButton)
                {
                    if (((RadioButton)item).Checked)
                    {
                        rb = (RadioButton)item;
                        break;
                    }
                }
            }

            switch (rb.Text)
            {
                case "REVERSE_PAYMENT_CASH":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_CASH;
                    break;
                case "REVERSE_PAYMENT_BANK_CARD_VOID":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_VOID;
                    break;
                case "REVERSE_PAYMENT_BANK_CARD_REFUND":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_REFUND;
                    break;
                case "REVERSE_PAYMENT_YEMEKCEKI":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_YEMEKCEKI;
                    break;
                case "REVERSE_PAYMENT_MOBILE":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_MOBILE;
                    break;
                case "REVERSE_PAYMENT_HEDIYE_CEKI":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_HEDIYE_CEKI;
                    break;
                case "REVERSE_PAYMENT_PUAN":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_PUAN;
                    break;
                case "REVERSE_PAYMENT_ACIK_HESAP":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_ACIK_HESAP;
                    break;
                case "REVERSE_PAYMENT_KAPORA":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_KAPORA;
                    break;
                case "REVERSE_PAYMENT_GIDER_PUSULASI":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_GIDER_PUSULASI;
                    break;
                case "REVERSE_PAYMENT_BANKA_TRANSFERI":
                    m_PaymentType = EPaymentTypes.REVERSE_PAYMENT_BANKA_TRANSFERI;
                    break;
                case "PAYMENT_CASH_TL":
                    m_PaymentType = EPaymentTypes.PAYMENT_CASH_TL;
                    break;
                case "PAYMENT_CASH_CURRENCY":
                    m_PaymentType = EPaymentTypes.PAYMENT_CASH_CURRENCY;
                    break;
                case "PAYMENT_BANK_CARD":
                    m_PaymentType = EPaymentTypes.PAYMENT_BANK_CARD;
                    break;
                case "PAYMENT_YEMEKCEKI":
                    m_PaymentType = EPaymentTypes.PAYMENT_YEMEKCEKI;
                    break;
                case "PAYMENT_MOBILE":
                    m_PaymentType = EPaymentTypes.PAYMENT_MOBILE;
                    break;
                case "PAYMENT_HEDIYE_CEKI":
                    m_PaymentType = EPaymentTypes.PAYMENT_HEDIYE_CEKI;
                    break;
                case "PAYMENT_IKRAM":
                    m_PaymentType = EPaymentTypes.PAYMENT_IKRAM;
                    break;
                case "PAYMENT_ODEMESIZ":
                    m_PaymentType = EPaymentTypes.PAYMENT_ODEMESIZ;
                    break;
                case "PAYMENT_KAPORA":
                    m_PaymentType = EPaymentTypes.PAYMENT_KAPORA;
                    break;
                case "PAYMENT_PUAN":
                    m_PaymentType = EPaymentTypes.PAYMENT_PUAN;
                    break;
                case "PAYMENT_GIDER_PUSULASI":
                    m_PaymentType = EPaymentTypes.PAYMENT_GIDER_PUSULASI;
                    break;
                case "PAYMENT_BANKA_TRANSFERI":
                    m_PaymentType = EPaymentTypes.PAYMENT_BANKA_TRANSFERI;
                    break;
                case "PAYMENT_CEK":
                    m_PaymentType = EPaymentTypes.PAYMENT_CEK;
                    break;
                case "PAYMENT_ACIK_HESAP":
                    m_PaymentType = EPaymentTypes.PAYMENT_ACIK_HESAP;
                    break;
                default:
                    break;
            }
        }

        UInt32 ReversePayment(ST_PAYMENT_REQUEST pstPaymentRequest)
        {
            UInt32 retcode = Defines.DLL_RETCODE_FAIL;
            ST_TICKET m_stTicket = new ST_TICKET();
            string display = "";
            UInt32 TicketAmount = 0;
            UInt32 PaymentAmount = 0;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_ReversePayment(buffer, buffer.Length, ref pstPaymentRequest, 1);
                AddIntoCommandBatch("prepare_ReversePayment", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                return Defines.TRAN_RESULT_OK;
            }
            else
            {
                switch ((EPaymentTypes)pstPaymentRequest.typeOfPayment)
                {
                    case EPaymentTypes.REVERSE_PAYMENT_CASH:
                    case EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_VOID:
                    case EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_REFUND:
                    case EPaymentTypes.REVERSE_PAYMENT_YEMEKCEKI:
                    case EPaymentTypes.REVERSE_PAYMENT_MOBILE:
                    case EPaymentTypes.REVERSE_PAYMENT_HEDIYE_CEKI:

                        retcode = Json_GMPSmartDLL.FP3_ReversePayment(CurrentInterface, GetTransactionHandle(CurrentInterface), ref pstPaymentRequest, 1, ref m_stTicket, Defines.TIMEOUT_CARD_TRANSACTIONS);

                        break;
                    default:
                        return 0;
                }


                switch (retcode)
                {
                    case Defines.TRAN_RESULT_OK:
                        TicketAmount = m_stTicket.TotalReceiptAmount;
                        PaymentAmount = m_stTicket.TotalReceiptPayment;

                        switch ((TTicketType)m_stTicket.ticketType)
                        {
                            case TTicketType.TPayment:
                                display = String.Format("KASA PAYMENT TOTAL: {0}", formatAmount(m_stTicket.KasaPaymentAmount, ECurrency.CURRENCY_TL));
                                TicketAmount = m_stTicket.KasaPaymentAmount;
                                PaymentAmount = m_stTicket.TotalReceiptReversedPayment;
                                break;
                            case TTicketType.TRefund:
                                display = String.Format("REFUND TOTAL : {0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));
                                TicketAmount = m_stTicket.TotalReceiptAmount;
                                PaymentAmount = m_stTicket.TotalReceiptReversedPayment;
                                break;
                            case TTicketType.TCariHesap:
                                display = String.Format("TOTAL : {0}", formatAmount(m_stTicket.stPayment[0].payAmount, ECurrency.CURRENCY_TL));
                                break;
                            case TTicketType.TGiderPusulasi:
                                display = String.Format("Gider Pusulasi TOTAL : {0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));
                                TicketAmount = m_stTicket.TotalReceiptAmount;
                                PaymentAmount = m_stTicket.TotalReceiptReversedPayment;
                                break;
                            default:
                                display = String.Format("TOTAL : {0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));
                                TicketAmount = m_stTicket.TotalReceiptAmount;
                                break;
                        }
                        if ((TTicketType)m_stTicket.ticketType == TTicketType.TCariHesap)
                            display += String.Format(Environment.NewLine + "REMAIN : {0}", formatAmount(m_stTicket.KasaPaymentAmount, ECurrency.CURRENCY_TL));
                        else
                            display += String.Format(Environment.NewLine + "REMAIN : {0}", formatAmount(m_stTicket.KasaPaymentAmount != 0 ? m_stTicket.KasaPaymentAmount - m_stTicket.stPayment[0].payAmount : TicketAmount - m_stTicket.TotalReceiptPayment, ECurrency.CURRENCY_TL));

                        if ((pstPaymentRequest.typeOfPayment == (uint)EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_VOID) || (pstPaymentRequest.typeOfPayment == (uint)EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_REFUND) || (pstPaymentRequest.typeOfPayment == (uint)EPaymentTypes.REVERSE_PAYMENT_MOBILE))
                        {
                            display += String.Format(Environment.NewLine + "{0}", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.bankName);
                            display += String.Format(Environment.NewLine + "ONAY KODU : {0}", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.authorizeCode);
                            display += String.Format(Environment.NewLine + "{0}", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stCard.pan);
                        }

                        if (PaymentAmount >= TicketAmount)
                        {
                            retcode = GMPSmartDLL.FP3_PrintTotalsAndPayments(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                            if (retcode != Defines.TRAN_RESULT_OK)
                                break;

                            retcode = GMPSmartDLL.FP3_PrintBeforeMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                            if (retcode != Defines.TRAN_RESULT_OK)
                                break;

                            ST_USER_MESSAGE[] stUserMessage = new ST_USER_MESSAGE[1];
                            for (int i = 0; i < stUserMessage.Length; i++)
                                stUserMessage[i] = new ST_USER_MESSAGE();

                            stUserMessage[0].flag = Defines.PS_38 | Defines.PS_CENTER;
                            stUserMessage[0].message = Localization.VoidCompleted;
                            stUserMessage[0].len = (byte)Localization.VoidCompleted.Length;

                            retcode = Json_GMPSmartDLL.FP3_PrintUserMessage(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stUserMessage, (ushort)stUserMessage.Length, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                            //retcode = Json_GMPSmartDLL.FP3_PrintUserMessage_Ex(ref stUserMessage, (ushort)stUserMessage.Length, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                            retcode = GMPSmartDLL.FP3_PrintMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_CARD_TRANSACTIONS);
                            if (retcode != Defines.TRAN_RESULT_OK)
                                break;

                            ClearTransactionUniqueId(CurrentInterface);
                            UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                            retcode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                            if (retcode == Defines.TRAN_RESULT_OK)
                                DeleteTrxHandles(CurrentInterface, TransHandle);
                        }

                        DisplayTransaction(m_stTicket, false);
                        break;

                    case Defines.APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_NO_MORE_ERROR_CODE:
                        DisplayTransaction(m_stTicket, false);
                        break;

                    case Defines.APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_MORE_ERROR_CODE:
                        DisplayTransaction(m_stTicket, false);

                        switch ((EPaymentTypes)pstPaymentRequest.typeOfPayment)
                        {
                            case EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_VOID:
                            case EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_REFUND:
                            case EPaymentTypes.REVERSE_PAYMENT_YEMEKCEKI:
                            case EPaymentTypes.REVERSE_PAYMENT_MOBILE:
                            case EPaymentTypes.REVERSE_PAYMENT_HEDIYE_CEKI:
                                if (m_stTicket.totalNumberOfPayments == 0) break;

                                display += String.Format(Environment.NewLine + "{0}({1})", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.ErrorMsg
                                                                                    , m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.ErrorCode
                                                                                    );
                                display += String.Format(Environment.NewLine + "{0}({1})", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.AppErrorMsg
                                                                                    , m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.AppErrorCode
                                                                                    );
                                break;
                        }

                        break;

                    default:
                        break;
                }

                if (display.Length != 0)
                    textBox1.Text = display;

                HandleErrorCode(retcode);
                m_txtInputData.Text = "";
                m_comboBoxCurrency.SelectedIndex = 0;

                return retcode;
            }
        }

        private void m_btnCompleteReversePayment_Click(object sender, EventArgs e)
        {

            uint retcode;

            byte NumberOfTotalRecords = 0;
            byte NumberOfTotalRecordsReceived = 0;
            ST_PAYMENT_APPLICATION_INFO[] StPaymentApplicationInfo = new ST_PAYMENT_APPLICATION_INFO[24];
            ST_LOYALTY_SERVICE_INFO[] stLoyaltyServiceInfo = new ST_LOYALTY_SERVICE_INFO[32];

            m_lblErrorCode.Text = "";

            for (int i = 0; i < stLoyaltyServiceInfo.Length; i++)
            {
                stLoyaltyServiceInfo[i] = new ST_LOYALTY_SERVICE_INFO();
            }

            UInt16 VasAppId = 0x599F;

            PaymentAppForm paf;
            GetInputForm gif;
            DialogResult dr;
            uint amount = 0;
            UInt16 currencyOfPayment = 949;
            if (m_comboBoxCurrency.Text != "")
                currencyOfPayment = Convert.ToUInt16(m_comboBoxCurrency.Text.Substring(0, 3));

            amount = (uint)getAmount(m_txtInputData.Text);

            ST_PAYMENT_REQUEST StPaymentRequest = new ST_PAYMENT_REQUEST();

            StPaymentRequest.typeOfPayment = (uint)m_PaymentType;
            StPaymentRequest.subtypeOfPayment = 0;
            StPaymentRequest.payAmount = amount;
            StPaymentRequest.payAmountCurrencyCode = currencyOfPayment;

            switch (m_PaymentType)
            {
                case EPaymentTypes.REVERSE_PAYMENT_YEMEKCEKI:
                case EPaymentTypes.REVERSE_PAYMENT_MOBILE:
                case EPaymentTypes.REVERSE_PAYMENT_HEDIYE_CEKI:
                case EPaymentTypes.REVERSE_PAYMENT_PUAN:
                case EPaymentTypes.REVERSE_PAYMENT_ACIK_HESAP:

                    retcode = Json_GMPSmartDLL.FP3_GetVasApplicationInfo(CurrentInterface, ref NumberOfTotalRecords, ref NumberOfTotalRecordsReceived, ref StPaymentApplicationInfo, (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_ALL);

                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);
                    else if (NumberOfTotalRecordsReceived == 0)
                        MessageBox.Show("ÖKC Üzerinde Ödeme Uygulanaması Bulunamadı", "HATA", MessageBoxButtons.OK);
                    else
                    {
                        paf = new PaymentAppForm(NumberOfTotalRecordsReceived, StPaymentApplicationInfo);
                        dr = paf.ShowDialog();
                        if (dr != System.Windows.Forms.DialogResult.OK)
                            return;

                        if (paf.pstPaymentApplicationInfoSelected.AppType == (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_LOYALTY)
                        {
                            if (paf.pstPaymentApplicationInfoSelected == null)
                            {
                                MessageBox.Show("Lütfen UYGULAMA Seçiniz");
                                return;
                            }

                            if (paf.pstPaymentApplicationInfoSelected.u16BKMId.Equals(null))
                            {
                                MessageBox.Show("UYGULAMA ID = 0");
                                return;
                            }

                            NumberOfTotalRecords = 5;
                            NumberOfTotalRecordsReceived = 0;
                            retcode = Json_GMPSmartDLL.FP3_GetVasLoyaltyServiceInfo(CurrentInterface, ref NumberOfTotalRecords, ref NumberOfTotalRecordsReceived, ref stLoyaltyServiceInfo, VasAppId);
                            if (retcode != Defines.TRAN_RESULT_OK)
                                HandleErrorCode(retcode);
                            else if (NumberOfTotalRecordsReceived == 0)
                                MessageBox.Show("ÖKC Üzerinde Servis Listesi Bulunamadı", "HATA", MessageBoxButtons.OK);
                            else
                            {
                                paf = new PaymentAppForm(NumberOfTotalRecordsReceived, stLoyaltyServiceInfo);
                                dr = paf.ShowDialog();
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;

                                if (paf.m_stLoyaltyServiceInfo == null)
                                {
                                    MessageBox.Show("Lütfen Servis Seçiniz");
                                    return;
                                }

                                gif = new GetInputForm("PROVISION ID", "", 2);
                                DialogResult dr2 = gif.ShowDialog();
                                if (dr != System.Windows.Forms.DialogResult.OK)
                                    return;

                                StPaymentRequest.PaymentProvisionId = gif.textBox1.Text;
                                StPaymentRequest.bankBkmId = paf.pstLoyaltyServiceInfoSelected.u16AppId;
                                StPaymentRequest.LoyaltyServiceId = paf.pstLoyaltyServiceInfoSelected.ServiceId;
                            }
                        }
                        else if (paf.pstPaymentApplicationInfoSelected.AppType == (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_YEMEKCEKI)
                        {
                            gif = new GetInputForm("PROVISION ID", "", 2);
                            DialogResult dr2 = gif.ShowDialog();
                            if (dr != System.Windows.Forms.DialogResult.OK)
                                return;

                            StPaymentRequest.PaymentProvisionId = gif.textBox1.Text;
                        }
                        else if (paf.pstPaymentApplicationInfoSelected.AppType == (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_PAYMENT)
                        {
                            gif = new GetInputForm("PROVISION ID", "", 2);
                            DialogResult dr2 = gif.ShowDialog();
                            if (dr != System.Windows.Forms.DialogResult.OK)
                                return;

                            StPaymentRequest.PaymentProvisionId = gif.textBox1.Text;
                            StPaymentRequest.bankBkmId = paf.pstLoyaltyServiceInfoSelected.u16AppId;
                        }
                    }

                    break;

                case EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_VOID:

                    retcode = Json_GMPSmartDLL.FP3_GetPaymentApplicationInfo(CurrentInterface, ref NumberOfTotalRecords, ref NumberOfTotalRecordsReceived, ref StPaymentApplicationInfo, 24);

                    if (retcode != Defines.TRAN_RESULT_OK)
                    {
                        HandleErrorCode(retcode);
                        return;
                    }
                    else if (NumberOfTotalRecordsReceived == 0)
                    {
                        MessageBox.Show("ÖKC Üzerinde Ödeme Uygulanaması Bulunamadı", "HATA", MessageBoxButtons.OK);
                        return;
                    }

                    paf = new PaymentAppForm(NumberOfTotalRecordsReceived, StPaymentApplicationInfo);
                    dr = paf.ShowDialog();
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    if (paf.pstPaymentApplicationInfoSelected.u16BKMId.Equals(null))
                        StPaymentRequest.bankBkmId = 0;
                    else
                        StPaymentRequest.bankBkmId = paf.pstPaymentApplicationInfoSelected.u16BKMId;

                    ////////////////// Terminal ID //////////////////////////

                    gif = new GetInputForm("TERMINAL ID (max 8)", "12345678", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.terminalId = Encoding.Default.GetBytes(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("TYPE 1:SALE 2:INSTALMENT", "0", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.OrgTransData.TransactionType = Convert.ToByte(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    if (StPaymentRequest.OrgTransData.TransactionType == 2)
                    {
                        gif = new GetInputForm("INSTALMENT NUMBER (1-9)", "0", 2);
                        dr = gif.ShowDialog();
                        StPaymentRequest.numberOfinstallments = Convert.ToUInt16(gif.textBox1.Text);
                        if (dr != System.Windows.Forms.DialogResult.OK)
                            return;
                    }

                    gif = new GetInputForm("BATCH NO", "0", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.batchNo = Convert.ToUInt32(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("STAN NO", "0", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.stanNo = Convert.ToUInt32(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    break;

                case EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_REFUND:
                    retcode = Json_GMPSmartDLL.FP3_GetPaymentApplicationInfo(CurrentInterface, ref NumberOfTotalRecords, ref NumberOfTotalRecordsReceived, ref StPaymentApplicationInfo, 24);

                    if (retcode != Defines.TRAN_RESULT_OK)
                    {
                        HandleErrorCode(retcode);
                        return;
                    }
                    else if (NumberOfTotalRecordsReceived == 0)
                    {
                        MessageBox.Show("ÖKC Üzerinde Ödeme Uygulanaması Bulunamadı", "HATA", MessageBoxButtons.OK);
                        return;
                    }
                    paf = new PaymentAppForm(NumberOfTotalRecordsReceived, StPaymentApplicationInfo);
                    dr = paf.ShowDialog();
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;
                    StPaymentRequest.bankBkmId = StPaymentApplicationInfo[0].u16BKMId;

                    gif = new GetInputForm("ORG MERCHANT ID (max 15)", "123456789012345", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.OrgTransData.MerchantId = Encoding.Default.GetBytes(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("ORG TRANSACTION AMOUNT", "0", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.OrgTransData.TransactionAmount = Convert.ToUInt32(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("REF CODE OF TRANSACTION (max 10)", "1234567890", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.OrgTransData.referenceCodeOfTransaction = Encoding.Default.GetBytes(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("AUTH CODE (max 6)", "ABC123", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.OrgTransData.AuthorizationCode = Encoding.Default.GetBytes(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("REFRRN (max 12)", "123456789012", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.OrgTransData.rrn = Encoding.Default.GetBytes(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("ORG LOYALTY AMOUNT", "0", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.OrgTransData.LoyaltyAmount = Convert.ToUInt32(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    gif = new GetInputForm("LOYALTY AMOUNT TO REFUND", "0", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.payAmountBonus = Convert.ToUInt32(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    //Kontrol et.
                    gif = new GetInputForm("ORGINAL DATE YYMMDDHHMM", "1510221350", 2);
                    dr = gif.ShowDialog();
                    StPaymentRequest.OrgTransData.TransactionDate = Encoding.Default.GetBytes(gif.textBox1.Text);
                    if (dr != System.Windows.Forms.DialogResult.OK)
                        return;

                    break;

            }

            StPaymentRequest.rawData = Encoding.Default.GetBytes("RawData from external application for the payment application");
            StPaymentRequest.rawDataLen = (ushort)StPaymentRequest.rawData.Length;

            ReversePayment(StPaymentRequest);

        }

        private void m_btnCompleteOtherPayment_Click(object sender, EventArgs e)
        {
            uint amount = 0;
            UInt16 currencyOfPayment = 949;
            if (m_comboBoxCurrency.Text != "")
                currencyOfPayment = Convert.ToUInt16(m_comboBoxCurrency.Text.Substring(0, 3));
            amount = (uint)getAmount(m_txtInputData.Text);

            switch (m_PaymentType)
            {
                case EPaymentTypes.PAYMENT_BANK_CARD:
                    m_btn_Click(m_btn_043, null); //Credit
                    break;

                case EPaymentTypes.PAYMENT_YEMEKCEKI:
                    m_getApplicationInfoToolStripMenuItem.PerformClick();
                    break;

                case EPaymentTypes.PAYMENT_CASH_CURRENCY:
                case EPaymentTypes.PAYMENT_CASH_TL:
                case EPaymentTypes.PAYMENT_MOBILE:
                case EPaymentTypes.PAYMENT_HEDIYE_CEKI:
                case EPaymentTypes.PAYMENT_IKRAM:
                case EPaymentTypes.PAYMENT_ODEMESIZ:
                case EPaymentTypes.PAYMENT_KAPORA:
                case EPaymentTypes.PAYMENT_PUAN:
                case EPaymentTypes.PAYMENT_GIDER_PUSULASI:
                case EPaymentTypes.PAYMENT_BANKA_TRANSFERI:
                case EPaymentTypes.PAYMENT_CEK:
                case EPaymentTypes.PAYMENT_ACIK_HESAP:
                    ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];
                    for (int i = 0; i < stPaymentRequest.Length; i++)
                    {
                        stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
                    }
                    stPaymentRequest[0].typeOfPayment = (uint)m_PaymentType;
                    stPaymentRequest[0].subtypeOfPayment = 0;
                    stPaymentRequest[0].payAmount = amount;
                    stPaymentRequest[0].payAmountCurrencyCode = currencyOfPayment;
                    stPaymentRequest[0].paymentName = "INGENICO";

                    stPaymentRequest[0].bankBkmId = Convert.ToUInt16(KampanyaBkmId);
                    stPaymentRequest[0].numberOfinstallments = 0;
                    stPaymentRequest[0].LoyaltyServiceId = Convert.ToUInt16(KampanyaServiceId);
                    stPaymentRequest[0].LoyaltyCustomerId = KampanyaCustomerId;

                    GetPayment(stPaymentRequest, 1);
                    break;

                default:
                    MessageBox.Show("Ödeme Türü Seçiniz!");
                    break;
            }
        }

        private void m_pluDataBaseMenuItem_Click(object sender, EventArgs e)
        {
            PLUDialog pd = new PLUDialog();
            pd.ShowDialog();
        }

        private void m_btnCashPaymentMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 amount = 0;
            if (m_comboBoxCurrency.SelectedIndex == -1)
            {
                m_comboBoxCurrency.SelectedIndex = 0;
            }
            UInt16 currencyOfPayment = (UInt16)m_comboBoxCurrency.SelectedIndex;

            if (currencyOfPayment == (UInt16)ECurrency.CURRENCY_NONE)
                currencyOfPayment = (UInt16)ECurrency.CURRENCY_TL;

            if (m_txtInputData.Text.Length > 0)
            {
                amount = (uint)getAmount(m_txtInputData.Text);
                m_txtInputData.Text = "";
            }

            ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];
            for (int i = 0; i < stPaymentRequest.Length; i++)
            {
                stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
            }

            stPaymentRequest[0].typeOfPayment = (uint)EPaymentTypes.PAYMENT_CASH_TL;
            stPaymentRequest[0].subtypeOfPayment = 0;
            stPaymentRequest[0].payAmount = amount;
            stPaymentRequest[0].payAmountCurrencyCode = currencyOfPayment;

            GetPayment(stPaymentRequest, 1);
        }

        private void m_rbBatchMode_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbBatchMode.Checked)
            {
                tabControl1.SelectedTab = tabPage6;
            }
        }

        private void m_rbSingleMode_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbSingleMode.Checked)
            {
                tabControl1.SelectedTab = tabPage1;
            }
        }

        string ByteArrayToString(byte[] buffer, int bufferLen)
        {
            string str = "";
            for (int i = 0; i < bufferLen; i++)
            {
                str += buffer[i].ToString("X2");
            }
            return str;
        }

        //input  : "1234"
        //output : byte arr[0]=0x12
        //output : byte arr[0]=0x34
        public void StringToByteArray(string s, byte[] Out_byteArr, ref int Out_byteArrLen)
        {
            byte[] ba = new byte[s.Length / 2];
            for (int i = 0; i < ba.Length; i++)
            {
                string temp = s.Substring(i * 2, 2);
                ba[(ba.Length - 1) - i] = Convert.ToByte(temp, 16);
            }
            Out_byteArrLen = ba.Length;
            Array.Copy(ba, 0, Out_byteArr, 0, ba.Length);
        }

        public void StringToByteArray_Rev(string s, byte[] Out_byteArr, ref int Out_byteArrLen)
        {
            byte[] ba = new byte[s.Length / 2];
            for (int i = 0; i < ba.Length; i++)
            {
                string temp = s.Substring(i * 2, 2);
                ba[i] = Convert.ToByte(temp, 16);
            }
            Out_byteArrLen = ba.Length;
            Array.Copy(ba, 0, Out_byteArr, 0, ba.Length);
        }

        public void AddIntoCommandBatch(string commandName, int commandType, byte[] buffer, int bufferLen)
        {
            byte[] dataPtr = new byte[bufferLen + 6];
            byte[] type = new byte[4];
            int typeLen = 0;
            StringToByteArray(commandType.ToString("X2"), type, ref typeLen);
            Buffer.BlockCopy(type, 0, dataPtr, 0, 4);

            byte[] bufLen = new byte[2];
            int bufLenLen = 0;

            String TempLen;
            TempLen = bufferLen.ToString("X2");
            if ((TempLen.Length % 2) == 1)
                TempLen = "0" + TempLen;
            StringToByteArray(TempLen, bufLen, ref bufLenLen);
            Buffer.BlockCopy(bufLen, 0, dataPtr, 4, 2);

            Buffer.BlockCopy(buffer, 0, dataPtr, 6, bufferLen);

            ListViewItem item1 = new ListViewItem((m_listBatchCommand.Items.Count + 1).ToString());
            item1.SubItems.Add(commandName);
            item1.SubItems.Add(ByteArrayToString(dataPtr, bufferLen + 6));

            m_listBatchCommand.Items.Add(item1);
        }

        private void m_btnSendOnCable_Click(object sender, EventArgs e)
        {
            ProcessBatchCommand("123456789012");
        }

        int GetBatchCommand(byte[] sendBuffer)
        {
            int numberOfTotalCommands = m_listBatchCommand.Items.Count;
            UInt32 MessageCommandType = 0;
            int sendBufferLen = 0;
            byte[] MessageBuffer = new byte[1024 * 16];	// this is buffer for just one msg type (exp: GMP_FISCAL_PRINTER_REQ or GMP_EXT_DEVICE_GET ...
            UInt16 MessageBufferLen = 0;

            for (int i = 0; i < numberOfTotalCommands; i++)
            {
                byte[] Data = new byte[1024];
                int DataLen = 0;
                UInt16 Len = 0;
                UInt32 CommandType;
                string RowData = m_listBatchCommand.Items[i].SubItems[2].Text;
                StringToByteArray(RowData, Data, ref DataLen);

                if (DataLen == 0) // There is no data to send
                    continue;

                // This is the data to be sent to ECR.
                string TempStr = "";
                for (int j = DataLen - 4; j < DataLen; j++)
                {
                    TempStr += Data[j].ToString("X2");
                }
                CommandType = UInt32.Parse(TempStr, System.Globalization.NumberStyles.HexNumber);

                TempStr = "";
                for (int j = DataLen - 6; j < DataLen - 4; j++)
                {
                    TempStr += Data[j].ToString("X2");
                }
                Len = UInt16.Parse(TempStr, System.Globalization.NumberStyles.HexNumber);

                if (MessageCommandType == 0)
                    MessageCommandType = CommandType;

                if (MessageCommandType != CommandType)
                {

                    // this means that the msgCommandType is changing in the list, so close the previous package..
                    sendBufferLen += GMPSmartDLL.gmpSetTLV_HL(sendBuffer, sendBufferLen, MessageCommandType, MessageBuffer, MessageBufferLen);
                    MessageBufferLen = 0;
                    MessageCommandType = CommandType;
                }

                StringToByteArray_Rev(RowData, Data, ref DataLen);

                Buffer.BlockCopy(Data, 6, MessageBuffer, MessageBufferLen, Len);
                MessageBufferLen += Len;
            }
            if (MessageBufferLen != 0)
            {
                // this means that the msgCommandType is changing in the list, so close the privous package..
                sendBufferLen += GMPSmartDLL.gmpSetTLV_HL(sendBuffer, sendBufferLen, MessageCommandType, MessageBuffer, MessageBufferLen);
                MessageBufferLen = 0;
            }

            return sendBufferLen;
        }

        void ProcessBatchCommand(string sicilNo)
        {
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            byte[] sendBuffer = new byte[1024 * 16];
            UInt16 sendBufferLen = 0;
            ST_MULTIPLE_RETURN_CODE[] stReturnCodes = new ST_MULTIPLE_RETURN_CODE[1024]; // will return return codes of each subcommand
            ST_TICKET m_stTicket = new ST_TICKET();
            UInt32 msgCommandType = 0;
            byte[] msgBuffer = new byte[1024 * 16];	// this is buffer for just one msg type (exp: GMP_FISCAL_PRINTER_REQ or GMP_EXT_DEVICE_GET ...
            UInt16 msgBufferLen = 0;
            UInt16 numberOfreturnCodes = 512;

            // Prepare Data To Send
            sendBufferLen = (UInt16)GetBatchCommand(sendBuffer);
            if (sendBufferLen == 0)
                // Nothing to send...
                return;

            UInt16 Len = 0;
            UInt64 TransactionHandle = 0;

            while ((Len < sendBufferLen) && (retcode == Defines.TRAN_RESULT_OK))
            {
                Len += GMPSmartDLL.gmpReadTLVtag(ref msgCommandType, sendBuffer, Len);
                Len += GMPSmartDLL.gmpReadTLVlen_HL(ref msgBufferLen, sendBuffer, Len);
                Buffer.BlockCopy(sendBuffer, Len, msgBuffer, 0, msgBufferLen);
                Len += msgBufferLen;
                MessageBox.Show(Len.ToString());
                // Preceed received message
                switch (msgCommandType)
                {
                    case Defines.GMP3_FISCAL_PRINTER_MODE_REQ:
                    case Defines.GMP3_FISCAL_PRINTER_MODE_REQ_E:

                        // Send to ECR and wait for the response (one error code for each sub command until one of them is failed !!)
                        TransactionHandle = GetTransactionHandle(CurrentInterface);
                        retcode = Json_GMPSmartDLL.FP3_MultipleCommand(CurrentInterface, ref TransactionHandle, ref stReturnCodes, ref numberOfreturnCodes, msgBuffer, msgBufferLen, ref m_stTicket, 1000 * 100);

                        ACTIVE_TRX_HANDLE = TransactionHandle;

                        break;
                    case Defines.GMP3_EXT_DEVICE_GET_DATA_REQ:
                    case Defines.GMP3_EXT_DEVICE_GET_DATA_REQ_E:
                        // Send to ECR and wait for the response (one error code for each sub command until one of them is failed !!)
                        retcode = 0xFFFF;//GMPSmartDLL.GetDialogInput_MultipleCommand_HL(stReturnCodes, numberOfreturnCodes, ref tempNumberOfreturnCodes, msgBuffer, msgBufferLen, ref m_stTicket, 1000 * 100);
                        //numberOfreturnCodes += tempNumberOfreturnCodes;
                        break;
                }
            }

            if (retcode == Defines.TRAN_RESULT_OK)
            {
                //int indexOnListCtrl = 0;
                numberOfreturnCodes = (ushort)m_listBatchCommand.Items.Count;

                for (int t = 0; t < numberOfreturnCodes; t++)
                {
                    byte[] returnCodeString = new byte[256];

                    if (stReturnCodes[t] != null)
                    {
                        // This is not a result of subCommand (it is a tag value in Get Response )
                        if (stReturnCodes[t].indexOfSubCommand == 0)
                            continue;

                        // This is not a result of subCommand (it is a tag value in Get Response )
                        if (stReturnCodes[t].subCommand == 0)
                            continue;

                        GMPSmartDLL.GetErrorMessage(stReturnCodes[t].retcode, returnCodeString);
                    }

                    m_listBatchCommand.Items[t].SubItems[2].Text = GMP_Tools.SetEncoding(returnCodeString);
                }

                // This does not mean all subcommands are OK, check returnCodes structure for each individual commands
                DisplayTransaction(m_stTicket, false);
            }

            HandleErrorCode(retcode);
        }

        private void m_btnClearList_Click(object sender, EventArgs e)
        {
            m_listBatchCommand.Items.Clear();
        }

        private void m_getTSMUniqueIDMenuItem_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = tabPage4;
        }

        private void m_btnServiceComplete_Click(object sender, EventArgs e)
        {
            m_lstUniqueID.Items.Clear();
            Stopwatch stopWatch = new Stopwatch();

            ServiceReference1.TSM_GetUniqueIdIn input = new ServiceReference1.TSM_GetUniqueIdIn();
            ServiceReference1.TSM_GetUniqueIdOut output = new ServiceReference1.TSM_GetUniqueIdOut();

            input.Header_Info = new ServiceReference1.Header();

            input.Header_Info.UserName = "wsTest";
            input.Header_Info.Password = "wsTest";
            input.Header_Info.FirmCode = "ws";
            input.BranchCode = m_txtServiceBranchCode.Text;

            //Trust all certificates
            System.Net.ServicePointManager.ServerCertificateValidationCallback = delegate { return true; };

            ServiceReference1.TsmUniqueIDClntWsSoapClient ws = new ServiceReference1.TsmUniqueIDClntWsSoapClient();

            stopWatch.Start();
            output = ws.TSM_GetUniqueId(input);
            stopWatch.Stop();
            TsmSign = new byte[256];

            //Sign Datası globale alındı...
            Array.Copy(output.TsmSign.Bin, TsmSign, TsmSign.Length);

            //UniqueID listeye alındı...
            ListViewItem item1 = new ListViewItem(output.UniqueID.HexStr);

            m_lstUniqueID.Items.Add(item1.Text);

            long duration = stopWatch.ElapsedMilliseconds;
            m_lblErrorCode.Text = output.ResultMessage + " - Resp Time :" + duration.ToString();
            label2.Text = output.UniqueID.HexStr;
        }

        private void m_taxFreeTicketMenuItem_Click(object sender, EventArgs e)
        {
            ST_TICKET m_stTicket = new ST_TICKET();
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            string csName = "JACK";
            string csSurname = "DANIELS";
            string csIdentificationNo = "BL123456";
            string csCity = "NEW YORK";
            string csCountry = "USA";

            GetInputForm gif = new GetInputForm("PASSANGER NAME", csName, 2);
            DialogResult dr2 = gif.ShowDialog();
            csName = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("PASSANGER SURNAME", csSurname, 2);
            dr2 = gif.ShowDialog();
            csSurname = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("PASSANGER ID NO", csIdentificationNo, 2);
            dr2 = gif.ShowDialog();
            csIdentificationNo = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("PASSANGER CITY", csCity, 2);
            dr2 = gif.ShowDialog();
            csCity = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("PASSANGER COUNTRY", csCountry, 2);
            dr2 = gif.ShowDialog();
            csCountry = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                // start
                bufferLen = GMPSmartDLL.prepare_SetTaxFree(buffer, buffer.Length, 0, csName, csSurname, csIdentificationNo, csCity, csCountry);
                AddIntoCommandBatch("prepare_SetTaxFree", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            }
            else
            {
                bool localStart = false;
                UInt64 activeFlags = 0;

                if (GetTransactionHandle(CurrentInterface) == 0)
                {
                    UInt64 TranHandle = 0;
                    retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TranHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, TsmSign, TsmSign == null ? 0 : TsmSign.Length, null, 0, 10000);
                    AddTrxHandles(CurrentInterface, TranHandle, isBackground);

                    // handle opened locally here, in case of an error close it here!
                    localStart = true;

                    if (retcode == Defines.TRAN_RESULT_OK)
                        retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0, Defines.TIMEOUT_DEFAULT);
                }

                if (retcode == Defines.TRAN_RESULT_OK)
                    retcode = Json_GMPSmartDLL.FP3_SetTaxFree(CurrentInterface, GetTransactionHandle(CurrentInterface), 0, csName, csSurname, csIdentificationNo, csCity, csCountry, ref m_stTicket, 10000);

                if (retcode == Defines.TRAN_RESULT_OK)
                {
                    retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), TTicketType.TTaxFree, Defines.TIMEOUT_DEFAULT);

                    if (retcode == Defines.TRAN_RESULT_OK)
                        // local handle can not be closed after this point
                        localStart = false;
                }

                if (retcode == Defines.TRAN_RESULT_OK)
                    DisplayTransaction(m_stTicket, false);
                else if (localStart)
                {
                    UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                    retcode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                    if (retcode == Defines.TRAN_RESULT_OK)
                        DeleteTrxHandles(CurrentInterface, TransHandle);
                }
            }

            HandleErrorCode(retcode);
        }

        private void m_ParkingEntryMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode;
            ST_TICKET m_stTicket = new ST_TICKET();
            string carPlateNo = "34 ABC 99";

            GetInputForm gif = new GetInputForm("CAR IDENTIFICATION", carPlateNo, 2);
            DialogResult dr2 = gif.ShowDialog();
            carPlateNo = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            if (StartTicket(TTicketType.TOtopark) != 0)
                return;

            retcode = Json_GMPSmartDLL.FP3_SetParkingTicket(CurrentInterface, GetTransactionHandle(CurrentInterface), carPlateNo, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return;
            }

            retcode = GMPSmartDLL.FP3_PrintBeforeMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return;
            }

            retcode = GMPSmartDLL.FP3_PrintMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_CARD_TRANSACTIONS);
            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return;
            }

            ClearTransactionUniqueId(CurrentInterface);
            UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
            retcode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
            if (retcode == Defines.TRAN_RESULT_OK)
                DeleteTrxHandles(CurrentInterface, TransHandle);

            HandleErrorCode(retcode);
        }

        private void m_getSetTicketHeaderMenuItem_Click(object sender, EventArgs e)
        {
            ST_TICKET_HEADER stTicketHeader = new ST_TICKET_HEADER();
            ushort totalNumberOfHeaderPlaces = 0;
            ushort UsedNumberOfHeaderPlaces = 0;
            UInt32 retcode;
            string cs = "";

            retcode = Json_GMPSmartDLL.FP3_GetTicketHeader(CurrentInterface, 0xFF, ref stTicketHeader, ref totalNumberOfHeaderPlaces, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return;
            }

            GetInputForm gif = new GetInputForm("CUSTOMER NAME 1", stTicketHeader.szMerchName1, 2);
            DialogResult dr2 = gif.ShowDialog();
            stTicketHeader.szMerchName1 = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("CUSTOMER NAME 2", stTicketHeader.szMerchName2, 2);
            dr2 = gif.ShowDialog();
            stTicketHeader.szMerchName2 = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("CUSTOMER ADDRESS 1", stTicketHeader.szMerchAddr1, 2);
            dr2 = gif.ShowDialog();
            stTicketHeader.szMerchAddr1 = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("CUSTOMER ADDRESS 2", stTicketHeader.szMerchAddr2, 2);
            dr2 = gif.ShowDialog();
            stTicketHeader.szMerchAddr2 = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("CUSTOMER ADDRESS 3", stTicketHeader.szMerchAddr3, 2);
            dr2 = gif.ShowDialog();
            stTicketHeader.szMerchAddr3 = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("CUSTOMER TAX OFFICE", stTicketHeader.VATOffice, 2);
            dr2 = gif.ShowDialog();
            stTicketHeader.VATOffice = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("CUSTOMER TAX NUMBER", stTicketHeader.VATNumber, 2);
            dr2 = gif.ShowDialog();
            stTicketHeader.VATNumber = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("CUSTOMER MERSIS NUMBER", stTicketHeader.MersisNo, 2);
            dr2 = gif.ShowDialog();
            stTicketHeader.MersisNo = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("CUSTOMER TICARI SICIL NUMBER", stTicketHeader.TicariSicilNo, 2);
            dr2 = gif.ShowDialog();
            stTicketHeader.TicariSicilNo = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("CUSTOMER WEB", stTicketHeader.WebAddress, 2);
            dr2 = gif.ShowDialog();
            stTicketHeader.WebAddress = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            cs = String.Format("Total Space to SET Ticket Header = {0}\nUsed = {1}\nFree = {2}", totalNumberOfHeaderPlaces, stTicketHeader.index + 1, totalNumberOfHeaderPlaces - stTicketHeader.index - 1);
            DialogResult dr = MessageBox.Show(cs, "Continue to SET a new Ticket Header", MessageBoxButtons.OKCancel);
            if (dr != System.Windows.Forms.DialogResult.OK)
                return;

            PassForm pf = new PassForm();
            pf.ShowDialog();

            retcode = Json_GMPSmartDLL.FP3_FunctionChangeTicketHeader(CurrentInterface, pf.m_PASS, ref totalNumberOfHeaderPlaces, ref UsedNumberOfHeaderPlaces, ref stTicketHeader, Defines.TIMEOUT_CARD_TRANSACTIONS);

            HandleErrorCode(retcode);
        }

        private void m_jumpToECRSinglePaymentMenuItem_Click(object sender, EventArgs e)
        {
            ST_TICKET m_stTicket = new ST_TICKET();

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                // start
                bufferLen = GMPSmartDLL.prepare_JumpToECR(buffer, buffer.Length, Defines.GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT);
                AddIntoCommandBatch("prepare_JumpToECR", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                string display = "";

                display += "PLEASE USE ECRPOS FOR PAYMENT\r\nWAITING RESPONSE...";

                UInt32 retcode = Json_GMPSmartDLL.FP3_JumpToECR(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT, ref m_stTicket, Defines.TIMEOUT_CARD_TRANSACTIONS);

                if (retcode == Defines.TRAN_RESULT_OK)
                {

                    display = String.Format("TOPLAM : {0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));

                    if (m_stTicket.CashBackAmount != 0)
                        display += String.Format(Environment.NewLine + "P.ÜSTÜ : {0}", formatAmount(m_stTicket.CashBackAmount, ECurrency.CURRENCY_TL));
                    else if (m_stTicket.TotalReceiptAmount != 0)
                        display += String.Format(Environment.NewLine + "KALAN : {0}", formatAmount(m_stTicket.TotalReceiptAmount - m_stTicket.TotalReceiptPayment, ECurrency.CURRENCY_TL));
                    else
                        display += String.Format(Environment.NewLine + "ÖDENEN : {0}", formatAmount(m_stTicket.TotalReceiptPayment, ECurrency.CURRENCY_TL));

                    DisplayTransaction(m_stTicket, false);

                }

                HandleErrorCode(retcode);
            }
        }

        private void m_chcJumpToEcrOptions_CheckedChanged(object sender, EventArgs e)
        {
            int OptionSum = Convert.ToInt32(m_lblOptionSum.Text);
            CheckBox m_chc = (CheckBox)sender;
            bool CheckedFlag = false;
            if (m_chc.Checked)
                CheckedFlag = true;

            switch (m_chc.Text)
            {
                case "GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT : OptionSum -= Defines.GMP3_OPTION_RETURN_AFTER_SINGLE_PAYMENT;
                    break;
                case "GMP3_OPTION_RETURN_AFTER_COMPLETE_PAYMENT":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_RETURN_AFTER_COMPLETE_PAYMENT : OptionSum -= Defines.GMP3_OPTION_RETURN_AFTER_COMPLETE_PAYMENT;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_ITEM":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_ITEM : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_ITEM;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_VOID_ITEM":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_VOID_ITEM : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_VOID_ITEM;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_VOID_PAYMENT":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_VOID_PAYMENT : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_VOID_PAYMENT;
                    break;
                case "GMP3_OPTION_CONTINUE_IN_OFFLINE_MODE":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_CONTINUE_IN_OFFLINE_MODE : OptionSum -= Defines.GMP3_OPTION_CONTINUE_IN_OFFLINE_MODE;
                    break;
                case "GMP3_OPTION_DONT_SEND_TRANSACTION_RESULT":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_SEND_TRANSACTION_RESULT : OptionSum -= Defines.GMP3_OPTION_DONT_SEND_TRANSACTION_RESULT;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_TL":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_TL : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_TL;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_EXCHANGE":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_EXCHANGE : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_CASH_EXCHANGE;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_BANKCARD":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_BANKCARD : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_BANKCARD;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_YEMEKCEKI":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_YEMEKCEKI : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_YEMEKCEKI;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_MOBILE":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_MOBILE : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_MOBILE;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_HEDIYECEKI":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_HEDIYECEKI : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_HEDIYECEKI;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_IKRAM":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_IKRAM : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_IKRAM;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ODEMESIZ":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ODEMESIZ : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_ODEMESIZ;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_KAPORA":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_KAPORA : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_KAPORA;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_PUAN":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_PUAN : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT_PUAN;
                    break;
                case "GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT":
                    OptionSum = CheckedFlag == true ? OptionSum |= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT : OptionSum -= Defines.GMP3_OPTION_DONT_ALLOW_NEW_PAYMENT;
                    break;

                default:
                    break;
            }

            m_lblOptionSum.Text = OptionSum.ToString();
        }

        private void m_btnCompleteJumpToEcr_Click(object sender, EventArgs e)
        {
            ST_TICKET m_stTicket = new ST_TICKET();

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                // start
                bufferLen = GMPSmartDLL.prepare_JumpToECR(buffer, buffer.Length, Convert.ToUInt64(m_lblOptionSum.Text));
                AddIntoCommandBatch("prepare_JumpToECR", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                string display = "";

                display += "PLEASE USE ECRPOS FOR PAYMENT\r\nWAITING RESPONSE...";

                UInt32 retcode = Json_GMPSmartDLL.FP3_JumpToECR(CurrentInterface, GetTransactionHandle(CurrentInterface), Convert.ToUInt64(m_lblOptionSum.Text), ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                if (retcode != Defines.TRAN_RESULT_OK)
                    HandleErrorCode(retcode);
                else
                {

                    display = String.Format("TOPLAM : {0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));

                    if (m_stTicket.CashBackAmount != 0)
                        display += String.Format(Environment.NewLine + "P.ÜSTÜ : {0}", formatAmount(m_stTicket.CashBackAmount, ECurrency.CURRENCY_TL));
                    else if (m_stTicket.TotalReceiptAmount != 0)
                        display += String.Format(Environment.NewLine + "KALAN : {0}", formatAmount(m_stTicket.TotalReceiptAmount - m_stTicket.TotalReceiptPayment, ECurrency.CURRENCY_TL));
                    else
                        display += String.Format(Environment.NewLine + "ÖDENEN : {0}", formatAmount(m_stTicket.TotalReceiptPayment, ECurrency.CURRENCY_TL));

                    DisplayTransaction(m_stTicket, false);
                }

                if (display.Length != 0)
                    textBox1.Text = display;
            }
        }

        private void m_OptionFlagsMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.DLL_RETCODE_FAIL;

            UInt64 activeFlags = 0;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_OptionFlags(buffer, buffer.Length, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0);
                AddIntoCommandBatch("prepare_OptionFlags", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0, Defines.TIMEOUT_DEFAULT);
                HandleErrorCode(retcode);
            }
        }

        private void m_btnCompleteMatrahsiz_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.DLL_RETCODE_FAIL;
            ST_TICKET m_stTicket = new ST_TICKET();


            uint amount = 0;

            if (m_comboBoxCurrency.SelectedIndex == -1)
            {
                m_comboBoxCurrency.SelectedIndex = 0;
            }
            UInt16 currencyOfPayment = (UInt16)m_comboBoxCurrency.SelectedIndex;

            if (currencyOfPayment == (UInt16)ECurrency.CURRENCY_NONE)
                currencyOfPayment = (UInt16)ECurrency.CURRENCY_TL;

            if (m_txtInputData.Text.Length > 0)
            {
                amount = (uint)getAmount(m_txtInputData.Text);
                m_txtInputData.Text = "";
            }
            else
            {
                MessageBox.Show("Tutar Giriniz...");
                return;
            }
            byte unitType = 0;
            UInt32 itemCount = 1;
            if (m_txtInputData.Text.Contains("X"))
            {
                itemCount = Convert.ToUInt32(m_txtInputData.Text.Substring(0, m_txtInputData.Text.IndexOf('X')));
            }
            byte itemCountPrecition = 0;
            int itemcountDotLocation = m_txtInputData.Text.IndexOf('.');

            ST_ITEM stItem = new ST_ITEM();

            stItem.type = Defines.ITEM_TYPE_MONEYCOLLECTION;
            stItem.subType = 0;
            stItem.deptIndex = (byte)0;
            stItem.amount = (uint)amount;
            stItem.currency = (ushort)ECurrency.CURRENCY_TL;
            stItem.count = itemCount;
            stItem.unitType = unitType;
            stItem.pluPriceIndex = 0;
            stItem.countPrecition = itemCountPrecition;

            stItem.subType = Convert.ToByte(m_lblMatrahsizOptionSum.Text);

            switch ((ETypeOfMatrahsiz)stItem.subType)
            {
                case ETypeOfMatrahsiz.MATRAHSIZ_TYPE_ILAC:
                case ETypeOfMatrahsiz.MATRAHSIZ_TYPE_MUAYANE:
                case ETypeOfMatrahsiz.MATRAHSIZ_TYPE_MUAYANE_RECETE:

                    stItem.tckno = "123456791110";
                    GetInputForm gif = new GetInputForm("TC No", stItem.tckno, 2);
                    DialogResult dr2 = gif.ShowDialog();
                    stItem.tckno = gif.textBox1.Text;
                    if (dr2 != System.Windows.Forms.DialogResult.OK)
                        return;

                    break;

                case ETypeOfMatrahsiz.MATRAHSIZ_TYPE_INVOICE_COLLECTION:
                    stItem.Date = new byte[3];
                    stItem.Date[0] = 0x01;
                    stItem.Date[1] = 0x01;
                    stItem.Date[2] = 0x01;
                    //stItem.date = 0x57330A83;
                    stItem.firm = "TURK TELEKOM A.Ş.";
                    gif = new GetInputForm("UTILITY FIRM", stItem.firm, 2);
                    dr2 = gif.ShowDialog();
                    stItem.firm = gif.textBox1.Text;
                    if (dr2 != System.Windows.Forms.DialogResult.OK)
                        return;

                    stItem.invoiceNo = "A-12345678";
                    gif = new GetInputForm("INVOICE NO ?", stItem.invoiceNo, 2);
                    dr2 = gif.ShowDialog();
                    stItem.invoiceNo = gif.textBox1.Text;
                    if (dr2 != System.Windows.Forms.DialogResult.OK)
                        return;

                    stItem.subscriberId = "02124440333";
                    gif = new GetInputForm("SUBSCRIBER ID ?", stItem.subscriberId, 2);
                    dr2 = gif.ShowDialog();
                    stItem.subscriberId = gif.textBox1.Text;
                    if (dr2 != System.Windows.Forms.DialogResult.OK)
                        return;

                    break;
            }

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_ItemSale(buffer, buffer.Length, ref stItem);
                AddIntoCommandBatch("prepare_ItemSale", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                StartTicket(TTicketType.TProcessSale);

                retcode = Json_GMPSmartDLL.FP3_ItemSale(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stItem, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                HandleErrorCode(retcode);
                if (retcode == 0)
                    DisplayTransaction(m_stTicket, false);
            }
        }

        private void m_rbMatrahsizOption_CheckedChanged(object sender, EventArgs e)
        {
            int OptionSum = Convert.ToInt32(m_lblMatrahsizOptionSum.Text);
            RadioButton m_chc = (RadioButton)sender;
            bool CheckedFlag = false;
            if (m_chc.Checked)
                CheckedFlag = true;

            switch (m_chc.Text)
            {
                case "MATRAHSIZ_TYPE_ILAC":
                    OptionSum = CheckedFlag == true ? OptionSum += (int)ETypeOfMatrahsiz.MATRAHSIZ_TYPE_ILAC : OptionSum -= (int)ETypeOfMatrahsiz.MATRAHSIZ_TYPE_ILAC;
                    break;
                case "MATRAHSIZ_TYPE_MUAYANE":
                    OptionSum = CheckedFlag == true ? OptionSum += (int)ETypeOfMatrahsiz.MATRAHSIZ_TYPE_MUAYANE : OptionSum -= (int)ETypeOfMatrahsiz.MATRAHSIZ_TYPE_MUAYANE;
                    break;
                case "MATRAHSIZ_TYPE_MUAYANE_RECETE":
                    OptionSum = CheckedFlag == true ? OptionSum += (int)ETypeOfMatrahsiz.MATRAHSIZ_TYPE_MUAYANE_RECETE : OptionSum -= (int)ETypeOfMatrahsiz.MATRAHSIZ_TYPE_MUAYANE_RECETE;
                    break;
                case "MATRAHSIZ_TYPE_INVOICE_COLLECTION":
                    OptionSum = CheckedFlag == true ? OptionSum += (int)ETypeOfMatrahsiz.MATRAHSIZ_TYPE_INVOICE_COLLECTION : OptionSum -= (int)ETypeOfMatrahsiz.MATRAHSIZ_TYPE_INVOICE_COLLECTION;
                    break;

                default:
                    break;
            }

            m_lblMatrahsizOptionSum.Text = OptionSum.ToString();
        }

        private void m_CustomerAdvantageMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode;
            ST_TICKET m_stTicket = new ST_TICKET();
            string CustomerName = "ALI CAN";
            string TckNo = "1232434234";
            string VkNo = "12324";

            if (GetTransactionHandle(CurrentInterface) != 0)
            {
                MessageBox.Show("A Transaction has already started. Multiple sessions can not be managed", "Error", MessageBoxButtons.OK);
                return;
            }

            if (m_txtInputData.Text == "")
            {
                MessageBox.Show("Enter an Amount!", "Error", MessageBoxButtons.OK);
                return;
            }

            GetInputForm gif = new GetInputForm("CUSTOMER NAME", CustomerName, 2);
            DialogResult dr2 = gif.ShowDialog();
            CustomerName = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("TCK NO", TckNo, 2);
            dr2 = gif.ShowDialog();
            TckNo = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            gif = new GetInputForm("VK NO", VkNo, 2);
            dr2 = gif.ShowDialog();
            VkNo = gif.textBox1.Text;
            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_KasaAvans(buffer, buffer.Length, getAmount(m_txtInputData.Text), CustomerName, TckNo, VkNo);
                AddIntoCommandBatch("prepare_KasaAvans", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                retcode = StartTicket(TTicketType.TAvans);
                if (retcode != Defines.TRAN_RESULT_OK)
                    return;

                retcode = Json_GMPSmartDLL.Json_FP3_CustomerAvans(CurrentInterface, GetTransactionHandle(CurrentInterface), getAmount(m_txtInputData.Text), ref m_stTicket, CustomerName, TckNo, VkNo, Defines.TIMEOUT_DEFAULT);

                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                DisplayTransaction(m_stTicket, false);
                HandleErrorCode(retcode);
            }
        }

       uint LoadEkuModuleInfo()
        {
            tabControl1.SelectedIndex = 0;
            uint retcode = Defines.TRAN_RESULT_OK;

            ST_EKU_MODULE_INFO pstEkuModuleInfo = new ST_EKU_MODULE_INFO();

            retcode = Json_GMPSmartDLL.FP3_FunctionEkuReadInfo(CurrentInterface, (ushort)EInfo.TLV_FUNC_INFO_DEVICE, ref pstEkuModuleInfo, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return retcode;
            }

            retcode = Json_GMPSmartDLL.FP3_FunctionEkuReadInfo(CurrentInterface, (ushort)EInfo.TLV_FUNC_INFO_EKU, ref pstEkuModuleInfo, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return retcode;
            }
            TransactionInfo(m_listTransaction, "EKU MODULE INFO (DEVICE)");
            TransactionInfo(m_listTransaction, "------------------------");
            TransactionInfo(m_listTransaction, String.Format("SW VERS     : {0}", pstEkuModuleInfo.Device.szSoftVersion));
            TransactionInfo(m_listTransaction, String.Format("HW VERS     : {0}", pstEkuModuleInfo.Device.szHardVersion));
            TransactionInfo(m_listTransaction, String.Format("COMPL DATE  : {0}", pstEkuModuleInfo.Device.szCompileDate));
            TransactionInfo(m_listTransaction, String.Format("DESCRIPTION : {0}", pstEkuModuleInfo.Device.szDescription));
            TransactionInfo(m_listTransaction, String.Format("HW REF      : {0}", pstEkuModuleInfo.Device.szHardwareReference));
            TransactionInfo(m_listTransaction, String.Format("HW S/N      : {0}", pstEkuModuleInfo.Device.szHardwareSerial));
            TransactionInfo(m_listTransaction, String.Format("CPU         : {0}", pstEkuModuleInfo.Device.szCpuID));
            TransactionInfo(m_listTransaction, String.Format("BOOT        : {0}", pstEkuModuleInfo.Device.szCpuID));

            TransactionInfo(m_listTransaction, "\n");
            TransactionInfo(m_listTransaction, "EKU MODULE INFO (EKU)");
            TransactionInfo(m_listTransaction, "------------------------");
            TransactionInfo(m_listTransaction, "LAST RECORD");
            TransactionInfo(m_listTransaction, String.Format("  ZNO       : {0}", pstEkuModuleInfo.Eku.LastRecord.ZNo));
            TransactionInfo(m_listTransaction, String.Format("  FNO       : {0}", pstEkuModuleInfo.Eku.LastRecord.FNo));
            TransactionInfo(m_listTransaction, String.Format("  TYPE      : {0}", pstEkuModuleInfo.Eku.LastRecord.Type));
            TransactionInfo(m_listTransaction, String.Format("  DATETIME  : {0}", pstEkuModuleInfo.Eku.LastRecord.DateTime));
            TransactionInfo(m_listTransaction, String.Format("  STATUS    : {0}", pstEkuModuleInfo.Eku.LastRecord.Status));
            TransactionInfo(m_listTransaction, "\n");
            TransactionInfo(m_listTransaction, "CAPACITY");
            TransactionInfo(m_listTransaction, String.Format("  DATA USED : {0}", pstEkuModuleInfo.Eku.DataUsedArea));
            TransactionInfo(m_listTransaction, String.Format("  DATA FREE : {0}", pstEkuModuleInfo.Eku.DataFreeArea));
            TransactionInfo(m_listTransaction, String.Format("  HEADER USED: {0}", pstEkuModuleInfo.Eku.HeaderUsed));
            TransactionInfo(m_listTransaction, String.Format("  HEADER FREE: {0}", pstEkuModuleInfo.Eku.HeaderTotal - pstEkuModuleInfo.Eku.HeaderUsed));

            HandleErrorCode(retcode);
            return retcode;
        }

        private void m_ekuInfoMenuItem_Click(object sender, EventArgs e)
        {
            LoadEkuModuleInfo();
        }

        private void m_setTaxRefundMenuItem_Click(object sender, EventArgs e)
        {
            ST_TICKET m_stTicket = new ST_TICKET();
            int amount = 0;
            UInt32 retcode = Defines.TRAN_RESULT_OK;

            if (m_txtInputData.Text != "")
            {
                amount = getAmount(m_txtInputData.Text);
                m_txtInputData.Text = "";
            }

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_SetTaxFreeRefundAmount(buffer, buffer.Length, amount, (ushort)ECurrency.CURRENCY_TL);
                AddIntoCommandBatch("prepare_SetTaxFreeRefundAmount", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                retcode = Json_GMPSmartDLL.FP3_SetTaxFreeRefundAmount(CurrentInterface, GetTransactionHandle(CurrentInterface), amount, (ushort)ECurrency.CURRENCY_TL, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                if (retcode == Defines.TRAN_RESULT_OK)
                    DisplayTransaction(m_stTicket, false);
            }

            HandleErrorCode(retcode);
        }

        private void m_getApplicationInfoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            byte NumberOfTotalRecord = 24;
            byte NumberOfTotalRecordReceived = 0;

            ST_PAYMENT_APPLICATION_INFO[] StPaymentApplicationInfo = new ST_PAYMENT_APPLICATION_INFO[24];
            for (int i = 0; i < StPaymentApplicationInfo.Length; i++)
            {
                StPaymentApplicationInfo[i] = new ST_PAYMENT_APPLICATION_INFO();
            }

            uint retcode = Json_GMPSmartDLL.FP3_GetVasApplicationInfo(CurrentInterface, ref NumberOfTotalRecord, ref NumberOfTotalRecordReceived, ref StPaymentApplicationInfo, (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_YEMEKCEKI);

            if (retcode != Defines.TRAN_RESULT_OK)
                HandleErrorCode(retcode);
            else if (NumberOfTotalRecordReceived == 0)
                MessageBox.Show("ÖKC Üzerinde Ödeme Uygulanaması Bulunamadı", "HATA", MessageBoxButtons.OK);
            else
            {
                PaymentAppForm paf = new PaymentAppForm(NumberOfTotalRecordReceived, StPaymentApplicationInfo);
                DialogResult dr = paf.ShowDialog();
                if (dr != System.Windows.Forms.DialogResult.OK)
                    return;

                UInt32 amount = 0;
                if (m_comboBoxCurrency.SelectedIndex == -1)
                {
                    m_comboBoxCurrency.SelectedIndex = 0;
                }
                UInt16 currencyOfPayment = (UInt16)m_comboBoxCurrency.SelectedIndex;

                if (currencyOfPayment == (UInt16)ECurrency.CURRENCY_NONE)
                    currencyOfPayment = (UInt16)ECurrency.CURRENCY_TL;

                if (m_txtInputData.Text.Length > 0)
                {
                    amount = (uint)getAmount(m_txtInputData.Text);
                    m_txtInputData.Text = "";
                }

                ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];
                for (int i = 0; i < stPaymentRequest.Length; i++)
                {
                    stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
                }

                stPaymentRequest[0].typeOfPayment = (uint)EPaymentTypes.PAYMENT_YEMEKCEKI;
                stPaymentRequest[0].subtypeOfPayment = 0;
                stPaymentRequest[0].payAmount = amount;
                stPaymentRequest[0].payAmountCurrencyCode = (ushort)ECurrency.CURRENCY_TL;
                if (paf.pstPaymentApplicationInfoSelected.u16BKMId.Equals(null))
                    stPaymentRequest[0].bankBkmId = 0;
                else
                    stPaymentRequest[0].bankBkmId = paf.pstPaymentApplicationInfoSelected.u16AppId;
                stPaymentRequest[0].numberOfinstallments = 0;

                GetPayment(stPaymentRequest, 1);
            }
        }

        private void m_ticketHeaderOptions(object sender, EventArgs e)
        {
            ToolStripMenuItem btn = (ToolStripMenuItem)sender;

            int TicketType = Convert.ToInt32(btn.Name.Substring(btn.Name.IndexOf('_') + 1));
            MessageBox.Show(btn.Name);
            UInt32 retcode = Defines.TRAN_RESULT_OK;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = GMPSmartDLL.prepare_TicketHeader(buffer, buffer.Length, (TTicketType)TicketType);
                AddIntoCommandBatch("prepare_TicketHeader", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
            }
            else
            {
                if (GMPSmartDLL.FiscalPrinter_GetHandle() == 0)
                    return;

                retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), (TTicketType)TicketType, Defines.TIMEOUT_DEFAULT);
            }
            HandleErrorCode(retcode);
        }

        private void promosyonKullanToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult dr = new Promotion().ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (button1.Text == "Yemek Çeki Başlat")
            {
                button1.Text = "Yemek Çeki Ödeme";
                button1.BackColor = System.Drawing.Color.Red;
                UInt32 retcode = Defines.TRAN_RESULT_OK;
                UInt64 activeFlags = 0;

                if (m_rbBatchMode.Checked)
                {
                    byte[] buffer = new byte[1024];
                    int bufferLen = 0;

                    bufferLen = GMPSmartDLL.prepare_TicketHeader(buffer, buffer.Length, TTicketType.TYemekceki);
                    AddIntoCommandBatch("prepare_TicketHeader", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                }
                else
                {
                    if (GetTransactionHandle(CurrentInterface) == 0)
                    {
                        UInt64 TranHandle = 0;
                        retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TranHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
                        AddTrxHandles(CurrentInterface, TranHandle, isBackground);

                        if (retcode != Defines.TRAN_RESULT_OK)
                            HandleErrorCode(retcode);

                        retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, (Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS), 0x00000000, Defines.TIMEOUT_DEFAULT);
                        if (retcode != Defines.TRAN_RESULT_OK)
                            HandleErrorCode(retcode);
                    }

                    retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), TTicketType.TYemekceki, Defines.TIMEOUT_DEFAULT);
                }
                HandleErrorCode(retcode);
            }
            else if (button1.Text == "Yemek Çeki Ödeme")
            {

                //tODO
                m_getApplicationInfoToolStripMenuItem.PerformClick();
                button1.BackColor = System.Drawing.Color.LightBlue;
                button1.Text = "Yemek Çeki Başlat";

            }
        }

        private void eşleşmeBaslatToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_btnStartPairing.PerformClick();
        }

        private void flightModeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 resp = 0;
            byte[] flightMode = new byte[1];
            short len = 0;

            m_echoTestMenuItem.PerformClick();

            resp = GMPSmartDLL.FP3_GetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_FLIGHT_MODE, flightMode, (short)flightMode.Length, ref len);
            HandleErrorCode(resp);

            if (resp == Defines.TRAN_RESULT_OK)
            {

                if (flightMode[0] == 1)
                {
                    //m_btnFlightMode.Text = "Flight Mode : ON";
                    flightModeToolStripMenuItem.Text = (Localization.FlightMode) + " ON(Now)";
                }
                else
                {
                    //m_btnFlightMode.Text = "Flight Mode : OFF";
                    flightModeToolStripMenuItem.Text = (Localization.FlightMode) + " OFF(Now)";
                }

                if (flightMode[0] == 0)
                {
                    flightMode[0] = 1;
                    resp = GMPSmartDLL.FP3_SetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_FLIGHT_MODE, flightMode, (UInt16)flightMode.Length);
                    HandleErrorCode(resp);

                    if (resp == Defines.TRAN_RESULT_OK)
                    {
                        //m_btnFlightMode.Text = "Flight Mode : ON";
                        flightModeToolStripMenuItem.Text = (Localization.FlightMode) + " ON(Now)";
                    }

                }
                else if (flightMode[0] == 1)
                {
                    flightMode[0] = 0;
                    resp = GMPSmartDLL.FP3_SetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_FLIGHT_MODE, flightMode, (UInt16)flightMode.Length);
                    HandleErrorCode(resp);

                    if (resp == Defines.TRAN_RESULT_OK)
                    {
                        //m_btnFlightMode.Text = "Flight Mode : OFF";
                        flightModeToolStripMenuItem.Text = (Localization.FlightMode) + " OFF(Now)";
                    }
                }
            }
        }

        private void checkConnStatusToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //////////////////////// Connection Control//////////////////////////////////////
            UInt32 resp_comm_status = 0;
            byte[] comm_status = new byte[1];
            short len_comm_status = 0;
            resp_comm_status = GMPSmartDLL.FP3_GetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_COMM_STATUS, comm_status, (short)comm_status.Length, ref len_comm_status);

            if (resp_comm_status != 0)
                HandleErrorCode(resp_comm_status);
            if (resp_comm_status == Defines.TRAN_RESULT_OK)
            {
                string binValuem = Convert.ToString(comm_status[0], 2);

                string[] arrm = new string[] { "FLIGHT_MODE", "GPRS_CONNECTED", "ETHERNET_CONNECTED" };

                int bitNum = 7;
                String status = "";

                for (int j = 0; j < binValuem.Length; j++)
                {
                    bitNum = Convert.ToInt32(binValuem.Substring(binValuem.Length - 1 - j, 1));

                    switch (bitNum)
                    {
                        case 0:
                            status += arrm[j] + " = NO\n";
                            break;
                        case 1:
                            status += arrm[j] + " = YES\n";
                            //ParserClass.DisplayStruct(" set bit : " + j.ToString(), "  -- ", "  -- ", "  " + arrm[j]);
                            break;
                        default:
                            break;
                    }
                }
                MessageBox.Show(status);
            }
        }

        private void setTicketLimitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            String ticketLimit = "";
            uint resp = 0;
            byte[] TempArr = new byte[100];
            short TempLen = 0;
            resp = GMPSmartDLL.FP3_GetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_FIS_LIMIT, TempArr, (short)TempArr.Length, ref TempLen);
            HandleErrorCode(resp);

            GetInputForm gif = new GetInputForm("Ticket Limit", ticketLimit, 2);
            gif.ShowDialog();
            ticketLimit = gif.textBox1.Text;

            int num;
            bool isNumeric = int.TryParse(ticketLimit, out num);

            if (isNumeric)
            {
                byte[] ticketLimitBytes = new Byte[6];
                ConvertStringToHexArray(ticketLimit.PadLeft(12, '0'), ref ticketLimitBytes, 6);
                short lenLimit = 6;
                resp = GMPSmartDLL.FP3_SetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_FIS_LIMIT, ticketLimitBytes, (UInt16)lenLimit);
                HandleErrorCode(resp);
            }
            else
            {
                MessageBox.Show("Enter Numeric Char set...");
                return;
            }
        }

        private void m_chcIsBackground_CheckedChanged(object sender, EventArgs e)
        {
            // P12 sonrası kullanılmaya başlayacak.
            //if (m_chcIsBackground.Checked == true)
            //    isBackground = 1;
            //else
            //    isBackground = 0;
        }

        private void setStandbyTimeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            String standby = "";
            uint resp = 0;
            byte[] TempArr = new byte[100];
            short TempLen = 0;
            resp = GMPSmartDLL.FP3_GetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_STAND_BY_TIME, TempArr, (short)TempArr.Length, ref TempLen);
            HandleErrorCode(resp);

            GetInputForm gif = new GetInputForm("Set Standby Time : Current VAL = " + ConvertByteArrayToString(TempArr, TempLen), standby, 2);
            DialogResult dr2 = gif.ShowDialog();
            standby = gif.textBox1.Text;

            UInt16 num;
            bool isNumeric = UInt16.TryParse(standby, out num);

            if (isNumeric)
            {
                byte[] standbyBytes = BitConverter.GetBytes(num);
                resp = GMPSmartDLL.FP3_SetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_STAND_BY_TIME, standbyBytes, (UInt16)standbyBytes.Length);
                HandleErrorCode(resp);
            }
            else
            {
                MessageBox.Show("Enter Numeric Char set...");
                return;
            }

            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;
        }

        private void setCommScenarioToolStripMenuItem_Click(object sender, EventArgs e)
        {
            String commScenario = "";
            uint resp = 0;
            byte[] TempArr = new byte[100];
            short TempLen = 0;
            resp = GMPSmartDLL.FP3_GetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_COMM_SCENARIO, TempArr, (short)TempArr.Length, ref TempLen);
            HandleErrorCode(resp);

            GetInputForm gif = new GetInputForm("1:ETH, 2:GPRS, 3:ETH_GPRS #Current :" + ConvertByteArrayToString(TempArr, TempLen), commScenario, 2);
            DialogResult dr2 = gif.ShowDialog();
            commScenario = gif.textBox1.Text;

            int num;
            bool isNumeric = int.TryParse(commScenario, out num);

            byte[] arr2 = new byte[1];

            if (isNumeric && (Convert.ToInt32(commScenario) >= 1 && Convert.ToInt32(commScenario) <= 3))
            {
                if (Convert.ToInt32(commScenario) == 1)
                {
                    arr2[0] = Defines.FLAG_SETSCENARIO_ETHERNET;
                    resp = GMPSmartDLL.FP3_SetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_COMM_SCENARIO, arr2, (UInt16)arr2.Length);
                    HandleErrorCode(resp);
                }
                else if (Convert.ToInt32(commScenario) == 2)
                {
                    arr2[0] = Defines.FLAG_SETSCENARIO_GPRS;
                    resp = GMPSmartDLL.FP3_SetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_COMM_SCENARIO, arr2, (UInt16)arr2.Length);
                    HandleErrorCode(resp);
                }
                else if (Convert.ToInt32(commScenario) == 3)
                {
                    arr2[0] = Defines.FLAG_SETSCENARIO_ETHERNET_GPRS;
                    resp = GMPSmartDLL.FP3_SetTlvData(CurrentInterface, Defines.GMP_EXT_DEVICE_COMM_SCENARIO, arr2, (UInt16)arr2.Length);
                    HandleErrorCode(resp);
                }
            }
            else
            {
                MessageBox.Show("Check Input value...");
                return;
            }

            if (dr2 != System.Windows.Forms.DialogResult.OK)
                return;
        }

        private void m_btnCreateUniqueID_Click(object sender, EventArgs e)
        {
            uint retcode = 0;

            byte[] uniqueID = new byte[24];

            retcode = GMPSmartDLL.FP3_FunctionCreateUniqueId(CurrentInterface, uniqueID, Defines.TIMEOUT_DEFAULT);

            string strUniqueId = "";
            for (int i = 0; i < 24; i++)
            {
                strUniqueId += uniqueID[i].ToString("X2");
            }

            MessageBox.Show(strUniqueId);
        }

        private void m_treeHandleList_AfterSelect(object sender, TreeViewEventArgs e)
        {
            TreeNode node = (TreeNode)e.Node;
            if (node.Parent == null)
            {
                CurrentInterface = (UInt32)node.Tag;
                if ((node.Nodes == null) || (node.Nodes.Count == 0))
                    ACTIVE_TRX_HANDLE = 0;
                else
                    ACTIVE_TRX_HANDLE = (UInt64)node.Nodes[0].Tag;

                GetInterfaceInfo(CurrentInterface);
            }
            else
            {
                CurrentInterface = (UInt32)node.Parent.Tag;
                ACTIVE_TRX_HANDLE = (UInt64)node.Tag;

                GetInterfaceInfo(CurrentInterface);
            }
        }

        private void GetInterfaceInfo(UInt32 InterfaceHandle)
        {
            ST_INTERFACE_XML_DATA stXmlData = new ST_INTERFACE_XML_DATA();
            UInt32 Ret = Json_GMPSmartDLL.FP3_GetInterfaceXmlDataByHandle(CurrentInterface, ref stXmlData);

            byte[] ID = new byte[64];
            string Str;

            Str = "Handle : " + CurrentInterface.ToString("X8") + Environment.NewLine;
            GMPSmartDLL.FP3_GetInterfaceID(CurrentInterface, ID, (UInt32)ID.Length);
            Str += "ID : " + GMP_Tools.GetStringFromBytes(ID) + Environment.NewLine;
            if (stXmlData.IsTcpConnection == 0)
            {
                Str += "ConnectionState Type : Port" + Environment.NewLine;
                Str += "Port Name :" + stXmlData.PortName + Environment.NewLine;
                Str += "Baudrate : " + stXmlData.BaudRate.ToString() + Environment.NewLine;
                Str += "ByteSize : " + stXmlData.ByteSize.ToString() + Environment.NewLine;
                Str += "fParity : " + stXmlData.fParity.ToString() + Environment.NewLine;
                Str += "Parity : " + stXmlData.Parity.ToString() + Environment.NewLine;
                Str += "StopBit : " + stXmlData.StopBit.ToString() + Environment.NewLine;

                Str += "RetryCounter : " + stXmlData.RetryCounter.ToString() + Environment.NewLine;
            }
            else
            {
                Str += "ConnectionState Type : IP" + Environment.NewLine;
                Str += "IP :" + stXmlData.IP + "" + stXmlData.Port.ToString() + Environment.NewLine;
                Str += "IpRetryCount : " + stXmlData.IpRetryCount.ToString() + Environment.NewLine;
            }

            Str += "AckTimeOut : " + stXmlData.AckTimeOut.ToString() + Environment.NewLine;
            Str += "CommTimeOut : " + stXmlData.CommTimeOut.ToString() + Environment.NewLine;
            Str += "InterCharacterTimeOut : " + stXmlData.InterCharacterTimeOut.ToString() + Environment.NewLine;

            m_CurrentHandleDisplay.Text = Str;
        }

        private void m_treeHandleList_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            TreeNode node = (TreeNode)e.Node;

            if (node.Parent != null)
            {
                uint RetCode = 0;
                UInt16 NumberOfItems = 20;
                UInt16 TotalNumberOfItems = 0;
                UInt16 NumberOfItemsInThis = 0;
                ST_HANDLE_LIST[] stHandleList = new ST_HANDLE_LIST[NumberOfItems];

                RetCode = Json_GMPSmartDLL.FP3_FunctionGetHandleList((UInt32)node.Parent.Tag, ref stHandleList, Defines.TRAN_STATUS_FREE, 0, NumberOfItems, ref TotalNumberOfItems, ref NumberOfItemsInThis, Defines.TIMEOUT_DEFAULT);

                if (RetCode == Defines.TRAN_RESULT_OK)
                {
                    for (int i = 0; i < NumberOfItemsInThis; ++i)
                    {
                        if ((UInt64)node.Tag == stHandleList[i].Handle)
                        {
                            string str = "Handle : " + stHandleList[i].Handle.ToString() + "\n";
                            str += "Amount : " + stHandleList[i].ReceiptAmount.ToString() + "\n";
                            str += "SicilNo : " + stHandleList[i].szMasterOkcSicilNo.ToString() + "\n";
                            str += "TranSubGroup : " + stHandleList[i].szUserDefinedTranSubGroup.ToString() + "\n";
                            str += "TranGroup : " + stHandleList[i].szUserDefinedTranGroup.ToString() + "\n";
                            str += "Status : " + stHandleList[i].Status.ToString() + "\n";

                            MessageBox.Show(str);
                        }
                    }
                }
            }
        }

        private void wincorFrontStationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] slipArray = {
                "              INGENICO IDE280\n",
                "               ECRPOS IDE280\n",
                "               Address Line 1\n",
                "               Address Line2\n",
                "           VAT OFFICE 1234567890\n",
                "\n",
                "TARİH  : " + DateTime.Now.ToShortDateString() + "\n",
                "SAAT   : " + DateTime.Now.ToShortTimeString() + "\n",
                "FİŞ NO : 0020\n",
                "\n",
                "EKMEK                         %24  *2,00\n",
                "EKMEK                         %24  *2,00\n",
                "EKMEK                         %24  *2,00\n",
                "-----------------------------------------\n",
                "TOPKDV                             *1,16\n",
                "TOPLAM                             *6,00\n",
                "-----------------------------------------\n",
                "NAKİT                              *7,02\n",
                "PARA ÜSTÜ                          *0,0\n",
                "\n",
                "MERSİS : REGISTIRATION NUM\n",
                "www.ingenio.com\n",

                "               TEŞEKKÜR EDERİZ\n"
            };
            UInt32 retcode;
            byte[] TempBuf = new byte[2000];
            byte[] SendBuf = new byte[2000];
            byte[] ReceiveBuffer = new byte[200];
            UInt16 Len = 200;
            //Wincor Front Station Test
            SendBuf[0] = 0x1c;
            SendBuf[1] = 0x0A;

            for (int i = 0; i < slipArray.Length; i++)
            {
                Array.Copy(Encoding.ASCII.GetBytes(slipArray[i].ToArray()), 0, SendBuf, 2, slipArray[i].Length);
                retcode = GMPSmartDLL.FP3_SendFrontStationPrintEx(CurrentInterface, GetTransactionHandle(CurrentInterface), SendBuf, (short)(2 + slipArray[i].Length), ReceiveBuffer, ref Len, Defines.TIMEOUT_DEFAULT, 0);

                if (retcode != Defines.TRAN_RESULT_OK)
                {
                    MessageBox.Show(this, "Komut hatası: " + retcode.ToString() + " (" + retcode.ToString("X") + ")");
                    return;
                }
            }

            // release paper
            SendBuf[0] = 0x1c;        
            SendBuf[1] = 0x1b;        
            SendBuf[2] = 0x71;
            retcode = GMPSmartDLL.FP3_SendFrontStationPrintEx(CurrentInterface, GetTransactionHandle(CurrentInterface), SendBuf, (short)(3), ReceiveBuffer, ref Len, Defines.TIMEOUT_DEFAULT, Defines.TIMEOUT_DEFAULT);

        }

        private void starFrontStationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] slipArray = {
                "              INGENICO IDE280\n",
                "               ECRPOS IDE280\n",
                "               Address Line 1\n",
                "               Address Line2\n",
                "           VAT OFFICE 1234567890\n",
                "\n",
                "TARİH  : " + DateTime.Now.ToShortDateString() + "\n",
                "SAAT   : " + DateTime.Now.ToShortTimeString() + "\n",
                "FİŞ NO : 0020\n",
                "\n",
                "EKMEK                            %24  *2,00\n",
                "EKMEK                            %24  *2,00\n",
                "EKMEK                            %24  *2,00\n",
                "---------------------------------------------\n",
                "TOPKDV                                *1,16\n",
                "TOPLAM                                *6,00\n",
                "---------------------------------------------\n",
                "NAKİT                                 *7,02\n",
                "PARA ÜSTÜ                             *0,0\n",
                "\n",
                "MERSİS : REGISTIRATION NUM\n",
                "www.ingenio.com\n",

                "               TEŞEKKÜR EDERİZ\n"
            };
            UInt32 retcode;
            int t = 0;
            byte[] TempBuf = new byte[2000];
            byte[] SendBuf = new byte[2000];
            byte[] ReceiveBuffer = new byte[200];
            UInt16 Len = 0;

            // select the front printer
            SendBuf[t++] = 0x1B;
            SendBuf[t++] = 0x2B;
            SendBuf[t++] = 0x41;
            SendBuf[t++] = 0x33;

            retcode = GMPSmartDLL.FP3_SendFrontStationPrintEx(CurrentInterface, GetTransactionHandle(CurrentInterface), SendBuf, (short)(t), ReceiveBuffer, ref Len, Defines.TIMEOUT_DEFAULT, Defines.TIMEOUT_DEFAULT);

            for (int i = 0; i < slipArray.Length; i++)
            {
                Array.Copy(Encoding.ASCII.GetBytes(slipArray[i].ToArray()), 0, SendBuf, 4, slipArray[i].Length);

                retcode = GMPSmartDLL.FP3_SendFrontStationPrintEx(CurrentInterface, GetTransactionHandle(CurrentInterface), SendBuf, (short)(4 + slipArray[i].Length), ReceiveBuffer, ref Len, Defines.TIMEOUT_DEFAULT, 0);

                if (retcode != Defines.TRAN_RESULT_OK)
                {
                    MessageBox.Show(this, "Komut hatası: " + retcode.ToString() + " (" + retcode.ToString("X") + ")");
                    return;
                }
            }
        }
        private void epsonFrontStationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] slipArray = {
                "              INGENICO IDE280\n",
                "               ECRPOS IDE280\n",
                "               Address Line 1\n",
                "               Address Line2\n",
                "           VAT OFFICE 1234567890\n",
                "\n",
                "TARİH  : " + DateTime.Now.ToShortDateString() + "\n",
                "SAAT   : " + DateTime.Now.ToShortTimeString() + "\n",
                "FİŞ NO : 0020\n",
                "\n",
                "EKMEK                            %24  *2,00\n",
                "EKMEK                            %24  *2,00\n",
                "EKMEK                            %24  *2,00\n",
                "---------------------------------------------\n",
                "TOPKDV                                *1,16\n",
                "TOPLAM                                *6,00\n",
                "---------------------------------------------\n",
                "NAKİT                                 *7,02\n",
                "PARA ÜSTÜ                             *0,0\n",
                "\n",
                "MERSİS : REGISTIRATION NUM\n",
                "www.ingenio.com\n",

                "               TEŞEKKÜR EDERİZ\n"
            };
            UInt32 retcode;
            int t = 0;
            byte[] TempBuf = new byte[2000];
            byte[] SendBuf = new byte[2000];
            byte[] ReceiveBuffer = new byte[200];
            UInt16 Len = 200;

            // select the front printer
            SendBuf[t++] = 0x1B;
            SendBuf[t++] = 0x63;
            SendBuf[t++] = 0x30;
            SendBuf[t++] = 0x04;

            SendBuf[t++] = 0x10;
            SendBuf[t++] = 0x04;
            SendBuf[t++] = 0x05;

            retcode = GMPSmartDLL.FP3_SendFrontStationPrintEx(CurrentInterface, GetTransactionHandle(CurrentInterface), SendBuf, (short)(t), ReceiveBuffer, ref Len, Defines.TIMEOUT_DEFAULT, Defines.TIMEOUT_DEFAULT);
            if (Len == 1)
            {
                int temp = (ReceiveBuffer[0] & 0x60);
                if(temp != 0)
                {
                    MessageBox.Show("Yazıcıya kağıt koyun! " + ReceiveBuffer[0].ToString("X"), "Uyarı", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
            }
            else
            {
                MessageBox.Show("Yazıcı ileilgili bir sorun oluştu!", "HATA", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            Len = 0;
            for (int i = 0; i < slipArray.Length; i++)
            {
                Array.Copy(Encoding.ASCII.GetBytes(slipArray[i].ToArray()), 0, SendBuf, 4, slipArray[i].Length);

                retcode = GMPSmartDLL.FP3_SendFrontStationPrintEx(CurrentInterface, GetTransactionHandle(CurrentInterface), SendBuf, (short)(4 + slipArray[i].Length), ReceiveBuffer, ref Len, Defines.TIMEOUT_DEFAULT, 0);

                if (retcode != Defines.TRAN_RESULT_OK)
                {
                    MessageBox.Show(this, "Komut hatası: " + retcode.ToString() + " (" + retcode.ToString("X") + ")");
                    return;
                }
            }


            // select back printer
            SendBuf[0] = 0x1b;
            SendBuf[1] = 0x63;
            SendBuf[2] = 0x30;
            SendBuf[3] = 0x01;
            retcode = GMPSmartDLL.FP3_SendFrontStationPrintEx(CurrentInterface, GetTransactionHandle(CurrentInterface), SendBuf, (short)(4), ReceiveBuffer, ref Len, Defines.TIMEOUT_DEFAULT, Defines.TIMEOUT_DEFAULT);

        }

        private void onlineInvoiceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            clearGroupBox();
            tabControl1.SelectedTab = tabPage14;
        }

        private void setOnlineTaxFreeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            clearGroupBox();
            tabControl1.SelectedTab = tabPage15;
        }

        private void m_btnSendOnlineInvoice_Click(object sender, EventArgs e)
        {
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_ONLINE_INVIOCE_INFO stOnlineInvoiceInfo = new ST_ONLINE_INVIOCE_INFO();

            string dateStr;

            UInt64 activeFlags = 0;

            m_stTicket.SaleInfo[0] = new ST_SALEINFO();

            stOnlineInvoiceInfo.CustomerName = m_txtCustName.Text;
            stOnlineInvoiceInfo.VKN = m_txtIDNo.Text;
            stOnlineInvoiceInfo.HomeAddress = m_txtAddress.Text;
            stOnlineInvoiceInfo.District = m_txtDistrict.Text;
            stOnlineInvoiceInfo.City = m_txtCity.Text;
            stOnlineInvoiceInfo.Country = m_txtCountry.Text;
            stOnlineInvoiceInfo.Mail = m_txtEmail.Text;
            stOnlineInvoiceInfo.WebSite = m_txtWeb.Text;
            stOnlineInvoiceInfo.Phone = m_txtPhone.Text;
            stOnlineInvoiceInfo.TaxOffice = m_txtTaxOffice.Text;
            //stOnlineInvoiceInfo.Ettn = m_txtEttn.Text;
            stOnlineInvoiceInfo.DespatchNo = m_txtDespatchNo.Text;
            stOnlineInvoiceInfo.Identifier = m_txtID.Text;
            stOnlineInvoiceInfo.OrderNo = m_txtOrderNo.Text;
            stOnlineInvoiceInfo.SellerIdentifier_OnlineInvoice = m_txtSupplierID.Text;
            stOnlineInvoiceInfo.SellerIdentifier_OnlineArchive = m_txtSupplierID2.Text;
            //stOnlineInvoiceInfo.su

            //string str2;
            //str2 = '0' + (m_cmbOnlineInvoiceType.SelectedIndex + 1).ToString();

            //stOnlineInvoiceInfo.Type = new byte[2];
            //ConvertStringToHexArray(str2, ref stOnlineInvoiceInfo.Type, 2);
            //Array.Reverse(stOnlineInvoiceInfo.Type);

            //stOnlineInvoiceInfo.Ettn = m_txtEttn.Text;

            if (m_checkOrderDate.Checked)
            {
                stOnlineInvoiceInfo.OrderDate = new byte[4];
                dateStr = m_dateOrderDate.Value.Day.ToString().PadLeft(2, '0') + m_dateOrderDate.Value.Month.ToString().PadLeft(2, '0') + m_dateOrderDate.Value.Year.ToString().Substring(2, 2).PadLeft(2, '0') + "20";
                ConvertStringToHexArray(dateStr, ref stOnlineInvoiceInfo.OrderDate, 4);
                Array.Reverse(stOnlineInvoiceInfo.OrderDate);

                stOnlineInvoiceInfo.OrderNo = m_txtOrderNo.Text;
            }

            if (m_checkDespatchDate.Checked)
            {
                stOnlineInvoiceInfo.DespatchDate = new byte[4];
                dateStr = m_dateDespatchDate.Value.Day.ToString().PadLeft(2, '0') + m_dateDespatchDate.Value.Month.ToString().PadLeft(2, '0') + m_dateDespatchDate.Value.Year.ToString().Substring(2, 2).PadLeft(2, '0') + "20";
                ConvertStringToHexArray(dateStr, ref stOnlineInvoiceInfo.DespatchDate, 4);
                Array.Reverse(stOnlineInvoiceInfo.DespatchDate);

                stOnlineInvoiceInfo.DespatchNo = m_txtDespatchNo.Text;

            }
            stOnlineInvoiceInfo.Identifier = m_txtID.Text;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_SetOnlineInvoice(buffer, buffer.Length, ref stOnlineInvoiceInfo);
                AddIntoCommandBatch("prepare_SetOnlineInvoice", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                //Array.Clear(buffer, 0, buffer.Length);
                //bufferLen = 0;
                //bufferLen = GMPSmartDLL.prepare_TicketHeader(buffer, buffer.Length, TTicketType.TInvoice);
                //AddIntoCommandBatch("prepare_TicketHeader", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                //tabControl1.SelectedTab = tabPage6;
            }
            else
            {
                UInt32 retcode = 0;
                if (GetTransactionHandle(CurrentInterface) == 0)
                {
                    UInt64 TransactionHandle = 0;
                    retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TransactionHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
                    AddTrxHandles(CurrentInterface, TransactionHandle, isBackground);

                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);

                    retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, (Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS), 0x00000000, Defines.TIMEOUT_DEFAULT);
                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);
                }

                retcode = Json_GMPSmartDLL.FP3_SetOnlineInvoice(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stOnlineInvoiceInfo, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), TTicketType.TInvoice, Defines.TIMEOUT_DEFAULT);
                if ((retcode != Defines.TRAN_RESULT_OK) && (retcode != Defines.APP_ERR_TICKET_HEADER_ALREADY_PRINTED))
                {
                    HandleErrorCode(retcode);
                    return;
                }

                HandleErrorCode(retcode);
                DisplayTransaction(m_stTicket, false);
            }
        }

        private void m_btnGetOnlineInvoice_Click(object sender, EventArgs e)
        {
            ST_TICKET_HEADER stTicketHeader = new ST_TICKET_HEADER();
            ST_ONLINE_INVIOCE_INFO stOnlineInvoice = new ST_ONLINE_INVIOCE_INFO();

            UInt32 retcode;

            byte[] id = new byte[100];

            if (m_txtIDNo.Text == "")
                MessageBox.Show("Lütfen VKN bilgisini giriniz...");
            else
            {
                ConvertAscToBcdArray(m_txtIDNo.Text, ref id, id.Length);

                retcode = Json_GMPSmartDLL.FP3_GetOnlineInvoiceInfo(CurrentInterface, id, m_txtIDNo.Text.Length, ref stOnlineInvoice, Defines.TIMEOUT_DEFAULT);

                if (retcode != Defines.TRAN_RESULT_OK)
                {
                    HandleErrorCode(retcode);
                    return;
                }
                m_txtCustName.Text = stOnlineInvoice.CustomerName;
                m_txtIDNo.Text = stOnlineInvoice.VKN;
                m_txtAddress.Text = stOnlineInvoice.HomeAddress;
                m_txtDistrict.Text = stOnlineInvoice.District;
                m_txtCity.Text = stOnlineInvoice.City;
                m_txtCountry.Text = stOnlineInvoice.Country;
                m_txtEmail.Text = stOnlineInvoice.Mail;
                m_txtWeb.Text = stOnlineInvoice.WebSite;
                m_txtPhone.Text = stOnlineInvoice.Phone;
                m_txtTaxOffice.Text = stOnlineInvoice.TaxOffice;

                m_txtOrderNo.Text = stOnlineInvoice.OrderNo;

                m_txtDespatchNo.Text = stOnlineInvoice.DespatchNo;
                m_txtID.Text = stOnlineInvoice.Identifier;

                Array.Reverse(stOnlineInvoice.Type);

                string str = ConvertByteArrayToString(stOnlineInvoice.Type, 2);

                int itemindex = Convert.ToInt32(str);

                if (stOnlineInvoice.OrderDate[0] != 0x0)
                {
                    m_checkOrderDate.Checked = true;
                    m_dateOrderDate.Enabled = true;
                    string str1 = ConvertByteArrayToString(stOnlineInvoice.OrderDate, 7);

                    DateTime myDate1 = DateTime.ParseExact(str1, "yyyyMMddHHmmss",
                                           System.Globalization.CultureInfo.InvariantCulture);

                    m_dateOrderDate.Value = myDate1;
                }
                else
                {
                    m_checkOrderDate.Checked = false;
                    m_dateOrderDate.Enabled = false;
                }

                if (stOnlineInvoice.DespatchDate[0] != 0x0)
                {
                    m_checkDespatchDate.Checked = true;
                    m_dateDespatchDate.Enabled = true;
                    string str2 = ConvertByteArrayToString(stOnlineInvoice.DespatchDate, 7);

                    DateTime myDate2 = DateTime.ParseExact(str2, "yyyyMMddHHmmss", System.Globalization.CultureInfo.InvariantCulture);

                    m_dateDespatchDate.Value = myDate2;
                }
                else
                {
                    m_checkDespatchDate.Checked = false;
                    m_dateDespatchDate.Enabled = false;
                }
            }
        }

        private void m_btnSendTaxFree_Click(object sender, EventArgs e)
        {
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_TAXFREE_INFO stTaxFreeInfo = new ST_TAXFREE_INFO();

            string dateStr;

            UInt64 activeFlags = 0;

            stTaxFreeInfo.BuyerName = m_txtTaxFreeCustName.Text;
            stTaxFreeInfo.BuyerSurname = m_txtTaxFreeCustSurname.Text;
            stTaxFreeInfo.City = m_txtTaxFreeCity.Text;
            stTaxFreeInfo.Country = m_txtTaxFreeCountry.Text;
            stTaxFreeInfo.CountryCode = m_cmbTaxFreeCountryCode.Text.Substring(0, 2);
            stTaxFreeInfo.Ettn = m_txtTaxFreeETTN.Text;

            if (m_checkTaxFreeID.Checked)
            {
                stTaxFreeInfo.IDDate = new byte[4];
                dateStr = m_dateTaxFreeIDDate.Value.Day.ToString().PadLeft(2, '0') + m_dateTaxFreeIDDate.Value.Month.ToString().PadLeft(2, '0') + m_dateTaxFreeIDDate.Value.Year.ToString().Substring(2, 2).PadLeft(2, '0') + "20";
                ConvertStringToHexArray(dateStr, ref stTaxFreeInfo.IDDate, 4);
                Array.Reverse(stTaxFreeInfo.IDDate);
            }

            stTaxFreeInfo.Identifier = m_txtTaxFreeEtiket.Text;
            stTaxFreeInfo.VKN = m_txtTaxFreeVKN.Text;

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_SetTaxFreeInfo(buffer, buffer.Length, ref stTaxFreeInfo);
                AddIntoCommandBatch("prepare_SetTaxFreeInfo", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                //Array.Clear(buffer, 0, buffer.Length);
                //bufferLen = 0;
                //bufferLen = GMPSmartDLL.prepare_TicketHeader(buffer, buffer.Length, TTicketType.TInvoice);
                //AddIntoCommandBatch("prepare_TicketHeader", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                //tabControl1.SelectedTab = tabPage6;
            }
            else
            {
                UInt32 retcode = 0;
                if (GetTransactionHandle(CurrentInterface) == 0)
                {
                    UInt64 TransactionHandle = 0;
                    retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TransactionHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
                    AddTrxHandles(CurrentInterface, TransactionHandle, isBackground);

                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);

                    retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, (Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS), 0x00000000, Defines.TIMEOUT_DEFAULT);
                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);
                }

                retcode = Json_GMPSmartDLL.FP3_SetTaxFreeInfo(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stTaxFreeInfo, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), TTicketType.TInvoice, Defines.TIMEOUT_DEFAULT);
                if ((retcode != Defines.TRAN_RESULT_OK) && (retcode != Defines.APP_ERR_TICKET_HEADER_ALREADY_PRINTED))
                {
                    HandleErrorCode(retcode);
                    return;
                }

                HandleErrorCode(retcode);
                DisplayTransaction(m_stTicket, false);
            }
        }

        private void m_checkOrderDate_CheckedChanged(object sender, EventArgs e)
        {
            m_dateOrderDate.Enabled = m_checkOrderDate.Checked;
            m_txtOrderNo.Enabled = m_checkOrderDate.Checked;
        }

        private void m_checkDespatchDate_CheckedChanged(object sender, EventArgs e)
        {
            m_dateDespatchDate.Enabled = m_checkDespatchDate.Checked;
            m_txtDespatchNo.Enabled = m_checkDespatchDate.Checked;
        }

        private void m_checkTaxFreeID_CheckedChanged(object sender, EventArgs e)
        {
            m_dateTaxFreeIDDate.Enabled = m_checkTaxFreeID.Checked;
        }

        private void m_btnMusteriSorgu_Click(object sender, EventArgs e)
        {
            UInt64 activeFlags = 0;
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            ST_TICKET m_stTicket = new ST_TICKET();
            byte NumberOfTotalRecord = 24;
            byte NumberOfTotalRecordReceived = 0;
            ST_LOYALTY_SERVICE_REQ stLoyaltyServiceReq = new ST_LOYALTY_SERVICE_REQ();
            ST_LOYALTY_SERVICE_INFO[] stLoyaltyServiceInfo = new ST_LOYALTY_SERVICE_INFO[32];
            ST_PAYMENT_APPLICATION_INFO[] StPaymentApplicationInfo = new ST_PAYMENT_APPLICATION_INFO[24];

            for (int i = 0; i < StPaymentApplicationInfo.Length; i++)
            {
                StPaymentApplicationInfo[i] = new ST_PAYMENT_APPLICATION_INFO();
            }

            for (int i = 0; i < stLoyaltyServiceInfo.Length; i++)
            {
                stLoyaltyServiceInfo[i] = new ST_LOYALTY_SERVICE_INFO();
            }

            if (GetTransactionHandle(CurrentInterface) == 0)
            {
                MessageBox.Show("Lütfen İşlem Başlatınız");
                HandleErrorCode(retcode);
                return;
            }

            retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, (Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS | Defines.GMP3_OPTION_ECHO_LOYALTY_DETAILS), 0, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return;
            }

            retcode = Json_GMPSmartDLL.FP3_GetTicket(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return;
            }

            retcode = Json_GMPSmartDLL.FP3_GetVasApplicationInfo(CurrentInterface, ref NumberOfTotalRecord, ref NumberOfTotalRecordReceived, ref StPaymentApplicationInfo, (ushort)EVasType.TLV_OKC_ASSIST_VAS_TYPE_LOYALTY);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return;
            }

            if (NumberOfTotalRecordReceived == 0)
            {
                MessageBox.Show("ÖKC Üzerinde Ödeme Uygulanaması Bulunamadı", "HATA", MessageBoxButtons.OK);
                return;
            }

            PaymentAppForm paf = new PaymentAppForm(NumberOfTotalRecordReceived, StPaymentApplicationInfo);
            DialogResult dr = paf.ShowDialog();
            if (dr != System.Windows.Forms.DialogResult.OK)
                return;

            if (paf.pstPaymentApplicationInfoSelected == null)
            {
                MessageBox.Show("Lütfen UYGULAMA Seçiniz");
                return;
            }

            if (paf.pstPaymentApplicationInfoSelected.u16BKMId.Equals(null))
            {
                MessageBox.Show("UYGULAMA ID = 0");
                return;
            }

            retcode = Json_GMPSmartDLL.FP3_GetVasLoyaltyServiceInfo(CurrentInterface, ref NumberOfTotalRecord, ref NumberOfTotalRecordReceived, ref stLoyaltyServiceInfo, paf.pstPaymentApplicationInfoSelected.u16AppId);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return;
            }

            if (NumberOfTotalRecordReceived == 0)
            {
                MessageBox.Show("ÖKC Üzerinde Servis Listesi Bulunamadı", "HATA", MessageBoxButtons.OK);
                return;
            }

            paf = new PaymentAppForm(NumberOfTotalRecordReceived, stLoyaltyServiceInfo);
            if (paf.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                return;

            if (paf.m_stLoyaltyServiceInfo == null)
            {
                MessageBox.Show("Lütfen Servis Seçiniz");
                return;
            }

            GetInputForm gif = new GetInputForm("CODE", "", 2);
            if (gif.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                return;

            stLoyaltyServiceReq.CustomerId = gif.textBox1.Text;
            stLoyaltyServiceReq.CustomerIdType = Defines.LOYALTY_CUSTOMER_ID_TYPE_MUSTERI_NO; // HOPI icin gerekli deger
            stLoyaltyServiceReq.ServiceId = paf.pstLoyaltyServiceInfoSelected.ServiceId;
            stLoyaltyServiceReq.u16AppId = paf.pstLoyaltyServiceInfoSelected.u16AppId;

            if (m_txtInputData.Text.Length > 0)
            {
                stLoyaltyServiceReq.Amount = (uint)getAmount(m_txtInputData.Text);
                m_txtInputData.Text = "";
            }

            ConvertAscToBcdArray("RAW DATA FROM EXTERNAL DEVICE TO LOYALTY APPLICATION", ref stLoyaltyServiceReq.rawData, stLoyaltyServiceReq.rawDataLen);
            stLoyaltyServiceReq.rawDataLen = (ushort)("RAW DATA FROM EXTERNAL DEVICE TO LOYALTY APPLICATION").Length;

            retcode = Json_GMPSmartDLL.FP3_LoyaltyCustomerQuery(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stLoyaltyServiceReq, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return;
            }

            DisplayTransaction(m_stTicket, true);

            if (stLoyaltyServiceReq.ServiceId != 3)
                return;

            Int32 changedAmount = 0;

            retcode = Json_GMPSmartDLL.FP3_LoyaltyDiscount(CurrentInterface, GetTransactionHandle(CurrentInterface), (byte)1, 100, 10, "100877", "INDIRIM", 0xFFFF, ref changedAmount, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return;
            }
        }

        private void m_btnLoyaltyIslem_Click(object sender, EventArgs e)
        {
            UInt64 activeFlags = 0;
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            ST_TICKET m_stTicket = new ST_TICKET();

            if (GetTransactionHandle(CurrentInterface) == 0)
            {
                MessageBox.Show("Lütfen İşlem Başlatınız");
                return;
            }

            retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, (Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS | Defines.GMP3_OPTION_ECHO_LOYALTY_DETAILS), 0, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return;
            }

            retcode = Json_GMPSmartDLL.FP3_GetTicket(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
                return;
            }

            PaymentAppForm paf = new PaymentAppForm((byte)m_stTicket.numberOfLoyaltyInThis, m_stTicket.stLoyaltyService);
            DialogResult dr = paf.ShowDialog();
            if (dr != System.Windows.Forms.DialogResult.OK)
                return;

            if (paf.pstLoyaltyServiceInfoSelected == null)
            {
                MessageBox.Show("Lütfen UYGULAMA Seçiniz");
                return;
            }

            KampanyaName = GMP_Tools.GetStringFromBytes(paf.pstLoyaltyServiceInfoSelected.name);
            KampanyaBkmId = paf.pstLoyaltyServiceInfoSelected.u16AppId.ToString();
            KampanyaServiceId = paf.pstLoyaltyServiceInfoSelected.ServiceId.ToString();
            KampanyaCustomerId = paf.pstLoyaltyServiceInfoSelected.CustomerId;

            groupBox17.Visible = true;
            groupBox16.Visible = false;

            tabControl1.SelectedTab = tabPage3;

        }

        private void checkInterfacePairingStatusToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 retcode = GMPSmartDLL.FP3_IsGmpPairingDone(CurrentInterface);
            if (retcode == 0)
                MessageBox.Show("Eşleşme yapılmamış", "Warning!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
                MessageBox.Show("Eşleşme yapılmış. Fakat eşlenilen ÖKC ile harici cihaza takılı ÖKC aynı cihaz olmayabilir. Lütfen kontrol ediniz.", "Warning!", MessageBoxButtons.OK, MessageBoxIcon.Warning);

        }

        public int DepartmentSaleForTaxTest(int deptIndex)
        {
            uint retcode = 0;
            string name = "";
            string barcode = "";
            int amount = 100;
            UInt16 currency = 949;
            byte unitType = 3;
            UInt32 itemCount = 0;
            byte itemCountPrecition = 3;
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_ITEM stItem = new ST_ITEM();

            m_lblErrorCode.Text = "";

            stItem.type = Defines.ITEM_TYPE_DEPARTMENT;
            stItem.subType = 0;
            stItem.deptIndex = (byte)(deptIndex - 1);
            stItem.amount = (uint)amount;
            stItem.currency = currency;
            stItem.count = itemCount;
            stItem.unitType = unitType;
            stItem.pluPriceIndex = 0;
            stItem.countPrecition = itemCountPrecition;
            stItem.name = name;
            stItem.barcode = barcode;

            for (int i = 0; i < 12; i++)
            {
                stDepartmentsTmp[i] = new ST_DEPARTMENT();
            }

            UInt32 RetCode = Json_GMPSmartDLL.FP3_GetTaxRates(GMPForm.CurrentInterface, ref numberOfTotalTaxRates, ref numberOfTotalRecordsReceived, ref stTaxRatesTmp, 8);
            RetCode = Json_GMPSmartDLL.FP3_GetDepartments(GMPForm.CurrentInterface, ref numberOfTotalDepartments, ref numberOfTotalRecordsReceived, ref stDepartmentsTmp, 12);

            int taxIndex = 0;
            for (taxIndex = 0; taxIndex < stTaxRatesForStart.Length; taxIndex++)
            {
                if (stTaxRatesForStart[taxIndex].taxRate != 0)
                {
                    break;
                }
            }
            if (taxIndex == stTaxRatesForStart.Length)
            {
                for (int i = 0; i < stTaxRatesForStart.Length; i++)
                {
                    stTaxRatesForStart[i].taxRate = stTaxRatesTmp[i].taxRate;  //Init edildi.                  
                }
                for (int i = 0; i < 12; i++)
                {
                    stDepartmentsForStart[i] = new ST_DEPARTMENT();
                }
                for (int i = 0; i < stDepartmentsForStart.Length; i++)
                {
                    stDepartmentsForStart[i].u8TaxIndex = stDepartmentsTmp[i].u8TaxIndex;  //Init edildi.                  
                }
            }

            bool isTaxHasChanged = false;
            for (int i = 0; i < 8; i++)
            {
                if (stTaxRatesTmp[i].taxRate != stTaxRatesForStart[i].taxRate)
                {
                    isTaxHasChanged = true;
                    break;
                }
            }
            if (isTaxHasChanged)
            {
                ST_DEPARTMENT[] stDepartments = new ST_DEPARTMENT[12];

                for (int i = 0; i < stDepartments.Length; i++)
                {
                    stDepartments[i] = new ST_DEPARTMENT();
                }

                RetCode = Json_GMPSmartDLL.FP3_GetDepartments(GMPForm.CurrentInterface, ref numberOfTotalDepartments, ref numberOfTotalRecordsReceived, ref stDepartments, 12);

                ErrorClass.DisplayErrorMessage(RetCode);

                for (int i = 0; i < stDepartments.Length; i++)
                {
                    int index = stDepartmentsForStart[i].u8TaxIndex;
                    for (int j = 0; j < stTaxRates.Length; j++)
                    {
                        if (stTaxRatesTmp[j].taxRate == stTaxRatesForStart[index].taxRate)
                        {
                            stDepartments[i].u8TaxIndex = Convert.ToByte(j);
                            break;
                        }
                    }
                }

                if (isTaxHasChanged)
                {
                    MessageBox.Show("KDV oranları değiştiği için Department tablosu güncellenecek");
                    PassForm pf = new PassForm();
                    pf.ShowDialog();

                    //retcode = Defines.DLL_RETCODE_FAIL;
                    if (pf.m_PASS != "")
                    {
                        retcode = Json_GMPSmartDLL.FP3_SetDepartments(GMPForm.CurrentInterface, ref stDepartments, 12, pf.m_PASS);
                    }
                }
            }

            retcode = StartTicket(TTicketType.TProcessSale);
            if (retcode != Defines.TRAN_RESULT_OK)
                return (int)retcode;

            GMPSmartDLL.FiscalPrinter_GetHandle();

            retcode = Json_GMPSmartDLL.FP3_ItemSale(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stItem, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return (int)retcode;
            }

            HandleErrorCode(retcode);
            return (int)retcode;
        }

        public int GetPaymentTest(ST_PAYMENT_REQUEST[] stPaymentRequest, int numberOfPayments)
        {
            UInt32 retcode;
            ST_TICKET m_stTicket = new ST_TICKET();

            //char display[256];
            string display = "";


            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_Payment(buffer, buffer.Length, ref stPaymentRequest[0]);
                AddIntoCommandBatch("prepare_Payment", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);
                return Defines.TRAN_RESULT_OK;
            }
            else
            {
                m_lstBankErrorMessage.Items.Clear();

                retcode = Json_GMPSmartDLL.FP3_Payment(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stPaymentRequest[0], ref m_stTicket, 120000);

                for (int i = 0; i < m_stTicket.stPayment.Length; i++)
                {
                    if (m_stTicket.stPayment[i] != null)
                    {
                        if (m_stTicket.stPayment[i].stBankPayment.bankName != "")
                        {
                            m_lstBankErrorMessage.Items.Add(m_stTicket.stPayment[i].stBankPayment.bankName);
                            m_lstBankErrorMessage.Items.Add("Banking Error : " + m_stTicket.stPayment[i].stBankPayment.stPaymentErrMessage.ErrorCode + " " + m_stTicket.stPayment[i].stBankPayment.stPaymentErrMessage.ErrorMsg);
                            m_lstBankErrorMessage.Items.Add("Application Error : " + m_stTicket.stPayment[i].stBankPayment.stPaymentErrMessage.AppErrorCode + " " + m_stTicket.stPayment[i].stBankPayment.stPaymentErrMessage.AppErrorMsg);
                            m_lstBankErrorMessage.Items.Add("----------------------------------------------");
                        }
                    }
                }

                UInt32 TicketAmount = m_stTicket.TotalReceiptAmount + m_stTicket.KatkiPayiAmount;

                switch (retcode)
                {
                    case Defines.TRAN_RESULT_OK:

                        if (stPaymentRequest[0].numberOfinstallments != 0)
                            display += String.Format("TAKSIT SAYISI : {0}", stPaymentRequest[0].numberOfinstallments);

                        if (m_stTicket.KasaAvansAmount != 0)
                        {
                            display += String.Format("KASA AVANS TOTAL: {0}", formatAmount(m_stTicket.KasaAvansAmount, ECurrency.CURRENCY_TL));
                            TicketAmount = m_stTicket.KasaAvansAmount;
                        }
                        else if (m_stTicket.invoiceAmount != 0)
                        {
                            display += String.Format("INVOICE TOTAL : {0}", formatAmount(m_stTicket.invoiceAmount, ECurrency.CURRENCY_TL));
                            TicketAmount = m_stTicket.invoiceAmount;
                        }
                        else if ((TTicketType)m_stTicket.ticketType == TTicketType.TCariHesap)
                            display += String.Format("TOTAL : {0}", formatAmount(m_stTicket.stPayment[0].payAmount, ECurrency.CURRENCY_TL));
                        else
                            display += String.Format("TOTAL : {0}", formatAmount(m_stTicket.TotalReceiptAmount, ECurrency.CURRENCY_TL));

                        if (m_stTicket.CashBackAmount != 0)
                            display += String.Format(Environment.NewLine + "CASHBACK : {0}", formatAmount(m_stTicket.CashBackAmount, ECurrency.CURRENCY_TL));
                        else
                        {
                            if ((TTicketType)m_stTicket.ticketType == TTicketType.TCariHesap)
                                display += String.Format(Environment.NewLine + "REMAIN : {0}", formatAmount(m_stTicket.KasaPaymentAmount, ECurrency.CURRENCY_TL));
                            else
                                display += String.Format(Environment.NewLine + "REMAIN : {0}", formatAmount(m_stTicket.KasaPaymentAmount != 0 ? m_stTicket.KasaPaymentAmount - m_stTicket.stPayment[0].payAmount : TicketAmount - m_stTicket.TotalReceiptPayment, ECurrency.CURRENCY_TL));
                        }

                        if ((stPaymentRequest[0].typeOfPayment == (uint)EPaymentTypes.PAYMENT_BANK_CARD) || (stPaymentRequest[0].typeOfPayment == (uint)EPaymentTypes.PAYMENT_MOBILE))
                        {
                            display += String.Format(Environment.NewLine + "{0}", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.bankName);
                            display += String.Format(Environment.NewLine + "ONAY KODU : {0}", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.authorizeCode);
                            display += String.Format(Environment.NewLine + "{0}", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stCard.pan);
                        }

                        if (m_stTicket.TotalReceiptPayment >= TicketAmount)
                        {
                            retcode = GMPSmartDLL.FP3_PrintTotalsAndPayments(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                            if (retcode != Defines.TRAN_RESULT_OK && retcode != Defines.APP_ERR_ALREADY_DONE)
                                break;

                            retcode = GMPSmartDLL.FP3_PrintBeforeMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                            if (retcode != Defines.TRAN_RESULT_OK && retcode != Defines.APP_ERR_ALREADY_DONE)
                                break;

                            ST_USER_MESSAGE[] stUserMessage = new ST_USER_MESSAGE[1];
                            for (int i = 0; i < stUserMessage.Length; i++)
                            {
                                stUserMessage[i] = new ST_USER_MESSAGE();
                            }

                            stUserMessage[0].flag = Defines.PS_38 | Defines.PS_CENTER;
                            stUserMessage[0].message = Localization.ThankYou;
                            stUserMessage[0].len = (byte)Localization.ThankYou.Length;

                            retcode = Json_GMPSmartDLL.FP3_PrintUserMessage(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stUserMessage, (ushort)stUserMessage.Length, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                            retcode = GMPSmartDLL.FP3_PrintMF(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_CARD_TRANSACTIONS);
                            if (retcode != Defines.TRAN_RESULT_OK && retcode != Defines.APP_ERR_ALREADY_DONE)
                                break;

                            ClearTransactionUniqueId(CurrentInterface);
                            UInt64 TransHandle = GetTransactionHandle(CurrentInterface);
                            retcode = GMPSmartDLL.FP3_Close(CurrentInterface, TransHandle, Defines.TIMEOUT_DEFAULT);
                            if (retcode == Defines.TRAN_RESULT_OK)
                                DeleteTrxHandles(CurrentInterface, TransHandle);
                        }

                        DisplayTransaction(m_stTicket, false);
                        break;

                    case Defines.APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_NO_MORE_ERROR_CODE:
                        DisplayTransaction(m_stTicket, false);
                        break;

                    case Defines.APP_ERR_PAYMENT_NOT_SUCCESSFUL_AND_MORE_ERROR_CODE:
                        DisplayTransaction(m_stTicket, false);

                        if (m_stTicket.totalNumberOfPayments != 0 && m_stTicket.stPayment[0] != null)
                        {
                            if ((stPaymentRequest[0].typeOfPayment == (uint)EPaymentTypes.PAYMENT_BANK_CARD) || (stPaymentRequest[0].typeOfPayment == (uint)EPaymentTypes.PAYMENT_MOBILE))
                            {
                                display += String.Format(Environment.NewLine + "{0}({1})", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.ErrorMsg
                                                                                    , m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.ErrorCode
                                                                                    );
                                display += String.Format(Environment.NewLine + "{0}({1})", m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.AppErrorMsg
                                                                                    , m_stTicket.stPayment[m_stTicket.totalNumberOfPayments - 1].stBankPayment.stPaymentErrMessage.AppErrorCode
                                                                                    );
                            }
                        }

                        break;

                    default:
                        break;
                }

                if (display.Length != 0)
                    textBox1.Text = display;

                HandleErrorCode(retcode);

                m_comboBoxCurrency.SelectedIndex = 0;

            }
            return (int)retcode;
        }
        public int DepartmentSaleTest(int deptIndex)
        {
            uint retcode = 0;
            string name = "";
            string barcode = "";
            int amount = 100;
            UInt16 currency = 949;
            byte unitType = 3;
            UInt32 itemCount = 0;
            byte itemCountPrecition = 3;
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_ITEM stItem = new ST_ITEM();

            m_lblErrorCode.Text = "";

            stItem.type = Defines.ITEM_TYPE_DEPARTMENT;
            stItem.subType = 0;
            stItem.deptIndex = (byte)(deptIndex - 1);
            stItem.amount = (uint)amount;
            stItem.currency = currency;
            stItem.count = itemCount;
            stItem.unitType = unitType;
            stItem.pluPriceIndex = 0;
            stItem.countPrecition = itemCountPrecition;
            stItem.name = name;
            stItem.barcode = barcode;

            retcode = StartTicket(TTicketType.TProcessSale);
            if (retcode != Defines.TRAN_RESULT_OK)
                return (int)retcode;

            GMPSmartDLL.FiscalPrinter_GetHandle();

            retcode = Json_GMPSmartDLL.FP3_ItemSale(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stItem, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

            if (retcode != 0)
            {
                HandleErrorCode(retcode);
                return (int)retcode;
            }

            HandleErrorCode(retcode);
            return (int)retcode;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Test TestForm = new Test();
            TestForm.ShowDialog();
        }

       private void m_btnStatus_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem m_btn = (ToolStripMenuItem)sender;
            byte status = Convert.ToByte(m_btn.Name.Substring(m_btn.Name.Length -1));
            m_treeHandleList.Nodes.Clear();

            UInt32[] InterfaceList = new UInt32[20];
            byte[] ID = new byte[64];
            UInt32 InterfaceCount = GMPSmartDLL.FP3_GetInterfaceHandleList(InterfaceList, (UInt32)InterfaceList.Length);
            TreeNode HandleTree;

            for (UInt32 Index = 0; Index < InterfaceCount; ++Index)
            {
                GMPSmartDLL.FP3_GetInterfaceID(InterfaceList[Index], ID, (UInt32)ID.Length);
                string Handle = InterfaceList[Index].ToString("X8") + "-" + GMP_Tools.SetEncoding(ID);

                HandleTree = new TreeNode(Handle);
                HandleTree.Tag = InterfaceList[Index];
                m_treeHandleList.Nodes.Add(HandleTree);

                UInt16 totalNumberOfHandles = 0;
                UInt16 totalNumberOfHandlesInThis = 0;
                UInt16 totalNumberOfHandlesRead = 0;
                byte isBackgroundTrx = 0;
                ST_HANDLE_LIST[] stHandleList = new ST_HANDLE_LIST[64];

                do
                {
                    totalNumberOfHandlesInThis = 0;
                    for (int i = 0; i < stHandleList.Length; i++)
                    {
                        stHandleList[i] = new ST_HANDLE_LIST();
                    }
                    UInt32 retcode = Json_GMPSmartDLL.FP3_FunctionGetHandleList(
                                                                   InterfaceList[Index],
                                                                   ref stHandleList,
                                                                   status,
                                                                   totalNumberOfHandlesRead,
                                                                   (ushort)stHandleList.Length,
                                                                   ref totalNumberOfHandles,
                                                                   ref totalNumberOfHandlesInThis,
                                                                   Defines.TIMEOUT_DEFAULT);
                    if (retcode != 0)
                    {
                        HandleErrorCode(retcode);
                    }

                    for (int i = 0; i < totalNumberOfHandlesInThis; i++)
                    {
                        if (stHandleList[i].Handle != 0)
                            AddTrxHandles(InterfaceList[Index], stHandleList[i].Handle, isBackgroundTrx);

                        isBackgroundTrx = 1;
                    }
                    totalNumberOfHandlesRead += totalNumberOfHandlesInThis;
                } while (totalNumberOfHandlesRead < totalNumberOfHandles);
            }

        }

        private void m_btnSendCariHesap_Click(object sender, EventArgs e)
        {
	        UInt32 retcode;
	        ST_TICKET m_stTicket = new ST_TICKET();

            string sCustomerName;
            string sTCKN;
            string sVKN;
            string sBelgeNo;
            string sBelgeDate;

	        int amount = getAmount(m_txtInputData.Text);
	        if(amount==0)
	        {
		        MessageBox.Show( "Lütfen tutar giriniz!" );
		        return;
	        }
           
	        if (m_rbBatchMode.Checked)
	        {
		        byte[] buffer = new byte[1024];
                int bufferLen = 0;
		        bufferLen = GMPSmartDLL.prepare_KasaAvans( buffer, buffer.Length,amount,"","","");
		        AddIntoCommandBatch( "prepare_KasaAvans", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen ); 
	        }
	        else
	        {
		        if(m_txtCariHesapCustName.Text == " ")
		        {
			        MessageBox.Show( "Lütfen Müşteri Adını giriniz!");
                    
			        return;
		        }
		        else sCustomerName = m_txtCariHesapCustName.Text;

		        if((m_txtCariHesapVKN.Text == "" ) && (m_txtCariHesapTCKN.Text == ""))
		        {
			        MessageBox.Show( "Lütfen TCKN ya da VKN giriniz!");
			        return;
		        }
		        else
		        {
                    sTCKN = m_txtCariHesapTCKN.Text;
                    sVKN = m_txtCariHesapVKN.Text;
		        }
		        if(m_txtCariHesapDokumanNo.Text == "")			
		        {
			        MessageBox.Show("Lütfen Döküman Numarasını giriniz!" );
			        return;
		        }
		        else
                    sBelgeNo = m_txtCariHesapDokumanNo.Text;
		
                sBelgeDate = m_dateCariHesapDate.Value.Day.ToString().PadLeft(2, '0') + m_dateCariHesapDate.Value.Month.ToString().PadLeft(2, '0') + m_dateCariHesapDate.Value.Year.ToString().Substring(2, 2).PadLeft(2, '0');
                
                retcode = StartTicket(TTicketType.TCariHesap);
		        if (retcode != Defines.TRAN_RESULT_OK)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                retcode = Json_GMPSmartDLL.Json_FP3_CariHesap(CurrentInterface, GetTransactionHandle(CurrentInterface), getAmount(m_txtInputData.Text), ref m_stTicket, sCustomerName, sTCKN, sVKN, sBelgeNo, sBelgeDate, Defines.TIMEOUT_DEFAULT);
                if (retcode != Defines.TRAN_RESULT_OK)
                {
			        HandleErrorCode(retcode);
			        return;
		        }

                DisplayTransaction(m_stTicket, false);
                HandleErrorCode(retcode);
	        }	
        }

        private void cariHesapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            clearGroupBox();
            tabControl1.SelectedTab = tabPage2;
        }

        private void m_btnReloadTransaction_Click(object sender, EventArgs e)
        {
            UInt32 RetCode = ReloadTransaction();

            HandleErrorCode(RetCode);
        }

        private void m_btnPaymentCash_Click(object sender, EventArgs e)
        {
            MessageBox.Show("20");
            UInt32 amount = 0;
            UInt16 currencyOfPayment = Convert.ToUInt16( m_comboBoxCurrency.Text.Substring(0, 3) );
            ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];
            
            ST_EXCHANGE_PROFILE[] stExchangeProfile = new ST_EXCHANGE_PROFILE[4];


            if (m_comboBoxCurrency.SelectedIndex == -1)
                m_comboBoxCurrency.SelectedIndex = 0;
            
            if (currencyOfPayment == (UInt16)ECurrency.CURRENCY_NONE)
                currencyOfPayment = (UInt16)ECurrency.CURRENCY_TL;
            else if (currencyOfPayment != (UInt16)ECurrency.CURRENCY_TL)
            {
                UInt32 RetCode = 0;
                ST_TICKET m_stTicket = new ST_TICKET();
                UInt64 activeFlags = 0;

                RetCode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, 0, 0, Defines.TIMEOUT_DEFAULT);
                if (RetCode != Defines.TRAN_RESULT_OK)
                    return ;

                RetCode = Json_GMPSmartDLL.FP3_GetTicket(CurrentInterface, GetTransactionHandle(CurrentInterface), ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                if (RetCode != Defines.TRAN_RESULT_OK)
                    return ;

                if(m_stTicket.CurrencyProfileIndex == 0xFF)
                {
                    MessageBox.Show("Lütfen kur profili seçiniz", "HATA");
                    return;
                }
            }


            if (m_txtInputData.Text.Length > 0)
            {
                amount = (uint)getAmount(m_txtInputData.Text);
                m_txtInputData.Text = "";
            }

            for (int i = 0; i < stPaymentRequest.Length; i++)
            {
                stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
            }

            stPaymentRequest[0].typeOfPayment = (uint)EPaymentTypes.PAYMENT_CASH_TL;
            stPaymentRequest[0].subtypeOfPayment = 0;
            stPaymentRequest[0].payAmount = amount;
            stPaymentRequest[0].payAmountCurrencyCode = currencyOfPayment;

            GetPayment(stPaymentRequest, 1);
        }

        private void m_treeHandleList_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
                mnu.Show(m_treeHandleList, e.Location);
        }

        private void m_lblCurrentTransactionHandle_DoubleClick(object sender, EventArgs e)
        {
            SwitchBackgroundToForeground_Click(null, null);
        }

        private void m_txtPluBarcode_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar == (char)Keys.Return))
            {
                DepartmentSale(1);
                m_txtPluBarcode.Text = "";
                m_txtPluBarcode.Focus();
            }
        }

        private void transInquiryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            byte NumberOfTotalRecords = 0;
            byte NumberOfTotalRecordsReceived = 0;
            ST_PAYMENT_APPLICATION_INFO[] stPaymentApplicationInfo = new ST_PAYMENT_APPLICATION_INFO[24];
            UInt32 RetCode = Json_GMPSmartDLL.FP3_GetPaymentApplicationInfo(CurrentInterface, ref NumberOfTotalRecords, ref NumberOfTotalRecordsReceived, ref stPaymentApplicationInfo, 24);
    		if (RetCode != Defines.TRAN_RESULT_OK)
    		{
                HandleErrorCode(RetCode);
    			return;
        	}
    		else if (NumberOfTotalRecordsReceived == 0)
    		{
    			MessageBox.Show("ÖKC Üzerinde Ödeme Uygulanaması Bulunamadı", "HATA");
    			return;
    		}

            PaymentAppForm paymentAppForm = new PaymentAppForm(NumberOfTotalRecordsReceived, stPaymentApplicationInfo);
            DialogResult dr = paymentAppForm.ShowDialog();
            if (dr != System.Windows.Forms.DialogResult.OK)
                return;
            if (paymentAppForm.pstPaymentApplicationInfoSelected == null)
            {
                MessageBox.Show("Select BANK first...");
                return;
            }

            ST_TRANS_INQUIRY stTransInquiry = new ST_TRANS_INQUIRY();

            if (paymentAppForm.pstPaymentApplicationInfoSelected.u16BKMId.Equals(null))
                stTransInquiry.BankBkmId = 0;
            else
            {
                stTransInquiry.BankBkmId = paymentAppForm.pstPaymentApplicationInfoSelected.u16BKMId;
            }

            ////////////////// Terminal ID //////////////////////////
            GetInputForm gif = new GetInputForm("Terminal ID", "12345678", 2);
            dr = gif.ShowDialog();
            if (dr != System.Windows.Forms.DialogResult.OK)
                return;

            if (gif.Text == null || gif.Text == "")
            {
                MessageBox.Show("Enter Terminal ID...");
                return;
            }
            stTransInquiry.szTerminalId = gif.textBox1.Text;


    		////////////////// BATCH NO//////////////////////////
            gif = new GetInputForm("Batch", "1", 2);
            dr = gif.ShowDialog();
            if (dr != System.Windows.Forms.DialogResult.OK)
                return;

            if (gif.Text == null || gif.Text == "")
            {
                MessageBox.Show("Enter Batch...");
                return;
            }
            UInt32.TryParse(gif.textBox1.Text, out stTransInquiry.Batch);

    		////////////////// STAN//////////////////////////
            gif = new GetInputForm("Stan", "1", 2);
            dr = gif.ShowDialog();
            if (dr != System.Windows.Forms.DialogResult.OK)
                return;

            if (gif.Text == null || gif.Text == "")
            {
                MessageBox.Show("Enter Stan...");
                return;
            }
            UInt32.TryParse(gif.textBox1.Text, out stTransInquiry.Stan);

            RetCode = Json_GMPSmartDLL.FP3_FunctionTransactionInquiry(CurrentInterface, ref stTransInquiry, 120 * 1000);
            if (RetCode != Defines.TRAN_RESULT_OK)
                HandleErrorCode(RetCode);
            else if (stTransInquiry.szResponseCode == "00")
                MessageBox.Show("ResponseCode: " + stTransInquiry.MessageResponseCode.ToString() + ", AuthorisedBank: " + stTransInquiry.AuthorisedBank.ToString() + ", AuthorisedAmount: " + stTransInquiry.AuthorisedAmount + ", PAN:" + stTransInquiry.szPAN);
            else
                MessageBox.Show(stTransInquiry.szAdditionalResponseDescriptionForDisplay);
        }

        private void comboBoxUniquId_MouseClick(object sender, MouseEventArgs e)
        {
            try
            {
                CreateDbFile();

                string sql = "select UniqueId from [UniqueIdData]";

                SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
                SQLiteDataReader reader = command.ExecuteReader();

                comboBoxUniquId.Items.Clear();

                while (reader.Read())
                    comboBoxUniquId.Items.Add(reader.GetValue(reader.GetOrdinal("UniqueId")));
                reader.Close();
                reader = null;
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, "Interface Get TUID List : " + ex.Message);
            }
            finally
            {
                if (m_dbConnection != null)
                {
                    m_dbConnection.Close();
                    m_dbConnection = null;
                    GC.Collect();
                }
            }          
        }

        private void eKUKullanımBilgileriToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_listTransaction.Items.Clear();

            tabControl1.SelectedIndex = 0;
            uint retcode = Defines.TRAN_RESULT_OK;

            ST_MODULE_USAGE_INFO pstEkuModuleInfo = new ST_MODULE_USAGE_INFO();

            retcode = Json_GMPSmartDLL.FP3_FunctionModuleReadInfo(CurrentInterface, Defines.GMP_EXT_DEVICE_EKU_USAGE_INFO, ref pstEkuModuleInfo, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
            }

            TransactionInfo(m_listTransaction, "EKU MODULE INFO (DEVICE)");
            TransactionInfo(m_listTransaction, "------------------------");
            TransactionInfo(m_listTransaction, String.Format("HW REF      : {0}", pstEkuModuleInfo.szHardwareReference));
            TransactionInfo(m_listTransaction, String.Format("HW S/N      : {0}", pstEkuModuleInfo.szHardwareSerial));

            TransactionInfo(m_listTransaction, "\n");
            TransactionInfo(m_listTransaction, "EKU MODULE INFO (EKU)");
            TransactionInfo(m_listTransaction, "------------------------");
            TransactionInfo(m_listTransaction, "\n");
            TransactionInfo(m_listTransaction, "CAPACITY");
            TransactionInfo(m_listTransaction, String.Format("  DATA USED : {0} bytes", pstEkuModuleInfo.DataUsedArea));
            TransactionInfo(m_listTransaction, String.Format("  DATA FREE : {0} bytes", pstEkuModuleInfo.DataFreeArea));
            TransactionInfo(m_listTransaction, String.Format("  MAP USED:   {0} bytes", pstEkuModuleInfo.MapUsedArea));
            TransactionInfo(m_listTransaction, String.Format("  MAP FREE:   {0} bytes", pstEkuModuleInfo.MapFreeArea));

            HandleErrorCode(retcode);
        }

        private void fISCALKullanımBilgileriToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_listTransaction.Items.Clear();

            tabControl1.SelectedIndex = 0;
            uint retcode = Defines.TRAN_RESULT_OK;

            ST_MODULE_USAGE_INFO pstFiscalModuleInfo = new ST_MODULE_USAGE_INFO();

            retcode = Json_GMPSmartDLL.FP3_FunctionModuleReadInfo(CurrentInterface, Defines.GMP_EXT_DEVICE_FISCAL_USAGE_INFO, ref pstFiscalModuleInfo, Defines.TIMEOUT_DEFAULT);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                HandleErrorCode(retcode);
            }

            TransactionInfo(m_listTransaction, "FISCAL MODULE INFO (DEVICE)");
            TransactionInfo(m_listTransaction, "------------------------");
            TransactionInfo(m_listTransaction, String.Format("HW REF      : {0}", pstFiscalModuleInfo.szHardwareReference));
            TransactionInfo(m_listTransaction, String.Format("HW S/N      : {0}", pstFiscalModuleInfo.szHardwareSerial));

            TransactionInfo(m_listTransaction, "\n");
            TransactionInfo(m_listTransaction, "FISCAL MODULE INFO (FISCAL)");
            TransactionInfo(m_listTransaction, "------------------------");
            TransactionInfo(m_listTransaction, "\n");
            TransactionInfo(m_listTransaction, "CAPACITY");
            TransactionInfo(m_listTransaction, String.Format("  DATA USED : {0} bytes", pstFiscalModuleInfo.DataUsedArea));
            TransactionInfo(m_listTransaction, String.Format("  DATA FREE : {0} bytes", pstFiscalModuleInfo.DataFreeArea));
            TransactionInfo(m_listTransaction, String.Format("  MAP USED:   {0} bytes", pstFiscalModuleInfo.MapUsedArea));
            TransactionInfo(m_listTransaction, String.Format("  MAP FREE:   {0} bytes", pstFiscalModuleInfo.MapFreeArea));

            HandleErrorCode(retcode);
        }

        int[] keyPressed = new int[2];

        private void changeTimeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            TimeChangerForm tc = new TimeChangerForm();
            tc.SetTime(m_lblProcDate.Text, m_lblProcTime.Text);
            DialogResult dr2 = tc.ShowDialog();
            if (dr2 == System.Windows.Forms.DialogResult.OK)
            {
                string[] dateParse = tc.getDate().Split('.');
                string[] timeParse = tc.getTime().Split(':');

                DateTime time = new DateTime(Convert.ToInt32(dateParse[2]), Convert.ToInt32(dateParse[1]), Convert.ToInt32(dateParse[0]),
                Convert.ToInt32(timeParse[0]), Convert.ToInt32(timeParse[1]), Convert.ToInt32(timeParse[2]));

                ApplicationTime = time; 
            }

            timer1.Enabled = true;
        }

        private void setExchangeProfileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 result;
            ST_EXCHANGE_PROFILE [] profiles = new ST_EXCHANGE_PROFILE[4];
            result = Json_GMPSmartDLL.FP3_GetCurrencyProfile(GMPForm.CurrentInterface, ref profiles);
            if (result != 0)
            {
                ErrorClass.DisplayErrorMessage(result);
                return;
            }

            IList<string> profileNames = new List<string>();
            foreach (var item in profiles)
            {
                if(!string.IsNullOrWhiteSpace(item.ProfileName))
                    profileNames.Add(item.ProfileName);
            }

            FormProfilesSelection selectionForm = new FormProfilesSelection();
            selectionForm.SetProfileNames(profileNames);
            DialogResult dr =  selectionForm.ShowDialog();
            //(dr == DialogResult.OK)
        }


        //  Test işlemleri için
    
        private void buttonTestSale_Click(object sender, EventArgs e)
        {
            UInt64 TranHandle = 0;
            byte[] TsmSign = null;
            ST_TICKET m_stTicket = new ST_TICKET();
            ST_ITEM stItem = CreateAndFillItem();
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            byte isBackground = 0;

            UInt32 numberOfItems = 0;
            UInt32 repetition = 1;
            try
            {
                numberOfItems = Convert.ToUInt32(textBoxNumberOfItems.Text);
            }
            catch
            {
                MessageBox.Show("Girdiğiniz değeri kontrol ediniz!", "HATA", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            try
            {
                repetition = Convert.ToUInt32(textBoxRepetition.Text);
                if (repetition == 0) throw new Exception("0'dan büyük değer olmalı");
            }
            catch
            {
                MessageBox.Show("Girdiğiniz değeri kontrol ediniz!", "HATA", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            TTicketType ticketType = TTicketType.TProcessSale;
            byte[] UserData = new byte[] { 0x74, 0x65, 0x73, 0x74, 0x64, 0x61, 0x74, 0x61 };

            textBoxLog.AppendText("Cihaz : " + pairingResp.szEcrModel + "-" + pairingResp.szVersionNumber + "-" + pairingResp.szEcrSerialNumber);
            textBoxLog.AppendText("\n");
            textBoxLog.AppendText("Fiş tekrar sayısı : " + repetition);
            textBoxLog.AppendText("\n");
            textBoxLog.AppendText("Ürün adedi sayısı : " + numberOfItems);
            textBoxLog.AppendText("\n");
            textBoxLog.AppendText("--------------------------------------");
            textBoxLog.AppendText("\n");

            for (int k = 0; k < repetition; k++)
            {
                long startTick = DateTime.Now.Ticks;
                textBoxLog.AppendText((k+1) + ". Fiş =>");

                retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TranHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, TsmSign, TsmSign == null ? 0 : TsmSign.Length, UserData, UserData.Length, 10000);
                if (retcode == Defines.TRAN_RESULT_OK)
                    retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, TranHandle, ticketType, Defines.TIMEOUT_DEFAULT);

                if (retcode == Defines.TRAN_RESULT_OK)
                {
                    UInt64 activeFlags = 0;
                    retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, TranHandle, ref activeFlags, Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS, 0x00000000, Defines.TIMEOUT_DEFAULT);
                }

                m_stTicket.SaleInfo[0] = new ST_SALEINFO();

                for (int i = 0; i < numberOfItems; i++)
                {
                    retcode = Json_GMPSmartDLL.FP3_ItemSale(CurrentInterface, TranHandle, ref stItem, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                }

                UInt32 amount = 0;
                UInt16 currencyOfPayment = (UInt16)ECurrency.CURRENCY_TL;
                ST_PAYMENT_REQUEST[] stPaymentRequest = new ST_PAYMENT_REQUEST[1];
                amount = (uint)100 * numberOfItems;


                for (int i = 0; i < stPaymentRequest.Length; i++)
                {
                    stPaymentRequest[i] = new ST_PAYMENT_REQUEST();
                }

                stPaymentRequest[0].typeOfPayment = (uint)EPaymentTypes.PAYMENT_CASH_TL;
                stPaymentRequest[0].subtypeOfPayment = 0;
                stPaymentRequest[0].payAmount = amount;
                stPaymentRequest[0].payAmountCurrencyCode = currencyOfPayment;

                retcode = Json_GMPSmartDLL.FP3_Payment(CurrentInterface, TranHandle, ref stPaymentRequest[0], ref m_stTicket, 30000);

                ST_USER_MESSAGE[] stUserMessage = new ST_USER_MESSAGE[1];
                for (int i = 0; i < stUserMessage.Length; i++)
                {
                    stUserMessage[i] = new ST_USER_MESSAGE();
                }

                stUserMessage[0].flag = Defines.PS_38 | Defines.PS_CENTER;
                stUserMessage[0].message = Localization.ThankYou;
                stUserMessage[0].len = (byte)Localization.ThankYou.Length;

                retcode = GMPSmartDLL.FP3_PrintTotalsAndPayments(CurrentInterface, TranHandle, Defines.TIMEOUT_DEFAULT);
                //if (retcode != Defines.TRAN_RESULT_OK && retcode != Defines.APP_ERR_ALREADY_DONE)
                //    break;

                retcode = GMPSmartDLL.FP3_PrintBeforeMF(CurrentInterface, TranHandle, Defines.TIMEOUT_DEFAULT);
                //if (retcode != Defines.TRAN_RESULT_OK && retcode != Defines.APP_ERR_ALREADY_DONE)
                //    break;

                retcode = Json_GMPSmartDLL.FP3_PrintUserMessage(CurrentInterface, TranHandle, ref stUserMessage, (ushort)stUserMessage.Length, ref m_stTicket, Defines.TIMEOUT_DEFAULT);

                retcode = GMPSmartDLL.FP3_PrintMF(CurrentInterface, TranHandle, Defines.TIMEOUT_CARD_TRANSACTIONS);
                //if (retcode != Defines.TRAN_RESULT_OK && retcode != Defines.APP_ERR_ALREADY_DONE)
                //    break;

                ClearTransactionUniqueId(CurrentInterface);

                retcode = GMPSmartDLL.FP3_Close(CurrentInterface, TranHandle, Defines.TIMEOUT_DEFAULT);

                long endTick = DateTime.Now.Ticks;
                textBoxLog.AppendText(" Bitiş - Başlangıç = " + new TimeSpan(endTick - startTick).TotalMilliseconds + " ms");
                textBoxLog.AppendText("\n");
                if (retcode == Defines.TRAN_RESULT_OK)
                    DeleteTrxHandles(CurrentInterface, TranHandle);
            }
            textBoxLog.AppendText("\n\n");
        }

        private ST_ITEM CreateAndFillItem()
        {
            ST_ITEM stItem = new ST_ITEM();

            stItem.type = Defines.ITEM_TYPE_DEPARTMENT;
            stItem.subType = 0;
            stItem.deptIndex = (byte)0;
            stItem.amount = (uint)100;
            stItem.currency = 949;
            stItem.count = 1;
            stItem.unitType = 0;
            stItem.pluPriceIndex = 0;
            stItem.countPrecition = 0;
            stItem.name = "";
            stItem.barcode = "";

            return stItem;
        }

        private void buttonClearLog_Click(object sender, EventArgs e)
        {
            textBoxLog.Clear();
        }

        private void buttonSaveLog_Click(object sender, EventArgs e)
        {
            SaveFileDialog save = new SaveFileDialog();
            save.Filter = "Metin Dosyası|*.txt";
            save.OverwritePrompt = true;
            save.CreatePrompt = true;

            if (save.ShowDialog() == DialogResult.OK)
            {
                StreamWriter record = new StreamWriter(save.FileName);
                record.WriteLine(textBoxLog.Text);
                record.Close();
            }
        }

        private void buttonSMMSend_Click(object sender, EventArgs e)
        {
            uint retcode = 0;
            ST_TICKET m_stTicket = new ST_TICKET();
            UInt64 activeFlags = 0;

            ST_SMMData smmData = new ST_SMMData();
            smmData.AdiSoyadi = textBoxSMMAd.Text;
            smmData.Adres = textBoxSMMAdres.Text;
            smmData.VknTckn = textBoxSMMTCKN_VKN.Text; 
            smmData.Unvan = textBoxSMMUnvan.Text;
            smmData.VergiDairesi = textBoxSMMVergiDairesi.Text;
            try
            {
                smmData.StopajOrani = Convert.ToUInt16(textBoxSMMStopajOrani.Text);
                smmData.TevkifatOrani = comboBoxSMMTevkifat.SelectedIndex * 10; // sending as %
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "HATA", MessageBoxButtons.OK);
                return;
            }

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_SendSMMData(buffer, buffer.Length, ref smmData);
                AddIntoCommandBatch("prepare_SendSMMData", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                Array.Clear(buffer, 0, buffer.Length);
                bufferLen = 0;
                bufferLen = GMPSmartDLL.prepare_TicketHeader(buffer, buffer.Length, TTicketType.TSerbestMeslekMakbuzu);
                AddIntoCommandBatch("prepare_TicketHeader", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                tabControl1.SelectedTab = tabPage6;
            }
            else
            {
                if (GetTransactionHandle(CurrentInterface) == 0)
                {
                    UInt64 TransactionHandle = 0;
                    retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TransactionHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
                    AddTrxHandles(CurrentInterface, TransactionHandle, isBackground);

                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);

                    retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, (Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS), 0x00000000, Defines.TIMEOUT_DEFAULT);
                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);
                }

                retcode = Json_GMPSmartDLL.FP3_SendSMMData(CurrentInterface, GetTransactionHandle(CurrentInterface), ref smmData, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                //retcode = Json_GMPSmartDLL.FP3_SetInvoice(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stInvoiceInfo, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), TTicketType.TSerbestMeslekMakbuzu, Defines.TIMEOUT_DEFAULT);
                if ((retcode != Defines.TRAN_RESULT_OK) && (retcode != Defines.APP_ERR_TICKET_HEADER_ALREADY_PRINTED))
                {
                    HandleErrorCode(retcode);
                    return;
                }

                HandleErrorCode(retcode);
                DisplayTransaction(m_stTicket, false);
            }
            
        }

        private void buttonGPSend_Click(object sender, EventArgs e)
        {
            uint retcode = 0;
            ST_TICKET m_stTicket = new ST_TICKET();
            UInt64 activeFlags = 0;

            ST_Gider_Pusulasi giderPusulasi = new ST_Gider_Pusulasi();
            giderPusulasi.AliciAdiSoyadi = textBoxGPAliciAdSoyad.Text;
            giderPusulasi.AliciAdres = textBoxGPAdres.Text;
            giderPusulasi.AliciUnvan = textBoxGPUnvan.Text;
            giderPusulasi.SaticiAdiSoyadi = textBoxGPSaticiAdSoyad.Text;
            giderPusulasi.FaturaSeri = textBoxGPFaturaSeri.Text;
            giderPusulasi.FaturaSira = textBoxGPFaturaSira.Text;
            giderPusulasi.FaturaTarih = dateTimePickerGPFaturaTarih.Text;

            if (checkBoxGPKDVDahil.Checked)
                giderPusulasi.KDVDahil = true;
            else
                giderPusulasi.KDVDahil = false;

            try
            {
                giderPusulasi.StopajOrani = (ushort)(Convert.ToUInt16(textBoxGPStopajOrani.Text) * 100);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "HATA", MessageBoxButtons.OK);
                return;
            }

            if (m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                bufferLen = Json_GMPSmartDLL.prepare_SendGiderPusulasi(buffer, buffer.Length, ref giderPusulasi);
                AddIntoCommandBatch("prepare_SendGiderPusulasi", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                Array.Clear(buffer, 0, buffer.Length);
                bufferLen = 0;
                bufferLen = GMPSmartDLL.prepare_TicketHeader(buffer, buffer.Length, TTicketType.TGiderPusulasi);
                AddIntoCommandBatch("prepare_TicketHeader", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

                tabControl1.SelectedTab = tabPage6;
            }
            else
            {
                if (GetTransactionHandle(CurrentInterface) == 0)
                {
                    UInt64 TransactionHandle = 0;
                    retcode = GMPSmartDLL.FP3_Start(CurrentInterface, ref TransactionHandle, isBackground, GetUniqueIdByInterface(CurrentInterface), 24, null, 0, null, 0, Defines.TIMEOUT_DEFAULT);
                    AddTrxHandles(CurrentInterface, TransactionHandle, isBackground);

                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);

                    retcode = GMPSmartDLL.FP3_OptionFlags(CurrentInterface, GetTransactionHandle(CurrentInterface), ref activeFlags, (Defines.GMP3_OPTION_ECHO_PRINTER | Defines.GMP3_OPTION_ECHO_ITEM_DETAILS | Defines.GMP3_OPTION_ECHO_PAYMENT_DETAILS), 0x00000000, Defines.TIMEOUT_DEFAULT);
                    if (retcode != Defines.TRAN_RESULT_OK)
                        HandleErrorCode(retcode);
                }

                retcode = Json_GMPSmartDLL.FP3_SendGiderPusulasi(CurrentInterface, GetTransactionHandle(CurrentInterface), ref giderPusulasi, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                
                if (retcode != 0)
                {
                    HandleErrorCode(retcode);
                    return;
                }

                retcode = GMPSmartDLL.FP3_TicketHeader(CurrentInterface, GetTransactionHandle(CurrentInterface), TTicketType.TGiderPusulasi, Defines.TIMEOUT_DEFAULT);
                if ((retcode != Defines.TRAN_RESULT_OK) && (retcode != Defines.APP_ERR_TICKET_HEADER_ALREADY_PRINTED))
                {
                    HandleErrorCode(retcode);
                    return;
                }

                HandleErrorCode(retcode);
                DisplayTransaction(m_stTicket, false);
            }
        }

        private void odemeFişiToolStripMenuItem_Click(object sender, EventArgs e)
        {

            SlipForm slipForm = new SlipForm(this);
            slipForm.ShowDialog(this);
            HandleErrorCode(slipForm.GetRetcode());
        }

        private void slipYazmaAyarıToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SlipYazmaAyariForm form = new SlipYazmaAyariForm(this);
            form.ShowDialog();
        }

        private void kullanıcıDatasıToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UserDataForm form = new UserDataForm(this);
            form.ShowDialog();
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            DrawerStateForm form = new DrawerStateForm(this);
            form.ShowDialog();
        }

        private void testUserMessageToolStripMenuItem_Click(object sender, EventArgs e)
        {
                uint retcode = 0;
                //retcode = StartTicket(TTicketType.TTasnifDisi);
                retcode = StartTicket(TTicketType.TProcessSale);
                uint messageCount = 0;

                var gif = new GetInputForm("Kaç satır user message yazılsın.", "40", 2);
                var dr = gif.ShowDialog();
                UInt32.TryParse(gif.textBox1.Text, out messageCount);

                ST_USER_MESSAGE[] stUserMessage = new ST_USER_MESSAGE[messageCount];
                for (int i = 0; i < stUserMessage.Length; i++)
                {
                    stUserMessage[i] = new ST_USER_MESSAGE();
                    stUserMessage[i].flag = Defines.PS_38 | Defines.PS_CENTER;
                    stUserMessage[i].message = "Long User Message Test " + (i + 1) + " %8 20,00 TL";
                    stUserMessage[i].len = (byte)stUserMessage[0].message.Length;
                }

                ushort messageLength = (ushort)stUserMessage.Length;

                ST_TICKET m_stTicket = new ST_TICKET();
                retcode = Json_GMPSmartDLL.FP3_PrintUserMessage(CurrentInterface, GetTransactionHandle(CurrentInterface), ref stUserMessage, messageLength, ref m_stTicket, Defines.TIMEOUT_DEFAULT);
                //retcode = GMPSmartDLL.FP3_Close(CurrentInterface, GetTransactionHandle(CurrentInterface), Defines.TIMEOUT_DEFAULT);
                HandleErrorCode(retcode);
            }

        private void groupBox7_Enter(object sender, EventArgs e)
        {

        }
    }
}

