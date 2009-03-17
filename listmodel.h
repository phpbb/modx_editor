/***************************************************************************
 *   Copyright (C) 2009 by the phpBB Group                                 *
 *   phpbb.com                                                             *
 *                                                                         *
 *  This file is part of MODX Editor.                                      *
 *                                                                         *
 *  MODX Editor is free software: you can redistribute it and/or modify    *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  MODX Editor is distributed in the hope that it will be useful,         *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with MODX Editor.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

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

		switch (role)
		{
			case Qt::DisplayRole:
				return QVariant(QString(m_data.at(index.row())));
			case Qt::EditRole:
				return QVariant::fromValue(m_data.at(index.row()));
			default:
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
//		emit dataChanged(createIndex(row - 1, 0), createIndex(row, 0));
		reset();
		return row - 1;
	}

	int moveDown(int row)
	{
		if (m_data.isEmpty() || row == rowCount() - 1)
			return row;

		m_data.swap(row, row + 1);
//		emit dataChanged(createIndex(row, 0), createIndex(row + 1, 0));
		reset();
		return row + 1;
	}

private:
	QList<T> m_data;
};

#endif // LISTMODEL_H
