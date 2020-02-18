#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);

private slots:
    void itemClicked(QListWidgetItem* item);
    void updateItem();

private:
    QListWidget *mWidget;
    QLineEdit *mEdit;
    QPushButton *mButton;
};

#endif // CUSTOMWIDGET_H
