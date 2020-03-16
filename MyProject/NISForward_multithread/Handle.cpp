#include "Handle.h"

mainHandle::mainHandle(QWidget *parent) : QMainWindow(parent)
{
	//读取配置文件，获取连接IP端口号
	
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("NISForward"));
	connect(this, SIGNAL(showText(QString)), this, SLOT(DisPlayText(QString)));
	bool temp = connect(&lsnThread, SIGNAL(showText(QString)), this, SLOT(DisPlayText(QString)));
	if (read_ini_file() > 0)
	{
		//初始化socket,调用监听线程listenThrd
		init_socket_F5();
	}

}

mainHandle::~mainHandle()
{
	disconnect(this, SIGNAL(showText(QString)), this, SLOT(DisPlayText(QString)));
}

void mainHandle::closeEvent(QCloseEvent *event)
{
    event->ignore();
//	int ret = QMessageBox::question(this, "ATTENTION!", "Sure to leave?");
//	if (QMessageBox::Yes != ret)
//		event->ignore();
//	else
//	{
//		if (lsnThread.isRunning())
//        {
//           lsnThread.stop();
//           lsnThread.wait();
//        }
//		qApp->quit();
//	}
}

void mainHandle::Slot_SaveActions()
{
	int a = 0;
}

void mainHandle::DisPlayText(QString txt)
{
	ui.textEdit->append(txt);
}

//读取配置文件
int mainHandle::read_ini_file()
{
	exepath = QCoreApplication::applicationDirPath();
	QString file_path = exepath +"/config.ini";
    QSettings *configIni = new QSettings(file_path, QSettings::IniFormat);

	if (configIni->contains(tr("F5/ip"))
		&& configIni->contains(tr("F5/port")) 
		&& configIni->contains(tr("NIS/ip")) 
		&& configIni->contains(tr("NIS/port"))
		&& configIni->contains(tr("Param/cnt_wait_time_msecs")))//如果已经存在这个文件，那就进行读取  
	{
		F5_ip = configIni->value("F5/ip").toString();
		F5_port = configIni->value("F5/port").toString();
		NIS_ip = configIni->value("NIS/ip").toString();
		NIS_port = configIni->value("NIS/port").toString();


		int tmp = configIni->value("Param/cnt_wait_time_msecs").toInt();
		CntWaitTime_secs = tmp / 1000;
		CntWaitTime_msecs = tmp % 1000;
	}
	else
	{
		return -1;
	}
	
	return 1;
}
int mainHandle::init_socket_F5() 
{
	//创建套接字
#ifdef WIN32
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
    {
        qDebug("socket:errno = %d\n", errno);//cout << endl << "WSASTartup初始化失败" << endl;
		emit showText("socket:errno = %d\n");
        return -1;
    }

#endif
	if (lsnThread.isRunning())
	{
		lsnThread.stop();
		//rcvThread.stop();
	}
	else
	{
		if (initPort())
		{
			lsnThread.start();

		}
		else
		{
			qDebug("fail to start!");
			emit showText("fail to start!");
		}
			
	}


}

int mainHandle::initPort()
{
	QByteArray temp = F5_ip.toLocal8Bit();
	const char* ipadd1 = temp.data();
	unsigned short portNum = F5_port.toUShort();

	memset((void*)&addrServer, 0, sizeof(addrServer));

	if (F5_ip.isEmpty() || ("localhost" == GetLow(F5_ip)))
        addrServer.sin_addr.s_addr = INADDR_ANY;
	else
        addrServer.sin_addr.s_addr = inet_addr(ipadd1);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(portNum);//绑定端口

	sockServer = socket(AF_INET, SOCK_STREAM, 0);

	if (sockServer < 0)
	{
		qDebug("socket:errno = %d\n", errno);
		emit showText("socket:errno = %d\n");
		return false;
	}
	int bReuseaddr = 1;          //设置地址绑定复用，Linux下需要
#ifdef _WIN32
	setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReuseaddr, sizeof(int));
#else
	setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, &bReuseaddr, sizeof(int));
#endif 
    if (::bind(sockServer, (struct sockaddr*)&addrServer, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		qDebug("bind:errno = %d\n", errno);//perror("bind");
        CloseSocket(sockServer);
		sockServer = INVALID_SOCKET;
		return false;
	}

#ifdef WIN32
    unsigned long ll = 1; //非阻塞模式；0：阻塞模式
    if (ioctlsocket(sockServer, FIONBIO, &ll) != 0)
#else
    int flags = 0;
    if (fcntl(sockServer, F_SETFL, flags | O_NONBLOCK)<0)
#endif
	{
		qDebug("ioctlsocket:errno = %d\n", errno);//perror("listen");
		emit showText("ioctlsocket:errno = %d\n");
        CloseSocket(sockServer);
		sockServer = INVALID_SOCKET;
		return false;
	}

	if (listen(sockServer, 4) == SOCKET_ERROR)
	{
		qDebug("listen:errno = %d\n", errno);//perror("listen");
		emit showText("listen:errno = %d\n");
		//serv.RecvText->append(tr("listen:errno = %1\n").arg(errno));
        CloseSocket(sockServer);
		sockServer = INVALID_SOCKET;
		return false;
	}

	qDebug("listen successful");
	emit showText("listen successful !");
	

	return true;

}
