#pragma once
#include <QQmlContext>
#include <QStringList>
#include <QObject>
#include "QDebug"
class UIControl  : public QObject
{
	Q_OBJECT

public:
    explicit UIControl(QObject* parent = nullptr) : QObject(parent) {}
	~UIControl();

    Q_INVOKABLE QStringList scanPorts();
public slots:
    Q_INVOKABLE void handleSignal(const QString &message);

signals:
    void portsScanned(const QStringList& portNames);
};

