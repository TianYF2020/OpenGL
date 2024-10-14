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
        anchors.right: settingsView.right
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
