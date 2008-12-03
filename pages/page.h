#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

class ModXData;

class Page : public QWidget
{
	Q_OBJECT
	Q_DISABLE_COPY(Page)
public:
	explicit Page(QWidget *parent) : QWidget(parent) {}
	virtual ~Page() {}

	virtual void setData(const ModXData *data) = 0;
	virtual void getData(ModXData *data) = 0;
};

#endif // PAGE_H
