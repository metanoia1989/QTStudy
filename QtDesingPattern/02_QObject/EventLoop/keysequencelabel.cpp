#include "keysequencelabel.h"
#include "./ui_keysequencelabel.h"
#include "./lib/objectbrowser/qobjectbrowseraction.h"
#include <QtGui>

KeySequenceLabel::KeySequenceLabel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KeySequenceLabel)
    , m_browserAction(new QObjectBrowserAction(this))
    , m_paints{0}
{
    ui->setupUi(this);
    startTimer(2000);
}

KeySequenceLabel::~KeySequenceLabel()
{
    delete ui;
}

// start id = "timer"
void KeySequenceLabel::timerEvent(QTimerEvent *)
{
    ui->m_lcdNumber->display(m_paints);
}

void KeySequenceLabel::paintEvent(QPaintEvent *event)
{
    ++m_paints;
    QMainWindow::paintEvent(event);
}
// end

// start id = "keyevent"
void KeySequenceLabel::keyPressEvent(QKeyEvent *event)
{
    bool doNothing = false;
    if (event->key() == 0) doNothing = true;
    if (m_keys.size() > 3) doNothing = true;
    if (doNothing) {
        QMainWindow::keyPressEvent(event);
        return;
    }
    QPair<int, int> pair = QPair<int, int>(event->modifiers(), event->key());
    m_keys << pair;
    event->accept();
    updateUi();
}

void KeySequenceLabel::updateUi()
{
    if (!m_keys.isEmpty()) {
        int keys[4] {0, 0, 0, 0};
        for (int i = 0; i < m_keys.size(); ++i) {
            QPair<int, int> pair = m_keys[i];
            keys[i] = pair.first | pair.second;
        }
        QKeySequence seq = QKeySequence(keys[0], keys[1], keys[2], keys[3]);
        ui->m_label->setText(seq.toString());
    } else {
        ui->m_label->clear();
    }
}
// end

// start id = "enterleave"
void KeySequenceLabel::enterEvent(QEvent *event)
{
    statusBar()->showMessage(tr("Mouse is in da house"));
    event->accept();
}

void KeySequenceLabel::leaveEvent(QEvent *event)
{
    statusBar()->showMessage(tr("Mouse has left the building"));
    event->accept();
}
// end

void KeySequenceLabel::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void KeySequenceLabel::on_actionQuit_triggered()
{
    qApp->quit();
}

void KeySequenceLabel::on_m_clearButton_clicked()
{
    m_keys.clear();
    updateUi();
}

void KeySequenceLabel::on_actionShow_ObjectBrowser_triggered(bool checked)
{
    m_browserAction->setChecked(checked);
}
