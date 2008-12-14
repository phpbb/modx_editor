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
	ui.fileView->hideColumn(1);
	ui.fileView->hideColumn(2);
	ui.fileView->hideColumn(3);

	connect(ui.copyFiles, SIGNAL(toggled(bool)), this, SLOT(updateFiles(bool)));
}

void FilePage::setData(const ModXData *data)
{
	ui.copyFiles->setChecked(data->copyFiles);
	setRootDir();
}

void FilePage::getData(ModXData *data)
{
	data->copyFiles = ui.copyFiles->isChecked();
}

void FilePage::updateFiles(bool /*checked*/)
{
	setRootDir();
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

void FilePage::setRootDir()
{
	QFileInfo rootDir = QFileInfo(ModXApp::currentFile).absoluteDir().canonicalPath() + "/root";
	if (rootDir.exists())
	{
		ui.fileViewContainer->setCurrentIndex(0);
		QModelIndex index = fileModel->setRootPath(rootDir.absoluteFilePath());
		ui.fileView->setRootIndex(index);
	}
	else
	{
		ui.fileViewContainer->setCurrentIndex(1);
	}
}
