import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Timeline 1.0
import QtQuick.Window 2.15
import QtQuick.Layouts 2.15
import LearnOpenGL 1.0
import EasyModel 1.0
Window {
    width: 720
    height: 480
    visible: true
    title: qsTr("Hello World")


        // FBOItem
        // {
        //     id:myView
        //     width: parent.width*0.5
        //     height: parent.height*0.5
        // }




    EasyTableModel
    {
        id: testData
        horHeader: ["Id","Name","Age","Note"]
        initData: [
            {"id":1,"name":"gonge","age":20,"note":"test model view"},
        ]
    }

        Column {
            id: column
            width: parent.width *0.8
            height: parent.height
            MyTableView
            {
                id: testTableView
                width: parent.width
                height: parent.height/2
            }
            EasyTableWidget
            {
                id: testTableView1
                // anchors.top: testTableView.Bottom
                width: parent.width
                height: parent.height/2
                myModel: testData
            }
        }

        Button
        {
            id:addData
            width: 100
            height:50
            text: "添加"
            font.pointSize: 15
            anchors.left: column.right
            background: Rectangle
            {
                color:"red"
                radius: 10
            }

            onClicked:
            {
                console.log("test")
                //testData.addRow({"id": 4, "name": "tyf", "age": 30, "note": "new data---"});
                testData.addRow({"id": testData.rowCount() + 1, "name": "tyf", "age": 28, "note": "测试"})
            }
        }
    

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
