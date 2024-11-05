#pragma once

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QVariant>
#include <QRandomGenerator>
class ChartModel : public QObject {
    Q_OBJECT
 
public:
    explicit ChartModel(QObject *parent = nullptr);
 
    Q_INVOKABLE QVariant series(int index);
    Q_INVOKABLE void addSeries();
    Q_INVOKABLE void appendData();
 
signals:
    void seriesAdded(int seriesIndex);
    void seriesUpdate(int seriesIndex);
 
private:
    QVector<QVector<QPointF>> m_seriesData;
    QRandomGenerator *randomGen = QRandomGenerator::global();
};
 
