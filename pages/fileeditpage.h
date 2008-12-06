#ifndef FILEEDITPAGE_H
#define FILEEDITPAGE_H

#include "page.h"
#include "listmodel.h"
#include "modxdata.h"

#include "ui_fileeditpage.h"

class FileEditPage : public Page {
    Q_OBJECT
    Q_DISABLE_COPY(FileEditPage)
public:
	explicit FileEditPage(QWidget *parent = 0);

	virtual void setData(const ModXData *data);
	virtual void getData(ModXData *data);

	void setFileModel(QAbstractItemModel *model);

protected slots:
	void updateActionModel(const QString &file = "");

	void updateAction(const QItemSelection &, const QItemSelection &);
	void on_actionType_currentIndexChanged();
	void on_add_clicked();
	void on_remove_clicked();
	void on_moveUp_clicked();
	void on_moveDown_clicked();

protected:
	virtual void changeEvent(QEvent *e);

private:
	void retranslateUi();
	void clearFields();

	ListModel<Action> *model;

	QMap< QString, QList<Action> > actions;

	QString currentFile;

	Ui::FileEditPage ui;
};

#endif // FILEEDITPAGE_H
