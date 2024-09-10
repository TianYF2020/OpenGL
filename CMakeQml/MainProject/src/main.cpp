#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "UIControl.h"
#include "qDebug"
#include "DrawTestGL.h"
#include "TableDataModel.h"
#include "EasyTableModel.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //把item类型注册到qml中<Cpp类型>(qml模块名,主版本,次版本,qml类型)
    qmlRegisterType<FBOItem>("LearnOpenGL", 1, 0, "FBOItem");

    TableDataModel tableModel;  // 创建 TableDataModel 实例
    // 将数据模型注册到 QML 中
    engine.rootContext()->setContextProperty("tableModel", &tableModel);
    UIControl m_UIControl;
    engine.rootContext()->setContextProperty("myUIControl", &m_UIControl);
    qmlRegisterType<EasyTableModel>("EasyModel", 1, 0, "EasyTableModel");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(QUrl(QStringLiteral("qrc:qml/Main.qml")));


    return app.exec();
}


