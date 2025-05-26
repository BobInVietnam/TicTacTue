import QtQuick

Rectangle {
    id: root
    width: playerTime.width
    height: 240
    color: "#00ffffff"
    border.color: "#00000000"
    property alias playerScore: playerScore
    property alias playerTime: playerTime
    property alias playerImage: playerImage
    
    Image {
        id: playerImage
        width: 100
        height: 100
        anchors.right: game.left
        anchors.top: playerTime.bottom
        anchors.rightMargin: 32
        anchors.topMargin: 16
        source: "qrc:/qtquickplugin/images/template_image.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }
    
    Text {
        id: playerTime
        width: 120
        height: 42
        color: "#ffffff"
        text: qsTr("00:00")
        anchors.top: parent.top
        anchors.topMargin: 0
        font.pixelSize: 32
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
    }
    
    Text {
        id: playerScore
        width: 120
        height: 48
        color: "#ffffff"
        text: qsTr("0")
        anchors.top: playerImage.bottom
        anchors.topMargin: 16
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
    }
}
