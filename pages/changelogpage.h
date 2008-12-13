#ifndef CHANGELOGPAGE_H
#define CHANGELOGPAGE_H

#include "page.h"
#include "modxdata.h"
#include "listmodel.h"

#include "ui_changelogpage.h"

class ChangelogSortFilterProxyModel;

class ChangelogPage : public Page {
    Q_OBJECT
    Q_DISABLE_COPY(ChangelogPage)
public:
	explicit ChangelogPage(QWidget *parent = 0);

	virtual void setData(const ModXData *data);
	virtual void getData(ModXData *data);

protected slots:
	void updateEntry(const QItemSelection &, const QItemSelection &);
	void updateVersion(const QString &newName);

	void addVersion();
	void removeVersion();

protected:
    virtual void changeEvent(QEvent *e);

private:
	ListModel<ChangelogEntry> *model;
	ChangelogSortFilterProxyModel *proxyModel;

	Ui::ChangelogPage ui;
};

#endif // CHANGELOGPAGE_H
