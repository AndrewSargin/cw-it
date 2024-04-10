#include "filereadingerror.h"
#include "ui_filereadingerror.h"

FileReadingError::FileReadingError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileReadingError)
{
    ui->setupUi(this);
}

FileReadingError::~FileReadingError()
{
    delete ui;
}
