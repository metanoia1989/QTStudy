#include "qformdoc.h"
#include "ui_qformdoc.h"
#include "mainwindow.h"

#include <QToolBar>
#include <QVBoxLayout>
#include <QFileDialog>
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

    // 使用UI设计的Actions设计工具栏
    QToolBar *locToolBar = new QToolBar(tr("文档"), this);
    locToolBar->addAction(ui->actOpen);
    locToolBar->addAction(ui->actFont);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actCut);
    locToolBar->addAction(ui->actCopy);
    locToolBar->addAction(ui->actPaste);
    locToolBar->addAction(ui->actUndo);
    locToolBar->addAction(ui->actRedo);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actClose);
    locToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(locToolBar); // 设置工具栏和编辑器垂直布局
    layout->addWidget(ui->plainTextEdit);
    layout->setContentsMargins(2, 2, 2, 2); // 减小边框的宽度
    layout->setSpacing(2);
    this->setLayout(layout);	// 应用布局

}

QFormDoc::~QFormDoc()
{
    delete ui;
}

void QFormDoc::loadFromFile(QString &aFileName)
{
    QString str;
    QFile aFile(aFileName);	// 以文件方式读出
    // 以只读文本方式打开文件
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream aStream(&aFile);	// 用文本流读取文件
        ui->plainTextEdit->clear();
        while (!aStream.atEnd()) {
            str = aStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
        }
        aFile.close();

        mCurrentFile = aFileName;
        QFileInfo fileInfo(aFileName);
        QString shorName = fileInfo.fileName();
        this->setWindowTitle(shorName);
    }
}

void QFormDoc::on_actOpen_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this, tr("打开一个文件"), curPath,
                 "C程序文件文件(*.h *cpp);;文本文件(*.txt);;所有文件(*.*)");
    if (aFileName.isEmpty()) {
        return;
    }
    loadFromFile(aFileName);
}

void QFormDoc::on_actFont_triggered()
{
    QFont font;
    font = ui->plainTextEdit->font();

    bool ok = false;
    font = QFontDialog::getFont(&ok, font);
    if (ok) {
        ui->plainTextEdit->setFont(font);
    }
}
