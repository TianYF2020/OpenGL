

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

RowLayout {
    id: rootItem
    width: 250
    height: 30
    property alias text: textItem.text
    property alias value: slider.value
    property alias from: slider.from
    property alias to: slider.to
    property alias stepSize: slider.stepSize

    signal toggled
    signal moved

    Material.theme: Material.Dark
    Material.accent: Material.LightGreen
    spacing: 20


    // Row {

    Text {
        id: textItem
        // anchors.horizontalCenter: parent.horizontalCenter
        // color: "#f0f0f0"
        text: "test"
        color: "#000000"
        font.pixelSize: 14 * dp
        Layout.alignment: Qt.AlignHCenter
    }
    Slider 
    {
        id: slider
        width: 200
        value: 50
        height: 40
        from: 0
        to: 255
        stepSize: 1
        onMoved: 
        {
            rootItem.moved();
        }


    }
        Text {
            id: sliderValue
            text:slider.value

            color: "#000000"
            font.pixelSize: 14 * dp
            Layout.alignment: Qt.AlignHCenter
        }
    // }
}



