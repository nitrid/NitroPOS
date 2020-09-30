namespace GmpSampleSim
{
    partial class PaymentForm
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
            this.m_listPayment = new System.Windows.Forms.ListView();
            this.m_listBankPayment = new System.Windows.Forms.ListView();
            this.SuspendLayout();
            // 
            // m_listPayment
            // 
            this.m_listPayment.Location = new System.Drawing.Point(12, 13);
            this.m_listPayment.Name = "m_listPayment";
            this.m_listPayment.Size = new System.Drawing.Size(756, 178);
            this.m_listPayment.TabIndex = 0;
            this.m_listPayment.UseCompatibleStateImageBehavior = false;
            this.m_listPayment.View = System.Windows.Forms.View.Details;
            this.m_listPayment.SelectedIndexChanged += new System.EventHandler(this.m_listPayment_SelectedIndexChanged);
            // 
            // m_listBankPayment
            // 
            this.m_listBankPayment.Location = new System.Drawing.Point(12, 211);
            this.m_listBankPayment.Name = "m_listBankPayment";
            this.m_listBankPayment.Size = new System.Drawing.Size(756, 191);
            this.m_listBankPayment.TabIndex = 1;
            this.m_listBankPayment.UseCompatibleStateImageBehavior = false;
            this.m_listBankPayment.View = System.Windows.Forms.View.Details;
            // 
            // PaymentForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(780, 414);
            this.Controls.Add(this.m_listBankPayment);
            this.Controls.Add(this.m_listPayment);
            this.Name = "PaymentForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PaymentForm";
            this.Load += new System.EventHandler(this.PaymentForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView m_listBankPayment;
        public System.Windows.Forms.ListView m_listPayment;

    }
}