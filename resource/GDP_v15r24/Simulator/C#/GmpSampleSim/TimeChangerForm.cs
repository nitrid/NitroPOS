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
    public partial class TimeChangerForm : Form
    {
        string date;
        string time;

        public TimeChangerForm()
        {
            InitializeComponent();
        }

        public void SetTime(string date, string time)
        {
            textBoxDateChanger.Text = date;
            textBoxTimeChanger.Text = time;
        }

        private void buttonChangeTime_Click(object sender, EventArgs e)
        {
            date = textBoxDateChanger.Text;
            time = textBoxTimeChanger.Text;
           
            this.DialogResult = DialogResult.OK;
            this.Visible = false;
        }

        public string getTime() { return time; }
        public string getDate() { return date; }

    }
}
