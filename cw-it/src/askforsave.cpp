#include "askforsave.h"
#include "ui_askforsave.h"
#include "filehandler.h"
#include <iostream>

AskForSave::AskForSave(QWidget *parent, FileHandler *fileHandle, int ind) :
    QDialog(parent),
    ui(new Ui::AskForSave)
{
    fileHandler = fileHandle;
    index = ind;
    std::string text = "File \"" + fileHandle->getFileName() + "\" was changed. Do you want to save it before closing?";
    ui->setupUi(this);
    ui->textBrowser->setText(QString::fromStdString(text));
}

AskForSave::~AskForSave()
{
    delete ui;
}

void AskForSave::on_buttonBox_accepted()
{
    fileHandler->save(index);
}


void AskForSave::on_buttonBox_rejected()
{

}

