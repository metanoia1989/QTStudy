#ifndef STUDY_H
#define STUDY_H

#include <QMainWindow>

class QAction;
class QActionGroup;

class Study : public QMainWindow
{
    Q_OBJECT

public:
    explicit Study(QWidget *parent = nullptr);

public slots:
    void actionEvent(QAction *act);

protected:
    /* 添加新的QAction到toolbar并且返回 */
    QAction* addChoice(QString name, QString text);

private:
    QActionGroup *actionGroup;
    QToolBar *toolbar;

    QAction *useTheForce;
    QAction *useTheDarkSide;
    QAction *studyWithObiWan;
    QAction *studyWithYoda;
    QAction *studyWithEmperor;
    QAction *fightYoda;
    QAction *fightDarthVader;
    QAction *fightObiWan;
    QAction *fightEmperor;
};
#endif // STUDY_H
