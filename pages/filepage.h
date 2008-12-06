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
	void on_setLatestVersion_clicked();

protected:
    virtual void changeEvent(QEvent *e);

private:
	void setRootDir();

	QFileSystemModel *fileModel;
	Ui::FilePage ui;
};

#endif // FILEPAGE_H
