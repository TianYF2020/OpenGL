#include "ChartModel.h"
#include <QRandomGenerator>
 
ChartModel::ChartModel(QObject *parent) : QObject(parent) 
{


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
        double y = randomGen->bounded(255.0);
        series.append(QPointF(x, y));
        emit seriesUpdate(i);
    }
}

void ChartModel::LoadInitData()
{
    addSeries();
    // emit seriesAdded(m_seriesData.length()-1);
    for(int i = 0; i < 255;i ++)
    {

        // emit seriesUpdate(0);
        m_seriesData[0].push_back(QPointF(i, i));
        // m_seriesData.append(series);
    }
       emit seriesUpdate(0);
}