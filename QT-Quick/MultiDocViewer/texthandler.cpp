#include "texthandler.h"
#include <QtGui/QTextDocument>
#include <QtCore/QFileInfo>

TextHandler::TextHandler()
    : m_target(nullptr), m_doc(nullptr),
      m_cursorPosition(-1),
      m_selectionStart(0),
      m_selectionEnd(0)
{}

// 设置要显示文档的目标元素
void TextHandler::setTarget(QQuickItem *target)
{
    m_doc = nullptr;
    m_target = target;
    if (!m_target) {
        return;
    }
    QVariant doc = m_target->property("textDocument");
    if (doc.canConvert<QQuickTextDocument*>()) {
        QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument*>();
        if (qqdoc) {
            m_doc = qqdoc->textDocument();
        }
    }
    emit targetChanged();	// 发出目标元素改变信号
}

// 设置文件路径
void TextHandler::setFileUrl(const QUrl &arg)
{
    if (m_fileUrl != arg) {	// 若与原来路径不同，则赋值
        m_fileUrl = arg;
        QString fileName = QQmlFile::urlToLocalFileOrQrc(arg);
        if (QFile::exists(fileName)) {	// 若文件存在
            QFile file(fileName);
            if (file.open(QFile::ReadOnly)) {
                QByteArray data = file.readAll();
                QTextCodec *codec = QTextCodec::codecForName("GB2312");	// 以text格式编码
                setText(codec->toUnicode(data));	// 转换为 Unicode 字符

                if (m_doc){
                    m_doc->setModified(false);
                }
                // 若文件名为空，则取默认 untitled.txt 或为 文件名作标题
                if (fileName.isEmpty()) {
                    m_textTitle = QStringLiteral("untitled.text");
                } else {
                    m_textTitle = QFileInfo(fileName).fileName();
                }
                emit textChanged();	// 发出文本改变信号
                emit textTitleChanged();	// 发出文档标题改变信号
            }
        }
        emit fileUrlChanged();	// 发出文件路径改变信号
    }
}

// 返回 text 文档的标题
QString TextHandler::textTitle() const
{
    return m_textTitle;
}

// 设置文档标题
void TextHandler::setTextTitle(QString arg)
{
    if (m_textTitle != arg) {
        m_textTitle = arg;
        emit textTitleChanged();
    }
}

// 设置文本内容
void TextHandler::setText(const QString &arg)
{
    if (m_text != arg) {
        m_text = arg;
        emit textChanged();
    }
}

// 返回文件路径
QUrl TextHandler::fileUrl() const
{
    return m_fileUrl;
}

// 返回文本内容
QString TextHandler::text() const
{
    return m_text;
}
