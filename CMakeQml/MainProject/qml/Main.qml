import QtQuick
import QtQuick.Controls
import QtQuick.Timeline 
import QtQuick.Window 
import QtQuick.Layouts 
import LearnOpenGL 
import EasyModel 1.0
import QtQuick.Window
import QtQuick.Effects
import "CustomMultiEffect"

ApplicationWindow  {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Hello World")

    readonly property real dp: 0.2 + Math.min(width, height) / 1200
    property var stretchState: false 
    property var showHideAnimationSpeed: 400
    // readonly property real dp: 0.2 + Math.min(width, height) / 1200

        // FBOItem
        // {
        //     id:myView
        //     width: parent.width*0.5
        //     height: parent.height*0.5
        // }


    Settings {
        id: settings
        onReseted: {
            settingsView.resetSettings();
        }
    }

    Settings {
        id: defaultSettings
    }

    SettingsView {
        id: settingsView
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        z:999
        anchors.right: parent.right
        // anchors.left: parent.left
        // anchors.margins: 20
        visible: settings.showSettingsView
        Component.onCompleted: {
            settings.reset();
        }
    }

    Rectangle
     {
        id: mainArea
        // anchors.left: settingsView.right
        // anchors.right: parent.right
        anchors.left: parent.left
        anchors.right: settingsView.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        // color: "black"

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


        ColumnLayout 
        {
            id: slidersColumn
            spacing: 6
            anchors.top: testBtn.bottom

            LabeledSlider {
                id: rotation1Slider
                text: "R"
                from: 0
                to: 255
                value: 255
            }

            LabeledSlider {
                id: rotation2Slider
                text: "G"
                from: 0
                to: 255
                value: 255
            }

            LabeledSlider {
                id: rotation3Slider
                text: "B"
                from: 0
                to: 255
                value: 255
            }

            Button
            {
                width: 100
                height: 50
                text: "add"
                onClicked:
                {
                    mlog.addLineText("This is a line log")
                }
            }
            Button
            {
                width: 100
                height: 50
                text: "clear"
                onClicked:
                {
                    mlog.clearListView()
                }
            }
        }


    

        Rectangle
        {
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


    // LogShow
    // {
    //     width: parent.width
    //     height: 200
    //     anchors.left: parent.left
    //     anchors.bottom: parent.bottom
    // }

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
