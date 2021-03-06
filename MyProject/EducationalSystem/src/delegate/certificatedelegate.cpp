#include "certificatedelegate.h"
#include <QComboBox>
#include <QStandardItemModel>
#include <QPainter>


CertificateDelegate::CertificateDelegate(QObject *parent)
    : InhertStyleDelegate(parent)
{

}

QWidget *CertificateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem("未制作");
    editor->addItem("已制作");
    editor->addItem("未寄出");
    editor->addItem("已寄出");
    // 禁止选择已寄出
    auto model = qobject_cast<QStandardItemModel*>(editor->model());
    auto item = model->item(3);
    item->setEnabled(false);
    return editor;
}

void CertificateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    int itemIndex = comboBox->findText(text);
    comboBox->setCurrentIndex(itemIndex);
}

void CertificateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text, Qt::EditRole);
}

void CertificateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
