#include <QApplication>
#include <QScreen>
#include <QMessageLogContext>
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include "widget.h"

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    qInstallMessageHandler(customMessageHandler);
    QApplication a(argc, argv);
    Widget w;
    w.move(QApplication::screens().at(0)->geometry().center() - w.rect().center());
    w.show();
    a.setWindowIcon(QIcon(":/app.ico"));
    return a.exec();
}

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
   Q_UNUSED(context);
 
   QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
   QString txt = QString("[%1] ").arg(dt);
 
   switch (type)
   {
      case QtDebugMsg:
         txt += QString("{Debug} \t\t %1").arg(msg);
         break;
      case QtWarningMsg:
         txt += QString("{Warning} \t %1").arg(msg);
         break;
      case QtCriticalMsg:
         txt += QString("{Critical} \t %1").arg(msg);
         break;
      case QtFatalMsg:
         txt += QString("{Fatal} \t\t %1").arg(msg);
         abort();
         break;
   }
 
   QFile outFile("LogFile.log");
   outFile.open(QIODevice::WriteOnly | QIODevice::Append);
 
   QTextStream textStream(&outFile);
   textStream << txt << endl;
}
