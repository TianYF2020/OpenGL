import QtQuick
import QtQuick.Controls
import QtQuick.Timeline 
import QtQuick.Window 
import QtQuick.Layouts 
import QtQuick.Window
import QtQuick.Effects
import QtQuick.Controls.Material
import LearnOpenGL 
import EasyModel 1.0
import "CustomMultiEffect"

ApplicationWindow    
{
    id:uiMainContol
    width: 1080 + headLine.height
    height: 720
    visible: true
    title: qsTr("Hello World")
    color:"#00000000"
    flags: Qt.Window | Qt.FramelessWindowHint 
    Material.theme: Material.Dark // 使用暗色主题
    readonly property real dp: 0.2 + Math.min(width, height) / 1200
    property var stretchState: false 
    property var showHideAnimationSpeed: 400
    property var tabBarTextList: ["界面1","界面2","界面3","界面4"]
    property var pageQmlList: ["qrc:/qml/Page1.qml", "qrc:/qml/Page2.qml","qrc:/qml/Page3.qml","qrc:/qml/Page4.qml"]


    function switchPage(index) {
        if (index >= 0 && index < pageList.length) {
            stackView.replace(pageList[index])  // 根据索引切换页面
        }
    }

    Rectangle 
    {
        id: inrec
        anchors.fill: parent // 矩形填充父组件
        clip: true
        radius: 10 // 圆角半径设置为10
        opacity:1
        // layer.enabled: true
        // layer.effect: OpacityMask
        // {
        //     maskSource: Rectangle
        //     {
        //         width: inrec.width
        //         height: inrec.height
        //         radius: inrec.radius
        //     }
        // }

        WindowHead 
        {
            id: headLine
            height: 40 
            width: parent.width
            z: 10
            anchors.left: parent.left // 标题栏左部锚定在inrec的左部
            anchors.top: parent.top // 标题栏顶部锚定在inrec的顶部
            onMoveWindow: function(delta)
            { // 当移动窗口时触发的事件
                uiMainContol.setX(uiMainContol.x + delta.x) // 更新窗口的X坐标
                uiMainContol.setY(uiMainContol.y + delta.y) // 更新窗口的Y坐标
            }

            onCloseWindow: { // 当关闭窗口时触发的事件
                uiMainContol.close() // 关闭窗口
            }
            onMinimizeWindow: { // 当最小化窗口时触发的事件
                // uiMainContol.hide()
                // uiMainContol.showMinimized() // 最小化窗口
                if (uiMainContol.isFullScreen) 
                {
                    // 隐藏窗口并直接最小化，避免恢复正常大小
                    uiMainContol.hide()   // 隐藏窗口
                    uiMainContol.showMinimized()  // 然后最小化窗口
                } 
                else 
                {
                    uiMainContol.showMinimized()  // 非全屏时正常最小化
                }
            }
            onMaximizeWindow: 
            { // 当最大化窗口时触发的事件
                if(headLine.fullStates === false) 
                {
                    uiMainContol.showFullScreen()
                }
                else
                {
                    uiMainContol.showNormal()
                }
            }
            onDefaultWindow: {
                console.log("window resver size")
                uiMainContol.showNormal()
                // uiMainContol.resize(1080 + headLine.height,720)
            }
        }
        Settings {
            id: settings
            onReseted: {
                settingsView.resetSettings();
            }
        }

        // Settings {
        //     id: defaultSettings
        // }

        Rectangle
        {
            anchors.left: parent.left
            anchors.top: headLine.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom  

            SettingsView {
            id: settingsView
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            z:999
            // anchors.left: parent.left
            // anchors.margins: 20
            visible: settings.showSettingsView
            // Component.onCompleted: {
            //     settings.reset();
            // }
            // onSendDevType:function(value)
            // {
            //     pageone.item.revBtn.setButtonText(value)
            // }
        }
        TabBar
        {
            id: tabBar
            anchors.left: settingsView.right
            anchors.right: parent.right
            // anchors.top: headLine.bottom
            height: 40
            currentIndex: 0
            clip: true

            Repeater
            {
                model: tabBarTextList
                delegate: TabButton
                {
                    height: parent.height
                    text: modelData
                }
            }
  
        }

        StackLayout 
        {
            id: stackLayout
            anchors.top:tabBar.bottom
            anchors.left: settingsView.right
            anchors.bottom: mainArea.top
            anchors.right: parent.right
            currentIndex: tabBar.currentIndex

            Repeater
            {
                model: pageQmlList
                delegate: Loader
                {
                    source: modelData
                }
            }

            // // Page 1
            // Loader {
            //     id: pageone
            //     source: "qrc:/qml/Page1.qml"
            //     onLoaded: {
            //         item.pageParentItem = settingsView;  // 传递值给加载的子组件
            //     }
            // }

            // // Page 2
            // Loader 
            // {
            //     source: "qrc:/qml/Page2.qml"
            // }

            // // Page 2
            // Loader 
            // {
            //     source: "qrc:/qml/Page3.qml"
            // }
        }


    // StackView {
    //     id:stackView
    //     anchors {
    //         left: settingsView.right
    //         right: parent.right
    //         bottom: mprogress.top
    //         top: parent.top
    //     }

    //     initialItem: Page1 {}
    //     // currentIndex: 1
    // }

            // FBOItem
        // {
        //     id:myView
        //     width: parent.width*0.5
        //     height: parent.height*0.5
        // }


        Rectangle
        {
            id: mainArea
            // anchors.left: settingsView.right
            // anchors.right: parent.right
            anchors.left: settingsView.right
            anchors.right: parent.right
            // anchors.top: parent.top
            anchors.bottom: parent.bottom
            // color: "black"
            height: mprogress.height + mlog.height
            Rectangle
            {
                id: mprogress
                width: parent.width
                height: 20
                color: "#666666"
                anchors.bottom: mlog.top
                anchors.left: parent.left
                RowLayout
                {
                    anchors.fill: parent
                    ProgressBar
                    {
                        Layout.preferredWidth: parent.width *0.9
                        Layout.preferredHeight: parent.height
                        height: 20
                        value: 50  // 当前进度值
                        from: 0   // 最小值
                        to: 100   // 最大值
                        // anchors.verticalCenter: parent.verticalCenter
                    }
                    Item 
                    {
                        id: lightsSettings
                        Layout.preferredWidth: parent.width *0.1
                        Layout.preferredHeight: parent.height

                        Rectangle 
                        {
                            anchors.fill: parent
                            color: "#404040"
                            border.width: 1
                            border.color: "#808080"
                            opacity: 0.4
                            Image 
                            {
                                x: 8
                                source: "images/arrow.png"
                                anchors.verticalCenter: parent.verticalCenter
                                rotation: stretchState? 270 : 90
                                Behavior on rotation {
                                    NumberAnimation {
                                        duration: 400
                                        easing.type: Easing.InOutQuad
                                    }
                                }
                            }
                            MouseArea 
                            {
                                anchors.fill: parent
                                onClicked: {
                                    stretchState = !stretchState
                                    if (stretchState) {
                                        mlog.height = 400
                                    //     hideAnimation.stop();
                                    //     showAnimation.start();
                                    } else {
                                                                            mlog.height = 200
                                    //     showAnimation.stop();
                                    //     hideAnimation.start();
                                    }

                                }
                            }
                        }
                    }
                }
            }
            LogShow
            {
                id: mlog
                width: parent.width
                height: 200
                anchors.left: parent.left
                anchors.bottom: parent.bottom

                        // 动画效果
                Behavior on height {
                    NumberAnimation {
                        duration: 400
                    }
                }
            }
        }

        }
    }

    // Column
    // {
    //     width: parent.width
    //     height: parent.height
    //     MyInputField
    //     {
    //         id: test
    //         width: 100
    //         height: 50
    //         myText:"hello"
    //         cppFunction: myUIControl.handleSignal
    //         onMySignal: { // 连接信号
    //             console.log(message) // 响应信号
    //         }
    //     }


    //     Button
    //     {
    //         id: testBtn
    //         width: 100
    //         height: 50
    //         onClicked:
    //         {
    //             console.log(test.myText)
    //             // showText.text = test.myText
    //             showText.text = test.textFieldText
    //         }
    //     }

    //     TextField
    //     {
    //         id:showText
    //         width: 100
    //         height: 50
    //     }



    //     MyInputField
    //     {
    //         id: test2
    //         width: 100
    //         height: 50
    //         myText:"222222"
    //         cppFunction: myUIControl.handleSignal
    //         onMySignal: { // 连接信号
    //             console.log(message) // 响应信号
    //         }
    //     }

    // }



    // EasyTableModel
    // {
    //     id: testData
    //     horHeader: ["Id","Name","Age","Note"]
    //     initData: [
    //         {"id":1,"name":"gonge","age":20,"note":"test model view"},
    //     ]
    // }

    //     Column {
    //         id: column
    //         width: parent.width *0.8
    //         height: parent.height
    //         MyTableView
    //         {
    //             id: testTableView
    //             width: parent.width
    //             height: parent.height/2
    //         }
    //         EasyTableWidget
    //         {
    //             id: testTableView1
    //             // anchors.top: testTableView.Bottom
    //             width: parent.width
    //             height: parent.height/2
    //             myModel: testData
    //         }
    //     }

    //     Button
    //     {
    //         id:addData
    //         width: 100
    //         height:50
    //         text: "添加"
    //         font.pointSize: 15
    //         anchors.left: column.right
    //         background: Rectangle
    //         {
    //             color:"red"
    //             radius: 10
    //         }

    //         onClicked:
    //         {
    //             console.log("test")
    //             //testData.addRow({"id": 4, "name": "tyf", "age": 30, "note": "new data---"});
    //             testData.addRow({"id": testData.rowCount() + 1, "name": "tyf", "age": 28, "note": "测试"})
    //         }
    //     }
    

//    Rectangle
//    {
//        width: parent.width
//        height: parent.height
//        color: "red"
//    }

    // RowLayout {
    //     id: rowLayout
    //     width: 100
    //     height: 100

    //     ComboBox {
    //         id: combobox
    //         implicitWidth: 150
    //         implicitHeight: 50

    //     }
    //     Button {
    //         id: button
    //         text: qsTr("传入")
    //         implicitWidth: 100
    //         implicitHeight: 50
    //         onClicked:
    //         {   
    //             combobox.model = myUIControl.scanPorts();
    //         }
    //     }
    // }




}
