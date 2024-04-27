#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QTranslator>
#include "about.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void changeEvent(QEvent * event) override;

private slots:
    void on_action_4_triggered();

    void on_action_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_actionEnglish_triggered();

    void on_actionRussian_triggered();

private:
    Ui::MainWindow *ui;
    QTranslator languageTranslator;

    void WrtieSettings();

    void ReadSettings();

};
#endif // MAINWINDOW_H
