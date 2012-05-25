namespace BotStudio
{
	partial class BotPropDlg
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
			this.OK_Button = new System.Windows.Forms.Button();
			this.Cancel_Button = new System.Windows.Forms.Button();
			this.propGrid = new System.Windows.Forms.PropertyGrid();
			this.SuspendLayout();
			// 
			// OK_Button
			// 
			this.OK_Button.Location = new System.Drawing.Point(83, 413);
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
			this.Cancel_Button.Location = new System.Drawing.Point(325, 413);
			this.Cancel_Button.Name = "Cancel_Button";
			this.Cancel_Button.Size = new System.Drawing.Size(75, 23);
			this.Cancel_Button.TabIndex = 12;
			this.Cancel_Button.Text = "Cancel";
			this.Cancel_Button.UseVisualStyleBackColor = true;
			this.Cancel_Button.Click += new System.EventHandler(this.CancelButton_Click);
			// 
			// propGrid
			// 
			this.propGrid.Dock = System.Windows.Forms.DockStyle.Top;
			this.propGrid.Location = new System.Drawing.Point(0, 0);
			this.propGrid.Name = "propGrid";
			this.propGrid.PropertySort = System.Windows.Forms.PropertySort.NoSort;
			this.propGrid.Size = new System.Drawing.Size(493, 395);
			this.propGrid.TabIndex = 19;
			// 
			// BotPropDlg
			// 
			this.AcceptButton = this.OK_Button;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.Cancel_Button;
			this.ClientSize = new System.Drawing.Size(493, 449);
			this.Controls.Add(this.propGrid);
			this.Controls.Add(this.Cancel_Button);
			this.Controls.Add(this.OK_Button);
			this.DoubleBuffered = true;
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "BotPropDlg";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Bot Property";
			this.Load += new System.EventHandler(this.NewBotDlg_Load);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.NewBotDlg_FormClosed);
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.NewBotDlg_FormClosing);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button OK_Button;
		private System.Windows.Forms.Button Cancel_Button;
		private System.Windows.Forms.PropertyGrid propGrid;
	}
}