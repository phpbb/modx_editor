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
