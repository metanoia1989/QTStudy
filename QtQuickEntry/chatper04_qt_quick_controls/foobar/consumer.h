#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QThread>

class Consumer : public QThread
{
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = nullptr);
    void run() override;

signals:

};

#endif // CONSUMER_H
