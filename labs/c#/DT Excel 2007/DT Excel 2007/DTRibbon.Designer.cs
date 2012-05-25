namespace DT_Excel_2007
{
    partial class DTRibbon : Microsoft.Office.Tools.Ribbon.RibbonBase
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        public DTRibbon()
            : base(Globals.Factory.GetRibbonFactory())
        {
            InitializeComponent();
        }

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

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.dtTab = this.Factory.CreateRibbonTab();
			this.stringGroup = this.Factory.CreateRibbonGroup();
			this.group1 = this.Factory.CreateRibbonGroup();
			this.dialogGroup = this.Factory.CreateRibbonGroup();
			this.questGroup = this.Factory.CreateRibbonGroup();
			this.setupGroup = this.Factory.CreateRibbonGroup();
			this.stringExportButton = this.Factory.CreateRibbonButton();
			this.stringImportButton = this.Factory.CreateRibbonButton();
			this.checkStringButton = this.Factory.CreateRibbonButton();
			this.exportHSButton = this.Factory.CreateRibbonButton();
			this.importHSButton = this.Factory.CreateRibbonButton();
			this.correctButton = this.Factory.CreateRibbonButton();
			this.checkHSButton = this.Factory.CreateRibbonButton();
			this.hsPrevButton = this.Factory.CreateRibbonButton();
			this.hsHelperMenu = this.Factory.CreateRibbonMenu();
			this.hsItemLinkButton = this.Factory.CreateRibbonButton();
			this.hsMobLinkButton = this.Factory.CreateRibbonButton();
			this.hsWPLinkButton = this.Factory.CreateRibbonButton();
			this.maplinkButton = this.Factory.CreateRibbonButton();
			this.charnameButton = this.Factory.CreateRibbonButton();
			this.charproLinkButton = this.Factory.CreateRibbonButton();
			this.newlineButton = this.Factory.CreateRibbonButton();
			this.exportDlgButton = this.Factory.CreateRibbonButton();
			this.importDlgButton = this.Factory.CreateRibbonButton();
			this.dlgCheckButton = this.Factory.CreateRibbonButton();
			this.setupButton = this.Factory.CreateRibbonButton();
			this.reloadButton = this.Factory.CreateRibbonButton();
			this.dtTab.SuspendLayout();
			this.stringGroup.SuspendLayout();
			this.group1.SuspendLayout();
			this.dialogGroup.SuspendLayout();
			this.setupGroup.SuspendLayout();
			// 
			// dtTab
			// 
			this.dtTab.Groups.Add(this.stringGroup);
			this.dtTab.Groups.Add(this.group1);
			this.dtTab.Groups.Add(this.dialogGroup);
			this.dtTab.Groups.Add(this.questGroup);
			this.dtTab.Groups.Add(this.setupGroup);
			this.dtTab.KeyTip = "T";
			this.dtTab.Label = "星石传说策划工具";
			this.dtTab.Name = "dtTab";
			// 
			// stringGroup
			// 
			this.stringGroup.Items.Add(this.stringExportButton);
			this.stringGroup.Items.Add(this.stringImportButton);
			this.stringGroup.Items.Add(this.checkStringButton);
			this.stringGroup.Label = "Plain String";
			this.stringGroup.Name = "stringGroup";
			// 
			// group1
			// 
			this.group1.Items.Add(this.exportHSButton);
			this.group1.Items.Add(this.importHSButton);
			this.group1.Items.Add(this.correctButton);
			this.group1.Items.Add(this.checkHSButton);
			this.group1.Items.Add(this.hsPrevButton);
			this.group1.Items.Add(this.hsHelperMenu);
			this.group1.Label = "HyperString";
			this.group1.Name = "group1";
			// 
			// dialogGroup
			// 
			this.dialogGroup.Items.Add(this.exportDlgButton);
			this.dialogGroup.Items.Add(this.importDlgButton);
			this.dialogGroup.Items.Add(this.dlgCheckButton);
			this.dialogGroup.Label = "对话";
			this.dialogGroup.Name = "dialogGroup";
			// 
			// questGroup
			// 
			this.questGroup.Label = "任务";
			this.questGroup.Name = "questGroup";
			// 
			// setupGroup
			// 
			this.setupGroup.Items.Add(this.setupButton);
			this.setupGroup.Items.Add(this.reloadButton);
			this.setupGroup.Label = "其他";
			this.setupGroup.Name = "setupGroup";
			// 
			// stringExportButton
			// 
			this.stringExportButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.stringExportButton.Label = "导出";
			this.stringExportButton.Name = "stringExportButton";
			this.stringExportButton.OfficeImageId = "FileSave";
			this.stringExportButton.ScreenTip = "导出";
			this.stringExportButton.ShowImage = true;
			this.stringExportButton.SuperTip = "导出";
			this.stringExportButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.stringExportButton_Click);
			// 
			// stringImportButton
			// 
			this.stringImportButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.stringImportButton.Label = "导入";
			this.stringImportButton.Name = "stringImportButton";
			this.stringImportButton.OfficeImageId = "FileOpen";
			this.stringImportButton.ScreenTip = "导入";
			this.stringImportButton.ShowImage = true;
			this.stringImportButton.SuperTip = "导入";
			this.stringImportButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.stringImportButton_Click);
			// 
			// checkStringButton
			// 
			this.checkStringButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.checkStringButton.Label = "检查错误";
			this.checkStringButton.Name = "checkStringButton";
			this.checkStringButton.OfficeImageId = "WhatIfAnalysisMenu";
			this.checkStringButton.ScreenTip = "检查错误";
			this.checkStringButton.ShowImage = true;
			this.checkStringButton.SuperTip = "检查错误";
			this.checkStringButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.checkStringButton_Click);
			// 
			// exportHSButton
			// 
			this.exportHSButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.exportHSButton.Label = "导出";
			this.exportHSButton.Name = "exportHSButton";
			this.exportHSButton.OfficeImageId = "FileSave";
			this.exportHSButton.ScreenTip = "导出到HyperString表";
			this.exportHSButton.ShowImage = true;
			this.exportHSButton.SuperTip = "导出到HyperString表";
			this.exportHSButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.exportHSButton_Click);
			// 
			// importHSButton
			// 
			this.importHSButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.importHSButton.Label = "导入";
			this.importHSButton.Name = "importHSButton";
			this.importHSButton.OfficeImageId = "FileOpen";
			this.importHSButton.ScreenTip = "导入HyperString表";
			this.importHSButton.ShowImage = true;
			this.importHSButton.SuperTip = "导入HyperString表";
			this.importHSButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.importHSButton_Click);
			// 
			// correctButton
			// 
			this.correctButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.correctButton.Label = "自动纠正";
			this.correctButton.Name = "correctButton";
			this.correctButton.OfficeImageId = "WhatIfAnalysisMenu";
			this.correctButton.ScreenTip = "纠正";
			this.correctButton.ShowImage = true;
			this.correctButton.SuperTip = "自动纠正选择单元格中的物品和怪物的名字，地图和路点的名字暂时无法纠正";
			this.correctButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.correctButton_Click);
			// 
			// checkHSButton
			// 
			this.checkHSButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.checkHSButton.Label = "检查错误";
			this.checkHSButton.Name = "checkHSButton";
			this.checkHSButton.OfficeImageId = "WhatIfAnalysisMenu";
			this.checkHSButton.ScreenTip = "检查错误";
			this.checkHSButton.ShowImage = true;
			this.checkHSButton.SuperTip = "检查错误";
			this.checkHSButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.checkHSButton_Click);
			// 
			// hsPrevButton
			// 
			this.hsPrevButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.hsPrevButton.Label = "预览";
			this.hsPrevButton.Name = "hsPrevButton";
			this.hsPrevButton.OfficeImageId = "FilePrintPreview";
			this.hsPrevButton.ScreenTip = "预览";
			this.hsPrevButton.ShowImage = true;
			this.hsPrevButton.SuperTip = "预览";
			this.hsPrevButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.hsPrevButton_Click);
			// 
			// hsHelperMenu
			// 
			this.hsHelperMenu.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.hsHelperMenu.Items.Add(this.hsItemLinkButton);
			this.hsHelperMenu.Items.Add(this.hsMobLinkButton);
			this.hsHelperMenu.Items.Add(this.hsWPLinkButton);
			this.hsHelperMenu.Items.Add(this.maplinkButton);
			this.hsHelperMenu.Items.Add(this.charnameButton);
			this.hsHelperMenu.Items.Add(this.charproLinkButton);
			this.hsHelperMenu.Items.Add(this.newlineButton);
			this.hsHelperMenu.KeyTip = "T";
			this.hsHelperMenu.Label = "模板";
			this.hsHelperMenu.Name = "hsHelperMenu";
			this.hsHelperMenu.OfficeImageId = "FunctionWizard";
			this.hsHelperMenu.ScreenTip = "模板";
			this.hsHelperMenu.ShowImage = true;
			this.hsHelperMenu.SuperTip = "模板";
			// 
			// hsItemLinkButton
			// 
			this.hsItemLinkButton.KeyTip = "I";
			this.hsItemLinkButton.Label = "物品";
			this.hsItemLinkButton.Name = "hsItemLinkButton";
			this.hsItemLinkButton.ShowImage = true;
			this.hsItemLinkButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.hsItemLinkButton_Click);
			// 
			// hsMobLinkButton
			// 
			this.hsMobLinkButton.KeyTip = "M";
			this.hsMobLinkButton.Label = "怪物";
			this.hsMobLinkButton.Name = "hsMobLinkButton";
			this.hsMobLinkButton.ShowImage = true;
			this.hsMobLinkButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.hsMobLinkButton_Click);
			// 
			// hsWPLinkButton
			// 
			this.hsWPLinkButton.KeyTip = "W";
			this.hsWPLinkButton.Label = "地点";
			this.hsWPLinkButton.Name = "hsWPLinkButton";
			this.hsWPLinkButton.ShowImage = true;
			this.hsWPLinkButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.hsWPLinkButton_Click);
			// 
			// maplinkButton
			// 
			this.maplinkButton.Label = "地图";
			this.maplinkButton.Name = "maplinkButton";
			this.maplinkButton.ShowImage = true;
			this.maplinkButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.maplinkButton_Click);
			// 
			// charnameButton
			// 
			this.charnameButton.Label = "角色名";
			this.charnameButton.Name = "charnameButton";
			this.charnameButton.ShowImage = true;
			this.charnameButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.charnameButton_Click);
			// 
			// charproLinkButton
			// 
			this.charproLinkButton.Label = "角色职业";
			this.charproLinkButton.Name = "charproLinkButton";
			this.charproLinkButton.ShowImage = true;
			this.charproLinkButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.charproLinkButton_Click);
			// 
			// newlineButton
			// 
			this.newlineButton.Label = "换行";
			this.newlineButton.Name = "newlineButton";
			this.newlineButton.ShowImage = true;
			this.newlineButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.newlineButton_Click);
			// 
			// exportDlgButton
			// 
			this.exportDlgButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.exportDlgButton.Enabled = false;
			this.exportDlgButton.Label = "导出";
			this.exportDlgButton.Name = "exportDlgButton";
			this.exportDlgButton.OfficeImageId = "FileSave";
			this.exportDlgButton.ScreenTip = "导出对话";
			this.exportDlgButton.ShowImage = true;
			this.exportDlgButton.SuperTip = "导出对话";
			// 
			// importDlgButton
			// 
			this.importDlgButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.importDlgButton.Enabled = false;
			this.importDlgButton.Label = "导入";
			this.importDlgButton.Name = "importDlgButton";
			this.importDlgButton.OfficeImageId = "FileOpen";
			this.importDlgButton.ScreenTip = "导入对话";
			this.importDlgButton.ShowImage = true;
			this.importDlgButton.SuperTip = "导入对话";
			// 
			// dlgCheckButton
			// 
			this.dlgCheckButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.dlgCheckButton.Enabled = false;
			this.dlgCheckButton.Label = "检查错误";
			this.dlgCheckButton.Name = "dlgCheckButton";
			this.dlgCheckButton.OfficeImageId = "WhatIfAnalysisMenu";
			this.dlgCheckButton.ScreenTip = "检查错误";
			this.dlgCheckButton.ShowImage = true;
			this.dlgCheckButton.SuperTip = "检查错误";
			this.dlgCheckButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.dlgCheckButton_Click);
			// 
			// setupButton
			// 
			this.setupButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.setupButton.Description = "设置";
			this.setupButton.Label = "设置";
			this.setupButton.Name = "setupButton";
			this.setupButton.OfficeImageId = "ControlsGallery";
			this.setupButton.ScreenTip = "设置";
			this.setupButton.ShowImage = true;
			this.setupButton.SuperTip = "设置";
			this.setupButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.setupButton_Click);
			// 
			// reloadButton
			// 
			this.reloadButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
			this.reloadButton.Label = "重置资源";
			this.reloadButton.Name = "reloadButton";
			this.reloadButton.OfficeImageId = "ControlsGallery";
			this.reloadButton.ScreenTip = "重置资源";
			this.reloadButton.ShowImage = true;
			this.reloadButton.SuperTip = "重置资源";
			this.reloadButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.reloadButton_Click);
			// 
			// DTRibbon
			// 
			this.Name = "DTRibbon";
			this.RibbonType = "Microsoft.Excel.Workbook";
			this.Tabs.Add(this.dtTab);
			this.Load += new Microsoft.Office.Tools.Ribbon.RibbonUIEventHandler(this.DTRibbon_Load);
			this.dtTab.ResumeLayout(false);
			this.dtTab.PerformLayout();
			this.stringGroup.ResumeLayout(false);
			this.stringGroup.PerformLayout();
			this.group1.ResumeLayout(false);
			this.group1.PerformLayout();
			this.dialogGroup.ResumeLayout(false);
			this.dialogGroup.PerformLayout();
			this.setupGroup.ResumeLayout(false);
			this.setupGroup.PerformLayout();

        }

        #endregion

        private Microsoft.Office.Tools.Ribbon.RibbonTab dtTab;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup group1;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton exportHSButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton importHSButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup dialogGroup;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton exportDlgButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton importDlgButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup setupGroup;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton setupButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup questGroup;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup stringGroup;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton stringExportButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton stringImportButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton checkStringButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton checkHSButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonMenu hsHelperMenu;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton hsItemLinkButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton hsMobLinkButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton hsWPLinkButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton dlgCheckButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton hsPrevButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton reloadButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton maplinkButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton charnameButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton charproLinkButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton newlineButton;
		internal Microsoft.Office.Tools.Ribbon.RibbonButton correctButton;

    }

    partial class ThisRibbonCollection
    {
        internal DTRibbon DTRibbon
        {
            get { return this.GetRibbon<DTRibbon>(); }
        }
    }
}
