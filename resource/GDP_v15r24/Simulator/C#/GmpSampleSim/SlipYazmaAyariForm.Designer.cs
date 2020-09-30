namespace GmpSampleSim
{
    partial class SlipYazmaAyariForm
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
            this.radioButtonActive = new System.Windows.Forms.RadioButton();
            this.radioButtonPassive = new System.Windows.Forms.RadioButton();
            this.buttonOK = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // radioButtonActive
            // 
            this.radioButtonActive.AutoSize = true;
            this.radioButtonActive.Location = new System.Drawing.Point(12, 24);
            this.radioButtonActive.Name = "radioButtonActive";
            this.radioButtonActive.Size = new System.Drawing.Size(109, 17);
            this.radioButtonActive.TabIndex = 0;
            this.radioButtonActive.TabStop = true;
            this.radioButtonActive.Text = "Slip yazdırma açık";
            this.radioButtonActive.UseVisualStyleBackColor = true;
            // 
            // radioButtonPassive
            // 
            this.radioButtonPassive.AutoSize = true;
            this.radioButtonPassive.Location = new System.Drawing.Point(12, 47);
            this.radioButtonPassive.Name = "radioButtonPassive";
            this.radioButtonPassive.Size = new System.Drawing.Size(117, 17);
            this.radioButtonPassive.TabIndex = 1;
            this.radioButtonPassive.TabStop = true;
            this.radioButtonPassive.Text = "Slip yazdırma kapalı";
            this.radioButtonPassive.UseVisualStyleBackColor = true;
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(86, 83);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 2;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // SlipYazmaAyariForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(272, 118);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.radioButtonPassive);
            this.Controls.Add(this.radioButtonActive);
            this.Name = "SlipYazmaAyariForm";
            this.Text = "Slip Yazma Ayarı";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton radioButtonActive;
        private System.Windows.Forms.RadioButton radioButtonPassive;
        private System.Windows.Forms.Button buttonOK;
    }
}