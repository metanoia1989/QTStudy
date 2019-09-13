#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("UserInfo"));
    /* 左侧 */
    UserNameLabel = new QLabel(tr("用户名："));
    UserNameLineEdit = new QLineEdit;
    NameLabel = new QLabel(tr("姓名："));
    NameLineEdit = new QLineEdit;
    SexLabel = new QLabel(tr("性别："));
    SexComboBox = new QComboBox;
    SexComboBox->addItem(tr("女"));
    SexComboBox->addItem(tr("男"));
    DepartmentLabel = new QLabel(tr("部门："));
    DepartmentTextEdit = new QTextEdit;
    AgeLabel = new QLabel(tr("年龄"));
    AgeLineEdit = new QLineEdit;
    OtherLabel = new QLabel(tr("备注："));
    OtherLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken); // 设置控件风格
    LeftLayout = new QGridLayout; // 左侧布局，不是主布局管理器，不用指定父窗口
    // 向布局中加入更多控件
    LeftLayout->addWidget(UserNameLabel, 0, 0); // 用户名
    LeftLayout->addWidget(UserNameLineEdit, 0, 1);
    LeftLayout->addWidget(NameLabel, 1, 0); // 姓名
    LeftLayout->addWidget(NameLineEdit, 1, 1);
    LeftLayout->addWidget(SexLabel, 2, 0); // 性别
    LeftLayout->addWidget(SexComboBox, 2, 1);
    LeftLayout->addWidget(DepartmentLabel, 3, 0); // 部门
    LeftLayout->addWidget(DepartmentTextEdit, 3, 1);
    LeftLayout->addWidget(AgeLabel, 4, 0); // 年龄
    LeftLayout->addWidget(AgeLineEdit, 4, 1);
    LeftLayout->addWidget(OtherLabel, 5, 0, 1, 2); // 其他
    LeftLayout->setColumnStretch(0, 1); // 设定两列分别占用控件的比例 1:3
    LeftLayout->setColumnStretch(1, 3);

    /* 右侧 */
    HeadLabel = new QLabel(tr("头像：")); // 右上角部分
    HeadIconLabel = new QLabel;
    QPixmap icon("user.jpg");
    HeadIconLabel->setPixmap(icon);
    HeadIconLabel->resize(50, 50);
    UpdateHeadBtn = new QPushButton(tr("更新"));
    // 完成右上侧头像选择区的布局
    TopRightLayout = new QHBoxLayout;
    TopRightLayout->setSpacing(20);
    TopRightLayout->addWidget(HeadLabel);
    TopRightLayout->addWidget(HeadIconLabel);
    TopRightLayout->addWidget(UpdateHeadBtn);
    IntroductionLabel = new QLabel(tr("个人说明：")); // 右下角部分
    IntroductionTextEdit = new QTextEdit;
    // 完成右侧的布局
    RightLayout = new QVBoxLayout;
    RightLayout->setMargin(10);
    RightLayout->addLayout(TopRightLayout);
    RightLayout->addWidget(IntroductionLabel);
    RightLayout->addWidget(IntroductionTextEdit);

    /* 底部 */
    OkBtn = new QPushButton(tr("确定"));
    CancelBtn = new QPushButton(tr("取消"));
    // 完成下方两个按钮的布局
    BottomLayout = new QHBoxLayout();
    BottomLayout->addStretch(); // 在按钮之前插入一个占位符，使两个按钮能够靠右对齐
    BottomLayout->addWidget(OkBtn);
    BottomLayout->addWidget(CancelBtn);

    QGridLayout *mainLayout = new QGridLayout(this); // 实现主布局
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(LeftLayout, 0, 0);
    mainLayout->addLayout(RightLayout, 0, 1);
    mainLayout->addLayout(BottomLayout, 1, 0, 1, 2);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize); // 设定最优化显示，所有控件都按 sizeHint() 的大小显示
}

Dialog::~Dialog()
{
    delete ui;
}
