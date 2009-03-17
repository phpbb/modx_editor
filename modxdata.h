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

#ifndef MODXDATA_H
#define MODXDATA_H

#include "version.h"

#include <QObject>
#include <QMetaType>
#include <QDate>
#include <QStringList>
#include <QDebug>

class Author;
class ChangelogEntry;
class Action;

class ModXData : public QObject
{
	Q_OBJECT

public:
	enum SqlDialect
	{
		DialectSqlParser,
		DialectMySql,
		DialectMySql40,
		DialectMySql41,
		DialectMySqli,
		DialectMySql4,
		DialectMsAccess,
		DialectOracle,
		DialectPostgres,
		DialectDb2,
		DialectFirebird,
		DialectSqlite,
	};

	enum InstallationLevel
	{
		LevelEasy,
		LevelIntermediate,
		LevelAdvanced
	};

	ModXData(QObject *parent = 0);

	QMap<QString, QString> title;
	QMap<QString, QString> description;
	QMap<QString, QString> authorNotes;
	QList<Author> authorGroup;
	QList<ChangelogEntry> history;

	QString license;

	Version version;
	Version targetVersion;
	InstallationLevel installLevel;
	quint32 installTime;

	SqlDialect sqlDialect;
	QStringList sql;

	bool copyFiles;
	QMap<QString, QString> copyInstructions;

	QMap<QString, QString> diy;

	QMap<QString, QList<Action> > actions;

	static QMap <SqlDialect, QString> sqlDialects;
	static const QStringList installationLevels;

private:
	static bool init;

	static void setUp();
};

class Author
{

public:

	Author();

	operator QString() const
	{
		return userName;
	}

	bool operator<(const Author &other) const
	{
		return userName < other.userName;
	}

	QString realName;
	QString userName;
	QString email;
	QString homePage;
	QString contributionStatus;
	QDate contributionFrom;
	QDate contributionTo;
};


class ChangelogEntry
{

public:
	ChangelogEntry();

	operator QString() const
	{
		return version;
	}

	QDate date;
	Version version;
	QMap<QString, QStringList> changes;

	bool operator<(const ChangelogEntry &other) const
	{
		return version < other.version;
	}
};

class Action
{

public:

	enum Type
	{
		Find,
		Edit,
		InlineFind,
		InlineEdit
	};

	enum EditType
	{
		AfterAdd,
		BeforeAdd,
		Replace,
		Operation
	};

	Action();

	operator QString() const
	{
/*		switch (type)
		{
			case Edit:
			case InlineEdit:
				return types[type] + ", " + editTypes[editType];
			default:
				return types[type];
		}
*/
		return types[type];
	}

	// All types
	Type type;

	// Find/InlineEdit type
	QString find;

	// Edit/InlinEdit type
	EditType editType;

	// Edit/InlineEdit type
	QString edit;

	static QMap <Type, QString> types;
	static QMap <EditType, QString> editTypes;

private:
	static bool init;

	static void setUp();
};

Q_DECLARE_METATYPE(ChangelogEntry);
Q_DECLARE_METATYPE(Author);
Q_DECLARE_METATYPE(Action);


#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const ModXData &d);
QDebug operator<<(QDebug dbg, const Author &a);
QDebug operator<<(QDebug dbg, const ChangelogEntry &a);
QDebug operator<<(QDebug dbg, const Action &a);
#endif

#endif // MODXDATA_H
