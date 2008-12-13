#include "version.h"

#include <QStringList>
#include <QRegExp>


Version::Version(int major, int minor, int maintenance, char patch, VersionType type, int special)
{
	m_major = major;
	m_minor = minor;
	m_maintenance = maintenance;
	m_patch = patch;
	m_type = type;
	m_special = 0;
	if (m_type != NormalVersion)
	{
		m_special = special;
	}
}

Version::Version(const QString &version)
{
	parse(version);
}

Version::Version(const char *version)
{
	parse(QString(version));
}


Version::Version(const Version &other)
{
	valid = other.valid;
	m_major = other.m_major;
	m_minor = other.m_minor;
	m_maintenance = other.m_maintenance;
	m_patch = other.m_patch;
	m_type = other.m_type;
	m_special = other.m_special;
}

Version::~Version()
{
}

bool Version::isValid() const
{
	return valid;
}

Version::operator const QString&() const
{
	if (cache != "")
	{
		return cache;
	}

	cache = QString::number(m_major) + "." + QString::number(m_minor) + "." + QString::number(m_maintenance);
	if (m_patch)
	{
		cache += QChar(m_patch);
	}

	switch(m_type)
	{
		case AlphaVersion:
			cache += "A" + QString::number(m_special);
		break;
		case BetaVersion:
			cache += "B" + QString::number(m_special);
		break;
		case RCVersion:
			cache += "RC" + QString::number(m_special);
		break;
		case NormalVersion:
		default:
		break;
	}

	return cache;
}


int Version::major() const
{
	return  m_major;
}

int Version::minor() const
{
	return m_minor;
}

int Version::maintenance() const
{
	return m_maintenance;
}

int Version::patch() const
{
	return m_patch;
}

Version::VersionType Version::type() const
{
	return m_type;
}

int Version::special() const
{
	return m_special;
}

bool Version::operator<(const Version &other) const
{

	if (m_major < other.m_major)
		return true;
	if (other.m_major < m_major)
		return false;

	if (m_minor < other.m_minor)
		return true;
	if (other.m_minor < m_minor)
		return false;

	if (m_maintenance < other.m_maintenance)
		return true;
	if (other.m_maintenance < m_maintenance)
		return false;

	if (m_patch < other.m_patch)
		return true;
	if (other.m_patch < m_patch)
		return false;

	if (m_type > other.m_type)
		return true;
	if (other.m_type > m_type)
		return false;

	if (m_special < other.m_special)
		return true;

	return false;
}

bool Version::operator==(const Version &other) const
{
	return m_major == other.m_major && m_minor == other.m_minor && m_patch == other.m_maintenance && m_patch == other.m_patch
			&& m_type == other.m_type && m_special == other.m_special;
}


void Version::parse(const QString &version)
{
	QRegExp rx("([1-9][0-9]+|[0-9])\\.([1-9][0-9]+|[0-9])\\.([1-9][0-9]+|[0-9])([a-z])?(?:([AB]|RC)([1-9][0-9]+|[0-9]))?");
	valid = false;
	m_major = 0;
	m_minor = 0;
	m_maintenance = 0;
	m_patch = 0;

	if (!rx.exactMatch(version))
		return;

	valid = true;
	m_major = rx.cap(1).toInt();
	m_minor = rx.cap(2).toInt();
	m_maintenance = rx.cap(3).toInt();

	if (rx.cap(4).size())
	{
		m_patch = rx.cap(4).toAscii().at(0);
	}

	m_type = NormalVersion;
	m_special = 0;

	if (rx.cap(5).size())
	{
		QString type = rx.cap(5);
		if (type == "A")
		{
			m_type = AlphaVersion;
		}
		else if (type == "B")
		{
			m_type = BetaVersion;
		}
		else if (type == "RC")
		{
			m_type = RCVersion;
		}
	}

	if (rx.cap(6).size())
	{
		m_special = rx.cap(6).toInt();
	}
}

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const Version &v)
{
	dbg.nospace() << "Version "/* << QString(v)*/;
	return dbg.space();
}
#endif
