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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <table.h>

QT_BEGIN_NAMESPACE

class Ui_TabPage
{
public:
    QGridLayout *gridLayout;
    Table *tableWidget;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QWidget *TabPage)
    {
        if (TabPage->objectName().isEmpty())
            TabPage->setObjectName(QString::fromUtf8("TabPage"));
        TabPage->resize(1081, 767);
        TabPage->setContextMenuPolicy(Qt::DefaultContextMenu);
        gridLayout = new QGridLayout(TabPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new Table(TabPage);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        tableWidget->setAcceptDrops(true);
        tableWidget->setDragEnabled(true);
        tableWidget->setDragDropOverwriteMode(false);
        tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
        tableWidget->setDefaultDropAction(Qt::IgnoreAction);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableWidget, 3, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        lineEdit = new QLineEdit(TabPage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        label = new QLabel(TabPage);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(TabPage);

        QMetaObject::connectSlotsByName(TabPage);
    } // setupUi

    void retranslateUi(QWidget *TabPage)
    {
        TabPage->setWindowTitle(QCoreApplication::translate("TabPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("TabPage", " Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TabPage: public Ui_TabPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABPAGE_H
