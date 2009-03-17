/***************************************************************************
 *   Copyright (C) 2009 by the phpBB Group                                 *
 *   phpbb.com                                                             *
 *                                                                         *
 *  This file is part of MODX Editor.                                      *
 *                                                                         *
 *  MODX Editor is free software: you can redistribute it and/or modify    *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  MODX Editor is distributed in the hope that it will be useful,         *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with MODX Editor.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

#include "generalpage.h"

#include "modxdata.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

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

   manager = NULL;
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

void GeneralPage::on_setLatestVersion_clicked()
{
	if (manager == NULL)
	{
		manager = new QNetworkAccessManager(this);
		connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handleNetworkReply(QNetworkReply *)));
	}
	manager->get(QNetworkRequest(QUrl("http://www.phpbb.com/updatecheck/30x.txt")));
}

void GeneralPage::handleNetworkReply(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		return;
	}
	QString latestVersion(reply->readLine(1024));
	ui.targetVersion->setText(latestVersion.trimmed());
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
