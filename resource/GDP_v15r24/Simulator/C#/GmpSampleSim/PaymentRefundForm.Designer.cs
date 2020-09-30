namespace GmpSampleSim
{
    partial class PaymentRefundForm
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
            this.m_listPaymentRefund = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // m_listPaymentRefund
            // 
            this.m_listPaymentRefund.FormattingEnabled = true;
            this.m_listPaymentRefund.ItemHeight = 16;
            this.m_listPaymentRefund.Location = new System.Drawing.Point(17, 16);
            this.m_listPaymentRefund.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_listPaymentRefund.Name = "m_listPaymentRefund";
            this.m_listPaymentRefund.Size = new System.Drawing.Size(521, 484);
            this.m_listPaymentRefund.TabIndex = 0;
            this.m_listPaymentRefund.SelectedIndexChanged += new System.EventHandler(this.m_listPaymentRefund_SelectedIndexChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(430, 508);
            this.button1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(100, 28);
            this.button1.TabIndex = 1;
            this.button1.Text = "Tamamla";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // PaymentRefundForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(543, 549);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.m_listPaymentRefund);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "PaymentRefundForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PaymentRefundForm";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox m_listPaymentRefund;
        private System.Windows.Forms.Button button1;
    }
}