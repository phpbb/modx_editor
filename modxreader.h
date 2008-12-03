#ifndef MODXREADER_H
#define MODXREADER_H

#include <QXmlStreamReader>

#include "modxdata.h"

#include <QDebug>


class ModXReader : public QXmlStreamReader
{
public:
	ModXReader();

	bool read(QIODevice *device);

	ModXData *data() const;

private:
	void readUnknownElement();
	void readModX();

	void readHeader();
	void readAuthorGroup();
	Author readAuthor();

	void readHistory();
	ChangelogEntry readEntry();
	QStringList readChanges();

	void readInstallation();

	void readActionGroup();

	ModXData *m_data;
};

QDebug operator<<(QDebug dbg, const QXmlStreamAttribute &a);

#endif // MODXREADER_H
