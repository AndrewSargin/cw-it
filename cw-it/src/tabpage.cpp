#include "tabpage.h"
#include "ui_tabpage.h"

TabPage::TabPage(QWidget *parent, openedFile *file) :
    QWidget(parent),
    ui(new Ui::TabPage)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(file->data.size());
    for (unsigned long i=0; i<file->data.size(); i++)
    {
    ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(file->data[i].getType())));
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(file->data[i].getId())));
    ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(file->data[i].getCpu())));
    ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(file->data[i].getGpu())));
    ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(file->data[i].getRam())));
    ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(file->data[i].getMemory())));
    ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(file->data[i].getDate())));
    ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(file->data[i].getPrice())));
    }
}

TabPage::~TabPage()
{
    delete ui;
}
