#include "askforsave.h"
#include "ui_askforsave.h"
#include "filehandler.h"
#include <iostream>

AskForSave::AskForSave(QWidget *par, FileHandler *fileHandle, int ind) :
    QDialog(par),
    ui(new Ui::AskForSave)
{
    fileHandler = fileHandle;
    index = ind;
    std::string text = "File \"" + fileHandle->getFileName() + "\" was changed. Do you want to save it before closing?";
    ui->setupUi(this);
    parent = par;
    ui->textBrowser->setText(QString::fromStdString(text));
    this->setStyleSheet("QDialog {background-color:rgb(255,255,255);} QTextBrowser {border: 0px}");
}

AskForSave::~AskForSave()
{
    delete ui;
}

void AskForSave::on_buttonBox_accepted()
{
    fileHandler->save(parent, index);
}


void AskForSave::on_buttonBox_rejected()
{

}

