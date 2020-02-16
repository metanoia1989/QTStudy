#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto tb = new QTableWidget(this);
    tb->setRowCount(10);
    tb->setColumnCount(3);

    QStringList tbH = { "语文", "数学", "英文" };
    tb->setHorizontalHeaderLabels(tbH);

    for (int row=0; row<10; row++) {
        for (int column=0; column<3; column++) {
            QString str = tr("num: %1, %2").arg(row).arg(column);
            auto item = new QTableWidgetItem(str);
            tb->setItem(row, column, item);
        }
    }
    tb->setSelectionBehavior(QAbstractItemView::SelectRows);
    tb->setSelectionMode(QAbstractItemView::SingleSelection);

    auto item = tb->item(1, 1);
//    item->setFlags(Qt::NoItemFlags);
    item->setFlags(item->flags() &  ~Qt::ItemIsSelectable );
    setCentralWidget(tb);
}

MainWindow::~MainWindow()
{
    delete ui;
}

