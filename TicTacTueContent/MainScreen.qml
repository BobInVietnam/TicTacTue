

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import TicTacTue

Rectangle {
    id: root
    width: Constants.width
    height: Constants.height
    color: "#2d3f2d"
    property alias startButton: startButton

    Column {
        id: column
        y: 434
        width: 368
        height: 190
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 356
        anchors.bottomMargin: 96
        anchors.horizontalCenter: parent.horizontalCenter
        transformOrigin: Item.Center
        spacing: 20

        GeneralButton {
            id: startButton
            y: 0
            width: parent.width
            text: "START GAME"
        }

        GeneralButton {
            id: settingsButton
            y: 70
            width: parent.width
            text: "Settings"
        }

        GeneralButton {
            id: quitButton
            y: 140
            width: parent.width
            text: "QUIT"

            Connections {
                target: quitButton
                function onClicked() {
                    Qt.quit()
                }
            }
        }
    }

    Text {
        id: title
        x: 323
        y: 96
        color: "#ffffff"
        text: qsTr("TIC-TAC-TOE")
        font.pixelSize: 96
        rotation: -2.637
        font.bold: true
        font.family: "Courier"
    }

    states: [
        State {
            name: "clicked"
        }
    ]
}
