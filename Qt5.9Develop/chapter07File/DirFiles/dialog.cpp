#include "dialog.h"
#include "ui_dialog.h"
#include <QPushButton>
#include <QFileInfo>
#include <QDateTime>
#include <QDir>
#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QFileDialog>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
}

Dialog::~Dialog()
{
    delete ui;
}

// QFileSystemWather::directoryChanged() 信号的槽函数
void Dialog::on_directoryChanged(const QString path)
{
    ui->plainTextEdit->appendPlainText(path);
    ui->plainTextEdit->appendPlainText("目录发生了变化\n");
}

// QFileSystemWather::fileChanged() 信号的槽函数
void Dialog::on_fileChanged(const QString path)
{
    ui->plainTextEdit->appendPlainText(path);
    ui->plainTextEdit->appendPlainText("文件发生了变化\n");
}

// 显示btn的信息
void Dialog::showBtnInfo(QObject *btn)
{
    QPushButton *theBtn = static_cast<QPushButton*>(btn);
    ui->plainTextEdit->appendPlainText(theBtn->text());
    ui->plainTextEdit->appendPlainText(theBtn->toolTip()+"\n");
}


// QCoreApplication::applicationDirPath() 返回应用程序启动路径
void Dialog::on_pushButton_4_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::applicationDirPath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QCoreApplication::applicationFilePath() 返回应用程序的带有目录的完整文件名
void Dialog::on_pushButton_6_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::applicationFilePath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QCoreApplication::applicationName() 返回应用程序名称，无路径无后缀
void Dialog::on_pushButton_5_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::applicationName();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QCoreApplication::libraryPaths() 返回动态加载库文件时，应用程序搜索的目录列表
void Dialog::on_pushButton_7_clicked()
{
    showBtnInfo(sender());
    QStringList strList = QCoreApplication::libraryPaths();
    for (int i=0; i<strList.count(); i++) {
        ui->plainTextEdit->appendPlainText(strList.at(i));
    }
    ui->plainTextEdit->appendPlainText("");
}

// QCoreApplication::origanizationName() 返回应用程序的机构名
void Dialog::on_pushButton_8_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::organizationName();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QCoreApplication::exit() 退出应用程序
void Dialog::on_pushButton_9_clicked()
{
    QCoreApplication::exit();
}

// static QFile::copy()
void Dialog::on_pushButton_10_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text(); // 源文件
    QFileInfo fileInfo(sous);
    QString newFile = fileInfo.path() + "/" +
            fileInfo.baseName() + "--副本." +
            fileInfo.suffix();
    QFile::copy(sous, newFile);
    ui->plainTextEdit->appendPlainText("源文件：" + sous);
    ui->plainTextEdit->appendPlainText("复制为文件：" + newFile + "\n");
}

// static QFile::exists()
void Dialog::on_pushButton_11_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text(); // 源文件
    bool the = QFile::exists(sous);
    if (the) {
        ui->plainTextEdit->appendPlainText(+"true \n");
    } else {
        ui->plainTextEdit->appendPlainText(+"false \n");
    }
}

// static QFile::remove()
void Dialog::on_pushButton_12_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text(); // 源文件
    QFile::remove(sous);
    ui->plainTextEdit->appendPlainText("删除文件：" + sous + "\n");
}

// static QFile::rename()
void Dialog::on_pushButton_13_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text(); // 源文件
    QFileInfo fileInfo(sous); // 源文件信息
    QString newFile = fileInfo.path() + "/" + fileInfo.baseName()
            + ".XYZ"; // 更改文件后缀为 ".XYZ"
    QFile::rename(sous, newFile);	// 重命名文件
    ui->plainTextEdit->appendPlainText("源文件：" + sous);
    ui->plainTextEdit->appendPlainText("重命名为：" + newFile + "\n");
}

// member QFile::copy()
void Dialog::on_pushButton_14_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text(); // 源文件
    QFile file(sous);

    QFileInfo fileInfo(sous);
    QString newFile = fileInfo.path() + "/" +
            fileInfo.baseName() + "--副本." +
            fileInfo.suffix();
    file.copy(newFile);
    ui->plainTextEdit->appendPlainText("源文件：" + sous);
    ui->plainTextEdit->appendPlainText("复制为文件：" + newFile + "\n");
}

