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

#include "sqlpage.h"

#include "widgets/sqlsyntaxhighlighter.h"
#include "modxdata.h"

SqlPage::SqlPage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);

	new SqlSyntaxHighlighter(ui.sql->document());

	QStringList sqlDialects;
	sqlDialects
			<< tr("SQL Parser")
			<< tr("MySQL")
			<< tr("MySQL 4.0")
			<< tr("MySQL 4.1")
			<< tr("MySQLi")
			<< tr("MySQL 4")
			<< tr("MS Access")
			<< tr("Oracle")
			<< tr("PostgreSQL")
			<< tr("DB2")
			<< tr("Firebird")
			<< tr("SQLite");
	ui.sqlDialect->addItems(sqlDialects);
	ui.sqlDialect->setCurrentIndex(0);
}

void SqlPage::setData(const ModXData *data)
{
	ui.sqlDialect->setCurrentIndex(data->sqlDialect);
	ui.sql->setText(data->sql.join("\n\n"));
}

void SqlPage::getData(ModXData *data)
{
	data->sqlDialect = (ModXData::SqlDialect) ui.sqlDialect->currentIndex();
	data->sql = QStringList(ui.sql->toPlainText());
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
