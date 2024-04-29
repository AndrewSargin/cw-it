#include "entry.h"
#include "technical.h"
#include "constants.h"
#include <iostream>
#include <vector>


///Конструктор (получает строку из файла)
Entry::Entry(std::string line)
{

    //Разделитель в строке файла
    std::string delimiter = ";";

    //Разбиваем строку
    std::vector<std::string> columnEtries = SplitLine(line, delimiter);

    //Записываем данные из строки в экземпляр класса
    for(int i = 0; i < (int) columnEtries.size() - 1; i++)
    {
        properties.insert({entryProps[i], columnEtries[i]});
    }
}


///Конструктор класса (не получает никаких данных)
Entry::Entry()
{

    //Заполняем все данные пустотой
    for(int i = 0; i < 11; i++)
    {
        properties.insert({entryProps[i], ""});
    }
}

