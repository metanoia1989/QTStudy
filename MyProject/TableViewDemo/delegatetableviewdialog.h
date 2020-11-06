#ifndef DELEGATETABLEVIEWDIALOG_H
#define DELEGATETABLEVIEWDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>

class MyDelegate;

QT_BEGIN_NAMESPACE
namespace Ui { class DelegateTableViewDialog; }
QT_END_NAMESPACE

class DelegateTableViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelegateTableViewDialog(QWidget *parent = nullptr);
    ~DelegateTableViewDialog();

private:
    Ui::DelegateTableViewDialog *ui;

    QStandardItemModel *model;
    MyDelegate *myDelegate;
};
#endif // DELEGATETABLEVIEWDIALOG_H
