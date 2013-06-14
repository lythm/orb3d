/********************************************************************************
** Form generated from reading UI file 'mdisceneform.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MDISCENEFORM_H
#define UI_MDISCENEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMdiSubWindow>

QT_BEGIN_NAMESPACE

class Ui_MDISceneForm
{
public:
    QLabel *label;

    void setupUi(QMdiSubWindow *MDISceneForm)
    {
        if (MDISceneForm->objectName().isEmpty())
            MDISceneForm->setObjectName(QStringLiteral("MDISceneForm"));
        MDISceneForm->resize(588, 393);
        label = new QLabel(MDISceneForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 50, 54, 12));

        retranslateUi(MDISceneForm);

        QMetaObject::connectSlotsByName(MDISceneForm);
    } // setupUi

    void retranslateUi(QMdiSubWindow *MDISceneForm)
    {
        MDISceneForm->setWindowTitle(QApplication::translate("MDISceneForm", "MDISceneForm", 0));
        label->setText(QApplication::translate("MDISceneForm", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MDISceneForm: public Ui_MDISceneForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MDISCENEFORM_H
