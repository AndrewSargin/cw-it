#include "chart.h"
#include "ui_chart.h"
#include <QtCharts>
#include <algorithm>


///Конструктор
Chart::Chart(QWidget *parent, std::vector<std::vector<float>> vector) :
    QMainWindow(parent),
    ui(new Ui::Chart)
{
    ui->setupUi(this);

    QRect availableGeometry = QApplication::desktop()->availableGeometry(this);

    int x = (availableGeometry.width() - this->width()) / 2;
    int y = (availableGeometry.height() - this->height()) / 2;
    this->move(x, y);

    setWindowTitle(tr("Chart of total price of computers depending on RAM and memory"));

    CreateChart(vector);

}

bool sortcol(const std::vector<float>& v1, const std::vector<float>& v2)
{
    return v1[0]<v2[0];
}


///Деструктор
Chart::~Chart()
{
    delete ui;
}


///Создание графика
void Chart::CreateChart(std::vector<std::vector<float>> data)
{
    QBarSeries *series = new QBarSeries;

    std::vector<float> memoryList;
    std::vector<float> ramList;

    QStringList ramLabels;

    std::sort(data.begin(), data.end(), sortcol);

    for (int i = 0; i < (int) data.size(); i++)
    {
        if(std::find(memoryList.begin(), memoryList.end(), data[i][1]) == memoryList.end())
            memoryList.push_back(data[i][1]);

        if(std::find(ramList.begin(), ramList.end(), data[i][0]) == ramList.end())
        {
            ramList.push_back(data[i][0]);
            ramLabels.push_back(QString::number(data[i][0]));
        }

    }

    std::sort(memoryList.begin(), memoryList.end());

    for (int i = 0; i < (int) memoryList.size(); i++)
    {
        QBarSet *set = new QBarSet(QString::number(memoryList[i]));

        float price = 0;

        for(int j = 0; j < (int) ramList.size(); j++)
        {
            for(int k = 0; k < (int) data.size(); k++)
            {
                if (data[k][1] == memoryList[i] && ramList[j] == data[k][0])
                {
                    price += data[k][2];
                }
            }

            *set << price;
            price = 0;
        }

        series->append(set);
    }

    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);


    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(ramLabels);

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->setTitle(tr("Total price of computers depending on RAM and memory"));

    this->setCentralWidget(chartView);
    this->resize(1000, 600);

}
