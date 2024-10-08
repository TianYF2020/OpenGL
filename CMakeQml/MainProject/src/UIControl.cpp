#include "UIControl.h"


UIControl::UIControl()
{
    writeJsonFile("config.json");
    readJson("config.json");
}

UIControl::~UIControl()
{
}


Q_INVOKABLE QStringList UIControl::scanPorts() //你好
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