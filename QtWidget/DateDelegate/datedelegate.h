#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QItemDelegate>

class DateDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    DateDelegate(QObject *parent=nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;	// 完成创建控件的工作
    void setEditorData(QWidget *editor, const QModelIndex &index) const;	// 设置控件显示的数据
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;	// 将 Delegate 中对数据的改变更新至Model中
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;	// 更新控件区的显示
};

#endif // DATEDELEGATE_H
