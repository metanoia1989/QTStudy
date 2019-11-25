#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 完成数据模型与界面视图组件的关联
    QStringList theStrList;	// 保存初始 StringList
    theStrList << "北京" << "上海" << "天津" << "河北" << "山东"
               << "四川" << "重庆" << "广东" << "河南";
    theModel = new QStringListModel(this);	// 创建数据模型
    theModel->setStringList(theStrList);	// 为模型设置StringList
    ui->listView->setModel(theModel);	// 设置数据模型

    // 设置QListView的条目是否可以编辑，以及如何进入变量状态
    // 双击或者选择并单击列表项后，进入编辑状态
    // QAbstractItemView::NoEditriggers 禁止编辑
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked
                                  |QAbstractItemView::SelectedClicked);

}

Widget::~Widget()
{
    delete ui;
}

// 显示 QModelIndex 的列、行号
void Widget::on_listView_clicked(const QModelIndex &index)
{
    ui->LabInfo->setText(QString::asprintf("当前项：row=%d，column=%d",
                        index.row(), index.column()));
}

// 重新载入 theStrList 的内容，初始化 theModel 的内容
void Widget::on_btnIniList_clicked()
{
    QStringList theStrList;	// 保存初始 StringList
    theStrList << "北京" << "上海" << "天津" << "河北" << "山东"
               << "四川" << "重庆" << "广东" << "河南";
    theModel->setStringList(theStrList);	// 为模型设置StringList
}

//添加项
void Widget::on_btnListAppend_clicked()
{
    theModel->insertRow(theModel->rowCount()); // 在尾部插入一空行
    QModelIndex index = theModel->index(theModel->rowCount()-1, 0); // 获取最后一行
    theModel->setData(index, "new item", Qt::DisplayRole);	// 设置显示文字
    ui->listView->setCurrentIndex(index); // 设置当前选中的行
}

// 插入项
void Widget::on_btnListInsert_clicked()
{
    QModelIndex index;
    index = ui->listView->currentIndex(); // 当前 modelIndex
    theModel->insertRow(index.row());	// 在当前行的前面插入一行
    theModel->setData(index, "inserted item", Qt::DisplayRole);	// 设置显示文字
    // 设置对齐方式，不起作用
    theModel->setData(index, Qt::AlignRight, Qt::TextAlignmentRole);
    ui->listView->setCurrentIndex(index);
}

// 删除当前项
void Widget::on_btnListDelete_clicked()
{
    QModelIndex index;
    // 获取当前 modelIndex
    index = ui->listView->currentIndex();
    theModel->removeRow(index.row());
}

// 删除列表 清除ListView所有项
void Widget::on_btnListClear_clicked()
{
    theModel->removeRows(0, theModel->rowCount());
}

// 显示数据模型的 StringList
void Widget::on_btnTextImport_clicked()
{
    QStringList tmpList;
    // 获取数据模型的StringList
    tmpList = theModel->stringList();
    ui->plainTextEdit->clear();
    for (int i = 0; i < tmpList.count(); i++) {
        ui->plainTextEdit->appendPlainText(tmpList.at(i));
    }
}

// 清空plainTextEdit显示的文本
void Widget::on_btnTextClear_clicked()
{
    ui->plainTextEdit->clear();
}
