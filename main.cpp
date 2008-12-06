#include "modxapp.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setApplicationName("ModX Editor");
	QCoreApplication::setApplicationVersion("1.0.0-alpha1");
	ModXApp app(argc, argv);
	return app.exec();
}
