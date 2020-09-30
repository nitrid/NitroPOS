using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace GmpSampleSim
{
    public partial class GetInputForm : Form
    {
        public GetInputForm()
        {
            InitializeComponent();
        }


        public GetInputForm(string str, string str2, int type)
        {
            InitializeComponent();

            label1.Text = str;
            textBox1.Text = str2;
        }

        private void GetInputForm_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }
    }
}
