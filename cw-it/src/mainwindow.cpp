#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabpage.h"
#include "about.h"
#include <QFileDialog>
#include <QTableWidget>
#include <iostream>
#include <stdio.h>
#include "filehandler.h"

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
    aboutWindow = new About(this);
    aboutWindow->show();
}


void MainWindow::on_action_triggered()
{

    OpenedFile *file = new OpenedFile;
    if(fileHandler.open(this, file))
    {

        QString fileName = QString::fromStdString(fileHandler.getFileName());
        ui->tabWidget->addTab(new TabPage(nullptr, file), fileName);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    }

}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
    fileHandler.close(index);
}


void MainWindow::on_action_2_triggered()
{
    fileHandler.save(ui->tabWidget->currentIndex());
}

