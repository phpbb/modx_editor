#ifndef MODXWRITER_H
#define MODXWRITER_H

#include <QXmlStreamWriter>

class ModXData;

class ModXWriter : public QXmlStreamWriter
{
public:
	ModXWriter();

	void setData(const ModXData *data);

	void write(QIODevice *device);

private:
	void writeHeader();
	void writeAuthorGroup();
	void writeHistory();

	void writeActionGroup();

	const ModXData *m_data;
};

#endif // MODXWRITER_H
