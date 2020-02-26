#ifndef QWCOMBOBOXDELEGATE_H
#define QWCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>

class QWComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QWComboBoxDelegate(QObject *parent=nullptr);

    void setItems(QStringList items, bool isEdit); // 初始化设置列表内容，是否可编辑
    // 自定义代理组件必须继承以下4个函数
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

private:
    QStringList mItemList; // 选择列表
    bool mIsEdit; // 是否可编辑
};

#endif // QWCOMBOBOXDELEGATE_H
