#include "qformdoc.h"
#include "ui_qformdoc.h"

#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QFontDialog>
#include <QFileInfo>
#include <QMessageBox>

QFormDoc::QFormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormDoc)
{
    ui->setupUi(this);

    this->setWindowTitle("New Doc");	// 标题
    this->setAttribute(Qt::WA_DeleteOnClose);	// 关闭时自动删除
}

QFormDoc::~QFormDoc()
{
    delete ui;
}

// 打开文件
void QFormDoc::loadFromFile(QString &aFileName)
{
    QFile aFile(aFileName);
    if (aFile.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QTextStream aStream(&aFile);
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(aStream.readAll());
        aFile.close();

        mCurrentFile = aFileName;	// 保存当前文件名
        QFileInfo fileInfo(aFileName); // 文件信息
        QString str = fileInfo.fileName(); // 去除路径后的文件名
        this->setWindowTitle(str);
        mFileOpened = true;
    }
}

// 当前打开的文件名
QString QFormDoc::currentFileName()
{
    return mCurrentFile;
}

// 文件是否已打开
bool QFormDoc::isFileOpened()
{
    return mFileOpened;
}

void QFormDoc::setEditFont()
{
    QFont font;
    font = ui->plainTextEdit->font();

    bool ok;
    font = QFontDialog::getFont(&ok, font);
    if (ok) {
        ui->plainTextEdit->setFont(font);
    }
}

void QFormDoc::textCut()
{
    ui->plainTextEdit->cut();
}

void QFormDoc::textCopy()
{
    ui->plainTextEdit->copy();
}

void QFormDoc::textPaste()
{
    ui->plainTextEdit->paste();
}
