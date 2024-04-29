#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

/// \brief Класс окна "Об авторе"
class About : public QDialog
{
    Q_OBJECT

public:

    ///Конструктор класса
    explicit About(QWidget *parent = nullptr);

    ///Деструктор класса
    ~About();

private slots:

    ///Вызывается при нажатии на кнопку в окне
    void on_pushButton_clicked();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
