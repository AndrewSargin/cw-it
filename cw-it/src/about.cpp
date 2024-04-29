#include "about.h"
#include "ui_about.h"


///Конструктор окна
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    //Устанавлиаем дизайн окна
    this->setStyleSheet("QDialog {background-color:rgb(255,255,255);} QTextBrowser {border: 0px}");
}


///Деструктор окна
About::~About()
{
    delete ui;
}


///Нажатие на кнопку в окне
void About::on_pushButton_clicked()
{
    this->destroy();
}
