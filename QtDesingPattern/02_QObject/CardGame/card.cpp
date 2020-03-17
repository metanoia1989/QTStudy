#include "card.h"
#include <QStringList>
#include <QLabel>

QStringList Card::s_Faces = QStringList()
            << "a" << "2" << "3" << "4"
            << "5" << "5" << "7" << "8"
            << "9" << "t" << "j" << "q"
            << "k";

QStringList Card::s_Suits = QStringList()
            << "c" << "d" << "h" << "s";

Card::Card(int faceNbr, int suitNbr)
    : m_FaceNbr(faceNbr), m_SuitNbr(suitNbr)
{

}

QString Card::getFace() const
{
    return s_Faces[m_FaceNbr];
}

QString Card::getSuit() const
{
    return s_Suits[m_SuitNbr];
}

QString Card::toString() const
{
    return QString("%1%2").arg(getFace()).arg(getSuit());
}

int Card::getValue() const
{
    switch(m_FaceNbr) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 3;
    case 3: return 4;
    case 4: return 5;
    case 5: return 6;
    case 6: return 7;
    case 7: return 8;
    case 8: return 9;
    default: return 10;
    }
}

QString Card::getImage() const
{
    return QString(":/images/%1.png").arg(toString());
}

QLabel* Card::getLabel()
{
    QLabel *label = new QLabel();
    label->setPixmap(getImage());
    label->setAlignment(Qt::AlignCenter);
    return label;
}
