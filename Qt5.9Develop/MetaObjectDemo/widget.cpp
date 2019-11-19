#include "widget.h"
#include "ui_widget.h"
#include <QMetaProperty>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置动态属性
    boy = new QPerson("王小明");
    boy->setProperty("score", 95);
    boy->setProperty("age", 10);
    boy->setProperty("sex", "Boy");
    connect(boy, SIGNAL(ageChanged(int)), this, SLOT(on_ageChanged(int)));

    girl = new QPerson("张小丽");
    boy->setProperty("score", 81);
    boy->setProperty("age", 20);
    boy->setProperty("sex", "Girl");
    connect(girl, SIGNAL(ageChanged(int)), this, SLOT(on_ageChanged(int)));

    ui->spinBoy->setProperty("isBoy", true); // 动态属性
    ui->spinGirl->setProperty("isBoy", false); // 动态属性
    connect(ui->spinBoy, SIGNAL(valueChanged(int)), this, SLOT(on_spin_valueChanged(int)));
    connect(ui->spinGirl, SIGNAL(valueChanged(int)), this, SLOT(on_spin_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

// 清空文本框按钮
void Widget::on_btnClear_clicked()
{
    ui->textEdit->clear();
}

// boy 长大一岁按钮
void Widget::on_btnBoyInc_clicked()
{
    boy->incAge();
}

// birl 长大一岁按钮
void Widget::on_btnGirlInc_clicked()
{
    girl->incAge();
}

// 类的元对象信息按钮
void Widget::on_btnClassInfo_clicked()
{
    const QMetaObject *meta = boy->metaObject();
    ui->textEdit->clear();
    ui->textEdit->appendPlainText("==元对象信息==\n");
    ui->textEdit->appendPlainText(QString("类名称：%1\n")
        .arg(meta->className()));
    ui->textEdit->appendPlainText("property");
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++)
    {
        QMetaProperty prop = meta->property(i);
        const char* propName = prop.name();
        QString propValue = boy->property(propName).toString();
        ui->textEdit->appendPlainText(QString("属性名称=%1，属性值%2")
            .arg(propName).arg(propValue));
    }

    ui->textEdit->appendPlainText("");
    ui->textEdit->appendPlainText("classInfo");
    for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); i++)
    {
        QMetaClassInfo classInfo = meta->classInfo(i);
        ui->textEdit->appendPlainText(QString("Name=%1；Value=%2")
            .arg(classInfo.name()).arg(classInfo.value()));
    }
}

// 自定义槽函数
// 响应 QPerson 的 ageChanged() 信号
void Widget::on_ageChanged(int value)
{
    Q_UNUSED(value);
    // 类型投射 获取发射信号的对象
    QPerson *aPerson = qobject_cast<QPerson*>(sender());
    QString hisName = aPerson->property("name").toString(); // 姓名
    QString hisSex = aPerson->property("sex").toString(); // 动态属性
    int hisAge = aPerson->age();	// 通过接口函数获取年龄
//    int hisAge2 = aPerson->property("age").toInt();	// 通过属性获取年龄
    ui->textEdit->appendPlainText(hisName + "," + hisSex +
        QString::asprintf("，年龄=%d ", hisAge));
}

// 响应界面上 spinBox 的 valueChanged(int) 信号
// 不建议使用下面的名称格式，因为会触发 Qt 信号槽的自动连接机制
void Widget::on_spin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    qDebug() << "触发了 valueChanged 信号，响应槽函数";
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if (spinBox->property("isBoy").toBool()) {
        boy->setAge(spinBox->value());
    } else {
        girl->setAge(spinBox->value());
    }
}
