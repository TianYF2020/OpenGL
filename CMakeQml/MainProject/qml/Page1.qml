import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Item {
    id: root
    width: 300
    height: 200
    property var pageParentItem
    ColumnLayout
    {
        id: slidersColumn
        spacing: 6

        LabeledSlider {
            id: rotation1Slider
            text: "R"
            from: 0
            to: 255
            value: 255
        }

        LabeledSlider {
            id: rotation2Slider
            text: "G"
            from: 0
            to: 255
            value: 255
        }

        LabeledSlider {
            id: rotation3Slider
            text: "B"
            from: 0
            to: 255
            value: 255
        }

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
            width: 100
            height: 50
            text: "clear"
            onClicked:
            {
                mlog.clearListView()
                revBtn.setButtonText("清理")
            }
        }
        MyButton
        {
            id: revBtn
        }


        Connections {
            target: pageParentItem  // 监听 SettingView 的信号
            function onSendDevType(txt)
            {
                revBtn.setButtonText(txt)  // 当 valueChanged 信号发出时调用 test 的 switch 方法
            }
        }
    }

}
