import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts
Item 
{
    width: 600
    height: 400
    visible: true
    ChartView 
    {
        id: chartView
        anchors.fill: parent
        antialiasing: true
 
        // 初始化轴
        ValueAxis {
            id: axisX
            min: 0
            max: 100
            labelFormat: "%d"
            tickCount:5
        }
 
        ValueAxis {
            id: axisY
            min: 0
            max: 1
            labelFormat: "%.2f"
            tickCount:5
        }
 
        Connections 
        {
            target: ChartModel
            function onSeriesAdded(seriesIndex)
            {
                var series = ChartModel.series(seriesIndex);
                var chartSeries = chartView.series(seriesIndex);
                if (!chartSeries) 
                {
                    var newSeries = chartView.createSeries(ChartView.SeriesTypeLine, "数据系列 " + seriesIndex, axisX, axisY);
                }
            }
            function onSeriesUpdate(seriesIndex)
            {
                var series = ChartModel.series(seriesIndex);
                var chartSeries = chartView.series(seriesIndex);
                if (chartSeries) 
                {
                    chartSeries.clear();
                    for (var i = 0; i < series.length; i++) {
                        console.log(series[i].x+":"+series[i].y)
                        chartSeries.append(series[i].x, series[i].y);
                    }
                }
            }
        }
    }
 
    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10
        Button {
            id:addSeries
            text: "新增曲线"
            onClicked: {
                ChartModel.addSeries();
            }
        }
 
        Button {
            id:addData
            text: "追加数据"
            onClicked: {
                ChartModel.appendData();
            }
        }
    }

}
       



