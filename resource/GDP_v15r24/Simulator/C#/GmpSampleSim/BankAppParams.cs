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
    public partial class BankAppParams : Form
    {
        public bool missingInput { get; set; }

        public BankAppParams()
        {
            InitializeComponent();
        }

        public BankAppParams(bool _true)
        {
            InitializeComponent();
            BankAppParams_Init(_true);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        public void BankAppParams_Init(bool _true) {
            if (_true == true)
            {
                BankAppParams _missingInput = new BankAppParams();

                if (_m_chcAskForMissingInputs.Checked == true)
                    _missingInput.missingInput = false;
            }   
        }

        private void _m_chcAskForMissingInputs_CheckedChanged(object sender, EventArgs e)
        { 

            CheckBox chc = (CheckBox)sender;
            missingInput = chc.Checked;
        
        }

        public class BankParams
        {

            public Boolean missingInput;

            public BankParams(bool _missingInput){

                missingInput = _missingInput;
                
            }
        }
    }
}
