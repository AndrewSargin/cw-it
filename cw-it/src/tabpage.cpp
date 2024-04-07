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
    else if (column == 10)
    {

        std::string dateStr = item->text().toStdString();
        std::string ddStr;
        std::string mmStr;
        std::string yyyyStr;
        try
        {
            float dateFloat = std::stof(dateStr);
            int ddNum = dateFloat / 1000000;
            if (ddNum < 1 || ddNum > 31)
                throw;
            int mmNum = ((int) dateFloat % 1000000) / 10000;
            if (mmNum < 1 || mmNum > 12)
                throw;
            int yyyyNum = (int) dateFloat % 10000;
            if(yyyyNum < 1990 || yyyyNum > 2050) // по возможности сделать, чтобы
                //сравнивалось с нынешним годом
                throw;
            dateStr = std::to_string(ddNum) + "." + std::to_string(mmNum) + "." + std::to_string(yyyyNum);
            currentLine.at("DateOfPurchase") = dateStr;
            item->setText(QString::fromStdString(dateStr));
            //у int нет 0 впереди, поэтому даже с нормальными датами может выскочить ошибка
            //возможно, стоит отказаться от идеи ввода даты без точек
        }
        catch(...)
        {
            try
            {
                //перевести дату с точками

            }

            catch(...)
            {
                //не получилось ни с числом, ни с строкой

            }
        }


    }


    currentLine.at(entryProps[column]) = item->text().toStdString();
}

