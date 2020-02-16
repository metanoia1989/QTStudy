#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    appPath = QCoreApplication::applicationDirPath(); // 没有 `/` 后缀
    player1 = new QSoundEffect;
    player1->setLoopCount(3);
}

Widget::~Widget()
{
    delete ui;
}

// 防守方播放声音
void Widget::defense(QString weapon)
{
    QUrl url = QUrl::fromLocalFile(appPath+"/sound/"+weapon);
    player1->setSource(url);
    player1->play();
}

// 进攻方播放声音
void Widget::attack(QString weapon)
{
    QString filename = appPath + "/sound/" + weapon;
    QSound::play(filename); // 异步播放
}

// 防守方 AK47
void Widget::on_pushButton_clicked()
{
    defense("Ak7.wav");
}

// 防守方 机枪
void Widget::on_pushButton_2_clicked()
{
    defense("machinegun.wav");
}

// 防守方 开枪
void Widget::on_pushButton_3_clicked()
{
    defense("fire.wav");
}

// 防守方 炮弹
void Widget::on_pushButton_4_clicked()
{
    defense("shell.wav");
}

// 防守方 爆炸
void Widget::on_pushButton_5_clicked()
{
    defense("blast.wav");
}

// 防守方 爆炸2
void Widget::on_pushButton_6_clicked()
{
    defense("blast2.wav");
}

// 进攻方 AK47
void Widget::on_pushButton_13_clicked()
{
    attack("Ak7.wav");
}

// 进攻方 机枪
void Widget::on_pushButton_14_clicked()
{
    attack("machinegun.wav");
}

// 进攻方 开枪
void Widget::on_pushButton_15_clicked()
{
    attack("fire2.wav");
}

// 进攻方 地雷
void Widget::on_pushButton_16_clicked()
{
    attack("mine.wav");
}

// 进攻方 爆炸
void Widget::on_pushButton_17_clicked()
{
    attack("blast.wav");
}

// 进攻方 坦克
void Widget::on_pushButton_18_clicked()
{
    attack("tank.wav");
}
