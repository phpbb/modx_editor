#include "changelogsortfilterproxymodel.h"

#include "modxdata.h"

ChangelogSortFilterProxyModel::ChangelogSortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

bool ChangelogSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right ) const
{
	QVariant leftData = sourceModel()->data(left, sortRole());
	QVariant rightData = sourceModel()->data(right, sortRole());

	if (!leftData.canConvert<ChangelogEntry>() || !rightData.canConvert<ChangelogEntry>())
	{
		return QSortFilterProxyModel::lessThan(left, right);
	}
	return leftData.value<ChangelogEntry>() < rightData.value<ChangelogEntry>();
}
