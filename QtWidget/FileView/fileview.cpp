#include "fileview.h"

FileView::FileView(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle(tr("File View"));
    fileLineEdit = new QLineEdit(tr("/"));
    fileListWidget = new QListWidget;
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(fileLineEdit);
    mainLayout->addWidget(fileListWidget);
    connect(fileLineEdit, SIGNAL(returnPressed()), this, SLOT(slotShow(QDir)));
    connect(fileListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this,
        SLOT(slotDirShow(QListWidgetItem *)));
    QString root = "/";
    QDir rootDir(root);
    QStringList string;
    string << "*";
    QFileInfoList list = rootDir.entryInfoList(string);
    showFileInfoList(list);
}

FileView::~FileView()
{

}

// 显示目录下的所有文件
void FileView::slotShow(QDir dir)
{
    QStringList string;
    string << "*";
    QFileInfoList list = dir.entryInfoList(string, QDir::AllEntries, QDir::DirsFirst); // 获取目录下的文件列表
    showFileInfoList(list);
}

// 根据用户选择，显示下一目录中的所有文件
void FileView::slotDirShow(QListWidgetItem *item)
{
    QString str = item->text(); 	// 将下一级的目录名保存在 str 中
    QDir dir;
    dir.setPath(fileLineEdit->text()); // 设置QDir对象的路径为当前目录路径
    dir.cd(str);
    fileLineEdit->setText(dir.absolutePath());	// 显示当前目录绝对路径
    slotShow(dir);	// 显示当前目录下的所有文件
}

// 用户双击目录，进入下一级目录
void FileView::showFileInfoList(QFileInfoList list)
{
    fileListWidget->clear();	// 先清空列表控件
    for (unsigned int i=0;i<list.count();i++) {	// 依次从QFileInfoList对象中取出所有项
        QFileInfo tmpFileInfo = list.at(i);
        if (tmpFileInfo.isDir()) {
            QIcon icon("dir.png");
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(icon, fileName);
            fileListWidget->addItem(tmp);
        } else if (tmpFileInfo.isFile()) {
            QIcon icon("file.png");
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(icon, fileName);
            fileListWidget->addItem(tmp);
        }
    }
}
