/***************************************************************************
 *   Copyright (C) 2009 by the phpBB Group                                 *
 *   phpbb.com                                                             *
 *                                                                         *
 *  This file is part of MODX Editor.                                      *
 *                                                                         *
 *  MODX Editor is free software: you can redistribute it and/or modify    *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  MODX Editor is distributed in the hope that it will be useful,         *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with MODX Editor.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

#include "mainwindow.h"

#include "modxapp.h"
#include "modxreader.h"
#include "modxwriter.h"
#include "modxdata.h"
#include "pages/generalpage.h"
#include "pages/authorgrouppage.h"
#include "pages/changelogpage.h"
#include "pages/sqlpage.h"
#include "pages/filepage.h"
#include "pages/editedfilespage.h"
#include "pages/fileeditpage.h"
#include "pages/diypage.h"
#include "widgets/aboutdialog.h"


#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QListWidgetItem>
#include <QCloseEvent>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
	init = true;
	ui.setupUi(this);


	setCurrentFile("Untitled");

	connect(ui.actionNew,	SIGNAL(triggered()),	this,	SLOT(newFile()));
	connect(ui.actionOpen,	SIGNAL(triggered()),	this,	SLOT(loadFile()));
	connect(ui.actionSave,	SIGNAL(triggered()),	this,	SLOT(saveFile()));
	connect(ui.actionSaveAs,SIGNAL(triggered()),	this,	SLOT(saveFileAs()));
	connect(ui.actionQuit,	SIGNAL(triggered()),	this,	SLOT(close()));

	connect(ui.pageList, SIGNAL(currentRowChanged(int)), this, SLOT(changePage(int)));

	EditedFilesPage *editedFilesPage = new EditedFilesPage(ui.stackedWidget);
	FileEditPage *fileEditPage = new FileEditPage(ui.stackedWidget);

	fileEditPage->setFileModel(editedFilesPage->model());


	ui.stackedWidget->removeWidget(ui.stackedWidget->currentWidget());
//	ui.stackedWidget->removeTab(ui.stackedWidget->currentIndex());
	addPage(tr("General Info"),		new GeneralPage(ui.stackedWidget));
	addPage(tr("Authors"),			new AuthorGroupPage(ui.stackedWidget));
	addPage(tr("Changelog"),		new ChangelogPage(ui.stackedWidget));
	addPage(tr("SQL"),				new SqlPage(ui.stackedWidget));
	addPage(tr("Copy Files"),		new FilePage(ui.stackedWidget));
	addPage(tr("Files to Edit"),	editedFilesPage);
	addPage(tr("File Edits"),		fileEditPage);
	addPage(tr("Do-It-Yourself"),	new DIYPage(ui.stackedWidget));

	ui.pageList->setCurrentRow(0);

	{
		// GAH!!!
		QList<int> sizes;
		sizes << 100 << 1000;
		ui.splitter->setSizes(sizes);
		ui.splitter->setCollapsible(1, false);
	}
	newFile();
	init = false;
}

MainWindow::~MainWindow()
{

}

void MainWindow::newFile()
{
	if (!init)
	{
		if (!askSave())
		{
			return;
		}
	}
	setCurrentFile("Untitled");
	ModXData data;
	data.authorGroup << Author();
	data.history << ChangelogEntry();
	setData(&data);
}

void MainWindow::loadFile()
{
	QString fileName = QFileDialog::getOpenFileName(
			this,
			tr("Open MODX file..."),
			QDesktopServices::storageLocation(QDesktopServices::HomeLocation),
			"MODX files (*.xml *.modx)");

	if (fileName == "")
		return;

	setCurrentFile(fileName);

	ModXReader reader;
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);

	if(!reader.read(&file))
	{
qDebug() << "FAIL!!";
qDebug() << reader.errorString();
		ui.statusBar->showMessage(tr("Failed opening file: %1. Error: %2").arg(file.fileName()).arg(reader.errorString()));
		return;
	}
qDebug() << "SUCESS!!";

	ModXData *data = reader.data();
	setData(data);
	delete data;

	ui.statusBar->showMessage(tr("Opened file: %1").arg(file.fileName()));
}

bool MainWindow::saveFile()
{
	if (ModXApp::currentFile == "Untitled")
	{
		return saveFileAs();
	}

	ModXData data;

	for (int i = 0; i < ui.stackedWidget->count(); ++i)
	{
		qobject_cast<Page *>(ui.stackedWidget->widget(i))->getData(&data);
	}

	QFile file(ModXApp::currentFile);
	file.open(QIODevice::WriteOnly);

	ModXWriter writer;
	writer.setData(&data);

	writer.write(&file);
	ui.statusBar->showMessage(tr("File Saved"));
	return true;
}


bool MainWindow::saveFileAs()
{
	QString fileName = QFileDialog::getSaveFileName(
			this,
			tr("Save file as..."),
			QDesktopServices::storageLocation(QDesktopServices::HomeLocation),
			"MODX files (*.xml *.modx)");

	if (fileName == "")
		return false;

	setCurrentFile(fileName);
	return saveFile();
}

bool MainWindow::askSave()
{
	int ret = QMessageBox::warning(
				this,
				tr("MODX Editor"),
				tr("Save changes to document?"),
				QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

	switch (ret)
	{
		case QMessageBox::Save:
			return saveFile();
		break;
		case QMessageBox::Discard:
			return true;
		break;
		case QMessageBox::Cancel:
		default:
			return false;
		break;
	}
}

void MainWindow::closeEvent(QCloseEvent *e)
{
	if (askSave())
	{
		e->accept();
	}
	else
	{
		e->ignore();
	}
}

void MainWindow::changePage(int i)
{
	ui.stackedWidget->setCurrentIndex(i);
}

void MainWindow::on_actionAbout_triggered()
{
	AboutDialog dialog(this);
	dialog.exec();
}


void MainWindow::addPage(const QString &title, Page *page)
{
	page->show();
	ui.pageList->addItem(title);
	ui.stackedWidget->addWidget(page);
//	ui.stackedWidget->addTab(page, title);
}

void MainWindow::setData(const ModXData *data)
{
	for (int i = 0; i < ui.stackedWidget->count(); ++i)
	{
		qobject_cast<Page *>(ui.stackedWidget->widget(i))->setData(data);
	}
}

void MainWindow::setCurrentFile(const QString &file)
{
	ModXApp::currentFile = file;
	setWindowTitle(tr("MODX Editor - %1 [*]").arg(file));
}
