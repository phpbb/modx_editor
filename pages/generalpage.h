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
