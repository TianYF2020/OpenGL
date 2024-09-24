// pragma NativeMethodBehavior: AcceptThisObject
import QtQuick 2.15
import QtQuick.Controls 2.15

Item
{
    signal mySignal(string message)

    //方案1 双向链接，信号响应变量重新赋值
    property var myText: ""
    //方案2 暴漏属性的方式，不用赋值
    property alias textFieldText: textField.text
    //方案3 传入函数进来
    property var cppFunction:null
    property var onSignalReceived: null // 响应逻辑
    Column {
        id: column
        width: 200
        height: 400

        Label
        {
            text:"test"
        }

        TextField {
            id: textField
            placeholderText: qsTr("Text Field")
            text: myText
            onTextEdited:
            {
                // 实现双向链接
                // myText = text
                // mySignal("Button was clicked!")
                if(cppFunction)
                {
                              cppFunction("Cpp runing ************")
                }

            }
        }
    }

}
