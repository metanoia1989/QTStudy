#ifndef CARDDECK_H
#define CARDDECK_H

#include <QList>
#include "card.h"
#include "cardhand.h"

class CardDeck : public QList<Card*>
{
public:
    CardDeck();
    ~CardDeck();
    CardHand* deal(int handSize);
    QString toString();
    int getCardsLeft() const;
    void shuffleDeck();
};

#endif // CARDDECK_H
