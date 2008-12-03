# -------------------------------------------------
# Project created by QtCreator 2008-11-07T13:37:18
# -------------------------------------------------
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
    pages/diypage.cpp
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
    listmodel.h
FORMS += mainwindow.ui \
    pages/generalpage.ui \
    pages/changelogpage.ui \
    pages/authorgrouppage.ui \
    pages/sqlpage.ui \
    pages/filepage.ui \
    pages/diypage.ui
