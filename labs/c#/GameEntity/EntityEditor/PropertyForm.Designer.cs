﻿namespace EntityEditor
{
	partial class PropertyForm
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
			this.propGrid = new System.Windows.Forms.PropertyGrid();
			this.SuspendLayout();
			// 
			// propGrid
			// 
			this.propGrid.Dock = System.Windows.Forms.DockStyle.Fill;
			this.propGrid.Location = new System.Drawing.Point(0, 0);
			this.propGrid.Name = "propGrid";
			this.propGrid.Size = new System.Drawing.Size(628, 585);
			this.propGrid.TabIndex = 0;
			// 
			// PropertyForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(628, 585);
			this.Controls.Add(this.propGrid);
			this.Name = "PropertyForm";
			this.Text = "PropertyForm";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.PropertyGrid propGrid;
	}
}