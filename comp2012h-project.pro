#-------------------------------------------------
#
# Project created by QtCreator 2018-11-05T16:16:24
#
#-------------------------------------------------

QT       += core gui svg multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = comp2012h-project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += sticker

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mygraphicsview.cpp \
    mygraphicsscene.cpp \
    sticker/anchor.cpp \
    sticker/sticker.cpp \
    sticker/svgsticker.cpp \
    sticker/textsticker.cpp \
    sticker/transformhandler.cpp \
    colordisplay.cpp \
    camerawindow.cpp \
    imageutil.cpp \
    imagekernel.cpp \
    filtereffect.cpp

HEADERS += \
        mainwindow.h \
    mygraphicsview.h \
    mygraphicsscene.h \
    sticker/anchor.h \
    sticker/sticker.h \
    sticker/svgsticker.h \
    sticker/textsticker.h \
    sticker/transformhandler.h \
    colordisplay.h \
    camerawindow.h \
    imageutil.h \
    imagekernel.h \
    filtereffect.h

FORMS += \
        mainwindow.ui \
    camerawindow.ui

RESOURCES += \
    resources.qrc
