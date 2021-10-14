#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "doctor.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    Doctor test1;
    test1.createNewProfile("A", "B", "C", "D", "E", "F", "G");

    Doctor test2;
    test2.createNewProfile("H", "I", "J", "K", "L", "M", "N");

    return app.exec();
}
