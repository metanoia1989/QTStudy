#include "widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QFontMetrics>
#include <string>
#include "exec.hpp"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_curDir = new QLabel();
    m_inputCommnad = new QLineEdit();
    m_displayContent = new QPlainTextEdit();
    m_displayContent->setReadOnly(true);

    QHBoxLayout *hLayout = new QHBoxLayout();
    QLabel *indicator = new QLabel("$ ");
    hLayout->addWidget(indicator);
    hLayout->addWidget(m_inputCommnad);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_displayContent);
    mainLayout->addWidget(m_curDir);
    mainLayout->addLayout(hLayout);

    // 设置Label
    QString curPath = QCoreApplication::applicationDirPath();
    QFontMetrics metrics(m_curDir->font());
    QString elidedText = metrics.elidedText(curPath, Qt::ElideMiddle, width());
    m_curDir->setText(elidedText);
    m_curDir->setStyleSheet("color: blue");

    resize(400, 300);
    setWindowTitle("控制台");
    setLayout(mainLayout);

    // 输入框回车时执行命令
    connect(m_inputCommnad, &QLineEdit::returnPressed, this, &Widget::executeCommand);
}

Widget::~Widget()
{
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
    auto text = QString::fromStdString(result);
    displayOutput(text);
}

