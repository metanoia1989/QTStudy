#include "widget.h"
#include "ui_widget.h"

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

// append()函数
void Widget::on_btnAppend_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    str2 = ui->comboBox2->currentText();
    str1.append(str2);
    ui->edtResult->setText(str1);
}

// prepend()函数
void Widget::on_btnPrepend_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    str2 = ui->comboBox2->currentText();
    str1.prepend(str2);
    ui->edtResult->setText(str1);
}

// toUpper() 函数
void Widget::on_btnToUpper_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    str2 = str1.toUpper();

    ui->edtResult->setText(str2);
}

void Widget::on_btnbtnToLower_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    str2 = str1.toLower();

    ui->edtResult->setText(str2);
}

// left() 函数
void Widget::on_btnLeft_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    int v = ui->spinBox->value();
    str2 = str1.left(v);
    ui->edtResult->setText(str2);
}

// right() 函数
void Widget::on_btnRight_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    int cnt = str1.size();
    int v = ui->spinBox->value();
    str2 = str1.left(cnt - v - 1);
    ui->edtResult->setText(str2);
}

// section() 函数
void Widget::on_btnSection_clicked()
{
    int i;
    QString str1, str2, str3;
    str1 = ui->comboBox1->currentText();
    i = ui->spinBox->value();
    str3 = ui->comboBox2->currentText();
    if (QString::compare(str3, "\\", Qt::CaseInsensitive) == 0){
        str2 = str1.section("\\", i, i+2);
    } else {
        str2 = str1.section(str3, i, i+1);
    }
    ui->edtResult->setText(str2);
}

// simplified()函数
void Widget::on_btnSimplified_clicked()
{
    QString str1;
    str1 = ui->comboBox1->currentText();
    str1 = str1.simplified();
    ui->edtResult->setText(str1);
}

// trimmed() 函数
void Widget::on_btnTrimmed_clicked()
{
    QString str1;
    str1 = ui->comboBox1->currentText();
    str1 = str1.trimmed();

    ui->edtResult->setText(str1);
}

// count() 函数
void Widget::on_btnCount_clicked()
{
    QString str1 = ui->comboBox1->currentText();
    int i = str1.count();
    //int i = str.length();
    ui->spinBox->setValue(i);
    ui->LabSpin->setText("count()");
}

// size() 函数
void Widget::on_btnSize_clicked()
{
    QString str1;
    str1 = ui->comboBox1->currentText();
    int i = str1.size();
    ui->spinBox->setValue(i);
    ui->LabSpin->setText("size()");
}

// indexOf() 函数
void Widget::on_btnIndexOf_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    str2 = ui->comboBox2->currentText();

    int i;
    i = str1.indexOf(str2);
    ui->spinBox->setValue(i);
    ui->LabSpin->setText("indexOf()");
}

// lastIndexOf() 函数
void Widget::on_btnLastIndexOf_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    str2 = ui->comboBox2->currentText();

    int i;
    i = str1.lastIndexOf(str2);
    ui->spinBox->setValue(i);
    ui->LabSpin->setText("lastIndexOf()");
}

// endsWith() 函数
void Widget::on_btnEndsWith_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    str2 = ui->comboBox2->currentText();

    bool chk;
    chk = str1.endsWith(str2);
    ui->checkBox->setChecked(chk);
    ui->checkBox->setText("endsWith()");
    ui->checkBox->sizeHint();
}

// startsWith() 函数
void Widget::on_btnStartsWith_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    str2 = ui->comboBox2->currentText();

    bool chk;
    chk = str1.startsWith(str2);
    ui->checkBox->setChecked(chk);
    ui->checkBox->setText("startsWith()");
    ui->checkBox->sizeHint();
}

// contains() 函数
void Widget::on_btnContains_clicked()
{
    QString str1, str2;
    str1 = ui->comboBox1->currentText();
    str2 = ui->comboBox2->currentText();

    bool chk;
    chk = str1.contains(str2);
    ui->checkBox->setChecked(chk);
    ui->checkBox->setText("contains()");
    ui->checkBox->sizeHint();
}

// isNull() 函数
void Widget::on_btnIsNull_clicked()
{
    QString str1;
    str1 = ui->comboBox1->currentText();

    bool chk;
    chk = str1.isNull();
    ui->checkBox->setChecked(chk);
    ui->checkBox->setText("isNull()");
    ui->checkBox->sizeHint();
}

// isEmpty() 函数
void Widget::on_btnIsEmpty_clicked()
{
    QString str1;
    str1 = ui->comboBox1->currentText();

    bool chk;
    chk = str1.isEmpty();
    ui->checkBox->setChecked(chk);
    ui->checkBox->setText("isEmpty()");
    ui->checkBox->sizeHint();
}
