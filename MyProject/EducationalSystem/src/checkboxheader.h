#ifndef CHECKBOXHEADER_H
#define CHECKBOXHEADER_H

#include <QHeaderView>

class CheckboxHeader : public QHeaderView
{
    Q_OBJECT
public:
    explicit CheckboxHeader(Qt::Orientation orientation, QWidget *parent=nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintSection(QPainter *painter, const QRect& rect, int logicalIndex) const override;

public slots:
    void updateCheckState(QStyle::StateFlag state); // 改变复选框的状态

signals:
    void selectAllClicked(QStyle::StateFlag state); // 复选框全选信号

private:
    // 控制列头复选框样式、位置以及大小
    int m_x_offset = 0;
    int m_y_offset = 0;
    int m_width = 20;
    int m_height = 20;

    QStyle::StateFlag m_state = QStyle::State_Off;
};

#endif // CHECKBOXHEADER_H
