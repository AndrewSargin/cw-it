#include "filereadingerror.h"
#include "ui_filereadingerror.h"

FileReadingError::FileReadingError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileReadingError)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog {background-color:rgb(255,255,255);} QTextBrowser {border: 0px}");
}

FileReadingError::~FileReadingError()
{
    delete ui;
}
