#include "listenThrd.h"
#include "global.h"


listenThrd::listenThrd()
{
	stopped = false;
    qRegisterMetaType<SOCKETINF>("SOCKETINF");

}
listenThrd::~listenThrd()
{

}


void listenThrd::listenPort()
{
//	struct timeval tv;
//	tv.tv_sec = 1;
//	tv.tv_usec = 0;

	//FD_SETSIZE

	//emit comming("listening...", DATA);
	WriteLog(QString::fromLocal8Bit("开始监听..."));
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(sockServer, &readfds);
	int nfds = sockServer + 1, ret;



    while (!stopped )
	{
		//nfds=FD_SETSIZE;
		ret = select(nfds, &readfds, NULL, NULL, NULL);//&tv);//         //阻塞执行,避免循环调用accept函数消耗资源
		if (ret > 0)
		{

            socklen_t length = sizeof(client_addr);
            newsocket = accept(sockServer, (struct sockaddr*)&client_addr, &length);
			if (newsocket == INVALID_SOCKET)
			{
				qDebug("wrong client");				
				WriteLog(QString::fromLocal8Bit("无效的socket"));
                continue;
			}

#ifdef WIN32
            QString cAddr = QString("%1.%2.%3.%4\n%5\nComming...").arg(client_addr.sin_addr.S_un.S_un_b.s_b1).
                arg(client_addr.sin_addr.S_un.S_un_b.s_b2).
                arg(client_addr.sin_addr.S_un.S_un_b.s_b3).
                arg(client_addr.sin_addr.S_un.S_un_b.s_b4).
                arg(ntohs(client_addr.sin_port));
#else
            cnt++;
            QString cAddr = QString("%1\n%2Comming...count is %3").arg(inet_ntoa(client_addr.sin_addr)).arg(client_addr.sin_port).arg(cnt);
#endif
             WriteLog(cAddr);
#ifdef WIN32
            QString sAddr = QString("Welcome to\n%1.%2.%3.%4\n%5").arg(addrServer.sin_addr.S_un.S_un_b.s_b1).
                arg(addrServer.sin_addr.S_un.S_un_b.s_b2).
                arg(addrServer.sin_addr.S_un.S_un_b.s_b3).
                arg(addrServer.sin_addr.S_un.S_un_b.s_b4).
                arg(ntohs(addrServer.sin_port));
#else
            QString sAddr = QString("Welcome to\n%1\n%2").arg(inet_ntoa(addrServer.sin_addr)).arg(addrServer.sin_port);
#endif

			//存入map
			SOCKETINF sInfTmp;
			sInfTmp.Skt = newsocket;
			sInfTmp.IPAddr = F5_ip;
			sInfTmp.Port = F5_port.toInt();
			sInfTmp.Status = true;
			sInfTmp.AcceptTime = QDateTime::currentDateTime();
            recvThrd* rcvThread = new recvThrd(newsocket);
            rcvThread->start();
            WriteLog(QString::fromLocal8Bit("监听到新设备"));
		}
	}
}

void listenThrd::stop()
{
    //shutdown(sockServer, 2);
    CloseSocket(sockServer);
	stopped = true;



}

void listenThrd::run()
{
	listenPort();
	stopped = false;
    //shutdown(sockServer, 2);
    CloseSocket(sockServer);
	sockServer = INVALID_SOCKET;
	qDebug("stop listen");
	
}
