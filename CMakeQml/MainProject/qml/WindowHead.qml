import QtQuick
import QtQuick.Controls
ToolBar {
    id: root
    width: parent.width
    height: 40
    clip: true // 启用裁剪效果
    property bool fullStates: false
    background: Rectangle 
    {
        anchors.fill: parent
        color: "#386dfa"
    }
    // property string buttonColor: "#ecf0f1"
    // property int spare: 50
    signal closeWindow
    signal moveWindow(var delta)
    signal minimizeWindow
    signal maximizeWindow
    signal defaultWindow
    signal exitFullScreenWindow

    // function setHeadTabButton(index)
    // {
    //     repeaterTabBtn.model = qmlSettings.tabBarText[index]
    // }

    //鼠标拽动窗口，最底层
    MouseArea 
    {
        x: 0 // 设置鼠标区域左上角的X坐标为0
        y: 0 // 设置鼠标区域左上角的Y坐标为0
        z: 1 // 设置鼠标区域的Z轴顺序，确保它在其他元素之上
        anchors.fill: parent // 将鼠标区域的大小调整为填充父元素的大小
        acceptedButtons: Qt.LeftButton // 只接受左键点击事件
        property point clickPos: "0,0" // 定义一个属性clickPos来存储鼠标点击的位置，初始值为(0,0)
        // onReleased: mouse.accepted = false // 当鼠标释放时，取消对鼠标事件的接受
        // onClicked: mouse.accepted = false // 当鼠标点击时，取消对鼠标事件的接受
        // acceptedButtons: Qt.LeftButton | Qt.RightButton 
        onPressed:function(mouse)
        {
            clickPos = Qt.point(mouse.x, mouse.y) // 当鼠标按下时，记录当前鼠标位置到clickPos
        }
        onPositionChanged:function(mouse)
        {
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y) // 计算鼠标移动的距离差
            moveWindow(delta) // 调用moveWindow函数，根据鼠标移动的距离差来移动窗口
        }
    }
    Image
    {
        id: logo
        width: parent.height
        height: parent.height
        // scale: 0.9
        source: "qrc:/icons/logo.png"
        fillMode: Image.PreserveAspectFit
        anchors.left: parent.left
        // anchors.leftMargin: 5
    }
    TabBar
    {
         id: tabBar
         clip: true
         anchors.left: logo.right
         anchors.top: parent.top
         anchors.leftMargin: 10
         width: 300
         height: parent.height
         spacing: 5 
         z:10
         background: Rectangle
         {
            color: "transparent"
         }
        Repeater 
        {
            id: repeaterTabBtn
            model: settings.tabBarText
            TabButton 
            {
                text: modelData
                width: 120
                anchors.top: parent.top
                // anchors.topMargin: 8
                height: parent.height 
                background: Rectangle 
                {
                    radius: 10 
                    color: "transparent" 
                    border.width: (tabBar.currentIndex === index)?1:0
                    border.color: (tabBar.currentIndex === index)?"white":"black"
                }
                contentItem: Text 
                {
                    color: (tabBar.currentIndex === index)?"white":"black"
                    text: parent.text
                    font.bold: true
                    font.pointSize: 16
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                onClicked:
                {
                    settings.currentIndex = tabBar.currentIndex;
                }
            }
        }
    }

    ToolButton {
        id: minimize // 定义一个ToolButton组件，并为其设置唯一的ID为minimize
        z: 2 // 设置按钮的Z轴顺序，确保其在其他元素之上
        width: parent.height
        height: parent.height
        icon.source: "qrc:/icons/min.png" // 设置按钮图标的源路径
        // icon.color: buttonColor // 设置按钮图标的颜色为buttonColor变量的值
        anchors.right: max.left // 将按钮定位到父组件的左侧
        padding: 5
        scale: 0.9 
        anchors.verticalCenter: parent.verticalCenter 
        onClicked: {
            minimizeWindow() 
        }
        background: Rectangle{
            color: minimize.hovered ? "lightgrey" : "transparent"
        }
    }

    ToolButton 
    {
        id: max // 定义一个ToolButton的ID为close
        width: parent.height
        height: parent.height
        padding: 3
        icon.source: (fullStates === true ? "qrc:/icons/reserve.png": "qrc:/icons/max.png")
        // icon.color: buttonColor // 设置按钮图标的颜色，使用buttonColor变量
        anchors.right: close.left // 将按钮定位到父组件的右侧
        anchors.verticalCenter: parent.verticalCenter // 将按钮垂直居中于父组件
        z: 2 // 设置按钮的Z轴顺序，使其位于其他元素之上
        onClicked: 
        {
            maximizeWindow() // 当按钮被点击时，调用closeWindow函数
            fullStates =!fullStates // 切换states的值
        }
        background: Rectangle 
        {
            color: max.hovered ? "lightgrey" : "transparent"
        }
    }

    ToolButton 
    {
        id: close // 定义一个ToolButton的ID为close
        width: parent.height
        height: parent.height
        padding: 3
        // icon.color: buttonColor // 设置按钮图标的颜色，使用buttonColor变量
        anchors.right: parent.right // 将按钮定位到父组件的右侧
        anchors.verticalCenter: parent.verticalCenter // 将按钮垂直居中于父组件
        icon.source: "qrc:/icons/close.png" // 设置按钮图标的源路径
        z: 2 // 设置按钮的Z轴顺序，使其位于其他元素之上
        onClicked: {
            closeWindow() // 当按钮被点击时，调用closeWindow函数
        }
        background: Rectangle 
        {
            anchors.fill: parent
            color: close.hovered ? "lightgrey" : "transparent"
        }
    }

}
