#pragma once
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringList>

class UIControl : public QObject
{
    Q_OBJECT
public:
    explicit UIControl(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void scanPorts()
    {
        QStringList portNames;
        //foreach(const QSerialPortInfo & info, QSerialPortInfo::availablePorts()) {
        //    portNames << info.portName();
        //}
        portNames << "Com1" << "Com2" << "Com3";
        emit portsScanned(portNames);
    }

signals:
    void portsScanned(const QStringList& portNames);
};
