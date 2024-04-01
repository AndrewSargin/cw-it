#include "tabpage.h"
#include "ui_tabpage.h"

TabPage::TabPage(QWidget *parent, openedFile *file) :
    QWidget(parent),
    ui(new Ui::TabPage)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(file->cpu.size());
    for (unsigned long i=0; i<file->cpu.size(); i++)
    {
    ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(file->type[i])));
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(file->id[i])));
    ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(file->cpu[i])));
    ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(file->gpu[i])));
    ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(file->ram[i])));
    ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(file->memory[i])));
    ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(file->date[i])));
    ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(file->price[i])));
    }
}

TabPage::~TabPage()
{
    delete ui;
}
