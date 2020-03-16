#ifndef KEYSEQUENCELABEL_H
#define KEYSEQUENCELABEL_H

#include <QMainWindow>
#include <QList>
#include <QPair>

class QObjectBrowserAction;

QT_BEGIN_NAMESPACE
namespace Ui { class KeySequenceLabel; }
QT_END_NAMESPACE

class KeySequenceLabel : public QMainWindow
{
    Q_OBJECT

public:
    explicit KeySequenceLabel(QWidget *parent = nullptr);
    ~KeySequenceLabel();

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent *);
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void updateUi();

private slots:
    void on_actionShow_ObjectBrowser_triggered(bool checked);
    void on_m_clearButton_clicked();
    void on_actionQuit_triggered();

private:
    Ui::KeySequenceLabel *ui;
    QObjectBrowserAction *m_browserAction;
    QList<QPair<int, int>> m_keys;
    int m_paints;
};
#endif // KEYSEQUENCELABEL_H
