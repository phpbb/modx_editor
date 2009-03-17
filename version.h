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

#ifndef VERSION_H
#define VERSION_H

#include <QString>

class Version
{
public:

	enum VersionType
	{
		NormalVersion,
		RCVersion,
		BetaVersion,
		AlphaVersion,
	};

	Version(int major = 0, int minor = 0, int maintenance = 0, char patch = 0, VersionType type = NormalVersion, int special = 0);
	Version(const QString &version);
	Version(const char *version);
	Version(const Version &other);
	~Version();

	bool isValid() const;

	operator const QString&() const;

	int major() const;
	int minor() const;
	int maintenance() const;
	int patch() const;
	VersionType type() const;
	int special() const;

	bool operator<(const Version &other) const;
	bool operator==(const Version &other) const;

private:
	void parse(const QString &version);

	int m_major;
	int m_minor;
	int m_maintenance;
	char m_patch;
	VersionType m_type;
	int m_special;

	bool valid;

	mutable QString cache;
};

#ifndef QT_NO_DEBUG
#include <QDebug>
QDebug operator<<(QDebug dbg, const Version &v);
#endif

#endif // VERSION_H
