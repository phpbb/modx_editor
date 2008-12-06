#include "changelogpage.h"

#include <QModelIndexList>

ChangelogPage::ChangelogPage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);

	model = new ListModel<ChangelogEntry>(this);

	ui.versionList->setModel(model);
	ui.versionList->setSelectionMode(QAbstractItemView::SingleSelection);

	connect(ui.versionList->selectionModel(),	SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),	this,	SLOT(updateEntry(const QItemSelection &, const QItemSelection &)));
	connect(ui.version,		SIGNAL(textChanged(const QString &)),								this,	SLOT(updateVersion(const QString &)));
	connect(ui.add,			SIGNAL(clicked()),	this,	SLOT(addVersion()));
	connect(ui.remove,		SIGNAL(clicked()),	this,	SLOT(removeVersion()));
	connect(ui.moveUp,		SIGNAL(clicked()),	this,	SLOT(moveUp()));
	connect(ui.moveDown,	SIGNAL(clicked()),	this,	SLOT(moveDown()));


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
		ui.versionList->selectionModel()->select(model->index(0, 0), QItemSelectionModel::SelectCurrent);
	}
}

void ChangelogPage::getData(ModXData *data)
{
	QItemSelection selection = ui.versionList->selectionModel()->selection();
	updateEntry(selection, selection);
	data->history = model->list();
}


void ChangelogPage::updateEntry(const QItemSelection &newSelection, const QItemSelection &oldSelection)
{
	if (oldSelection.count())
	{
		QModelIndexList list = oldSelection.indexes();

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
		QModelIndexList list = newSelection.indexes();
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
	QModelIndexList list = ui.versionList->selectionModel()->selection().indexes();
	if (list.isEmpty())
		return;
	QModelIndex index = list.at(0);
	ChangelogEntry entry = model->data(index, Qt::EditRole).value<ChangelogEntry>();
	entry.version = version;
	model->setData(index, QVariant::fromValue(entry));
}

void ChangelogPage::addVersion()
{
	model->insertRow(model->rowCount(), QModelIndex());
	ui.versionList->selectionModel()->clearSelection();
	ui.versionList->selectionModel()->select(model->index(model->rowCount() - 1, 0), QItemSelectionModel::Select);
}

void ChangelogPage::removeVersion()
{
	QModelIndexList selected = ui.versionList->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;
	int row = selected.at(0).row();
	model->removeRow(row);
	if (model->rowCount())
	{
		ui.versionList->selectionModel()->select(model->index(row ? row - 1 : 0, 0), QItemSelectionModel::SelectCurrent);
	}
}

void ChangelogPage::moveUp()
{
	QModelIndexList selected = ui.versionList->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;
	int row = selected.at(0).row();

	row = model->moveUp(row);
	ui.versionList->selectionModel()->select(model->index(row, 0), QItemSelectionModel::SelectCurrent);

}

void ChangelogPage::moveDown()
{
	QModelIndexList selected = ui.versionList->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;
	int row = selected.at(0).row();

	row = model->moveDown(row);
	ui.versionList->selectionModel()->select(model->index(row, 0), QItemSelectionModel::SelectCurrent);
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

