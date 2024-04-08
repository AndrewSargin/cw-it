#include "tabpage.h"
#include "ui_tabpage.h"
#include "constants.h"
#include "validator.h"

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
    Validator validate = Validator();
    int EntryId = std::stoi(ui->tableWidget->item(row, 0)->text().toStdString());
    std::map<std::string, std::string> *currentLine = &currentFile->data.at(EntryId).properties;

    switch(column)
    {
    case 9: validate.PriceInput(item, currentLine);
        break;
    case 10: validate.DateInput(item, currentLine);
        break;
    }

    currentLine->at(entryProps[column]) = item->text().toStdString();
}