// member QFile::exists()
void Dialog::on_pushButton_15_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text(); // 源文件
    QFile file(sous);
    bool the = file.exists();
    if (the) {
        ui->plainTextEdit->appendPlainText(+"true \n");
    } else {
        ui->plainTextEdit->appendPlainText(+"false \n");
    }
}

// member QFile::remove()
void Dialog::on_pushButton_16_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text(); // 源文件
    QFile file(sous);
    file.remove();
    ui->plainTextEdit->appendPlainText("删除文件：" + sous + "\n");

}

// member QFile::rename()
void Dialog::on_pushButton_17_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text(); // 源文件
    QFile file(sous);	// 源文件对象
    QFileInfo fileInfo(sous); // 源文件信息
    QString newFile = fileInfo.path() + "/" + fileInfo.baseName()
            + ".XYZ"; // 更改文件后缀为 ".XYZ"
    file.rename(newFile); // 重命名文件
    ui->plainTextEdit->appendPlainText("源文件：" + sous);
    ui->plainTextEdit->appendPlainText("重命名为：" + newFile + "\n");
}

// QFileInfo::absoluteFilePath()
void Dialog::on_pushButton_18_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.absoluteFilePath();
    ui->plainTextEdit->appendPlainText(str+"\n");
}

// QFileInfo::absolutePath()
void Dialog::on_pushButton_19_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.absolutePath();
    ui->plainTextEdit->appendPlainText(str+"\n");
}

// QFileInfo::fileName()
void Dialog::on_pushButton_20_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.fileName();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QFileInfo::filePath()
void Dialog::on_pushButton_21_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.filePath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QFileInfo::size()
void Dialog::on_pushButton_22_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    qint64 dt = fileInfo.size();
    QString str = QString("%1 Bytes").arg(dt);
    ui->plainTextEdit->appendPlainText(str + "\n");

}

// QFileInfo::path()
void Dialog::on_pushButton_23_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.path();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QFileInfo::baseName()
void Dialog::on_pushButton_24_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.baseName();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QFileInfo::completeBaseName()
void Dialog::on_pushButton_25_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.completeBaseName();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QFileInfo::suffix()
void Dialog::on_pushButton_26_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.suffix();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QFileInfo::completeSuffix()
void Dialog::on_pushButton_27_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.completeSuffix();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QFileInfo::isDir()
void Dialog::on_pushButton_28_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editDir->text());
    bool the = fileInfo.isDir();
    if (the) {
        ui->plainTextEdit->appendPlainText(+"true \n");
    } else {
        ui->plainTextEdit->appendPlainText(+"false \n");
    }
}

// QFileInfo::isFile()
void Dialog::on_pushButton_29_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    bool the = fileInfo.isFile();
    if (the) {
        ui->plainTextEdit->appendPlainText(+"true \n");
    } else {
        ui->plainTextEdit->appendPlainText(+"false \n");
    }
}

// QFileInfo::isExecutable()
void Dialog::on_pushButton_30_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    bool the = fileInfo.isExecutable();
    if (the) {
        ui->plainTextEdit->appendPlainText(+"true \n");
    } else {
        ui->plainTextEdit->appendPlainText(+"false \n");
    }
}

// QFileInfo::created()
void Dialog::on_pushButton_31_clicked()
{

}

// QFileInfo::lastModified()
void Dialog::on_pushButton_32_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QDateTime dt = fileInfo.lastModified();
    QString str = dt.toString("yyyy-MM-dd hh:mm:ss");
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QFileInfo::lastRead()
void Dialog::on_pushButton_33_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QDateTime dt = fileInfo.lastRead();
    QString str = dt.toString("yyyy-MM-dd hh:mm:ss");
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// static QFileInfo::exists()
void Dialog::on_pushButton_34_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    bool the = QFileInfo::exists(sous);
    if (the) {
        ui->plainTextEdit->appendPlainText(+"true \n");
    } else {
        ui->plainTextEdit->appendPlainText(+"false \n");
    }
}

// member QFileInfo::exists()
void Dialog::on_pushButton_35_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    bool the = fileInfo.exists();
    if (the) {
        ui->plainTextEdit->appendPlainText(+"true \n");
    } else {
        ui->plainTextEdit->appendPlainText(+"false \n");
    }
}

