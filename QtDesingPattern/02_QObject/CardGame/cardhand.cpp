#include "cardhand.h"

CardHand::~CardHand()
{
    qDeleteAll(*this);
    clear();
}

int CardHand::getValue()
{
    int value = 0;
    for (Card *card : *this) {
        if (card->getFace() == "a")
            gotAce = true;
        value += card->getValue();
    }
    if ((value <= 11) && (gotAce == true))
        value += 10;
    return value;
}

QString CardHand::toString()
{
    QString cards;
    for (Card *card : *this)
        cards.append(card->toString() + ", ");
    return cards;
}

QList<QLabel*> CardHand::getLabels()
{
    QList<QLabel*> labels;
    for (Card* card : *this)
        labels.append(card->getLabel());
    return labels;
}
