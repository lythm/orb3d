#include "mdisceneform.h"

MDISceneForm::MDISceneForm(QWidget *parent)
	: QMdiSubWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

MDISceneForm::~MDISceneForm()
{

}
