import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Timeline 1.0
import QtQuick.Window 2.15
import QtQuick.Layouts 2.15
import LearnOpenGL 1.0
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


        // FBOItem
        // {
        //     id:myView
        //     width: parent.width*0.5
        //     height: parent.height*0.5
        // }






        Column {
            id: column
            width: parent.width
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
