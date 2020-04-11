#ifndef PALINDATE_H
#define PALINDATE_H

#include <QValidator>
#include <QString>

class Palindate : public QValidator
{
    Q_OBJECT
public:
    explicit Palindate(QObject *parent = nullptr);
    QValidator::State validate(QString& input, int& pos) const;
};

#endif // PALINDATE_H
