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

#include <Qdebug>

QDebug operator<<(QDebug dbg, const Version &v);

#endif

#endif // VERSION_H
