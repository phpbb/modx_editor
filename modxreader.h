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

	QList<Action> readOpen();
	QList<Action> readEdit();

	QList<Action> readInlineEdit();

	ModXData *m_data;

};

QDebug operator<<(QDebug dbg, const QXmlStreamAttribute &a);

#endif // MODXREADER_H
