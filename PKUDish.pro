QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# QMAKE_CFLAGS += -std=c99

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    browsetab.cpp \
    dish.cpp \
    dishbox.cpp \
    dishes.cpp \
    dishfilehandler.cpp \
    loadingwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    randomtab.cpp \
    randdish.cpp \
    tags.cpp

HEADERS += \
    browsetab.h \
    dish.h \
    dishbox.h \
    dishes.h \
    dishfilehandler.h \
    loadingwidget.h \
    mainwindow.h \
    randomtab.h \
    randdish.h \
    tags.h

FORMS += \
    browsetab.ui \
    loadingwidget.ui \
    mainwindow.ui \
    dishbox.ui \
    mainwindow.ui \
    randomtab.ui

TRANSLATIONS += \
    PKUDish_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../qtImage/image.qrc \
    assets.qrc
