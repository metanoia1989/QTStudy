#ifndef MSGBOXDLG_H
#define MSGBOXDLG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>


class MsgBoxDlg : public QDialog
{
    Q_OBJECT
public:
    MsgBoxDlg(QWidget* parent=nullptr);

private:
    QLabel *label;
    QPushButton *questionBtn;
    QPushButton *informationBtn;
    QPushButton *warningBtn;
    QPushButton *criticalBtn;
    QPushButton *aboutBtn;
    QPushButton *aboutQtBtn;
    QGridLayout *mainLayout;

private slots:
    void showQuestionMsg();
    void showInformationMsg();
    void showWarningMsg();
    void showCriticalMsg();
    void showAboutMsg();
    void showAboutQtMsg();
};

#endif // MSGBOXDLG_H
