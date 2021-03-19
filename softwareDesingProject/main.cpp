#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "api.h"
#include "controller.h"
#include "model.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    Controller controller;

    // TODO: cleanup
    Model* model = new Model();

    controller.setModel(model);

//    qmlRegisterType<Controller>("controller", 1, 0, "Controller");

//    API api;
//    api.load("https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::forecast::hirlam::surface::point::simple&place=Tampere&parameters=temperature");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("viewController", &controller);
    engine.rootContext()->setContextProperty("model", model);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
