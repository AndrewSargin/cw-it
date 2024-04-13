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

FileHandler fileHandler = FileHandler();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
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
}


void MainWindow::on_actionEnglish_triggered()
{

}

