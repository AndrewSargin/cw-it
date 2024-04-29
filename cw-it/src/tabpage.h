#ifndef TABPAGE_H
#define TABPAGE_H

#include <QWidget>
#include <openedfile.h>

namespace Ui {
class TabPage;
}

/// \brief Класс страницы в QtTabWidget
class TabPage : public QWidget
{
    Q_OBJECT

public:

    ///Конструктор
    explicit TabPage(QWidget *parent = nullptr, OpenedFile *file = nullptr);

    ///Деструктор
    ~TabPage();

private slots:

    ///Вызвается при изменении ячейки таблицы
    void on_tableWidget_cellChanged(int row, int column);

    ///Вызов контекстного меню
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    ///Добавление новой строки после выбранной
    void on_addAfter_triggered();

    ///Добавление новой строки перед выбранной
    void on_addBefore_triggered();

    ///Удаление выбранной строки
    void on_deleteEntry_triggered();

    ///Создает строку в указанном месте
    void NewRow(int row);

    ///При изменении поискового запроса
    void on_lineEdit_textChanged(const QString &arg1);

private:

    Ui::TabPage *ui;

    ///Храним открытый файл (программа работает таким образом, что
    ///за каждой страницей в QtTabWidget закреплен свой файл, причем
    ///индекс страницы совпадает с индексом файла, хранящимся в
    ///векторе файлов)
    OpenedFile *currentFile;

};

#endif // TABPAGE_H
