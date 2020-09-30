using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;


namespace GmpSampleSim
{
    public partial class PaymentAppForm : Form
    {
        public PaymentAppForm()
        {
            InitializeComponent();
        }

        private bool IsLoyalty = false;
        public byte numberOfTotalRecords;
        public uint m_paymentType;

        public ST_PAYMENT_APPLICATION_INFO[] stPaymentApplicationInfo2;
        public ST_PAYMENT_APPLICATION_INFO pstPaymentApplicationInfoSelected;

        public ST_LOYALTY_SERVICE_INFO[] m_stLoyaltyServiceInfo;
        public ST_LOYALTY_SERVICE_INFO pstLoyaltyServiceInfoSelected;

        string getAppTypeName(ushort m_typeOfPayment)
        {

            if (m_typeOfPayment == 0)
                return "";


            EVasType typeOfPayment = (EVasType)m_typeOfPayment;

            switch (typeOfPayment)
            {
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_ADISYON:
                    return "TYPE_ADISYON";
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_IN_FLIGHT:
                    return("TYPE_IN_FLIGHT");
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_INGENICO:
                    return("TYPE_INGENICO");
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_OTHER:
                    return("TYPE_OTHER");
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_AKTIFNOKTA:
                    return("TYPE_AKTIF.");
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_MOBIL_ODEME:
                    return("TYPE_MOBIL_ODEME");
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_OTOPARK:
                    return("TYPE_OTOPARK");
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_YEMEKCEKI:
                    return("TYPE_YEMEKCEKI");
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_LOYALTY:
                    return("TYPE_LOYALTY");
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_PAYMENT:
                    return("TYPE_ODEME");
                case EVasType.TLV_OKC_ASSIST_VAS_TYPE_ALL:
                    return "";
                default:
                    return("TYPE_UNKNOWN");
            }
        }

        public PaymentAppForm(byte numberOfTotalRecordsReceived, ST_PAYMENT_APPLICATION_INFO[] stPaymentApplicationInfo)
        {
            InitializeComponent();

            IsLoyalty = false;

            stPaymentApplicationInfo2 = new ST_PAYMENT_APPLICATION_INFO[24];
            Array.Copy(stPaymentApplicationInfo, stPaymentApplicationInfo2, stPaymentApplicationInfo.Length);
            for (int i = 0; i < numberOfTotalRecordsReceived; i++)
            {

                string str = "";
                str += GMP_Tools.GetStringFromBytes(stPaymentApplicationInfo[i].name) + 
                    " [" + stPaymentApplicationInfo[i].u16BKMId.ToString() + "] " + 
                    " [" + stPaymentApplicationInfo[i].u16AppId.ToString("X2") + "] " +
                    " [" + stPaymentApplicationInfo[i].Status.ToString() + "] " +
                    " [" + stPaymentApplicationInfo[i].Priority.ToString() + "]" +
                    " [" + getAppTypeName(stPaymentApplicationInfo[i].AppType) + "]";

                m_listPaymentApplications.Items.Add(str);
            }
            if (numberOfTotalRecordsReceived > 0)
                pstPaymentApplicationInfoSelected = null;

        }

        public PaymentAppForm(byte numberOfTotalRecordsReceived, ST_LOYALTY_SERVICE_INFO[] stLoyaltyServiceInfo)
        {
            InitializeComponent();

            IsLoyalty = true;

            m_stLoyaltyServiceInfo = new ST_LOYALTY_SERVICE_INFO[16];
            Array.Copy(stLoyaltyServiceInfo, m_stLoyaltyServiceInfo, stLoyaltyServiceInfo.Length);

            for (int i = 0; i < numberOfTotalRecordsReceived; i++)
            {

                string str = "";
                str += GMP_Tools.GetStringFromBytes(stLoyaltyServiceInfo[i].name) + " [" + stLoyaltyServiceInfo[i].ServiceId + "]";

                m_listPaymentApplications.Items.Add(str);
            }
            if (numberOfTotalRecordsReceived > 0)
                pstLoyaltyServiceInfoSelected = null;

        }

        public PaymentAppForm(int a)
        {
            InitializeComponent();

            m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_CASH");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_BANK_CARD_VOID");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_BANK_CARD_REFUND");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_YEMEKCEKI");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_MOBILE");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_HEDIYE_CEKI");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_PUAN");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_ACIK_HESAP");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_KAPORA");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_GIDER_PUSULASI");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_BANKA_TRANSFERI");
		    m_listPaymentApplications.Items.Add("REVERSE_PAYMENT_CEK");

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            Close();
        }

        uint GetPaymentType(string Text)
        {
            switch (Text)
            {
                case ("REVERSE_PAYMENT_CASH") : 
                    return (int)EPaymentTypes.REVERSE_PAYMENT_CASH;
                case ("REVERSE_PAYMENT_BANK_CARD_VOID"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_VOID;
                case ("REVERSE_PAYMENT_BANK_CARD_REFUND"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_BANK_CARD_REFUND;
                case ("REVERSE_PAYMENT_YEMEKCEKI"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_YEMEKCEKI;
                case ("REVERSE_PAYMENT_MOBILE"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_MOBILE;
                case ("REVERSE_PAYMENT_HEDIYE_CEKI"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_HEDIYE_CEKI;
                case ("REVERSE_PAYMENT_PUAN"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_PUAN;
                case ("REVERSE_PAYMENT_ACIK_HESAP"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_ACIK_HESAP;
                case ("REVERSE_PAYMENT_KAPORA"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_KAPORA;
                case ("REVERSE_PAYMENT_GIDER_PUSULASI"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_GIDER_PUSULASI;
                case ("REVERSE_PAYMENT_BANKA_TRANSFERI"):
                    return (int)EPaymentTypes.REVERSE_PAYMENT_BANKA_TRANSFERI;
                default:
                    return 0xFF;
            }

        }

        private void m_listPaymentApplications_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            int i = m_listPaymentApplications.SelectedIndex;

            if (i >= 0)
            {
                m_paymentType = 0xFF;

                m_paymentType = GetPaymentType(m_listPaymentApplications.SelectedItem.ToString());

                if (IsLoyalty == false && i != -1 && m_paymentType == 0xFF)
                    pstPaymentApplicationInfoSelected = stPaymentApplicationInfo2[i];
                else if (IsLoyalty == true && i != -1 && m_paymentType == 0xFF)
                    pstLoyaltyServiceInfoSelected = m_stLoyaltyServiceInfo[i];
            }
        }

    }
}
