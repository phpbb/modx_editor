#include "generalpage.h"

#include "../modxdata.h"

GeneralPage::GeneralPage(QWidget *parent) :
	Page(parent){
   ui.setupUi(this);
}

void GeneralPage::setData(const ModXData *data)
{
	ui.title->setText(data->title["en"]);
	ui.version->setText(data->version);
	ui.description->setPlainText(data->description["en"]);
	ui.authorNotes->setPlainText(data->authorNotes["en"]);
	ui.license->setText(data->license);

	ui.installLevel->setText(data->installLevel);
	ui.installTime->setValue(data->installTime);
	ui.targetVersion->setText(data->targetVersion);
}

void GeneralPage::getData(ModXData *data)
{
	data->title["en"] = ui.title->text();
	data->version = ui.version->text();
	data->description["en"] = ui.description->toPlainText();
	data->authorNotes["en"] = ui.authorNotes->toPlainText();
	data->license = ui.license->text();

	data->installLevel = ui.installLevel->text();
	data->installTime = ui.installTime->value();
	data->targetVersion = ui.targetVersion->text();
}


void GeneralPage::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
		ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
