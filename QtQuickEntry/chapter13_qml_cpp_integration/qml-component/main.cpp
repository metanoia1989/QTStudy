#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlExpression>
#include <QQuickItem>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent component(&engine, url);

    QObject *myObject = component.create();
    QQuickItem *item = qobject_cast<QQuickItem*>(myObject);
    qreal width = item->width();
    qDebug() << "组件宽度：" << width;

    QQmlExpression *expr = new QQmlExpression(engine.rootContext(),
                                              myObject, "width * 2");
    int result = expr->evaluate().toInt();
    qDebug() << "组件宽度 * 2：" << result;

    return app.exec();
}
