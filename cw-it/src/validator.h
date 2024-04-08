#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QTableWidgetItem>


class Validator
{
public:

    Validator();

    void PriceInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine);
    void DateInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine);

};

#endif // VALIDATOR_H
