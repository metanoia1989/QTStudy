#include "study.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QMessageBox>
#include <QDebug>

Study::Study(QWidget *parent)
    : QMainWindow(parent)
{
    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(false);
    statusBar();

    setWindowTitle("to become a jedi, you wish?");

    QMenu *useMenu = new QMenu("&Use", this);
    QMenu *studyMenu = new QMenu("&Study", this);
    QMenu *fightMenu = new QMenu("&Fight", this);

    useTheForce = addChoice("useTheForce", "Use The &Force");
    useTheForce->setStatusTip("This is the start of a journey...");
    useTheForce->setEnabled(true);
    useMenu->addAction(useTheForce);

    useTheDarkSide = addChoice("useTheDarkSide", "Use the &Dark Side");
    useMenu->addAction(useTheDarkSide);
    useTheDarkSide->setStatusTip("It's unavoidable, like the Apple in eden...");

    studyWithObiWan = addChoice("studyWithObiWan", "&Study With Obi Wan");
    studyMenu->addAction(studyWithObiWan);
    studyWithObiWan->setStatusTip("He will certainly open doors for you...");

    fightObiWan = addChoice("fightObiWan", "Fight &Obi Wan");
    fightMenu->addAction(fightObiWan);
    fightObiWan->setStatusTip("You'll learn some tricks from him");

    studyWithYoda = addChoice("studyWithYoda", "Study with &Yoda");
    studyMenu->addAction(studyWithYoda);
    studyWithYoda->setStatusTip("He's the master, why wouldn't you?");

    fightYoda = addChoice("fightYoda", "Fight Y&oda");
    fightMenu->addAction(fightYoda);
    fightYoda->setStatusTip("What are you, nuts?");

    fightDarthVader = addChoice("fightDarthVader", "Fight Darth &Vader");
    fightMenu->addAction(fightDarthVader);

    fightEmperor = addChoice("fightEmperor", "Fight &Emperor");
    fightMenu->addAction(fightEmperor);

    studyWithEmperor = addChoice("studyWithEmperor", "Study With Emperor&r");
    studyMenu->addAction(studyWithEmperor);

    QMainWindow::menuBar()->addMenu(useMenu);
    QMainWindow::menuBar()->addMenu(studyMenu);
    QMainWindow::menuBar()->addMenu(fightMenu);

    toolbar = new QToolBar("Choice ToolBar", this);
    toolbar->addActions(actionGroup->actions());

    QMainWindow::addToolBar(Qt::LeftToolBarArea, toolbar);

    connect(actionGroup, &QActionGroup::triggered, this,
            &Study::actionEvent);

    move(300, 300);
    resize(300, 300);
}

QAction* Study::addChoice(QString name, QString text)
{
    QAction *retval = new QAction(text, this);
    retval->setObjectName(name);
    retval->setEnabled(false);
    retval->setCheckable(true);
    actionGroup->addAction(retval);
    return retval;
}

void Study::actionEvent(QAction *act)
{
    QString name = act->objectName();
    QString msg = QString();

    if (act == useTheForce) {
        studyWithObiWan->setEnabled(true);
        fightObiWan->setEnabled(true);
        useTheDarkSide->setEnabled(true);
    } else if (act == useTheDarkSide) {
        studyWithYoda->setEnabled(false);
        fightYoda->setEnabled(true);
        studyWithEmperor->setEnabled(true);
        fightEmperor->setEnabled(true);
        fightDarthVader->setEnabled(true);
    } else if (act == studyWithObiWan) {
        fightObiWan->setEnabled(true);
        fightDarthVader->setEnabled(true);
        studyWithYoda->setEnabled(true);
    } else if (act == studyWithYoda) {
        fightDarthVader->setEnabled(true);
        fightEmperor->setEnabled(true);
    } else if (act == fightYoda) {
        msg = "You Lose.";
        act->setChecked(false);
        studyWithYoda->setEnabled(false);
    } else if (act == fightObiWan) {
        if (studyWithEmperor->isChecked()) {
            msg = "You are victorious!";
        } else {
            msg = "You lose.";
            act->setChecked(false);
            studyWithYoda->setEnabled(false);
        }
    } else if (act == fightDarthVader) {
        if (studyWithYoda->isChecked() == false) {
            msg = "Off with your hand! Chop!";
            act->setChecked(false);
        } else {
            msg = "You whupped some Vader ass!";
            studyWithEmperor->setEnabled(false);
            studyWithYoda->setEnabled(true);
        }
    } else if (act == studyWithEmperor) {
        studyWithEmperor->setChecked(true);
    } else if (act == fightEmperor) {
        if (fightObiWan->isChecked()) {
            msg = "You defeated the evil emperor!";
        } else {
            msg = "You've been burned to a crisp.";
            studyWithEmperor->setEnabled(false);
            fightEmperor->setChecked(false);
        }
    }

    if (msg != QString())
        QMessageBox::information(this, "Result", msg, "ok");
}
