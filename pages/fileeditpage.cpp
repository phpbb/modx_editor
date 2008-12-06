#include "fileeditpage.h"

#include "modxdata.h"

#include <QStringList>
#include <QDebug>

FileEditPage::FileEditPage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);
	retranslateUi();

	model = new ListModel<Action>(this);
	ui.actionView->setModel(model);

	connect(ui.actionView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(updateAction(const QItemSelection &, const QItemSelection &)));
	connect(ui.currentFile, SIGNAL(activated(const QString &)), this, SLOT(updateActionModel(const QString &)));
}

void FileEditPage::setData(const ModXData *data)
{
	actions = data->actions;
	clearFields();

	ui.currentFile->setCurrentIndex(0);
	updateActionModel(ui.currentFile->currentText());
}

void FileEditPage::getData(ModXData *data)
{
	QItemSelection selection = ui.actionView->selectionModel()->selection();
	updateAction(selection, selection);

	if (currentFile != "")
	{
		actions[currentFile] = model->list();
	}
	ListModel<QString> *fileModel = dynamic_cast<ListModel<QString> *>(ui.currentFile->model());
	if (fileModel != NULL)
	{
		QMap<QString, QList<Action> > newActions;

		foreach (QString file, fileModel->list())
		{
			newActions[file] = actions[file];
		}
		actions = newActions;
	}
	data->actions = actions;
}

void FileEditPage::updateActionModel(const QString &file)
{
	QString nextFile = file;

	if (currentFile != "")
	{
		actions[currentFile] = model->list();
	}
	currentFile = nextFile;
	if (nextFile == "")
	{
		model->setList(QList<Action>());
		return;
	}
	model->setList(actions[nextFile]);
}

void FileEditPage::updateAction(const QItemSelection &newSelection, const QItemSelection &oldSelection)
{
	if (oldSelection.count())
	{
		QModelIndexList list = oldSelection.indexes();

		if (!list.isEmpty())
		{
			QModelIndex index = list.at(0);
			Action action = model->data(index, Qt::EditRole).value<Action>();

			action.type = (Action::Type) ui.actionType->currentIndex();

			switch (action.type)
			{
				case Action::Find:
					action.find = ui.find->toPlainText();
				break;
				case Action::Edit:
					action.editType = (Action::EditType) ui.editType->currentIndex();
					action.edit = ui.edit->toPlainText();
				break;
				case Action::InlineFind:
					action.find = ui.inlineFind->text();
				break;
				case Action::InlineEdit:
					action.editType = (Action::EditType) ui.inlineEditType->currentIndex();
					action.edit = ui.inlineEdit->text();
				break;
			}

			model->setData(index, QVariant::fromValue(action));
		}
	}

	Action action;
	if (newSelection.count())
	{
		QModelIndexList list = newSelection.indexes();
		if (!list.isEmpty())
		{
			action = model->data(list.at(0), Qt::EditRole).value<Action>();
		}
	}

	clearFields();

	ui.actionType->setCurrentIndex(action.type);

	switch (action.type)
	{
		case Action::Find:
			ui.find->setText(action.find);
		break;
		case Action::Edit:
			ui.editType->setCurrentIndex(action.editType);
			ui.edit->setText(action.edit);
		break;
		case Action::InlineFind:
			ui.inlineFind->setText(action.find);
		break;
		case Action::InlineEdit:
			ui.inlineEditType->setCurrentIndex(action.editType);
			ui.inlineEdit->setText(action.edit);
		break;
	}
}

void FileEditPage::on_actionType_currentIndexChanged()
{
	if (!ui.actionView->selectionModel())
		return;

	QModelIndexList list = ui.actionView->selectionModel()->selection().indexes();
	if (list.isEmpty())
		return;
	QModelIndex index = list.at(0);
	Action action = model->data(index, Qt::EditRole).value<Action>();
	action.type = (Action::Type) ui.actionType->currentIndex();
	model->setData(index, QVariant::fromValue(action));
}

void FileEditPage::on_add_clicked()
{
	model->insertRow(model->rowCount(), QModelIndex());
	ui.actionView->selectionModel()->clearSelection();
	ui.actionView->selectionModel()->select(model->index(model->rowCount() - 1, 0), QItemSelectionModel::Select);
}

void FileEditPage::on_remove_clicked()
{
	QModelIndexList selected = ui.actionView->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;
	int row = selected.at(0).row();
	model->removeRow(row);
	if (model->rowCount())
	{
		ui.actionView->selectionModel()->select(model->index(row ? row - 1 : 0, 0), QItemSelectionModel::SelectCurrent);
	}
}

void FileEditPage::on_moveUp_clicked()
{
	QModelIndexList selected = ui.actionView->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;
	int row = selected.at(0).row();

	row = model->moveUp(row);
	ui.actionView->selectionModel()->select(model->index(row, 0), QItemSelectionModel::SelectCurrent);
}

void FileEditPage::on_moveDown_clicked()
{
	QModelIndexList selected = ui.actionView->selectionModel()->selectedIndexes();
	if (selected.isEmpty())
		return;
	int row = selected.at(0).row();

	row = model->moveDown(row);
	ui.actionView->selectionModel()->select(model->index(row, 0), QItemSelectionModel::SelectCurrent);
}

void FileEditPage::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
		ui.retranslateUi(this);
		retranslateUi();
        break;
    default:
        break;
    }
}

void FileEditPage::setFileModel(QAbstractItemModel *model)
{
	ui.currentFile->setModel(model);
	ui.currentFile->setCurrentIndex(0);
	connect(model, SIGNAL(modelReset()), this, SLOT(updateActionModel()));
}

void FileEditPage::retranslateUi()
{
	QStringList actionTypes;
	actionTypes << tr("Find") << tr("Edit") << tr("Inline Find") << tr("Inline Edit");

	QStringList editTypes;
	editTypes << tr("after-add") << tr("before-add") << tr("replace") << tr("operation");

	ui.actionType->clear();
	ui.actionType->addItems(actionTypes);

	ui.editType->clear();
	ui.inlineEditType->clear();

	ui.editType->addItems(editTypes);
	ui.inlineEditType->addItems(editTypes);
}

void FileEditPage::clearFields()
{
	ui.actionType->setCurrentIndex(Action::Find);
	ui.find->setText("");

	ui.editType->setCurrentIndex(Action::AfterAdd);
	ui.edit->setText("");

	ui.inlineFind->setText("");

	ui.inlineEditType->setCurrentIndex(Action::AfterAdd);
	ui.inlineEdit->setText("");
}
