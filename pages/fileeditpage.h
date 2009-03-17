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
