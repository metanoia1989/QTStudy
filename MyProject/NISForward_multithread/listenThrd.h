#ifndef listenThrd_H
#define listenThrd_H

#include <QMetaType>
#include "global.h"
#include "recvThrd.h"

//监听F5传来的数据


class listenThrd : public QThread
{
	Q_OBJECT

public:
	listenThrd();
	~listenThrd();

	void stop();


signals:       
	void showText(QString txt);
	void comming(QString txt, int type);
    void newDeviceCome(SOCKETINF temp);

protected:
	void run();



private:
	void listenPort();
	volatile bool stopped;
    int cnt;
};

#endif 
