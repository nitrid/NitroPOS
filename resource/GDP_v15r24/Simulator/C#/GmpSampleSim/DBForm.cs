using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace GmpSampleSim
{
    public partial class DBForm : Form
    {

        byte[] TranDbName = new byte[100];
        short len = 0;

        public DBForm()
        {
            InitializeComponent();
        }

        private void DBForm_Load(object sender, EventArgs e)
        {
            ushort ZNo = 0;
            ushort FNo = 0;
            ushort EKUNo = 0;

            UInt32 retcode = GMPSmartDLL.FP3_GetCurrentFiscalCounters(GMPForm.CurrentInterface, ref ZNo, ref FNo, ref EKUNo);
            if (retcode == Defines.TRAN_RESULT_OK)
            {
                ListViewItem item1 = new ListViewItem("" + ZNo);
                item1.SubItems.Add("" + FNo);
                item1.SubItems.Add("" + EKUNo);
                m_list_Z.Items.Add(item1);

                for (int k = ZNo - 1; k > 0; k--)
                {
                    ListViewItem item2 = new ListViewItem("" + k);
                    m_list_Z.Items.Add(item2);
                }
            }
        }

        private void m_list_Z_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_list_Z.SelectedItems.Count == 0)
                return;
            int ZNo = Convert.ToInt32(m_list_Z.SelectedItems[0].Text);


            if (GMPSmartDLL.FP3_GetTlvData(GMPForm.CurrentInterface, Defines.GMP_EXT_DEVICE_TAG_TRAN_DB_NAME, TranDbName, (short)TranDbName.Length, ref len) == Defines.TRAN_RESULT_OK)
            {
                string command = "SELECT * FROM TBL_TRANSACTION WHERE ZNO=" + ZNo + ";";

                FillListControlFromDB(GMP_Tools.SetEncoding(TranDbName, 0, len), m_listTransaction, command);
            }

        }

        void FillListControlFromDB(string dbName, ListView plistCtrl, string swlWord)
        {
            try
            {
                UInt32 retcode;
                ushort numberOfColumns = 24;
                ST_DATABASE_RESULT stDatabaseResult = new ST_DATABASE_RESULT();
                retcode = GMPSmartDLL.FP3_Database_Open(GMPForm.CurrentInterface, dbName);
                if ((retcode != Defines.TRAN_RESULT_OK))
                    goto Exit;

                retcode = GMPSmartDLL.FP3_Database_Query(GMPForm.CurrentInterface, swlWord, ref numberOfColumns);
                if (retcode != Defines.TRAN_RESULT_OK)
                    goto Exit;

                retcode = Json_GMPSmartDLL.FP3_Database_QueryColomnCaptions(GMPForm.CurrentInterface, ref stDatabaseResult);

                if (retcode == Defines.TRAN_RESULT_OK)
                {
                    plistCtrl.Items.Clear();

                    numberOfColumns = (ushort)stDatabaseResult.pstCaptionArray[0].numberOfColomns;
                    for (int i = 0; i < numberOfColumns; i++)
                    {

                        plistCtrl.Columns.Add(stDatabaseResult.pstCaptionArray[0].pstColomnArray[i].data);
                        //                //CString cs;
                        //                //cs = CString();
                        //                //plistCtrl->InsertColumn(i, cs );
                        //                //plistCtrl->SetColumnWidth(i, cs.GetLength() * 10 );
                    }
                    //Json_GMPSmartDLL.Database_FreeStructure(ref stDatabaseResult);
                    stDatabaseResult = new ST_DATABASE_RESULT();
                    do
                    {
                        retcode = Json_GMPSmartDLL.FP3_Database_QueryReadLine(GMPForm.CurrentInterface, 50, numberOfColumns, ref stDatabaseResult);
                        if ((retcode != Defines.SQLITE_ROW) && (retcode != Defines.SQLITE_DONE))
                            break;

                        for (int line = 0; line < stDatabaseResult.numberOfLines; line++)
                        {
                            ListViewItem item1 = new ListViewItem(stDatabaseResult.pstLineArray[line].pstColomnArray[0].data);

                            for (int i = 1; i < stDatabaseResult.pstLineArray[line].numberOfColomns; i++)
                            {
                                item1.SubItems.Add(stDatabaseResult.pstLineArray[line].pstColomnArray[i].data);
                            }

                            plistCtrl.Items.Add(item1);
                        }

                    } while (retcode == Defines.SQLITE_ROW);
                }
                stDatabaseResult = new ST_DATABASE_RESULT();
                //Json_GMPSmartDLL.Database_FreeStructure(ref stDatabaseResult);
                GMPSmartDLL.FP3_Database_QueryFinish(GMPForm.CurrentInterface);

            Exit:
                if (GMPSmartDLL.FP3_Database_GetHandle(GMPForm.CurrentInterface) != 0)
                    GMPSmartDLL.FP3_Database_Close(GMPForm.CurrentInterface);
                //ErrorClass.DisplayErrorMessage(retcode);

            }
            catch (Exception)
            {
                GMPSmartDLL.FP3_Database_Close(GMPForm.CurrentInterface);
                throw;
            }

        }

        private void m_listTransaction_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_listTransaction.SelectedItems.Count == 0)
                return;
            string ZNo = "";
            string FNo = "";

            ZNo = m_listTransaction.SelectedItems[0].SubItems[3].Text;
            FNo = m_listTransaction.SelectedItems[0].SubItems[4].Text;

            if (GMP_Tools.SetEncoding(TranDbName, 0, len).Length == 0)
                GMPSmartDLL.FP3_GetTlvData(GMPForm.CurrentInterface, Defines.GMP_EXT_DEVICE_TAG_TRAN_DB_NAME, TranDbName, (short)TranDbName.Length, ref len);

            if (ZNo.Length != 0 && FNo.Length != 0)
            {
                string swlWord = String.Format("SELECT * FROM TBL_ITEM WHERE ZNO={0} AND FNO={1};", ZNo, FNo);
                FillListControlFromDB(GMP_Tools.SetEncoding(TranDbName, 0, len), m_listItems, swlWord);
            }
        }

        private void m_listItems_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_listItems.SelectedItems.Count == 0)
                return;

            string ItemDetailIndex = m_listItems.SelectedItems[0].SubItems[6].Text;


            if (GMP_Tools.SetEncoding(TranDbName, 0, len).Length == 0)
                GMPSmartDLL.FP3_GetTlvData(GMPForm.CurrentInterface, Defines.GMP_EXT_DEVICE_TAG_TRAN_DB_NAME, TranDbName, (short)TranDbName.Length, ref len);

            if (ItemDetailIndex.Length != 0 )
            {
                string swlWord = String.Format("SELECT * FROM TBL_ITEM_DETAIL WHERE IDX={0}", ItemDetailIndex);
                FillListControlFromDB(GMP_Tools.SetEncoding(TranDbName, 0, len), m_lstItemDetails, swlWord);
            }
        }
    }
}
