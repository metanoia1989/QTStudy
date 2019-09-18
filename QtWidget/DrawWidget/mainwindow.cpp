#include "mainwindow.h"
#include <QToolBar>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    drawWidget = new DrawWidget;
    setCentralWidget(drawWidget);	// 将drawWidget设为主窗体的中心
    createToolBar();
    setMinimumSize(600, 400);
    ShowStyle();
    drawWidget->setWidth(widthSpinBox->value());	// 初始化线宽
    drawWidget->setColor(Qt::black);	// 初始化颜色
}

MainWindow::~MainWindow()
{

}

// 创建工具栏
void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tool");

    styleLabel = new QLabel(tr("线型风格："));	// 创建线型选择控件
    styleComboBox = new QComboBox;
    styleComboBox->addItem(tr("SolidLine"), static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem(tr("DashLine"), static_cast<int>(Qt::DashLine));
    styleComboBox->addItem(tr("DotLine"), static_cast<int>(Qt::DotLine));
    styleComboBox->addItem(tr("DashDotLine"), static_cast<int>(Qt::DashDotLine));
    styleComboBox->addItem(tr("DashDotDotLine"), static_cast<int>(Qt::DashDotDotLine));
    connect(styleComboBox, SIGNAL(activated(int)), this, SLOT(ShowStyle()));

    widthLabel = new QLabel(tr("线宽："));	// 创建线宽选择控件
    widthSpinBox = new QSpinBox;
    connect(widthSpinBox, SIGNAL(valueChanged(int)), drawWidget, SLOT(setWidth(int)));

    colorBtn = new QToolButton;	// 创建颜色选择控件
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::black);
    colorBtn->setIcon(QIcon(pixmap));
    connect(colorBtn, SIGNAL(clicked()), this, SLOT(ShowColor()));

    clearBtn = new QToolButton;
    clearBtn->setText(tr("清除"));
    connect(clearBtn, SIGNAL(clicked()), drawWidget, SLOT(clear()));

    toolBar->addWidget(styleLabel);
    toolBar->addWidget(styleComboBox);
    toolBar->addWidget(widthLabel);
    toolBar->addWidget(widthSpinBox);
    toolBar->addWidget(colorBtn);
    toolBar->addWidget(clearBtn);
}

// 改变线型参数，将当前线型选择控件中的线型参数传递给绘制区
void MainWindow::ShowStyle()
{
    drawWidget->setStyle(styleComboBox->itemData(
        styleComboBox->currentIndex(), Qt::UserRole).toInt());
}

// 设置画笔颜色，将用户在标准颜色对话框中选择的颜色值传递给绘制区
void MainWindow::ShowColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black), this);
    if (color.isValid()) {
        drawWidget->setColor(color);	// 将选择的颜色传递给绘制区
        QPixmap p(20, 20);
        p.fill(color);
        colorBtn->setIcon(QIcon(p));	// 更改颜色选择按钮上的颜色
    }
}
