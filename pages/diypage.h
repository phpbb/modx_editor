#ifndef DIYPAGE_H
#define DIYPAGE_H

#include "page.h"

#include "ui_diypage.h"

class DIYPage : public Page {
    Q_OBJECT
    Q_DISABLE_COPY(DIYPage)
public:
    explicit DIYPage(QWidget *parent = 0);

	virtual void setData(const ModXData *data);
	virtual void getData(ModXData *data);

protected:
    virtual void changeEvent(QEvent *e);

private:
	Ui::DIYPage ui;
};

#endif // DIYPAGE_H
