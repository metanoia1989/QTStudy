#include "searchcombobox.h"
#include <QLineEdit>

SearchComboBox::SearchComboBox(QWidget *parent) : QComboBox(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setEditable(true);

    // 添加过滤模型来匹配过滤项
    mFilterModel = new QSortFilterProxyModel(this);
    mFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mFilterModel->setSourceModel(model());

    // 添加 completer
    mCompleter = new QCompleter(mFilterModel, this);
    mCompleter->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    setCompleter(mCompleter);

    // 连接信号
    connect(lineEdit(), &QLineEdit::textEdited, mFilterModel,
        &QSortFilterProxyModel::setFilterFixedString);
    connect(this->completer(), static_cast<void(QCompleter::*)(const QString &)>(&QCompleter::activated),
            this, &SearchComboBox::on_completer_activated);
}

void SearchComboBox::setModel(QAbstractItemModel *model)
{
    QComboBox::setModel(model);
    mFilterModel->setSourceModel(model);
    mCompleter->setModel(mFilterModel);
}

void SearchComboBox::setModelColumn(int visibleColumn)
{
    mCompleter->setCompletionColumn(visibleColumn);
    mFilterModel->setFilterKeyColumn(visibleColumn);
    QComboBox::setModelColumn(visibleColumn);
}

void SearchComboBox::on_completer_activated(const QString &text)
{
    if (text.isEmpty()) {
        return;
    }
    int index = findText(text);
    setCurrentIndex(index);
    emit activated(index);
}
