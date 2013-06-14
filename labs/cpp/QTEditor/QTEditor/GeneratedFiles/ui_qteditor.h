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
        QBrush brush(QColor(213, 213, 213, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(83, 83, 83, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(177, 177, 177, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush2);
        QBrush brush3(QColor(158, 158, 158, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush4(QColor(120, 120, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QTEditorClass->setPalette(palette);
        QTEditorClass->setStyleSheet(QStringLiteral("background-color: rgb(83, 83, 83);"));
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
        menuBar->setGeometry(QRect(0, 0, 1029, 23));
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
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">fdafdafdas</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">aaaa</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class QTEditorClass: public Ui_QTEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTEDITOR_H
