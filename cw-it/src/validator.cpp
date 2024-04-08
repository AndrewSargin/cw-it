#include "validator.h"
#include <iostream>

Validator::Validator()
{

}

void Validator::PriceInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine)
{
    try
    {
        float price = std::stof(item->text().toStdString());
    }
    catch(...)
    {
        item->setText(QString::fromStdString(currentLine->at("Cost")));
    }
}

void Validator::DateInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine)
{

    std::string dateStr = item->text().toStdString();
    std::string writeDate;
    std::string ddStr, mmStr, yyyyStr;
    int ddNum, mmNum, yyyyNum;

    if (dateStr.length() != 8 && dateStr.length() != 10)
    {
        item->setText(QString::fromStdString(currentLine->at("DateOfPurchase")));
        return;
    }
    else {
        if (dateStr.length() == 8)
        {
            ddStr = dateStr.substr(0, 2);
            ddNum = std::stoi(ddStr);
            mmStr = dateStr.substr(2, 2);
            mmNum = std::stoi(mmStr);
            yyyyStr = dateStr.substr(4, 4);
            yyyyNum = std::stoi(yyyyStr);
        }
        else
        {
            ddStr = dateStr.substr(0, 2);
            ddNum = std::stoi(ddStr);
            mmStr = dateStr.substr(3, 2);
            mmNum = std::stoi(mmStr);
            yyyyStr = dateStr.substr(6, 4);
            yyyyNum = std::stoi(yyyyStr);
        }

        if (ddNum < 1 || ddNum > 31 || mmNum < 1 || mmNum > 12 ||
                yyyyNum < 1990 || yyyyNum > 2050) // по возможности сделать, чтобы
            //сравнивалось с нынешним годом
        {
            item->setText(QString::fromStdString(currentLine->at("DateOfPurchase")));
            return;
        }
    }

    writeDate = ddStr + "." + mmStr + "." + yyyyStr;
    item->setText(QString::fromStdString(writeDate));
}
