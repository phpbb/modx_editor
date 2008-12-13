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

//typedef QString Version;

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

// --------------------------------------------------------------
// @todo Why does macro fail, while macro contents works?
/*
Q_DECLARE_META_TYPE(ChangelogEntry);
Q_DECLARE_META_TYPE(Author);
Q_DECLARE_META_TYPE(Action);

*/
QT_BEGIN_NAMESPACE
template <>
struct QMetaTypeId< ChangelogEntry >
{
	enum { Defined = 1 };
	static int qt_metatype_id()
		{
			static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
			if (!metatype_id)
				metatype_id = qRegisterMetaType< ChangelogEntry >("ChangelogEntry");
			return metatype_id;
		}
};
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
template <>
struct QMetaTypeId< Action >
{
	enum { Defined = 1 };
	static int qt_metatype_id()
		{
			static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
			if (!metatype_id)
				metatype_id = qRegisterMetaType< Action >("Action");
			return metatype_id;
		}
};
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
template <>
struct QMetaTypeId< Author >
{
	enum { Defined = 1 };
	static int qt_metatype_id()
		{
			static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
			if (!metatype_id)
				metatype_id = qRegisterMetaType< Author >("Author");
			return metatype_id;
		}
};
QT_END_NAMESPACE
// --------------------------------------------------------------

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const ModXData &d);
QDebug operator<<(QDebug dbg, const Author &a);
QDebug operator<<(QDebug dbg, const ChangelogEntry &a);
QDebug operator<<(QDebug dbg, const Action &a);
#endif

#endif // MODXDATA_H
