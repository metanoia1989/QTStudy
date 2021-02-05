#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QSimpleUpdater;

namespace Ui {
class MainWidget;
}


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void checkAppUpdate();

private:
    Ui::MainWidget *ui;

    QSimpleUpdater *m_updater;
};

#endif // MAINWIDGET_H
