namespace BotStudio
{
	partial class NewBotDlg
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
			this.label2 = new System.Windows.Forms.Label();
			this.silencedBox = new System.Windows.Forms.CheckBox();
			this.countBox = new System.Windows.Forms.NumericUpDown();
			this.OK_Button = new System.Windows.Forms.Button();
			this.Cancel_Button = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this.nameBox = new System.Windows.Forms.TextBox();
			this.hostAddrBox = new IPAddressControlLib.IPAddressControl();
			this.label4 = new System.Windows.Forms.Label();
			this.portBox = new System.Windows.Forms.NumericUpDown();
			((System.ComponentModel.ISupportInitialize)(this.countBox)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.portBox)).BeginInit();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(30, 88);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(35, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "Count";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(29, 49);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(29, 12);
			this.label2.TabIndex = 1;
			this.label2.Text = "Addr";
			// 
			// silencedBox
			// 
			this.silencedBox.AutoSize = true;
			this.silencedBox.Location = new System.Drawing.Point(34, 171);
			this.silencedBox.Name = "silencedBox";
			this.silencedBox.Size = new System.Drawing.Size(96, 16);
			this.silencedBox.TabIndex = 7;
			this.silencedBox.Text = "Silence Mode";
			this.silencedBox.UseVisualStyleBackColor = true;
			// 
			// countBox
			// 
			this.countBox.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
			this.countBox.Location = new System.Drawing.Point(80, 85);
			this.countBox.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
			this.countBox.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.countBox.Name = "countBox";
			this.countBox.Size = new System.Drawing.Size(120, 21);
			this.countBox.TabIndex = 9;
			this.countBox.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
			// 
			// OK_Button
			// 
			this.OK_Button.Location = new System.Drawing.Point(31, 221);
			this.OK_Button.Name = "OK_Button";
			this.OK_Button.Size = new System.Drawing.Size(75, 23);
			this.OK_Button.TabIndex = 11;
			this.OK_Button.Text = "OK";
			this.OK_Button.UseVisualStyleBackColor = true;
			this.OK_Button.Click += new System.EventHandler(this.OKButton_Click);
			// 
			// Cancel_Button
			// 
			this.Cancel_Button.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.Cancel_Button.Location = new System.Drawing.Point(128, 221);
			this.Cancel_Button.Name = "Cancel_Button";
			this.Cancel_Button.Size = new System.Drawing.Size(75, 23);
			this.Cancel_Button.TabIndex = 12;
			this.Cancel_Button.Text = "Cancel";
			this.Cancel_Button.UseVisualStyleBackColor = true;
			this.Cancel_Button.Click += new System.EventHandler(this.CancelButton_Click);
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(29, 16);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(29, 12);
			this.label3.TabIndex = 14;
			this.label3.Text = "Name";
			// 
			// nameBox
			// 
			this.nameBox.Location = new System.Drawing.Point(80, 12);
			this.nameBox.Name = "nameBox";
			this.nameBox.Size = new System.Drawing.Size(123, 21);
			this.nameBox.TabIndex = 15;
			// 
			// hostAddrBox
			// 
			this.hostAddrBox.AllowInternalTab = false;
			this.hostAddrBox.AutoHeight = true;
			this.hostAddrBox.BackColor = System.Drawing.SystemColors.Window;
			this.hostAddrBox.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.hostAddrBox.Cursor = System.Windows.Forms.Cursors.IBeam;
			this.hostAddrBox.Location = new System.Drawing.Point(80, 46);
			this.hostAddrBox.MinimumSize = new System.Drawing.Size(96, 21);
			this.hostAddrBox.Name = "hostAddrBox";
			this.hostAddrBox.ReadOnly = false;
			this.hostAddrBox.Size = new System.Drawing.Size(123, 21);
			this.hostAddrBox.TabIndex = 16;
			this.hostAddrBox.Text = "...";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(32, 122);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(29, 12);
			this.label4.TabIndex = 17;
			this.label4.Text = "Port";
			// 
			// portBox
			// 
			this.portBox.Location = new System.Drawing.Point(80, 118);
			this.portBox.Maximum = new decimal(new int[] {
            999999,
            0,
            0,
            0});
			this.portBox.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.portBox.Name = "portBox";
			this.portBox.Size = new System.Drawing.Size(120, 21);
			this.portBox.TabIndex = 18;
			this.portBox.Value = new decimal(new int[] {
            9118,
            0,
            0,
            0});
			// 
			// NewBotDlg
			// 
			this.AcceptButton = this.OK_Button;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.Cancel_Button;
			this.ClientSize = new System.Drawing.Size(249, 259);
			this.Controls.Add(this.portBox);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.hostAddrBox);
			this.Controls.Add(this.nameBox);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.Cancel_Button);
			this.Controls.Add(this.OK_Button);
			this.Controls.Add(this.countBox);
			this.Controls.Add(this.silencedBox);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "NewBotDlg";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "NewBotDlg";
			this.Load += new System.EventHandler(this.NewBotDlg_Load);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.NewBotDlg_FormClosed);
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.NewBotDlg_FormClosing);
			((System.ComponentModel.ISupportInitialize)(this.countBox)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.portBox)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.CheckBox silencedBox;
		private System.Windows.Forms.NumericUpDown countBox;
		private System.Windows.Forms.Button OK_Button;
		private System.Windows.Forms.Button Cancel_Button;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox nameBox;
		private IPAddressControlLib.IPAddressControl hostAddrBox;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.NumericUpDown portBox;
	}
}