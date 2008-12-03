#include "sqlpage.h"

#include "modxdata.h"

SqlPage::SqlPage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);
}

void SqlPage::setData(const ModXData *data)
{
	ui.sql->setText(data->sql.join("\n\n"));
}

void SqlPage::getData(ModXData *data)
{
	data->sql << ui.sql->toPlainText();
}


void SqlPage::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
		ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
