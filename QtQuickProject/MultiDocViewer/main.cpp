#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqml.h>
#include <QIcon>
#include "htmlhandler.h"
#include "texthandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/vieweye.png"));
    qmlRegisterType<HtmlHandler>("org.qtproject.easybooks", 1, 0, "HtmlHandler");//
    qmlRegisterType<TextHandler>("org.qtproject.easybooks", 1, 0, "TextHandler");//

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
