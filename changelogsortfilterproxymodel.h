#ifndef CHANGELOGSORTFILTERPROXYMODEL_H
#define CHANGELOGSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class ChangelogSortFilterProxyModel : public QSortFilterProxyModel
{
public:
	ChangelogSortFilterProxyModel(QObject *parent = 0);

protected:

	bool lessThan(const QModelIndex &left, const QModelIndex &right ) const;
};

#endif // CHANGELOGSORTFILTERPROXYMODEL_H
