#include "widget.h"
#include "exec.hpp"
#include <string>
#include <stdexcept>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QFontMetrics>
#include <QRegularExpression>
#include <QDir>
#include <QTextCodec>
#include <QDebug>

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
    QDir dir(path);
    if (dir.exists()) {
        if(QDir::setCurrent(dir.absolutePath())) {
            m_curDir->setText(dir.absolutePath());
        }
    }
    QFontMetrics metrics(m_curDir->font());
    QString elidedText = metrics.elidedText(path, Qt::ElideMiddle, width()/ 4);
    m_curDir->setText(elidedText);
}

// 执行用户输入的命令
void Widget::executeCommand()
{
    QString command = m_inputCommnad->text();
    m_inputCommnad->clear();

    // 添加当前目录和执行的命令
    QString content= QString("<p style='color: #4eb236'>%1</p>").arg(m_curDir->text());
    content = content + QString("<p style='color: blue'>$ %1</p>").arg(command);

    // 检测是否是cd命令
    QRegularExpression regex(R"(^( *)?cd (.*)$)");
    regex.setPatternOptions(QRegularExpression::DotMatchesEverythingOption);
    auto match = regex.match(command);
    if (match.hasMatch()) {
        QString path = match.captured(2);
        updateCurDir(path);
    }

    try {
        std::string result = exec(command.toStdString().c_str());
        std::cout << result;
        if (!result.empty()) {
            auto text = QString::fromStdString(result);
            content = content + QString("<div>%1</div>").arg(text).replace("\n", "<br>");
        }
    } catch (const std::exception& e) {
        content = content + "\n" + e.what();
    }

    // 检测是否没有新增内容，没有则是命令执行失败，手动换行
    if (content.endsWith("</p>"))
        content += "<div></div>";
    qDebug() << content;

    m_displayContent->appendHtml(content);
}

