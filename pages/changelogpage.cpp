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

#include "changelogpage.h"

#include "changelogsortfilterproxymodel.h"

#include <QModelIndexList>

ChangelogPage::ChangelogPage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);

	model = new ListModel<ChangelogEntry>(this);
	proxyModel = new ChangelogSortFilterProxyModel(this);
	proxyModel->setSourceModel(model);
	proxyModel->setSortRole(Qt::EditRole);
	proxyModel->sort(0, Qt::DescendingOrder);

	ui.versionList->setModel(proxyModel);
	ui.versionList->setSelectionMode(QAbstractItemView::SingleSelection);

	connect(ui.versionList->selectionModel(),	SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),	this,	SLOT(updateEntry(const QItemSelection &, const QItemSelection &)));
	connect(ui.version,		SIGNAL(textChanged(const QString &)),	this,	SLOT(updateVersion(const QString &)));
	connect(ui.add,			SIGNAL(clicked()),	this,	SLOT(addVersion()));
	connect(ui.remove,		SIGNAL(clicked()),	this,	SLOT(removeVersion()));
}


void ChangelogPage::setData(const ModXData *data)
{
	model->setList(data->history);
	if (data->authorGroup.isEmpty())
	{
		updateEntry(QItemSelection(), QItemSelection());
	}
	else
	{
		ui.versionList->selectionModel()->select(proxyModel->index(0, 0), QItemSelectionModel::SelectCurrent);
	}
}

void ChangelogPage::getData(ModXData *data)
{
	QItemSelection selection = ui.versionList->selectionModel()->selection();
	updateEntry(selection, selection);
	QList<ChangelogEntry> list = model->list();
	qSort(list);
	data->history = list;
}


void ChangelogPage::updateEntry(const QItemSelection &newSelection, const QItemSelection &oldSelection)
{
	if (oldSelection.count())
	{
		QModelIndexList list = proxyModel->mapSelectionToSource(oldSelection).indexes();

		if (!list.isEmpty())
		{
			QModelIndex index = list.at(0);
			ChangelogEntry entry = model->data(index, Qt::EditRole).value<ChangelogEntry>();

			entry.version = ui.version->text();
			entry.date = ui.date->date();
			entry.changes["en"] = ui.changes->toPlainText().split('\n', QString::SkipEmptyParts);

			model->setData(index, QVariant::fromValue(entry));
		}
	}

	ChangelogEntry entry;
	if (newSelection.count())
	{
		QModelIndexList list = proxyModel->mapSelectionToSource(newSelection).indexes();
		if (!list.isEmpty())
		{
			entry = model->data(list.at(0), Qt::EditRole).value<ChangelogEntry>();
		}
	}
	ui.version->setText(entry.version);
	ui.date->setDate(entry.date);
	ui.changes->setText(entry.changes["en"].join("\n"));
}

void  ChangelogPage::updateVersion(const QString &version)
{
	QModelIndexList list = proxyModel->mapSelectionToSource(ui.versionList->selectionModel()->selection()).indexes();
	if (list.isEmpty())
		return;
	QModelIndex index = list.at(0);
	ChangelogEntry entry = model->data(index, Qt::EditRole).value<ChangelogEntry>();
	if (entry.version == version)
		return;
	entry.version = version;
	model->setData(index, QVariant::fromValue(entry));
	proxyModel->invalidate();
}

void ChangelogPage::addVersion()
{
	model->insertRow(model->rowCount());
	proxyModel->invalidate();
	ui.versionList->selectionModel()->clearSelection();
	ui.versionList->selectionModel()->select(proxyModel->mapFromSource(model->index(model->rowCount() - 1, 0)), QItemSelectionModel::Select);
}

void ChangelogPage::removeVersion()
{
	QModelIndexList selected = ui.versionList->selectionModel()->selection().indexes();
	if (selected.isEmpty())
		return;
	int modelRow = proxyModel->mapToSource(selected.at(0)).row();
	int proxyModelRow = selected.at(0).row();

	proxyModel->setSourceModel(0);
	model->removeRow(modelRow);
	proxyModel->setSourceModel(model);

	if (model->rowCount())
	{
		ui.versionList->selectionModel()->select(proxyModel->index(proxyModelRow ? proxyModelRow - 1 : 0, 0), QItemSelectionModel::SelectCurrent);
	}
}

void ChangelogPage::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
		ui.retranslateUi(this);
        break;
    default:
        break;
    }
}

