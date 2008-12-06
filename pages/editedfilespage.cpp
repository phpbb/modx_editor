#include "editedfilespage.h"

#include "modxdata.h"

#include <QFileDialog>
#include <QFileSystemModel>


EditedFilesPage::EditedFilesPage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);

	m_model = new ListModel<QString>(this);
	fileModel = new QFileSystemModel(this);

	ui.editedFilesView->setModel(m_model);
	ui.allFilesView->setModel(fileModel);
	ui.allFilesView->hideColumn(1);
	ui.allFilesView->hideColumn(2);
	ui.allFilesView->hideColumn(3);
	ui.allFilesView->hideColumn(4);

}

void EditedFilesPage::setData(const ModXData *data)
{
	m_model->setList(data->actions.keys());
}

void EditedFilesPage::getData(ModXData *)
{

}

void EditedFilesPage::on_addFile_clicked()
{
	QList<QString> list = m_model->list();
	if (list.contains(ui.file->text()))
		return;

	list << ui.file->text();
	m_model->setList(list);
	ui.file->setText("");
}

void EditedFilesPage::on_addFiles_clicked()
{
	QModelIndexList list = ui.allFilesView->selectionModel()->selectedIndexes();

	QString basepath = QFileInfo(ui.phpbbRootPath->text()).absoluteFilePath() + "/";

	QSet<QString> currentfiles = m_model->list().toSet();
	QSet<QString> newFiles;
	foreach (QModelIndex index, list)
	{
		QString newPath = fileModel->fileInfo(index).absoluteFilePath().replace(basepath, "");
		newFiles.insert(newPath);
	}
	m_model->setList((currentfiles + newFiles).toList());
	ui.allFilesView->clearSelection();
}

void EditedFilesPage::on_removeFiles_clicked()
{
	QModelIndexList list = ui.editedFilesView->selectionModel()->selectedIndexes();

	QList<QString> currentFiles = m_model->list();
	foreach (QModelIndex index, list)
	{
		currentFiles.removeAll(m_model->data(index, Qt::EditRole).toString());
	}
	m_model->setList(currentFiles);
	ui.editedFilesView->clearSelection();
}

void EditedFilesPage::on_phpbbRootPath_textChanged(const QString &path)
{
	ui.allFilesView->setRootIndex(fileModel->setRootPath(path));
}

void EditedFilesPage::on_browseButton_clicked()
{
	QString path = QFileDialog::getExistingDirectory(
			this,
			tr("phpBB root"));

	if (path == "")
		return;

	ui.phpbbRootPath->setText(path);
}


void EditedFilesPage::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
		ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
