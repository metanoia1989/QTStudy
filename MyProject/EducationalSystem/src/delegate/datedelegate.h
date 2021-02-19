#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include "inhertstyledelegate.h"

class DateDelegate : public InhertStyleDelegate
{
    Q_OBJECT
public:
    explicit DateDelegate(QObject *parent = nullptr);
    // 创建编辑器
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    // 设置编辑器
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    // 更新模型数据
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    // 给编辑空间位置的大小
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DATEDELEGATE_H
