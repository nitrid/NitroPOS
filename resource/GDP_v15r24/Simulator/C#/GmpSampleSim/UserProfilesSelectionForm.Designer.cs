namespace GmpSampleSim
{
    partial class FormProfilesSelection
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
            this.flowLayoutPanelForProfiles = new System.Windows.Forms.FlowLayoutPanel();
            this.buttonProfileSelection = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // flowLayoutPanelForProfiles
            // 
            this.flowLayoutPanelForProfiles.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.flowLayoutPanelForProfiles.Location = new System.Drawing.Point(12, 12);
            this.flowLayoutPanelForProfiles.Name = "flowLayoutPanelForProfiles";
            this.flowLayoutPanelForProfiles.Size = new System.Drawing.Size(252, 127);
            this.flowLayoutPanelForProfiles.TabIndex = 0;
            // 
            // buttonProfileSelection
            // 
            this.buttonProfileSelection.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.buttonProfileSelection.Location = new System.Drawing.Point(99, 145);
            this.buttonProfileSelection.Name = "buttonProfileSelection";
            this.buttonProfileSelection.Size = new System.Drawing.Size(75, 23);
            this.buttonProfileSelection.TabIndex = 1;
            this.buttonProfileSelection.Text = "OK";
            this.buttonProfileSelection.UseVisualStyleBackColor = true;
            this.buttonProfileSelection.Click += new System.EventHandler(this.buttonProfileSelection_Click);
            // 
            // FormProfilesSelection
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(276, 171);
            this.Controls.Add(this.buttonProfileSelection);
            this.Controls.Add(this.flowLayoutPanelForProfiles);
            this.Name = "FormProfilesSelection";
            this.Text = "Profile Selection";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanelForProfiles;
        private System.Windows.Forms.Button buttonProfileSelection;
    }
}