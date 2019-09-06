#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    // 声明属性
    // 不直接成员变量的形式
    Q_PROPERTY(QString nickName READ nickName WRITE setNickName NOTIFY nickNameChanged)
    // 直接标出成员变量的形式
    Q_PROPERTY(int count MEMBER m_count READ count WRITE setCount NOTIFY countChanged)
    // 标出成员变量，可以省略读写函数
    Q_PROPERTY(double value MEMBER m_value NOTIFY valueChanged)

    // nickName 读函数声明
    const QString& nickName();
    // count 读函数
    int count();

signals:
    // 三个属性数值变化时发信号
    void nickNameChanged(const QString& strNewName);
    void countChanged(int nNewCount);
    void valueChanged(double dblNewValue);

public slots:
    // 写函数通常可以作为槽函数，方便与其他信号关联，自动调整数值
    // nickName 写函数声明
    void setNickName(const QString& strNewName);
    // const 写函数声明
    void setCount(int nNewCount);
    // value 写代码由 moc自动声明，没有写函数

private:
    Ui::Widget *ui;
    // 三个私有变量，对应三个属性
    QString m_nickName;
    int m_count;
    double m_value;
};

#endif // WIDGET_H
