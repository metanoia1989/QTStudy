#include "mainwindow.h"
#include <QGridLayout>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGroupBox *factory = createFactoryGroupBox();
    QGroupBox *cars = createCarGroupBox();
    QGroupBox *details = createDetailsGroupBox();
    // 布局
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(factory, 0, 0);
    layout->addWidget(cars, 1, 0);
    layout->addWidget(details, 0, 1, 2, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);

    createMenuBar();
    resize(850, 400);
    setWindowTitle(tr("主从视图"));
}

MainWindow::~MainWindow()
{

}

QGroupBox* MainWindow::createFactoryGroupBox()
{
    factoryView = new QTableView;
    factoryView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止用户编辑
    factoryView->setSortingEnabled(true);
    factoryView->setSelectionBehavior(QAbstractItemView::SelectRows);
    factoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    factoryView->setShowGrid(false);
    factoryView->setAlternatingRowColors(true);

    QGroupBox *box = new QGroupBox(tr("汽车制造商"));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(factoryView, 0, 0);
    box->setLayout(layout);
    return box;
}


QGroupBox* MainWindow::createCarGroupBox()
{
    carView = new QTableView;
    carView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止用户编辑
    carView->setSortingEnabled(true);
    carView->setSelectionBehavior(QAbstractItemView::SelectRows);
    carView->setSelectionMode(QAbstractItemView::SingleSelection);
    carView->setShowGrid(false);
    carView->setAlternatingRowColors(true);
    carView->verticalHeader()->hide();

    QGroupBox *box = new QGroupBox(tr("汽车"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(carView, 0, nullptr);
    box->setLayout(layout);
    return box;
}

QGroupBox* MainWindow::createDetailsGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("详细信息"));
    profileLabel = new QLabel;
    profileLabel->setWordWrap(true);
    profileLabel->setAlignment(Qt::AlignBottom);

    titleLabel = new QLabel;
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignBottom);

    attribList = new QListWidget;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(profileLabel, 0, 0, 1, 2);
    layout->addWidget(titleLabel, 1, 0, 1, 2);
    layout->addWidget(attribList, 2, 0, 1, 2);
    layout->setRowStretch(2, 1);
    box->setLayout(layout);
    return box;
}

void MainWindow::createMenuBar()
{
    QAction *addAction = new QAction(tr("添加"), this);
    QAction *deleteAction = new QAction(tr("删除"), this);
    QAction *quitAction = new QAction(tr("退出"), this);
    addAction->setShortcut(tr("Ctrl+A"));
    deleteAction->setShortcut(tr("Ctrl+D"));
    quitAction->setShortcut(tr("Ctrl+Q"));
    QMenu *fileMenu = menuBar()->addMenu(tr("操作菜单"));
    fileMenu->addAction(addAction);
    fileMenu->addAction(deleteAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);
}
