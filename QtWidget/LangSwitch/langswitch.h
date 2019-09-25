#ifndef LANGSWITCH_H
#define LANGSWITCH_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>

class LangSwitch : public QWidget
{
    Q_OBJECT

public:
    LangSwitch(QWidget *parent = nullptr);
    ~LangSwitch();

private slots:
    void changeLang(int index);	// 响应下拉菜单中语言项的改变

private:
    void createScreen();	// 协助创建界面和改变语言
    void changeTr(const QString& langCode);
    void refreshLabel();

    QComboBox *combo;	// 下拉菜单
    QLabel *label;	// 标签
};

#endif // LANGSWITCH_H
