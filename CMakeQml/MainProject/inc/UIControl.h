#pragma once
#include <QQmlContext>
#include <QStringList>
#include <QObject>
#include "QDebug"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
class UIControl  : public QObject
{
	Q_OBJECT

public:
    // explicit UIControl(QObject* parent = nullptr) : QObject(parent) {}
    UIControl();
	~UIControl();

    Q_INVOKABLE QStringList scanPorts();
public slots:
    Q_INVOKABLE void handleSignal(const QString &message);
    void writeJsonFile(const QString &filePath); 
    void  readJson(const QString &filePath); 
signals:
    void portsScanned(const QStringList& portNames);
};

