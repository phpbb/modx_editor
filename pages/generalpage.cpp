#include "generalpage.h"

#include "../modxdata.h"

GeneralPage::GeneralPage(QWidget *parent) :
	Page(parent){
   ui.setupUi(this);

   QStringList licenses;
   licenses	<< "http://opensource.org/licenses/agpl-v3.html GNU Affero General Public License v3"
			<< "http://opensource.org/licenses/gpl-license.php GNU General Public License v2"
			<< "http://opensource.org/licenses/gpl-license.php GNU General Public License v3"
			<< "http://www.apache.org/licenses/ Apache License, Version 2.0"
			<< "http://opensource.org/licenses/lgpl-license.php GNU Lesser General Public License v2"
			<< "http://opensource.org/licenses/lgpl-license.php GNU Lesser General Public License v3"
			<< "http://opensource.org/licenses/bsd-license.php BSD License";
   ui.license->addItems(licenses);

   QStringList installationLevels;
   installationLevels	<< tr("Easy")
						<< tr("Intermediate")
						<< tr("Hard");

   ui.installLevel->addItems(installationLevels);
}

void GeneralPage::setData(const ModXData *data)
{
	ui.title->setText(data->title["en"]);
	ui.version->setText(data->version);
	ui.description->setPlainText(data->description["en"]);
	ui.authorNotes->setPlainText(data->authorNotes["en"]);
	ui.license->setEditText(data->license);

	ui.installLevel->setCurrentIndex(int(data->installLevel));
	ui.installTime->setValue(data->installTime);
	ui.targetVersion->setText(data->targetVersion);
}

void GeneralPage::getData(ModXData *data)
{
	data->title["en"] = ui.title->text();
	data->version = ui.version->text();
	data->description["en"] = ui.description->toPlainText();
	data->authorNotes["en"] = ui.authorNotes->toPlainText();
	data->license = ui.license->currentText();

	data->installLevel = ModXData::InstallationLevel(ui.installLevel->currentIndex());
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
