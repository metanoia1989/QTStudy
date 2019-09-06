#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    boy = new QPerson("王小明");
    boy->setProperty("score", 95);
    boy->setProperty("age", 10);
    boy->setProperty("sex", "Boy"); // 动态属性
    connect(boy, &QPerson::ageChanged, this, &Widget::on_ageChanged);

    girl = new QPerson("张小丽");
    girl->setProperty("score", 81);
    girl->setProperty("age", 20);
    girl->setProperty("sex", "Girl");
    connect(girl, &QPerson::ageChanged, this, &Widget::on_ageChanged);

    ui->spinBoy->setProperty("isBoy", true);
    ui->spinGirl->setProperty("isBoy", false);
    connect(ui->spinBoy, SIGNAL(valueChagend(int)), this, SLOT(on_spin_valueChagned(int)));
    connect(ui->spinGirl, SIGNAL(valueChagend(int)), this, SLOT(on_spin_valueChagned(int)));
}

Widget::~Widget()
{
    delete ui;
}

// 槽函数 响应 QPerson 的 ageChanged() 信号
void Widget::on_ageChanged(int value)
{
    Q_UNUSED(value);
    QPerson *aPerson = qobject_cast<QPerson *>(sender()); // 类型投射
    QString hisName = aPerson->property("name").toString();
    QString hisSex = aPerson->property("sex").toString();
    int hisAge = aPerson->age(); 	// 通过接口函数获取年龄
//   	int hisAge = aPerson->property("age").toInt(); // 通过属性获得年龄
    auto text = hisName + ", " + hisSex + QString::asprintf(", 年龄=%d", hisAge);
    ui->textEdit->appendPlainText(text);
}

// 响应界面上 spinBox 的 valueChanged(int) 信号
void Widget::on_spin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(sender());
    if (spinBox->property("isBoy").toBool()) {
        boy->setAge(spinBox->value());
    } else {
        girl->setAge(spinBox->value());
    }
}
