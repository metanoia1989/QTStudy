#include "dialog.h"
#include "ui_dialog.h"
#include <QDir>
#include <QFileDialog>
#include <QColorDialog>
#include <QPalette>
#include <QFont>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

// 选择单个文件
void Dialog::on_btnOpen_clicked()
{
    // 获取系统当前目录
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";	 // 对话框标题
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    if (!aFileName.isEmpty()) {
        ui->plainTextEdit->appendPlainText(aFileName);
    }
}

// 选择多个文件
void Dialog::on_btnOpenMulti_clicked()
{
    // 获取系统当前目录
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择多个文件";	 // 对话框标题
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)";
    QStringList fileList = QFileDialog::getOpenFileNames(this, dlgTitle, curPath, filter);
    for (int i = 0; i < fileList.count(); i++) {
        ui->plainTextEdit->appendPlainText(fileList.at(i));
    }

}

// 选择文件夹
void Dialog::on_btnSelDir_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle = "选择一个目录";	 // 对话框标题
    QString selectedDir = QFileDialog::getExistingDirectory(this, dlgTitle,
                            curPath,  QFileDialog::ShowDirsOnly);

    if (!selectedDir.isEmpty()) {
        ui->plainTextEdit->appendPlainText(selectedDir);
    }

}

// 保存文件
void Dialog::on_btnSave_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle = "保存文件";	 // 对话框标题
    QString filter = "文本文件(*.txt);;h文件(*.h);;C++文件(.cpp);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if (!aFileName.isEmpty()) {
        ui->plainTextEdit->appendPlainText(aFileName);
    }
}

// 选择颜色
void Dialog::on_btnColor_clicked()
{
    QPalette pal = ui->plainTextEdit->palette();
    QColor iniColor = pal.color(QPalette::Text);	// 现有文字颜色
    QColor color = QColorDialog::getColor(iniColor, this, "选择颜色");
    if (color.isValid()) {
        pal.setColor(QPalette::Text, color);
        ui->plainTextEdit->setPalette(pal);
    }
}

// 选择字体
void Dialog::on_btnFont_clicked()
{
    QFont iniFont = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, iniFont);
    if (ok) {
        ui->plainTextEdit->setFont(font);
    }
}

// 输入字符串
void Dialog::on_btnInputString_clicked()
{
    QString dlgTitle = "输入文字对话框";
    QString txtLabel = "请输入文件名";
    QString defaultInput = "新建文件.txt";
    QLineEdit::EchoMode echoMode = QLineEdit::Normal; // 正常文字输入
//    QLineEdit::EchoMode echoMode = QLineEdit::Password; // 密码输入

    bool ok = false;
    QString text = QInputDialog::getText(this, dlgTitle,
                     txtLabel, echoMode, defaultInput, &ok);
    if (ok && !text.isEmpty()) {
        ui->plainTextEdit->appendPlainText(text);
    }
}

// 输入整数
void Dialog::on_btnInputInt_clicked()
{
    QString dlgTitle = "输入整数对话框";
    QString txtLabel = "请输入字体大小";
    int defaultValue = ui->plainTextEdit->font().pointSize();
    int minValue = 6, maxValue = 50, stepValue = 1; // 范围，步长

    bool ok = false;
    int inputValue = QInputDialog::getInt(this, dlgTitle, txtLabel,
                      defaultValue, minValue, maxValue, stepValue, &ok);
    if (ok) {
        QFont font = ui->plainTextEdit->font();
        font.setPointSize(inputValue);
        ui->plainTextEdit->setFont(font);
    }
}

// 输入浮点数
void Dialog::on_btnInputFloat_clicked()
{
    QString dlgTitle = "输入浮点数对话框";
    QString txtLabel = "输入一个浮点数";

    double defaultValue = 3.13;
    double minValue = 0, maxValue = 10000; // 范围
    int decimals = 2; // 小数点位数

    bool ok = false;
    double inputValue = QInputDialog::getDouble(this, dlgTitle, txtLabel,
                      defaultValue, minValue, maxValue, decimals, &ok);
    if (ok) {
        QString str = QString::asprintf("输入了一个浮点数：%.2f", inputValue);
        ui->plainTextEdit->appendPlainText(str);
    }
}

// 条目选择输入
void Dialog::on_btnInputItem_clicked()
{
    QStringList items;	// ComboBox列表的内容
    items << "优秀" << "良好" << "合格" << "不合格";

    QString dlgTitle = "条目选择对话框";
    QString txtLabel = "请选择级别";
    int curIndex = 0;	// 初始选择项
    bool editable = true; // ComboBox 可编辑
    bool ok = false;
    QString text = QInputDialog::getItem(this, dlgTitle, txtLabel,
                     items, curIndex, editable, &ok);
    if (ok && !text.isEmpty()) {
        ui->plainTextEdit->appendPlainText(text);
    }

}

void Dialog::on_btnMsgQuestion_clicked()
{
    QString dlgTitle = "Question消息框";
    QString strInfo = "文件已被修改，是否保存修改？";

    // 默认按钮
    QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton;
    QMessageBox::StandardButton result; // 返回选择的按钮
    result = QMessageBox::question(this, dlgTitle, strInfo,
               QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, defaultBtn);
    switch (result) {
    case QMessageBox::Yes:
        ui->plainTextEdit->appendPlainText("Question消息框：Yes被选择");
        break;
    case QMessageBox::No:
        ui->plainTextEdit->appendPlainText("Question消息框：No被选择");
        break;
    case QMessageBox::Cancel:
        ui->plainTextEdit->appendPlainText("Question消息框：Cancel被选择");
        break;
    default:
        ui->plainTextEdit->appendPlainText("Question消息框：没有选择");
        break;
    }
}

void Dialog::on_btnMsgInformation_clicked()
{
    QString dlgTitle = "information消息框";
    QString strInfo = "文件已经打开，字体大小已设置";
    QMessageBox::information(this, dlgTitle, strInfo,
        QMessageBox::Ok, QMessageBox::NoButton);
}

void Dialog::on_btnMsgWarning_clicked()
{
    QString dlgTitle = "warning 消息框";
    QString strInfo = "文件内容已被修改";
    QMessageBox::warning(this, dlgTitle, strInfo);
}

void Dialog::on_btnMsgCritical_clicked()
{
    QString dlgTitle = "critical 消息框";
    QString strInfo = "有不明程序访问网络";
    QMessageBox::critical(this, dlgTitle, strInfo);
}

void Dialog::on_btnMsgAbout_clicked()
{
    QString dlgTitle = "about 消息框";
    QString strInfo = "我开发的数据查看软件 V1.0 \n 保留所有版权";
    QMessageBox::about(this, dlgTitle, strInfo);
}

void Dialog::on_btnMsgAboutQt_clicked()
{
    QString dlgTitle = "aboutQt 消息框";
    QMessageBox::aboutQt(this, dlgTitle);
}

void Dialog::on_btnClearText_clicked()
{
    ui->plainTextEdit->clear();
}
