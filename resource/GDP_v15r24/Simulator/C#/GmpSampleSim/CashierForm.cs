using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace GmpSampleSim
{
    public partial class CashierForm : Form
    {
        public static GMPForm cashierCls;

        public CashierForm()
        {
            InitializeComponent();
        }

        private void m_btnCashierLogOut_Click(object sender, EventArgs e)
        {
            int retcode = GMPSmartDLL.FP3_FunctionCashierLogout(GMPForm.CurrentInterface);

        }

    	int numberOfTotalCashiers;
	    short activeCashier;
        private void CashierForm_Load(object sender, EventArgs e)
        {
            RefreshCashierInfo();
        }

        private void RefreshCashierInfo()
        {
            GMPForm gf = new GMPForm();
            m_ListCashiers.Items.Clear();
            UInt32 retcode;
            int numberOfTotalRecordsReceived = 0;
            ST_CASHIER[] stCashierTable = new ST_CASHIER[10];


            retcode = Json_GMPSmartDLL.FP3_GetCashierTable(GMPForm.CurrentInterface, ref numberOfTotalCashiers, ref numberOfTotalRecordsReceived, ref stCashierTable, 10, ref activeCashier);

            if (retcode != 0)
            {
                gf.HandleErrorCode(retcode);
                return;
            }
            gf.HandleErrorCode(retcode);

            if (retcode == Defines.TRAN_RESULT_OK)
            {
                gf.m_echoTestMenuItem_Click(null, null);
            }

            m_activeCashierIndex.Text = activeCashier.ToString();
            if (activeCashier < numberOfTotalCashiers)
                m_activeCashierName.Text = stCashierTable[activeCashier].name;

            for (int i = 0; i < numberOfTotalCashiers; i++)
            {

                ListViewItem item1 = new ListViewItem(stCashierTable[i].index.ToString());
                item1.SubItems.Add(stCashierTable[i].name);
                item1.SubItems.Add(stCashierTable[i].flags.ToString("X8"));

                m_ListCashiers.Items.Add(item1);
            }
        }

        private void m_ListCashiers_SelectedIndexChanged(object sender, EventArgs e)
        {
            PassForm pf = new PassForm();
            DialogResult dr = pf.ShowDialog();

            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                if (m_ListCashiers.SelectedItems.Count > 0)
                {
                    GMPForm gf = new GMPForm();
                    UInt32 retcode = GMPSmartDLL.FP3_FunctionCashierLogin(GMPForm.CurrentInterface, m_ListCashiers.Items.IndexOf(m_ListCashiers.SelectedItems[0]), pf.m_PASS);
                    gf.HandleErrorCode(retcode);
                }
            }
        }

        private void m_btnAddCashier_Click(object sender, EventArgs e)
        {
            PassForm pf = new PassForm();
            DialogResult dr = pf.ShowDialog();

            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                GMPForm gf = new GMPForm();
                UInt32 retcode = GMPSmartDLL.FP3_FunctionAddCashier(GMPForm.CurrentInterface, Convert.ToUInt16(m_txtCashierIndex.Text), m_txtCashierName.Text, m_txtCashierPassword.Text, pf.m_PASS);
                gf.HandleErrorCode(retcode);

                RefreshCashierInfo();
            }
        }
    }
}

