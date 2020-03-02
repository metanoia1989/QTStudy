#include "widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QFontMetrics>
#include "exec.hpp"
#include <string>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_curDir = new QLabel();
    m_inputCommnad = new QLineEdit();
    m_displayContent = new QPlainTextEdit();
    m_displayContent->setReadOnly(true);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(m_curDir);
    hLayout->addWidget(m_inputCommnad);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_displayContent);
    mainLayout->addLayout(hLayout);

    setLayout(mainLayout);

    initUI();

    // 输入框回车时执行命令
    connect(m_inputCommnad, &QLineEdit::returnPressed, this, &Widget::executeCommand);
}

Widget::~Widget()
{
}

// 初始化界面
void Widget::initUI()
{
    resize(400, 300);
    setWindowTitle("控制台");

    // 当前目录
    QString curPath = QCoreApplication::applicationDirPath();
    QFontMetrics metrics(m_curDir->font());
    QString elidedText = metrics.elidedText(curPath, Qt::ElideMiddle, width()/ 4);
    m_curDir->setText(elidedText);
    m_curDir->setStyleSheet("color: blue");
}

// 更新当前目录
void Widget::updateCurDir(const QString& path)
{
    QFontMetrics metrics(m_curDir->font());
    QString elidedText = metrics.elidedText(path, Qt::ElideMiddle, width()/ 4);
    m_curDir->setText(elidedText);
}

// 展示命令执行输出
void Widget::displayOutput(const QString& output)
{
    m_displayContent->appendPlainText(output);
}

// 执行用户输入的命令
void Widget::executeCommand()
{
    QString command = m_inputCommnad->text();
    m_inputCommnad->clear();
    std::string result = exec(command.toStdString().c_str());
    displayOutput(QString::fromStdString(result));
}

