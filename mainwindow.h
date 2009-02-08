#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"

class Page;
class ModXData;
class PagePanel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

public slots:
	void newFile();
	void loadFile();
	bool saveFile();
	bool saveFileAs();
	bool askSave();

	void changePage(int i);

	void on_actionAbout_triggered();

protected:
	void closeEvent(QCloseEvent *event);

private:
	void addPage(const QString &title, Page *page);
	void setData(const ModXData *data);

	void setCurrentFile(const QString &file);

	PagePanel *pagePanel;

	Ui::MainWindowClass ui;
	bool init;
};

#endif // MAINWINDOW_H
