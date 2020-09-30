namespace GmpSampleSim
{
    partial class TimeChangerForm
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
            this.textBoxDateChanger = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxTimeChanger = new System.Windows.Forms.TextBox();
            this.buttonChangeTime = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(27, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(30, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Date";
            // 
            // textBoxDateChanger
            // 
            this.textBoxDateChanger.Location = new System.Drawing.Point(77, 20);
            this.textBoxDateChanger.Name = "textBoxDateChanger";
            this.textBoxDateChanger.Size = new System.Drawing.Size(189, 20);
            this.textBoxDateChanger.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(27, 52);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Time";
            // 
            // textBoxTimeChanger
            // 
            this.textBoxTimeChanger.Location = new System.Drawing.Point(77, 52);
            this.textBoxTimeChanger.Name = "textBoxTimeChanger";
            this.textBoxTimeChanger.Size = new System.Drawing.Size(189, 20);
            this.textBoxTimeChanger.TabIndex = 3;
            // 
            // buttonChangeTime
            // 
            this.buttonChangeTime.Location = new System.Drawing.Point(133, 90);
            this.buttonChangeTime.Name = "buttonChangeTime";
            this.buttonChangeTime.Size = new System.Drawing.Size(75, 23);
            this.buttonChangeTime.TabIndex = 4;
            this.buttonChangeTime.Text = "OK";
            this.buttonChangeTime.UseVisualStyleBackColor = true;
            this.buttonChangeTime.Click += new System.EventHandler(this.buttonChangeTime_Click);
            // 
            // TimeChangerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(358, 134);
            this.Controls.Add(this.buttonChangeTime);
            this.Controls.Add(this.textBoxTimeChanger);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxDateChanger);
            this.Controls.Add(this.label1);
            this.Name = "TimeChangerForm";
            this.Text = "TimeChangerForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxDateChanger;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxTimeChanger;
        private System.Windows.Forms.Button buttonChangeTime;
    }
}