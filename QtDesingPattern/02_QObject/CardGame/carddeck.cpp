#include "carddeck.h"
#include <cstdlib>
#include <chrono>
#include <memory>
#include <algorithm>
#include <random>
#include <QtAlgorithms>
#include <QDebug>

static int const SUIT_NUM = 4;
static int const FACE_NUM = 13;

CardDeck::CardDeck()
{
    shuffleDeck();
}

CardDeck::~CardDeck()
{
    qDeleteAll(*this);
    clear();
}

// 随机取出卡片，回手
CardHand* CardDeck::deal(int handSize)
{
    CardHand *hand = new CardHand();

    // 如果我们的卡片用完了
    if (handSize > count()) {
        qDebug() << "\n*~ We're out of cards, restoring deck...~*\n";
        shuffleDeck();
    }

    for (int i = 0; i < handSize; i++) {
        hand->append(last());
        removeLast();
    }
    return hand;
}

QString CardDeck::toString()
{
    QString str;
    for (Card *card : *this)
        str.append(card->toString() + ", ");
    return str;
}

void CardDeck::shuffleDeck()
{
    if (!isEmpty()) {
        qDeleteAll(*this);
        clear();
    }
    for (int suit = 0; suit < SUIT_NUM; suit++) {
        for (int face = 0; face < FACE_NUM; face++)
            append(new Card(face, suit));
    }
    unsigned seed = std::chrono::system_clock::now()
                        .time_since_epoch().count();
    std::shuffle(begin(), end(), std::default_random_engine(seed));
}

int CardDeck::getCardsLeft() const
{
    return count();
}
