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
    public partial class CurrencyProfileForm : Form
    {
        public uint retcode;
        private ST_EXCHANGE_PROFILE[] stExchangeProfiles;
        private ST_EXCHANGE_PROFILE[] stExchangeProfilesTemp;

        private int newItem = -1;

        public CurrencyProfileForm()
        {
            InitializeComponent();
            SetCurrencyProfiles();
        }

        public void SetCurrencyProfiles()
        {
            stExchangeProfiles = new ST_EXCHANGE_PROFILE[4];
            stExchangeProfilesTemp = new ST_EXCHANGE_PROFILE[4];

            for (int i = 0; i < 4; i++)
                stExchangeProfiles[i] = new ST_EXCHANGE_PROFILE();

            retcode = Json_GMPSmartDLL.FP3_GetCurrencyProfile(GMPForm.CurrentInterface, ref stExchangeProfilesTemp);
            if (retcode != 0)
            {
                ErrorClass.DisplayErrorMessage(retcode);
                return;
            }

            for (int i = 0; i < stExchangeProfilesTemp.Length; i++)
            {
                ST_EXCHANGE_PROFILE profile = stExchangeProfilesTemp[i];
                stExchangeProfiles[i].ProfileName = profile.ProfileName;
                stExchangeProfiles[i].NumberOfCurrency = profile.NumberOfCurrency;

                for (int t = 0; t < profile.ExchangeRecords.Length; t++)
                {
                    stExchangeProfiles[i].ExchangeRecords[t] = profile.ExchangeRecords[t];
                }
            }

            if (retcode != 0)
            {
                ErrorClass.DisplayErrorMessage(retcode);
                return;
            } 
            foreach (var item in stExchangeProfiles)
            {
                if(!string.IsNullOrWhiteSpace(item.ProfileName))
                    comboBoxCurrencyProfile.Items.Add(item.ProfileName);  
            }

            for (int i = 0; i < stExchangeProfiles[0].NumberOfCurrency; i++)
            {
                ST_EXCHANGE currency = stExchangeProfiles[0].ExchangeRecords[i];
                object[] data = new object[] {currency.code, currency.sign,
                        currency.prefix, (char)currency.tousandSeperator, (char)currency.centSeperator, (int)currency.numberOfCentDigit, (long)currency.rate};
                dataGridViewCurrencyProfile.Rows.Add(data);
            }

            comboBoxCurrencyProfile.SelectedIndex = 0;
           
        }

        private void comboBoxCurrencyProfile_SelectedIndexChanged(object sender, EventArgs e)
        {
            dataGridViewCurrencyProfile.Rows.Clear();
            int index = comboBoxCurrencyProfile.SelectedIndex;

            for (int i = 0; i < stExchangeProfiles[index].NumberOfCurrency; i++)
            {
                ST_EXCHANGE currency = stExchangeProfiles[index].ExchangeRecords[i];
                object[] data = new object[] {currency.code, currency.sign,
                        currency.prefix, (char)currency.tousandSeperator, (char)currency.centSeperator, (int)currency.numberOfCentDigit, (long)currency.rate};
                dataGridViewCurrencyProfile.Rows.Add(data);
            } 

            if (index == 0)
                dataGridViewCurrencyProfile.Enabled = false;
            else
                dataGridViewCurrencyProfile.Enabled = true;
        }

        private void dataGridViewCurrencyProfile_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            int index = comboBoxCurrencyProfile.SelectedIndex;
            try
            {
                switch (e.ColumnIndex)
                {
                    case 0:
                        stExchangeProfiles[index].ExchangeRecords[e.RowIndex].code = Convert.ToUInt16(dataGridViewCurrencyProfile.Rows[e.RowIndex].Cells[e.ColumnIndex].Value);
                        break;
                    case 1:
                        stExchangeProfiles[index].ExchangeRecords[e.RowIndex].sign = dataGridViewCurrencyProfile.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString();
                        break;
                    case 2:
                        stExchangeProfiles[index].ExchangeRecords[e.RowIndex].prefix = dataGridViewCurrencyProfile.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString();
                        break;
                    case 3:
                        stExchangeProfiles[index].ExchangeRecords[e.RowIndex].tousandSeperator = (byte)Convert.ToChar(dataGridViewCurrencyProfile.Rows[e.RowIndex].Cells[e.ColumnIndex].Value);
                        break;
                    case 4:
                        stExchangeProfiles[index].ExchangeRecords[e.RowIndex].centSeperator = (byte)Convert.ToChar(dataGridViewCurrencyProfile.Rows[e.RowIndex].Cells[e.ColumnIndex].Value);
                        break;
                    case 5:
                        stExchangeProfiles[index].ExchangeRecords[e.RowIndex].numberOfCentDigit = (byte)Convert.ToInt32(dataGridViewCurrencyProfile.Rows[e.RowIndex].Cells[e.ColumnIndex].Value);
                        break;
                    case 6:
                        stExchangeProfiles[index].ExchangeRecords[e.RowIndex].rate = Convert.ToUInt64(dataGridViewCurrencyProfile.Rows[e.RowIndex].Cells[e.ColumnIndex].Value);
                        break;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("ERROR : " + ex.Message);
            }
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            byte index = (byte)this.comboBoxCurrencyProfile.SelectedIndex;
            ST_EXCHANGE_PROFILE [] ExchangeProfiles = new ST_EXCHANGE_PROFILE[4];
            for (int i = 0; i < 4; i++)
            {
                ExchangeProfiles[i] = new ST_EXCHANGE_PROFILE();
            }

            ExchangeProfiles[0] = stExchangeProfiles[index];

            string password = "0000";

            if (newItem != -1)
            {
                // process type = 2 -> add
                retcode = Json_GMPSmartDLL.FP3_SetCurrencyProfile(GMPForm.CurrentInterface, password, (byte)newItem, 2, ExchangeProfiles);  
            }
            else
            {
                // process type = 1 -> update
                retcode = Json_GMPSmartDLL.FP3_SetCurrencyProfile(GMPForm.CurrentInterface, password, index, 1, ExchangeProfiles);
            }

            /* if save is successfull, reset the newItem.*/
            if (retcode == 0) newItem = -1;
            ErrorClass.DisplayErrorMessage(retcode);
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            int index = this.comboBoxCurrencyProfile.SelectedIndex;
            if (index == 0)
            {
                MessageBox.Show("TSM can't be deleted!");
                return;
            }
            string password = "0000";
            retcode = Json_GMPSmartDLL.FP3_SetCurrencyProfile(GMPForm.CurrentInterface, password, (byte)index, 3, stExchangeProfiles);
            comboBoxCurrencyProfile.Items.RemoveAt(index);
            RefreshTable(0);
            ErrorClass.DisplayErrorMessage(retcode);
        }

        private void buttonNew_Click(object sender, EventArgs e)
        {

            if (newItem != -1)
            {
                MessageBox.Show("Save the changes first!");
                return;
            }    

            GetInputForm form = new GetInputForm("Profile Name", "Name", 0);
            DialogResult result = form.ShowDialog();
            if (result == DialogResult.OK)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (string.IsNullOrWhiteSpace(stExchangeProfiles[i].ProfileName))
                    {
                        stExchangeProfiles[i].ProfileName = form.textBox1.Text;
                        comboBoxCurrencyProfile.Items.Add(stExchangeProfiles[i].ProfileName);
                        newItem = i;
                        RefreshTable(comboBoxCurrencyProfile.Items.Count - 1);
                        return;
                    }
                }

                MessageBox.Show("Max number of profile!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void RefreshTable(int index)
        {           
            comboBoxCurrencyProfile.SelectedIndex = index;
        }

        private void buttonRowAdd_Click(object sender, EventArgs e)
        {
            int index = comboBoxCurrencyProfile.SelectedIndex;
            if (index == 0)
                return; // TSM

            dataGridViewCurrencyProfile.Rows.Add();
            stExchangeProfiles[index].NumberOfCurrency++;
        }

        private void dataGridViewCurrencyProfile_UserDeletedRow(object sender, DataGridViewRowEventArgs e)
        {
            int index = comboBoxCurrencyProfile.SelectedIndex;
            stExchangeProfiles[index].NumberOfCurrency--;
        }
    }
}
