#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    // 状态栏上添加组件
    fLabCurFile = new QLabel;
    fLabCurFile->setMinimumWidth(150);
    fLabCurFile->setText("当前文件：");
    ui->statusBar->addWidget(fLabCurFile); // 添加到状态栏

    progressBar1 = new QProgressBar;
    progressBar1->setMinimumWidth(200);
    progressBar1->setMinimum(5);
    progressBar1->setMaximum(50);
    progressBar1->setValue(ui->txtEdit->font().pointSize());
    ui->statusBar->addWidget(progressBar1);

    // 工具栏上添加组件
    spinFontSize = new QSpinBox; // 文字大小
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->txtEdit->font().pointSize());
    spinFontSize->setMinimumWidth(50);
    ui->mainToolBar->addWidget(new QLabel("字体大小 "));
    ui->mainToolBar->addWidget(spinFontSize); // SpinBox 添加到工具栏

    ui->mainToolBar->addSeparator(); // 分隔条
    ui->mainToolBar->addWidget(new QLabel(" 字体 "));
    comboFont = new QFontComboBox;
    comboFont->setMinimumWidth(50);
    ui->mainToolBar->addWidget(comboFont);

    setCentralWidget(ui->txtEdit);
}

void MainWindow::on_actFontBold_triggred(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();
    if (checked) {
        fmt.setFontWeight((QFont::Normal));
    } else {
        fmt.setFontWeight(QFont::Normal);
    }
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actFontItalic_triggred(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->txtEdit->mergeCurrentCharFormat(fmt);

}

void MainWindow::on_actFontUnder_triggred(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_txtEdit_copyAvailable(bool b)
{
    // 更新 cut, copy, paste 的 enabled 属性
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->txtEdit->canPaste());
}

void MainWindow::on_txtEdit_selectionChanged()
{
    // 更新粗体、斜体和下划线三种action的checked属性
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();
    ui->actFontItalic->setChecked(fmt.fontItalic()); // 是否斜体
    ui->actFontBold->setChecked(fmt.font().bold());  // 是否粗体
    ui->actFontUnder->setChecked(fmt.fontUnderline());  // 是否有下划线
}
