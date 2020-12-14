#include "techmaterialdelegate.h"
#include <QComboBox>
#include <QStandardItemModel>


TechMaterialDelegate::TechMaterialDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

QWidget *TechMaterialDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem("否");
    editor->addItem("是");
    return editor;
}

void TechMaterialDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    int itemIndex = comboBox->findText(text);
    comboBox->setCurrentIndex(itemIndex);
}

void TechMaterialDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text, Qt::EditRole);
}

void TechMaterialDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
