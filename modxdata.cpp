#include "modxdata.h"

#include <QMetaProperty>

ModXData::ModXData(QObject *parent) : QObject(parent)
{
}

QDebug operator<<(QDebug dbg, const ModXData &d)
{
	dbg.nospace() << "ModXData (";
	for (int i = d.metaObject()->propertyOffset(); i < d.metaObject()->propertyCount(); ++i)
	{
	 dbg.nospace() << "\n\t" << d.metaObject()->property(i).name() << " = " <<  d.metaObject()->property(i).read(&d).toString();
	}
	dbg.nospace() << "\n\ttitle = " << d.title;
	dbg.nospace() << "\n\tdescription = " << d.description;
	dbg.nospace() << "\n\tauthorNotes = " << d.authorNotes;
	dbg.nospace() << "\n\tauthorGroup = " << d.authorGroup;
	dbg.nospace() << "\n\thistory = " << d.history;
	dbg.nospace() << "\n\tlicense = " << d.license;
	dbg.nospace() << "\n\tinstallLevel = " << d.installLevel;
	dbg.nospace() << "\n\tinstallTime = " << d.installTime;

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
	return dbg.space();
}

QDebug operator<<(QDebug dbg, const ChangelogEntry &e)
{
	dbg.nospace() << "ChangelogEntry (";
	dbg.nospace() << "\n\tdate = " << e.date.toString(Qt::ISODate);
	dbg.nospace() << "\n\tversion = " << e.version;
	dbg.nospace() << "\n\tChanges = " << e.changes;
	return dbg.space();
}
