using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using System.IO;
using System.Diagnostics;
using System.Configuration;

namespace BotStudio
{
	public partial class BotTemplatesForm : DockContent
	{
		private BotTemplateList FBotTplList;



		void OnTemplateListUpdate()
		{
			UpdateFromList();
		}
		public BotTemplatesForm(BotTemplateList BotTplList)
		{
			InitializeComponent();

			FBotTplList = BotTplList;
			FBotTplList.OnUpdate += OnTemplateListUpdate;
		}

		private void BotTemplatesForm_Load(object sender, EventArgs e)
		{
			UpdateFromList();
		}

		private void UpdateFromList()
		{
			TemplateTree.Nodes.Clear();

			UpdateNode(null, FBotTplList.RootNode);
		}
		private void UpdateNode(TreeNode TreeRoot, BotTemplateList.Node node)
		{
			if(node == null)
				return;

			TreeNode TreeNode = new TreeNode();
			TreeNode.Text = Path.GetFileNameWithoutExtension(node.Value);
			TreeNode.Tag = node;

			if (node.Type == BotTemplateList.Node.NodeType.type_file)
			{
				TreeNode.ImageIndex = 0;
				TreeNode.SelectedImageIndex = 0;
			}
			else
			{
				TreeNode.ImageIndex = 1;
				TreeNode.SelectedImageIndex = 1;
			}

			if (TreeRoot == null)
			{
				TemplateTree.Nodes.Add(TreeNode);
			}
			else
			{
				TreeRoot.Nodes.Add(TreeNode);
			}

			foreach (BotTemplateList.Node child in node.Children)
			{
				UpdateNode(TreeNode, child);
			}
		}
	
		private void refreshToolStripMenuItem_Click(object sender, EventArgs e)
		{
			FBotTplList.Update();
		}

		private void BotTplMenu_Opening(object sender, CancelEventArgs e)
		{
			TreeNode node = TemplateTree.SelectedNode;

			editBotMenuItem.Enabled = false;
			refreshToolStripMenuItem.Enabled = true;
			runToolStripMenuItem.Enabled = false;
			openFolderToolStripMenuItem.Enabled = false;

			if (node == null)
			{
				runToolStripMenuItem.Enabled = false;
				return;
			}

			BotTemplateList.Node botNode = (BotTemplateList.Node)node.Tag;

			if (botNode.Type == BotTemplateList.Node.NodeType.type_file)
			{
				runToolStripMenuItem.Enabled = true;
				editBotMenuItem.Enabled = true;
			}
			if (botNode.Type == BotTemplateList.Node.NodeType.type_folder)
			{
				openFolderToolStripMenuItem.Enabled = true;
			}
			
		}
		private string GetNodeValue(TreeNode node)
		{
			BotTemplateList.Node BotNode = (BotTemplateList.Node)node.Tag;

			return BotNode.Value;
		}
		private void openFolderToolStripMenuItem_Click(object sender, EventArgs e)
		{
			TreeNode node = TemplateTree.SelectedNode;
			if (node != null)
			{
				string fullPath = Path.GetFullPath(GetNodeValue(node));

				Process.Start("Explorer.exe", fullPath);
			}
		}

		private void runToolStripMenuItem_Click(object sender, EventArgs e)
		{
			TreeNode node = TemplateTree.SelectedNode;

			if (node != null)
			{
				BotPropDlg dlg = new BotPropDlg((string)GetNodeValue(node));
				dlg.ShowDialog(this.Parent);

				if (dlg.DialogResult == DialogResult.OK)
				{
					AppContext.BotList.AddBot(dlg.BotDesc);
				}
			}
		}

		private void TemplateTree_ItemDrag(object sender, ItemDragEventArgs e)
		{
			TreeNode node = TemplateTree.SelectedNode;

			if(node == null)
				return;

			BotTemplateList.Node BotNode = (BotTemplateList.Node)node.Tag;
			if(BotNode.Type != BotTemplateList.Node.NodeType.type_file)
				return;

			if(e.Button != MouseButtons.Left)
				return;

			DoDragDrop(BotNode.Value, DragDropEffects.Copy);
		}

		private void TemplateTree_MouseDown(object sender, MouseEventArgs e)
		{
			Point l = e.Location;
			l.Offset(TemplateTree.ClientRectangle.X, TemplateTree.ClientRectangle.Y);

			TreeViewHitTestInfo info = TemplateTree.HitTest(l.X, l.Y);

			TemplateTree.SelectedNode = info.Node;
		}

		private void editBotMenuItem_Click(object sender, EventArgs e)
		{
			TreeNode node = TemplateTree.SelectedNode;

			if (node != null)
			{
				string file = GetNodeValue(node);

				try
				{
					Process.Start(ConfigurationManager.AppSettings["BotEditor"], file);
				}
				catch (Exception ex)
				{
					MessageBox.Show(ex.Message);
				}
			}
		}
	}
}
