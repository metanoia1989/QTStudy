#ifndef GLOBAL_H
#define GLOBAL_H

#include <QMap>
#include <QObject>
#include <QFile>
//#include <WS2tcpip.h>
#include  <QCoreApplication>
#include <QThread>
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>
#ifdef WIN32 
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib"  )
#else
#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <arpa/inet.h>
#include <signal.h>
//#include <sys/ioctl.h>
#endif

//全局变量

extern QMutex My_mutex;
enum { CLIENT, DATA };
extern int sockServer, newsocket;//SOCKET sockServer;

extern unsigned char Buf[300];
#ifdef WIN32
extern SOCKADDR_IN addrServer;
extern SOCKADDR_IN client_addr;
#else
extern sockaddr_in addrServer;
extern sockaddr_in client_addr;
#endif
#ifndef WIN32
#define byte unsigned char
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#endif


extern QCoreApplication* App;
extern QString F5_ip;
extern QString F5_port;
extern QString NIS_ip;
extern QString NIS_port;

extern int CntWaitTime_secs;     
extern int CntWaitTime_msecs;
extern QString  exepath;
extern void WriteLog(QString szlog);







typedef struct
{
	unsigned char    Sec;
	unsigned char    Min;
	unsigned char    Hour;
	unsigned char    Day;
	unsigned char    Month;
	unsigned short   Year;
	unsigned short   mSec;
}CP56TIME;




typedef struct
{
	int NIS_Skt;
	int DEV_Skt;
	int Add_ID;
	QString BCD_ID;
}DEV_TRANC;


typedef struct
{
	bool Status;
	int  Skt;
	int  Port;
	//int  AcceptTime;
	QString IPAddr;
	QDateTime AcceptTime;
}SOCKETINF;

//extern QMap<int, SOCKETINF> SocketList;
//extern QMap<QString, DEV_TRANC> DevSkt;

inline QString GetLow(QString TempStr)
{
	QString Ret = "";
	std::string StrTmp = TempStr.toStdString();
	for (int i = 0; i<StrTmp.length(); i++)
	{
		char word;
		if (StrTmp.data()[i] >= 'A' && StrTmp.data()[i] <= 'Z')
			word = StrTmp.data()[i] + 0x20;
		else
			word = StrTmp.data()[i];
		Ret += word;
	}
	return Ret;
}

inline int MyRcv(int fd, char* Buf, int Len)
{
#ifdef WIN32
	return recv(fd, Buf, Len, 0);
#else
    sigset_t signal_mask;
    sigemptyset(&signal_mask);
    sigaddset(&signal_mask, SIGPIPE);
    int rc = pthread_sigmask(SIG_BLOCK, &signal_mask, NULL);
    if (rc != 0) {
        WriteLog("block sigpipe error/n");
    }
	return recv(fd, Buf, Len, MSG_DONTWAIT);
#endif
}

inline int MySnd(int fd, char* Buf, int Len)
{
#ifdef WIN32
	return send(fd, Buf, Len, 0);
#else
    sigset_t signal_mask;
    sigemptyset(&signal_mask);
    sigaddset(&signal_mask, SIGPIPE);
    int rc = pthread_sigmask(SIG_BLOCK, &signal_mask, NULL);
    if (rc != 0) {
        WriteLog("block sigpipe error/n");
    }
    return send(fd, Buf, Len, MSG_DONTWAIT|MSG_NOSIGNAL);
#endif
}

inline void CloseSocket(int sockfd)
{
#ifdef _WIN32
	shutdown(sockfd, 2);
	closesocket(sockfd);
#else
	shutdown(sockfd, SHUT_RDWR);
	struct linger linger;
	linger.l_onoff = 1;
	linger.l_linger = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (char *)&linger, sizeof(linger));
	close(sockfd);
#endif
}

#endif