// QDir::tempPath()
void Dialog::on_pushButton_36_clicked()
{
    showBtnInfo(sender());
    QString str = QDir::tempPath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QDir::rootPath()
void Dialog::on_pushButton_37_clicked()
{
    showBtnInfo(sender());
    QString str = QDir::rootPath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QDir::homePath()
void Dialog::on_pushButton_38_clicked()
{
    showBtnInfo(sender());
    QString str = QDir::homePath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QDir::drives()
void Dialog::on_pushButton_39_clicked()
{
    showBtnInfo(sender());
    QFileInfoList strList = QDir::drives();
    for (int i=0; i<strList.count(); i++) {
        ui->plainTextEdit->appendPlainText(strList.at(i).path());
    }
    ui->plainTextEdit->appendPlainText("\n");
}

// QDir::currentPath()
void Dialog::on_pushButton_40_clicked()
{
    showBtnInfo(sender());
    QString str = QDir::currentPath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QDir::setCurrent()
void Dialog::on_pushButton_41_clicked()
{
    showBtnInfo(sender());
    QDir::setCurrent(ui->editDir->text());
    QString str = QDir::currentPath();
    ui->editDir->setText(str);
    ui->plainTextEdit->appendPlainText("设置当前路径为：" + str + "\n");
}

// QDir::mkdir()
void Dialog::on_pushButton_42_clicked()
{
    showBtnInfo(sender());
    QString subDir = "subdir1";
    QDir dir(ui->editDir->text());
    bool ok = dir.mkdir(subDir);
    if (ok) {
        ui->plainTextEdit->appendPlainText("所选目录下成功新建一个目录" + subDir + "\n");
    } else {
        ui->plainTextEdit->appendPlainText("创建目录失败\n");
    }
}

// QDir::rmdir()
void Dialog::on_pushButton_43_clicked()
{
    showBtnInfo(sender());
    QString sous(ui->editDir->text());
    QDir dir(sous);
    bool ok = dir.rmdir(sous);
    if (ok) {
        ui->plainTextEdit->appendPlainText("成功删除所选目录:" + sous + "\n");
    } else {
        ui->plainTextEdit->appendPlainText("删除失败\n");
    }

}

// QDir::remove()
void Dialog::on_pushButton_44_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    QString sous(ui->editFile->text());
    bool ok = dir.remove(sous);
    if (ok) {
        ui->plainTextEdit->appendPlainText("删除文件：" + sous + "\n");
    } else {
        ui->plainTextEdit->appendPlainText("删除文件失败\n");
    }
}

// QDir::rename()
void Dialog::on_pushButton_45_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    QString sous = ui->editFile->text(); // 源文件
    QFileInfo fileInfo(sous);
    QString newFile = fileInfo.path() + "/" + fileInfo.baseName() + ".XYZ";
    dir.rename(sous, newFile);

    ui->plainTextEdit->appendPlainText("源文件：" + sous);
    ui->plainTextEdit->appendPlainText("重命名为：" + newFile + "\n");
}

// QDir::setPath()
void Dialog::on_pushButton_46_clicked()
{
}

// QDir::removeRecursively()
void Dialog::on_pushButton_47_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    bool ok = dir.removeRecursively();
    if (ok) {
        ui->plainTextEdit->appendPlainText("删除目录及文件成功\n");
    } else {
        ui->plainTextEdit->appendPlainText("删除目录及文件失败\n");
    }
}

// QDir::absoluteFilePath()
void Dialog::on_pushButton_48_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.absoluteFilePath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QDir::absolutePath()
void Dialog::on_pushButton_49_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->editFile->text());
    QString str = fileInfo.absolutePath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QDir::canonicalPath()
void Dialog::on_pushButton_50_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    QString str = dir.canonicalPath();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QDir::filePath()
void Dialog::on_pushButton_51_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    QString str = dir.filePath(ui->editDir->text());
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QDir::exists()
void Dialog::on_pushButton_52_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    bool the = dir.exists();
    if (the) {
        ui->plainTextEdit->appendPlainText("true \n");
    } else {
        ui->plainTextEdit->appendPlainText("false \n");
    }
}

