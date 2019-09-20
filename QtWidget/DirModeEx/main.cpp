#include "mainwindow.h"
#include <QApplication>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QDirModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDirModel model;	// 访问文件和目录的对象
    /* 新建三种不同的 View 对象，以便文件目录可以以三种不同的方式显示 */
    QTreeView tree;
    QListView list;
    QTableView table;
    tree.setModel(&model);	// 设置 view 对象的 model
    list.setModel(&model);
    table.setModel(&model);
    tree.setSelectionMode(QAbstractItemView::MultiSelection);	// 设置QTreeView对象的选择方式为多选
    list.setSelectionModel(tree.selectionModel());	// 设置 ListView 对象与 QTreeView 对象使用相同的选择模型
    table.setSelectionModel(tree.selectionModel());
    // 双击 QTreeView 对象中的某个目录时，QListView 对象和 QTableView 对象中显示选定目录下的所有文件和目录
    // 需要连接 QTreeView 对象的 doubleClicked() 信号与 QListView QTableView 对象的 setRootIndex() 槽函数
    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)), &list, SLOT(setRootIndex(QModelIndex)));
    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)), &table, SLOT(setRootIndex(QModelIndex)));

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(&tree);
    splitter->addWidget(&list);
    splitter->addWidget(&table);
    splitter->setWindowTitle(QObject::tr("Model/View"));
    splitter->show();

    return a.exec();
}
