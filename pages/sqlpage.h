#ifndef SQLPAGE_H
#define SQLPAGE_H

#include "page.h"

#include "ui_sqlpage.h"

class SqlPage : public Page {
    Q_OBJECT
    Q_DISABLE_COPY(SqlPage)
public:
	explicit SqlPage(QWidget *parent = 0);

	virtual void setData(const ModXData *data);
	virtual void getData(ModXData *data);

protected:
    virtual void changeEvent(QEvent *e);

private:
	Ui::SqlPage ui;
};

#endif // SQLPAGE_H
