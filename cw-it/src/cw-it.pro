QT       += core gui
QT       += printsupport
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    askforsave.cpp \
    chart.cpp \
    entry.cpp \
    filehandler.cpp \
    filereadingerror.cpp \
    main.cpp \
    mainwindow.cpp \
    openedfile.cpp \
    table.cpp \
    tabpage.cpp \
    technical.cpp \
    validator.cpp

HEADERS += \
    about.h \
    askforsave.h \
    chart.h \
    constants.h \
    entry.h \
    filehandler.h \
    filereadingerror.h \
    mainwindow.h \
    openedfile.h \
    table.h \
    tabpage.h \
    technical.h \
    validator.h

FORMS += \
    about.ui \
    askforsave.ui \
    chart.ui \
    filereadingerror.ui \
    mainwindow.ui \
    tabpage.ui

TRANSLATIONS = languages/cw-it_ru_RU.ts languages/cw-it_en_US.ts languages/cw-it_hy_HY.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
