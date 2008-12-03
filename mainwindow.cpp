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
#include "pages/diypage.h"


#include <QFileDialog>
#include <QDesktopServices>
#include <QListWidgetItem>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
	ui.setupUi(this);

	setCurrentFile("Untitled");

	connect(ui.actionNew,	SIGNAL(triggered()),	this,	SLOT(newFile()));
	connect(ui.actionOpen,	SIGNAL(triggered()),	this,	SLOT(loadFile()));
	connect(ui.actionSave,	SIGNAL(triggered()),	this,	SLOT(saveFile()));
	connect(ui.actionSaveAs,SIGNAL(triggered()),	this,	SLOT(saveFileAs()));
	connect(ui.actionQuit,	SIGNAL(triggered()),	qApp,	SLOT(quit()));

	connect(ui.pageList, SIGNAL(currentRowChanged(int)), this, SLOT(changePage(int)));

	ui.stackedWidget->removeWidget(ui.stackedWidget->currentWidget());
	addPage(tr("General Info"),		new GeneralPage(ui.stackedWidget));
	addPage(tr("Authors"),			new AuthorGroupPage(ui.stackedWidget));
	addPage(tr("Changelog"),		new ChangelogPage(ui.stackedWidget));
	addPage(tr("SQL"),				new SqlPage(ui.stackedWidget));
	addPage(tr("Files"),			new FilePage(ui.stackedWidget));
	addPage(tr("Do-It-Yourself"),	new DIYPage(ui.stackedWidget));

	ui.pageList->setCurrentRow(0);
}

MainWindow::~MainWindow()
{

}

void MainWindow::newFile()
{
	ModXData data;
	setData(&data);
}

void MainWindow::loadFile()
{
	QString fileName = QFileDialog::getOpenFileName(
			this,
			tr("Open ModX file..."),
			QDesktopServices::storageLocation(QDesktopServices::HomeLocation),
			"ModX files (*.xml *.modx)");

	if (fileName == "")
		return;

	setCurrentFile(fileName);

	ModXReader reader;
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);

	if(!reader.read(&file))
	{
qDebug() << "FAIL!!";
		return;
	}
qDebug() << "SUCESS!!";

	ModXData *data = reader.data();


	setData(data);

	delete data;
}

void MainWindow::saveFile()
{
	if (ModXApp::currentFile == "Untitled")
	{
		saveFileAs();
		return;
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
}


void MainWindow::saveFileAs()
{
	QString fileName = QFileDialog::getSaveFileName(
			this,
			tr("Save file as..."),
			QDesktopServices::storageLocation(QDesktopServices::HomeLocation),
			"ModX files (*.xml *.modx)");

	if (fileName == "")
		return;

	setCurrentFile(fileName);
	saveFile();
}


void MainWindow::changePage(int i)
{
	ui.stackedWidget->setCurrentIndex(i);
}

void MainWindow::addPage(const QString &title, Page *page)
{
	page->show();
	ui.pageList->addItem(title);
	ui.stackedWidget->addWidget(page);
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
	setWindowTitle(tr("ModX Editor - %1 [*]").arg(file));
}
