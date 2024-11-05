import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Item {
    id: root
    width: 600
    height: 400
    // property var pageParentItem
    ColumnLayout
    {
        id: slidersColumn
        clip: true
        width: parent.width
        height: 200
        spacing: 6
        LabeledSlider {
            height: 30
            id: rotation1Slider
            text: "R"
            from: 0
            to: 255
            value: 255
        }

        LabeledSlider {
            id: rotation2Slider
            height: 30
            text: "G"
            from: 0
            to: 255
            value: 255
        }

        LabeledSlider {
            id: rotation3Slider
            height: 30
            text: "B"
            from: 0
            to: 255
            value: 255
        }
        RowLayout
        {
            spacing: 20
            Button
            {
                width: 100
                height: 50
                text: "add"
                onClicked:
                {
                    mlog.addLineText("This is a line log")
                }
            }
            Button
            {
                id:clearButton
                width: 100
                height: 50
                text: "clear"
                onClicked:
                {
                    mlog.clearListView()
                    revBtn.setButtonText("清理")
                }
            }
            Button
            {
                id: testBtn
                width: 300
                height: 50
                text: "Test Button"
                onClicked:
                {
                    var qtet = "ni hao"
                    myUIControl.setCommonParam("asdf",1);
                    myUIControl.setCommonParam(qtet,9.9);
                }
            }
        }

        // Connections {
        //     target: pageParentItem  // 监听 SettingView 的信号
        //     function onSendDevType(txt)
        //     {
        //         revBtn.setButtonText(txt)  // 当 valueChanged 信号发出时调用 test 的 switch 方法
        //     }
        // }
    }
    MyListView
    {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: slidersColumn.bottom
        anchors.bottom: parent.bottom
    }

}
