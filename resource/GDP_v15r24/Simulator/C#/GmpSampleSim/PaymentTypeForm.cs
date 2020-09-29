using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GmpSampleSim
{
    public partial class PaymentTypeForm : Form
    {
        public static int PaymentTypeIndex { get; set; }

        public PaymentTypeForm()
        {
            InitializeComponent();
            List<String> paymentType = new List<String>();

            paymentType.Add("SELECT TRANSACTION TYPE ON DEVICE");
            paymentType.Add("SALE");
            paymentType.Add("INSTALMENT SALE");
            paymentType.Add("BONUS SALE");

            for (int i = 0; i < paymentType.Count; i++)
            {

                string str = "";
                str += paymentType[i];

                m_listPaymentTypes.Items.Add(str);
            }
            m_listPaymentTypes.SelectedIndex = 0;
        }

        private void m_listPaymentTypes_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_listPaymentTypes.SelectedIndex != -1)
            {
                PaymentTypeIndex = m_listPaymentTypes.SelectedIndex;
                
                //pstPaymentApplicationInfoSelected = stPaymentApplicationInfo2[i];
                //stPaymentRequest[0].subtypeOfPayment
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            Close();
        }

    }
}
