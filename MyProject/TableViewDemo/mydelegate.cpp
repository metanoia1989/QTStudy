#include "mydelegate.h"

MyDelegate::MyDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(100);
    return editor;
}

/**
 * 设置编辑器，然后从模型获取数据，输入编辑器
 *
 * @brief MyDelegate::setEditorData
 * @param editor
 * @param index
 */
void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor);
    spinbox->setValue(value);
}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinbox = qobject_cast<QSpinBox*>(editor);
    spinbox->interpretText();
    int value = spinbox->value();
    model->setData(index, value, Qt::EditRole);
}

/**
 * 设置编辑器的位置和大小
 *
 * @brief MyDelegate::updateEditorGeometry
 * @param editor
 * @param option
 * @param index
 */
void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(editor);
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
