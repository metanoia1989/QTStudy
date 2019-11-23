#include "widget.h"
#include "ui_widget.h"
#include <QTextDocument>
#include <QTextBlock>
#include <QMenu>
#include <QMap>
#include <QVariant>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

// 初始化列表按钮，初始化下拉列表框的列表内容
void Widget::on_btnIniItems_clicked()
{
    QIcon icon;
    icon.addFile(":/images/icons/aim.ico");
    ui->comboBox->clear();
    for (int i = 0;i < 20; i++) {
        ui->comboBox->addItem(icon, QString::asprintf("Item %d", i)); // 带图标
//        ui->comboBox->addItem(QString::asprintf("Item %d", i)); // 不带图标
    }
//    QStringList strList;
//    strList << "北京" << "上海" << "天津" << "河北省" << "山东省" << "山西省";
//    ui->comboBox->addItems(strList);	// 添加字符串列表项
}

// 初始化城市+区号，添加自定义数据
// QMap 自动根据 key 排序
void Widget::on_btnIni2_clicked()
{
    QMap<QString, int> CityZone;
    CityZone.insert("北京", 10);
    CityZone.insert("上海", 21);
    CityZone.insert("天津", 22);
    CityZone.insert("大连", 411);
    CityZone.insert("锦州", 416);
    CityZone.insert("徐州", 516);
    CityZone.insert("福州", 591);
    CityZone.insert("青岛", 532);
    ui->comboBox2->clear();
    foreach(const QString& str, CityZone.keys()) {
        ui->comboBox2->addItem(str, CityZone.value(str));
    }
}

// QComboBox 组件上选择项发生变化时的槽函数
// comboBox 选择一个条目时，文本添加到 plainTextEdit
void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}

// comboBox2 选择一个条目时，将用户数据添加到 plainTextEdit
void Widget::on_comboBox2_currentIndexChanged(const QString &arg1)
{
    QString zone = ui->comboBox2->currentData().toString();
    ui->plainTextEdit->appendPlainText(arg1 + ": 区号=" + zone);
}

// 清除条目
void Widget::on_btnClearItems_clicked()
{
    ui->comboBox->clear();
}


// 切换 comboBox 可编辑
void Widget::on_chkBoxEditable_clicked(bool checked)
{
    ui->comboBox->setEditable(checked);
}

// 文本框内容都添加到ComboBox按钮被点击
// plainTextEdit 的内容逐行添加为 comboBox 的条目
void Widget::on_btnToComboBox_clicked()
{
    // 将 QPlainTextEdit 的内容保存在一个 QTextDocument 里
    QTextDocument* doc = ui->plainTextEdit->document();
    // QTextDocument 分块保存内容，文本文件就是硬回车符是一个block
    int cnt = doc->blockCount();

    QIcon icon(":/images/icons/aim.ico");
    ui->comboBox->clear();
    // 扫描所有 block
    for (int i = 0; i < cnt; i++) {
        // 用 block 编号获取 block，就是获取一行
        QTextBlock textLine = doc->findBlockByNumber(i);
        QString str = textLine.text(); // 转换为文本
        ui->comboBox->addItem(icon, str);	// 添加一个条目到 comboBox
    }
}

// 创建并显示标准弹出菜单
void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    // 创建标准右键菜单
    QMenu* menu = ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);	// 在鼠标光标位置显示右键快捷菜单
//    menu->exec(QCursor::pos());
}


// 清除文本框
void Widget::on_btnClearText_clicked()
{
    ui->plainTextEdit->clear();
}

// 设置 plainTextEdit 的 ReadOnly 属性
void Widget::on_chkBoxReadonly_clicked(bool checked)
{
    ui->plainTextEdit->setReadOnly(checked);
}

