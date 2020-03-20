#ifndef FRACTION_H
#define FRACTION_H

#include <QPair>
#include <QString>
#include <QMetaType>

class QTextStream;
class QDataStream;

class Fraction : public QPair<qint32, qint32>
{
public:
    Fraction(qint32 n = 0, qint32 d = 1)
        : QPair<qint32, qint32>(n, d) { }
};

Q_DECLARE_METATYPE(Fraction);

QTextStream& operator<<(QTextStream& os, const Fraction& fr);
QDataStream& operator<<(QDataStream& os, const Fraction& fr);
QDataStream& operator>>(QDataStream& is, const Fraction& fr);

#endif // FRACTION_H
