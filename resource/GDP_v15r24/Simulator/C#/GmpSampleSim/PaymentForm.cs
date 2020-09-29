using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace GmpSampleSim
{
    public partial class PaymentForm : Form
    {
        public PaymentForm()
        {
            InitializeComponent();
        }

        public int selectedIndex= 0;

        public PaymentForm(ST_PAYMENT[] m_stPayment, int m_numberOfPayments )
        {
            InitializeComponent();

            m_listPayment.Columns.Add("typeOfPayment");
            m_listPayment.Columns.Add("subtypeOfPayment");
            m_listPayment.Columns.Add("flags");
            m_listPayment.Columns.Add("dateOfPayment");
            m_listPayment.Columns.Add("orgAmount");
            m_listPayment.Columns.Add("payAmount");
            m_listPayment.Columns.Add("curreny");

            GMPForm gf = new GMPForm();
            for( int i=0;i<m_numberOfPayments;i++ )
	        {
                ListViewItem item1 = new ListViewItem(gf.GetPaymentTypeName((int)m_stPayment[i].typeOfPayment));
		        item1.SubItems.Add(gf.GetPaymentSubtypeName((int)m_stPayment[i].subtypeOfPayment));
		        item1.SubItems.Add(m_stPayment[i].flags.ToString("X8"));
		        item1.SubItems.Add(m_stPayment[i].dateOfPayment.ToString("X8"));
                item1.SubItems.Add(gf.formatAmount(m_stPayment[i].orgAmount, (ECurrency)m_stPayment[i].orgAmountCurrencyCode));
                item1.SubItems.Add(gf.formatAmount(m_stPayment[i].payAmount, (ECurrency)m_stPayment[i].payAmountCurrencyCode));
                item1.SubItems.Add(gf.formatAmount(m_stPayment[i].cashBackAmountInTL, ECurrency.CURRENCY_TL));

                m_listPayment.Items.Add(item1);
	        }

            m_listBankPayment.Columns.Add("bankName");
	        m_listBankPayment.Columns.Add("bankBkmId" );
	        m_listBankPayment.Columns.Add("terminalId" );
	        m_listBankPayment.Columns.Add("merchantId" );
	        m_listBankPayment.Columns.Add("batchNo" );
	        m_listBankPayment.Columns.Add("stan" );
	        m_listBankPayment.Columns.Add("authorizeCode" );
	        m_listBankPayment.Columns.Add("transFlag" );
	        m_listBankPayment.Columns.Add("Error" );
	        m_listBankPayment.Columns.Add("Error" );
	        m_listBankPayment.Columns.Add("Card PAN" );
	        m_listBankPayment.Columns.Add("Card Holder Name" );
	        m_listBankPayment.Columns.Add("Card Input Type" );
        }

        private void PaymentForm_Load(object sender, EventArgs e)
        {

        }

        private void m_listPayment_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
            selectedIndex = m_listPayment.Items.IndexOf(m_listPayment.SelectedItems[0]);
            Close();
        }
    }
}
