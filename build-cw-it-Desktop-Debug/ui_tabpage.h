/********************************************************************************
** Form generated from reading UI file 'tabpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABPAGE_H
#define UI_TABPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabPage
{
public:
    QTableWidget *tableWidget;

    void setupUi(QWidget *TabPage)
    {
        if (TabPage->objectName().isEmpty())
            TabPage->setObjectName(QString::fromUtf8("TabPage"));
        TabPage->resize(663, 422);
        tableWidget = new QTableWidget(TabPage);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 661, 391));

        retranslateUi(TabPage);

        QMetaObject::connectSlotsByName(TabPage);
    } // setupUi

    void retranslateUi(QWidget *TabPage)
    {
        TabPage->setWindowTitle(QCoreApplication::translate("TabPage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TabPage: public Ui_TabPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABPAGE_H
