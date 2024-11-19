// import QtQuick
// import QtQuick.Controls.Basic
// import QtQuick.Layouts


// ColumnLayout {
//     anchors.fill: parent
//     anchors.margins: 15

//     spacing: 15



//     Rectangle {
//         id: tableFrame

//         property double spaceBetweenRows: 2
//         property double spaceBetweenColumns: 2

//         property double delegateWidth: 200
//         property double delegateHeight: 50

//         property double delegateBorderWidth: 2

//         Layout.fillWidth: true
//         Layout.fillHeight: true
//         radius: 15

//         border.color: 'lightblue'
//         border.width: 2
//         clip: true

//         Rectangle {
//             color: "#6495ED"
//             anchors.left: parent.left
//             anchors.leftMargin: 2
//             anchors.right: parent.right
//             anchors.top: parent.top
//             height: parent.delegateHeight
//             radius: 15

//             CustomRadius {}
//             z: 1
//         }

//         Row {
//             id: myHeaders
//             x: -tableView.contentX
//             z: 2

//             Repeater {
//                 model: tableView.columns > 0 ? tableView.columns : 1
//                 Rectangle {
//                     id: roundRect
//                     color: "transparent"
//                     width: tableFrame.delegateWidth
//                     height: tableFrame.delegateHeight

//                     RowLayout {
//                         anchors.fill: parent
//                         Text {
//                             color: 'white'
//                             text: myproxymodel.headerData(model.index, Qt.Horizontal)
//                             verticalAlignment: Text.AlignVCenter
//                             font.family: "Inter"
//                             font.pixelSize: 20
//                             leftPadding: 40
//                             Layout.fillWidth: true
//                             Layout.fillHeight: true
//                             font.bold: true
//                         }

//                         Button {
//                             icon.color: 'white'
//                             Layout.fillHeight: true
//                             Layout.preferredWidth: height
//                             icon.source: 'qrc:/icons/sort.png'
//                             onClicked: () => {
//                                            console.log("header index " + model.index + " clicked!")
//                                            myproxymodel.sort(model.index, Qt.AscendingOrder)
//                                        }

//                             background: Rectangle {
//                                 color: "transparent"
//                             }
//                         }
//                     }
//                 }
//             }
//         }

//         TableView {
//             id: tableView

//             clip: true

//             selectionBehavior: TableView.SelectRows

//             function getRow(delegateIndex) {
//                 return delegateIndex % tableView.rows
//             }

//             function myIsRowSelected(delegateIndex) {
//                 for (let i = 0; i < mySelectionModel.selectedIndexes.length; i++) {
// //                    console.log(i + ", " + mySelectionModel.selectedIndexes[i].row + ", " + getRow(delegateIndex))
//                     if (mySelectionModel.selectedIndexes[i].row === getRow(delegateIndex)) {
//                         return true;
//                     }
//                 }
//                 return false;
//             }

//             anchors.fill: parent
//             anchors.margins: 2
//             anchors.topMargin: tableFrame.delegateHeight + tableFrame.spaceBetweenRows

//             model: myproxymodel

//             selectionModel: ItemSelectionModel {
//                 id: mySelectionModel
//                 model: myproxymodel
//                 onCurrentChanged: (cur, prv)=>{
//                                       print("cur: ", cur)
//                                       print("prv:", prv)
//                                   }

// //                onSelectedIndexesChanged: console.log("'onSelectedIndexesChanged' called!")
//             }

//             property var columnWidths: [tableFrame.delegateWidth, tableFrame.delegateWidth, tableFrame.delegateWidth, tableFrame.width - 3 * tableFrame.width]
//             columnWidthProvider: function (column) { return columnWidths[column] }

//             delegate: Rectangle {
//                 id: tableDelegate

//                 implicitWidth: tableFrame.width
//                 implicitHeight: tableFrame.delegateHeight
//                 color: tableView.myIsRowSelected(index) ? "grey" : tableView.getRow(index) % 2 == 0 ? "lightblue": "white"

//                 HoverHandler {
//                     id: stylus
//                     onHoveredChanged: () => {
//                                           if (hovered)
//                                             mySelectionModel.select(myproxymodel.index(tableView.getRow(index), 0), ItemSelectionModel.Select | ItemSelectionModel.Rows)
//                                           else
//                                             mySelectionModel.select(myproxymodel.index(tableView.getRow(index), 0), ItemSelectionModel.Deselect | ItemSelectionModel.Rows)
// //                                          console.log(hovered)
// //                                          console.log(mySelectionModel.selectedIndexes)
// //                                          mySelectionModel.select(myproxymodel.index(index, i), ItemSelectionModel.Select | ItemSelectionModel.Current)
//                                       }
//                 }

//                 MouseArea {
//                     anchors.fill: parent

