/********************************************************************************
** Form generated from reading UI file 'qteditor.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEDITOR_H
#define UI_QTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTEditorClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuProject;
    QMenu *menuHelp;
    QDockWidget *ObjectTreeWnd;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    QTreeView *ObjectTreeView;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout_4;
    QWidget *widget;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents_4;
    QCheckBox *checkBox;
    QCommandLinkButton *commandLinkButton;
    QToolButton *toolButton;
    QPushButton *pushButton;
    QDockWidget *OutputWnd;
    QWidget *dockWidgetContents_5;
    QGridLayout *gridLayout_3;
    QTextBrowser *InfoOutput;

    void setupUi(QMainWindow *QTEditorClass)
    {
        if (QTEditorClass->objectName().isEmpty())
            QTEditorClass->setObjectName(QStringLiteral("QTEditorClass"));
        QTEditorClass->resize(1029, 816);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QTEditorClass->sizePolicy().hasHeightForWidth());
        QTEditorClass->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(83, 83, 83, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QTEditorClass->setPalette(palette);
        QTEditorClass->setStyleSheet(QString::fromUtf8("*{  \n"
"  font-size:13px;  \n"
"  color:white;  \n"
"  font-family:\"\345\256\213\344\275\223\";  \n"
"}  \n"
"CallWidget QLineEdit#telEdt  \n"
"{  \n"
"  font-size:24px;  \n"
"}  \n"
"QMainWindow,QDialog{  \n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #1B2534, stop: 0.4 #010101,  \n"
"                                 stop: 0.5 #000101, stop: 1.0 #1F2B3C);  \n"
"}  \n"
"QWidget{  \n"
"    background:#535353\n"
"}  \n"
"QLabel{  \n"
"   background:transparent;  \n"
"}  \n"
"DailForm QLineEdit#phoneLineEdt{  \n"
"  font-size:36px;  \n"
"  font-weight: bold;  \n"
"}  \n"
"QPushButton,QToolButton{  \n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #5B5F5F, stop: 0.5 #0C2436,  \n"
"                                 stop: 1.0 #27405A);  \n"
"    border-style: outset;  \n"
"    border-width: 1px;  \n"
"    border-radius: 5px;  \n"
"    border-color: #11223F;  \n"
"    padding: 1px;  \n"
"	f"
                        "lat:true;\n"
"}  \n"
"QPushButton::hover,QToolButton::hover{  \n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #758385, stop: 0.5 #122C39,  \n"
"                                 stop: 1.0 #0E7788);  \n"
"    border-color: #11505C;  \n"
"}  \n"
"QPushButton::pressed,QToolButton::pressed{  \n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #969B9C, stop: 0.5 #16354B,  \n"
"                                 stop: 1.0 #244F76);  \n"
"    border-color: #11505C;  \n"
"}  \n"
"QPushButton::disabled,QToolButton::disabled{  \n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #282B2C, stop: 0.5 #09121A,  \n"
"                                 stop: 1.0 #111D29);  \n"
"    border-color: #0A1320;  \n"
"    color:#6A6864;  \n"
"}  \n"
"QDialog QPushButton,QDialog QToolButton{  \n"
"  min-width:30px;  \n"
"  min-height:23px;  \n"
"}  \n"
"QToolB"
                        "utton[objectName=\"minimizeToolBtn\"] {  \n"
"    background: transparent;  \n"
"    border:none;  \n"
"    image:url(qss/minimize.png)  \n"
"}  \n"
"QToolButton[objectName=\"minimizeToolBtn\"]:hover,QToolButton[objectName=\"minimizeToolBtn\"]:pressed {  \n"
"    image:url(qss/minimize_hover.png)  \n"
"}  \n"
"QToolButton[objectName=\"maximizeToolBtn\"] {  \n"
"    background: transparent;  \n"
"    border:none;  \n"
"    image:url(qss/maximize.png)  \n"
"}  \n"
"QToolButton[objectName=\"maximizeToolBtn\"]:hover,QToolButton[objectName=\"maximizeToolBtn\"]:pressed {  \n"
"    image:url(qss/maximize_hover.png)  \n"
"}  \n"
"QToolButton[objectName=\"closeToolBtn\"],QToolButton[objectName=\"customCloseWindow\"] {  \n"
"    background: transparent;  \n"
"    border:none;  \n"
"    image:url(qss/close.png)  \n"
"}  \n"
"QToolButton[objectName=\"closeToolBtn\"]:hover,QToolButton[objectName=\"closeToolBtn\"]:pressed{  \n"
"    image:url(qss/close_hover.png)  \n"
"}  \n"
"QToolButton[objectName=\"customCloseWindow\"]:h"
                        "over,QToolButton[objectName=\"customCloseWindow\"]:pressed{  \n"
"    image:url(qss/close_hover.png)  \n"
"}  \n"
"QToolButton[objectName=\"titleSetUpToolBtn\"]{  \n"
"    background: transparent;  \n"
"    border:none;  \n"
"    image:url(qss/setup.png)  \n"
"}  \n"
"DailForm QToolButton#oneToolBtn,QToolButton#OneToolBtn,QToolButton#twoToolBtn,QToolButton#threeToolBtn,  \n"
"         QToolButton#fourToolBtn,QToolButton#fiveToolBtn,QToolButton#sixToolBtn,  \n"
"         QToolButton#sevenToolBtn,QToolButton#eightToolBtn,QToolButton#nineToolBtn,  \n"
"         QToolButton#starToolBtn,QToolButton#zeroToolBtn,QToolButton#sharpToolBtn {  \n"
"    font-size:36px;  \n"
"    border-radius: 10px;  \n"
"}  \n"
"DailForm QToolButton#delToolBtn{  \n"
"    border-radius: 10px;  \n"
"}  \n"
"QFrame{  \n"
"    border-color:#32435E;  \n"
"    border-width:1px;  \n"
"    border-radius: 3px;  \n"
"}  \n"
"QLineEdit,QTextEdit {  \n"
"    border: 1px solid #32435E;  \n"
"    border-radius: 3px;  \n"
"    /* padding: 0 8px; */  \n"
""
                        "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #080B10,  \n"
