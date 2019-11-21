#include "widget.h"
#include "ui_widget.h"

#include <QDateTime>
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    fTimer = new QTimer(this);  // 创建定时器
    fTimer->stop();
    fTimer->setInterval(1000);	// 设置定时周期，单位毫秒
    // 关联定时器的信号和槽
    connect(fTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
}

Widget::~Widget()
{
    delete ui;
}

// 获取当前时间，为三个专用编辑器设置日期时间数据，并转换为字符串在LineEdit里显示
void Widget::on_btnGetTime_clicked()
{
    QDateTime curDateTime = QDateTime::currentDateTime(); // 当前日期时间

    ui->timeEdit->setTime(curDateTime.time());	// 设置时间
    ui->editTime->setText(curDateTime.toString("hh:mm:ss"));	// 转换为字符串显示
    ui->dateEdit->setDate(curDateTime.date());	// 设置日期
    ui->editDate->setText(curDateTime.toString("yyyy-MM-dd"));
    ui->dateTimeEdit->setDateTime(curDateTime);	// 设置日期时间
    ui->editDateTime->setText(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}

// 设置日期时间，字符串转换为 QDateTime
void Widget::on_btnSetDateTime_clicked()
{
    QString str = ui->editDateTime->text();
    str = str.trimmed();	// 去掉空格
    if (!str.isEmpty()) {
        QDateTime datetime = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
        ui->dateTimeEdit->setDateTime(datetime);
    }
}

// 设置日期，字符串转换为 QDate
void Widget::on_btnSetDate_clicked()
{
    QString str = ui->editDate->text();
    str = str.trimmed();	// 去掉空格
    if (!str.isEmpty()) {
        QDate date = QDate::fromString(str, "yyyy-MM-dd");	// 字符串转为 QDate
        ui->dateEdit->setDate(date); // 设置日期
    }
}

// 设置时间，字符串转换为 QTime
void Widget::on_btnSetTime_clicked()
{
    QString str = ui->editTime->text(); // 读取字符串表示的时间
    str = str.trimmed();	// 去掉空格
    if (!str.isEmpty()) {
        QTime time = QTime::fromString(str, "hh:mm:ss");
        ui->timeEdit->setTime(time);
    }
}

// 在日历上选择日期
void Widget::on_calendarWidget_selectionChanged()
{
    QDate date = ui->calendarWidget->selectedDate();	// 读取选择的日期时间
    QString str = date.toString("yyyy年M月d日");
    ui->editCalendar->setText(str);
}

// 启动定时器
void Widget::on_btnStart_clicked()
{
    fTimer->start();	// 定时器开始工作
    fTimeCounter.start(); // 计时器开始工作
    // 更新各按键的状态
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->btnSetIntv->setEnabled(false);
}

// 关闭定时器
void Widget::on_btnStop_clicked()
{
    fTimer->stop();	// 定时器停止

    int tmMsec = fTimeCounter.elapsed(); // 毫秒数
    int ms = tmMsec % 1000; // 余数毫秒
    int sec = tmMsec / 1000; // 整秒

    QString str = QString::asprintf("流逝时间：%d 秒，%d 毫秒", sec, ms);
    ui->LabElapsTime->setText(str);	// 显示流逝的时间

    // 更新按键状态
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->btnSetIntv->setEnabled(true);
}

// 设置定时周期
void Widget::on_btnSetIntv_clicked()
{
    // 设置定时器的周期
    fTimer->setInterval(ui->spinBoxIntv->value());
}

// 定时器中断响应槽函数
void Widget::on_timer_timeout()
{
    QTime curTime = QTime::currentTime();	// 获取当前时间
    ui->LCDHour->display(curTime.hour()); // 显示小时
    ui->LCDMin->display(curTime.minute()); // 显示分钟
    ui->LCDSec->display(curTime.second()); // 显示秒

    int val = ui->progressBar->value();	// 读取 progressBar 的值
    val++;
    if (val > 100) {
        val = 0;
    }
    ui->progressBar->setValue(val);
}
