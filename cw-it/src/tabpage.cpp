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
    ui->tableWidget->blockSignals(1);
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
    currentFile = file;
    ui->tableWidget->blockSignals(0);
}

TabPage::~TabPage()
{
    delete ui;
}

void TabPage::on_tableWidget_cellChanged(int row, int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    int EntryId = std::stoi(ui->tableWidget->item(row, 0)->text().toStdString());
    auto currentLine = currentFile->data.at(EntryId).properties;

    if(column == 9)
    {
        try
        {
            float price = std::stof(item->text().toStdString());
            currentLine.at("Cost") = std::to_string(price);
        }
        catch(...)
        {
            item->setText(QString::fromStdString(currentLine.at("Cost")));
        }
    }
    if (column == 10)
    {

        std::string dateStr = item->text().toStdString();
        std::string writeDate;
        std::string ddStr, mmStr, yyyyStr;
        int ddNum, mmNum, yyyyNum;

        if (dateStr.length() != 8 && dateStr.length() != 10)
        {
            item->setText(QString::fromStdString(currentLine.at("DateOfPurchase")));
            return;
        }
        else {
            if (dateStr.length() == 8)
            {
                ddStr = dateStr.substr(0, 2);
                ddNum = std::stoi(ddStr);
                mmStr = dateStr.substr(2, 2);
                mmNum = std::stoi(mmStr);
                yyyyStr = dateStr.substr(4, 4);
                yyyyNum = std::stoi(yyyyStr);
            }
            else
            {
                ddStr = dateStr.substr(0, 2);
                ddNum = std::stoi(ddStr);
                mmStr = dateStr.substr(3, 2);
                mmNum = std::stoi(mmStr);
                yyyyStr = dateStr.substr(6, 4);
                yyyyNum = std::stoi(yyyyStr);
            }

            if (ddNum < 1 || ddNum > 31 || mmNum < 1 || mmNum > 12 ||
                    yyyyNum < 1990 || yyyyNum > 2050) // по возможности сделать, чтобы
                //сравнивалось с нынешним годом
            {
                item->setText(QString::fromStdString(currentLine.at("DateOfPurchase")));
                return;
            }
        }

        writeDate = ddStr + "." + mmStr + "." + yyyyStr;
        item->setText(QString::fromStdString(writeDate));
    }

    currentLine.at(entryProps[column]) = item->text().toStdString();
}

