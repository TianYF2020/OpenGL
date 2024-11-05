#include "ChartModel.h"
#include <QRandomGenerator>
 
ChartModel::ChartModel(QObject *parent) : QObject(parent) {
 
}
 
QVariant ChartModel::series(int index) {
    if (index < 0 || index >= m_seriesData.size()) {
        return QVariant();
    }
    return QVariant::fromValue(m_seriesData[index]);
}
 
void ChartModel::addSeries() {
    QVector<QPointF> series;
    m_seriesData.append(series);
    emit seriesAdded(m_seriesData.length()-1);
}
 
void ChartModel::appendData()
{
    for(int i=0;i<m_seriesData.length();i++)
    {
        QVector<QPointF> &series = m_seriesData[i];
        int x = series.isEmpty() ? 0 : series.last().x() + 1;
        double y = randomGen->bounded(1.0);
        series.append(QPointF(x, y));
        emit seriesUpdate(i);
    }
}