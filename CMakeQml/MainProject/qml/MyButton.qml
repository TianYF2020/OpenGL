import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Item {

    width: 200
    height: 60

    function setButtonText(txt)
    {
        console.log("test sucess",txt)
        myBtn.text = txt
    }

    ColumnLayout
    {
        Text {
            id: name
            text: qsTr("test")
        }

        Button
        {
            id: myBtn
            text:"tyf"
        }
    }
}
