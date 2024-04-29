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


///Создаем единственный на программу экземпляр класса FileHandler
FileHandler fileHandler = FileHandler();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ///Чтение настроек интерфейса
    ReadSettings();

}

MainWindow::~MainWindow()
{

    ///Запись настроек интерфейса
    WrtieSettings();

    delete ui;
}


///Открытие окна "Об авторе"
void MainWindow::on_action_4_triggered()
{
    About *aboutWindow = new About(this);
    aboutWindow->show();
}


///Открытие существующего файла
void MainWindow::on_action_triggered()
{

    OpenedFile *file = new OpenedFile;
    if(fileHandler.open(this, file, ui->tabWidget))
    {
        //Получение названия файла
        QString fileName = QString::fromStdString(fileHandler.getFileName());

        //Создание новой страницы в виджете QTabWidget
        ui->tabWidget->addTab(new TabPage(nullptr, file), fileName);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

        //Включение кнопок, доступных только, когда есть файл с данными
        ui->actionPrint->setEnabled(1);
        ui->actionShow->setEnabled(1);
    }
}


///Создание нового файла
void MainWindow::on_action_New_File_triggered()
{
    OpenedFile *file = new OpenedFile;
    fileHandler.NewFile(file);

    //Получение названия файла
    QString fileName = QString::fromStdString(fileHandler.getFileName());

    //Создание новой страницы в виджете QTabWidget
    ui->tabWidget->addTab(new TabPage(nullptr, file), fileName);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    //Включение кнопок, доступных только, когда есть файл с данными
    ui->actionPrint->setEnabled(1);
    ui->actionShow->setEnabled(1);
}


///Закрытие страницы в виджете QTabWidget
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    //Если закрываемый файл был изменен, спрашиваем пользователя
    //о сохранении перед выходом
    if (fileHandler.isFileChanged(index) == true)
    {
        AskForSave *saveWindow = new AskForSave(this, &fileHandler, index);
        saveWindow->show();
    }

    //Удаление страницы
    ui->tabWidget->removeTab(index);

    //Если страниц больше нет, то блокируем кнопки, которые не должны работать
    //без данных
    if (ui->tabWidget->count() == 0)
    {
        ui->actionPrint->setDisabled(1);
        ui->actionShow->setDisabled(1);
    }

    //Закрытие файла в классе, управляющем файлами
    fileHandler.close(index);
}


///Сохранение файла
void MainWindow::on_action_2_triggered()
{
    //Проверка на наличие файла
    if(ui->tabWidget->count() != 0)
        fileHandler.save(this, ui->tabWidget->currentIndex());
}


///Функция "Сохранить как
void MainWindow::on_actionSave_As_triggered()
{
    if(ui->tabWidget->count() != 0)
        fileHandler.saveAs(this, ui->tabWidget->currentIndex());
}


///Закрытие файла через меню программы
void MainWindow::on_action_3_triggered()
{
    int index = ui->tabWidget->currentIndex();
    //Если есть хотя бы одна страница в QTabWidget, закрываем ее
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
    //Если в QTabWidget нет страниц, то закрываем саму программу
    else MainWindow::close();
}


///Перевести программу на английский язык
void MainWindow::on_actionEnglish_triggered()
{
    if (languageTranslator.load(".qm/cw-it_en_US"))
        qApp->installTranslator(&languageTranslator);
}


///Перевести программу на русский язык
void MainWindow::on_actionRussian_triggered()
{
    if(languageTranslator.load(".qm/cw-it_ru_RU."))
        qApp->installTranslator(&languageTranslator);
}


///Событие изменения языка
void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
}


///Функция запоминания настроек интерфейса
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


///Функция чтения настроек интерфейса
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


///Вывод данных на печать
void MainWindow::on_actionPrint_triggered()
{
    //Настройка параметров печати
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(QDir::currentPath() + "/cw-it.pdf");

    //Настройка параметров страницы
    printer.pageLayout().setMode(QPageLayout::FullPageMode);
    printer.setPageMargins(QMargins(0, 0, 0, 0));
    printer.setPageOrientation(QPageLayout::Orientation::Landscape);

    //Создаем диалоговое окно печати и устанавливаем настройки принтера
    QPrintDialog printDialog(&printer, nullptr);
    printDialog.setWindowTitle("Print");
    printDialog.setOptions(QAbstractPrintDialog::PrintToFile | QAbstractPrintDialog::PrintPageRange);

    if (printDialog.exec() != QDialog::Accepted)
    {
        return;
    }

    //Запись данных в документ для вывода
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

    //Печать документа
    textBrowser.print(&printer);

    return;
}


///Показать диаграмму
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
