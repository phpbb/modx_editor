#include "diypage.h"

#include "modxdata.h"

DIYPage::DIYPage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);
}

void DIYPage::setData(const ModXData *data)
{
	ui.diy->setText(data->diy["en"]);
}
void DIYPage::getData(ModXData *data)
{
	data->diy["en"] = ui.diy->toPlainText();
}

void DIYPage::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
		ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
