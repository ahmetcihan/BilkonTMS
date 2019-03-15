#-------------------------------------------------
#
# Project created by QtCreator 2019-03-06T17:54:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = BilkonTMS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    remoteconnection.cpp \
    qcustomplot.cpp \
    ethernet.cpp \
    plot.cpp \
    theme.cpp \
    process.cpp

HEADERS  += mainwindow.h \
    remoteconnection.h \
    qcustomplot.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
