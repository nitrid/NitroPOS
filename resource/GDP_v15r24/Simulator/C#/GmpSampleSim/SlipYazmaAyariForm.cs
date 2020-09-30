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
    public partial class SlipYazmaAyariForm : Form
    {
        private GMPForm parent;

        public SlipYazmaAyariForm(GMPForm parent)
        {
            this.parent = parent;
            InitializeComponent();

            ulong activeFlags = GetSlipWriteOption();
            
            if ((activeFlags & Defines.GMP3_OPTION_DONT_PRINT_MERCHANT_SLIPS) == 0) // flag is unset
                radioButtonPassive.Checked = true;
            else
                radioButtonActive.Checked = true;
        }

        private ulong GetSlipWriteOption()
        {
            UInt64 activeFlags = 0;
            uint retcode = Defines.TRAN_RESULT_OK;

            retcode = GMPSmartDLL.FP3_OptionFlags(GMPForm.CurrentInterface,
                                        this.parent.ACTIVE_TRX_HANDLE, 
                                        ref activeFlags,
                                        0, //Defines.GMP3_OPTION_DONT_PRINT_MERCHANT_SLIPS, 
                                        0, 
                                        Defines.TIMEOUT_DEFAULT
                                        );
            if(retcode != Defines.TRAN_RESULT_OK)
            {
                MessageBox.Show("Pairing yapılması gerekiyor!");
            }
            return activeFlags;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            UInt64 activeFlags = 0;
            uint retcode = Defines.TRAN_RESULT_OK;

            if (radioButtonPassive.Checked)
            {
                retcode = GMPSmartDLL.FP3_OptionFlags(GMPForm.CurrentInterface,
                                       this.parent.ACTIVE_TRX_HANDLE,
                                       ref activeFlags,
                                       Defines.GMP3_OPTION_DONT_PRINT_MERCHANT_SLIPS,
                                       0,
                                       Defines.TIMEOUT_DEFAULT
                                       );
            }
            else
            {
                retcode = GMPSmartDLL.FP3_OptionFlags(GMPForm.CurrentInterface,
                                      this.parent.ACTIVE_TRX_HANDLE,
                                      ref activeFlags,
                                      0,
                                      Defines.GMP3_OPTION_DONT_PRINT_MERCHANT_SLIPS,
                                      Defines.TIMEOUT_DEFAULT
                                      );
            }

            if (retcode != Defines.TRAN_RESULT_OK)
            {
                MessageBox.Show("Pairing yapılması gerekiyor!");
            }

            this.Dispose();
        }
    }
}
