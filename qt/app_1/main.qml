import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TextInput {
        id: textInput
        x: 35
        y: 30
        width: 143
        height: 25
        text: qsTr("Text Input")
        font.pixelSize: 16
    }

    Text {
        id: text1
        x: 35
        y: 88
        width: 300
        height: 80
        text: qsTr("")
        font.pixelSize: 16
    }
}
