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

#include "modxdata.h"

ModXData::ModXData(QObject *parent) : QObject(parent)
{
	sqlDialect = DialectSqlParser;
	installTime = 60;
	installLevel = LevelIntermediate;
	if (init)
		return;
	setUp();
}

void ModXData::setUp()
{
	sqlDialects.insert(DialectSqlParser,"sql-parser");
	sqlDialects.insert(DialectMySql,	"mysql");
	sqlDialects.insert(DialectMySql40,	"mysql_40");
	sqlDialects.insert(DialectMySql41,	"mysql_41");
	sqlDialects.insert(DialectMySqli,	"mysqli");
	sqlDialects.insert(DialectMySql4,	"mysql4");
	sqlDialects.insert(DialectMsAccess,	"mssaccess");
	sqlDialects.insert(DialectOracle,	"oracle");
	sqlDialects.insert(DialectPostgres,	"postgres");
	sqlDialects.insert(DialectDb2,		"db2");
	sqlDialects.insert(DialectFirebird,	"firebird");
	sqlDialects.insert(DialectSqlite,	"sqlite");
}

QMap <ModXData::SqlDialect, QString> ModXData::sqlDialects;
const QStringList ModXData::installationLevels = QStringList() << "easy" << "intermediate" << "advanced";
bool ModXData::init = false;



Action::Action()
{
	type = Find;
	if (init)
		return;
	setUp();
}

QMap <Action::Type, QString> Action::types;
QMap <Action::EditType, QString> Action::editTypes;


bool Action::init = false;

Author::Author()
{
	userName = "new Author";
}

ChangelogEntry::ChangelogEntry()
{
	version = "1.0.0";
}

void Action::setUp()
{
	types.insert(Action::Find,			"Find");
	types.insert(Action::Edit,			"Edit");
	types.insert(Action::InlineFind,	"Inline-Find");
	types.insert(Action::InlineEdit,	"Inline-Edit");

	editTypes.insert(Action::AfterAdd,	"after-add");
	editTypes.insert(Action::BeforeAdd,	"before-add");
	editTypes.insert(Action::Replace,	"replace-with");
	editTypes.insert(Action::Operation,	"operation");
}

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const ModXData &d)
{
	dbg.nospace() << "ModXData (";
	dbg.nospace() << "\n\ttitle = " << d.title;
	dbg.nospace() << "\n\tdescription = " << d.description;
	dbg.nospace() << "\n\tauthorNotes = " << d.authorNotes;
	dbg.nospace() << "\n\tauthorGroup = " << d.authorGroup;
	dbg.nospace() << "\n\thistory = " << d.history;
	dbg.nospace() << "\n\tlicense = " << d.license;
	dbg.nospace() << "\n\tinstallLevel = " << d.installLevel;
	dbg.nospace() << "\n\tinstallTime = " << d.installTime;

	dbg.nospace() << "\n\tactions = " << d.actions;

	dbg.nospace() << "\n\tdiy = " << d.diy;

	dbg.nospace() << "\n)";

	return dbg.space();
}

QDebug operator<<(QDebug dbg, const Author &a)
{
	dbg.nospace() << "Author (";
	dbg.nospace() << "\n\t" << a.userName;
	dbg.nospace() << "\n\t" << a.realName;
	dbg.nospace() << "\n\t" << a.homePage;
	dbg.nospace() << "\n\t" << a.contributionStatus;
	dbg.nospace() << "\n\t" << a.contributionFrom;
	dbg.nospace() << "\n\t" << a.contributionTo;
	dbg.nospace() << "\n)";
	return dbg.space();
}

QDebug operator<<(QDebug dbg, const ChangelogEntry &e)
{
	dbg.nospace() << "ChangelogEntry (";
	dbg.nospace() << "\n\tdate = " << e.date.toString(Qt::ISODate);
	dbg.nospace() << "\n\tversion = " << e.version;
	dbg.nospace() << "\n\tChanges = " << e.changes;
	dbg.nospace() << "\n)";
	return dbg.space();
}

QDebug operator<<(QDebug dbg, const Action &a)
{
	dbg.nospace() << "Action (";
	dbg.nospace() << "\n\t Type = " << a.type;
	switch (a.type)
	{
		case Action::Find:
		case Action::InlineFind:
			dbg.nospace() << "\n\tfind = " << a.find;
		break;
		case Action::Edit:
		case Action::InlineEdit:
			dbg.nospace() << "\n\teditType = " << a.editType;
			dbg.nospace() << "\n\tedit = " << a.edit;
		break;
	}
	dbg.nospace() << "\n)";
	return dbg.space();
}

#endif // QT_BO_DEBUG
