#include "masktestform.h"
#include <QtWidgets>

MaskTestForm::MaskTestForm(QWidget *parent)
    : QWidget(parent)
    , m_InputMask(new QLineEdit)
    , m_StringEntry(new QLineEdit)
    , m_Result(new QLabel)
{
    setupForm();
    move(500, 500);
}

void MaskTestForm::setupForm()
{
    setWindowTitle("Mask Test Demo");
    QPushButton *againButton = new QPushButton("Another Input Mask", this);
    QPushButton *quitButton = new QPushButton("Quit", this);
    QFormLayout *form = new QFormLayout(this);
    form->addRow("Mask String: ", m_InputMask);
    form->addRow("Test Input: ", m_StringEntry);
    form->addRow("Result: ", m_Result);

    QHBoxLayout *hBox = new QHBoxLayout;
    form->addRow(hBox);
    hBox->addWidget(againButton);
    hBox->addWidget(quitButton);

    m_Result->setFrameStyle(QFrame::Panel);
    m_Result->setFrameShadow(QFrame::Raised);

    connect(m_InputMask, &QLineEdit::returnPressed, this,
            &MaskTestForm::installMask);
    connect(m_InputMask, &QLineEdit::textChanged, this,
            &MaskTestForm::installMask);
    connect(m_StringEntry, &QLineEdit::returnPressed, this,
            &MaskTestForm::showResult);
    connect(m_StringEntry, &QLineEdit::textChanged, this,
            &MaskTestForm::showResult);
    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(againButton, &QPushButton::clicked, this, &MaskTestForm::again);
}

void MaskTestForm::installMask()
{
    m_StringEntry->setInputMask(m_InputMask->text());
}

void MaskTestForm::showResult()
{
    QString str = m_StringEntry->text();
    m_Result->setText(str);
}

void MaskTestForm::again()
{
    m_StringEntry->clear();
    m_Result->setText("");
    m_StringEntry->setFocus();
}
