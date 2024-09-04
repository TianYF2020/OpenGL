#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "UIControl.h"
#include "qDebug"
#include "DrawTestGL.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //把item类型注册到qml中<Cpp类型>(qml模块名,主版本,次版本,qml类型)
    qmlRegisterType<FBOItem>("LearnOpenGL", 1, 0, "FBOItem");

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


