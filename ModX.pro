CONFIG -= debug
CONFIG += release
TARGET = ModX

TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    modxapp.cpp \
    modxreader.cpp \
    pages/generalpage.cpp \
    modxdata.cpp \
    pages/changelogpage.cpp \
    pages/authorgrouppage.cpp \
    modxwriter.cpp \
    pages/sqlpage.cpp \
    pages/filepage.cpp \
    pages/diypage.cpp \
    pages/fileeditpage.cpp \
    pages/editedfilespage.cpp
HEADERS += mainwindow.h \
    modxapp.h \
    modxreader.h \
    pages/generalpage.h \
    modxdata.h \
    pages/page.h \
    pages/changelogpage.h \
    pages/authorgrouppage.h \
    modxwriter.h \
    pages/sqlpage.h \
    pages/filepage.h \
    pages/diypage.h \
    listmodel.h \
    pages/fileeditpage.h \
    pages/editedfilespage.h
FORMS += mainwindow.ui \
    pages/generalpage.ui \
    pages/changelogpage.ui \
    pages/authorgrouppage.ui \
    pages/sqlpage.ui \
    pages/filepage.ui \
    pages/diypage.ui \
    pages/fileeditpage.ui \
    pages/editedfilespage.ui
RC_FILE += resources/win.rc
include(widgets/widgets.pri)
OTHER_FILES += widgets/widgets.pri
