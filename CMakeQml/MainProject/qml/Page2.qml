import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {

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
}
