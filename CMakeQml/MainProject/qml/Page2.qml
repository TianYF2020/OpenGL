import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
// import QtGraphs
import QtCharts
Item {
    width:400
    height: 400

    ChartView 
    {
        id: mChartView
        anchors.fill: parent
        title: "XXX数据读取"
        antialiasing: true
        backgroundColor: "#9917719b"
        animationOptions: ChartView.SeriesAnimations
        titleColor: "#ccffffff"
        titleFont.bold: true
        titleFont.family: "方正粗倩_GBK"
        titleFont.pointSize: 15
        legend.visible:false
        margins.left: 10
        margins.right: 10
        margins.top: 10
        margins.bottom: 10
        property int timer: 0
        ValueAxis
        {
            id: myAxisX
            min: 0
            max: 10>mChartView.timer? 10:mChartView.timer+1
            tickCount: 11
            labelsColor: "#ffffff"
            labelsFont.pointSize: 13
            labelsFont.bold: true
            labelFormat: '%d'
        }
        ValueAxis
        {
            id:myAxisY
            min:0
            max:50
            tickCount: 6
            labelsColor: "#ffffff"
            labelsFont.pointSize: 13
            labelsFont.bold: true
            labelFormat: '%d'
        }

        LineSeries
        {
            id:lineSeries
            name: "LineSeries"
            axisX: myAxisX
            axisY:myAxisY
            color: "#00ffff"
            width: 3
        }

        Timer
        {
            interval: 1000
            running: true
            repeat: true
            onTriggered: 
            {
                if(mChartView.timer <10)
                {
                    lineSeries.append(mChartView.timer,Math.random()*50)
                    mChartView.timer = mChartView.timer+1
                }
                else
                {
                    running = false
                }
                // console.log("add a data")
            }
        }
    }

}
