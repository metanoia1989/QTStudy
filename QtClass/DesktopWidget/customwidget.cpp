#include "customwidget.h"
#include <QVBoxLayout>
#include <QCoreApplication>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    mWidget = new QListWidget(this);
    layout->addWidget(mWidget);

    mEdit = new QLineEdit(this);
    layout->addWidget(mEdit);

    mButton = new QPushButton("Quit", this);
    layout->addWidget(mButton);
    setLayout(layout);

    QStringList cities;
    cities << "Paris" << "London" << "Munich";
    foreach(const QString& city, cities) {
        mWidget->addItem(city);
    }

    connect(mWidget, &QListWidget::itemClicked, this, &CustomWidget::itemClicked);
    connect(mEdit, &QLineEdit::editingFinished, this, &CustomWidget::updateItem);
    connect(mButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
}

void CustomWidget::itemClicked(QListWidgetItem *item)
{
    Q_ASSERT(item);
    mEdit->setText(item->text());
}

void CustomWidget::updateItem()
{
    QListWidgetItem *item = mWidget->currentItem();
    if (item) {
        item->setText(mEdit->text());
    }
}
