#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "UIControl.h"
#include "qDebug"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    UIControl m_UIControl;
    engine.rootContext()->setContextProperty("myUIControl", &m_UIControl);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(QUrl(QStringLiteral("qrc:qml/Main.qml")));


    return app.exec();
}


