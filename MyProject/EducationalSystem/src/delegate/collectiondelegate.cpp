#include "collectiondelegate.h"
#include <QComboBox>
#include <QStandardItemModel>


CollectionDelegate::CollectionDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

QWidget *CollectionDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem("未收齐");
    editor->addItem("已收齐");
    return editor;
}

void CollectionDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    int itemIndex = comboBox->findText(text);
    comboBox->setCurrentIndex(itemIndex);
}

void CollectionDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text, Qt::EditRole);
}

void CollectionDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
