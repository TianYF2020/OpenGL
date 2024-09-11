import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0

Rectangle {
    Rectangle{
        id:header
        width: parent.width
        height: 30

        Row{
            spacing: 0

            Repeater{
                model: ["name","age","class","number"]

                Rectangle{
                    width: header.width/4
                    height: header.height
                    color: "#000000"
                    border.width: 1
                    border.color: "#848484"
                    Text {
                        text: modelData
                        anchors.centerIn: parent
                        font.pointSize: 12
                        color: "white"
                    }
                }
            }
        }
    }
    TableView{
        id:tableView
        width: parent.width
        anchors.top:header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true
        boundsBehavior: Flickable.OvershootBounds


        ScrollBar.vertical: ScrollBar {
            anchors.right:parent.right
            anchors.rightMargin: 0
            visible: tableModel.rowCount > 5
            background: Rectangle{
                color:"#666666"
            }
            onActiveChanged: {
                active = true;
            }
            contentItem: Rectangle
            {
                implicitWidth  : 6
                implicitHeight : 30
                radius : 3
                color  : "#848484"
            }
        }

        model: TableModel {
            id:tableModel

            TableModelColumn{display: "name"}
            TableModelColumn{display: "age"}
            TableModelColumn{display: "class"}
            TableModelColumn{display: "number"}

        }
        delegate:Rectangle{
            color: "#666666"
            implicitWidth: tableView.width/4
            implicitHeight: 32
            border.width: 1
            border.color: "#848484"

            Text {
                text: display
                anchors.centerIn: parent
                font.pointSize: 12
                color: "white"
            }
        }
    }

    Component.onCompleted: {
        tableModel.appendRow({"name":"小明","age":12,"class":"三年二班","number":"003"})
        tableModel.appendRow({"name":"小刚","age":13,"class":"三年三班","number":"012"})
        tableModel.appendRow({"name":"小李","age":11,"class":"三年四班","number":"023"})
        tableModel.appendRow({"name":"小王","age":10,"class":"三年二班","number":"021"})
        tableModel.appendRow({"name":"小张","age":13,"class":"三年五班","number":"004"})
        tableModel.appendRow({"name":"小林","age":14,"class":"三年一班","number":"008"})
    }

}

