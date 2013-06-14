#ifndef INSPECTORFORM_H
#define INSPECTORFORM_H

#include <QWidget>
#include "ui_inspectorform.h"

class InspectorForm : public QWidget
{
	Q_OBJECT

public:
	InspectorForm(QWidget *parent = 0);
	~InspectorForm();

private:
	Ui::InspectorForm ui;
};

#endif // INSPECTORFORM_H
