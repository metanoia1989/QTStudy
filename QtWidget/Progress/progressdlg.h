#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>


class ProgressDlg : public QDialog
{
    Q_OBJECT

public:
    ProgressDlg(QWidget *parent = nullptr);
    ~ProgressDlg();

private:
    QLabel *FileNum;
    QLineEdit *FileNumLineEdit;
    QLabel *ProgressType;
    QComboBox *comboBox;
    QProgressBar *progressBar;
    QPushButton *starBtn;
    QGridLayout *mainLayout;

private slots:
    void startProgress();
};

#endif // PROGRESSDLG_H
