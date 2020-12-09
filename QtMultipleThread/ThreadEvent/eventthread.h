#pragma once

#include <QThread>

class EventThread : public QThread
{
    Q_OBJECT
public:
    EventThread();

protected:
    void run() override;

signals:
    void sendData(QString content);
};

