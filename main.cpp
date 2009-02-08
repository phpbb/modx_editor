#include "modxapp.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setApplicationName("ModX Editor");
	QCoreApplication::setOrganizationName("phpBB Group");
	QCoreApplication::setOrganizationDomain("phpbb.com");
	QCoreApplication::setApplicationVersion("1.0.0A2");

	ModXApp app(argc, argv);
	return app.exec();
}
