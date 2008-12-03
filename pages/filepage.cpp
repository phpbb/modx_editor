#include "filepage.h"

#include "modxapp.h"
#include "modxdata.h"

#include <QDir>
#include <QFileSystemModel>
#include <QListWidgetItem>

#include <QDebug>

FilePage::FilePage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);

	fileModel = new QFileSystemModel(this);
	fileModel->setReadOnly(true);

	ui.fileView->setModel(fileModel);

	connect(ui.copyFiles, SIGNAL(toggled(bool)), this, SLOT(updateFiles(bool)));
}

void FilePage::setData(const ModXData *data)
{
	ui.copyFiles->setChecked(data->copyFiles);
	QModelIndex index = fileModel->setRootPath(QFileInfo(ModXApp::currentFile).absoluteDir().canonicalPath() + "/root");
	ui.fileView->setRootIndex(index);
}

void FilePage::getData(ModXData *data)
{
	data->copyFiles = ui.copyFiles->isChecked();
}

void FilePage::updateFiles(bool checked)
{
	if (!checked)
		return;


}

void FilePage::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
		ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
