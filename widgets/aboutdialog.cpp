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

#include "aboutdialog.h"

#include "modxapp.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent){
    m_ui.setupUi(this);
	m_ui.copyright->setText(
			tr("&copy; 2009 by the <a href=\"http://%2\">%1</a>")
			.arg(QApplication::organizationName())
			.arg(QApplication::organizationDomain()));
	m_ui.appName->setText(QApplication::applicationName() + " v" + QApplication::applicationVersion());
	setWindowTitle(tr("About %1").arg(QApplication::applicationName()));
}

void AboutDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
