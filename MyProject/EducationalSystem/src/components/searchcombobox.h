#ifndef SEARCHCOMBOBOX_H
#define SEARCHCOMBOBOX_H

#include <QComboBox>
#include <QSortFilterProxyModel>
#include <QCompleter>

class SearchComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SearchComboBox(QWidget *parent = nullptr);
    void setModel(QAbstractItemModel *model);
    void setModelColumn(int visibleColumn);

public slots:
    void on_completer_activated(const QString &text);

private:
    QSortFilterProxyModel *mFilterModel;
    QCompleter *mCompleter;
};

#endif // SEARCHCOMBOBOX_H
