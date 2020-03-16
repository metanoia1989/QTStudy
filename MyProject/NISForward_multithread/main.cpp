#include "Handle.h"
#ifndef WIN32
#include <signal.h>
#endif // !



#ifdef WIN32 
HANDLE m_hMutex;
bool checkOnly()
{

	
	//  创建互斥量  
	m_hMutex = CreateMutex(NULL, FALSE, L"NISFORWARD");
	//  检查错误代码  
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		//  如果已有互斥量存在则释放句柄并复位互斥量  
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
		//  程序退出  
		//QMessageBox::warning(NULL,QString::fromLocal8Bit("重复打开"), QString::fromLocal8Bit("程序已运行"));
		QMessageBox::warning(NULL,"ReOpen","Soft is Running");

		return  false;
	}else
		return true;

}
#else
bool checkOnly()
{
	const char filename[] = "/tmp/lockfile_Forward";
	int fd = open(filename, O_WRONLY | O_CREAT, 0644);
	int flock = lockf(fd, F_TLOCK, 0);
	if (fd == -1) {
		perror("open lockfile/n");
		QMessageBox::warning(NULL, QString::fromLocal8Bit("重复打开"), QString::fromLocal8Bit("程序已运行"));
		return false;
	}
	//给文件加锁  
	if (flock == -1) {
		perror("lock file error/n");
		QMessageBox::warning(NULL, QString::fromLocal8Bit("重复打开"), QString::fromLocal8Bit("程序已运行"));
		return false;
	}
	//程序退出后，文件自动解锁  
	return true;
}
#endif

int main(int argc, char *argv[])
{
//#ifndef WIN32
//    sigset_t signal_mask;
//    sigemptyset(&signal_mask);
//    sigaddset(&signal_mask, SIGPIPE);
//    int rc = pthread_sigmask(SIG_BLOCK, &signal_mask, NULL);
//    if (rc != 0) {
//        printf("block sigpipe error/n");
//    }
//#endif
	QApplication a(argc, argv);
	if (false == checkOnly())
		return 0;
	mainHandle w;
	w.show();
	return a.exec();
}
