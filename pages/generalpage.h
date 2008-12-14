#ifndef GENERALPAGE_H
#define GENERALPAGE_H

#include "page.h"
#include "ui_generalpage.h"

class QNetworkAccessManager;
class QNetworkReply;

class GeneralPage : public Page {
    Q_OBJECT
    Q_DISABLE_COPY(GeneralPage)
public:
	explicit GeneralPage(QWidget *parent = 0);
	virtual ~GeneralPage(){}

	virtual void setData(const ModXData *data);
	virtual void getData(ModXData *data);

protected slots:
	void on_setLatestVersion_clicked();
	void handleNetworkReply(QNetworkReply *reply);

protected:
    virtual void changeEvent(QEvent *e);

private:
	QNetworkAccessManager *manager;
	Ui::GeneralPage ui;
};

#endif // GENERALPAGE_H