// QDir::dirName()
void Dialog::on_pushButton_53_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    QString str = dir.dirName();
    ui->plainTextEdit->appendPlainText(str + "\n");
}

// QDir::entryList(dir) 列出子目录
void Dialog::on_pushButton_54_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    QStringList strList = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);

    ui->plainTextEdit->appendPlainText("所选目录下的所有目录：");
    for (int i=0; i<strList.count(); i++) {
        ui->plainTextEdit->appendPlainText(strList.at(i));
    }
    ui->plainTextEdit->appendPlainText("\n");
}

// QDir::entryList(file) 列出所有文件
void Dialog::on_pushButton_55_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    QStringList strList = dir.entryList(QDir::Files);

    ui->plainTextEdit->appendPlainText("所选目录下的所有文件：");
    for (int i=0; i<strList.count(); i++) {
        ui->plainTextEdit->appendPlainText(strList.at(i));
    }
    ui->plainTextEdit->appendPlainText("\n");
}

// QTemporaryDir
void Dialog::on_pushButton_56_clicked()
{
    showBtnInfo(sender());
    QTemporaryDir dir;
    dir.setAutoRemove(true);
    ui->plainTextEdit->appendPlainText(dir.path() + "\n");
}

// QTemporaryFile
void Dialog::on_pushButton_57_clicked()
{
    showBtnInfo(sender());
    QTemporaryFile aFile;
    aFile.setAutoRemove(true);
    aFile.open();
    ui->plainTextEdit->appendPlainText(aFile.fileName() + "\n");
}

// QFileSystemWatcher::addPath() 开始监听
void Dialog::on_pushButton_58_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("监听目录：" +
                   ui->editDir->text() + "\n");
    fileWatcher.addPath(ui->editDir->text());	// 添加监听目录
    fileWatcher.addPath(ui->editFile->text());	// 添加监听文件
    connect(&fileWatcher, &QFileSystemWatcher::directoryChanged,
            this, &Dialog::on_directoryChanged);
    connect(&fileWatcher, &QFileSystemWatcher::fileChanged,
            this, &Dialog::on_fileChanged);
}

// QFileSystemWatcher::removePath() 停止监听
void Dialog::on_pushButton_59_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("停止监听目录：" +
                   ui->editDir->text() + "\n");
    fileWatcher.removePath(ui->editDir->text());	// 添加监听目录
    fileWatcher.removePath(ui->editFile->text());	// 添加监听文件
    disconnect(&fileWatcher, &QFileSystemWatcher::directoryChanged,
            this, &Dialog::on_directoryChanged);
    disconnect(&fileWatcher, &QFileSystemWatcher::fileChanged,
            this, &Dialog::on_fileChanged);
}

// QFileSystemWatcher::directories() 显示监听目录
void Dialog::on_pushButton_60_clicked()
{
    showBtnInfo(sender());
    QStringList strList = fileWatcher.directories();
    for (int i=0; i<strList.count(); i++) {
        ui->plainTextEdit->appendPlainText(strList.at(i));
    }
    ui->plainTextEdit->appendPlainText("\n");
}

// QFileSystemWatcher::files() 显示监听文件
void Dialog::on_pushButton_61_clicked()
{
    showBtnInfo(sender());
    QStringList strList = fileWatcher.files();
    for (int i=0; i<strList.count(); i++) {
        ui->plainTextEdit->appendPlainText(strList.at(i));
    }
    ui->plainTextEdit->appendPlainText("\n");
}

// 打开文件
void Dialog::on_pushButton_clicked()
{
    QString curDir = QDir::currentPath();
    QString aFile = QFileDialog::getOpenFileName(this,
                     "打开一个文件", curDir, "所有文件(*.*)");
    ui->editFile->setText(aFile);
}

// 打开目录
void Dialog::on_pushButton_2_clicked()
{
    QString curDir = QDir::currentPath();
    QString aDir = QFileDialog::getExistingDirectory(this, "选择一个目录",
                         curDir, QFileDialog::ShowDirsOnly);
    ui->editDir->setText(aDir);
}

// 清除文本框
void Dialog::on_pushButton_3_clicked()
{
    ui->plainTextEdit->clear();
}
