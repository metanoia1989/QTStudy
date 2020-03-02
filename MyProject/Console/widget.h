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
    void initUI();	// 初始化界面
    void updateCurDir(const QString& path); // 更新当前目录
    void displayOutput(const QString& output); // 展示命令执行输出

private slots:
    void executeCommand();

private:
    QLabel *m_curDir;
    QLineEdit *m_inputCommnad;
    QPlainTextEdit *m_displayContent;
};
#endif // WIDGET_H