"                                 stop: 1.0 #212C3F);  \n"
"    selection-background-color: #0A246A;  \n"
"}  \n"
"QLineEdit::hover{  \n"
"  border-color:#5D8B9E;  \n"
"}  \n"
"QLineEdit[echoMode=\"3\"] {  \n"
"     lineedit-password-character: 9679;  \n"
"}  \n"
"#QLineEdit:read-only {  \n"
"     background: #543F7C;  \n"
"}  \n"
"QTabWidget::pane { /* The tab widget frame */  \n"
"     border: 0px solid #32435E;  \n"
"     position: absolute;  \n"
"     left: -0.1em;  \n"
"}  \n"
"QTabWidget#MainTabWidget::tab-bar {  \n"
"     left: -3px; /* move to the right by 5px */  \n"
"}  \n"
"QTabWidget#MainTabWidget QTabBar::tab {  \n"
"     height: 14ex;  \n"
"     width: 14ex;  \n"
"}  \n"
"QTabBar::tab {  \n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #292F31, stop: 1 #0C131E);  \n"
"}  \n"
"QTabBar::tab:selected{  \n"
"     backg"
                        "round: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #113845,  stop: 1.0 #15A8FF);  \n"
"}  \n"
"QTabBar::tab:hover {  \n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #113845,  stop: 1.0 #0E6F80);  \n"
"}  \n"
"#QTabBar::tab:selected {  \n"
"     border-color: #32435E;  \n"
"     border-right-color: #32435E; /* same as pane color */  \n"
"}  \n"
"#QTabBar::tab:!selected {  \n"
"     margin-left: 2px; /* make non-selected tabs look smaller */  \n"
"}  \n"
"#QTabBar:tab:first:selected {  \n"
"    margin-top: 0;  \n"
"}  \n"
"QTabBar:tab:last:selected {  \n"
"    margin-right: 0;  \n"
"}  \n"
"QTabBar:tab:only-one {  \n"
"     margin: 0;  \n"
"}  \n"
"QListWidget{  \n"
"    border: 1px solid #32435E;  \n"
"    background:#050609;  \n"
"}  \n"
"QListWidget::item:selected {  \n"
"     /*border: 0px solid #33CCFF;*/  \n"
"     border:none;  \n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
""
                        "                                 stop: 0 #6A848C,  stop: 1.0 #0F9EAF);  \n"
"     padding:0px;  \n"
"     margin:0px;  \n"
"}  \n"
"#QListWidget::item:selected:!active {  \n"
"     border-width: 0px ;  \n"
"}  \n"
"#QListWidget::item:selected:active {  \n"
"     border-width: 1px;  \n"
"}  \n"
"  \n"
"QComboBox {  \n"
"     border: 1px solid #32435E;  \n"
"     border-radius: 3px;  \n"
"     padding: 1px 18px 1px 3px;  \n"
"     min-width: 6em;  \n"
"}  \n"
"QComboBox::hover{  \n"
"  border-color:#5D8B9E;  \n"
"}  \n"
"QComboBox:editable {  \n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #080B10,  \n"
"                                 stop: 1.0 #212C3F);  \n"
"}  \n"
"QComboBox:!editable, QComboBox::drop-down:editable {  \n"
"      background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #080B10,  \n"
"                                 stop: 1.0 #212C3F);  \n"
"}  \n"
"/* QComboBox gets the \"on\" stat"
                        "e when the popup is open */  \n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on {  \n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #080B10,  \n"
