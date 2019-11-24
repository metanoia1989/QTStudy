#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LabFileName = new QLabel("");
    ui->statusBar->addWidget(LabFileName);

    // 设置中心布局组件
    this->setCentralWidget(ui->scrollArea);
    iniTree(); // 初始化目录树
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 初始化目录树 Tree
void MainWindow::iniTree()
{
    QString dataStr = "";	// Item的Data存储的string

    ui->treeFiles->clear(); // 清除目录树所有节点
    QIcon icon;
    icon.addFile(":/images/icons/15.ico");

    // 新建节点时设置类型为 itTopItem
    QTreeWidgetItem* item = new QTreeWidgetItem(MainWindow::itTopItem);
    item->setIcon(MainWindow::colItem, icon);	// 设置第1列的图标
    item->setText(MainWindow::colItem, "图片文件");	// 设置第1列的文字
    item->setText(MainWindow::colItemType, "type=itTopItem");	// 设置第2列的文字
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);	// 设置为选中
    // 设置节点第1列的Qt::UserRole的Data
    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dataStr));
    ui->treeFiles->addTopLevelItem(item); // 添加顶层节点
}

// 添加一个目录节点
void MainWindow::addFloderItem(QTreeWidgetItem *parItem, QString dirName)
{
    QIcon icon(":/images/icons/open3.bmp");
    // 从一个完整目录名称里，获得最后的文件夹名称
    QString NodeText = getFinalFolderName(dirName);

    QTreeWidgetItem *item; // 节点
    // 新建节点，设定 type 为 itGroupItem
    item = new QTreeWidgetItem(itGroupItem);
    item->setIcon(colItem, icon);	// 设置图标
    item->setText(colItem, NodeText);	// 最后的文件夹名称，第1列
    item->setText(colItemType, "type=itGroupItem");	// 完整目录名称，第二列
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);	// 设置为选中
    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dirName)); // 存储完整目录名称

    parItem->addChild(item);	// 在父节点下面添加子节点
}

// 从一个完整目录名称里，获得最后的文件夹名称
QString MainWindow::getFinalFolderName(const QString &fullPathName)
{
    int cnt = fullPathName.length(); // 字符串长度
    int i = fullPathName.lastIndexOf("/"); // 最后一次出现的位置
    QString str = fullPathName.right(cnt - i - 1);	// 获得最后的文件夹的名称
    return str;
}

// 添加一个图片文件节点
void MainWindow::addImageItem(QTreeWidgetItem *parItem, QString aFilename)
{
    QIcon icon(":/images/icons/31.ico");
    // 从一个完整目录名称里，获得最后的文件夹名称
    QString NodeText = getFinalFolderName(aFilename);

    QTreeWidgetItem *item; // 节点
    // 新建节点，设定 type 为 itImageItem
    item = new QTreeWidgetItem(itImageItem);
    item->setIcon(colItem, icon);	// 设置图标
    item->setText(colItem, NodeText);	// 最后的文件夹名称，第1列
    item->setText(colItemType, "type=itImageItem");	// 完整目录名称，第二列
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);	// 设置为选中
    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(aFilename)); // 存储完整目录名称

    parItem->addChild(item);	// 在父节点下面添加子节点
}

// 显示图片，节点 item 存储的图片文件名
void MainWindow::displayImage(QTreeWidgetItem *item)
{
    // 获取节点data里存储的文件名
    QString filename = item->data(colItem, Qt::UserRole).toString();
    LabFileName->setText(filename);
    curPixmap.load(filename); // 从文件载入图片
    on_actZoomFitH_triggered(); // 自动适应高度显示

    ui->actZoomFitH->setEnabled(true);
    ui->actZoomFitW->setEnabled(true);
    ui->actZoomIn->setEnabled(true);
    ui->actZoomOut->setEnabled(true);
    ui->actZoomRealSize->setEnabled(true);
}

// 改变节点的标题文字
void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str = "*" + item->text(colItem); // 节点标题前添加*
    item->setText(colItem, str);	// 设置节点标题

    // 如果有子节点
    if (item->childCount() > 0) {
        // 遍历子节点 递归
        for (int i = 0; i < item->childCount(); i++) {
            changeItemCaption(item->child(i));
        }
    }
}

// 添加组节点 选择一个文件夹，作为当前
// 当目录树上的当前节点类型是itTopItem或itGroupItem类型时，才可以添加组节点
void MainWindow::on_actAddFolder_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(); // 选择目录
    if (!dir.isEmpty()) {
        QTreeWidgetItem* parItem = ui->treeFiles->currentItem(); // 当前节点
        addFloderItem(parItem, dir);
    }
}

