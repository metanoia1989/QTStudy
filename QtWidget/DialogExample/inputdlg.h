#ifndef INPUTDLG_H
#define INPUTDLG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class InputDlg : public QDialog
{
    Q_OBJECT
public:
    InputDlg(QWidget* parent=nullptr);
private:
    QLabel *nameLabel1;
    QLabel *sexLabel1;
    QLabel *ageLabel1;
    QLabel *scoreLabel1;
    QLabel *nameLabel2;
    QLabel *sexLabel2;
    QLabel *ageLabel2;
    QLabel *scoreLabel2;
    QPushButton *nameBtn;
    QPushButton *sexBtn;
    QPushButton *ageBtn;
    QPushButton *scoreBtn;
    QGridLayout *mainLayout;

private slots:
    void ChangeName();
    void ChangeSex();
    void ChangeAge();
    void ChangeScore();
};

#endif // INPUTDLG_H
