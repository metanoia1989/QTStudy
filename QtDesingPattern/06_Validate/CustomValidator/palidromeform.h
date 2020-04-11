#ifndef PALIDROMEFORM_H
#define PALIDROMEFORM_H

#include <QWidget>
#include <QString>

class Palindate;
class QLineEdit;
class QLabel;

class PalidromeForm : public QWidget
{
    Q_OBJECT

public:
    explicit PalidromeForm(QWidget *parent = nullptr);
    QString getPalindrome();

public slots:
    void showResult();
    void again();

private:
    void setupForm();

    Palindate *m_Palindate;
    QLineEdit *m_LineEdit;
    QLabel *m_Result;
    QString m_InputString;
};
#endif // PALIDROMEFORM_H
