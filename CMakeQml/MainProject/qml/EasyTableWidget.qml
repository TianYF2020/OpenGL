import QtQuick 2.15
import QtQuick.Controls 2.15
import EasyModel 1.0

//自定义QtQuick 2中的TableView
Item 
{
    id: control
    implicitHeight: 300
    implicitWidth: 500

    //行表头-竖向的
    property int verHeaderHeight: 30
    property int verHeaderWidth: 30
    //列表头-横向的
    property int horHeaderHeight: 30
    //property int horHeaderWidth: 30
    //滚动条
    property color scrollBarColor: "cyan"
    property int scrollBarWidth: 3
    //列宽
    property variant columnWidthArr: [100,100,100,200]
    property var myModel: null;
  

    //表格内容（不包含表头）
    TableView{
        id: table_view
        anchors{
            fill: parent
            leftMargin: control.verHeaderWidth
            topMargin: control.horHeaderHeight
        }

        clip: true
        boundsBehavior: Flickable.StopAtBounds
        columnSpacing: 1
        rowSpacing: 1
        //视图的高度
        //contentHeight: rowHeightProvider(0) * rows + rowHeightProvider(rows-1)
        //视图的宽度
        //contentWidth:
        //content内容区域边距，但是不影响滚动条的位置
        //leftMargin:
        //topMargin:
        //此属性可以包含一个函数，该函数返回模型中每行的行高
        rowHeightProvider: function (row) {
            return control.verHeaderHeight;
        }
        //此属性可以保存一个函数，该函数返回模型中每个列的列宽
        columnWidthProvider: function (column) {
            return control.columnWidthArr[column];
            //return Math.max(1, (table_view.width - leftMargin) / table_view.columns)
        }
        ScrollBar.vertical: ScrollBar {
            id: scroll_vertical
            anchors.right: parent.right
            anchors.rightMargin: 2
            //active: table_view.ScrollBar.vertical.active
            //policy: ScrollBar.AsNeeded
            contentItem: Rectangle{
                visible: (scroll_vertical.size<1.0)
                implicitWidth: control.scrollBarWidth
                color: control.scrollBarColor
            }
        }

        ScrollBar.horizontal: ScrollBar {
            id: scroll_horizontal
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            //active: table_view.ScrollBar.vertical.active
            //policy: ScrollBar.AsNeeded
            contentItem: Rectangle{
                visible: (scroll_horizontal.size<1.0)
                implicitHeight: control.scrollBarWidth
                color: control.scrollBarColor
            }
        }
        //model是在C++中定义的，和QtC++是类似的
        model: myModel
        delegate: Rectangle{
            color: (model.row%2)?"orange":Qt.darker("orange")
            TextInput{
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                //elide: Text.ElideRight
                selectByMouse: true
                selectedTextColor: "black"
                selectionColor: "white"

                //获取单元格对应的值
                text: model.value
                onEditingFinished: {
                    model.edit=text;
                    console.log("edit",model.value)
                }
            }
        }
    }

    //横项表头
    Item{
        id: header_horizontal
        anchors{
            left: parent.left
            right: parent.right
            leftMargin: control.verHeaderWidth
        }
        height: control.horHeaderHeight
        z: 2
        //暂存鼠标拖动的位置
        property int posXTemp: 0
        MouseArea{
            anchors.fill: parent
            onPressed: header_horizontal.posXTemp=mouseX;
            onPositionChanged: {
                if(table_view.contentX+(header_horizontal.posXTemp-mouseX)>0){
                    table_view.contentX+=(header_horizontal.posXTemp-mouseX);
                }else{
                    table_view.contentX=0;
                }
                header_horizontal.posXTemp=mouseX;
            }
        }
        Row {
            id: header_horizontal_row
            anchors.fill: parent
            leftPadding: -table_view.contentX
            clip: true
            spacing: 0

            Repeater {
                model: table_view.columns > 0 ? table_view.columns : 0

                Rectangle {
                    id: header_horizontal_item
                    width: table_view.columnWidthProvider(index)+table_view.columnSpacing
                    height: control.horHeaderHeight
                    color: "purple"

                    Text {
                        anchors.centerIn: parent
                        text: myModel.headerData(index, Qt.Horizontal)
                    }
                    Rectangle{
                        width: 1
                        height: parent.height
                        anchors.right: parent.right
                        color: "black"
                        opacity: 0.5
                    }
                    MouseArea{
                        width: 3
                        height: parent.height
                        anchors.right: parent.right
                        cursorShape: Qt.SplitHCursor
                        onPressed: header_horizontal.posXTemp=mouseX;
                        onPositionChanged: {
                            if((header_horizontal_item.width-(header_horizontal.posXTemp-mouseX))>10){
                                header_horizontal_item.width-=(header_horizontal.posXTemp-mouseX);
                            }else{
                                header_horizontal_item.width=10;
                            }
                            header_horizontal.posXTemp=mouseX;
                            control.columnWidthArr[index]=(header_horizontal_item.width-table_view.columnSpacing);
                            //刷新布局，这样宽度才会改变
                            table_view.forceLayout();
                        }
                    }
                }
            }
        }
    }

    //竖向表头
    Column {
        id: header_verical
        anchors{
            top: parent.top
            bottom: parent.bottom
            topMargin: control.horHeaderHeight
        }
        topPadding: -table_view.contentY
        z: 2
        clip: true
        spacing: 1
        Repeater {
            model: table_view.rows > 0 ? table_view.rows : 0
            Rectangle {
                width: control.verHeaderWidth
                height: table_view.rowHeightProvider(index)
                color: "green"
                Text {
                    anchors.centerIn: parent
                    text: myModel.headerData(index, Qt.Vertical)
                }
            }
        }
    }
    // 增加一行数据的函数
    function addRow(data) {
        myModel.addRow(data);
    }

    // 删除最后一行的函数
    function removeLastRow() {
        myModel.removeLastRow();
    }

    // 删除所有行的函数
    function removeAllRows() {
        myModel.removeAllRows();
    }



}
