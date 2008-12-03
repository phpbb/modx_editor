#include "modxapp.h"

ModXApp::ModXApp(int argc, char **argv) : QApplication(argc, argv)
{
	mainWin = new MainWindow();

	mainWin->show();
}

ModXApp::~ModXApp()
{
	delete mainWin;
}

QString ModXApp::currentFile = "Untitled";
