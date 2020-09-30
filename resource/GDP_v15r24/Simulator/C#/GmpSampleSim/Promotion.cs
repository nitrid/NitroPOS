using GmpSampleSim.Models;
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
    public partial class Promotion : Form
    {

        public Promotion()
        {
            InitializeComponent();
        }

        private void m_btnAddPromotion_Click(object sender, EventArgs e)
        {
            PromotionModel promotion = PromotionModel.Instance;
            promotion.Amount = Convert.ToUInt32(m_txtPromotionAmount.Text);
            promotion.Message = m_txtPromotionText.Text;
            promotion.Type = PromotionType.DISCOUNT;

            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }
    }
}
