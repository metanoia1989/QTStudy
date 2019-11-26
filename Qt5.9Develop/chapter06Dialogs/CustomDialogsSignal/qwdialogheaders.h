#ifndef QWDIALOGHEADERS_H
#define QWDIALOGHEADERS_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class QWDialogHeaders;
}

class QWDialogHeaders : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogHeaders(QWidget *parent = nullptr);
    ~QWDialogHeaders();

    void setHeaderList(QStringList& headers);
    QStringList headerList();

private:
    QStringListModel *model;

    Ui::QWDialogHeaders *ui;
};

#endif // QWDIALOGHEADERS_H
