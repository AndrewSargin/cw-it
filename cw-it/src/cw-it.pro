QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    askforsave.cpp \
    entry.cpp \
    filehandler.cpp \
    filereadingerror.cpp \
    main.cpp \
    mainwindow.cpp \
    openedfile.cpp \
    tabpage.cpp \
    technical.cpp \
    validator.cpp

HEADERS += \
    about.h \
    askforsave.h \
    constants.h \
    entry.h \
    filehandler.h \
    filereadingerror.h \
    mainwindow.h \
    openedfile.h \
    tabpage.h \
    technical.h \
    validator.h

FORMS += \
    about.ui \
    askforsave.ui \
    filereadingerror.ui \
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
