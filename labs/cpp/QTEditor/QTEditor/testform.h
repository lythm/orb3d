#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include "ui_testform.h"

class TestForm : public QWidget, public Ui::TestForm
{
	Q_OBJECT

public:
	TestForm(QWidget *parent = 0);
	~TestForm();
};

#endif // TESTFORM_H
