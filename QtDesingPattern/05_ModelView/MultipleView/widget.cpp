#include "widget.hpp"
#include <QtWidgets>
#include <QDebug>
#include "createModel.hpp"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QStandardItemModel *model = createModel(this);
    QSplitter vsplitter(Qt::Vertical);


    QSplitter hsplitter;

    QListView list;
    QTableView table;
    QTreeView tree;
    QColumnView columnView;

    list.setToolTip("QListView");
    table.setToolTip("QTableView");
    tree.setToolTip("QTreeView");
    columnView.setToolTip("QColumnView");

    list.setModel(model);
    table.setModel(model);
    tree.setModel(model);
    columnView.setModel(model);

    table.setColumnWidth(0, 200);
    table.setColumnWidth(1, 150);
    tree.header()->resizeSection(0, 200);
    tree.header()->resizeSection(1, 150);

    list.setSelectionModel(tree.selectionModel());
    table.setSelectionModel(tree.selectionModel());
    columnView.setSelectionModel(tree.selectionModel());
    table.setSelectionBehavior(QAbstractItemView::SelectRows);
    table.setSelectionMode(QAbstractItemView::SingleSelection);

    hsplitter.addWidget(&list);
    hsplitter.addWidget(&table);
    vsplitter.addWidget(&hsplitter);
    vsplitter.addWidget(&tree);
    vsplitter.addWidget(&columnView);


    QObjectList kids = vsplitter.children();
    for (QObject* optr : kids) {
        qDebug() << optr->metaObject()->className();
    }

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(&vsplitter);
    layout->addWidget(new QLabel("测试"));
    setLayout(layout);
    setGeometry(300, 300, 500, 500);
    setWindowTitle("Multiple Views - Editable Model");
}

Widget::~Widget()
{
}

