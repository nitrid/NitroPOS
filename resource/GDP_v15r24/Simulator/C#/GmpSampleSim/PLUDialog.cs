using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

namespace GmpSampleSim
{
    public partial class PLUDialog : Form
    {
        public PLUDialog()
        {
            InitializeComponent();
        }

        private void PLUDialog_Load(object sender, EventArgs e)
        {
            textBox1.Text = Directory.GetCurrentDirectory();

            UpdateHostDbFiles();
        }

        uint m_PluDbSize;
        void RefreshEcrPluDbFileName()
        {
            GMPSmartDLL.FP3_Database_Close(GMPForm.CurrentInterface);
            UInt32 retcode = Defines.TRAN_RESULT_OK;
            string cs = "";
            string csPluDbName = "";
            short PluDbType = 0;
            uint PluDbGrupsLastModified = 0;
            uint PluDbItemsLastModified = 0;
            byte[] arrDbName = new byte[100];
            m_PluDbSize = 0;

            retcode = GMPSmartDLL.FP3_GetPluDatabaseInfo(GMPForm.CurrentInterface, arrDbName, ref PluDbType, ref m_PluDbSize, ref PluDbGrupsLastModified, ref PluDbItemsLastModified);
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                GMPForm gf = new GMPForm();
                gf.HandleErrorCode(retcode);
                return;
            }
            m_PluDbName = csPluDbName = GMP_Tools.SetEncoding(arrDbName).Substring(0, GMP_Tools.SetEncoding(arrDbName).IndexOf('\0'));
            cs = String.Format("{0} ({1} bytes) / {2} / {3}", csPluDbName, m_PluDbSize, PluDbGrupsLastModified, PluDbItemsLastModified);

            m_listEcrPluFileName.Items.Clear();
            m_listEcrPluFileName.Items.Add(cs);
        }


        int UpdateHostDbFiles()
        {
            m_lstDBFiles.Items.Clear();
            string[] filePaths = Directory.GetFiles(textBox1.Text, "*.d");

            if (filePaths.Length != 0)
            {
                for (int i = 0; i < filePaths.Length; i++)
                {
                    m_lstDBFiles.Items.Add(filePaths[i]);
                }
            }
            else
            {
                MessageBox.Show("File Not Found...");
            }
            return 0;
        }


        private void textBox1_TextChanged(object sender, EventArgs e)
        {

            try
            {
                string[] filePaths = Directory.GetFiles(textBox1.Text, "*.d");
                //string[] filePaths = Directory.GetFiles(@"C:\Users\ycelik\Desktop\MyDLL\Release\x86");
                m_lstDBFiles.Items.Clear();
                for (int i = 0; i < filePaths.Length; i++)
                {
                    m_lstDBFiles.Items.Add(filePaths[i]);
                }
            }
            catch (Exception)
            {
                m_lstDBFiles.Items.Clear();
            }


        }

        private void m_lstDBFiles_SelectedIndexChanged(object sender, EventArgs e)
        {
            string FileName = m_lstDBFiles.SelectedItem.ToString().Substring(m_lstDBFiles.SelectedItem.ToString().LastIndexOf('\\') + 1);
            UpdateHostPluGrups(FileName, m_listHostPluGrups, 0);
        }

        int UpdateHostPluGrups(string FileName, DataGridView plist, int pluGrupParent)
        {
            //string sqlWord = String.Format("SELECT ROWID,* FROM TBL_PLU_GRUP WHERE PLU_GRUP_PARENT={0};", pluGrupParent);
            string sqlWord = String.Format("SELECT * FROM TBL_PLU_GRUP WHERE PLU_GRUP_PARENT={0};", pluGrupParent);
            return FillListControlFromHostDB(FileName, plist, sqlWord);
        }

        int UpdateHostPluItems(string FileName, DataGridView plist, int pluGrupParent)
        {

            //string sqlWord = String.Format("SELECT ROWID,* FROM TBL_PLU WHERE PLU_GRUP_PARENT={0};", pluGrupParent);
            string sqlWord = String.Format("SELECT * FROM TBL_PLU WHERE PLU_GRUP_PARENT={0};", pluGrupParent);
            return FillListControlFromHostDB(FileName, plist, sqlWord);
        }

