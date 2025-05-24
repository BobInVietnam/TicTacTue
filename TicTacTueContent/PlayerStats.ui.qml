import QtQuick

Rectangle {
    id: column
    property int playerLose: 0
    property int playerWin: 0
    property string playerName: "This is a string"
    color: "#00ffffff"
    border.color: "#00000000"

    Image {
        id: avatar
        x: 8
        y: 0
        width: 64
        height: 64
        source: "qrc:/qtquickplugin/images/template_image.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: name
        x: -4
        y: 74
        color: "#ffffff"
        text: column.playerName
        anchors.top: avatar.bottom
        anchors.topMargin: 10
        font.pixelSize: 14
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Ubuntu"
    }

    Text {
        id: win
        x: 36
        y: 114
        color: "#ffffff"
        text: column.playerWin
        anchors.top: name.bottom
        anchors.topMargin: 24
        font.pixelSize: 14
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Ubuntu"
    }

    Text {
        id: lose
        x: 36
        y: 140
        color: "#ffffff"
        text: column.playerLose
        anchors.top: win.bottom
        anchors.topMargin: 10
        font.pixelSize: 14
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Ubuntu"
    }
}
