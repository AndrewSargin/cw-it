#include "tabpage.h"
#include "ui_tabpage.h"
#include "constants.h"
#include "validator.h"
#include <qmenu.h>
#include "entry.h"


///Конструктор
TabPage::TabPage(QWidget *parent, OpenedFile *file) :
    QWidget(parent),
    ui(new Ui::TabPage)
{
    //Названия столбиков
    QStringList labels;

    ui->setupUi(this);

    //Считываем названия столбиков из константного вектора
    //и записываем в созданный список названий
    for(int i  = 0; i < (int) columnNames.size(); i++)
    {
        QString name = QObject::tr(columnNames[i].c_str());
        labels.append(QString::fromStdString(columnNames[i]));
    }

    //Настраиваем таблицу
    ui->tableWidget->setColumnCount(11);
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->setRowCount(file->data.size());

    //Блокируем все сигналы таблице на время ее заполнения
    ui->tableWidget->blockSignals(1);

    //Заполняем таблицу (В случае существующего файла)
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
                //Запрещаем изменять колонку, содержащую Id стрки
                item->setFlags(Qt::ItemIsEnabled);
        }
        iterator++;
    }

    //Заполняем таблицу (В случае нового файла)
    if (file->fileName == "Untitled")
    {
        for(int j = 0; j < 11; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem();

            if(j == 0 || j == 9)
                item->setData(Qt::EditRole, 1);
            else item->setData(Qt::EditRole, QString(""));

            ui->tableWidget->setItem(0, j, item);
            if (j == 0)
                item->setFlags(Qt::ItemIsEnabled);
        }
    }

    //Подгоняем размеры столбиков под их содержимое
    ui->tableWidget->resizeColumnsToContents();

    //Запоминаем открытый файл
    currentFile = file;
    ui->tableWidget->SetFile(file);

    //Разрешаем таблице получать сигналы
    ui->tableWidget->blockSignals(0);

    //Включаем сортировку
    ui->tableWidget->setSortingEnabled(true);

    //Добаляем возвожность вызова контекстного меню
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), ui->tableWidget, SLOT(slotCustomMenuRequested(QPoint)));

}


///Деструктор
TabPage::~TabPage()
{
    delete ui;
}


///При изменении содержимого ячейки
void TabPage::on_tableWidget_cellChanged(int row, int column)
{
    //Почему-то при DragAndDrop в колонку с идентификатором
    //создается новая строчка, хотя вообще ничего не должно происходить,
    //поэтому просто удаляю новую строку
    /*if (column == 0)
    {
        ui->tableWidget->removeRow(row);
        return;
    }*/

    QTableWidgetItem *item = ui->tableWidget->item(row, column);

    //Создаем экземпляр класса, проверяющего правильность введенных данных
    Validator validate = Validator();

    int EntryId = std::stoi(ui->tableWidget->item(row, 0)->text().toStdString());
    std::map<std::string, std::string> *currentLine = &currentFile->data.at(EntryId).properties;

    //Изменяем состояние файла на "изменен"
    currentFile->isChanged = true;

    //В зависимости от колонки, в которой изменилась ячейка таблицы,
    //проверяем соответствующие данные
    switch(column)
    {
    case 9: validate.PriceInput(item, currentLine);
        break;
    case 10: validate.DateInput(item, currentLine);
        break;
    }

    //Записываем в данные из файла информацию из ячейки таблицы
    currentLine->at(entryProps[column]) = item->text().toStdString();
}


///При вызове контекстного меню
void TabPage::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu * menu = new QMenu(this);

    //Добавляем в меню кнопки
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

    //Отключаем некторые кнопки, если выбрано более 1
    //ячейки таблицы
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


///Добавление строки после выбранной
void TabPage::on_addAfter_triggered()
{
    int row = ui->tableWidget->currentRow() + 1;

    //Создаем новую строку
    ui->tableWidget->NewRow(row);
}


///Добавление строки до выбранной
void TabPage::on_addBefore_triggered()
{
    int row = ui->tableWidget->currentRow();

    //Создаем новую строку
    ui->tableWidget->NewRow(row);
}


///Удаление выбранной строки
void TabPage::on_deleteEntry_triggered()
{
    //Если в таблице есть сторки
    if (ui->tableWidget->rowCount() > 0)
    {
        int row = ui->tableWidget->currentRow();
        int id = std::stoi(ui->tableWidget->item(row, 0)->text().toStdString());

        //Удаляем строку
        ui->tableWidget->removeRow(row);

        //Изменяем статус файла на "изменен"
        currentFile->isChanged = true;

        //Удаляем соответствующие данные из файла
        currentFile->data.erase(id);
    }
}


///При изменении поискового запроса
void TabPage::on_lineEdit_textChanged(const QString &text)
{
    //Если есть запрос
    if(!text.isEmpty())
    {
        //Ищем ячейки таблицы, в которых есть совпадения с запросом
        QList<QTableWidgetItem*> items = ui->tableWidget->findItems(text, Qt::MatchContains);
        QList<int> rows;

        //Скрываем все строки таблицы
        for (int i = 0; i <ui->tableWidget->rowCount(); i++)
            ui->tableWidget->hideRow(i);

        //Добаляем в список строк для показа те, в которых
        //есть совпаднения с запросом (так, чтобы не было повторений)
        for (int i = 0; i < items.length(); i++)
            if (!rows.contains(items.at(i)->row()))
                rows.append(items.at(i)->row());

        //Показываем строки с совпадениями
        for (int i = 0; i < rows.length(); i++)
            ui->tableWidget->showRow(rows.at(i));
    }
    //Если запрос пуст, показываем все строки таблицы
    else
    {
        for (int i = 0; i <ui->tableWidget->rowCount(); i++)
            ui->tableWidget->showRow(i);
    }
}

