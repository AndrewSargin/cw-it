/********************************************************************************
** Form generated from reading UI file 'askforsave.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASKFORSAVE_H
#define UI_ASKFORSAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_AskForSave
{
public:
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *AskForSave)
    {
        if (AskForSave->objectName().isEmpty())
            AskForSave->setObjectName(QString::fromUtf8("AskForSave"));
        AskForSave->resize(400, 300);
        buttonBox = new QDialogButtonBox(AskForSave);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::No|QDialogButtonBox::Yes);
        buttonBox->setCenterButtons(true);
        textBrowser = new QTextBrowser(AskForSave);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(70, 30, 261, 191));

        retranslateUi(AskForSave);
        QObject::connect(buttonBox, SIGNAL(accepted()), AskForSave, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AskForSave, SLOT(reject()));

        QMetaObject::connectSlotsByName(AskForSave);
    } // setupUi

    void retranslateUi(QDialog *AskForSave)
    {
        AskForSave->setWindowTitle(QCoreApplication::translate("AskForSave", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AskForSave: public Ui_AskForSave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASKFORSAVE_H
