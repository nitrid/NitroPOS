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
    public partial class FormProfilesSelection : Form
    {
        RadioButton selectedRadioButton;

        public FormProfilesSelection()
        {
            InitializeComponent();
        }

        public void SetProfileNames(IList<string> profiles)
        {
            int counter = 0;
            foreach (var item in profiles)
            {
                RadioButton r = new RadioButton();
                r.Size = new Size(200, 30);
                r.Text = item;
                r.TabIndex = counter;
                counter++;
                r.CheckedChanged += new EventHandler(radioButton_CheckedChanged);
                this.flowLayoutPanelForProfiles.Controls.Add(r);
            }
        }

        private void radioButton_CheckedChanged(object sender, EventArgs e)
        {
            selectedRadioButton = (RadioButton)sender;
        }

        private void buttonProfileSelection_Click(object sender, EventArgs e)
        {
            ST_TICKET stTicket = new ST_TICKET();
            uint RetCode = Json_GMPSmartDLL.FP3_GetTicket(GMPForm.CurrentInterface, GMPForm.ActiveTransactionHandle, ref stTicket, Defines.TIMEOUT_DEFAULT);
            if (RetCode != 0)
            {
                ErrorClass.DisplayErrorMessage(RetCode);
                return;
            }
            RetCode = Json_GMPSmartDLL.FP3_SetCurrencyProfileIndex(GMPForm.CurrentInterface,
                GMPForm.ActiveTransactionHandle, (byte)selectedRadioButton.TabIndex, stTicket, Defines.TIMEOUT_DEFAULT);

            ErrorClass.DisplayErrorMessage(RetCode);
            this.Dispose();
        }
    }
}
