#include "datedelegate.h"
#include <QDateTimeEdit>

DateDelegate::DateDelegate(QObject *parent):QItemDelegate (parent)
{

}


QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QDateTimeEdit *editor = new QDateTimeEdit(parent);	// 编辑时的输入控件
    editor->setDisplayFormat("yyyy-MM-dd");	// 日期显示格式
    editor->setCalendarPopup(true);	// 日历选择的显示以 Popup 方式及及下拉菜单方式
    editor->installEventFilter(const_cast<DateDelegate*>(this));
    return editor;
}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString dateStr = index.model()->data(index).toString();
    QDate date = QDate::fromString(dateStr, Qt::ISODate);
    QDateTimeEdit *edit = static_cast<QDateTimeEdit*>(editor); // 将 editor 转换为 QDateTimeEdit 对象，获得编辑控件的对象指针
    edit->setDate(date);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
    QDateTimeEdit *edit = static_cast<QDateTimeEdit*>(editor);
    QDate date = edit->date();
    model->setData(index, QVariant(date.toString(Qt::ISODate)));
}

void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
