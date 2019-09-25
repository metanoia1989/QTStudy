#include "langswitch.h"
#include <QVBoxLayout>
#include <QTranslator>
#include <QApplication>

LangSwitch::LangSwitch(QWidget *parent)
    : QWidget(parent)
{
    createScreen();
}

LangSwitch::~LangSwitch()
{

}

// 创建基本的界面
void LangSwitch::createScreen()
{
    combo = new QComboBox;
    combo->addItem("English", "en");
    combo->addItem("Chinese", "zh");
    combo->addItem("Latin", "la");
    label = new QLabel;
    refreshLabel();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(combo, 1);
    layout->addWidget(label, 5);
    setLayout(layout);

    connect(combo, SIGNAL(currentIndexChanged(int)), this,
        SLOT(changeLang(int)));
}

void LangSwitch::refreshLabel()
{
    // 第一个参数翻译串时用到的ID，第二个参数为注释，找不到翻译将采用注释
    label->setText(tr("Text_HELLO_WORLD", "Hello, World"));
}

void LangSwitch::changeLang(int index)
{
    QString langCode = combo->itemData(index).toString();	// 从所选菜单中取得对应语言的值
    changeTr(langCode);	// 读取qm文件，并调用 installTranslator方法安装QTranslator对象
    refreshLabel();	// 刷新标签上的文字
}

void LangSwitch::changeTr(const QString &langCode)
{
    static QTranslator *translator;	// 静态对象方便移除和重新安装
    if (translator != nullptr) {
        qApp->removeTranslator(translator);
        delete translator;
        translator = nullptr;
    }
    translator = new QTranslator;
    QString qmFilename = "F:\\WORKSPACE\\QT\\QTStudy\\QtWidget\\LangSwitch\\lang_" + langCode;
    if (translator->load(qmFilename)) {
        qApp->installTranslator(translator);
    }
}
