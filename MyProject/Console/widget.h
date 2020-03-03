#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLabel>
#include <QLineEdit>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void updateCurDir(const QString& path); // 更新当前目录

private slots:
    void executeCommand();

private:
    QLabel *m_curDir;
    QLineEdit *m_inputCommnad;
    QPlainTextEdit *m_displayContent;
};
#endif // WIDGET_H
