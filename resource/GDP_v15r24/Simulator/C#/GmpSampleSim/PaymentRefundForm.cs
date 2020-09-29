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
    public partial class PaymentRefundForm : Form
    {

        public static int PaymentRefundIndex { get; set; }

        public PaymentRefundForm()
        {
            InitializeComponent();
            List<String> paymentRefund = new List<string>();

            paymentRefund.Add("REFUND WITH REFERENCE");
            paymentRefund.Add("REFUND W/O REFERENCE");
            paymentRefund.Add("REFUND WITH INSTALLMENT");
            paymentRefund.Add("REFUND WITH CARD WITH REFERENCE");
            paymentRefund.Add("REFUND W/O CARD WITH REFERENCE");

            for (int i = 0; i < paymentRefund.Count; i++)
            {
                string str = "";
                str += paymentRefund[i];

                m_listPaymentRefund.Items.Add(str);
            }
            m_listPaymentRefund.SelectedIndex = 0;
        }

        private void m_listPaymentRefund_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_listPaymentRefund.SelectedIndex != -1)
            {
                PaymentRefundIndex = m_listPaymentRefund.SelectedIndex;

            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            Close();
        }
    }
}
