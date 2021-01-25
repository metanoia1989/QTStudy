#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    settings.setDefaultFormat(QSettings::NativeFormat);

    QString executePath = settings.value("executePath").toString();
    int executeNum = settings.value("executeNum").toInt();
    ui->edit_execute_path->setText(executePath);
    ui->spin_execute_num->setValue(executeNum);
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_pushButton_clicked()
{
    QString executePath = QFileDialog::getOpenFileName();
    if (!executePath.isEmpty()) {
        ui->edit_execute_path->setText(executePath);
        settings.setValue("executePath", executePath);
    }
}

void Widget::on_btn_start_clicked()
{
    ui->btn_start->setEnabled(false);
    QString executePath = ui->edit_execute_path->text();
    int executeNum = ui->spin_execute_num->text().toInt();
    if (executePath.isEmpty()) {
        return showError("必须选择微信路径");
    }
    if (executeNum <= 0) {
        return showError("必须选择开启数量");
    }

    QProcess close;

    close.execute(QString("taskkill /im WeChat.exe /f"));
    close.close();
    for (int i = 0; i < executeNum; i++) {
        QProcess process;
        process.startDetached(executePath, QStringList(executePath));
    }
    ui->btn_start->setEnabled(true);
}

/**
 * @brief 展示错误信息
 * @param msg
 */
void Widget::showError(const QString& msg)
{
    auto msgBox = new QMessageBox(this);
    msgBox->setWindowTitle(tr("请求出错"));
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->setText(msg);
    msgBox->exec();
    ui->btn_start->setEnabled(true);
}

void Widget::on_spin_execute_num_valueChanged(int arg1)
{
    settings.setValue("executeNum", arg1);
}
