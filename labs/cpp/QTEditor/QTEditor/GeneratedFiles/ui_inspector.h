/********************************************************************************
** Form generated from reading UI file 'inspector.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSPECTOR_H
#define UI_INSPECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Inspector
{
public:

    void setupUi(QWidget *Inspector)
    {
        if (Inspector->objectName().isEmpty())
            Inspector->setObjectName(QStringLiteral("Inspector"));
        Inspector->resize(400, 300);

        retranslateUi(Inspector);

        QMetaObject::connectSlotsByName(Inspector);
    } // setupUi

    void retranslateUi(QWidget *Inspector)
    {
        Inspector->setWindowTitle(QApplication::translate("Inspector", "Inspector", 0));
    } // retranslateUi

};

namespace Ui {
    class Inspector: public Ui_Inspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSPECTOR_H
