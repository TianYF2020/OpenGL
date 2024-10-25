import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    anchors.fill: parent
    property int listViewCurrIndex:0
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

    ListModel {
         id: listModel
         ListElement{name: "新行1"; value: "0"; img: "qrc:/qml/images/warning.png"}
         ListElement{name: "新行2"; value: "0"; img: "qrc:/qml/images/warning.png"}
         ListElement{name: "新行3"; value: "0"; img: "qrc:/qml/images/warning.png"}
     }

    Rectangle
    {
        id: listViewArea
        clip: true
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: testBtn.bottom
        anchors.bottom: parent.bottom
        border.color: "red"
        border.width: 1
        radius: 20

         ListView
         {
             id: listView
             anchors.fill: parent
             model:listModel
             delegate: LineItem {
             width: listViewArea.width
                height: 50
             }  // 引用 ListItem.qml
             // 右键菜单
             Menu  {
                 id: contextMenu
                 MenuItem {
                     text: "添加一行"
                     onTriggered: {
                         // listModel.append({"name": "新行", "value": "0", "img": "qrc:/qml/images/warning.png"});
                         listModel.append({"name": "新行", "value": "0", "img": "images/warning.png"});  //通过路径来查找
                     }
                 }
                MenuItem
                {
                    text: "增加当前行"
                    onTriggered: {
                        listModel.insert(listViewCurrIndex+1, {"name": "新行", "value": "0", "img": "images/warning.png"});
                    }
                }
                 MenuItem
                 {
                     text: "删除当前行"
                     onTriggered: {
                         listModel.remove(listViewCurrIndex);
                     }
                 }
                 MenuItem {
                     text: "清除所有数据"
                     onTriggered: {
                         listModel.clear();
                     }
                 }
             }
             MouseArea {
                id: mouseArea
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onPressed: function(mouse){
                    if (mouse.button === Qt.RightButton) {
                        // 显示弹出菜单
                        console.log("当前路径:", Qt.resolvedUrl(""))
                        contextMenu.popup(mouse.x, mouse.y);
                        listViewCurrIndex = listView.indexAt(mouseX, mouseY)
                        if(listViewCurrIndex < 0)
                        {
                            listViewCurrIndex = listView.count -1
                        }
                    }
                }

             }

         }

    }




}
