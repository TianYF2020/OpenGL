import QtQuick 2.
import QtQuick 2.12
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Window 2.12
import TableModel 1.0
Rectangle
{
    id: mTabelView
    //    implicitHeight: parent.width
    //    implicitWidth: parent.height
    //行表头-竖向的
    property int verHeaderHeight: 30
    property int verHeaderWidth: 50
    //列表头-横向的
    property int horHeaderHeight: 30
    //property int horHeaderWidth: 30
    //滚动条
    property color scrollBarColor: "cyan"
    property int scrollBarWidth: 6
    //列宽
    property int leftwith:width -verHeaderWidth
    property int fontSize: 15
    property variant columnWidthArr: [ verHeaderWidth,leftwith/3, leftwith/6, leftwith/2]
    property var myModel: null;
    property var headColor
    property var numColor: "black"
    property int allHeight:0
    color: "transparent"
    //表格内容（不包含表头）
    TableView
    {
        id: table_view
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        //        anchors.leftMargin: verHeaderWidth
        anchors.top: parent.top
        anchors.topMargin: verHeaderHeight
        width: parent.width
        height: parent.height -verHeaderHeight
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        columnSpacing: 0
        rowSpacing: 0
        rowHeightProvider: function (row)
        {
            return mTabelView.verHeaderHeight;
        }
        //此属性可以保存一个函数，该函数返回模型中每个列的列宽
        columnWidthProvider: function (column)
        {
            return mTabelView.columnWidthArr[column];
        }
        ScrollBar.vertical: ScrollBar {
            id: scroll_vertical
            anchors.right: parent.right
            anchors.rightMargin: 1
            contentItem: Rectangle
            {
                color: "#bec1c1"
                //                visible: (scroll_vertical.size<1.0)
                visible:true
                implicitWidth: mTabelView.scrollBarWidth
            }
        }

        //model是在C++中定义的，和QtC++是类似的
        model: myModel
        delegate: Rectangle
        {
            color: "transparent"
            border.color:"#AAAAAA"
            TextInput
            {
                color: "white"
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                selectByMouse: true
                readOnly: true
                text: model.value
                font.pixelSize: fontSize
            }
        }

        onRowsChanged:
        {
            if(rows<table_view.height/horHeaderHeight)   //无奈规避，table_view.contentHeight好像有点bug，清空的row时候table_view.contentHeigh 值没变
            {
                table_view.contentY = 0
                scroll_vertical.visible = false
            }
            else
            {
                allHeight = rows*horHeaderHeight
                if(allHeight > table_view.height)
                {
                    scroll_vertical.visible = true
                    table_view.contentY = allHeight - (table_view.height)
                }
                //                if(table_view.contentHeight > table_view.height)
                //                {
                //                    scroll_vertical.visible = true
                //                    table_view.contentY = table_view.contentHeight - (table_view.height-  anchors.topMargin)
                //                }
            }
        }
        //        onContentHeightChanged:
        //        {
        //            console.log("kuang",table_view.contentHeight,"heigth", table_view.height)
        //        }
    }
    //横项表头
    Item
    {
        id: header_horizontal
        anchors
        {
            left: parent.left
            right: parent.right
            //leftMargin: mTabelView.verHeaderWidth
        }
        height: mTabelView.horHeaderHeight
        Row
        {
            id: header_horizontal_row
            clip: true
            spacing: 0
            Repeater
            {
                model: table_view.columns > 0 ? table_view.columns : 0
                Rectangle
                {
                    id: header_horizontal_item
                    width: table_view.columnWidthProvider(index)+table_view.columnSpacing
                    height: mTabelView.horHeaderHeight
                    color: headColor
                    Text
                    {
                        anchors.centerIn: parent
                        color: "white"
                        text: myModel.headerData(index, Qt.Horizontal)
                        font.pixelSize: fontSize
                    }
                    Rectangle
                    {
                        width: 1
                        height: parent.height
                        anchors.right: parent.right
                        color: "white"
                        opacity: 0.5
                    }
                    MouseArea
                    {
                        width: 3
                        height: parent.height
                        anchors.right: parent.right
                        cursorShape: Qt.SplitHCursor
                        onPressed: header_horizontal.posXTemp=mouseX;
                        onPositionChanged:
                        {
                            if((header_horizontal_item.width-(header_horizontal.posXTemp-mouseX))>10)
                            {
                                header_horizontal_item.width-=(header_horizontal.posXTemp-mouseX);
                            }
                            else
                            {
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
        Rectangle
        {
            id:num
            z:100
            width: mTabelView.verHeaderWidth
            height: mTabelView.horHeaderHeight
            border.color: "white"
            border.width: 1
            Text
            {
                z:parent.z
                id: name
                color: "White"
                text: qsTr("Num")
                anchors.centerIn: parent
                font.pixelSize: fontSize
            } color: numColor
        }
    }
}
