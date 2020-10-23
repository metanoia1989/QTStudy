#ifndef DTKMAINWINDOW_H
#define DTKMAINWINDOW_H

#include <DMainWindow>
#include <DPushButton>
#include <QPushButton>

DWIDGET_USE_NAMESPACE

class DTKMainWindow : public DMainWindow
{
    Q_OBJECT

public:
    DTKMainWindow(QWidget *parent = nullptr);
    ~DTKMainWindow();

    DPushButton *dBtnStyle;
    DPushButton *dBtnNone;
    QPushButton *qBtnStyle;
    QPushButton *qBtnNone;
};
#endif // DTKMAINWINDOW_H
