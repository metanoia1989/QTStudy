#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <chrono>
#include <ctime>

using namespace std::chrono;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto timenow =  system_clock::to_time_t(system_clock::now());
    QString time = ctime(&timenow);
    engine.rootContext()->setContextProperty("Current", time);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
