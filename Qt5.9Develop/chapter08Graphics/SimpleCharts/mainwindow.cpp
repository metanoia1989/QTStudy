#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 创建图表
void MainWindow::createChart()
{
    QChartView *chartView = new QChartView(this);	// 创建ChartView
    QChart *chart = new QChart();	// 创建 Chart
    chart->setTitle("简单函数曲线");
    chartView->setChart(chart);	// Chart添加到ChartView
    this->setCentralWidget(chartView);

    // 创建曲线序列
    QLineSeries *series0 = new QLineSeries();
    QLineSeries *series1 = new QLineSeries();
    series0->setName("Sin曲线");
    series1->setName("Cos曲线");
    chart->addSeries(series0);	// 序列添加到图表
    chart->addSeries(series1);

    // 序列添加数值
    qreal t = 0, y1, y2, intv = 0.1;
    int cnt = 100;
    for (int i = 0; i < cnt; i++) {
        y1 = qSin(t);
        series0->append(t, y1);

        y2 = qSin(t+20);
        series1->append(t, y2);

        t+= intv;
    }

    // 创建坐标轴
    QValueAxis *axisX = new QValueAxis;	// x轴
    axisX->setRange(0, 10);	// 设置坐标轴范围
    axisX->setTitleText("time(secs)");	// 标题

    QValueAxis *axisY = new QValueAxis; // y轴
    axisY->setRange(-2, 2);
    axisY->setTitleText("value");

    chart->setAxisX(axisX, series0);	// 为序列设置坐标轴
    chart->setAxisY(axisY, series0);
    chart->setAxisX(axisX, series1);
    chart->setAxisY(axisY, series1);
}
