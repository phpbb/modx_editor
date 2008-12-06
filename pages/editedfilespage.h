#ifndef EDITEDFILESPAGE_H
#define EDITEDFILESPAGE_H

#include "page.h"

#include "listmodel.h"

#include "ui_editedfilespage.h"

class QFileSystemModel;

class EditedFilesPage : public Page {
    Q_OBJECT
    Q_DISABLE_COPY(EditedFilesPage)
public:
    explicit EditedFilesPage(QWidget *parent = 0);

	virtual void setData(const ModXData *data);
	virtual void getData(ModXData *data);

	QAbstractItemModel *model() const
	{ return m_model; }

public slots:
	void on_addFile_clicked();
	void on_addFiles_clicked();
	void on_removeFiles_clicked();

	void on_phpbbRootPath_textChanged(const QString &path);
	void on_browseButton_clicked();

protected:
	virtual void changeEvent(QEvent *e);

private:
	ListModel<QString> *m_model;
	QFileSystemModel *fileModel;

	Ui::EditedFilesPage ui;
};

#endif // EDITEDFILESPAGE_H
