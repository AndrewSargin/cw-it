#include "tabpage.h"
#include "ui_tabpage.h"
#include "constants.h"

TabPage::TabPage(QWidget *parent, OpenedFile *file) :
    QWidget(parent),
    ui(new Ui::TabPage)
{
    QStringList labels;
    ui->setupUi(this);
    for(int i  = 0; i < (int) columnNames.size(); i++)
    {
        labels.append(QString::fromStdString(columnNames[i]));
    }
    ui->tableWidget->setColumnCount(11);
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->setRowCount(file->data.size());
    auto iterator = file->data.begin();
    for(int i = 0; i < (int) file->data.size(); i++)
    {
        for(int j = 0; j < 11; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(file->data.at(iterator->first).properties.at(entryProps[j])));
            ui->tableWidget->setItem(i, j, item);
            if (j == 0)
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        }
        iterator++;
    }
}

TabPage::~TabPage()
{
    delete ui;
}
