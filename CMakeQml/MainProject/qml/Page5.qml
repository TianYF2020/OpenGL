import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts
Item 
{
    width: 600
    height: 400
    visible: true
 
       ChartView {
        id: chartView
        anchors.fill: parent
        antialiasing: true
        z: 10

        // 使用 ScatterSeries 来显示数据点
        ScatterSeries {
            id: scatterSeries
            name: "Scatter Series"
            color: "blue"

            // 定义初始的散点数据
            // 这里我们使用了一些假数据，实际使用时可以通过其他方式来动态添加数据点
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1; y: 1 }
            XYPoint { x: 2; y: 2 }
        }

        // 使用 SplineSeries 来绘制平滑的曲线
        SplineSeries {
            id: splineSeries
            name: "Spline Series"
            color: "red"

            // 这里我们只用了一些假数据来展示，实际使用时会与散点数据同步
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1; y: 1 }
            XYPoint { x: 2; y: 2 }
        }

 

        // 定义鼠标事件处理
        MouseArea {
            id: dragArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor

            property bool isDragging: false
            property int draggedIndex: -1
            property real originalY: 0

            onPressed: {
                // 查找鼠标按下位置对应的点，开始拖动
                console.log("onPressed  ")
                var point = chartView.mapToValue(Qt.point(mouseX, mouseY))
                draggedIndex = -1;

                for (var i = 0; i < scatterSeries.count; ++i) {
                    var dataPoint = scatterSeries.at(i);
                    if (Math.abs(dataPoint.x - point.x) < 1 && Math.abs(dataPoint.y - point.y) < 1) {
                        draggedIndex = i;
                        originalY = dataPoint.y;
                        break;
                    }
                }
                isDragging = draggedIndex !== -1;
            }

            onReleased: {
                isDragging = false;
            }

            onPositionChanged: {
                if (isDragging && draggedIndex !== -1) {
                    var point = chartView.mapToValue(Qt.point(mouseX, mouseY))
                    var yValue = point.y;

                    // 在这里可以加入对Y值范围的限制（例如 min/max）
                    if (yValue < 0) yValue = 0;
                    if (yValue > 10) yValue = 10;

                    // 更新散点和曲线的数据
                    scatterSeries.replace(draggedIndex, point.x, yValue);
                    splineSeries.replace(draggedIndex, point.x, yValue);
                }
            }
        }

        // 设置 Y 轴的范围
        ValueAxis {
            id: yAxis
            min: 0
            max: 10
        }

        // 设置 X 轴的范围
        ValueAxis {
            id: xAxis
            min: 0
            max: 10
        }

        // 设置坐标轴
        axes: [xAxis, yAxis]

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
            anchors.left: parent.left
            text: "Mouse Position: " + dragArea.mouseX + ", " +dragArea.mouseY
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
