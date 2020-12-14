#include "paperphotodelegate.h"
#include <QComboBox>
#include <QStandardItemModel>


PaperPhotoDelegate::PaperPhotoDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

QWidget *PaperPhotoDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem("未收齐");
    editor->addItem("已收齐");
    editor->addItem("提前提交");
    return editor;
}

void PaperPhotoDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    int itemIndex = comboBox->findText(text);
    comboBox->setCurrentIndex(itemIndex);
}

void PaperPhotoDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text, Qt::EditRole);
}

void PaperPhotoDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
