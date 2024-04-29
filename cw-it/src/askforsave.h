#ifndef ASKFORSAVE_H
#define ASKFORSAVE_H

#include <QDialog>
#include "filehandler.h"

namespace Ui {
class AskForSave;
}


/// \brief Класс, создающий окно, предупреждающее
/// о закрытии несохраненного файла
class AskForSave : public QDialog
{
    Q_OBJECT

public:

    ///Конструктор
    explicit AskForSave(QWidget *parent = nullptr, FileHandler *fileHandler = nullptr, int index = 0);

    ///Деструктор
    ~AskForSave();

private slots:

    ///Согласие на сохранение
    void on_buttonBox_accepted();

    ///Отказ от сохранения
    void on_buttonBox_rejected();

private:

    Ui::AskForSave *ui;

    ///Храним экземпляр класса, управляющего файлами
    FileHandler *fileHandler;

    ///Индекс закрываемого файла
    int index;

    QWidget *parent;
};

#endif // ASKFORSAVE_H
