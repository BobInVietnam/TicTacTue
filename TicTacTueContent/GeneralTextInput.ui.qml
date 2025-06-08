import QtQuick

Rectangle {
    id: root
    width: 236
    height: 39
    color: "#00ffffff"
    border.color: "#ffffff"
    border.width: 4
    property alias textInput: textInput

    TextInput {
        id: textInput
        color: "#ffffff"
        text: qsTr("Text Input")
        anchors.fill: parent
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        font.pixelSize: 16
        verticalAlignment: Text.AlignVCenter
    }
}