//                     acceptedButtons: Qt.LeftButton | Qt.RightButton

//                     Text {
//                         text: model.display
//                         font.family: "Roboto"
//                         leftPadding: 40
//                         anchors.verticalCenter: parent.verticalCenter
//                         font.pixelSize: 20
//                     }

//                     onClicked: (mouse) => {
// //                                   console.log(myproxymodel.rowCount())
// //                                   console.log("index " + model.index + " clicked!")
//                                    mySelectionModel.setCurrentIndex(myproxymodel.index(tableView.getRow(index), 0), ItemSelectionModel.Select | ItemSelectionModel.Current)

// //                                   console.log("mySelectionModel.selectedIndexes: " + mySelectionModel.selectedIndexes)

//                                    //                console.log(mouse.button)
//                                    if (mouse.button === Qt.RightButton) {
//                                        //                    console.log("right click!")
//                                        contextMenu.popup()
//                                    }
//                                }

//                     Menu {
//                         id: contextMenu
//                         MenuItem {
//                             text: "Delete"
//                             onTriggered: () => {
//                                              //                        console.log("delete trigger on index " + model.index)
// //                                             let rowIndex = model.index % tableView.rows
// //                                             mymodel.myRemoveRow(rowIndex)
//                                              myproxymodel.myRemoveRow(mySelectionModel.currentIndex)
//                                          }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }



import QtQuick
import QtQuick.Controls 
import Qt.labs.qmlmodels 
 
