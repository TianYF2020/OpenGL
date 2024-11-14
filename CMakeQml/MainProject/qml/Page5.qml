import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts
Item 
{
    width: 600
    height: 400
    visible: true
 
    property var maxValue: 255
    property var step: 8
    property real pointSize: 0
    property var num: 1;   
    function resetData()
    {
        scatterSeries.clear()
        splineSeries.clear()
        for(let i=0;i<=maxValue;i++)
        {
            if( i%step == 0)
            {
                scatterSeries.append(i,i);
            }
            splineSeries.append(i,i);
        }
        if(maxValue % step != 0)
        {
            scatterSeries.append(maxValue,maxValue)
        }
    }
    Component.onCompleted: 
    {
        resetData()
        var tempPoint = chartView.mapToValue(Qt.point(scatterSeries.markerSize / 2.0, 0))
        var tempPoint0 = chartView.mapToValue(Qt.point(0, 0))
        pointSize = tempPoint.x - tempPoint0.x
        console.log("pointSize: ==== ", scatterSeries.markerSize , " size ",pointSize)
    }
    ChartView 
    {
        id: chartView
        width: parent.width
        height: parent.height - operateArea.height
        antialiasing: true
        // 使用 ScatterSeries 来显示数据点
        ScatterSeries {
            id: scatterSeries
            name: "Scatter Series"
            color: "blue"
            axisX: xAxis
            axisY: yAxis
        }
        // 使用 SplineSeries 来绘制平滑的曲线
        SplineSeries {
            id: splineSeries
            name: "Spline Series"
            color: "red"
            axisX: xAxis
            axisY: yAxis
        }
        MouseArea {// 定义鼠标事件处理
            id: dragArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            property bool isDragging: false
            property int draggedIndex: -1   // 拖动的点图
            property int draggedSpline: -1  //拖动的spline点图
            onWheel: 
            {
                if(wheel.angleDelta.y > 0)
                {
                    chartView.zoom(1.1 )
                }else
                {
                    chartView.zoom(0.9)
                }
            }
            onPressed: {
                var point = chartView.mapToValue(Qt.point(mouseX, mouseY))
                draggedIndex = -1;
                draggedSpline = -1
                console.log("coust ",point.x, point.y)
                for (var i = 0; i < scatterSeries.count; ++i) 
                {
                    var dataPoint = scatterSeries.at(i);
                    if (Math.abs(dataPoint.x - point.x) < pointSize && Math.abs(dataPoint.y - point.y) < pointSize) 
                    {
                        draggedIndex = i;
                        draggedSpline = i * step > maxValue  ? maxValue : i * step 
                        console.log(dataPoint.x, dataPoint.y, " - " , point.x,point.y)
                        break;
                    }
                }
                isDragging = draggedIndex !== -1;
            }
            onReleased: { 
                isDragging = false
            }
            onPositionChanged: 
            {
                if (isDragging && draggedIndex !== -1)
                {
                    var point = chartView.mapToValue(Qt.point(mouseX, mouseY))
                    var yValue = point.y;
                    if (yValue < 0)  yValue = 0;
                    if (yValue > xAxis.max)  yValue = xAxis.max;
                    // 更新散点和曲线的数据任意移动
                    // scatterSeries.replace(draggedIndex, point.x, yValue);
                    // splineSeries.replace(draggedSpline, point.x, yValue);
                    // 上下移动
                    scatterSeries.replace(draggedIndex, draggedSpline, yValue);
                    splineSeries.replace(draggedSpline, draggedSpline, yValue);
                    let startIndex = (draggedSpline - step) < 0 ? 0 : (draggedSpline - step )
                    let endIndex = (draggedSpline + step) >maxValue ? maxValue : (draggedSpline + step)
                    let diffIndex = (draggedSpline- startIndex) > 0 ? (draggedSpline- startIndex):0
                    let diffValue = (splineSeries.at(draggedSpline).y - splineSeries.at(startIndex).y) /diffIndex
                    num = 1;
                    for(let i = startIndex +1 ;i<draggedSpline;i++)
                    {
                        splineSeries.replace(i, i, splineSeries.at(startIndex).y + (num++)*diffValue);
                    }
                    num = 1;
                    diffIndex = (endIndex -draggedSpline) > 0 ? (endIndex - draggedSpline):0
                    diffValue = (splineSeries.at(endIndex).y - splineSeries.at(draggedSpline).y) /diffIndex
                    for(let i = draggedSpline +1 ;i<endIndex;i++)
                    {
                        splineSeries.replace(i, i, splineSeries.at(draggedSpline).y + (num++)*diffValue);
                    }
                }
            }
        }
        ValueAxis {
            id: yAxis
            min: 0
            max: maxValue
        }
        // 设置 X 轴的范围
        ValueAxis {
            id: xAxis
            min: 0
            max: maxValue
        }
        // // 缩放功能
        // MouseArea {
        //     id: zoomArea
        //     anchors.fill: parent
        //     cursorShape: Qt.PointingHandCursor

        //     onReleased: {
        //         if (dragArea.containsMouse) {
        //             chartView.chart.zoomReset();
        //         }
        //     }
        // }
        // 显示鼠标当前位置
        Text {
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            text: "Mouse Position: " + dragArea.mouseX + ", " +dragArea.mouseY
        }
    }
    RowLayout
    {
        id:operateArea
        anchors.top: chartView.bottom
        width: parent.width
        height: 30
        Button
        {
            text: "test"
            onClicked:
            {
                console.log("test")
                for(let i = 0; i<splineSeries.count; i++)
                {
                    let point = splineSeries.at(i)
                    console.log("pinghua: x:", point.x, "y:", point.y)
                }
                for(let i = 0; i<scatterSeries.count; i++)
                {
                    let point = scatterSeries.at(i)
                    console.log("x:", point.x, "y:", point.y)
                }
            }
        }
        Button
        {
            text: "复位"
            onClicked:
            {
                resetData()
            }
        }
    }
}
       


    //     ChartView 
    //     {
    //     id: chartView
    //     width: parent.width
    //     height: parent.height
    //     antialiasing: true

    //     LineSeries {
    //         id: lineSeries
    //         name: "Line Series"
    //         property var num: 0
    //         // 添加数据点
    //         axisX: myAxisX
    //         axisY: myAxisY
    //     }
    //     ValueAxis 
    //     {
    //         id: myAxisX
    //         min: 0        // 设置 X 轴的最小值
    //         max: 255       // 设置 X 轴的最大值
    //         tickCount: 6  // 设置 X 轴刻度的数量
    //     }

    //     // 创建 Y 轴的 ValueAxis
    //     ValueAxis {
    //         id: myAxisY
    //         min: 0        // 设置 Y 轴的最小值
    //         max: 255       // 设置 Y 轴的最大值
    //         tickCount: 6  // 设置 Y 轴刻度的数量
    //     }

    //     axes: [myAxisX, myAxisY]

    //     MouseArea {
    //         anchors.fill: parent
    //         onPositionChanged: {
    //             //  lineSeries.append(lineSeries.num++, 4) // (x, y)
    //             // 获取鼠标在ChartView中的坐标
    //             // var localX = chartView.mapToChart(mouse.x).x
    //             // var localY = chartView.mapToChart(mouse.y).y
    //             // console.log("Mouse Position in Chart: x = " + localX + ", y = " + localY)
    //         }
    //         onClicked:
    //         {
    //             console.log("Clicked on ChartView!")
    //             lineSeries.append(lineSeries.num++, lineSeries.num) // (x, y)
    //             var value = chartView.mapToValue(Qt.point(mouseX, mouseY))
    //          console.log("Chart value at mouse position: ", value.x, value.y)

    //         }
    //     }
    // }
