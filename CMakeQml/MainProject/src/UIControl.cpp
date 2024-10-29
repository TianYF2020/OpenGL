#include "UIControl.h"


UIControl::UIControl()
{
    writeJsonFile("config.json");
    readJson("config.json");
}

UIControl::~UIControl()
{
}


// qml 开发笔记
// qml 中子空间能不断的访问，能够访问自己以上的所有 id ，但是 向下访问有限制，一般只能访问一层，想多层访问就要使用内部函数来一次曾一层访问
// 比如设计的比较复杂后，可以在最上次设置一个配置文件，需要写的数据可以临时存在这里，其他地方可以从这里那

QStringList UIControl::scanPorts() //你好
{
    QStringList portNames;
    //foreach(const QSerialPortInfo & info, QSerialPortInfo::availablePorts()) {

    //    portNames << info.portName();
    //}

    portNames << "Com1" << "Com2" << "Com3";
    
    qDebug() << portNames;
    //emit portsScanned(portNames);
    return portNames;
}

int UIControl::setCommonParam(const QVariant &param1, const QVariant &param2)
{
    // 处理参数
    qDebug() << "参数1:" << param1 << "类型:" << param1.typeName();
    qDebug() << "参数2:" << param2 << "类型:" << param2.typeName();
    return 0;
}



void UIControl::handleSignal(const QString &message)
{

    qDebug() << "Received from QML:" << message;
}


    void UIControl::writeJsonFile(const QString &filePath)
    {
        QJsonObject json;

        // 创建 adjust 节点
        QJsonObject adjust;

        // 设备类型
        QStringList  deviceTypes;
        deviceTypes.append("NT68400");
        deviceTypes.append("3683");
        deviceTypes.append("V53");
        deviceTypes.append("V56");
        deviceTypes.append("V68830");
        // 为每个设备类型添加色温、色域、亮度和值
        for (const QString &type : deviceTypes) 
        {
            QJsonObject device;
            device["色温"] = true;
            device["Gamma"] = true;
            device["亮度"] = true;
            device["色域"] = true;
            device["3DLut"] = true;
            device["Comm"] = "NT";
            adjust[type] = device;
        }

        // 创建 serial 节点
        QJsonObject serial;
        serial["串口号"] = QString("COM1");  // 串口号
        serial["波特率"] = 9600;    // 正确的波特率值

        json["adjust"] = adjust;
        json["serial"] = serial;

        // 写入文件
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open the file.");
            return;
        }

        file.write(QJsonDocument(json).toJson());
        file.close();

    }


void UIControl::readJson(const QString &filePath) 
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the file.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject json = doc.object();

    // 读取 adjust 节点
    QJsonObject adjust = json["adjust"].toObject();
    for (const QString &type : adjust.keys()) {
        QJsonObject device = adjust[type].toObject();
        qDebug() << "设备类型:" << type;
        qDebug() << "色温:" << device["色温"].toBool();
        qDebug() << "色域:" << device["色域"].toBool();
        qDebug() << "亮度:" << device["亮度"].toBool();
        qDebug() << "值:" << device["值"].toBool();
    }

    // 读取 serial 节点
    QJsonObject serial = json["serial"].toObject();
    qDebug() << "串口号:" << serial["串口号"].toString();
    qDebug() << "波特率:" << serial["波特率"].toInt();
}