        int FillListControlFromHostDB(string dbName, DataGridView plistCtrl, string swlWord)
        {

            IntPtr db = IntPtr.Zero;
            IntPtr tail = IntPtr.Zero;
            int retcode;
            IntPtr psqlite3_stmt = IntPtr.Zero;
            int dbNumberOfTotalColumns;

            plistCtrl.DataSource = null;
            plistCtrl.Rows.Clear();
            plistCtrl.Refresh();

            int nColumnCount = plistCtrl.Columns.Count;
            // Delete all of the columns. 

            for (int i = nColumnCount - 1; i >= 0; i--)
                plistCtrl.Columns.Remove(plistCtrl.Columns[i]);

            retcode = GMPSmartDLL.sqlite3_open(dbName, out db);
            if ((retcode != Defines.SQLITE_OK))
                goto Exit;

            retcode = GMPSmartDLL.sqlite3_prepare_v2(db, swlWord, -1, out psqlite3_stmt, tail);
            if (retcode != Defines.SQLITE_OK)
                goto Exit;

            dbNumberOfTotalColumns = GMPSmartDLL.sqlite3_column_count(psqlite3_stmt);

            DataTable table = new DataTable();
            for (int i = 0; i < dbNumberOfTotalColumns; i++)
            {
                string cs = "";
                IntPtr ptr = GMPSmartDLL.sqlite3_column_origin_name(psqlite3_stmt, i);
                cs = Marshal.PtrToStringAnsi(ptr);
                //plistCtrl.Columns.Add(cs, cs.Length * 8 );
                table.Columns.Add(cs);
            }
            plistCtrl.DataSource = table;


            do
            {
                retcode = GMPSmartDLL.sqlite3_step(psqlite3_stmt);
                if (retcode != Defines.SQLITE_ROW)
                    break;

                int nItem = 0;

                //ListViewItem item1 = new ListViewItem();

                DataRow workRow = table.NewRow();


                for (int i = 0; i < dbNumberOfTotalColumns; i++)
                {
                    string data = "";
                    switch (GMPSmartDLL.sqlite3_column_type(psqlite3_stmt, i))
                    {
                        case Defines.SQLITE_FLOAT:
                        case Defines.SQLITE_INTEGER:
                            data = String.Format("{0}", GMPSmartDLL.sqlite3_column_int(psqlite3_stmt, i));
                            break;
                        case Defines.SQLITE_TEXT: // string
                            IntPtr ptr = GMPSmartDLL.sqlite3_column_text(psqlite3_stmt, i);
                            data = String.Format("{0}", Marshal.PtrToStringAnsi(ptr));
                            break;
                        case Defines.SQLITE_NULL: // byte
                        case Defines.SQLITE_BLOB: // blob
                        default:
                            data = "";
                            break;
                    }
                    workRow[i] = data;

                }
                table.Rows.Add(workRow);

                //plistCtrl.Items.Add(item1);
                nItem++;
            } while (retcode == Defines.SQLITE_ROW);

            if (retcode == Defines.SQLITE_DONE)
                retcode = Defines.SQLITE_OK;

        Exit:
            if (psqlite3_stmt != IntPtr.Zero)
                GMPSmartDLL.sqlite3_finalize(psqlite3_stmt);
            psqlite3_stmt = IntPtr.Zero;

            if (db != IntPtr.Zero)
                GMPSmartDLL.sqlite3_close(db);
            db = IntPtr.Zero;

            if (retcode != 0)
            {
                MessageBox.Show("error code : " + retcode);
            }

            return retcode;
        }

