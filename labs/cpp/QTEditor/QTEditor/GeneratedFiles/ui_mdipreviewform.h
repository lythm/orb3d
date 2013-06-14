/********************************************************************************
** Form generated from reading UI file 'mdipreviewform.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MDIPREVIEWFORM_H
#define UI_MDIPREVIEWFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMdiSubWindow>

QT_BEGIN_NAMESPACE

class Ui_MDIPreviewForm
{
public:

    void setupUi(QMdiSubWindow *MDIPreviewForm)
    {
        if (MDIPreviewForm->objectName().isEmpty())
            MDIPreviewForm->setObjectName(QStringLiteral("MDIPreviewForm"));
        MDIPreviewForm->resize(400, 300);

        retranslateUi(MDIPreviewForm);

        QMetaObject::connectSlotsByName(MDIPreviewForm);
    } // setupUi

    void retranslateUi(QMdiSubWindow *MDIPreviewForm)
    {
        MDIPreviewForm->setWindowTitle(QApplication::translate("MDIPreviewForm", "MDIPreviewForm", 0));
    } // retranslateUi

};

namespace Ui {
    class MDIPreviewForm: public Ui_MDIPreviewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MDIPREVIEWFORM_H
