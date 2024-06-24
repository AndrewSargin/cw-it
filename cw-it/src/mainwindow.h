#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QTranslator>
#include "about.h"
#include "constants.h"
#include <QApplication>
#include <QSettings>
#include <QPrinter>
#include <QtPrintSupport>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// \brief Класс основного окна
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    //Конструктор
    MainWindow(QWidget *parent = nullptr);

    //Деструктор
    ~MainWindow();

protected:

    //Событие изменения языка
    void changeEvent(QEvent * event) override;

private slots:

    //Вызов окна "Об авторе"
    void on_action_4_triggered();

    //Открыть файл
    void on_action_triggered();

    //Закрыть страницу в QTabWidget
    void on_tabWidget_tabCloseRequested(int index);

    //Сохранить файл
    void on_action_2_triggered();

    //Закрыть файл или программу
    void on_action_3_triggered();

    //Перевести программу на английский
    void on_actionEnglish_triggered();

    //Перевести программу на русский
    void on_actionRussian_triggered();

    //Перевести программу на армянский
    void on_action_HY_triggered();


    //Печать документа
    void on_actionPrint_triggered();

    //Открыть график
    void on_actionShow_triggered();

    //Создать новый файл
    void on_action_New_File_triggered();

    //Сохранить как
    void on_actionSave_As_triggered();

private:

    Ui::MainWindow *ui;
    QTranslator languageTranslator;

    //Запись настроек интерфейса
    void WrtieSettings();

    //Чтение настроек интерфейса
    void ReadSettings();

};
#endif // MAINWINDOW_H
