import QtQuick
import QtQuick.Controls

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
        validator: RegularExpressionValidator {regularExpression: /^[a-zA-Z0-9]*$/}
        anchors.fill: parent
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        font.pixelSize: 16
        verticalAlignment: Text.AlignVCenter
    }
}
