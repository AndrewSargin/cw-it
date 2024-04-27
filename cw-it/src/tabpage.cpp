#include "tabpage.h"
#include "ui_tabpage.h"
#include "constants.h"
#include "validator.h"
#include <qmenu.h>
#include "entry.h"

TabPage::TabPage(QWidget *parent, OpenedFile *file) :
    QWidget(parent),
    ui(new Ui::TabPage)
{
    QStringList labels;
    ui->setupUi(this);
    for(int i  = 0; i < (int) columnNames.size(); i++)
    {
        QString name = QObject::tr(columnNames[i].c_str());
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
            QTableWidgetItem *item = new QTableWidgetItem();

            if(j == 0 || j == 9)
                item->setData(Qt::EditRole, std::stoi(file->data.at(iterator->first).properties.at(entryProps[j])));
            else item->setData(Qt::EditRole, QString::fromStdString(file->data.at(iterator->first).properties.at(entryProps[j])));

            ui->tableWidget->setItem(i, j, item);
            if (j == 0)
                item->setFlags(Qt::ItemIsEnabled);
        }
        iterator++;
    }

    ui->tableWidget->resizeColumnsToContents();
    currentFile = file;
    ui->tableWidget->blockSignals(0);
    ui->tableWidget->setSortingEnabled(true);

    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), ui->tableWidget, SLOT(slotCustomMenuRequested(QPoint)));

}

TabPage::~TabPage()
{
    delete ui;
}

void TabPage::on_tableWidget_cellChanged(int row, int column)
{
    //Почему-то при DragAndDrop в колонку с идентификатором
    //создается новая строчка, хотя вообще ничего не должно происходить,
    //поэтому просто удаляю новую строку
    if (column == 0)
    {
        ui->tableWidget->removeRow(row);
        return;
    }
    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    Validator validate = Validator();
    int EntryId = std::stoi(ui->tableWidget->item(row, 0)->text().toStdString());
    std::map<std::string, std::string> *currentLine = &currentFile->data.at(EntryId).properties;

    currentFile->isChanged = true;

    switch(column)
    {
    case 9: validate.PriceInput(item, currentLine);
        break;
    case 10: validate.DateInput(item, currentLine);
        break;
    }

    currentLine->at(entryProps[column]) = item->text().toStdString();
}


void TabPage::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu * menu = new QMenu(this);

    QAction *addAfter = new QAction(tr("Add after"), this);
    QAction *addBefore = new QAction(tr("Add before"), this);
    QAction *deleteEntry = new QAction(tr("Delete row"), this);

    menu->addAction(addAfter);
    menu->addAction(addBefore);
    menu->addAction(deleteEntry);

    menu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));

    connect(addAfter, SIGNAL(triggered()), this, SLOT(on_addAfter_triggered()));
    connect(addBefore, SIGNAL(triggered()), this, SLOT(on_addBefore_triggered()));
    connect(deleteEntry, SIGNAL(triggered()), this, SLOT(on_deleteEntry_triggered()));

    if (ui->tableWidget->selectedItems().size() > 1)
    {
        addAfter->setEnabled(false);
        addBefore->setEnabled(false);
    }
    else
    {
        addAfter->setEnabled(true);
        addBefore->setEnabled(true);
    }
}

void TabPage::on_addAfter_triggered()
{
    int row = ui->tableWidget->currentRow() + 1;

    NewRow(row);
}

void TabPage::on_addBefore_triggered()
{
    int row = ui->tableWidget->currentRow() - 1;

    NewRow(row);
}

void TabPage::on_deleteEntry_triggered()
{
    int row = ui->tableWidget->currentRow();
    int id = std::stoi(ui->tableWidget->item(row, 0)->text().toStdString());
    ui->tableWidget->removeRow(row);
    currentFile->data.erase(id);
}

void TabPage::NewRow(int row)
{
    ui->tableWidget->insertRow(row);

    Entry newEntry = Entry();

    bool found = false;
    int key = 1;
    auto iterator = currentFile->data.begin();
    while(!found)
    {
        if (key == iterator->first)
        {
            key++;
            iterator++;
        }
        else found = true;
    }

    newEntry.properties["Id"] = std::to_string(key);

    currentFile->data[std::stoi(newEntry.properties["Id"])] = newEntry;

    for(int j = 0; j < 11; j++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(currentFile->data.at(key).properties.at(entryProps[j])));
        ui->tableWidget->setItem(row, j, item);
        if (j == 0)
            item->setFlags(Qt::ItemIsEnabled);
    }
}

void TabPage::on_lineEdit_textChanged(const QString &text)
{
    if(!text.isEmpty())
    {
        QList<QTableWidgetItem*> items = ui->tableWidget->findItems(text, Qt::MatchContains);
        QList<int> rows;

        for (int i = 0; i <ui->tableWidget->rowCount(); i++)
            ui->tableWidget->hideRow(i);

        for (int i = 0; i < items.length(); i++)
            if (!rows.contains(items.at(i)->row()))
                rows.append(items.at(i)->row());

        for (int i = 0; i < rows.length(); i++)
            ui->tableWidget->showRow(rows.at(i));
    }
    else
    {
        for (int i = 0; i <ui->tableWidget->rowCount(); i++)
            ui->tableWidget->showRow(i);
    }
}

