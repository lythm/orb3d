namespace BotStudio
{
	partial class OutputForm
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
			this.components = new System.ComponentModel.Container();
			this.FLogTextBox = new System.Windows.Forms.TextBox();
			this.outputTextContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.clearToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.outputTextContextMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// FLogTextBox
			// 
			this.FLogTextBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.FLogTextBox.ContextMenuStrip = this.outputTextContextMenu;
			this.FLogTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.FLogTextBox.Location = new System.Drawing.Point(0, 0);
			this.FLogTextBox.Multiline = true;
			this.FLogTextBox.Name = "FLogTextBox";
			this.FLogTextBox.ReadOnly = true;
			this.FLogTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.FLogTextBox.Size = new System.Drawing.Size(630, 472);
			this.FLogTextBox.TabIndex = 0;
			// 
			// outputTextContextMenu
			// 
			this.outputTextContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.clearToolStripMenuItem});
			this.outputTextContextMenu.Name = "outputTextContextMenu";
			this.outputTextContextMenu.Size = new System.Drawing.Size(107, 26);
			// 
			// clearToolStripMenuItem
			// 
			this.clearToolStripMenuItem.Name = "clearToolStripMenuItem";
			this.clearToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
			this.clearToolStripMenuItem.Text = "Clear";
			this.clearToolStripMenuItem.Click += new System.EventHandler(this.clearToolStripMenuItem_Click);
			// 
			// OutputForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(630, 472);
			this.Controls.Add(this.FLogTextBox);
			this.DockAreas = ((WeifenLuo.WinFormsUI.Docking.DockAreas)((WeifenLuo.WinFormsUI.Docking.DockAreas.DockBottom | WeifenLuo.WinFormsUI.Docking.DockAreas.Document)));
			this.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.HideOnClose = true;
			this.Name = "OutputForm";
			this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockBottom;
			this.Text = "OutputForm";
			this.outputTextContextMenu.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox FLogTextBox;
		private System.Windows.Forms.ContextMenuStrip outputTextContextMenu;
		private System.Windows.Forms.ToolStripMenuItem clearToolStripMenuItem;
	}
}