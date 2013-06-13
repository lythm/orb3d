#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include "ui_inspector.h"

class Inspector : public QWidget
{
	Q_OBJECT

public:
	Inspector(QWidget *parent = 0);
	~Inspector();

private:
	Ui::Inspector ui;
};

#endif // INSPECTOR_H
