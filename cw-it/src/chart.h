#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class Chart;
}

class Chart : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chart(QWidget *parent = nullptr, std::vector<float> price = std::vector<float>());

    ~Chart();

    void CreateChart(std::vector<float> price);

private:

    Ui::Chart *ui;
};

#endif // CHART_H