Rectangle 
{
    id: root
    width: 919
    height: 475
    property var tableViewCurrIndex: -1
    // anchors 
    // {
    //     top: parent.top
    //     topMargin: 88
    //     horizontalCenter: parent.horizontalCenter
    // }
    Item 
    {
        id: control
        implicitHeight: parent.height
        implicitWidth: parent.width

        //表头行高
        property int headerHeight: 48
        //行高
        property int rowHeight: 48
        //滚动条
        property color scrollBarColor: "#E5E5E5"
        property int scrollBarWidth: 7
        //列宽
        property variant columnWidthArr: [control.width *0.1, control.width *0.3, control.width * 0.2, control.width * 0.2,control.width * 0.2]

        property var horHeader: ["num", "序列号", "亮度","x","y"]
        property int selected: -1

        property var datas: [
            { "num": 1, "序列号": "123456789", "lv": "200", "x": "0.313", "y": "0.329" },
            { "num": 2, "序列号": "223456789", "lv": "200", "x": "0.313", "y": "0.329" },
            { "num": 3, "序列号": "333456789", "lv": "200", "x": "0.313", "y": "0.329" },
            { "num": 4, "序列号": "444456789", "lv": "200", "x": "0.313", "y": "0.329" },
            { "num": 5, "序列号": "555556789", "lv": "200", "x": "0.313", "y": "0.329" },
            { "num": 6, "序列号": "666666789", "lv": "200", "x": "0.313", "y": "0.329" },
            { "num": 7, "序列号": "777777789", "lv": "200", "x": "0.313", "y": "0.329" },
            { "num": 8, "序列号": "888888889", "lv": "200", "x": "0.313", "y": "0.329" }
        ]

        //展示数据
        TableView {
            id: table
            anchors {
                fill: parent
                topMargin: control.rowHeight
            }

            clip: true
            boundsBehavior: Flickable.StopAtBounds
            columnSpacing: 0
            rowSpacing: 0

            //内容行高
            rowHeightProvider: function (row) {
                return control.headerHeight
            }
            //内容列的列宽
            columnWidthProvider: function (column) {
                return control.columnWidthArr[column]
            }
            ScrollBar.vertical: ScrollBar {
                id: scroll_vertical
                anchors.right: parent.right
                
                anchors.rightMargin: 0
                // 确保将 ScrollBar 的 size 正确绑定
                size: table.contentHeight > 0 ? table.height / table.contentHeight  : 1.0
                // position: table.contentY / table.contentHeight
                // contentItem: Rectangle {
                //     visible: (scroll_vertical.size < 1.0)
                //     implicitWidth: control.scrollBarWidth
                //     color: control.scrollBarColor
                // }
                
            }
onContentHeightChanged: console.log("Content Height - :", table.height,table.contentHeight)
            ScrollBar.horizontal: ScrollBar {
                id: scroll_horizontal
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                // 确保将 ScrollBar 的 size 正确绑定
                size: table.contentWidth > 0 ? table.width / table.contentWidth : 1.0
                position: table.contentX / table.contentWidth
                // contentItem: Rectangle {
                //     visible: (scroll_horizontal.size < 1.0)
                //     implicitHeight: control.scrollBarWidth
                //     color: control.scrollBarColor
                // }

            }

            model: TableModel {

                TableModelColumn {
                    display: "num"
                }
                TableModelColumn {

                    display: "序列号"
                }
                TableModelColumn {
                    display: "lv"
                }

                TableModelColumn {
                    display: "x"
                }
                TableModelColumn {

                    display: "y"
                }
                rows: control.datas
            }

            delegate: Rectangle {
                color: control.selected === row ? "#EAF1FF" : "white" //点击改变行背景颜色

                Text {
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: display
                    font.pixelSize: 15
                    color: "#707070"
                }
                Rectangle {
                    color: "#E5E5E5"
                    width: parent.width
                    height: 1
                    anchors {
                        bottom: parent.bottom

                    }
                }

                // MouseArea {
                //     anchors.fill: parent

                //     onClicked: {
                //         // 点击后新增数据
                //         control.datas.push({
                //             "num": control.datas.length + 1, // 动态生成行号
                //             "序列号": "新增序列号",
                //             "lv": "150",
                //             "x": "0.310",
                //             "y": "0.320"
                //         })
                //         table.model.rows = control.datas
                //         console.log(table.model.rows.length,JSON.stringify(table.model.rows[row]))
                //     }
                // }
                    // 独立的 MouseArea，用于捕获右键事件
            }

        }
//表头样式
        MouseArea 
        {
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            // propagateComposedEvents: false
            onPressed: function(mouse)
            {
                if (mouse.button === Qt.RightButton) 
                {
                    // 显示弹出菜单
                    if (control.datas.length === 0) 
                    {
                        // 当表格为空时，直接弹出菜单并设置默认索引
                        tableViewCurrIndex = -1;
                    } 
                    else 
                    {

                        let row = Math.floor((mouse.y - table.contentY) / control.rowHeight);
                        console.log("row: ",row,mouse.y, table.contentY,control.rowHeight);
                        // 检查是否点击在有效的行内
                        if (row >= 0 && row < control.datas.length) 
                        {
                            tableViewCurrIndex = row;
                        } 
                        else 
                        {
                            tableViewCurrIndex = -1; // 点击无效区域
                        }
                                                        // 表格不为空，获取点击的行索引
                        // tableViewCurrIndex  = Math.floor(mouse.y / tableView.rowHeight);
                        // console.log("tableViewCurrIndex: " + tableViewCurrIndex)
                    }
                    contextMenu.popup();
                }
            }
        }
        Item {
            id: header_horizontal
            anchors {
                left: parent.left
                right: parent.right
            }
            height: control.rowHeight
            z: 2

            Row {
                id: header_horizontal_row
                anchors.fill: parent
                leftPadding: -table.contentX
                clip: true
                spacing: 0

                Repeater {
                    model: table.columns > 0 ? table.columns : 0

                    Rectangle {
                        id: header_horizontal_item
                        width: table.columnWidthProvider(index) + table.columnSpacing
                        height: control.rowHeight-1
                        color: "#F8F8F8"

                        Text {
                            anchors.centerIn: parent
                            text: control.horHeader[index]
                            font.pixelSize: 18
                            color: "#707070"
                        }
                        Rectangle {
                            height: 1
                            width: parent.width
                            anchors.bottom: parent.bottom
                            color: "#E5E5E5"
                        }
                        Rectangle {
                            height: 1
                            width: parent.width
                            anchors.top: parent.top
                            color: "#E5E5E5"
                        }
                    }
                }
            }
        }
    }



    Menu 
    {
        id: contextMenu
        MenuItem {
            text: "增加一行"
            onTriggered: root.addRow()
        }
        MenuItem {
            text: "删除最后一行"
            onTriggered: root.removeRow()
        }
        MenuItem {
            text: "删除当前行"
            onTriggered: 
            {
            root.removeRowAt(tableViewCurrIndex)
            }
        }
        MenuItem {
            text: "删除所有行"
            onTriggered: root.clearRows()
        }

    }
    
             // 增加一行
    function addRow() {
        let newRow = {
            "num": control.datas.length + 1,
            "序列号": "新增序列号",
            "lv": "150",
            "x": "0.310",
            "y": "0.320"
        }
        control.datas.push(newRow)
        table.model.rows = control.datas // 更新模型
    }

    // 删除最后一行
    function removeRow() {
        if (control.datas.length > 0) {
            control.datas.pop()
            table.model.rows = control.datas // 更新模型
        }
    }

    // 删除所有行
    function clearRows() {
        control.datas = []
        table.model.rows = control.datas // 更新模型
    }

    // 删除第 n 行（从 0 开始索引）
    function removeRowAt(index) {
        if (index >= 0 && index < control.datas.length) {
            control.datas.splice(index, 1)
            // 更新行号
            for (let i = index; i < control.datas.length; i++) {
                control.datas[i].num = i + 1
            }
            table.model.rows = control.datas // 更新模型
        }
    }
}