#ifndef MDISCENEFORM_H
#define MDISCENEFORM_H

#include <QMdiSubWindow>
#include "ui_mdisceneform.h"

class MDISceneForm : public QMdiSubWindow
{
	Q_OBJECT

public:
	MDISceneForm(QWidget *parent = 0);
	~MDISceneForm();

private:
	Ui::MDISceneForm ui;
};

#endif // MDISCENEFORM_H
