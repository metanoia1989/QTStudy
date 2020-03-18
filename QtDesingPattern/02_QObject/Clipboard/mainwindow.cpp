#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(qApp->clipboard(), &QClipboard::changed, this,
            &MainWindow::clipboardChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clipboardChanged(QClipboard::Mode)
{
    QStringList sl;
    QClipboard *cb = qApp->clipboard();
    const QMimeData *md = cb->mimeData();
    sl << "Formats: " + md->formats().join(",");
    for (const QString& format : md->formats()) {
        QByteArray ba = md->data(format);
        sl << " " + format + ": " + QString(ba);
    }
    ui->clipboardContentsEdit->setText(sl.join("\n"));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
