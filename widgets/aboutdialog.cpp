#include "aboutdialog.h"

#include "modxapp.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent){
    m_ui.setupUi(this);
	m_ui.copyright->setText(
			tr("&copy; 2009 by the <a href=\"http://%2\">%1</a>")
			.arg(QApplication::organizationName())
			.arg(QApplication::organizationDomain()));
	m_ui.appName->setText(QApplication::applicationName() + " v" + QApplication::applicationVersion());
	setWindowTitle(tr("About %1").arg(QApplication::applicationName()));
}

void AboutDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
