#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>

Drawer::Drawer(QWidget *parent, Qt::WindowFlags f) : QToolBox (parent, f)
{
    setWindowTitle("My QQ");
    toolBtn1_1 = new QToolButton;
    toolBtn1_1->setText(tr("张三"));
    toolBtn1_1->setIcon(QPixmap("11.png")); // 按钮图标
    toolBtn1_1->setIconSize(QPixmap("11.png").size());
    toolBtn1_1->setAutoRaise(true); // 鼠标离开时，按钮自动恢复弹起状态
    toolBtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); // 设置按钮的 ToolButtonStyle 属性

    toolBtn1_2 = new QToolButton;
    toolBtn1_2->setText(tr("李四"));
    toolBtn1_2->setIcon(QPixmap("12.png"));
    toolBtn1_2->setIconSize(QPixmap("12.png").size());
    toolBtn1_2->setAutoRaise(true);
    toolBtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_3 = new QToolButton;
    toolBtn1_3->setText(tr("王五"));
    toolBtn1_3->setIcon(QPixmap("13.png"));
    toolBtn1_3->setIconSize(QPixmap("13.png").size());
    toolBtn1_3->setAutoRaise(true);
    toolBtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_4 = new QToolButton;
    toolBtn1_4->setText(tr("小赵"));
    toolBtn1_4->setIcon(QPixmap("14.png"));
    toolBtn1_4->setIconSize(QPixmap("14.png").size());
    toolBtn1_4->setAutoRaise(true);
    toolBtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_5 = new QToolButton;
    toolBtn1_5->setText(tr("小孙"));
    toolBtn1_5->setIcon(QPixmap("155.png"));
    toolBtn1_5->setIconSize(QPixmap("155.png").size());
    toolBtn1_5->setAutoRaise(true);
    toolBtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    // 垂直布局
    QGroupBox *groupBox1 = new QGroupBox; // 抽屉组件
    QVBoxLayout *layout1 = new QVBoxLayout(groupBox1);
    layout1->setMargin(10);
    layout1->setAlignment(Qt::AlignHCenter);
    // 加入抽屉内的各个按钮
    layout1->addWidget(toolBtn1_1);
    layout1->addWidget(toolBtn1_2);
    layout1->addWidget(toolBtn1_3);
    layout1->addWidget(toolBtn1_4);
    layout1->addWidget(toolBtn1_5);
    // 插入一个占位符
    layout1->addStretch();


    toolBtn2_1 = new QToolButton;
    toolBtn2_1->setText(tr("小王"));
    toolBtn2_1->setIcon(QPixmap("21.png"));
    toolBtn2_1->setIconSize(QPixmap("21.png").size());
    toolBtn2_1->setAutoRaise(true);
    toolBtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn2_2 = new QToolButton;
    toolBtn2_2->setText(tr("小张"));
    toolBtn2_2->setIcon(QPixmap("22.png"));
    toolBtn2_2->setIconSize(QPixmap("22.png").size());
    toolBtn2_2->setAutoRaise(true);
    toolBtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox2 = new QGroupBox; // 抽屉组件
    QVBoxLayout *layout2 = new QVBoxLayout(groupBox2);
    layout2->setMargin(10);
    layout2->setAlignment(Qt::AlignHCenter);
    // 加入抽屉内的各个按钮
    layout2->addWidget(toolBtn2_1);
    layout2->addWidget(toolBtn2_2);

    toolBtn3_1 = new QToolButton;
    toolBtn3_1->setText(tr("小陈"));
    toolBtn3_1->setIcon(QPixmap("31.png"));
    toolBtn3_1->setIconSize(QPixmap("31.png").size());
    toolBtn3_1->setAutoRaise(true);
    toolBtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn3_2 = new QToolButton;
    toolBtn3_2->setText(tr("小李"));
    toolBtn3_2->setIcon(QPixmap("32.png"));
    toolBtn3_2->setIconSize(QPixmap("32.png").size());
    toolBtn3_2->setAutoRaise(true);
    toolBtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox3 = new QGroupBox; // 抽屉组件
    QVBoxLayout *layout3 = new QVBoxLayout(groupBox3);
    layout3->setMargin(10);
    layout3->setAlignment(Qt::AlignHCenter);
    // 加入抽屉内的各个按钮
    layout3->addWidget(toolBtn3_1);
    layout3->addWidget(toolBtn3_2);

    // 将准备好的抽屉插入 ToolBox 中
    this->addItem((QWidget*)groupBox1, tr("我的好友"));
    this->addItem((QWidget*)groupBox2, tr("陌上人"));
    this->addItem((QWidget*)groupBox3, tr("黑名单"));
}
