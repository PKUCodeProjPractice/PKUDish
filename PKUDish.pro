QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# QMAKE_CFLAGS += -std=c99

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dish.cpp \
    dishfilehandler.cpp \
    main.cpp \
    mainwindow.cpp \
    tab1.cpp

HEADERS += \
    dish.h \
    dishfilehandler.h \
    mainwindow.h \
    tab1.h

FORMS += \
    mainwindow.ui \
    tab1.ui

TRANSLATIONS += \
    PKUDish_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
