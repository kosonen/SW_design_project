#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "controller.h"
#include "model.h"
#include "settings.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    Controller controller;
    Model model;
    Settings settings;


    controller.setModel(&model);
    controller.setSettings(&settings);

//    qmlRegisterType<Controller>("controller", 1, 0, "Controller");


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("viewController", &controller);
    engine.rootContext()->setContextProperty("model", &model);
    engine.rootContext()->setContextProperty("settings", &settings);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