        int datagrigFlag = 0;
        private void m_listHostPluGrups_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                string FileName = m_lstDBFiles.SelectedItem.ToString().Substring(m_lstDBFiles.SelectedItem.ToString().LastIndexOf('\\') + 1);
                string pluGrupParent = m_listHostPluGrups.SelectedCells[0].Value.ToString();
                UpdateHostPluGrups(FileName, m_listHostPluGrup2, Convert.ToInt32(pluGrupParent));
            }
            catch (Exception)
            {
            }
        }

        private void m_listHostPluGrup2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                string FileName = m_lstDBFiles.SelectedItem.ToString().Substring(m_lstDBFiles.SelectedItem.ToString().LastIndexOf('\\') + 1);
                string pluGrupParent = m_listHostPluGrup2.SelectedCells[0].Value.ToString();
                UpdateHostPluItems(FileName, m_listHostPluItems, Convert.ToInt32(pluGrupParent));
            }
            catch (Exception)
            {
            }
        }

        private void m_btnUploadtoPC_Click(object sender, EventArgs e)
        {
            string HostFileName = "";
            UInt32 retcode = 0;

            int Offset = 0;
            int Whence = 0;
            byte[] Buffer = new byte[1024];
            short ReadLen = 0;

            if (m_PluDbName.Length == 0)
            {
                MessageBox.Show("Database Bulunamadı...");
                return;
            }

            HostFileName = m_PluDbName;
            HostFileName += ".d";

            if (File.Exists(HostFileName))
            {
                if (MessageBox.Show("A file with the same name already exists in the host computer. It will be removed if you continue. Do you want to proceed?", "WARNINIG", MessageBoxButtons.OKCancel) != DialogResult.OK)
                    return;
            }

            File.Delete(HostFileName);

            using (BinaryWriter b = new BinaryWriter(File.Open(HostFileName, FileMode.OpenOrCreate)))
            {
                b.BaseStream.Seek(0, SeekOrigin.Begin);

                while ((retcode = GMPSmartDLL.FP3_FileSystem_FileRead(GMPForm.CurrentInterface, m_PluDbName, Offset, Whence, Buffer, Buffer.Length, ref ReadLen)) == Defines.TRAN_RESULT_OK)
                {
                    b.Write(Buffer, 0, ReadLen);

                    Offset += ReadLen;

                    string cs;
                    cs = String.Format("Upload Status {0}", (Offset * 100) / m_PluDbSize);
                    this.Text = cs;
                }
            }

            if (retcode == Defines.APP_ERR_FILE_EOF)
            {

                UpdateHostDbFiles();

                MessageBox.Show("File has succesfully uploaded", "File Upload", MessageBoxButtons.OK);
                retcode = Defines.TRAN_RESULT_OK;
            }
            goto Exit;

        Exit:

            if (retcode != Defines.TRAN_RESULT_OK)
            {
                GMPForm gf = new GMPForm();
                gf.HandleErrorCode(retcode);
            }
        }

        string m_PluDbName = "";
        private void m_btnDownloadtoECR_Click(object sender, EventArgs e)
        {
            UInt32 retcode = Defines.TRAN_RESULT_OK;

            string csFileNamePlu;
            IntPtr pFileHost = IntPtr.Zero;

            string hostFileName = "";

            try
            {
                hostFileName = m_lstDBFiles.SelectedItem.ToString().Substring(m_lstDBFiles.SelectedItem.ToString().LastIndexOf('\\') + 1);
            }
            catch (Exception ex)
            {

                MessageBox.Show(ex.Message);
            }
            if (hostFileName.Length == 0)
                return;

            // Host ve PLU dosya adları aynı değil. Host'da ".sq3" uzantısı var, onları çıkartmak lazım
            csFileNamePlu = hostFileName.Substring(0, hostFileName.IndexOf('.'));

            if (csFileNamePlu != m_PluDbName)  //if( csFileNamePlu == m_PluDbName)  
            {
                // that means; PLU DB Name in ECR and the new file name (to be downloaded into ECR) are not the same. So, ECR PLU DB file name will be changed !! 
                if (MessageBox.Show("The existnig ECR PLU DB file name will be changed. Do you want to proceed?", "WARNINIG", MessageBoxButtons.OKCancel) != System.Windows.Forms.DialogResult.OK)
                    return;

                retcode = GMPSmartDLL.FP3_SetPluDatabaseInfo(GMPForm.CurrentInterface, csFileNamePlu, 0);
                if (retcode != Defines.TRAN_RESULT_OK)
                    goto Exit;
            }
            else
            {
                if (MessageBox.Show("The existnig file in ECR will be removed. Do you want to proceed?", "WARNINIG", MessageBoxButtons.OKCancel) != System.Windows.Forms.DialogResult.OK)
                    return;
            }

            using (BinaryReader b = new BinaryReader(File.Open(hostFileName, FileMode.Open)))
            {
                long HostFileSize = (long)b.BaseStream.Length;  //HostFileSize is the entire length of the file we are reading from. 
                int pos = 0;    //Pos is the index we want to start reading from.

                b.BaseStream.Seek(pos, SeekOrigin.Begin);

                retcode = GMPSmartDLL.FP3_FileSystem_FileRemove(GMPForm.CurrentInterface, Encoding.Default.GetBytes(csFileNamePlu));

                if (retcode != Defines.TRAN_RESULT_OK)
                    goto Exit;

                short ReadLen = 0;
                int offset = 0;

                while (true)
                {
                    byte[] buffer = new byte[1024];
                    ReadLen = (short)b.Read(buffer, 0, 1024);
                    if (ReadLen == 0)
                        goto Exit;

                    do
                    {
                        retcode = GMPSmartDLL.FP3_FileSystem_FileWrite(GMPForm.CurrentInterface, Encoding.Default.GetBytes(csFileNamePlu), offset, 0, buffer, ReadLen);
                        if (retcode == Defines.DLL_RETCODE_RECV_BUSY)
                            Thread.Sleep(1000);
                    } while (retcode == Defines.DLL_RETCODE_RECV_BUSY);

                    if (retcode != Defines.TRAN_RESULT_OK)
                        goto Exit;

                    offset += ReadLen;

                    if (HostFileSize != 0)
                    {
                        string cs;
                        cs = String.Format("Download Status {0}", (offset * 100) / HostFileSize);
                        this.Text = cs;
                    }
                }
            }

        Exit:
            if (retcode != Defines.TRAN_RESULT_OK)
            {
                GMPForm gf = new GMPForm();
                gf.HandleErrorCode(retcode);
            }
            RefreshEcrPluDbFileName();

        }

        private void m_btnInsert_Click(object sender, EventArgs e)
        {
            commonDBFunc(0);
        }

        private void m_btnUpdate_Click(object sender, EventArgs e)
        {
            commonDBFunc(1);
        }

        private void m_btnDelete_Click(object sender, EventArgs e)
        {
            commonDBFunc(2);
        }

        string GetDeleteString(DataGridView plist, int nItem)
        {
            string output = String.Format(" WHERE ROWID={0}", plist.Rows[nItem].Cells[0].Value.ToString());

            return output;
        }

        string GetUpdateString(DataGridView plist, int nItem)
        {
            string output = "";
            string columnName = "";
            string columnData = "";

            int nColumnCount = plist.ColumnCount;

            for (int i = 1; i < nColumnCount; i++)
            {
                columnName = plist.Columns[i].HeaderText;
                columnData = plist.Rows[nItem].Cells[i].Value.ToString();

                if (columnData.Length == 0)
                    continue;

                if (output.Length != 0)
                    output += ",";

                if ((columnName == "PLU_GRUP_NAME") || (columnName == "PLU_NAME") || (columnName == "PLU_BARCODE"))
                    output += String.Format("{0}='{1}'", columnName, columnData);
                else
                    output += String.Format("{0}={1}", columnName, columnData);

            }

            output += String.Format(" WHERE ROWID={0}", plist.Rows[nItem].Cells[0].Value.ToString());

            return output;
        }

        void commonDBFunc(int commandType)
        {
            IntPtr db = IntPtr.Zero;

            string hostFileName = m_lstDBFiles.SelectedItem.ToString().Substring(m_lstDBFiles.SelectedItem.ToString().LastIndexOf('\\') + 1);
            if (hostFileName.Length == 0)
                return;

            int retcode = GMPSmartDLL.sqlite3_open(hostFileName, out db);
            if ((retcode != Defines.SQLITE_OK))
                goto Exit;
            DataGridView dgv = new DataGridView();
            if (datagrigFlag == 1)
                dgv = m_listHostPluGrups;
            else if (datagrigFlag == 2)
                dgv = m_listHostPluGrup2;
            else if (datagrigFlag == 3)
                dgv = m_listHostPluItems;
            string sqlWord = "";

            if (commandType == 2)
            {
                if (datagrigFlag == 1 || datagrigFlag == 2)
                    sqlWord = String.Format("DELETE FROM TBL_PLU_GRUP {0};", GetDeleteString(dgv, dgv.CurrentRow.Index));
                else if (datagrigFlag == 3)
                    sqlWord = String.Format("DELETE FROM TBL_PLU {0};", GetDeleteString(dgv, dgv.CurrentRow.Index));
            }
            else if (commandType == 1)
            {
                if (datagrigFlag == 1 || datagrigFlag == 2)
                    sqlWord = String.Format("UPDATE TBL_PLU_GRUP SET {0};", GetUpdateString(dgv, dgv.CurrentRow.Index));
                else if (datagrigFlag == 3)
                    sqlWord = String.Format("UPDATE TBL_PLU SET {0};", GetUpdateString(dgv, dgv.CurrentRow.Index));
            }
            else
            {
                string DepartmentIndex = "";
                string grupName = "";
                string GrupId = "";
                string grupParentId = "0";
                if (datagrigFlag == 2 || datagrigFlag == 3)
                {
                    GetInputForm gif3 = new GetInputForm("GRUP PARENT ID", "", 1);
                    if (gif3.ShowDialog() != DialogResult.OK)
                        return;
                    grupParentId = gif3.textBox1.Text;
                }

                GetInputForm gif = new GetInputForm("GRUP ADI", "", 1);
                if (gif.ShowDialog() != DialogResult.OK)
                    goto Exit;
                grupName = gif.textBox1.Text;
                GetInputForm gif2 = new GetInputForm("BARKOD NO", "", 2);
                if (gif2.ShowDialog() != DialogResult.OK)
                    goto Exit;
                GrupId = gif2.textBox1.Text;

                if (datagrigFlag == 3)
                {
                    GetInputForm gif3 = new GetInputForm("Departman Index", "", 2);
                    if (gif3.ShowDialog() != DialogResult.OK)
                        goto Exit;
                    DepartmentIndex = gif3.textBox1.Text;
                }
                if (datagrigFlag == 1 || datagrigFlag == 2)
                    sqlWord = String.Format("INSERT INTO TBL_PLU_GRUP (PLU_GRUP_ID, PLU_GRUP_PARENT, PLU_GRUP_FLAG, PLU_GRUP_NAME, LAST_MODIFIED, RECORD_STATUS) VALUES({0}, '{1}', 0, '{2}', 0, 0);", GrupId, grupParentId, grupName);
                else if (datagrigFlag == 3)
                    sqlWord = String.Format("INSERT INTO TBL_PLU (PLU_BARCODE, DEPT_INDEX, PLU_GRUP_PARENT, PLU_FLAG, PLU_NAME, PLU_UNIT, LAST_MODIFIED, RECORD_STATUS, PLU_AMOUNT1_CURRENCY, PLU_AMOUNT1, PLU_AMOUNT2_CURRENCY, PLU_AMOUNT2, PLU_AMOUNT3_CURRENCY, PLU_AMOUNT3, ITEM_COUNT_PRECITION) VALUES('{0}',{1},'{2}', 0, '{3}', 0, 0, 0, 949,100,0,0,0,0,0);", GrupId, DepartmentIndex, grupParentId, grupName);

            }

            IntPtr psqlite3_stmt = IntPtr.Zero;
            IntPtr zErrMsg2 = IntPtr.Zero;
            retcode = GMPSmartDLL.sqlite3_prepare_v2(db, sqlWord, -1, out psqlite3_stmt, zErrMsg2);
            if (retcode != Defines.SQLITE_OK)
                goto Exit;

            retcode = GMPSmartDLL.sqlite3_step(psqlite3_stmt);

            if (psqlite3_stmt != IntPtr.Zero)
                GMPSmartDLL.sqlite3_finalize(psqlite3_stmt);
            psqlite3_stmt = IntPtr.Zero;

        Exit:
            if (retcode != Defines.SQLITE_OK)
            {
                GMPForm gf = new GMPForm();

                gf.HandleErrorCode((UInt32)retcode);
            }

            if (db != IntPtr.Zero)
                GMPSmartDLL.sqlite3_close(db);

            ErrorClass.DisplayErrorMessage((UInt32)retcode);

        }

        void commonECR_DBFunc(int commandType)
        {

            UInt32 retcode = GMPSmartDLL.FP3_Database_Open(GMPForm.CurrentInterface, m_PluDbName);
            if ((retcode != Defines.SQLITE_OK))
                goto Exit;

            DataGridView dgv = new DataGridView();
            if (datagrigFlag == 1)
                dgv = m_listECRPluGrups;
            else if (datagrigFlag == 2)
                dgv = m_listECRPluGrup2;
            else if (datagrigFlag == 3)
                dgv = m_listECRPluItems;
            string sqlWord = "";

            if (commandType == 2)
            {
                if (datagrigFlag == 1 || datagrigFlag == 2)
                    sqlWord = String.Format("DELETE FROM TBL_PLU_GRUP {0};", GetDeleteString(dgv, dgv.CurrentRow.Index));
                else if (datagrigFlag == 3)
                    sqlWord = String.Format("DELETE FROM TBL_PLU {0};", GetDeleteString(dgv, dgv.CurrentRow.Index));
            }
            else if (commandType == 1)
            {
                if (datagrigFlag == 1 || datagrigFlag == 2)
                    sqlWord = String.Format("UPDATE TBL_PLU_GRUP SET {0};", GetUpdateString(dgv, dgv.CurrentRow.Index));
                else if (datagrigFlag == 3)
                    sqlWord = String.Format("UPDATE TBL_PLU SET {0};", GetUpdateString(dgv, dgv.CurrentRow.Index));
            }
            else
            {
                string grupName = "";
                string GrupId = "";
                string grupParentId = "0";
                string DepartmentIndex = "";
                string ItemCountPrecition = "";
                if (datagrigFlag == 2 || datagrigFlag == 3)
                {
                    GetInputForm gif3 = new GetInputForm("GRUP PARENT ID", "", 1);
                    if (gif3.ShowDialog() != DialogResult.OK)
                        goto Exit;

                    grupParentId = gif3.textBox1.Text;
                }

                GetInputForm gif = new GetInputForm("GRUP ADI", "", 1);
                if (gif.ShowDialog() != DialogResult.OK)
                    goto Exit;

                grupName = gif.textBox1.Text;
                GetInputForm gif2 = new GetInputForm("BARKOD NO", "", 2);
                if (gif2.ShowDialog() != DialogResult.OK)
                    goto Exit;
                GrupId = gif2.textBox1.Text;

                if (datagrigFlag == 3)
                {
                    GetInputForm gif3 = new GetInputForm("DEPARTMAN INDEX", "", 2);
                    if (gif3.ShowDialog() != DialogResult.OK)
                        goto Exit;
                    DepartmentIndex = gif3.textBox1.Text;
                }

                if (datagrigFlag == 3)
                {
                    GetInputForm gif4 = new GetInputForm("ITEM COUNT PRECITION ", "", 2);
                    if (gif4.ShowDialog() != DialogResult.OK)
                        goto Exit;
                    ItemCountPrecition = gif4.textBox1.Text;
                }

                if (datagrigFlag == 1 || datagrigFlag == 2)
                    sqlWord = String.Format("INSERT INTO TBL_PLU_GRUP (PLU_GRUP_ID, PLU_GRUP_PARENT, PLU_GRUP_FLAG, PLU_GRUP_NAME, LAST_MODIFIED, RECORD_STATUS) VALUES({0}, '{1}', 0, {2}, 0, 0);", GrupId, grupParentId, grupName);
                else if (datagrigFlag == 3)
                    sqlWord = String.Format("INSERT INTO TBL_PLU (PLU_BARCODE, DEPT_INDEX, PLU_GRUP_PARENT, PLU_FLAG, PLU_NAME, PLU_UNIT, LAST_MODIFIED, RECORD_STATUS, PLU_AMOUNT1_CURRENCY, PLU_AMOUNT1, PLU_AMOUNT2_CURRENCY, PLU_AMOUNT2, PLU_AMOUNT3_CURRENCY, PLU_AMOUNT3, ITEM_COUNT_PRECITION) VALUES('{0}','{1}',{2}, 0, '{3}', 0, 0, 0, 949,100,0,0,0,0,{4});", GrupId, DepartmentIndex, grupParentId, grupName, ItemCountPrecition);

            }

            ST_DATABASE_RESULT stDatabaseResult = new ST_DATABASE_RESULT();

            retcode = Json_GMPSmartDLL.FP3_Database_Execute(GMPForm.CurrentInterface, sqlWord, ref stDatabaseResult);

            if (retcode != Defines.TRAN_RESULT_OK)
                goto Exit;

        Exit:
            if (GMPSmartDLL.FP3_Database_GetHandle(GMPForm.CurrentInterface) != 0)
                GMPSmartDLL.FP3_Database_Close(GMPForm.CurrentInterface);

            ErrorClass.DisplayErrorMessage(retcode);
        }

        private void m_listHostPluGrups_Click(object sender, EventArgs e)
        {
            datagrigFlag = 1;

        }

        private void m_listHostPluGrup2_Click(object sender, EventArgs e)
        {
            datagrigFlag = 2;

        }

        private void m_listHostPluItems_Click(object sender, EventArgs e)
        {
            datagrigFlag = 3;
        }

        private void m_btnRefreshPluDbName_Click(object sender, EventArgs e)
        {
            RefreshEcrPluDbFileName();
        }

        private void m_listEcrPluFileName_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdatePluGrups(m_listECRPluGrups, 0);

            m_listECRPluGrup2.DataSource = null;
            m_listECRPluGrup2.Rows.Clear();
            m_listECRPluGrup2.Refresh();


            m_listECRPluItems.DataSource = null;
            m_listECRPluItems.Rows.Clear();
            m_listECRPluItems.Refresh();

        }

        UInt32 UpdateTblPlu(DataGridView plist, int pluGrupParent)
        {

            string sqlWord = String.Format("SELECT * FROM TBL_PLU WHERE PLU_GRUP_PARENT={0};", pluGrupParent);
            return FillListControlFromDBExt(m_PluDbName, plist, sqlWord);
        }

        UInt32 UpdatePluGrups(DataGridView plist, int pluGrupParent)
        {

            string sqlWord = String.Format("SELECT * FROM TBL_PLU_GRUP WHERE PLU_GRUP_PARENT={0};", pluGrupParent);
            return FillListControlFromDBExt(m_PluDbName, plist, sqlWord);
        }

        DataTable table;

        UInt32 FillListControlFromDBExt(string dbName, DataGridView plistCtrl, string swlWord)
        {
            table = new DataTable();

            UInt32 retcode;
            ushort numberOfColumns = 24;

            retcode = GMPSmartDLL.FP3_Database_Open(GMPForm.CurrentInterface, dbName);
            if ((retcode != Defines.TRAN_RESULT_OK))
                goto Exit;

            retcode = GMPSmartDLL.FP3_Database_Query(GMPForm.CurrentInterface, swlWord, ref numberOfColumns);
            if (retcode != Defines.TRAN_RESULT_OK)
                goto Exit;
            try
            {
                ST_DATABASE_RESULT StDatabaseResult = new ST_DATABASE_RESULT();
                retcode = Json_GMPSmartDLL.FP3_Database_QueryColomnCaptions(GMPForm.CurrentInterface, ref StDatabaseResult);

                if (retcode == Defines.TRAN_RESULT_OK)
                {

                    numberOfColumns = (ushort)StDatabaseResult.pstCaptionArray[0].numberOfColomns;

                    if (StDatabaseResult.pstCaptionArray != null)
                    {
                        plistCtrl.DataSource = null;
                        plistCtrl.Rows.Clear();
                        plistCtrl.Refresh();


                        int nColumnCount = plistCtrl.Columns.Count;

                        // Delete all of the columns. 
                        for (int i = nColumnCount - 1; i >= 0; i--)
                            plistCtrl.Columns.Remove(plistCtrl.Columns[i]);

                        for (int i = 0; i < numberOfColumns; i++)
                        {
                            string cs;
                            cs = String.Format(StDatabaseResult.pstCaptionArray[0].pstColomnArray[i].data);
                            table.Columns.Add(cs);
                        }

                        //Json_GMPSmartDLL.Database_FreeStructure(ref StDatabaseResult);

                        if (numberOfColumns == 0)
                        {
                            retcode = GMPSmartDLL.FP3_Database_QueryFinish(GMPForm.CurrentInterface);
                            goto Exit;
                        }

                        do
                        {
                            retcode = Json_GMPSmartDLL.FP3_Database_QueryReadLine(GMPForm.CurrentInterface, 50, numberOfColumns, ref StDatabaseResult);

                            if ((retcode != Defines.SQLITE_ROW) && (retcode != Defines.SQLITE_DONE))
                                break;

                            int numberOfLines = (ushort)StDatabaseResult.numberOfLines;
                            for (int j = 0; j < numberOfLines; j++)
                            {
                                DataRow workRow = table.NewRow();
                                for (int i = 0; i < numberOfColumns; i++)
                                {
                                    workRow[i] = StDatabaseResult.pstLineArray[j].pstColomnArray[i].data;
                                }
                                table.Rows.Add(workRow);
                            }

                            plistCtrl.DataSource = table;


                        } while (retcode == Defines.SQLITE_ROW);
                    }
                }

                retcode = GMPSmartDLL.FP3_Database_QueryFinish(GMPForm.CurrentInterface);
            }
            catch (Exception)
            {
                if (GMPSmartDLL.FP3_Database_GetHandle(GMPForm.CurrentInterface) != 0)
                    GMPSmartDLL.FP3_Database_Close(GMPForm.CurrentInterface);
                throw;
            }

        Exit:
            if (GMPSmartDLL.FP3_Database_GetHandle(GMPForm.CurrentInterface) != 0)
                GMPSmartDLL.FP3_Database_Close(GMPForm.CurrentInterface);

            if (retcode != Defines.TRAN_RESULT_OK)
            {
                GMPForm gf = new GMPForm();
                gf.HandleErrorCode(retcode);
            }

            return retcode;
        }

        private void m_listECRPluGrups_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (m_listECRPluGrups.SelectedCells.Count > 0)
            {
                int selectedrowindex = m_listECRPluGrups.SelectedCells[0].RowIndex;

                DataGridViewRow selectedRow = m_listECRPluGrups.Rows[selectedrowindex];

                string a = Convert.ToString(selectedRow.Cells[1].Value);

                UpdatePluGrups(m_listECRPluGrup2, Convert.ToInt32(a));
            }
        }

        private void m_listECRPluGrup2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (m_listECRPluGrup2.SelectedCells.Count > 0)
            {
                int selectedrowindex = m_listECRPluGrup2.SelectedCells[0].RowIndex;

                DataGridViewRow selectedRow = m_listECRPluGrup2.Rows[selectedrowindex];

                string a = Convert.ToString(selectedRow.Cells[1].Value);

                UpdateTblPlu(m_listECRPluItems, Convert.ToInt32(a));
            }
        }

        private void m_listECRPluGrups_Click(object sender, EventArgs e)
        {
            datagrigFlag = 1;
        }

        private void m_listECRPluGrup2_Click(object sender, EventArgs e)
        {
            datagrigFlag = 2;
        }

        private void m_listECRPluItems_Click(object sender, EventArgs e)
        {
            datagrigFlag = 3;
        }

        private void m_btnInsertECR_Click(object sender, EventArgs e)
        {
            commonECR_DBFunc(0);
        }

        private void m_btnUpdateECR_Click(object sender, EventArgs e)
        {
            commonECR_DBFunc(1);
        }

        private void m_btnDeleteECR_Click(object sender, EventArgs e)
        {
            commonECR_DBFunc(2);
        }
    }
}
