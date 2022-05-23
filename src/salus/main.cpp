#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "backend.h"
#include "backend/patient/patientlistmodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext();

    qmlRegisterType<Backend>("io.qt.salus", 1, 0, "Backend");
    qmlRegisterType<PatientListModel>("io.qt.salus", 1, 0, "PatientListModel");

    const QUrl url(QStringLiteral("qrc:/frontend/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
