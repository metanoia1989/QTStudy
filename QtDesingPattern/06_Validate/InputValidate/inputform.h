#ifndef INPUTFORM_H
#define INPUTFORM_H

#include <QWidget>

class QLineEdit;
class QLabel;

class InputForm : public QWidget
{
    Q_OBJECT

public:
    InputForm(int ibot, int itop, double dbot, double dtop, QWidget *parent = nullptr);

public slots:
    void computeResult();

private:
    void setupForm();

    int m_BotI, m_TopI;
    double m_BotD, m_TopD;
    QLineEdit *m_IntEntry;
    QLineEdit *m_DoubleEntry;
    QLabel *m_Result;
};
#endif // INPUTFORM_H
