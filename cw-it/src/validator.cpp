#include "validator.h"
#include <iostream>
#include <ctime>


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
