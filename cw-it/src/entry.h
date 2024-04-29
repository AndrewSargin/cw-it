#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <vector>
#include <map>


/// \brief Класс, хранящий строку из файла
class Entry
{

public:

    ///Конструктор (получает строку из файла)
    Entry(std::string line);

    ///Конструктор
    Entry();

    ///Данные из строки
    std::map<std::string, std::string> properties;
};

#endif // ENTRY_H
