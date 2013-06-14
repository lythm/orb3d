/********************************************************************************
** Form generated from reading UI file 'inspectorform.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSPECTORFORM_H
#define UI_INSPECTORFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InspectorForm
{
public:

    void setupUi(QWidget *InspectorForm)
    {
        if (InspectorForm->objectName().isEmpty())
            InspectorForm->setObjectName(QStringLiteral("InspectorForm"));
        InspectorForm->resize(400, 300);

        retranslateUi(InspectorForm);

        QMetaObject::connectSlotsByName(InspectorForm);
    } // setupUi

    void retranslateUi(QWidget *InspectorForm)
    {
        InspectorForm->setWindowTitle(QApplication::translate("InspectorForm", "InspectorForm", 0));
    } // retranslateUi

};

namespace Ui {
    class InspectorForm: public Ui_InspectorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSPECTORFORM_H
