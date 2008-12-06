#include "sqlpage.h"

#include "widgets/sqlsyntaxhighlighter.h"
#include "modxdata.h"

SqlPage::SqlPage(QWidget *parent) :
	Page(parent){
	ui.setupUi(this);

	new SqlSyntaxHighlighter(ui.sql->document());

	QStringList sqlDialects;
	sqlDialects
			<< tr("SQL Parser")
			<< tr("MySQL")
			<< tr("MySQL 4.0")
			<< tr("MySQL 4.1")
			<< tr("MySQLi")
			<< tr("MySQL 4")
			<< tr("MS Access")
			<< tr("Oracle")
			<< tr("PostgreSQL")
			<< tr("DB2")
			<< tr("Firebird")
			<< tr("SQLite");
	ui.sqlDialect->addItems(sqlDialects);
	ui.sqlDialect->setCurrentIndex(0);
}

void SqlPage::setData(const ModXData *data)
{
	ui.sqlDialect->setCurrentIndex(data->sqlDialect);
	ui.sql->setText(data->sql.join("\n\n"));
}

void SqlPage::getData(ModXData *data)
{
	data->sqlDialect = (ModXData::SqlDialect) ui.sqlDialect->currentIndex();
}


void SqlPage::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
		ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
