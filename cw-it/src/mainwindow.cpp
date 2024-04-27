#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabpage.h"
#include "about.h"
#include <QFileDialog>
#include <QTableWidget>
#include <iostream>
#include <stdio.h>
#include "filehandler.h"
#include "askforsave.h"
#include <QApplication>
#include <QSettings>

FileHandler fileHandler = FileHandler();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ReadSettings();

}

MainWindow::~MainWindow()
{
    WrtieSettings();

    delete ui;
}


void MainWindow::on_action_4_triggered()
{
    About *aboutWindow = new About(this);
    aboutWindow->show();
}


void MainWindow::on_action_triggered()
{

    OpenedFile *file = new OpenedFile;
    if(fileHandler.open(this, file, ui->tabWidget))
    {
        QString fileName = QString::fromStdString(fileHandler.getFileName());
        ui->tabWidget->addTab(new TabPage(nullptr, file), fileName);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (fileHandler.isFileChanged(index) == true)
    {
        AskForSave *saveWindow = new AskForSave(this, &fileHandler, index);
        saveWindow->show();
    }

    ui->tabWidget->removeTab(index);
    fileHandler.close(index);
}


void MainWindow::on_action_2_triggered()
{
    if(ui->tabWidget->count() != 0)
        fileHandler.save(ui->tabWidget->currentIndex());
}

void MainWindow::on_action_3_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index != -1)
    {
        if (fileHandler.isFileChanged(index) == true)
        {
            AskForSave *saveWindow = new AskForSave(this, &fileHandler, index);
            saveWindow->show();
        }

        ui->tabWidget->removeTab(index);
        fileHandler.close(index);
    }
    else MainWindow::close();
}


void MainWindow::on_actionEnglish_triggered()
{
    if (languageTranslator.load(".qm/cw-it_en_US"))
        qApp->installTranslator(&languageTranslator);


}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
}


void MainWindow::on_actionRussian_triggered()
{
    if(languageTranslator.load(".qm/cw-it_ru_RU."))
        qApp->installTranslator(&languageTranslator);
}

void MainWindow::WrtieSettings()
{
    QSettings settings("cw-it", "cw-it");

    settings.beginGroup("mainWindow");
    settings.setValue("size", size());
    settings.setValue("position", pos());
    settings.endGroup();

    settings.beginGroup("language");
    settings.setValue("language", languageTranslator.filePath());
    settings.endGroup();

}

void MainWindow::ReadSettings()
{
    QSettings settings("cw-it", "cw-it");

    settings.beginGroup("mainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize()); // сбрасываем размеры окна
    move(settings.value("position", QPoint(200, 200)).toPoint()); // сбрасываем крайнюю левую верхнюю точку
    settings.endGroup();

    settings.beginGroup("language");
    languageTranslator.load(settings.value("language", QString()).toString());
    settings.endGroup();

    qApp->installTranslator(&languageTranslator);

}
