#include "global.h"


int sockServer, newsocket;   //SOCKET sockServer;
//QMap<int, SOCKETINF> SocketList;
unsigned char Buf[300];



#ifdef WIN32
 SOCKADDR_IN addrServer;
 SOCKADDR_IN client_addr;
#else
 sockaddr_in addrServer;
 sockaddr_in client_addr;
#endif

QCoreApplication* App;
QString F5_ip;
QString F5_port;
QString NIS_ip;
QString NIS_port;

int CntWaitTime_secs;     //创建socket客户端等待时间秒
int CntWaitTime_msecs;	  //创建socket客户端等待时间毫秒
QString  exepath;
//QMap<QString, DEV_TRANC> DevSkt;
QMutex My_mutex;

void WriteLog(QString szlog)
{
	QDateTime dateTime = QDateTime::currentDateTime();
	QString strFormat = "yyyy.MM.dd-hh:mm:ss.zzz ";
	QString strDateTime = dateTime.toString(strFormat);

	QFile file(exepath +"/log.txt");
	QString infostr = "NISForward:" + strDateTime;
    file.open(QIODevice::ReadWrite | QIODevice::Append);
	file.write((infostr+szlog).toUtf8()+"\r\n");
    file.flush();
	file.close();
}

