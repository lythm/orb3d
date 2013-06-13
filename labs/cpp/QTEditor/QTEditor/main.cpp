#include "qteditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTEditor w;
	w.show();
	return a.exec();
}
