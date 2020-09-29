namespace GmpSampleSim
{
    partial class DBForm
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
            this.m_list_Z = new System.Windows.Forms.ListView();
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.m_listTransaction = new System.Windows.Forms.ListView();
            this.m_listItems = new System.Windows.Forms.ListView();
            this.m_lstItemDetails = new System.Windows.Forms.ListView();
            this.SuspendLayout();
            // 
            // m_list_Z
            // 
            this.m_list_Z.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4});
            this.m_list_Z.FullRowSelect = true;
            this.m_list_Z.Location = new System.Drawing.Point(13, 13);
            this.m_list_Z.Name = "m_list_Z";
            this.m_list_Z.Size = new System.Drawing.Size(1074, 97);
            this.m_list_Z.TabIndex = 0;
            this.m_list_Z.UseCompatibleStateImageBehavior = false;
            this.m_list_Z.View = System.Windows.Forms.View.Details;
            this.m_list_Z.SelectedIndexChanged += new System.EventHandler(this.m_list_Z_SelectedIndexChanged);
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Z No";
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "Fiş No";
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "EKU No";
            // 
            // m_listTransaction
            // 
            this.m_listTransaction.Location = new System.Drawing.Point(12, 131);
            this.m_listTransaction.Name = "m_listTransaction";
            this.m_listTransaction.Size = new System.Drawing.Size(1074, 97);
            this.m_listTransaction.TabIndex = 1;
            this.m_listTransaction.UseCompatibleStateImageBehavior = false;
            this.m_listTransaction.View = System.Windows.Forms.View.Details;
            this.m_listTransaction.SelectedIndexChanged += new System.EventHandler(this.m_listTransaction_SelectedIndexChanged);
            // 
            // m_listItems
            // 
            this.m_listItems.Location = new System.Drawing.Point(13, 253);
            this.m_listItems.Name = "m_listItems";
            this.m_listItems.Size = new System.Drawing.Size(1074, 97);
            this.m_listItems.TabIndex = 2;
            this.m_listItems.UseCompatibleStateImageBehavior = false;
            this.m_listItems.View = System.Windows.Forms.View.Details;
            this.m_listItems.SelectedIndexChanged += new System.EventHandler(this.m_listItems_SelectedIndexChanged);
            // 
            // m_lstItemDetails
            // 
            this.m_lstItemDetails.Location = new System.Drawing.Point(12, 376);
            this.m_lstItemDetails.Name = "m_lstItemDetails";
            this.m_lstItemDetails.Size = new System.Drawing.Size(1074, 97);
            this.m_lstItemDetails.TabIndex = 3;
            this.m_lstItemDetails.UseCompatibleStateImageBehavior = false;
            this.m_lstItemDetails.View = System.Windows.Forms.View.Details;
            // 
            // DBForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1099, 485);
            this.Controls.Add(this.m_lstItemDetails);
            this.Controls.Add(this.m_listItems);
            this.Controls.Add(this.m_listTransaction);
            this.Controls.Add(this.m_list_Z);
            this.Name = "DBForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "DBForm";
            this.Load += new System.EventHandler(this.DBForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView m_list_Z;
        private System.Windows.Forms.ListView m_listTransaction;
        private System.Windows.Forms.ListView m_listItems;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ListView m_lstItemDetails;
    }
}

