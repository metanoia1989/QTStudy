#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QRegion>
#include <QMouseEvent>

class HistogramView : public QAbstractItemView
{
    Q_OBJECT
public:
    HistogramView(QWidget *parent=nullptr);
    // 虚函数声明 - QAbstractItemView 中的纯虚函数，必须声明
    QRect visualRect(const QModelIndex &index) const;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);
    QModelIndex indexAt(const QPoint &point) const;	// 鼠标点击视图，返回鼠标所在点的QModelIndex值
    // 为 selections 赋值
    void setSelectionModel(QItemSelectionModel *selectionModel);
    QRegion itemRegion(QModelIndex index);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);	// 柱状图可被鼠标点击，选中后以不同方式显示

protected slots:
    void selectionChanged(const QItemSelection &selected,
        const QItemSelection &deselected);    // 数据项选择发生变更时，此槽函数将响应
    void dataChanged(const QModelIndex &topLeft,
        const QModelIndex &bottomRight);		// 模型中的数据发生变更时，此槽函数将响应

protected:
    // 虚函数声明
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
        Qt::KeyboardModifiers modifiers);
    int horizontalOffset() const;
    int verticalOffset() const;
    bool isIndexHidden(const QModelIndex &index) const;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags);
    QRegion visualRegionForSelection(const QItemSelection &selection) const;

private:
    QItemSelectionModel *selections;
    QList<QRegion> MRegionList;		// 保存某一类柱状图的区域范围
    QList<QRegion> FRegionList;
    QList<QRegion> SRegionList;
};



#endif // HISTOGRAMVIEW_H
