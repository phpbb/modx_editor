#ifndef MODXAPP_H
#define MODXAPP_H

#include <QApplication>
#include "mainwindow.h"


class ModXApp : public QApplication
{
public:
	ModXApp(int argc, char **argv);
	virtual ~ModXApp();

	static QString currentFile;

private:
	MainWindow *mainWin;
};

#endif // MODXAPP_H
