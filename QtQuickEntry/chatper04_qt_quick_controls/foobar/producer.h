#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>
#include <QThread>

class Producer : public QThread
{
    Q_OBJECT
public:
    explicit Producer(QObject *parent = nullptr);
    void run() override;

signals:

};

#endif // PRODUCER_H
