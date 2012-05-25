namespace BotStudio
{
	partial class BotTemplatesForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BotTemplatesForm));
			this.TemplateTree = new System.Windows.Forms.TreeView();
			this.BotTplMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.runToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.editBotMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.refreshToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.NodeImageList = new System.Windows.Forms.ImageList(this.components);
			this.BotTplMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// TemplateTree
			// 
			this.TemplateTree.ContextMenuStrip = this.BotTplMenu;
			this.TemplateTree.Dock = System.Windows.Forms.DockStyle.Fill;
			this.TemplateTree.HideSelection = false;
			this.TemplateTree.ImageIndex = 0;
			this.TemplateTree.ImageList = this.NodeImageList;
			this.TemplateTree.Location = new System.Drawing.Point(0, 0);
			this.TemplateTree.Name = "TemplateTree";
			this.TemplateTree.SelectedImageIndex = 0;
			this.TemplateTree.Size = new System.Drawing.Size(293, 592);
			this.TemplateTree.TabIndex = 0;
			this.TemplateTree.MouseDown += new System.Windows.Forms.MouseEventHandler(this.TemplateTree_MouseDown);
			this.TemplateTree.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.TemplateTree_ItemDrag);
			// 
			// BotTplMenu
			// 
			this.BotTplMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.runToolStripMenuItem,
            this.toolStripSeparator1,
            this.editBotMenuItem,
            this.openFolderToolStripMenuItem,
            this.toolStripMenuItem1,
            this.refreshToolStripMenuItem});
			this.BotTplMenu.Name = "BotTplMenu";
			this.BotTplMenu.Size = new System.Drawing.Size(147, 104);
			this.BotTplMenu.Text = "Menu";
			this.BotTplMenu.Opening += new System.ComponentModel.CancelEventHandler(this.BotTplMenu_Opening);
			// 
			// runToolStripMenuItem
			// 
			this.runToolStripMenuItem.Name = "runToolStripMenuItem";
			this.runToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
			this.runToolStripMenuItem.Text = "NewBot";
			this.runToolStripMenuItem.Click += new System.EventHandler(this.runToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(143, 6);
			// 
			// editBotMenuItem
			// 
			this.editBotMenuItem.Name = "editBotMenuItem";
			this.editBotMenuItem.Size = new System.Drawing.Size(146, 22);
			this.editBotMenuItem.Text = "Edit Bot";
			this.editBotMenuItem.Click += new System.EventHandler(this.editBotMenuItem_Click);
			// 
			// openFolderToolStripMenuItem
			// 
			this.openFolderToolStripMenuItem.Name = "openFolderToolStripMenuItem";
			this.openFolderToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
			this.openFolderToolStripMenuItem.Text = "Open Folder";
			this.openFolderToolStripMenuItem.Click += new System.EventHandler(this.openFolderToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(143, 6);
			// 
			// refreshToolStripMenuItem
			// 
			this.refreshToolStripMenuItem.Name = "refreshToolStripMenuItem";
			this.refreshToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
			this.refreshToolStripMenuItem.Text = "Refresh";
			this.refreshToolStripMenuItem.Click += new System.EventHandler(this.refreshToolStripMenuItem_Click);
			// 
			// NodeImageList
			// 
			this.NodeImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("NodeImageList.ImageStream")));
			this.NodeImageList.TransparentColor = System.Drawing.Color.Transparent;
			this.NodeImageList.Images.SetKeyName(0, "Lua.bmp");
			this.NodeImageList.Images.SetKeyName(1, "folder.bmp");
			// 
			// BotTemplatesForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(293, 592);
			this.ContextMenuStrip = this.BotTplMenu;
			this.Controls.Add(this.TemplateTree);
			this.DockAreas = ((WeifenLuo.WinFormsUI.Docking.DockAreas)((WeifenLuo.WinFormsUI.Docking.DockAreas.DockLeft | WeifenLuo.WinFormsUI.Docking.DockAreas.DockRight)));
			this.DoubleBuffered = true;
			this.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.Name = "BotTemplatesForm";
			this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockLeft;
			this.Text = "BotTemplatesForm";
			this.Load += new System.EventHandler(this.BotTemplatesForm_Load);
			this.BotTplMenu.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TreeView TemplateTree;
		private System.Windows.Forms.ImageList NodeImageList;
		private System.Windows.Forms.ContextMenuStrip BotTplMenu;
		private System.Windows.Forms.ToolStripMenuItem refreshToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem runToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem openFolderToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem editBotMenuItem;

	}
}