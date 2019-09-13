#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // 文件对话框
    fileBtn = new QPushButton;
    fileBtn->setText(tr("文件标准对话框实例"));
    fileLineEdit = new QLineEdit; // 用来显示选择的文件名

    // 颜色对话框
    colorBtn = new QPushButton;
    colorBtn->setText(tr("颜色标准对话框实例"));
    colorFrame = new QFrame; // 根据用户选择的不同颜色更新不同的背景
    colorFrame->setFrameShape(QFrame::Box);
    colorFrame->setAutoFillBackground(true);

    // 字体对话框
    fontBtn = new QPushButton;
    fontBtn->setText(tr("字体标准对话框实例"));
    fontLineEdit = new QLineEdit;
    fontLineEdit->setText(tr("Welcome"));

    // 标准输入框
    inputBtn = new QPushButton;
    inputBtn->setText(tr("标准输入对话框实例"));

    // 消息对话框类
    MsgBtn = new QPushButton;
    MsgBtn->setText(tr("标准消息对话框实例"));

    // 自定义消息框
    CustomBtn = new QPushButton;
    CustomBtn->setText(tr("用户自定义消息对话框实例"));
    label = new QLabel;
    label->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    // 布局设计
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(fileBtn, 0, 0);
    mainLayout->addWidget(fileLineEdit, 0, 1);
    mainLayout->addWidget(colorBtn, 1, 0);
    mainLayout->addWidget(colorFrame, 1, 1);
    mainLayout->addWidget(fontBtn, 2, 0);
    mainLayout->addWidget(fontLineEdit, 2, 1);
    mainLayout->addWidget(inputBtn, 3, 0);
    mainLayout->addWidget(MsgBtn, 3, 1);
    mainLayout->addWidget(CustomBtn, 4, 0);
    mainLayout->addWidget(label, 4, 1);
    connect(fileBtn, SIGNAL(clicked()), this, SLOT(showFile())); // 事件关联
    connect(colorBtn, SIGNAL(clicked()), this, SLOT(showColor())); // 事件关联
    connect(fontBtn, SIGNAL(clicked()), this, SLOT(showFont())); // 事件关联
    connect(inputBtn, SIGNAL(clicked()), this, SLOT(showInputDlg())); // 事件关联
    connect(MsgBtn, SIGNAL(clicked()), this, SLOT(showMsgDlg())); // 事件关联
    connect(CustomBtn, SIGNAL(clicked()), this, SLOT(showCustomDlg())); // 事件关联
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showFile()
{
    QString s = QFileDialog::getOpenFileName(this, "打开文件对话框", "/", "C++ files(*.cpp);;C files(*.c);;Head files(*.h)");
    fileLineEdit->setText(s);
}


void Dialog::showColor()
{
    QColor c = QColorDialog::getColor(Qt::blue);
    if (c.isValid()) {
        colorFrame->setPalette(QPalette(c));
    }
}

void Dialog::showFont()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok);
    if (ok) {
        fontLineEdit->setFont(f);
    }
}


void Dialog::showInputDlg()
{
    inputDlg = new InputDlg(this);
    inputDlg->show();
}

void Dialog::showMsgDlg()
{
    msgDlg = new MsgBoxDlg(this);
    msgDlg->show();
}

void Dialog::showCustomDlg()
{
    label->setText(tr("Custom Message box"));
    QMessageBox customMsgBox;
    customMsgBox.setWindowTitle(tr("用户自定义消息框"));
    QPushButton *yesBtn = customMsgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
    QPushButton *noBtn = customMsgBox.addButton(tr("No"), QMessageBox::ActionRole);
    QPushButton *cancelBtn = customMsgBox.addButton(QMessageBox::Cancel);
    customMsgBox.setText(tr("这是一个用户自定义消息框"));
    customMsgBox.setIconPixmap(QPixmap("Qt.png"));
    customMsgBox.exec();
    if (customMsgBox.clickedButton() == yesBtn) {
        label->setText("Custom Message Box/Yes");
    } else if (customMsgBox.clickedButton() == noBtn) {
        label->setText("Custom Message Box/No");
    } else if (customMsgBox.clickedButton() == cancelBtn) {
        label->setText("Custom Message Box/Cancel");
    }
    return;
}
