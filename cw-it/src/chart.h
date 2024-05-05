#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class Chart;
}


/// \brief Класс, создающий график
class Chart : public QMainWindow
{
    Q_OBJECT

public:

    ///Конструктор
    explicit Chart(QWidget *parent = nullptr, std::vector<std::vector<float>> price = std::vector<std::vector<float>>());

    ///Деструктор
    ~Chart();

    ///Создание графика
    void CreateChart(std::vector<std::vector<float>>);

private:

    Ui::Chart *ui;
};

#endif // CHART_H
