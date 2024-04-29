#include "filereadingerror.h"
#include "ui_filereadingerror.h"


///Конструктор
FileReadingError::FileReadingError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileReadingError)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog {background-color:rgb(255,255,255);} QTextBrowser {border: 0px}");
}


///Деструктор
FileReadingError::~FileReadingError()
{
    delete ui;
}
