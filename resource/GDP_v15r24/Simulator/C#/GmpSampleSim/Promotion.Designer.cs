namespace GmpSampleSim
{
    partial class Promotion
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
            this.m_btnAddPromotion = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.m_txtPromotionAmount = new System.Windows.Forms.TextBox();
            this.m_txtPromotionText = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // m_btnAddPromotion
            // 
            this.m_btnAddPromotion.Location = new System.Drawing.Point(245, 125);
            this.m_btnAddPromotion.Name = "m_btnAddPromotion";
            this.m_btnAddPromotion.Size = new System.Drawing.Size(120, 23);
            this.m_btnAddPromotion.TabIndex = 0;
            this.m_btnAddPromotion.Text = "Ekle";
            this.m_btnAddPromotion.UseVisualStyleBackColor = true;
            this.m_btnAddPromotion.Click += new System.EventHandler(this.m_btnAddPromotion_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(132, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Promosyon Tutarı : ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 84);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(135, 17);
            this.label2.TabIndex = 2;
            this.label2.Text = "Promosyon Mesajı : ";
            // 
            // m_txtPromotionAmount
            // 
            this.m_txtPromotionAmount.Location = new System.Drawing.Point(175, 29);
            this.m_txtPromotionAmount.Name = "m_txtPromotionAmount";
            this.m_txtPromotionAmount.Size = new System.Drawing.Size(190, 22);
            this.m_txtPromotionAmount.TabIndex = 3;
            // 
            // m_txtPromotionText
            // 
            this.m_txtPromotionText.Location = new System.Drawing.Point(175, 81);
            this.m_txtPromotionText.Name = "m_txtPromotionText";
            this.m_txtPromotionText.Size = new System.Drawing.Size(190, 22);
            this.m_txtPromotionText.TabIndex = 4;
            // 
            // Promotion
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(377, 163);
            this.Controls.Add(this.m_txtPromotionText);
            this.Controls.Add(this.m_txtPromotionAmount);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.m_btnAddPromotion);
            this.Name = "Promotion";
            this.Text = "Promotion";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button m_btnAddPromotion;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox m_txtPromotionAmount;
        private System.Windows.Forms.TextBox m_txtPromotionText;
    }
}