#include "modxapp.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setApplicationVersion("0.5.0");
	ModXApp app(argc, argv);
	return app.exec();
}
