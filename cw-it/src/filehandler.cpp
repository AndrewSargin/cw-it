#include "filehandler.h"
#include "technical.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QFileDialog>
#include <QObject>
#include "entry.h"
#include "filereadingerror.h"


///Конструктор класса
FileHandler::FileHandler()
{

}


///Открытие файла
int FileHandler::open(QWidget *parent, OpenedFile *file, QTabWidget *tabWidget)
{
    //Получение пути открываемого файла
    QString fileName = QFileDialog::getOpenFileName(parent, QObject::tr("Open File"), "/home");
    std::string filePath = fileName.toUtf8().constData();

    //Если отменили открывание файла
    if(filePath == "")
        return 0;

    //Проверка, что файл еще не открыт в программе (по полному пути файла)
    for (int i = 0; i < (int) files_vector.size(); i++)
    {
        if (files_vector[i]->filePath == filePath)
        {
            tabWidget->setCurrentIndex(i);
            return 0;
        }
    }

    std::ifstream openedFile(filePath);
    std::string fileCheck;
    std::string fileLine;
    std::string lineFragment;
    std::string stream;
    std::string delimiter = ";";

    //Получение самой первой строки файла
    //(Программа работает только с теми файлами, у которых в первой строке
    //записано "===cw-it===")
    std::getline(openedFile, fileCheck);

    if(fileCheck.compare("===cw-it===") != 0)
    {
        //Говорим пользователю о том, что программа не работает с
        //открытым файлом
        openedFile.close();
        FileReadingError *errWindow = new FileReadingError(parent);
        errWindow->show();
        return 0;
    }

    //Запись пути файла в информацию о файле
    file->filePath = filePath;
    //делим путь файла таким образом, чтобы можно было извлечь
    //только название файла
    std::vector<std::string> vector = SplitLine(filePath, "/");
    //Записываем название файла в информацию о файле
    file->fileName = vector[vector.size()-1];

    //Считываем файл со второй строки до конца
    for(std::string line; std::getline(openedFile, line);)
    {
        //Создаем экземпляр класса Entry, который хранит в себе
        //строку из файла
        Entry newEntry = Entry(line);

        //Записываем в data экземпляр класса Entry
        file->data[std::stoi(newEntry.properties["Id"])] = newEntry;

    }

    //Добавляем в вектор файлов указатель на открытый файл
    files_vector.push_back(file);

    //Закрываем файл
    openedFile.close();

    return 1;

}


///Создать новый файл
void FileHandler::NewFile(OpenedFile *file)
{
    //Записываем в информацию о файле пустой путь
    file->filePath = "";

    //Называем файл "Безымянным"
    file->fileName = "Untitled";

    //Создаем экземпляр класса Entry
    Entry newEntry = Entry();

    //Записываем в экземпляр минимальную информацию
    //(Чтобы программа могла работать корректно)
    newEntry.properties["Id"] = "1";
    newEntry.properties["Cost"] = "0";

    //Записываем в данные из файла экземпляр Entry
    file->data[1] = newEntry;

    //Записываем в конец вектора файлов новый файл
    files_vector.push_back(file);
}


///Закрытие файла
int FileHandler::close(int index)
{
    //Удаляем из вектора файлов закрываемый файл
    files_vector.erase(files_vector.begin()+index);
    return 1;
}


///Сохранение файла
void FileHandler::save(QWidget *parent, int index)
{
    OpenedFile *dataToSave = files_vector[index];

    //Если в информации о файле отсутствует путь, значит, этот файл
    //был создан в программе, и его необходимо где-то сохранить, поэтому
    //вызываем диалоговое окно сохранения файла
    if (dataToSave->filePath == "")
    {
         dataToSave->filePath = QFileDialog::getSaveFileName(parent, QObject::tr("Save Document"), QDir::cleanPath("./.."), "Text Files (*.db)", nullptr).toStdString();

         //Если пользователь закрыл диалоговое окно сохранения файла,
         //выходим из метода
         if (dataToSave->filePath == "")
             return;
    }

    std::ofstream fileToSave(dataToSave->filePath);

    //Записываем в первую строку документа строчку, по которой программа
    //распознает рабочие файлы
    fileToSave << "===cw-it===\n";

    //Записываем необходимые данные в документ
    for(auto i = dataToSave->data.begin(); i != dataToSave->data.end(); i++)
    {
        for(int j = 0; j < 11; j++)
        {
            fileToSave << dataToSave->data.at(i->first).properties.at(entryProps[j]);
            fileToSave << ";";

            if(j == 10)
                fileToSave << "\n";
        }
    }

    //Ставим состояние файла "не изменен"
    dataToSave->isChanged = false;

    //Закрываем файл
    fileToSave.close();

}


///Сохранить как
void FileHandler::saveAs(QWidget *parent, int index)
{
    OpenedFile *dataToSave = files_vector[index];

    //Получаем путь для сохранения файла
    std::string filePath = QFileDialog::getSaveFileName(parent, QObject::tr("Save Document"), QDir::cleanPath("./.."), "Text Files (*.db)", nullptr).toStdString();

    //Если закрывается диалоговое окно сохранения файла,
    //выходим из метода
    if (filePath == "")
        return;
    //Иначе записываем путь в информацию о файле
    else dataToSave->filePath = filePath;

    std::ofstream fileToSave(dataToSave->filePath);

    //Записываем в первую строку документа строчку, по которой программа
    //распознает рабочие файлы
    fileToSave << "===cw-it===\n";

    //Записываем необходимые данные в документ
    for(auto i = dataToSave->data.begin(); i != dataToSave->data.end(); i++)
    {
        for(int j = 0; j < 11; j++)
        {
            fileToSave << dataToSave->data.at(i->first).properties.at(entryProps[j]);
            fileToSave << ";";

            if(j == 10)
                fileToSave << "\n";
        }
    }

    //Ставим состояние файла "не изменен"
    dataToSave->isChanged = false;

    //Закрываем файл
    fileToSave.close();

}


///Получить название файла
std::string FileHandler::getFileName()
{
    return files_vector.back()->fileName;
}


///Узнать состояние файла
bool FileHandler::isFileChanged(int index)
{
    return files_vector[index]->isChanged;
}


///Получить все данные из файла
std::map<int, Entry> FileHandler::getFileData(int index)
{
    return files_vector[index]->data;
}
