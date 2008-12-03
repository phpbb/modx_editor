#ifndef FILEPAGE_H
#define FILEPAGE_H

#include "page.h"

#include <QDir>

#include "ui_filepage.h"

class QFileSystemModel;

class FilePage : public Page {
    Q_OBJECT
    Q_DISABLE_COPY(FilePage)
public:
	explicit FilePage(QWidget *parent = 0);

	virtual void setData(const ModXData *data);
	virtual void getData(ModXData *data);

protected slots:
	void updateFiles(bool checked);

protected:
    virtual void changeEvent(QEvent *e);

private:

	QFileSystemModel *fileModel;
	Ui::FilePage ui;
};

#endif // FILEPAGE_H
