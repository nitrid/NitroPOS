namespace GmpSampleSim
{
    partial class PassForm
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
            this.m_txtGetPass = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.m_btnSendPass = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // m_txtGetPass
            // 
            this.m_txtGetPass.Location = new System.Drawing.Point(205, 18);
            this.m_txtGetPass.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_txtGetPass.Name = "m_txtGetPass";
            this.m_txtGetPass.Size = new System.Drawing.Size(132, 22);
            this.m_txtGetPass.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(29, 22);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(113, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Yonetici Sifresi : ";
            // 
            // m_btnSendPass
            // 
            this.m_btnSendPass.Location = new System.Drawing.Point(205, 63);
            this.m_btnSendPass.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.m_btnSendPass.Name = "m_btnSendPass";
            this.m_btnSendPass.Size = new System.Drawing.Size(133, 28);
            this.m_btnSendPass.TabIndex = 2;
            this.m_btnSendPass.Text = "Gönder";
            this.m_btnSendPass.UseVisualStyleBackColor = true;
            this.m_btnSendPass.Click += new System.EventHandler(this.m_btnSendPass_Click);
            // 
            // PassForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(363, 101);
            this.Controls.Add(this.m_btnSendPass);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.m_txtGetPass);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "PassForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Sifre Giris Ekranı";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox m_txtGetPass;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button m_btnSendPass;
    }
}