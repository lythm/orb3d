namespace BotStudio
{
	partial class BotListForm
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
			System.Windows.Forms.ColumnHeader nameHeader;
			System.Windows.Forms.ColumnHeader countHeader;
			System.Windows.Forms.ColumnHeader silencedHeader;
			System.Windows.Forms.ColumnHeader hostHeader;
			System.Windows.Forms.ColumnHeader stateHeader;
			System.Windows.Forms.ColumnHeader scriptHeader;
			this.botListContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.runToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.restartMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.stopToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.modifyMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.removeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.refreshListToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
			this.botCommand = new System.Windows.Forms.ToolStripMenuItem();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.BotList = new System.Windows.Forms.ListView();
			nameHeader = new System.Windows.Forms.ColumnHeader();
			countHeader = new System.Windows.Forms.ColumnHeader();
			silencedHeader = new System.Windows.Forms.ColumnHeader();
			hostHeader = new System.Windows.Forms.ColumnHeader();
			stateHeader = new System.Windows.Forms.ColumnHeader();
			scriptHeader = new System.Windows.Forms.ColumnHeader();
			this.botListContextMenu.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.SuspendLayout();
			// 
			// botListContextMenu
			// 
			this.botListContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.runToolStripMenuItem,
            this.restartMenuItem,
            this.stopToolStripMenuItem,
            this.toolStripSeparator1,
            this.modifyMenuItem,
            this.removeToolStripMenuItem,
            this.toolStripSeparator2,
            this.refreshListToolStripMenuItem,
            this.toolStripSeparator3,
            this.botCommand});
			this.botListContextMenu.Name = "botListContextMenu";
			this.botListContextMenu.Size = new System.Drawing.Size(163, 176);
			this.botListContextMenu.Opening += new System.ComponentModel.CancelEventHandler(this.botListContextMenu_Opening);
			// 
			// runToolStripMenuItem
			// 
			this.runToolStripMenuItem.Name = "runToolStripMenuItem";
			this.runToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
			this.runToolStripMenuItem.Text = "Run";
			this.runToolStripMenuItem.Click += new System.EventHandler(this.runToolStripMenuItem_Click);
			// 
			// restartMenuItem
			// 
			this.restartMenuItem.Name = "restartMenuItem";
			this.restartMenuItem.Size = new System.Drawing.Size(162, 22);
			this.restartMenuItem.Text = "Restart";
			this.restartMenuItem.Click += new System.EventHandler(this.restartMenuItem_Click);
			// 
			// stopToolStripMenuItem
			// 
			this.stopToolStripMenuItem.Name = "stopToolStripMenuItem";
			this.stopToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
			this.stopToolStripMenuItem.Text = "Stop";
			this.stopToolStripMenuItem.Click += new System.EventHandler(this.stopToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(159, 6);
			// 
			// modifyMenuItem
			// 
			this.modifyMenuItem.Name = "modifyMenuItem";
			this.modifyMenuItem.Size = new System.Drawing.Size(162, 22);
			this.modifyMenuItem.Text = "Modify";
			this.modifyMenuItem.Click += new System.EventHandler(this.modifyMenuItem_Click);
			// 
			// removeToolStripMenuItem
			// 
			this.removeToolStripMenuItem.Name = "removeToolStripMenuItem";
			this.removeToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
			this.removeToolStripMenuItem.Text = "Remove";
			this.removeToolStripMenuItem.Click += new System.EventHandler(this.removeToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(159, 6);
			// 
			// refreshListToolStripMenuItem
			// 
			this.refreshListToolStripMenuItem.Name = "refreshListToolStripMenuItem";
			this.refreshListToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
			this.refreshListToolStripMenuItem.Text = "RefreshList";
			this.refreshListToolStripMenuItem.Click += new System.EventHandler(this.refreshListToolStripMenuItem_Click);
			// 
			// toolStripSeparator3
			// 
			this.toolStripSeparator3.Name = "toolStripSeparator3";
			this.toolStripSeparator3.Size = new System.Drawing.Size(159, 6);
			// 
			// botCommand
			// 
			this.botCommand.Name = "botCommand";
			this.botCommand.Size = new System.Drawing.Size(162, 22);
			this.botCommand.Text = "Bot Commands";
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point(0, 0);
			this.splitContainer1.Name = "splitContainer1";
			this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
			this.splitContainer1.Size = new System.Drawing.Size(538, 475);
			this.splitContainer1.SplitterDistance = 179;
			this.splitContainer1.TabIndex = 1;
			// 
			// nameHeader
			// 
			nameHeader.Text = "Name";
			// 
			// countHeader
			// 
			countHeader.Text = "Count";
			// 
			// silencedHeader
			// 
			silencedHeader.Text = "Silenced";
			// 
			// hostHeader
			// 
			hostHeader.Text = "Host";
			hostHeader.Width = 150;
			// 
			// stateHeader
			// 
			stateHeader.Text = "state";
			stateHeader.Width = 82;
			// 
			// scriptHeader
			// 
			scriptHeader.Text = "script";
			scriptHeader.Width = 200;
			// 
			// BotList
			// 
			this.BotList.AllowDrop = true;
			this.BotList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            nameHeader,
            countHeader,
            silencedHeader,
            hostHeader,
            stateHeader,
            scriptHeader});
			this.BotList.ContextMenuStrip = this.botListContextMenu;
			this.BotList.Dock = System.Windows.Forms.DockStyle.Fill;
			this.BotList.FullRowSelect = true;
			this.BotList.GridLines = true;
			this.BotList.Location = new System.Drawing.Point(0, 0);
			this.BotList.MultiSelect = false;
			this.BotList.Name = "BotList";
			this.BotList.Size = new System.Drawing.Size(538, 475);
			this.BotList.TabIndex = 0;
			this.BotList.UseCompatibleStateImageBehavior = false;
			this.BotList.View = System.Windows.Forms.View.Details;
			this.BotList.ItemActivate += new System.EventHandler(this.BotList_ItemActivate);
			this.BotList.DragDrop += new System.Windows.Forms.DragEventHandler(this.BotList_DragDrop);
			this.BotList.DragEnter += new System.Windows.Forms.DragEventHandler(this.BostList_DragEnter);
			// 
			// BotListForm
			// 
			this.AllowDrop = true;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(538, 475);
			this.Controls.Add(this.BotList);
			this.Controls.Add(this.splitContainer1);
			this.DoubleBuffered = true;
			this.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.Name = "BotListForm";
			this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.Document;
			this.Text = "BotListForm";
			this.Load += new System.EventHandler(this.BotListForm_Load);
			this.botListContextMenu.ResumeLayout(false);
			this.splitContainer1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ContextMenuStrip botListContextMenu;
		private System.Windows.Forms.ToolStripMenuItem runToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem removeToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripMenuItem refreshListToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem modifyMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
		private System.Windows.Forms.ToolStripMenuItem botCommand;
		private System.Windows.Forms.ToolStripMenuItem restartMenuItem;
		private System.Windows.Forms.SplitContainer splitContainer1;
		private System.Windows.Forms.ListView BotList;
	}
}