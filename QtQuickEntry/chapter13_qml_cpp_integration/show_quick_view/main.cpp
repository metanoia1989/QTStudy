#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QQuickItem>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:///main.qml")));
    view.show();
    QQuickItem *object = view.rootObject();
    object->setWidth(500);
    qDebug() << object->width();

    return app.exec();
}
