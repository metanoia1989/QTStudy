#ifndef MASKTESTFORM_H
#define MASKTESTFORM_H

#include <QWidget>
#include <QString>

class QLineEdit;
class QLabel;

class MaskTestForm : public QWidget
{
    Q_OBJECT

public:
    explicit MaskTestForm(QWidget *parent = nullptr);

public slots:
    void showResult();
    void installMask();
    void again();

private:
    void setupForm();

    QLineEdit *m_InputMask;
    QLineEdit *m_StringEntry;
    QLabel *m_Result;
};
#endif // MASKTESTFORM_H
