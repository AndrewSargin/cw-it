#include "chart.h"
#include "ui_chart.h"
#include <QtCharts>


Chart::Chart(QWidget *parent, std::vector<float> price) :
    QMainWindow(parent),
    ui(new Ui::Chart)
{
    ui->setupUi(this);

    QRect availableGeometry = QApplication::desktop()->availableGeometry(this);

    int x = (availableGeometry.width() - this->width()) / 2;
    int y = (availableGeometry.height() - this->height()) / 2;
    this->move(x, y);

    setWindowTitle(tr("Computer distribution chart depending on price"));

    CreateChart(price);

}

Chart::~Chart()
{
    delete ui;
}

void Chart::CreateChart(std::vector<float> price)
{

    QBarSet *dataSet = new QBarSet(tr("Number of computers"));
    QBarSeries *series = new QBarSeries();
    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);

    QStringList barTitles;

    std::sort(price.begin(), price.end());

    int barAmount = 1 + int(log2(price.size()));

    float step = (price[price.size() - 1] - price[0]) / barAmount;

    for (int i = 0,  j = 0; i < barAmount; i++)
    {
        int barData = 0;
        QString left = QString::number(price[0] + i * step);
        QString right = QString::number(price[0] + (i+1) * step);
        barTitles.append(left + " - " + right);

        while ((price[j] <= (price[0] + (i + 1) * step) && j < (int) price.size()))
        {
            barData +=1;
            j++;
        }

        *dataSet << barData;
    }

    series->append(dataSet);
    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(barTitles);

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->setTitle(tr("Number of computers depending on price"));

    this->setCentralWidget(chartView);
    this->resize(1000, 600);

}
