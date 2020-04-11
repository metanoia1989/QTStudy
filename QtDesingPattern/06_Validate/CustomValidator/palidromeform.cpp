#include "palidromeform.h"
#include <QtWidgets>
#include "palindate.h"

PalidromeForm::PalidromeForm(QWidget *parent)
    : QWidget(parent)
    , m_Palindate(new Palindate)
    , m_LineEdit(new QLineEdit)
    , m_Result(new QLabel)
{
    setupForm();
}

void PalidromeForm::setupForm()
{
    setWindowTitle("Palindrome Checker");
    m_LineEdit->setValidator(m_Palindate);
    connect(m_LineEdit, &QLineEdit::returnPressed, this,
            &PalidromeForm::showResult);
    connect(m_LineEdit, &QLineEdit::textChanged, this,
            &PalidromeForm::showResult);

    QPushButton *againButton = new QPushButton("Another Palindrome", this);
    QPushButton *quitButton = new QPushButton("Quit", this);
    QFormLayout *formL = new QFormLayout(this);
    formL->addRow("String to test: ", m_LineEdit);
    formL->addRow("Result: ", m_Result);
    QHBoxLayout *hBox = new QHBoxLayout;
    formL->addRow(hBox);
    hBox->addWidget(againButton);
    hBox->addWidget(quitButton);
    m_Result->setFrameStyle(QFrame::Panel);
    m_Result->setFrameShadow(QFrame::Raised);

    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(againButton, &QPushButton::clicked, this, &PalidromeForm::again);

    move(500, 500);
}

void PalidromeForm::showResult()
{
    QString str = m_LineEdit->text();
    int pos(0);
    if (m_Palindate->validate(str, pos) == QValidator::Acceptable) {
        m_InputString = str;
        m_Result->setText("Valid Palindrome!");
    } else {
        m_InputString = "";
        m_Result->setText("Not a Palindrome!");
    }
}

void PalidromeForm::again()
{
    m_LineEdit->clear();
    m_Result->setText("");
    m_LineEdit->setFocus();
}
