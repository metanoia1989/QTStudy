#include "mainwindow.h"
#include <QItemSelectionModel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createAction();
    createMenu();
    setupModel();
    setupView();
    setWindowTitle(tr("View Example"));
    resize(600, 600);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createAction()
{
    openAct = new QAction(tr("打开"), this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(slotOpen()));
}

void MainWindow::createMenu()
{
    fileMenu = new QMenu(tr("文件"), this);
    fileMenu->addAction(openAct);
    menuBar()->addMenu(fileMenu);
}

// 新建一个Model并设置表头数据
void MainWindow::setupModel()
{
    model = new QStandardItemModel(4, 4, this);
    model->setHeaderData(0, Qt::Horizontal, tr("部门"));
    model->setHeaderData(1, Qt::Horizontal, tr("男"));
    model->setHeaderData(2, Qt::Horizontal, tr("女"));
    model->setHeaderData(3, Qt::Horizontal, tr("退休"));
}

void MainWindow::setupView()
{
    QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
    splitter = new QSplitter;

    table = new QTableView;
    table->setModel(model);
    table->setSelectionModel(selectionModel);

    histogram = new HistogramView(splitter);
    histogram->setModel(model);
    histogram->setSelectionModel(selectionModel);

    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        table, SLOT(selectionChanged(const QItemSelection &, const QItemSelection &)));
    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        histogram, SLOT(selectionChanged(const QItemSelection &, const QItemSelection &)));

    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(table);
    splitter->addWidget(histogram);
    setCentralWidget(splitter);
}

void MainWindow::slotOpen()
{
    QString name;
    name = QFileDialog::getOpenFileName(this, " 打 开 ", ".", "histogram files(*.txt)");
    if (!name.isEmpty()) {
        openFile(name);
    }
}

void MainWindow::openFile(QString path)
{
    if (!path.isEmpty()) {
        QFile file(path);
        if (file.open(QFile::ReadOnly|QFile::Text)) {
            QTextStream stream(&file);
            QString line;
            model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
            int row = 0;
            do {
                line = stream.readLine();
                qDebug() << line;
                if (!line.isEmpty()) {
                    model->insertRows(row, 1, QModelIndex());
                    QStringList pieces = line.split(",", QString::SkipEmptyParts);
                    model->setData(model->index(row, 0, QModelIndex()), pieces.value(0));
                    model->setData(model->index(row, 1, QModelIndex()), pieces.value(1));
                    model->setData(model->index(row, 2, QModelIndex()), pieces.value(2));
                    model->setData(model->index(row, 3, QModelIndex()), pieces.value(3));
                    row++;
                }
            } while (!line.isEmpty());
            file.close();
        }
    }
}
