/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *actionEnglish;
    QAction *actionRussian;
    QAction *actionPrint;
    QAction *actionShow;
    QAction *action_New_File;
    QAction *actionSave_As;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menuChange_Language;
    QMenu *menuPrice_Diagram;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 1000);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QString::fromUtf8("actionEnglish"));
        actionRussian = new QAction(MainWindow);
        actionRussian->setObjectName(QString::fromUtf8("actionRussian"));
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        actionPrint->setEnabled(false);
        actionShow = new QAction(MainWindow);
        actionShow->setObjectName(QString::fromUtf8("actionShow"));
        actionShow->setEnabled(false);
        action_New_File = new QAction(MainWindow);
        action_New_File->setObjectName(QString::fromUtf8("action_New_File"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        centralwidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1400, 22));
        menubar->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menuChange_Language = new QMenu(menu_2);
        menuChange_Language->setObjectName(QString::fromUtf8("menuChange_Language"));
        menuPrice_Diagram = new QMenu(menubar);
        menuPrice_Diagram->setObjectName(QString::fromUtf8("menuPrice_Diagram"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menuPrice_Diagram->menuAction());
        menu->addAction(action_New_File);
        menu->addAction(action);
        menu->addAction(action_2);
        menu->addAction(actionSave_As);
        menu->addAction(action_3);
        menu->addAction(actionPrint);
        menu_2->addSeparator();
        menu_2->addAction(menuChange_Language->menuAction());
        menu_2->addSeparator();
        menu_2->addAction(action_4);
        menuChange_Language->addAction(actionEnglish);
        menuChange_Language->addAction(actionRussian);
        menuPrice_Diagram->addAction(actionShow);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "cw-it Sargin Andrew", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        action_2->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        action_3->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        action_4->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionEnglish->setText(QCoreApplication::translate("MainWindow", "English (EN)", nullptr));
        actionRussian->setText(QCoreApplication::translate("MainWindow", "\320\240\321\203\321\201\321\201\320\272\320\270\320\271 (RU)", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
        actionShow->setText(QCoreApplication::translate("MainWindow", "Show", nullptr));
        action_New_File->setText(QCoreApplication::translate("MainWindow", "New File", nullptr));
        actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "Other", nullptr));
        menuChange_Language->setTitle(QCoreApplication::translate("MainWindow", "Change Language", nullptr));
        menuPrice_Diagram->setTitle(QCoreApplication::translate("MainWindow", "Price Chart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
