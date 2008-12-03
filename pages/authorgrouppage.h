#ifndef AUTHORGROUPPAGE_H
#define AUTHORGROUPPAGE_H

#include "page.h"

#include "modxdata.h"
#include "listmodel.h"

#include "ui_authorgrouppage.h"

class AuthorGroupPage : public Page
{
    Q_OBJECT
    Q_DISABLE_COPY(AuthorGroupPage)
public:
	explicit AuthorGroupPage(QWidget *parent = 0);

	virtual void setData(const ModXData *data);
	virtual void getData(ModXData *data);

protected slots:
	void updateDetails(const QItemSelection &, const QItemSelection &);
	void updateUserName(const QString &newName);

	void addAuthor();
	void removeAuthor();
	void moveUp();
	void moveDown();

protected:
    virtual void changeEvent(QEvent *e);

private:

	ListModel<Author> *model;

	Ui::AuthorGroupPage ui;
};

#endif // AUTHORGROUPPAGE_H
