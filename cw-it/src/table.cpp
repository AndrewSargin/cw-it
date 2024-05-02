#include "table.h"
#include "entry.h"
#include "constants.h"

#include <QMimeData>


///Конструктор
Table::Table(QWidget *parent):
    QTableWidget(parent)
{

}


///Передача в таблицу файла с данными
void Table::SetFile(OpenedFile *file)
{
    currentFile = file;
}


///Обработка данных
QMimeData *Table::mimeData(const QList<QTableWidgetItem *> items) const
{
    //Проверка на наличие ячеек в таблице
    if (items.isEmpty())
        return nullptr;

    //Проверка данных в первой ячейке
    if (items.at(0) == nullptr)
        return nullptr;

    //Выбор типа MIME данных
    QStringList types = mimeTypes();
    if (types.isEmpty())
        return nullptr;

    QString result;

    //Определяем левый верхний выбранный элемент
    int topSelectionRange = items.at(0)->row();
    int leftSelectionRange = items.at(0)->column();

    //Переменная для подсчета количества выбранных столбьцов
    int columnCountSelectionRange = 0;

    //Проходим по всем ячейкам
    for (int i = 0; i < items.count(); ++i)
    {
        // Проверка на наличие ячеек
        if (items.at(i) == nullptr)
            return nullptr;

        //Вычисление смещение относительно верхней левой ячейки
        int currentSelectedColumn = items.at(i)->column() - leftSelectionRange;
        int currentSelectedRow = items.at(i)->row() - topSelectionRange;

        //Если текущая ячейка не из первого столбца, не последняя
        //в столбце выделенного диапазона и из первой строки
        if (currentSelectedColumn > 0 &&
                (currentSelectedColumn < columnCountSelectionRange ||
                 items.at(i)->row() == topSelectionRange))
            //добавляем разделитель столбцов
            result += ";";

        //Если текущая ячейка не из первой строки, но первая в столбце
        if (currentSelectedRow > 0 && items.at(i)->column() == leftSelectionRange)
        {
            //добавляем разделитель
            result += cr;
            result += lf;
        }

        //вставляем строку
        result += items.at(i)->data(Qt::DisplayRole).toString();

        //счетчик количества столбцов
        if (items.at(i)->row() == topSelectionRange)
            columnCountSelectionRange++;
    }

    //добавляем разделитель
    result += cr;
    result += lf;

    QMimeData *mimeData = new QMimeData;

    //Добавляем полученные данные в объект экспорта MIME
    mimeData->setData("text/plain", result.toUtf8());

    return mimeData;

}


QStringList Table::mimeTypes() const
{
    QStringList types;
    //Задание типов MINE
    types << "text/plain";

    return types;
}


///Вставка данных
bool Table::dropMimeData(int row, int column,
                                 const QMimeData *data,
                                 Qt::DropAction action)
{
    Q_UNUSED(action);
    //Проверка на наличие данных
    if (data == nullptr)
        return false;

    //Проверяем формат входящих данных. Если он является форматом
    //таблиц Qt,
    if (data->hasFormat("application/x-qabstractitemmodeldatalist")) {
        // то пересылаем его в обработчик класса QMimeData
        return QTableWidget::dropMimeData(row, column, data, action);
    }

    //Если формат простой текст, то разбираем данные
    if (data->hasFormat("text/plain")) {

        QStringList strings;

        //Добавляем данные, разбивая на отдельные строки
        strings = data->text().split(QString("%1%2").arg(cr).arg(lf));

        //Проходим по строке
        for (int rowSelected = 0; rowSelected < strings.count(); ++rowSelected) {
            //Если после вставки номер последней строки будет больше,
            //чем номер последней существующей в таблице строки
            if ((row + rowSelected) >= rowCount())
                //добавляем ещё одну строку
                NewRow(rowCount());

            //Вытаскиваем из строки данные с одновременным разделением
            //на отдельные столбцы
            QStringList tokens = strings[rowSelected].split(";");
            //Проходим по столбцам
            for (int columnSelected = 0; columnSelected < tokens.count(); ++columnSelected) {

                //Вытаскиваем данные из столбца
                QString token = tokens[columnSelected];

                if (token.isEmpty())
                    continue;

                // Создаём пустую ячейку таблицы
                QTableWidgetItem *item = new QTableWidgetItem;

                // Добавляем в неё данные
                item->setText(token);

                // Вставляем ячейку в таблицу
                setItem(row + rowSelected, column + columnSelected, item);
            }
        }

        // Если вставить строку удалось
        return true;
    }

    // Если вставить строку не удалось
    return false;
}


///Добавление новой строки в таблицу
void Table::NewRow(int row)
{
    //Создаем строку
    insertRow(row);

    //Блокируем сигналы таблице
    blockSignals(1);

    //Создаем экземпляр класса Entry
    Entry newEntry = Entry();

    //Ищем ключ, который можно присвоить новой строке
    bool found = false;
    int key = 1;
    auto iterator = currentFile->data.begin();

    //Поскольку минимальный ключ в таблице раввен 1, и ключи идут
    //по возрастанию, можно просто перебирать по порядку все числа,
    //пока не найдем такое число, которого нет в таблице
    while(!found)
    {
        if (key == iterator->first)
        {
            key++;
            iterator++;
        }
        else found = true;
    }

    //В экземпляр класса Entry записываем некоторые данные
    //необходимые для корректной работы программы
    newEntry.properties["Id"] = std::to_string(key);
    newEntry.properties["Cost"] = "1";

    //Записываем в данные из файла новую строку
    currentFile->data[std::stoi(newEntry.properties["Id"])] = newEntry;

    for(int j = 0; j < 11; j++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(currentFile->data.at(key).properties.at(entryProps[j])));

        if(j == 0 || j == 9)
            item->setData(Qt::EditRole, std::stoi(newEntry.properties.at(entryProps[j])));
        else item->setData(Qt::EditRole, QString(""));

        setItem(row, j, item);
        if (j == 0)
            item->setFlags(Qt::ItemIsEnabled);
    }

    //Разрешаем таблице принимать сигналы
    blockSignals(0);

}

