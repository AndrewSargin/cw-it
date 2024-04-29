#ifndef FILEREADINGERROR_H
#define FILEREADINGERROR_H

#include <QDialog>

namespace Ui {
class FileReadingError;
}


/// \brief Класс, вызывающий окно об ошибке чтения
class FileReadingError : public QDialog
{
    Q_OBJECT

public:

    ///Конструктор
    explicit FileReadingError(QWidget *parent = nullptr);

    ///Деструктор
    ~FileReadingError();

private:
    Ui::FileReadingError *ui;
};

#endif // FILEREADINGERROR_H
