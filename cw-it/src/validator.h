#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QTableWidgetItem>


/// \brief Класс для проверки введенных пользователем данных
class Validator
{
public:


    ///Конструктор класса
    Validator();

    ///Проверка ввода цены
    void PriceInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine);

    ///Проверка ввода даты
    void DateInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine);

    ///Проверка ввода ОЗУ
    void RamInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine);

    /// Проверка ввода памяти
    void MemoryInput(QTableWidgetItem *item, std::map<std::string, std::string> *currentLine);

};

#endif // VALIDATOR_H
