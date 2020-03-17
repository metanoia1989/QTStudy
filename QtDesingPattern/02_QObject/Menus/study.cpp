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
}
