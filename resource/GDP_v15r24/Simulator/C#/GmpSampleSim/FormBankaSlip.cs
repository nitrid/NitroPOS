using GmpSampleSim;
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
    public partial class SlipForm : Form
    {
        GMPForm parent;
        uint retcode = 0;
        int slipLen = 0;

        public SlipForm(GMPForm parent)
        {
            this.parent = parent;
            InitializeComponent();

            textBoxFontSmall.Text = "45";
            textBoxFontMedium.Text = "32";
            textBoxFontLarge.Text = "26";

            textBoxHuge.Text = "20";
            textBoxMedium.Text = "13";
            textBoxSmall.Text = "9";

            ST_TICKET ticket = new ST_TICKET();
            retcode = Json_GMPSmartDLL.FP3_GetTicket(GMPForm.CurrentInterface, 
                                this.parent.ACTIVE_TRX_HANDLE, 
                                ref ticket, 
                                Defines.TIMEOUT_DEFAULT
                                );

            if (retcode != Defines.TRAN_RESULT_OK)
            {
                MessageBox.Show("Ticket alınırken hata oluştu", "Hata", MessageBoxButtons.OK);
                
                return;
            }

            SetOdemeIndexes( GetOdemeItems(ticket) );
        }

        public uint GetRetcode()
        {
            return retcode;
        }

        public void SetOdemeIndexes(string [] items)
        {
            if (items.Count() == 0) return;

            comboBoxOdemeIndex.Items.AddRange(items);
            comboBoxOdemeIndex.SelectedIndex = 0;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            IList<SlipLine>  slipList = GetSlipLines();
            richTextBoxSlip.Text = "";

            System.Drawing.Font currentFont = richTextBoxSlip.Font;
            FontStyle fontStyle;
            float fontSize = 10;

            foreach (var item in slipList)
            {
                switch((int)item.Format_P)
                {
                    case 0x01:
                        fontStyle = FontStyle.Bold;
                        break;
                    default:
                        fontStyle = currentFont.Style;
                        break;
                }
                try
                { 
                    switch ((int)item.Format_F)
                    {
                        case 0x00:  // medium
                            fontSize = Convert.ToInt32( textBoxMedium.Text ); //14;
                            break;
                        case 0x01:  // small
                            fontSize = Convert.ToInt32(textBoxSmall.Text); //12;
                            break;
                        case 0x02:  // Huge
                            fontSize = Convert.ToInt32(textBoxHuge.Text); //16;
                            break;
                        default:
                            fontSize = currentFont.Size;
                            break;
                    }
                }
                catch(Exception ex)
                {
                    MessageBox.Show("Lütfen tam sayı değerleri giriniz!" + ex.Message, "Hata");
                    return;
                }
                richTextBoxSlip.SelectionFont = new Font(
                                            "Courier New",
                                            fontSize,
                                            fontStyle
                                            );
                richTextBoxSlip.AppendText( item.Line + "\n" );
            }
        }

        private IList<SlipLine> GetSlipLines()
        {
            byte[] slip = new byte[4 * 1024];
            IList<SlipLine> slipList = new List<SlipLine>();
            try
                {
                int odemeIndex = this.comboBoxOdemeIndex.SelectedIndex;

                uint fontSize1 = Convert.ToUInt32(textBoxFontSmall.Text) 
                                 + Convert.ToUInt32(textBoxFontMedium.Text) * 100 
                                 + Convert.ToUInt32(textBoxFontLarge.Text) * 10000;

                retcode = GMPSmartDLL.FP3_GetMerchantSlip(GMPForm.CurrentInterface,
                                                                        parent.ACTIVE_TRX_HANDLE,
                                                                        odemeIndex,
                                                                        fontSize1,
                                                                        slip,
                                                                        ref slipLen,
                                                                        Defines.TIMEOUT_DEFAULT
                                                                        );
                if (retcode != 0)
                {
                    return slipList;
                }

                int index = 0;
                for (int i = 0; i < slipLen; i++)
                {
                    if (slip[i] == 255)
                    {
                        IList<byte> lineBytes = new List<byte>();
                        SlipLine line = new SlipLine();
                        line.Format_T = slip[index];
                        line.Format_F = slip[index + 1];
                        line.Format_P = slip[index + 2];
                        for (int k = index + 3; k < i; k++) // ilk üç byte format
                        {
                            lineBytes.Add(slip[k]);
                        }
                        line.Line = GMP_Tools.SetEncoding(lineBytes.ToArray(), 0, lineBytes.Count);

                        slipList.Add(line);
                        index = i + 1; // 0xFF ayraci alinmasin 
                    }
                }

                return slipList;
            }
            catch(Exception ex)
            {
                MessageBox.Show("Yalnızca tam sayı ve fazla büyük olmayan değerler giriniz! " + ex.Message, "Hata");
                return slipList;
            }
        }
        private string[] GetOdemeItems(ST_TICKET ticket)
        {
            IList<string> items = new List<string>();
            foreach (var payment in ticket.stPayment)
            {
                if (payment == null) break;
                items.Add(payment.payAmount.ToString() + " - " + payment.stBankPayment.bankName);
            }
            return items.ToArray<string>();
        }

      
    }
}
