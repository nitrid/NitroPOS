namespace GmpSampleSim
{
    partial class CashierForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.m_activeCashierIndex = new System.Windows.Forms.Label();
            this.m_activeCashierName = new System.Windows.Forms.Label();
            this.m_btnCashierLogOut = new System.Windows.Forms.Button();
            this.m_ListCashiers = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.m_btnAddCashier = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.m_txtCashierIndex = new System.Windows.Forms.TextBox();
            this.m_txtCashierName = new System.Windows.Forms.TextBox();
            this.m_txtCashierPassword = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(103, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Aktif Kasiyer Index : ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(92, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Aktif Kasiyer Adı : ";
            // 
            // m_activeCashierIndex
            // 
            this.m_activeCashierIndex.AutoSize = true;
            this.m_activeCashierIndex.Location = new System.Drawing.Point(144, 13);
            this.m_activeCashierIndex.Name = "m_activeCashierIndex";
            this.m_activeCashierIndex.Size = new System.Drawing.Size(35, 13);
            this.m_activeCashierIndex.TabIndex = 2;
            this.m_activeCashierIndex.Text = "label3";
            // 
            // m_activeCashierName
            // 
            this.m_activeCashierName.AutoSize = true;
            this.m_activeCashierName.Location = new System.Drawing.Point(144, 45);
            this.m_activeCashierName.Name = "m_activeCashierName";
            this.m_activeCashierName.Size = new System.Drawing.Size(35, 13);
            this.m_activeCashierName.TabIndex = 3;
            this.m_activeCashierName.Text = "label4";
            // 
            // m_btnCashierLogOut
            // 
            this.m_btnCashierLogOut.Location = new System.Drawing.Point(301, 40);
            this.m_btnCashierLogOut.Name = "m_btnCashierLogOut";
            this.m_btnCashierLogOut.Size = new System.Drawing.Size(75, 23);
            this.m_btnCashierLogOut.TabIndex = 4;
            this.m_btnCashierLogOut.Text = "Çıkış Yap";
            this.m_btnCashierLogOut.UseVisualStyleBackColor = true;
            this.m_btnCashierLogOut.Click += new System.EventHandler(this.m_btnCashierLogOut_Click);
            // 
            // m_ListCashiers
            // 
            this.m_ListCashiers.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3});
            this.m_ListCashiers.FullRowSelect = true;
            this.m_ListCashiers.Location = new System.Drawing.Point(12, 81);
            this.m_ListCashiers.Name = "m_ListCashiers";
            this.m_ListCashiers.Size = new System.Drawing.Size(364, 170);
            this.m_ListCashiers.TabIndex = 5;
            this.m_ListCashiers.UseCompatibleStateImageBehavior = false;
            this.m_ListCashiers.View = System.Windows.Forms.View.Details;
            this.m_ListCashiers.SelectedIndexChanged += new System.EventHandler(this.m_ListCashiers_SelectedIndexChanged);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Index";
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Name";
            this.columnHeader2.Width = 178;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "Flag";
            this.columnHeader3.Width = 84;
            // 
            // m_btnAddCashier
            // 
            this.m_btnAddCashier.Location = new System.Drawing.Point(268, 258);
            this.m_btnAddCashier.Name = "m_btnAddCashier";
            this.m_btnAddCashier.Size = new System.Drawing.Size(107, 75);
            this.m_btnAddCashier.TabIndex = 6;
            this.m_btnAddCashier.Text = "Kasiyer Tanımla";
            this.m_btnAddCashier.UseVisualStyleBackColor = true;
            this.m_btnAddCashier.Click += new System.EventHandler(this.m_btnAddCashier_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(16, 258);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Kasiyer Index : ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(16, 287);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(71, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Kasiyer Ismi : ";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(16, 315);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(74, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Kasiyer Sifre : ";
            // 
            // m_txtCashierIndex
            // 
            this.m_txtCashierIndex.Location = new System.Drawing.Point(128, 258);
            this.m_txtCashierIndex.Name = "m_txtCashierIndex";
            this.m_txtCashierIndex.Size = new System.Drawing.Size(100, 20);
            this.m_txtCashierIndex.TabIndex = 10;
            // 
            // m_txtCashierName
            // 
            this.m_txtCashierName.Location = new System.Drawing.Point(128, 284);
            this.m_txtCashierName.Name = "m_txtCashierName";
            this.m_txtCashierName.Size = new System.Drawing.Size(100, 20);
            this.m_txtCashierName.TabIndex = 11;
            // 
            // m_txtCashierPassword
            // 
            this.m_txtCashierPassword.Location = new System.Drawing.Point(128, 310);
            this.m_txtCashierPassword.Name = "m_txtCashierPassword";
            this.m_txtCashierPassword.Size = new System.Drawing.Size(100, 20);
            this.m_txtCashierPassword.TabIndex = 12;
            // 
            // CashierForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(388, 345);
            this.Controls.Add(this.m_txtCashierPassword);
            this.Controls.Add(this.m_txtCashierName);
            this.Controls.Add(this.m_txtCashierIndex);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.m_btnAddCashier);
            this.Controls.Add(this.m_ListCashiers);
            this.Controls.Add(this.m_btnCashierLogOut);
            this.Controls.Add(this.m_activeCashierName);
            this.Controls.Add(this.m_activeCashierIndex);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "CashierForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Kasiyer";
            this.Load += new System.EventHandler(this.CashierForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label m_activeCashierIndex;
        private System.Windows.Forms.Label m_activeCashierName;
        private System.Windows.Forms.Button m_btnCashierLogOut;
        private System.Windows.Forms.ListView m_ListCashiers;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.Button m_btnAddCashier;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox m_txtCashierIndex;
        private System.Windows.Forms.TextBox m_txtCashierName;
        private System.Windows.Forms.TextBox m_txtCashierPassword;
    }
}