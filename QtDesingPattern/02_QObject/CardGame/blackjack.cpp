#include "blackjack.h"
#include "./ui_blackjack.h"
#include "carddeck.h"
#include "cardhand.h"
#include <QMessageBox>
#include <QDebug>

static const int MAX_COLUMN = 2;

BlackJack::BlackJack(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BlackJack)
{
    ui->setupUi(this);

    deck = new CardDeck();

    playerHand = nullptr;
    dealerHand = nullptr;

    // 连接QAction到Toolbar上的按钮
    ui->tb_newGame->setDefaultAction(ui->actionNewGame);
    ui->tb_dealHand->setDefaultAction(ui->actionDeal_Hand);
    ui->tb_shuffleDeck->setDefaultAction(ui->actionShuffle_Deck);
    ui->tb_hit_me->setDefaultAction(ui->actionHit_Me);
    ui->tb_stay->setDefaultAction(ui->actionStay);

    // 连接QActions到槽函数
    connect(ui->actionNewGame, &QAction::triggered, this,
            &BlackJack::newGame);
    connect(ui->actionDeal_Hand, &QAction::triggered, this,
            &BlackJack::dealHand);
    connect(ui->actionShuffle_Deck, &QAction::triggered, this,
            &BlackJack::shuffleDeck);
    connect(ui->actionHit_Me, &QAction::triggered, this,
            &BlackJack::hitMe);
    connect(ui->actionStay, &QAction::triggered, this,
            &BlackJack::stay);

    dealHand();
}

BlackJack::~BlackJack()
{
    delete playerHand;
    delete dealerHand;
    delete deck;
    delete ui;
}

void BlackJack::handOver()
{
    qDebug() << "Player's hand is now " << playerHand->getValue();
    qDebug() << "dealer's hand is now " << dealerHand->getValue();

    ui->actionHit_Me->setDisabled(true);
    ui->actionStay->setDisabled(true);

    if (dealerHand->getValue() == 21) {
        finalDecision("Dealer gets blackjack. Dealer wins!", ui->sb_dealerScore);
        return;
    }
    if (playerHand->getValue() > 21) {
        finalDecision("You exceeded 21 thus have lost", ui->sb_dealerScore);
        return;
    }
    if (playerHand->getValue() == 21) {
        finalDecision("BlackJack! :D", ui->sb_playerScore);
        return;
    }
    if (dealerHand->getValue() > 21) {
        finalDecision("Dealer exceeds 21. You win!", ui->sb_playerScore);
        return;
    }

    if (playerHand->count() >= 5) {
        finalDecision("5 cards?? You win!", ui->sb_playerScore);
        return;
    }

    if (dealerHand->getValue() >= playerHand->getValue()) {
        finalDecision("Dealer hand equal or exceeds player hand. Dealer Wins!",
                      ui->sb_dealerScore);
    } else {
        finalDecision("Player hand exceeds dealer. Player wins!",
                      ui->sb_playerScore);
    }
}

void BlackJack::finalDecision(QString message, QSpinBox *spinbox, int score)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
    spinbox->setValue(spinbox->value() + score);
}

void BlackJack::refreshImages(CardHand *hand, QGridLayout *layout)
{
    while (!layout->isEmpty())
        delete layout->itemAt(0)->widget();

    QList<QLabel*> labels = hand->getLabels();
    for (int i = 0; i < labels.count(); i++) {
        layout->addWidget(labels[i], i/MAX_COLUMN, i % MAX_COLUMN, 1, 1);
    }
}

void BlackJack::newGame()
{
    qDebug() << "new game";

    ui->sb_dealerScore->setValue(0);
    ui->sb_playerScore->setValue(0);

    shuffleDeck();
    dealHand();
}

void BlackJack::dealHand()
{
    qDebug() << "Deal hand...";
    ui->actionDeal_Hand->setDisabled(true);

    ui->actionHit_Me->setEnabled(true);
    ui->actionStay->setEnabled(true);

    if (playerHand != nullptr || dealerHand != nullptr) {
        delete playerHand;
        delete  dealerHand;
        playerHand = nullptr;
        dealerHand = nullptr;
    }

    if (deck->count() <= 4) {
        qDebug() << "insufficient amount of cards...";
        shuffleDeck();
    }

    playerHand = deck->deal(2);
    dealerHand = deck->deal(2);

    refreshImages(playerHand, ui->layout_player);
    refreshImages(dealerHand, ui->layout_dealer);

    qDebug() << "player hand: " << playerHand->toString();
    qDebug() << QString("dealer hand: %1 thus value of %2")
                    .arg(dealerHand->toString())
                    .arg(dealerHand->getValue());
    ui->sb_cardsLeft->setValue(deck->getCardsLeft());
}

void BlackJack::shuffleDeck()
{
    qDebug() << "shuffling deck...";
    deck->shuffleDeck();
    ui->sb_cardsLeft->setValue(deck->getCardsLeft());
}

void BlackJack::hitMe()
{
    if (deck->count() <= 1) {
        qDebug() << "insufficient amount of cards...";
        shuffleDeck();
    }
    qDebug() << "Adding card...";
    playerHand->append(deck->last());
    deck->removeLast();
    qDebug() << "playerHand now has " << playerHand->toString();
    ui->sb_cardsLeft->setValue(deck->getCardsLeft());
    refreshImages(playerHand, ui->layout_player);
}

void BlackJack::stay()
{
    qDebug() << "Now dealer's trun...";
    while (dealerHand->getValue() <= 18) {
        dealerHand->append(deck->last());
        qDebug() << "Dealer adds a card: " << deck->last()->toString();
        deck->removeLast();
    }
    ui->sb_cardsLeft->setValue(deck->getCardsLeft());
    refreshImages(dealerHand, ui->layout_dealer);
    handOver();
    ui->actionDeal_Hand->setEnabled(true);
}
