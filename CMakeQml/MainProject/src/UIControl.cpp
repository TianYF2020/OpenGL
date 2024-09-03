#include "UIControl.h"


UIControl::~UIControl()
{

}


Q_INVOKABLE QStringList UIControl::scanPorts()
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
