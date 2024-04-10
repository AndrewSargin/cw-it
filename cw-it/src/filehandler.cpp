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

FileHandler::FileHandler()
{

}

int FileHandler::open(QWidget *parent, OpenedFile *file, QTabWidget *tabWidget)
{
    QString fileName = QFileDialog::getOpenFileName(parent, QObject::tr("Open File"), "/home");
    std::string filePath = fileName.toUtf8().constData();

    if(filePath == "")
        return 0;

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

    std::getline(openedFile, fileCheck);

    if(fileCheck.compare("===cw-it===") != 0)
    {
        openedFile.close();
        FileReadingError *errWindow = new FileReadingError(parent);
        errWindow->show();
        return 0;
    }

    file->filePath = filePath;
    std::vector<std::string> vector = SplitLine(filePath, "/");
    file->fileName = vector[vector.size()-1];

    for(std::string line; std::getline(openedFile, line);)
    {
        Entry newEntry = Entry(line);
        file->data[std::stoi(newEntry.properties["Id"])] = newEntry;

    }

    files_vector.push_back(file);

    openedFile.close();

    return 1;

}

int FileHandler::close(int index)
{

    files_vector.erase(files_vector.begin()+index);
    return 1;
}

void FileHandler::save(int index)
{
    OpenedFile *dataToSave = files_vector[index];
    std::ofstream fileToSave(dataToSave->filePath);
    fileToSave << "===cw-it===\n";
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

    dataToSave->isChanged = false;
    fileToSave.close();

}

std::string FileHandler::getFileName()
{
    return files_vector.back()->fileName;
}

bool FileHandler::isFileChanged(int index)
{
    return files_vector[index]->isChanged;
}
