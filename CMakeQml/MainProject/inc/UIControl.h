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
    Q_INVOKABLE int setCommonParam(const QVariant &param1, const QVariant &param2);
    
    void myFunction(const QVariant &param1, const QVariant &param2) {
        // 处理参数
        qDebug() << "参数1:" << param1 << "类型:" << param1.typeName();
        qDebug() << "参数2:" << param2 << "类型:" << param2.typeName();
    }

public slots:
    Q_INVOKABLE void handleSignal(const QString &message);
    void writeJsonFile(const QString &filePath); 
    void  readJson(const QString &filePath); 
signals:
    void portsScanned(const QStringList& portNames);
};

