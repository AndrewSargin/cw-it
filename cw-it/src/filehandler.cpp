#include "filehandler.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <QFileDialog>
#include <QObject>

FileHandler::FileHandler()
{

}

int FileHandler::open(QWidget *parent, struct openedFile *file)
{
    QString fileName = QFileDialog::getOpenFileName(parent, QObject::tr("Open File"), "/home");
    const char* filePath = fileName.toUtf8().constData();
    /*FILE *openedFile;
    openedFile = fopen(filePath, "r");*/

    std::ifstream openedFile(filePath);
    std::string fileCheck;
    std::string fileLine;
    std::string lineFragment;
    std::string stream;
    std::string delimiter = ";";



    //сделать экземпляр файла, передать в open, там заполнить, и передать в tabpage






    std::getline(openedFile, fileCheck);

    if(fileCheck.compare("===cw-it===") != 0)
    {
        FileHandler::close(file);
        QDialog *fileErrorWindow = new QDialog();
        fileErrorWindow->setWindowTitle(QObject::tr("Error while reading file"));
        fileErrorWindow->show();
        return 0;
    }

    file->filePath = filePath;
    std::vector<std::string> vector = SeparateLine(filePath, "/");
    file->fileName = vector[vector.size()-1];
    //file->fileName = to be done;
    //file->fileName = "fff";
    files_vector.push_back(file);

    while(std::getline(openedFile, fileLine))
    {
        std::vector<std::string> columnValues = SeparateLine(fileLine, ";");
        file->id.push_back(columnValues[0]);
        file->type.push_back(columnValues[1]);
        file->cpu.push_back(columnValues[2]);
        file->gpu.push_back(columnValues[3]);
        file->ram.push_back(columnValues[4]);
        file->memory.push_back(columnValues[5]);
        file->date.push_back(columnValues[6]);
        file->price.push_back(columnValues[7]);
    }

    file->data.push_back(file->id);
    file->data.push_back(file->type);
    file->data.push_back(file->cpu);
    file->data.push_back(file->gpu);
    file->data.push_back(file->ram);
    file->data.push_back(file->memory);
    file->data.push_back(file->date);
    file->data.push_back(file->price);

    files_vector.push_back(file);

    return 1;

}

int FileHandler::close(struct openedFile *file){

    free(file);
    return 1;
}

std::string FileHandler::getFileName()
{
    return files_vector.back()->fileName;
}

std::vector<std::string> FileHandler::SeparateLine(std::string line, std::string delimiter)
{
    std::vector<std::string> vector;
    //std::string delimiter = ";";
    std::string token = "";
       for (int i = 0; i < line.size(); i++) {
           bool flag = true;
           for (int j = 0; j < delimiter.size(); j++) {
               if (line[i + j] != delimiter[j]) flag = false;
           }
           if (flag) {
               if (token.size() > 0) {
                   vector.push_back(token);
                   token = "";
                   i += delimiter.size() - 1;
               }
           } else {
               token += line[i];
           }
       }
       vector.push_back(token);

    return vector;
}
