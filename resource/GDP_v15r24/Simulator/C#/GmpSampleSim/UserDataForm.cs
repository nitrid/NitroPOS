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
    public partial class UserDataForm : Form
    {
        private GMPForm parent;
        uint RetCode = Defines.TRAN_RESULT_OK;

        public UserDataForm(GMPForm parent)
        {
            InitializeComponent();
            this.parent = parent;
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            string data = textBoxUserData.Text.Trim();
            byte[] userData = Encoding.ASCII.GetBytes(data);
            if (parent.m_rbBatchMode.Checked)
            {
                byte[] buffer = new byte[1024];
                int bufferLen = 0;

                // start
                bufferLen = (int)GMPSmartDLL.prepare_SendUserData(buffer, buffer.Length, userData, userData.Length);
                parent.AddIntoCommandBatch("prepare_SendUserData", Defines.GMP3_FISCAL_PRINTER_MODE_REQ, buffer, bufferLen);

            }else
            {
                RetCode = GMPSmartDLL.FP3_SendUserData(GMPForm.CurrentInterface,
                                       this.parent.ACTIVE_TRX_HANDLE,
                                       userData,
                                       userData.Length,
                                       Defines.TIMEOUT_DEFAULT
                                       );
                parent.HandleErrorCode(RetCode);
            }
        }

        private void buttonAl_Click(object sender, EventArgs e)
        {
            textBoxUserData.Text = "";
            byte[] userData = new byte[64];
            int length = 0;
            RetCode = GMPSmartDLL.FP3_GetUserData(GMPForm.CurrentInterface,
                                        this.parent.ACTIVE_TRX_HANDLE,
                                        userData,
                                        ref length,
                                        Defines.TIMEOUT_DEFAULT
                                        );

            textBoxUserData.Text = Encoding.ASCII.GetString(userData);
            parent.HandleErrorCode(RetCode);
        }
    }
}
