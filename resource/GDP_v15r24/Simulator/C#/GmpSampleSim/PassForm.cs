using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace GmpSampleSim
{
    public partial class PassForm : Form
    {
        public PassForm()
        {
            InitializeComponent();
        }

        public string m_PASS = "";

        private void m_btnSendPass_Click(object sender, EventArgs e)
        {
            m_PASS = m_txtGetPass.Text;
            this.Close();

            this.DialogResult = System.Windows.Forms.DialogResult.OK;            
        }
    }
}
