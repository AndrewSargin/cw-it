#include "validator.h"
#include <iostream>
#include <ctime>
#include "technical.h"
#include <cctype>

///Конструктор класса
Validator::Validator()
{

}


///Проверка ввода цены
void Validator::PriceInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine)
{

    //Пробуем преобразовать данные в число
    try
    {
        std::stof(item->text().toStdString());
    }

    //Если не получается, то восстанавливаем данные в ячейке
    catch(...)
    {
        item->setText(QString::fromStdString(currentLine->at("Cost")));
    }
}


///Проверка ввода даты
void Validator::DateInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine)
{

    //Преобразовываем данные в строковый тип
    std::string dateStr = item->text().toStdString();
    std::string writeDate;
    std::string ddStr, mmStr, yyyyStr;
    int ddNum, mmNum, yyyyNum;

    //Если длина строки даты не 8, и не 10, восстанавливаем данные в ячейке
    if (dateStr.length() != 8 && dateStr.length() != 10)
    {
        item->setText(QString::fromStdString(currentLine->at("DateOfPurchase")));
        return;
    }
    else {
        //Если длина строки равна 8
        if (dateStr.length() == 8)
        {
            //В качестве дня записываем первые 2 символа
            ddStr = dateStr.substr(0, 2);
            ddNum = std::stoi(ddStr);

            //В качестве месяца записываем 3 и 4 символы
            mmStr = dateStr.substr(2, 2);
            mmNum = std::stoi(mmStr);

            //В качестве года записываем символы с 5 по 8
            yyyyStr = dateStr.substr(4, 4);
            yyyyNum = std::stoi(yyyyStr);
        }

        //Если длина строки равна 10
        else
        {
            //В качестве дня записываем первые 2 символа
            ddStr = dateStr.substr(0, 2);
            ddNum = std::stoi(ddStr);

            //В качестве месяца записываем 4 и 5 символа
            mmStr = dateStr.substr(3, 2);
            mmNum = std::stoi(mmStr);

            //В качестве года записываем символы с 7 по 10
            yyyyStr = dateStr.substr(6, 4);
            yyyyNum = std::stoi(yyyyStr);
        }

        //Получаем нынешний год
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int currentYear = 1900 + ltm->tm_year;

        //Проверка введенной дати на правдоподобность
        if (ddNum < 1 || ddNum > 31 || mmNum < 1 || mmNum > 12 ||
                yyyyNum < 1990 || yyyyNum > currentYear)
        {
            item->setText(QString::fromStdString(currentLine->at("DateOfPurchase")));
            return;
        }
    }

    //Запись введенных данных в ячейку таблицы
    writeDate = ddStr + "." + mmStr + "." + yyyyStr;
    item->setText(QString::fromStdString(writeDate));
}


///Проверка ввода ОЗУ
void Validator::RamInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine)
{

    //Разделяем запись в клетке по пробелам
    std::vector<std::string> ram = SplitLine(item->text().toStdString(), " ");

    //Если пользователь не ввел ничего, записываем в изначальные данные пустоту
    if (ram.size() == 1 && ram[0] == "")
    {
        currentLine->at("RAM") = "";
        return;
    }

    //Если в клетке ОЗУ было не 2 набора символов (например, 8 + Гб)
    if (ram.size() != 2)
    {
        //Восстанавливаем значение в клетке
        item->setData(Qt::EditRole, QString::fromStdString(currentLine->at("RAM")));
        return;
    }

    //Проверяем, чтобы все символы в первом наборе символов клетки были цифрами
    for (int i = 0; i < (int) ram[0].size(); i++)
        if (!std::isdigit(ram[0][i]))
        {
            item->setData(Qt::EditRole, QString::fromStdString(currentLine->at("RAM")));
            return;
        }

    //Если пользователь ввел число с нулем в начале, избавляемся от него
    int ramInt = std::stoi(ram[0]);
    ram[0] = std::to_string(ramInt);

    //Проверка на то, что пользователь ввел значения в гигабатах
    if (ram[1] != "гб" && ram[1] !="ГБ" && ram[1] != "Гб" && ram[1] !="гБ")
    {
        item->setData(Qt::EditRole, QString::fromStdString(currentLine->at("RAM")));
        return;
    }

    //Записываем в клетку новое значение (так, чтобы в "Гб" первый символ
    //был заглавный, второй - строчный (не имеет значения, но так захотелось))
    QString ramString = QString::fromStdString(ram[0]) + " Гб";
    item->setData(Qt::EditRole, ramString);

}


/// Проверка ввода памяти
void Validator::MemoryInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine)
{

    //Разделяем запись в клетке по плюсам (если несколько запоминающих устройств)
    std::vector<std::string> memory = SplitLine(item->text().toStdString(), "+");

    //Переменная для запоминания обработанных данных
    QString memoryString = "";

    //Если пользователь ввел пустоту, записываем в изначальные даные пустоту
    if (memory.size() == 1 && memory[0] == "")
    {
        currentLine->at("Memory") = "";
        return;
    }

    for (int j = 0; j < (int) memory.size(); j++)
    {
        //Разбиваем набор по пробелам
        std::vector<std::string> memoryEntry = SplitLine(memory[j], " ");

        //Если ЗУ описано не 3 наборами символов (например, 8 + Гб + SSD)
        if (memoryEntry.size() != 3 && memoryEntry[0] != "")
        {
            //Восстанавливаем значение в клетке
            item->setData(Qt::EditRole, QString::fromStdString(currentLine->at("Memory")));
            return;
        }

        //Проверяем, чтобы все символы в первом наборе символов клетки были цифрами
        for (int i = 0; i < (int) memoryEntry[0].size(); i++)
            if (!std::isdigit(memoryEntry[0][i]))
            {
                item->setData(Qt::EditRole, QString::fromStdString(currentLine->at("Memory")));
                return;
            }

        //Если пользователь ввел число с нулем в начале, избавляемся от него
        int memoryInt = std::stoi(memoryEntry[0]);
        memoryEntry[0] = std::to_string(memoryInt);

        //Проверка на то, что пользователь ввел значения в гигабатах  или терабайтах
        if (memoryEntry[1] != "гб" && memoryEntry[1] != "ГБ" && memoryEntry[1] != "Гб" && memoryEntry[1] != "гБ" &&
                memoryEntry[1] != "тб" && memoryEntry[1] != "ТБ" && memoryEntry[1] != "Тб" && memoryEntry[1] != "тБ")
        {
            item->setData(Qt::EditRole, QString::fromStdString(currentLine->at("Memory")));
            return;
        }

        //Проверка на то, что пользователь ввел в качестве ЗУ
        if (memoryEntry[2] != "SSD" && memoryEntry[2] != "HDD")
        {
            item->setData(Qt::EditRole, QString::fromStdString(currentLine->at("Memory")));
            return;
        }

        //Записываем в переменную новое значение (так, чтобы в "Гб" первый символ
        //был заглавный, второй - строчный (не имеет значения, но так захотелось))
        if (memoryString != "")
            memoryString += " ";
        if (memoryEntry[1] == "гб" || memoryEntry[1] == "ГБ" || memoryEntry[1] == "Гб" || memoryEntry[1] == "гБ")
            memoryString += QString::fromStdString(memoryEntry[0]) + " Гб " + QString::fromStdString(memoryEntry[2]);
        else memoryString += QString::fromStdString(memoryEntry[0]) + " Тб " + QString::fromStdString(memoryEntry[2]);

    }

    //Записываем в клетку новое значение
    item->setData(Qt::EditRole, memoryString);
    return;

}
