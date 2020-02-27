#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iniGraph3D(); // 创建图表
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(ui->groupBox); // 左侧控制面板
    splitter->addWidget(graphContainer); // 右侧图表
    setCentralWidget(splitter); // 设置主窗口中心组件
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniGraph3D()
{
    graph3D = new Q3DBars();
    graphContainer = QWidget::createWindowContainer(graph3D); // Q3DBars继承自QWindow
    graph3D->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFrontHigh); // 设置视角

    // 创建坐标轴
    QStringList rowLabs;
    QStringList colLabs;
    rowLabs << "row1" << "row2" << "row3";
    colLabs << "col1" << "col2" << "col3" << "col4" << "col5";

    QValue3DAxis *axisV = new QValue3DAxis; // 数值坐标
    axisV->setTitle("value");
    axisV->setTitleVisible(true);

    QCategory3DAxis *axisRow = new QCategory3DAxis;
    axisRow->setTitle("row axis");
    axisRow->setLabels(rowLabs);
    axisRow->setTitleVisible(true);

    QCategory3DAxis *axisCol = new QCategory3DAxis;
    axisCol->setTitle("column axis");
    axisCol->setLabels(colLabs);
    axisCol->setTitleVisible(true);

    graph3D->setValueAxis(axisV);
    graph3D->setRowAxis(axisRow);
    graph3D->setColumnAxis(axisCol);

    // 创建序列
    series = new QBar3DSeries;
    series->setMesh(QAbstract3DSeries::MeshCylinder); // MeshBar,MeshPyramid,MeshCylinder
    series->setItemLabelFormat("(@rowLabel,@colLabel): %.1f"); // 项的标签显示格式
    graph3D->addSeries(series);

    QBarDataArray *dataSet = new QBarDataArray; // 数据代理
    dataSet->reserve(rowLabs.count());

    QBarDataRow *dataRow = new QBarDataRow;
    *dataRow << 1 << 2 << 3 << 4 << 5; // 第1行数据，有5列
    dataSet->append(dataRow);

    QBarDataRow *dataRow2 = new QBarDataRow;
    *dataRow2 << 5 << 5 << 5 << 5 << 5; // 第2行数据，有5列
    dataSet->append(dataRow2);

    QBarDataRow *dataRow3 = new QBarDataRow;
    *dataRow3 << 1 << 5 << 9 << 5 << 1; // 第3行数据，有5列
    dataSet->append(dataRow3);

    series->dataProxy()->resetArray(dataSet);
}

// 变换视角
void MainWindow::on_comboCamera_currentIndexChanged(int index)
{
    Q3DCamera::CameraPreset cameraPos = Q3DCamera::CameraPreset(index);
    graph3D->scene()->activeCamera()->setCameraPreset(cameraPos);
}

// 水平旋转
void MainWindow::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot = ui->sliderH->value(); // 水平
    int yRot = ui->sliderV->value(); // 垂直
    int zoom = ui->sliderZoom->value(); // 缩放
    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot, zoom);
}


// 垂直旋转
void MainWindow::on_sliderV_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}

// 缩放
void MainWindow::on_sliderZoom_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}

// 设置主题
void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    Q3DTheme *currentTheme = graph3D->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(index));
}

// 棒图样式
void MainWindow::on_cBoxBarStyle_currentIndexChanged(int index)
{
    QAbstract3DSeries::Mesh aMesh;
    aMesh = QAbstract3DSeries::Mesh(index + 1);
    series->setMesh(aMesh);
}

// 选择模式
void MainWindow::on_cBoxSelectionMode_currentIndexChanged(int index)
{
    graph3D->setSelectionMode(QAbstract3DGraph::SelectionFlags(index));
}

// 轴标签字体大小
void MainWindow::on_spinFontSize_valueChanged(int arg1)
{
    QFont font = graph3D->activeTheme()->font();
    font.setPointSize(arg1);
    graph3D->activeTheme()->setFont(font);
}

// 设置序列柱状图的颜色
void MainWindow::on_btnBarColor_clicked()
{
    QColor color = series->baseColor();
    color = QColorDialog::getColor(color);
    if (color.isValid()) {
        series->setBaseColor(color);
    }
}

// 图表的背景
void MainWindow::on_chkBoxBackground_clicked(bool checked)
{
    graph3D->activeTheme()->setBackgroundEnabled(checked);
}

// 图标的背景网格
void MainWindow::on_chkBoxGrid_clicked(bool checked)
{
    graph3D->activeTheme()->setGridEnabled(checked);
}

// 柱状图的光滑性
void MainWindow::on_chkBoxSmooth_clicked(bool checked)
{
    series->setMeshSmooth(checked);
}

// 倒影、反射
void MainWindow::on_chkBoxReflection_clicked(bool checked)
{
    graph3D->setReflection(checked);
}

// 数值坐标轴Z轴 反向
void MainWindow::on_chkBoxReverse_clicked(bool checked)
{
    graph3D->valueAxis()->setReversed(checked);
}

// 项的标签可见
void MainWindow::on_chkBoxItemLabel_clicked(bool checked)
{
    series->setItemLabelFormat("value at (@rowLabel,@colLabel): %.1f");
    series->setItemLabelVisible(checked);
}

// 坐标轴标题
void MainWindow::on_chkBoxAxisTitle_clicked(bool checked)
{
    graph3D->valueAxis()->setTitleVisible(checked);
    graph3D->rowAxis()->setTitleVisible(checked);
    graph3D->columnAxis()->setTitleVisible(checked);
}

// 坐标轴标题背景
void MainWindow::on_chkBoxAxisBackground_clicked(bool checked)
{
    graph3D->activeTheme()->setLabelBackgroundEnabled(checked);
}
