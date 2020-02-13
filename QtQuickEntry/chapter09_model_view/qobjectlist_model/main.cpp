#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dataobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QObjectList objectList;
    objectList.append(new DataObject("Item1", "red"));
    objectList.append(new DataObject("Item2", "green"));
    objectList.append(new DataObject("Item3", "blue"));
    objectList.append(new DataObject("Item4", "yellow"));
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("objectListModel",
                                QVariant::fromValue(objectList));

    engine.load(url);

    return app.exec();
}
