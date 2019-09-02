#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H
#include <QQuickTextDocument>
#include <QtCore/QTextCodec>
#include <qqmlfile.h>

class QTextDocument;
class TextHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString textTitle READ textTitle WRITE setTextTitle NOTIFY textTitleChanged)

public:
    TextHandler();
    QQuickItem *target() { return m_target; }
    void setTarget(QQuickItem *target);	// 设置要显示文档的目标元素
    QUrl fileUrl() const;	// 文件路径
    QString text() const;	// 文本内容
    QString textTitle() const;	// 文档标题

public Q_SLOTS:
    void setFileUrl(const QUrl &arg);	// 设置文件路径
    void setText(const QString &arg);	// 设置文本内容
    void setTextTitle(QString arg);	// 设置文档标题

Q_SIGNALS:
    void targetChanged();	// 目标元素改变信号
    void fileUrlChanged();	// 文件路径改变信号
    void textChanged();	// 文本内容改变信号
    void textTitleChanged();	// 文档标题改变信号

private:
    QQuickItem	*m_target;	// 指向目标元素的指针
    QTextDocument	*m_doc;		// 指向文档的指针

    int m_cursorPosition;	// 光标位置
    int m_selectionStart;	// 选中文本段的起始点
    int m_selectionEnd;		// 选中文本段的终点

    QFont	m_font;
    QUrl	m_fileUrl;
    QString		m_text;
    QString		m_textTitle;
};


#endif // TEXTHANDLER_H
