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
#include "chart.h"

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

        ui->actionPrint->setEnabled(1);
        ui->actionShow->setEnabled(1);
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

    if (ui->tabWidget->count() == 0)
    {
        ui->actionPrint->setDisabled(1);
        ui->actionShow->setDisabled(1);
    }

    fileHandler.close(index);
}


void MainWindow::on_action_2_triggered()
{
    if(ui->tabWidget->count() != 0)
        fileHandler.save(this, ui->tabWidget->currentIndex());
}

void MainWindow::on_actionSave_As_triggered()
{
    if(ui->tabWidget->count() != 0)
        fileHandler.saveAs(this, ui->tabWidget->currentIndex());
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

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(QDir::currentPath() + "/cw-it.pdf");

    printer.pageLayout().setMode(QPageLayout::FullPageMode);
    printer.setPageMargins(QMargins(0, 0, 0, 0));
    printer.setPageOrientation(QPageLayout::Orientation::Landscape);

    /// Создаем диалоговое окно печати и устанавливаем настройки принтера
    QPrintDialog printDialog(&printer, nullptr);
    printDialog.setWindowTitle("Print");
    printDialog.setOptions(QAbstractPrintDialog::PrintToFile | QAbstractPrintDialog::PrintPageRange);

    /// Установка стиля CSS для диалогового окна печати
    printDialog.setStyleSheet("background-color: #272727; color: white;");

    if (printDialog.exec() != QDialog::Accepted)
    {
        return;
    }

    QString htmlTable;
    htmlTable = "<table border=1 cellspacing=1>\n"
                "<caption>Учет вычислительной техники на балансе строительной компании</caption>\n"
                "<tr>\n";

    for (int i = 0; i < (int) columnNames.size(); i++)
    {
        htmlTable += "<th>";
        htmlTable += columnNames[i].c_str();
        htmlTable += "</th>\n";
    }

    htmlTable += "</tr>\n";

    std::map<int, Entry> data = fileHandler.getFileData(ui->tabWidget->currentIndex());

    for (auto i = data.begin(); i != data.end(); i++)
    {
       htmlTable += "<tr>";

       for(int j = 0; j < 11; j++)
       {
           htmlTable += "<td>";
           htmlTable += i->second.properties.at(entryProps[j]).c_str();
           htmlTable += "</td>";
       }

       htmlTable += "</tr>\n";

    }

    htmlTable += "</table>\n<br>\n";

    QTextDocument document;
    document.setHtml(htmlTable);

    QTextBrowser textBrowser;
    textBrowser.setDocument(&document);

    textBrowser.print(&printer);

    return;
}


void MainWindow::on_actionShow_triggered()
{

    std::vector<float> price;
    std::map<int, Entry> data = fileHandler.getFileData(ui->tabWidget->currentIndex());

    for (auto i = data.begin(); i != data.end(); i++)
    {
        if (i->second.properties.at("Cost") != "")
            price.push_back(std::stof(i->second.properties.at("Cost")));
    }

    if(price.size() > 0)
    {
        Chart *newChart = new Chart(this, price);
        newChart->show();
    }
    else
    {
        QMessageBox::warning(this, "", tr("No data to put in chart"));
        return;
    }

}


void MainWindow::on_action_New_File_triggered()
{
    OpenedFile *file = new OpenedFile;
    fileHandler.NewFile(file);

    QString fileName = QString::fromStdString(fileHandler.getFileName());
    ui->tabWidget->addTab(new TabPage(nullptr, file), fileName);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    ui->actionPrint->setEnabled(1);
    ui->actionShow->setEnabled(1);
}
