namespace GmpSampleSim
{
    partial class PaymentTypeForm
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
            this.m_listPaymentTypes = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // m_listPaymentTypes
            // 
            this.m_listPaymentTypes.FormattingEnabled = true;
            this.m_listPaymentTypes.Location = new System.Drawing.Point(12, 12);
            this.m_listPaymentTypes.Name = "m_listPaymentTypes";
            this.m_listPaymentTypes.Size = new System.Drawing.Size(260, 186);
            this.m_listPaymentTypes.TabIndex = 0;
            this.m_listPaymentTypes.SelectedIndexChanged += new System.EventHandler(this.m_listPaymentTypes_SelectedIndexChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(197, 227);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Tamamla";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // PaymentTypeForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.m_listPaymentTypes);
            this.Name = "PaymentTypeForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PaymentTypeForm";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox m_listPaymentTypes;
        private System.Windows.Forms.Button button1;
    }
}