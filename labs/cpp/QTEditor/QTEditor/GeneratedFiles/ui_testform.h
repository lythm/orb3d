/********************************************************************************
** Form generated from reading UI file 'testform.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTFORM_H
#define UI_TESTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestForm
{
public:
    QPushButton *pushButton;
    QToolButton *toolButton;

    void setupUi(QWidget *TestForm)
    {
        if (TestForm->objectName().isEmpty())
            TestForm->setObjectName(QStringLiteral("TestForm"));
        TestForm->resize(400, 300);
        pushButton = new QPushButton(TestForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 70, 75, 23));
        toolButton = new QToolButton(TestForm);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(110, 200, 37, 18));

        retranslateUi(TestForm);

        QMetaObject::connectSlotsByName(TestForm);
    } // setupUi

    void retranslateUi(QWidget *TestForm)
    {
        TestForm->setWindowTitle(QApplication::translate("TestForm", "TestForm", 0));
        pushButton->setText(QApplication::translate("TestForm", "PushButton", 0));
        toolButton->setText(QApplication::translate("TestForm", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class TestForm: public Ui_TestForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTFORM_H
