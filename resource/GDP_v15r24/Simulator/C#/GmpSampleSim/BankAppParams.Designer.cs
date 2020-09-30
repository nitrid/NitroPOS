namespace GmpSampleSim
{
    partial class BankAppParams
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
            this._m_chcAskForMissingInputs = new System.Windows.Forms.CheckBox();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // _m_chcAskForMissingInputs
            // 
            this._m_chcAskForMissingInputs.AutoSize = true;
            this._m_chcAskForMissingInputs.Location = new System.Drawing.Point(13, 13);
            this._m_chcAskForMissingInputs.Margin = new System.Windows.Forms.Padding(4);
            this._m_chcAskForMissingInputs.Name = "_m_chcAskForMissingInputs";
            this._m_chcAskForMissingInputs.Size = new System.Drawing.Size(265, 21);
            this._m_chcAskForMissingInputs.TabIndex = 5;
            this._m_chcAskForMissingInputs.Text = "ASK FOR MISSING REFUND INPUTS";
            this._m_chcAskForMissingInputs.UseVisualStyleBackColor = true;
            this._m_chcAskForMissingInputs.CheckedChanged += new System.EventHandler(this._m_chcAskForMissingInputs_CheckedChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(145, 279);
            this.button1.Margin = new System.Windows.Forms.Padding(4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(100, 28);
            this.button1.TabIndex = 6;
            this.button1.Text = "Tamam";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // BankAppParams
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(379, 322);
            this.Controls.Add(this.button1);
            this.Controls.Add(this._m_chcAskForMissingInputs);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "BankAppParams";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "BankAppParams";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox _m_chcAskForMissingInputs;
        private System.Windows.Forms.Button button1;
    }
}