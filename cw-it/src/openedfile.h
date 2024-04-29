#ifndef OPENEDFILE_H
#define OPENEDFILE_H

#include <map>
#include <vector>
#include <string>
#include "entry.h"


/// \brief Класс открытого файла
class OpenedFile
{
public:

    ///Конструктор
    OpenedFile();

    ///Путь файла
    std::string filePath;

    ///Название файла
    std::string fileName;

    ///Данные из файла
    std::map<int, Entry> data;

    ///Состояние файла
    bool isChanged = false;
};

#endif // OPENEDFILE_H
