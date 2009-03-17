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

#include "authorgrouppage.h"

#include <QListWidgetItem>

AuthorGroupPage::AuthorGroupPage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);

	model = new ListModel<Author>(this);

	ui.authorList->setModel(model);

	connect(ui.authorList->selectionModel(),	SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),	this,	SLOT(updateDetails(const QItemSelection &, const QItemSelection &)));
	connect(ui.userName,						SIGNAL(textChanged(const QString &)),										this,	SLOT(updateUserName(const QString &)));
	connect(ui.add,								SIGNAL(clicked()),															this,	SLOT(addAuthor()));
	connect(ui.remove,							SIGNAL(clicked()),															this,	SLOT(removeAuthor()));
	connect(ui.moveUp,							SIGNAL(clicked()),															this,	SLOT(moveUp()));
	connect(ui.moveDown,						SIGNAL(clicked()),															this,	SLOT(moveDown()));
}

void AuthorGroupPage::setData(const ModXData *data)
{
	model->setList(data->authorGroup);
	if (data->authorGroup.isEmpty())
	{
		updateDetails(QItemSelection(), QItemSelection());
	}
	else
	{
		ui.authorList->selectionModel()->select(model->index(0, 0), QItemSelectionModel::SelectCurrent);
	}
}

void AuthorGroupPage::getData(ModXData *data)
{
	QItemSelection selection = ui.authorList->selectionModel()->selection();
	updateDetails(selection, selection);
	data->authorGroup = model->list();
}

void AuthorGroupPage::updateDetails(const QItemSelection &newSelection, const QItemSelection &oldSelection)
{
	if (oldSelection.count())
	{
		QModelIndexList list = oldSelection.indexes();

		if (!list.isEmpty())
		{
			QModelIndex index = list.at(0);
			Author author = model->data(index, Qt::EditRole).value<Author>();

			author.userName = ui.userName->text();
			author.realName = ui.realName->text();
			author.email	= ui.email->text();
			author.homePage = ui.homePage->text();
			author.contributionStatus = ui.contributionStatus->text();
			author.contributionFrom = ui.contributionFrom->date();
			author.contributionTo = ui.contributionTo->date();

			model->setData(index, QVariant::fromValue(author));
		}
	}

	Author author;
	if (newSelection.count())
	{
		QModelIndexList list = newSelection.indexes();
		if (!list.isEmpty())
		{
			author = model->data(list.at(0), Qt::EditRole).value<Author>();
		}
	}

	ui.userName->setText(author.userName);
	ui.realName->setText(author.realName);
	ui.email->setText(author.email);

	ui.homePage->setText(author.homePage);
	ui.contributionStatus->setText(author.contributionStatus);
	ui.contributionFrom->setDate(author.contributionFrom);
	ui.contributionTo->setDate(author.contributionTo);

}

void  AuthorGroupPage::updateUserName(const QString &newName)
{
	QModelIndexList list = ui.authorList->selectionModel()->selection().indexes();
	if (list.isEmpty())
		return;
	QModelIndex index = list.at(0);
	Author author = model->data(index, Qt::EditRole).value<Author>();
	author.userName = newName;
	model->setData(index, QVariant::fromValue(author));
}

void AuthorGroupPage::addAuthor()
{
	model->insertRow(model->rowCount(), QModelIndex());
	ui.authorList->selectionModel()->clearSelection();
	ui.authorList->selectionModel()->select(model->index(model->rowCount() - 1, 0), QItemSelectionModel::Select);
}

void AuthorGroupPage::removeAuthor()
{
	QModelIndexList selected = ui.authorList->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;
	int row = selected.at(0).row();
	model->removeRow(row);
	if (model->rowCount())
	{
		ui.authorList->selectionModel()->select(model->index(row ? row - 1 : 0, 0), QItemSelectionModel::SelectCurrent);
	}
}

void AuthorGroupPage::moveUp()
{
	QModelIndexList selected = ui.authorList->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;
	int row = selected.at(0).row();

	row = model->moveUp(row);
	ui.authorList->selectionModel()->select(model->index(row, 0), QItemSelectionModel::SelectCurrent);

}

void AuthorGroupPage::moveDown()
{
	QModelIndexList selected = ui.authorList->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;
	int row = selected.at(0).row();

	row = model->moveDown(row);
	ui.authorList->selectionModel()->select(model->index(row, 0), QItemSelectionModel::SelectCurrent);
}

void AuthorGroupPage::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
		ui.retranslateUi(this);
        break;
    default:
        break;
    }
}

