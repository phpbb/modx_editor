#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include <QItemSelectionModel>

#include <QDebug>

template<typename T> class ListModel : public QAbstractListModel
{
public:
	ListModel(QObject *parent = 0) : QAbstractListModel(parent) {}

	QList<T> list() const
	{
		return m_data;
	}

	void setList(QList<T> data)
	{
		m_data = data;
		reset();
	}

	int rowCount(const QModelIndex &parent = QModelIndex()) const
	{
		if (parent != QModelIndex())
		{
			return 0;
		}

		return m_data.count();
	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
	{
		if (index.row() < 0 || index.row() > rowCount() - 1)
			return QVariant();

		if (role == Qt::DisplayRole)
		{
			return QVariant(QString(m_data.at(index.row())));
		}
		else if (role == Qt::EditRole)
		{
			return QVariant::fromValue(m_data.at(index.row()));
		}
		else
		{
			return QVariant();
		}
	}

	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
	{
		if (role != Qt::EditRole)
			return false;

		m_data[index.row()] = value.value<T>();
		emit dataChanged(index, index);
		return true;
	}

	bool insertRows(int row, int count, const QModelIndex &parent)
	{
		if (parent != QModelIndex())
			return false;

		beginInsertRows(parent, row, row + count);
		for (int i = 0; i < count; ++i)
		{
			m_data.insert(row, T());
		}
		endInsertRows();
		return true;
	}

	bool removeRows(int row, int count,  const QModelIndex &parent)
	{
		if (parent != QModelIndex())
			return false;

		beginRemoveRows(parent, row, row + count);
		for (int i = 0; i < count; ++i)
		{
			m_data.removeAt(row);
		}
		endRemoveRows();

		return true;
	}

	int moveUp(int row)
	{
		if (!row || m_data.isEmpty())
			return row;

		m_data.swap(row, row - 1);
		emit dataChanged(createIndex(row - 1, 0), createIndex(row, 0));
		return row - 1;
	}

	int moveDown(int row)
	{
		if (m_data.isEmpty() || row == rowCount() - 1)
			return row;

		m_data.swap(row, row + 1);
		emit dataChanged(createIndex(row, 0), createIndex(row + 1, 0));
		return row + 1;
	}

private:
	QList<T> m_data;
};

#endif // LISTMODEL_H
