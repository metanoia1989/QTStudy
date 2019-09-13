#include "palette.h"
#include <QHBoxLayout>
#include <QGridLayout>

Palette::Palette(QWidget *parent)
    : QDialog(parent)
{
    createCtrlFrame();
    createContentFrame();
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(ctrlFrame);
    mainLayout->addWidget(contentFrame);
}

Palette::~Palette()
{

}

// 创建颜色选择区
void Palette::createCtrlFrame()
{
    ctrlFrame = new QFrame; // 颜色选择面板
    windowLabel = new QLabel(tr("QPalette::Window: "));
    windowComboBox = new QComboBox;
    fillColorList(windowComboBox); //向下拉列表框中插入各种不同的颜色
    connect(windowComboBox, SIGNAL(activated(int)), this, SLOT(ShowWindow()));

    windowTextLabel = new QLabel(tr("QPalette:WindowText: "));
    windowTextComboBox = new QComboBox;
    fillColorList(windowTextComboBox);
    connect(windowTextComboBox, SIGNAL(activated(int)), this, SLOT(ShowWindowText()));

    buttonLabel = new QLabel(tr("QPalette::Button: "));
    buttonComboBox = new QComboBox;
    fillColorList(buttonComboBox);
    connect(buttonComboBox, SIGNAL(activated(int)), this, SLOT(ShowButton()));

    buttonTextLabel = new QLabel(tr("QPalette::ButtonText："));
    buttonTextComboBox = new QComboBox;
    fillColorList(buttonTextComboBox);
    connect(buttonTextComboBox, SIGNAL(activated(int)), this, SLOT(ShowButtonText()));

    baseLabel = new QLabel(tr("QPalette::Base："));
    baseComboBox = new QComboBox;
    fillColorList(baseComboBox);
    connect(baseComboBox, SIGNAL(activated(int)), this, SLOT(ShowBase()));

    QGridLayout *mainLayout = new QGridLayout(ctrlFrame);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(windowLabel, 0, 0);
    mainLayout->addWidget(windowComboBox, 0, 1);
    mainLayout->addWidget(windowTextLabel, 1, 0);
    mainLayout->addWidget(windowTextComboBox, 1, 1);
    mainLayout->addWidget(buttonLabel, 2, 0);
    mainLayout->addWidget(buttonComboBox, 2, 1);
    mainLayout->addWidget(buttonTextLabel, 3, 0);
    mainLayout->addWidget(buttonTextComboBox, 3, 1);
    mainLayout->addWidget(baseLabel, 4, 0);
    mainLayout->addWidget(baseComboBox, 4, 1);
}

// 显示选择的颜色对窗体外观的改变
void Palette::createContentFrame()
{
    contentFrame = new QFrame;
    label1 = new QLabel(tr("请选择一个值："));
    comboBox1 = new QComboBox;
    label2 = new QLabel(tr("请输入字符串："));
    lineEdit2 = new QLineEdit;
    textEdit = new QTextEdit;
    QGridLayout *TopLayout = new QGridLayout;
    TopLayout->addWidget(label1, 0, 0);
    TopLayout->addWidget(comboBox1, 0, 1);
    TopLayout->addWidget(label2, 1, 0);
    TopLayout->addWidget(lineEdit2, 1, 1);
    TopLayout->addWidget(textEdit, 2, 0, 1, 2);
    OkBtn = new QPushButton(tr("确定"));
    CancelBtn = new QPushButton(tr("取消"));
    QHBoxLayout *BottomLayout = new QHBoxLayout;
    BottomLayout->addStretch(1);
    BottomLayout->addWidget(OkBtn);
    BottomLayout->addWidget(CancelBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(contentFrame);
    mainLayout->addLayout(TopLayout);
    mainLayout->addLayout(BottomLayout);
}

// 响应对背景颜色的选择
void Palette::ShowWindow()
{
    // 获得当前选择的颜色值
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[windowComboBox->currentIndex()]);
    QPalette p = contentFrame->palette(); // 获得 contentFrame 的调色板信息
    p.setColor(QPalette::Window, color); // 设置窗体的 Window 类颜色 即背景色
    contentFrame->setPalette(p);
    contentFrame->update();
}

// 响应对文字颜色的选择
void Palette::ShowWindowText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[windowTextComboBox->currentIndex()];
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::WindowText, color);
    contentFrame->setPalette(p);
}

// 响应对按钮背景色的选择
void Palette::ShowButton()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Button, color);
    contentFrame->setPalette(p);
    contentFrame->update();
}

// 响应对按钮上文字颜色的选择
void Palette::ShowButtonText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonTextComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::ButtonText, color);
    contentFrame->setPalette(p);
}


// 响应对输入框背景色的选择
void Palette::ShowBase()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[baseComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Base, color);
    contentFrame->setPalette(p);
}

// 插入颜色
void Palette::fillColorList(QComboBox *comboBox)
{
    QStringList colorList = QColor::colorNames();
    QString color;
    foreach(color, colorList) { // 对颜色名列表进行遍历
        QPixmap pix(QSize(70, 20));
        pix.fill(QColor(color)); // 为 pix 填充当前遍历的颜色
        comboBox->addItem(QIcon(pix), nullptr);
        comboBox->setIconSize(QSize(70, 20));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}
