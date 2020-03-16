#ifndef RECVTHRD_H
#define RECVTHRD_H


#include "global.h"
#include <QDebug>
#include <map>

class recvThrd : public QThread
{
	Q_OBJECT

public:
    recvThrd(int skt_FT);
	~recvThrd();


	void stop();

    bool init();
    void  Recv_Send_Deal();
    bool judgeConnection();

protected:
	void run();

private:



	volatile bool stopped;
    unsigned char RcvBuff[512];
    int skt_ft;
    int skt_nis;
    int Timer;


};

#endif 
