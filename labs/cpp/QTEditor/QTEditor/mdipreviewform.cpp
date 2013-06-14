#include "mdipreviewform.h"

MDIPreviewForm::MDIPreviewForm(QWidget *parent)
	: QMdiSubWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

MDIPreviewForm::~MDIPreviewForm()
{

}
