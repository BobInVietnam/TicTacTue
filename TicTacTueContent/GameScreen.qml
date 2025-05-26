

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import TicTacTue
import QtQuick.Layouts
import TicTacTueCore

Rectangle {
    id: root
    property string imageUrlPlayer : "images/ava1.png"
    property string imageUrlOpponent : "images/ava2.png"
    property int xWin : 0
    property int oWin : 0
    width: Constants.width
    height: Constants.height
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#2d3f2d"
        }

        GradientStop {
            position: 1
            color: "#1e301e"
        }
        orientation: Gradient.Vertical
    }

    TicTacTueCore {
        id: core;
        onMsgChanged: console.log(msg)
        onGameWon: (side) => {
            rematchButton.visible = true;
            winStatus.text = side + " WON!!!";
            winStatus.visible = true;
            if (side === "X") {
                xWin++;
            } else if (side === "O") {
                oWin++;
            }
        }
        onXTimerStringChanged: xGameStats.playerTime.text = core.xTimerString
        onOTimerStringChanged: oGameStats.playerTime.text = core.oTimerString
    }

    Rectangle {
        id: infoBoard
        x: 813
        width: 245
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 22
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#6a000000"
            }

            GradientStop {
                position: 0.15351
                color: "#3d000000"
            }

            orientation: Gradient.Vertical
            GradientStop {
                position: 0.88158
                color: "#40000000"
            }

            GradientStop {
                position: 1.01316
                color: "#64000000"
            }
        }

        Rectangle {
            id: rectangle
            width: 200
            height: 200
            color: "#00ffffff"
            border.color: "#00000000"
            anchors.top: parent.top
            anchors.topMargin: 24
            anchors.horizontalCenter: parent.horizontalCenter

            PlayerStats {
                id: playerStats
                x: -23
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.bottomMargin: 0
                width: 80
                avatar.source: imageUrlPlayer
            }

            PlayerStats {
                id: opponentStats
                x: 142
                width: 80
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.rightMargin: 0
                anchors.topMargin: 0
                anchors.bottomMargin: 0
                avatar.source: imageUrlOpponent
            }

            Text {
                id: win
                x: 88
                y: 114
                color: "#ffffff"
                text: qsTr("Win")
                anchors.top: parent.top
                anchors.topMargin: 114
                font.pixelSize: 14
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                id: loss
                x: 86
                y: 140
                color: "#ffffff"
                text: qsTr("Loss")
                anchors.top: win.bottom
                anchors.topMargin: 10
                font.pixelSize: 14
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            id: history
            x: -373
            width: 200
            height: 200
            color: "#4a000000"
            border.color: "#00000000"
            anchors.top: rectangle.bottom
            anchors.topMargin: 24
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: chat
            x: -373
            width: 200
            color: "#4a000000"
            anchors.top: history.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: 45
            anchors.bottomMargin: 32
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        id: game
        x: 203
        y: 60
        width: 600
        height: 600
        color: "#00ffffff"
        border.color: "#ffffff"
        border.width: 8

        Rectangle {
            id: rectangle2
            color: "#ffffff"
            border.width: 0
            anchors.fill: parent
            anchors.leftMargin: 16
            anchors.rightMargin: 17
            anchors.topMargin: 16
            anchors.bottomMargin: 16
        }

        Grid {
            id: grid
            anchors.fill: parent
            anchors.leftMargin: 16
            anchors.rightMargin: 16
            anchors.topMargin: 16
            anchors.bottomMargin: 16
            clip: false
            spacing: 16
            rows: 3
            columns: 3

            Repeater {
                id: boxGenerator
                model: 9
                XORect {
                    id: rec
                    width: (grid.width - 32) / 3
                    height: (grid.height - 32) / 3

                    Connections {
                        target: rec.mouseArea
                        function onClicked() {
                            // Eventual C++ logic here
                            if (core.getBoxPressed(index)) {
                                if (!core.xTurn) {
                                    rec.state = "x"
                                } else {
                                    rec.state = "o"
                                }
                            }
                        }
                    }

                }
            }
        }
    }

    GeneralButton {
        id: quit
        width: 67
        height: 50
        text: "Quit"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 17
        anchors.topMargin: 13

        Connections {
            target: quit
            function onClicked() {
                for (var i = 0; i < 9; i++) {
                    console.log(boxGenerator.itemAt(i).state)
                    boxGenerator.itemAt(i).state = "empty"
                }
                root.visible = false
            }
        }
    }

    PlayerTimeScore {
        id: xGameStats
        anchors.verticalCenter: game.verticalCenter
        anchors.right: game.left
        anchors.rightMargin: 32
        playerScore.text: xWin
        playerImage.source: imageUrlPlayer
    }

    Text {
        id: winStatus
        x: 203
        y: 8
        width: 600
        height: 44
        visible: false
        color: "#ffffff"
        text: qsTr("WON!!!")
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
    }

    PlayerTimeScore {
        id: oGameStats
        anchors.verticalCenter: game.verticalCenter
        anchors.left: game.right
        anchors.leftMargin: 32
        playerScore.text: oWin
        playerImage.source: imageUrlOpponent
    }

    GeneralButton {
        id: rematchButton
        x: 863
        visible: false
        text: "REMATCH"
        anchors.right: infoBoard.left
        anchors.top: parent.top
        anchors.rightMargin: 16
        anchors.topMargin: 13
        onClicked: {
            for (var i = 0; i < 9; i++) {
                console.log(boxGenerator.itemAt(i).state)
                boxGenerator.itemAt(i).state = "empty"
            }
            core.reset();
            visible = false;
            winStatus.visible = false;
        }
    }
}
