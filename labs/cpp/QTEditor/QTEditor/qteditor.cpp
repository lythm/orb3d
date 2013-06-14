#include "qteditor.h"
#include "mdisceneform.h"
#include "mdipreviewform.h"

QTEditor::QTEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	MDISceneForm* pScene = new MDISceneForm(this);
	MDIPreviewForm* pPreview = new MDIPreviewForm(this);
	ui.mdiArea->addSubWindow(pScene);
	ui.mdiArea->addSubWindow(pPreview);

	pScene->show();
	pPreview->show();

}

QTEditor::~QTEditor()
{

}
