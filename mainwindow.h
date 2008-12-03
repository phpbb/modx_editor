#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"

class Page;
class ModXData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

public slots:
	void newFile();
	void loadFile();
	void saveFile();
	void saveFileAs();

	void changePage(int i);

private:
	void addPage(const QString &title, Page *page);
	void setData(const ModXData *data);

	void setCurrentFile(const QString &file);

	QString currentFile;

    Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H
