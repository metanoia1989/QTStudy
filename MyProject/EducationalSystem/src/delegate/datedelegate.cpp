#include "datedelegate.h"
#include <QDateEdit>
#include <QStandardItemModel>


DateDelegate::DateDelegate(QObject *parent)
    : InhertStyleDelegate(parent)
{

}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDateEdit *editor = new QDateEdit(parent);
    editor->setDate(QDate::currentDate());
    editor->setDisplayFormat("yyyy-MM-dd");
    editor->setCalendarPopup(true);
    return editor;
}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString dateStr= index.model()->data(index, Qt::EditRole).toString();
    QDate date = QDate::fromString(dateStr, Qt::ISODate);
    QDateEdit *dateEditor = static_cast<QDateEdit*>(editor);
    dateEditor->setDate(date);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDateEdit *dateEditor = static_cast<QDateEdit*>(editor);
    QDate date = dateEditor->date();
    model->setData(index, date.toString(Qt::ISODate), Qt::EditRole);
}

void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