"                                 stop: 1.0 #212C3F);;  \n"
"}  \n"
"QComboBox:on { /* shift the text when the popup opens */  \n"
"     padding-top: 3px;  \n"
"     padding-left: 4px;  \n"
"}  \n"
"QComboBox::drop-down {  \n"
"     subcontrol-origin: padding;  \n"
"     subcontrol-position: top right;  \n"
"     width: 15px;  \n"
"     border-left-width: 1px;  \n"
"     border-left-color: 32435E;  \n"
"     border-left-style: solid; /* just a single line */  \n"
"     border-top-right-radius: 3px; /* same radius as the QComboBox */  \n"
"     border-bottom-right-radius: 3px;  \n"
"}  \n"
"QComboBox::down-arrow {  \n"
"     image: url(qss/downarrow.png);  \n"
"}  \n"
"QComboBox::down-arrow:on { /* shift the arrow when popup is open */  \n"
"     top: 1px;  \n"
"     left: 1px;  \n"
"}  \n"
"QC"
                        "omboBox QAbstractItemView {  \n"
"     border: 2px solid #32435E;  \n"
"     selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #506B79,  \n"
"                                 stop: 1.0 #0D95A6);  \n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \n"
"                                 stop: 0 #1B2534, stop: 0.4 #010101,  \n"
"                                 stop: 0.5 #000101, stop: 1.0 #1F2B3C);  \n"
"}  "));
        QTEditorClass->setDocumentMode(true);
        QTEditorClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);
        actionOpen = new QAction(QTEditorClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(QTEditorClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(QTEditorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(QTEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setAutoFillBackground(true);
        mdiArea->setFrameShadow(QFrame::Plain);
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setDocumentMode(true);
        mdiArea->setTabsClosable(true);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        QTEditorClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(QTEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTEditorClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(QTEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1029, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuProject = new QMenu(menuBar);
        menuProject->setObjectName(QStringLiteral("menuProject"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        QTEditorClass->setMenuBar(menuBar);
        ObjectTreeWnd = new QDockWidget(QTEditorClass);
        ObjectTreeWnd->setObjectName(QStringLiteral("ObjectTreeWnd"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        ObjectTreeView = new QTreeView(dockWidgetContents);
        ObjectTreeView->setObjectName(QStringLiteral("ObjectTreeView"));

        gridLayout_2->addWidget(ObjectTreeView, 0, 0, 1, 1);

        ObjectTreeWnd->setWidget(dockWidgetContents);
        QTEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), ObjectTreeWnd);
        dockWidget_2 = new QDockWidget(QTEditorClass);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        gridLayout_4 = new QGridLayout(dockWidgetContents_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        widget = new QWidget(dockWidgetContents_2);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout_4->addWidget(widget, 0, 0, 1, 1);

        dockWidget_2->setWidget(dockWidgetContents_2);
        QTEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_2);
        dockWidget_4 = new QDockWidget(QTEditorClass);
        dockWidget_4->setObjectName(QStringLiteral("dockWidget_4"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        checkBox = new QCheckBox(dockWidgetContents_4);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(20, 30, 71, 16));
        commandLinkButton = new QCommandLinkButton(dockWidgetContents_4);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(20, 70, 185, 41));
        toolButton = new QToolButton(dockWidgetContents_4);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(40, 150, 37, 18));
        pushButton = new QPushButton(dockWidgetContents_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(130, 150, 75, 23));
        dockWidget_4->setWidget(dockWidgetContents_4);
        QTEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_4);
        OutputWnd = new QDockWidget(QTEditorClass);
        OutputWnd->setObjectName(QStringLiteral("OutputWnd"));
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QStringLiteral("dockWidgetContents_5"));
        gridLayout_3 = new QGridLayout(dockWidgetContents_5);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        InfoOutput = new QTextBrowser(dockWidgetContents_5);
        InfoOutput->setObjectName(QStringLiteral("InfoOutput"));

        gridLayout_3->addWidget(InfoOutput, 0, 0, 1, 1);

        OutputWnd->setWidget(dockWidgetContents_5);
        QTEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), OutputWnd);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuProject->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(QTEditorClass);

        QMetaObject::connectSlotsByName(QTEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTEditorClass)
    {
        QTEditorClass->setWindowTitle(QApplication::translate("QTEditorClass", "QTEditor", 0));
        actionOpen->setText(QApplication::translate("QTEditorClass", "Open", 0));
        actionSave->setText(QApplication::translate("QTEditorClass", "Save", 0));
        actionExit->setText(QApplication::translate("QTEditorClass", "Exit", 0));
        menuFile->setTitle(QApplication::translate("QTEditorClass", "File", 0));
        menuView->setTitle(QApplication::translate("QTEditorClass", "View", 0));
        menuProject->setTitle(QApplication::translate("QTEditorClass", "Project", 0));
        menuHelp->setTitle(QApplication::translate("QTEditorClass", "Help", 0));
        ObjectTreeWnd->setWindowTitle(QApplication::translate("QTEditorClass", "Test", 0));
        checkBox->setText(QApplication::translate("QTEditorClass", "CheckBox", 0));
        commandLinkButton->setText(QApplication::translate("QTEditorClass", "CommandLinkButton", 0));
        toolButton->setText(QApplication::translate("QTEditorClass", "...", 0));
        pushButton->setText(QApplication::translate("QTEditorClass", "PushButton", 0));
        InfoOutput->setHtml(QApplication::translate("QTEditorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:13px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">fdafdafdas</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">aaaa</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class QTEditorClass: public Ui_QTEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTEDITOR_H
