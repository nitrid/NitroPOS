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
    public partial class DrawerStateForm : Form
    {
        private GMPForm parent;
        uint RetCode = Defines.TRAN_RESULT_OK;

        public DrawerStateForm(GMPForm parent)
        {
            InitializeComponent();
            this.parent = parent;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            int state;
            if (radioButtonActive.Checked)
                state = 1;
            else
                state = 0;

            RetCode = GMPSmartDLL.FP3_SetDrawerState(GMPForm.CurrentInterface,
                                       state,
                                       Defines.TIMEOUT_DEFAULT
                                       );
            parent.HandleErrorCode(RetCode);
            this.Close();
        }
    }
}
