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
	ModXData *data;

	Ui::MainWindowClass ui;
	bool init;
};

#endif // MAINWINDOW_H
