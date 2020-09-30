namespace GmpSampleSim
{
    partial class PLUDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.m_lstDBFiles = new System.Windows.Forms.ListBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.m_listHostPluGrups = new System.Windows.Forms.DataGridView();
            this.m_listHostPluGrup2 = new System.Windows.Forms.DataGridView();
            this.m_listHostPluItems = new System.Windows.Forms.DataGridView();
            this.m_btnUploadtoPC = new System.Windows.Forms.Button();
            this.m_btnDownloadtoECR = new System.Windows.Forms.Button();
            this.m_btnInsert = new System.Windows.Forms.Button();
            this.m_btnUpdate = new System.Windows.Forms.Button();
            this.m_btnDelete = new System.Windows.Forms.Button();
            this.m_listEcrPluFileName = new System.Windows.Forms.ListBox();
            this.m_btnRefreshPluDbName = new System.Windows.Forms.Button();
            this.m_listECRPluItems = new System.Windows.Forms.DataGridView();
            this.m_listECRPluGrup2 = new System.Windows.Forms.DataGridView();
            this.m_listECRPluGrups = new System.Windows.Forms.DataGridView();
            this.m_btnDeleteECR = new System.Windows.Forms.Button();
            this.m_btnUpdateECR = new System.Windows.Forms.Button();
            this.m_btnInsertECR = new System.Windows.Forms.Button();
            this.m_lblErrorCode = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_listHostPluGrups)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listHostPluGrup2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listHostPluItems)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listECRPluItems)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listECRPluGrup2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listECRPluGrups)).BeginInit();
            this.SuspendLayout();
            // 
            // m_lstDBFiles
            // 
            this.m_lstDBFiles.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.m_lstDBFiles.FormattingEnabled = true;
            this.m_lstDBFiles.Location = new System.Drawing.Point(12, 36);
            this.m_lstDBFiles.Name = "m_lstDBFiles";
            this.m_lstDBFiles.Size = new System.Drawing.Size(504, 69);
            this.m_lstDBFiles.TabIndex = 0;
            this.m_lstDBFiles.SelectedIndexChanged += new System.EventHandler(this.m_lstDBFiles_SelectedIndexChanged);
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.textBox1.Location = new System.Drawing.Point(12, 10);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(504, 20);
            this.textBox1.TabIndex = 1;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // m_listHostPluGrups
            // 
            this.m_listHostPluGrups.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_listHostPluGrups.Location = new System.Drawing.Point(12, 111);
            this.m_listHostPluGrups.Name = "m_listHostPluGrups";
            this.m_listHostPluGrups.Size = new System.Drawing.Size(504, 163);
            this.m_listHostPluGrups.TabIndex = 7;
            this.m_listHostPluGrups.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.m_listHostPluGrups_CellContentClick);
            this.m_listHostPluGrups.Click += new System.EventHandler(this.m_listHostPluGrups_Click);
            // 
            // m_listHostPluGrup2
            // 
            this.m_listHostPluGrup2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_listHostPluGrup2.Location = new System.Drawing.Point(12, 280);
            this.m_listHostPluGrup2.Name = "m_listHostPluGrup2";
            this.m_listHostPluGrup2.Size = new System.Drawing.Size(504, 163);
            this.m_listHostPluGrup2.TabIndex = 8;
            this.m_listHostPluGrup2.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.m_listHostPluGrup2_CellContentClick);
            this.m_listHostPluGrup2.Click += new System.EventHandler(this.m_listHostPluGrup2_Click);
            // 
            // m_listHostPluItems
            // 
            this.m_listHostPluItems.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_listHostPluItems.Location = new System.Drawing.Point(12, 449);
            this.m_listHostPluItems.Name = "m_listHostPluItems";
            this.m_listHostPluItems.Size = new System.Drawing.Size(504, 142);
            this.m_listHostPluItems.TabIndex = 9;
            this.m_listHostPluItems.Click += new System.EventHandler(this.m_listHostPluItems_Click);
            // 
            // m_btnUploadtoPC
            // 
            this.m_btnUploadtoPC.Location = new System.Drawing.Point(522, 36);
            this.m_btnUploadtoPC.Name = "m_btnUploadtoPC";
            this.m_btnUploadtoPC.Size = new System.Drawing.Size(128, 23);
            this.m_btnUploadtoPC.TabIndex = 10;
            this.m_btnUploadtoPC.Text = "Upload To PC";
            this.m_btnUploadtoPC.UseVisualStyleBackColor = true;
            this.m_btnUploadtoPC.Click += new System.EventHandler(this.m_btnUploadtoPC_Click);
            // 
            // m_btnDownloadtoECR
            // 
            this.m_btnDownloadtoECR.Location = new System.Drawing.Point(522, 65);
            this.m_btnDownloadtoECR.Name = "m_btnDownloadtoECR";
            this.m_btnDownloadtoECR.Size = new System.Drawing.Size(128, 23);
            this.m_btnDownloadtoECR.TabIndex = 11;
            this.m_btnDownloadtoECR.Text = "Download To ECR";
            this.m_btnDownloadtoECR.UseVisualStyleBackColor = true;
            this.m_btnDownloadtoECR.Click += new System.EventHandler(this.m_btnDownloadtoECR_Click);
            // 
            // m_btnInsert
            // 
            this.m_btnInsert.Location = new System.Drawing.Point(522, 111);
            this.m_btnInsert.Name = "m_btnInsert";
            this.m_btnInsert.Size = new System.Drawing.Size(58, 23);
            this.m_btnInsert.TabIndex = 12;
            this.m_btnInsert.Text = "Insert";
            this.m_btnInsert.UseVisualStyleBackColor = true;
            this.m_btnInsert.Click += new System.EventHandler(this.m_btnInsert_Click);
            // 
            // m_btnUpdate
            // 
            this.m_btnUpdate.Location = new System.Drawing.Point(522, 140);
            this.m_btnUpdate.Name = "m_btnUpdate";
            this.m_btnUpdate.Size = new System.Drawing.Size(58, 23);
            this.m_btnUpdate.TabIndex = 13;
            this.m_btnUpdate.Text = "Update";
            this.m_btnUpdate.UseVisualStyleBackColor = true;
            this.m_btnUpdate.Click += new System.EventHandler(this.m_btnUpdate_Click);
            // 
            // m_btnDelete
            // 
            this.m_btnDelete.Location = new System.Drawing.Point(522, 169);
            this.m_btnDelete.Name = "m_btnDelete";
            this.m_btnDelete.Size = new System.Drawing.Size(58, 23);
            this.m_btnDelete.TabIndex = 14;
            this.m_btnDelete.Text = "Delete";
            this.m_btnDelete.UseVisualStyleBackColor = true;
            this.m_btnDelete.Click += new System.EventHandler(this.m_btnDelete_Click);
            // 
            // m_listEcrPluFileName
            // 
            this.m_listEcrPluFileName.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.m_listEcrPluFileName.FormattingEnabled = true;
            this.m_listEcrPluFileName.Location = new System.Drawing.Point(657, 36);
            this.m_listEcrPluFileName.Name = "m_listEcrPluFileName";
            this.m_listEcrPluFileName.Size = new System.Drawing.Size(504, 69);
            this.m_listEcrPluFileName.TabIndex = 15;
            this.m_listEcrPluFileName.SelectedIndexChanged += new System.EventHandler(this.m_listEcrPluFileName_SelectedIndexChanged);
            // 
            // m_btnRefreshPluDbName
            // 
            this.m_btnRefreshPluDbName.Location = new System.Drawing.Point(657, 7);
            this.m_btnRefreshPluDbName.Name = "m_btnRefreshPluDbName";
            this.m_btnRefreshPluDbName.Size = new System.Drawing.Size(503, 23);
            this.m_btnRefreshPluDbName.TabIndex = 16;
            this.m_btnRefreshPluDbName.Text = "Refresh PLU DB Name";
            this.m_btnRefreshPluDbName.UseVisualStyleBackColor = true;
            this.m_btnRefreshPluDbName.Click += new System.EventHandler(this.m_btnRefreshPluDbName_Click);
            // 
            // m_listECRPluItems
            // 
            this.m_listECRPluItems.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_listECRPluItems.Location = new System.Drawing.Point(656, 449);
            this.m_listECRPluItems.Name = "m_listECRPluItems";
            this.m_listECRPluItems.Size = new System.Drawing.Size(504, 163);
            this.m_listECRPluItems.TabIndex = 19;
            this.m_listECRPluItems.Click += new System.EventHandler(this.m_listECRPluItems_Click);
            // 
            // m_listECRPluGrup2
            // 
            this.m_listECRPluGrup2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_listECRPluGrup2.Location = new System.Drawing.Point(656, 280);
            this.m_listECRPluGrup2.Name = "m_listECRPluGrup2";
            this.m_listECRPluGrup2.Size = new System.Drawing.Size(504, 163);
            this.m_listECRPluGrup2.TabIndex = 18;
            this.m_listECRPluGrup2.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.m_listECRPluGrup2_CellContentClick);
            this.m_listECRPluGrup2.Click += new System.EventHandler(this.m_listECRPluGrup2_Click);
            // 
            // m_listECRPluGrups
            // 
            this.m_listECRPluGrups.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_listECRPluGrups.Location = new System.Drawing.Point(656, 111);
            this.m_listECRPluGrups.Name = "m_listECRPluGrups";
            this.m_listECRPluGrups.Size = new System.Drawing.Size(504, 163);
            this.m_listECRPluGrups.TabIndex = 17;
            this.m_listECRPluGrups.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.m_listECRPluGrups_CellContentClick);
            this.m_listECRPluGrups.Click += new System.EventHandler(this.m_listECRPluGrups_Click);
            // 
            // m_btnDeleteECR
            // 
            this.m_btnDeleteECR.Location = new System.Drawing.Point(592, 169);
            this.m_btnDeleteECR.Name = "m_btnDeleteECR";
            this.m_btnDeleteECR.Size = new System.Drawing.Size(58, 23);
            this.m_btnDeleteECR.TabIndex = 22;
            this.m_btnDeleteECR.Text = "Delete";
            this.m_btnDeleteECR.UseVisualStyleBackColor = true;
            this.m_btnDeleteECR.Click += new System.EventHandler(this.m_btnDeleteECR_Click);
            // 
            // m_btnUpdateECR
            // 
            this.m_btnUpdateECR.Location = new System.Drawing.Point(592, 140);
            this.m_btnUpdateECR.Name = "m_btnUpdateECR";
            this.m_btnUpdateECR.Size = new System.Drawing.Size(58, 23);
            this.m_btnUpdateECR.TabIndex = 21;
            this.m_btnUpdateECR.Text = "Update";
            this.m_btnUpdateECR.UseVisualStyleBackColor = true;
            this.m_btnUpdateECR.Click += new System.EventHandler(this.m_btnUpdateECR_Click);
            // 
            // m_btnInsertECR
            // 
            this.m_btnInsertECR.Location = new System.Drawing.Point(592, 111);
            this.m_btnInsertECR.Name = "m_btnInsertECR";
            this.m_btnInsertECR.Size = new System.Drawing.Size(58, 23);
            this.m_btnInsertECR.TabIndex = 20;
            this.m_btnInsertECR.Text = "Insert";
            this.m_btnInsertECR.UseVisualStyleBackColor = true;
            this.m_btnInsertECR.Click += new System.EventHandler(this.m_btnInsertECR_Click);
            // 
            // m_lblErrorCode
            // 
            this.m_lblErrorCode.AutoSize = true;
            this.m_lblErrorCode.Location = new System.Drawing.Point(12, 601);
            this.m_lblErrorCode.Name = "m_lblErrorCode";
            this.m_lblErrorCode.Size = new System.Drawing.Size(0, 13);
            this.m_lblErrorCode.TabIndex = 23;
            // 
            // PLUDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1172, 621);
            this.Controls.Add(this.m_lblErrorCode);
            this.Controls.Add(this.m_btnDeleteECR);
            this.Controls.Add(this.m_btnUpdateECR);
            this.Controls.Add(this.m_btnInsertECR);
            this.Controls.Add(this.m_listECRPluItems);
            this.Controls.Add(this.m_listECRPluGrup2);
            this.Controls.Add(this.m_listECRPluGrups);
            this.Controls.Add(this.m_btnRefreshPluDbName);
            this.Controls.Add(this.m_listEcrPluFileName);
            this.Controls.Add(this.m_btnDelete);
            this.Controls.Add(this.m_btnUpdate);
            this.Controls.Add(this.m_btnInsert);
            this.Controls.Add(this.m_btnDownloadtoECR);
            this.Controls.Add(this.m_btnUploadtoPC);
            this.Controls.Add(this.m_listHostPluItems);
            this.Controls.Add(this.m_listHostPluGrup2);
            this.Controls.Add(this.m_listHostPluGrups);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.m_lstDBFiles);
            this.Name = "PLUDialog";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PLUDialog";
            this.Load += new System.EventHandler(this.PLUDialog_Load);
            ((System.ComponentModel.ISupportInitialize)(this.m_listHostPluGrups)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listHostPluGrup2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listHostPluItems)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listECRPluItems)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listECRPluGrup2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_listECRPluGrups)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox m_lstDBFiles;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.DataGridView m_listHostPluGrups;
        private System.Windows.Forms.DataGridView m_listHostPluGrup2;
        private System.Windows.Forms.DataGridView m_listHostPluItems;
        private System.Windows.Forms.Button m_btnUploadtoPC;
        private System.Windows.Forms.Button m_btnDownloadtoECR;
        private System.Windows.Forms.Button m_btnInsert;
        private System.Windows.Forms.Button m_btnUpdate;
        private System.Windows.Forms.Button m_btnDelete;
        private System.Windows.Forms.ListBox m_listEcrPluFileName;
        private System.Windows.Forms.Button m_btnRefreshPluDbName;
        private System.Windows.Forms.DataGridView m_listECRPluItems;
        private System.Windows.Forms.DataGridView m_listECRPluGrup2;
        private System.Windows.Forms.DataGridView m_listECRPluGrups;
        private System.Windows.Forms.Button m_btnDeleteECR;
        private System.Windows.Forms.Button m_btnUpdateECR;
        private System.Windows.Forms.Button m_btnInsertECR;
        private System.Windows.Forms.Label m_lblErrorCode;
    }
}