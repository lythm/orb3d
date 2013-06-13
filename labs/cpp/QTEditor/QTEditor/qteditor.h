#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_qteditor.h"

class QTEditor : public QMainWindow
{
	Q_OBJECT

public:
	QTEditor(QWidget *parent = 0);
	~QTEditor();

private:
	Ui::QTEditorClass ui;
};

#endif // QTEDITOR_H
