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
