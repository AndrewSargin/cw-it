#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include "openedfile.h"

///Класс таблицы
class Table : public QTableWidget
{

    Q_OBJECT

    //Возврат каретки
    const char cr = '\r';

    //Перевод на новцю строку
    const char lf = '\n';

    //Табуляция
    const char tab = '\t';

    //Разделитель
    const char semicolon = ';';

public:

    ///Конструктор
    Table(QWidget *parent = nullptr);

    ///Получение файла с данными
    void SetFile(OpenedFile *file);

    ///Добавление новой строки
    void NewRow(int row);

protected:

    ///Обработка данных
    QMimeData *mimeData(const QList<QTableWidgetItem *> items) const override;

    ///Определение типов MIME
    QStringList mimeTypes() const override;

    ///Вставка данных
    bool dropMimeData(int row, int column, const QMimeData *data,
                      Qt::DropAction action) override;

private:

    ///Файл с данными
    OpenedFile* currentFile;

};

#endif // TABLE_H
