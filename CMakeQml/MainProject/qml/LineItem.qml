import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    width: 400
    height: 80
    clip: true
    signal removeListIndex(int listIndex)

    // function setLineData(var )
    RowLayout
    {
        spacing: 10
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter

        Text {
            text: model.name
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 60
            Layout.preferredHeight: parent.height *0.5
        }

        TextField {
            id: inputField
            text: model.value
            Layout.preferredWidth: 100
            Layout.preferredHeight: parent.height *0.8
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
        }

        Image {
            source: model.img
            Layout.preferredWidth: parent.height * 0.9
            Layout.preferredHeight: parent.height * 0.9
        }

        Button {
            text: "删除"

            Layout.preferredWidth: 60
            Layout.preferredHeight: parent.height * 0.5
            onClicked: {
                listModel.remove(index);
                // removeListIndex(index)
            }
        }
    }
    Rectangle {
        height: 2
        color: "black"
        width: parent.width
        anchors.bottom: parent.bottom
        // visible: index < model.count - 1  // 最后一个项后面不需要分割线
    }
}
