#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    setActionsForButton();
    createSelectionPopMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 为 ToolButton 按钮设置 Action
void MainWindow::setActionsForButton()
{
     ui->tBtnListIni->setDefaultAction(ui->actListIni);
     ui->tBtnListClear->setDefaultAction(ui->actListClear);
     ui->tBtnListInsert->setDefaultAction(ui->actListInsert);
     ui->tBtnListAppend->setDefaultAction(ui->actListAppend);
     ui->tBtnListDelete->setDefaultAction(ui->actListDelete);

     ui->tBtnSelALL->setDefaultAction(ui->actSelAll);
     ui->tBtnSelNone->setDefaultAction(ui->actSelNone);
     ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);
}

// 创建下拉菜单
void MainWindow::createSelectionPopMenu()
{
    // 创建选择弹出式菜单
    QMenu* menuSelection = new QMenu(this);
    menuSelection->addAction(ui->actSelAll);
    menuSelection->addAction(ui->actSelNone);
    menuSelection->addAction(ui->actSelInvs);

    // listWidget 上方的 tBtnSelectItem 按钮
    ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup); // 菜单弹出模式 执行按钮的 Action
    ui->tBtnSelectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); // 按钮样式
    ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu);	// 关联Action
    ui->tBtnSelectItem->setMenu(menuSelection); // 设置下拉菜单

    // 工具栏上的 下拉菜单按钮
    QToolButton* aBtn = new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup); // 按钮拥有的 action 不被触发
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // 按钮样式
    aBtn->setDefaultAction(ui->actSelPopMenu);	// 关联Action，获取图标、标题等设置
    aBtn->setMenu(menuSelection); // 设置下拉菜单
    ui->mainToolBar->addWidget(aBtn);	// 工具栏添加按钮

    // 工具栏添加分隔条，和"退出"按钮
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actQuit);
}

// 初始化列表
void MainWindow::on_actListIni_triggered()
{
    QListWidgetItem *aItem;	// 每一行是一个  QListWidgetItem
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk = ui->chkBoxListEditable->isChecked(); // 是否可编辑
    ui->listWidget->clear();	// 清除项
    for (int i = 0; i < 10; i++) {
        QString str = QString::asprintf("Item %d", i);
        aItem = new QListWidgetItem();	// 新建一个项
        aItem->setText(str);	// 设置文字标签
        aItem->setIcon(aIcon);	// 设置图标
        aItem->setCheckState(Qt::Checked); // 设置选中状态
        // 根据是否可编辑，设置相应的 flags
        if (chk) {
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable
                | Qt::ItemIsUserCheckable| Qt::ItemIsEnabled);
        } else {
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }
        ui->listWidget->addItem(aItem); // 增加一个项
    }
}

// 插入一个项
void MainWindow::on_actListInsert_triggered()
{
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk = ui->chkBoxListEditable->isChecked(); // 是否可编辑

    QListWidgetItem* aItem = new QListWidgetItem("New Inserted Item");	// 新建一个项
    aItem->setIcon(aIcon);	// 设置图标
    aItem->setCheckState(Qt::Checked); // 设置选中状态
    if (chk) { // 设置标记
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable
        | Qt::ItemIsUserCheckable| Qt::ItemIsEnabled);
    } else {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
    // 在当前行的上方插入一个项
    ui->listWidget->insertItem(ui->listWidget->currentRow(), aItem);
}

// 增加一个项
void MainWindow::on_actListAppend_triggered()
{
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk = ui->chkBoxListEditable->isChecked(); // 是否可编辑

    QListWidgetItem* aItem = new QListWidgetItem("New Inserted Item");	// 新建一个项
    aItem->setIcon(aIcon);	// 设置图标
    aItem->setCheckState(Qt::Checked); // 设置选中状态
    if (chk) { // 设置标记
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable
            | Qt::ItemIsUserCheckable| Qt::ItemIsEnabled);
    } else {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
    // 在当前行的上方插入一个项
    ui->listWidget->addItem(aItem);

}

// 删除当前项
void MainWindow::on_actListDelete_triggered()
{
    int row = ui->listWidget->currentRow();
    // 移除指定行的项，但不delete
    QListWidgetItem* aItem = ui->listWidget->takeItem(row);
    delete aItem;	// 手工释放对象内存
    aItem = nullptr;
}

// 清除所有项
void MainWindow::on_actListClear_triggered()
{
    ui->listWidget->clear();
}

// 全选
void MainWindow::on_actSelAll_triggered()
{
    int cnt = ui->listWidget->count(); // 项个数
    for (int i = 0; i < cnt; i++) {
        // 获取一个项
        QListWidgetItem *aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Checked);	 // 设置为选中
    }
}

// 全不选
void MainWindow::on_actSelNone_triggered()
{
    int cnt = ui->listWidget->count(); // 项个数
    for (int i = 0; i < cnt; i++) {
        // 获取一个项
        QListWidgetItem *aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Unchecked);	 // 设置为未选中
    }
}

// 反选
void MainWindow::on_actSelInvs_triggered()
{
    int cnt = ui->listWidget->count(); // 项个数
    for (int i = 0; i < cnt; i++) {
        // 获取一个项
        QListWidgetItem *aItem = ui->listWidget->item(i);
        if (aItem->checkState() == Qt::Checked) {
            aItem->setCheckState(Qt::Unchecked);	 // 设置为未选中
        } else {
            aItem->setCheckState(Qt::Checked);	 // 设置为选中
        }
    }
}

// listWidget 当前选中项发生变化
void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if (current != nullptr) {	// 需要检测变量指针是否为空
        if (previous == nullptr) {
            str = "当前：" + current->text();
        } else {
            str = "前一项：" + previous->text() + "；当前项：" + current->text();
        }
        ui->editCutItemText->setText(str);
    }
}

// 自定义 listWidget 的右键菜单
void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu* menuList = new QMenu(this);	// 创建菜单

    // 添加 Actions 创建菜单项
    menuList->addAction(ui->actListIni);
    menuList->addAction(ui->actListClear);
    menuList->addAction(ui->actListInsert);
    menuList->addAction(ui->actListAppend);
    menuList->addAction(ui->actListDelete);
    menuList->addSeparator();
    menuList->addAction(ui->actSelAll);
    menuList->addAction(ui->actSelNone);
    menuList->addAction(ui->actSelInvs);
    menuList->exec(QCursor::pos());	// 在鼠标光标位置显示右键快捷菜单

    delete  menuList; // 手工创建的指针必须手工删除
    menuList = nullptr;
}

// "可编辑" QCheckBox 的响应代码，设置所有项是否可编辑
void MainWindow::on_chkBoxListEditable_clicked(bool checked)
{
    int cnt = ui->listWidget->count();
    QListWidgetItem *aItem;
    for (int i = 0; i < cnt; i++) {
        aItem = ui->listWidget->item(i); // 获得一个项
        if (checked) {// 可编辑
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable
                | Qt::ItemIsUserCheckable| Qt::ItemIsEnabled);
        } else {
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        }
    }

}
