#include "recvThrd.h"

recvThrd::recvThrd(int skt_FT)
{
    stopped = false;
    skt_ft = skt_FT;
    Timer = 0;
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

}
recvThrd::~recvThrd()
{

}

void recvThrd::stop()
{
    stopped = true;
}

bool recvThrd::init()
{
#ifdef WIN32
    SOCKADDR_IN server;
#else
    sockaddr_in server;
#endif // WIN32
    const char* ipaddr = NIS_ip.toLocal8Bit().data();
    skt_nis = socket(AF_INET, SOCK_STREAM, 0);
    int size_sockaddrin = 0;
#ifdef WIN32
    size_sockaddrin = sizeof(SOCKADDR_IN);
#else
    size_sockaddrin = sizeof(sockaddr_in);
#endif
    memset(&server, 0, size_sockaddrin);
    server.sin_family = PF_INET;
    server.sin_port = htons(NIS_port.toUShort());
    server.sin_addr.s_addr = inet_addr(ipaddr);

#ifdef WIN32
    unsigned long ll = 1;
    if (ioctlsocket(skt_nis, FIONBIO, &ll) != 0)
#else
    int flags = 0;
    if (fcntl(skt_nis, F_SETFL, flags | O_NONBLOCK) < 0)
#endif
    {

        CloseSocket(skt_nis);
        return false;
    }
    bool ret = false;
    if (::connect(skt_nis, (struct sockaddr*)&server, size_sockaddrin) == -1)
    {
        int error = -1, len = sizeof(int);
        fd_set writefds;
        timeval tm = { CntWaitTime_secs,CntWaitTime_msecs };
        FD_ZERO(&writefds);
        FD_SET(skt_nis, &writefds);
        if (select(skt_nis + 1, NULL, &writefds, NULL, &tm) > 0)
        {
#ifdef WIN32
            getsockopt(skt_nis, SOL_SOCKET, SO_ERROR, (char*)&error, &len);
#else
            getsockopt(skt_nis, SOL_SOCKET, SO_ERROR, &error, (socklen_t*)&len);

#endif
            if (0 == error)
                ret = true;
            else
                ret = false;
        }
        else
            ret = false;
    }
    else
        ret = false;

    return ret;
}

void recvThrd::run()
{
    if(!init())
        return;
    while (!stopped )
    {
        Timer++;
        msleep(500);
        Recv_Send_Deal();

    }
    qDebug()<<"end";
    WriteLog("end");
}

bool recvThrd::judgeConnection()
{
    if (Timer >= 20)    //通断测试 s
    {
        int sndLen = send(skt_ft, "", 0, 0);
        if (sndLen < 0)
        {
            return false;
        }
        sndLen = send(skt_nis, "", 0, 0);
        if (sndLen < 0)
        {
            return false;
        }
        Timer = 0;

    }
    return true;

}


void recvThrd::Recv_Send_Deal()
{

    if(!judgeConnection())
    {

        CloseSocket(skt_ft);
        CloseSocket(skt_nis);
        stopped = true;

        return;
    }

    int receive_len = MyRcv(skt_ft, (char*)&RcvBuff[0], 280);
    if (receive_len > 0)
    {

        int sndLen = MySnd(skt_nis, (char*)&RcvBuff[0], receive_len);
        if (sndLen < 0)
        {

            CloseSocket(skt_ft);
            CloseSocket(skt_nis);
            stopped = true;
            return;
        }

    }

    int receive_len2 = MyRcv(skt_nis, (char*)&RcvBuff[0], 280);
    if (receive_len2 > 0)
    {

        int sndLen = MySnd(skt_ft, (char*)&RcvBuff[0], receive_len2);
        if (sndLen < 0)
        {
            CloseSocket(skt_ft);
            CloseSocket(skt_nis);
            stopped = true;
            return;
        }

    }
}




