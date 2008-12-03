#ifndef MODXDATA_H
#define MODXDATA_H

#include <QObject>
#include <QMetaType>
#include <QDate>
#include <QStringList>
#include <QDebug>

class Author;
class ChangelogEntry;

typedef QString Version;

class ModXData : public QObject
{
	Q_OBJECT

public:

	ModXData(QObject *parent = 0);

	QMap<QString, QString> title;
	QMap<QString, QString> description;
	QMap<QString, QString> authorNotes;
	QList<Author> authorGroup;
	QList<ChangelogEntry> history;

	QString license;

	Version version;
	Version targetVersion;
	QString installLevel;
	quint32 installTime;

	QStringList sql;
	bool copyFiles;
	QMap<QString, QString> copyInstructions;

	QMap<QString, QString> diy;
};

class Author
{

public:

	operator QString() const
	{
		return userName;
	}

	QString realName;
	QString userName;
	QString homePage;
	QString contributionStatus;
	QDate contributionFrom;
	QDate contributionTo;
};


class ChangelogEntry
{

public:

	operator QString() const
	{
		return version;
	}

	QDate date;
	Version version;
	QMap<QString, QStringList> changes;
};

// --------------------------------------------------------------
// @todo Why does macro fail, while macro contents works?
//Q_DECLARE_META_TYPE(ChangelogEntry);

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


QDebug operator<<(QDebug dbg, const ModXData &d);
QDebug operator<<(QDebug dbg, const Author &a);
QDebug operator<<(QDebug dbg, const ChangelogEntry &a);


#endif // MODXDATA_H
