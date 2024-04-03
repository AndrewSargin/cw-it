QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    entity.cpp \
    filehandler.cpp \
    main.cpp \
    mainwindow.cpp \
    tabpage.cpp

HEADERS += \
    about.h \
    entity.h \
    filehandler.h \
    filestructure.h \
    mainwindow.h \
    tabpage.h

FORMS += \
    about.ui \
    mainwindow.ui \
    tabpage.ui

TRANSLATIONS += \
    cw-it_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
