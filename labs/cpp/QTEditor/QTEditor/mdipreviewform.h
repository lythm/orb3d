#ifndef MDIPREVIEWFORM_H
#define MDIPREVIEWFORM_H

#include <QMdiSubWindow>
#include "ui_mdipreviewform.h"

class MDIPreviewForm : public QMdiSubWindow
{
	Q_OBJECT

public:
	MDIPreviewForm(QWidget *parent = 0);
	~MDIPreviewForm();

private:
	Ui::MDIPreviewForm ui;
};

#endif // MDIPREVIEWFORM_H