// 添加图片文件节点
void MainWindow::on_actAddFiles_triggered()
{
    // 选择多个文件
    QStringList files = QFileDialog::getOpenFileNames(this, "选择一个或多个文件", "", "Images(*.jpg)");
    if (files.isEmpty()) {
        return;
    }

    QTreeWidgetItem *parItem, *item; // 节点
    item = ui->treeFiles->currentItem(); // 当前节点

    if (item->type() == itImageItem) { // 当前节点是图片节点，取其父节点作为父节点
        parItem = item->parent();
    } else { // 否则取当前节点为父节点
        parItem = item;
    }
    for (int i = 0; i < files.size(); ++i) {
        QString aFilename = files.at(i);	// 获取 StringList 的一行
        addImageItem(parItem, aFilename); // 添加一个图片节点
    }
}

// 适应高度显示图片
void MainWindow::on_actZoomFitH_triggered()
{
    int H = ui->scrollArea->height();
    int realH = curPixmap.height(); // 原始图片的实际高度
    pixRatio = double (H) / realH; // 当前显示比例，必须转换为浮点数

    QPixmap pix = curPixmap.scaledToHeight(H - 30); // 图片缩放到指定高度
    ui->LabPicture->setPixmap(pix);	// 设置Label的PixMap
}

// 适应宽度显示图片
void MainWindow::on_actZoomFitW_triggered()
{
    int W = ui->scrollArea->width() - 20; // ScrollArea的宽度
    int realW = curPixmap.width(); // 原始图片的实际宽度
    pixRatio = double(W) / realW; // 当前显示比例，转换为浮点数

    QPixmap pix = curPixmap.scaledToWidth(W - 30);
    ui->LabPicture->setPixmap(pix);
}

// 放大显示
void MainWindow::on_actZoomIn_triggered()
{
    pixRatio = pixRatio * 0.8; // 在当前比例基础上乘以0.8

    int w = static_cast<int>(pixRatio * curPixmap.width()); // 显示宽度
    int h = static_cast<int>(pixRatio * curPixmap.height()); // 显示高度

    QPixmap pix = curPixmap.scaled(w, h); // 图片缩放到指定高度和宽度，保持长宽比例
    ui->LabPicture->setPixmap(pix);
}

// 缩小显示
void MainWindow::on_actZoomOut_triggered()
{
    pixRatio = pixRatio * 1.2; // 在当前比例基础上乘以1.2

    int w = static_cast<int>(pixRatio * curPixmap.width()); // 显示宽度
    int h = static_cast<int>(pixRatio * curPixmap.height()); // 显示高度

    QPixmap pix = curPixmap.scaled(w, h); // 图片缩放到指定高度和宽度，保持长宽比例
    ui->LabPicture->setPixmap(pix);
}

// 实际大小显示
void MainWindow::on_actZoomRealSize_triggered()
{
    pixRatio = 1; // 恢复显示比例为1
    ui->LabPicture->setPixmap(curPixmap);
}

// 删除节点
void MainWindow::on_actDeleteItem_triggered()
{
    QTreeWidgetItem* item = ui->treeFiles->currentItem(); // 当前节点
    QTreeWidgetItem* parItem = item->parent(); // 父节点
    parItem->removeChild(item);	// 移除并不会删除
    delete item;
}

// 遍历节点
void MainWindow::on_actScanItems_triggered()
{
    for (int i = 0; i < ui->treeFiles->topLevelItemCount(); i++) {
        QTreeWidgetItem* item = ui->treeFiles->topLevelItem(i); // 顶层节点
        changeItemCaption(item); // 更改节点标题
    }
}

// 当前节点选择变化时触发
void MainWindow::on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
     Q_UNUSED(previous);
    if (current == nullptr) {
        return;
    }

    int var = current->type(); // 节点的类型

    switch (var) {
        case itTopItem: // 顶层节点
            ui->actAddFolder->setEnabled(true);
            ui->actAddFiles->setEnabled(true);
            ui->actDeleteItem->setEnabled(false); // 顶层节点不能删除
        break;
        case itGroupItem: // 文件组节点
            ui->actAddFolder->setEnabled(true);
            ui->actAddFiles->setEnabled(true);
            ui->actDeleteItem->setEnabled(true);
        break;
        case itImageItem: // 图片文件节点
            ui->actAddFolder->setEnabled(false); // 图片节点不能添加目录节点
            ui->actAddFiles->setEnabled(true);
            ui->actDeleteItem->setEnabled(true);
            displayImage(current);	// 显示图片
        break;
    }
}

// 停靠区的可见性
void MainWindow::on_actDockVisible_toggled(bool arg1)
{
    ui->dockWidget->setVisible(arg1);
}

// 停靠区的浮动性
void MainWindow::on_actDockFloat_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}

// 停靠区可见性变化
void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actDockVisible->setChecked(visible);
}

// 停靠区浮动性变化
void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actDockFloat->setChecked(topLevel);
}
