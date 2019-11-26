#ifndef QFORMDOC_H
#define QFORMDOC_H

#include <QWidget>

namespace Ui {
class QFormDoc;
}

class QFormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit QFormDoc(QWidget *parent = nullptr);
    ~QFormDoc();

    void loadFromFile(QString &aFileName);

private slots:
    void on_actOpen_triggered();

    void on_actFont_triggered();

private:
    QString mCurrentFile;	// 当前文件

    Ui::QFormDoc *ui;
};

#endif // QFORMDOC_H
