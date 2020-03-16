#ifndef HANDLE_H
#define HANDLE_H
#include <QObject>
#include <QSettings>
#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QCloseEvent>
#include <QMessageBox>
#include "listenThrd.h"
#include "global.h"
#include "ui_mainHandle.h"


class mainHandle: public QMainWindow
{
	Q_OBJECT
public:
	mainHandle(QWidget *parent = 0);
	~mainHandle();
	int read_ini_file();
	int init_socket_F5();
	int initPort();

	void closeEvent(QCloseEvent *event);
public:
	Ui::mainHandle ui;

signals:       //自定义信号
	void showText(QString txt);


public:
	listenThrd lsnThread;
	
public slots:
    void Slot_SaveActions();
	void DisPlayText(QString txt);

};
#endif
