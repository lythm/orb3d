namespace DT_Excel_2007
{
    partial class SetupForm
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
			this.assetsPathEdit = new System.Windows.Forms.TextBox();
			this.assetsBrowseButton = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.okButton = new System.Windows.Forms.Button();
			this.cancelButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// assetsPathEdit
			// 
			this.assetsPathEdit.Location = new System.Drawing.Point(71, 34);
			this.assetsPathEdit.Name = "assetsPathEdit";
			this.assetsPathEdit.Size = new System.Drawing.Size(298, 21);
			this.assetsPathEdit.TabIndex = 0;
			// 
			// assetsBrowseButton
			// 
			this.assetsBrowseButton.Location = new System.Drawing.Point(375, 34);
			this.assetsBrowseButton.Name = "assetsBrowseButton";
			this.assetsBrowseButton.Size = new System.Drawing.Size(75, 23);
			this.assetsBrowseButton.TabIndex = 1;
			this.assetsBrowseButton.Text = "浏览...";
			this.assetsBrowseButton.UseVisualStyleBackColor = true;
			this.assetsBrowseButton.Click += new System.EventHandler(this.assetsBrowseButton_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 37);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(53, 12);
			this.label1.TabIndex = 2;
			this.label1.Text = "资源目录";
			// 
			// okButton
			// 
			this.okButton.Location = new System.Drawing.Point(105, 282);
			this.okButton.Name = "okButton";
			this.okButton.Size = new System.Drawing.Size(75, 23);
			this.okButton.TabIndex = 3;
			this.okButton.Text = "OK";
			this.okButton.UseVisualStyleBackColor = true;
			this.okButton.Click += new System.EventHandler(this.OKButton_Click);
			// 
			// cancelButton
			// 
			this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.cancelButton.Location = new System.Drawing.Point(293, 280);
			this.cancelButton.Name = "cancelButton";
			this.cancelButton.Size = new System.Drawing.Size(75, 23);
			this.cancelButton.TabIndex = 4;
			this.cancelButton.Text = "Cancel";
			this.cancelButton.UseVisualStyleBackColor = true;
			// 
			// SetupForm
			// 
			this.AcceptButton = this.okButton;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(462, 317);
			this.Controls.Add(this.cancelButton);
			this.Controls.Add(this.okButton);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.assetsBrowseButton);
			this.Controls.Add(this.assetsPathEdit);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "SetupForm";
			this.Text = "设置";
			this.Load += new System.EventHandler(this.SetupForm_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox assetsPathEdit;
        private System.Windows.Forms.Button assetsBrowseButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
    }
}