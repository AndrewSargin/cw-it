/********************************************************************************
** Form generated from reading UI file 'filereadingerror.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEREADINGERROR_H
#define UI_FILEREADINGERROR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_FileReadingError
{
public:
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *FileReadingError)
    {
        if (FileReadingError->objectName().isEmpty())
            FileReadingError->setObjectName(QString::fromUtf8("FileReadingError"));
        FileReadingError->resize(400, 119);
        buttonBox = new QDialogButtonBox(FileReadingError);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 91, 341, 21));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        textBrowser = new QTextBrowser(FileReadingError);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(70, 30, 256, 41));

        retranslateUi(FileReadingError);
        QObject::connect(buttonBox, SIGNAL(accepted()), FileReadingError, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FileReadingError, SLOT(reject()));

        QMetaObject::connectSlotsByName(FileReadingError);
    } // setupUi

    void retranslateUi(QDialog *FileReadingError)
    {
        FileReadingError->setWindowTitle(QCoreApplication::translate("FileReadingError", "Dialog", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("FileReadingError", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Error while reading a file</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileReadingError: public Ui_FileReadingError {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEREADINGERROR_H
