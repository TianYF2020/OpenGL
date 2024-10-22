import QtQuick 
import QtQuick.Controls 

Rectangle
{
    id: logshow
    visible: true
    width: 400
    height: 300
    border.width: 2
    border.color: "red"
    function addLineText(text)
    {
        logListView.model.append({  log: new Date().toLocaleTimeString() + text});
        logListView.positionViewAtEnd()
    }
    function clearListView()
    {
         logListView.model.clear() // 清空
    }

    ListView {
        id: logListView
        anchors.fill: parent
        model: ListModel {}
        width: parent.width
        height: parent.height
        clip: true  
        spacing: 0
        delegate: Item {
             width: logListView.width
            height: 30
            Text {
                text: model.log
                height: parent.height - 1
                font.pixelSize: 16
                color: "black"
            }
            Rectangle {
                width: parent.width
                height: 1  // 分隔线的高度
                color: "black"  // 分隔线颜色
                anchors.bottom: parent.bottom  // 定位到 Item 的底部
            }
        }
    }
}
