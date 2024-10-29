import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Item {
    id: root
    width: 600
    height: 400
    RowLayout 
    {
        id: graiTitle
        width: parent.width
        spacing: 10
        TextField {
            id: rowInput
            text: "5"
            placeholderText: "输入行数 (m)"
        }
        TextField {
            id: columnInput
              text: "5"
            placeholderText: "输入列数 (n)"
        }
        Button {
            text: "生成网格"
            onClicked: {
                gridView.clearGrid(rowInput.text, columnInput.text);
            }
        }
    }
    Rectangle 
    {
        anchors.top: graiTitle.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "white"
        border.width: 1
        border.color: "black"


         GridView {
            id: gridView
            width: parent.width
            height: parent.height
            flickableDirection: Flickable.AutoFlickDirection
            // spacing: 2
            cellWidth: parent.width /parseFloat(rowInput.text);
            cellHeight: parent.height/parseFloat(columnInput.text);
            // horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            // verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            model: ListModel {}

            delegate: Rectangle {
                width: gridView.cellWidth
                height: gridView.cellHeight
                color: model.color
                border.color: "black"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        model.color = (model.color === "red") ? "lightgray" : "red";
                    }
                }
            }

            function clearGrid(rows, cols) {
                model.clear();
                for (var i = 0; i < rows; i++) {
                    for (var j = 0; j < cols; j++) {
                        model.append({color: "lightgray"});
                    }
                }
            }
        }

    }
       


}
