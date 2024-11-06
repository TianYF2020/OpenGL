import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Item {
    id: root
    width: 600
    height: 400
    property var rowsDiv: 5
    property var columnsDiv: 5
    property real startX: 0
    property real startY: 0
    property var gridSize: 10
    property bool isSelecting: false // 新增属性
    RowLayout 
    {
        id: graiTitle
        width: parent.width
        height: 30
        spacing: 10
        TextField {
            id: rowInput
            text: rowsDiv.toString()
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 16
            Layout.preferredHeight: parent.height
            placeholderText: "输入行数 (m)"
        }
        TextField {
            id: columnInput
            text: columnsDiv.toString()
            verticalAlignment: Text.AlignVCenter
            Layout.preferredHeight: parent.height
            font.pointSize: 16
            placeholderText: "输入列数 (n)"
        }
        Button {
            text: "生成网格"
            onClicked: {
                rowsDiv = parseFloat(rowInput.text)
                columnsDiv = parseFloat(columnInput.text)
                gridView.clearGrid(rowsDiv, columnsDiv);
            }
        }
    }

    ListModel
    {
        id: gridModel
        Component.onCompleted: 
        {
            // 初始化m*n个矩形的isSelect状态
            for (var i = 0; i < rowsDiv * columnsDiv; i++) 
            {
                append({ isSelected: false })
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


        GridView 
        {
            id: gridView
            width: parent.width
            height: parent.height
            cellWidth: parent.width / columnsDiv;
            cellHeight: parent.height / rowsDiv;
            flickableDirection: Flickable.AutoFlickDirection
            model: gridModel

            delegate: Rectangle
            {
                width: gridView.cellWidth
                height: gridView.cellHeight
                color: (isSelected === false) ? "lightgray" : "red";
                border.color: "black"
                // MouseArea
                // {
                //     anchors.fill: parent
                //     onClicked: 
                //     {
                //         // isSelected = !isSelected
                //         if (!gridView.isSelecting) 
                //         { // 只有在不选择的情况下才反转颜色
                //             isSelected = !isSelected;
                //         }
                //     }  
                // }
            }
            function clearGrid(rows, cols)
            {
                model.clear();
                for (var i = 0; i < rows; i++) 
                {
                    for (var j = 0; j < cols; j++) 
                    {
                        model.append({isSelected: false});
                    }   
                }        
            }
            function resetGrid()
            {
                for (var i = 0; i < model.count; i++)
                {
                   gridModel.set(i, {isSelected: false})
                }     
            }

            function setColor(row, col,state)
            {
                var temp = row * columnsDiv + col;
                if(temp < gridModel.count)
                {
                    gridModel.set(row * columnsDiv + col, {isSelected: state})
                }    
            }    
        }
        Rectangle
        {
            id: selectionRect
            color: "transparent"
            border.color: "black"
            border.width: 1
            visible: false
            x: Math.min(startX, mouseArea.mouseX)
            y: Math.min(startY, mouseArea.mouseY)
            width: Math.abs(mouseArea.mouseX - startX)
            height: Math.abs(mouseArea.mouseY - startY)
        }

        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
            propagateComposedEvents: true
            property var startRowIndex: 0  
            property var endRowIndex: 0
            property var startColumIndex: 0  
            property var endColumIndex: 0
            property bool isMove: false
            acceptedButtons: Qt.LeftButton | Qt.RightButton 
            onPressed:function(mouse)
            {
                if (mouse.button === Qt.RightButton) 
                {
                    menu.popup() // 打开菜单
                }
                else
                {
                    startX = mouseX;
                    startY = mouseY;
                    selectionRect.visible = true; 
                    isMove = false
                }

            }
            onPositionChanged:function(mouse)
            {

                if (mouse.buttons & Qt.LeftButton) 
                {
                    selectionRect.width = Math.abs(mouseX - startX)
                    selectionRect.height = Math.abs(mouseY - startY)
                    if(mouseY > startY)
                    {
                        startRowIndex = Math.floor(startY /gridView.cellHeight)
                        endRowIndex = Math.ceil(mouseY/gridView.cellHeight)                    
                    }
                    else
                    {
                        startRowIndex = Math.floor(mouseY /gridView.cellHeight)
                        endRowIndex = Math.ceil(startY/gridView.cellHeight)
                    }                    
                    if(mouseX > startX)
                    {
                        startColumIndex = Math.floor(startX /gridView.cellWidth)
                        endColumIndex = Math.ceil(mouseX /gridView.cellWidth)
                    }                    
                    else
                    {
                        startColumIndex = Math.floor(mouseX /gridView.cellWidth) 
                        endColumIndex = Math.ceil(startX /gridView.cellWidth) 

                    }
                    startColumIndex = startColumIndex < 0 ? 0 : startColumIndex
                    startRowIndex = startRowIndex < 0 ? 0 : startRowIndex
                    endRowIndex = endRowIndex > rowsDiv ? rowsDiv : endRowIndex
                    endColumIndex = endColumIndex > columnsDiv ? columnsDiv : endColumIndex
                    for(let i = startRowIndex ; i < endRowIndex; i++)
                    {
                        for(let j = startColumIndex; j < endColumIndex;j++)
                        {
                            gridView.setColor(i,j, true);
                        }
                    }  
                    isMove = true
                }

            }
            onReleased:function(mouse)
            {
                if (mouse.button === Qt.LeftButton) 
                {
                    selectionRect.width = 0
                    selectionRect.height = 0
                    if(!isMove)
                    {
                        var index = Math.floor(mouseY /gridView.cellHeight)*columnsDiv + Math.floor(mouseX/gridView.cellWidth)
                        gridModel.setProperty(index, "isSelected", !gridModel.get(index).isSelected)
                    }
                    isMove = false
                }

            }
        }

        Menu 
        {
            id: menu

            MenuItem {
                text: "矫正 "
                onTriggered: console.log("选项 1 被选择")
            }
            MenuItem {
                text: "拷贝矫正文件"
                onTriggered: console.log("选项 2 被选择")
            }
            MenuItem {
                text: "烧录矫正文件"
                onTriggered: console.log("选项 3 被选择")
            }
            MenuItem {
                text: "复位 "
                onTriggered: 
                {
                    gridView.resetGrid()
                }
            }
        }
    }
}
       



