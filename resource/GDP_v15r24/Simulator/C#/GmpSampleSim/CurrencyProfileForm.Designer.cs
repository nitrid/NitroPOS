namespace GmpSampleSim
{
    partial class CurrencyProfileForm
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
            this.dataGridViewCurrencyProfile = new System.Windows.Forms.DataGridView();
            this.CurrencyCode = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Sign = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Prefix = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ThousandSeperator = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CentSeperator = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.NumberOfCentDigit = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Rate = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.comboBoxCurrencyProfile = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonNew = new System.Windows.Forms.Button();
            this.buttonRowAdd = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCurrencyProfile)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewCurrencyProfile
            // 
            this.dataGridViewCurrencyProfile.AllowUserToAddRows = false;
            this.dataGridViewCurrencyProfile.AllowUserToDeleteRows = false;
            this.dataGridViewCurrencyProfile.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridViewCurrencyProfile.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewCurrencyProfile.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewCurrencyProfile.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.CurrencyCode,
            this.Sign,
            this.Prefix,
            this.ThousandSeperator,
            this.CentSeperator,
            this.NumberOfCentDigit,
            this.Rate});
            this.dataGridViewCurrencyProfile.Location = new System.Drawing.Point(21, 40);
            this.dataGridViewCurrencyProfile.Name = "dataGridViewCurrencyProfile";
            this.dataGridViewCurrencyProfile.Size = new System.Drawing.Size(738, 249);
            this.dataGridViewCurrencyProfile.TabIndex = 0;
            this.dataGridViewCurrencyProfile.CellEndEdit += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewCurrencyProfile_CellEndEdit);
            this.dataGridViewCurrencyProfile.UserDeletedRow += new System.Windows.Forms.DataGridViewRowEventHandler(this.dataGridViewCurrencyProfile_UserDeletedRow);
            // 
            // CurrencyCode
            // 
            this.CurrencyCode.HeaderText = "Currency Code";
            this.CurrencyCode.Name = "CurrencyCode";
            // 
            // Sign
            // 
            this.Sign.HeaderText = "Sign";
            this.Sign.Name = "Sign";
            // 
            // Prefix
            // 
            this.Prefix.HeaderText = "Prefix";
            this.Prefix.Name = "Prefix";
            // 
            // ThousandSeperator
            // 
            this.ThousandSeperator.HeaderText = "Thousand Seperator";
            this.ThousandSeperator.Name = "ThousandSeperator";
            // 
            // CentSeperator
            // 
            this.CentSeperator.HeaderText = "Cent Seperator";
            this.CentSeperator.Name = "CentSeperator";
            // 
            // NumberOfCentDigit
            // 
            this.NumberOfCentDigit.HeaderText = "# Cent Digit";
            this.NumberOfCentDigit.Name = "NumberOfCentDigit";
            // 
            // Rate
            // 
            this.Rate.HeaderText = "Rate";
            this.Rate.Name = "Rate";
            // 
            // comboBoxCurrencyProfile
            // 
            this.comboBoxCurrencyProfile.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxCurrencyProfile.FormattingEnabled = true;
            this.comboBoxCurrencyProfile.Location = new System.Drawing.Point(115, 13);
            this.comboBoxCurrencyProfile.Name = "comboBoxCurrencyProfile";
            this.comboBoxCurrencyProfile.Size = new System.Drawing.Size(249, 21);
            this.comboBoxCurrencyProfile.TabIndex = 1;
            this.comboBoxCurrencyProfile.SelectedIndexChanged += new System.EventHandler(this.comboBoxCurrencyProfile_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(18, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(79, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Profile Name";
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(375, 12);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(75, 23);
            this.buttonSave.TabIndex = 3;
            this.buttonSave.Text = "Save";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(537, 13);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(75, 23);
            this.buttonDelete.TabIndex = 4;
            this.buttonDelete.Text = "Delete";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // buttonNew
            // 
            this.buttonNew.Location = new System.Drawing.Point(456, 12);
            this.buttonNew.Name = "buttonNew";
            this.buttonNew.Size = new System.Drawing.Size(75, 23);
            this.buttonNew.TabIndex = 5;
            this.buttonNew.Text = "New";
            this.buttonNew.UseVisualStyleBackColor = true;
            this.buttonNew.Click += new System.EventHandler(this.buttonNew_Click);
            // 
            // buttonRowAdd
            // 
            this.buttonRowAdd.Location = new System.Drawing.Point(619, 13);
            this.buttonRowAdd.Name = "buttonRowAdd";
            this.buttonRowAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonRowAdd.TabIndex = 6;
            this.buttonRowAdd.Text = "Add Row";
            this.buttonRowAdd.UseVisualStyleBackColor = true;
            this.buttonRowAdd.Click += new System.EventHandler(this.buttonRowAdd_Click);
            // 
            // CurrencyProfileForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(761, 293);
            this.Controls.Add(this.buttonRowAdd);
            this.Controls.Add(this.buttonNew);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBoxCurrencyProfile);
            this.Controls.Add(this.dataGridViewCurrencyProfile);
            this.Name = "CurrencyProfileForm";
            this.Text = "Currency Profile Form";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCurrencyProfile)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewCurrencyProfile;
        private System.Windows.Forms.ComboBox comboBoxCurrencyProfile;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.DataGridViewTextBoxColumn CurrencyCode;
        private System.Windows.Forms.DataGridViewTextBoxColumn Sign;
        private System.Windows.Forms.DataGridViewTextBoxColumn Prefix;
        private System.Windows.Forms.DataGridViewTextBoxColumn ThousandSeperator;
        private System.Windows.Forms.DataGridViewTextBoxColumn CentSeperator;
        private System.Windows.Forms.DataGridViewTextBoxColumn NumberOfCentDigit;
        private System.Windows.Forms.DataGridViewTextBoxColumn Rate;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonNew;
        private System.Windows.Forms.Button buttonRowAdd;
    }
}