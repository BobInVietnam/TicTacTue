import QtQuick
import TicTacTue
import QtQuick.Studio.DesignEffects
import QtQuick.Controls 6.8

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "TicTacTue"

    MainScreen {
        id: mainScreen
        startButton.onClicked: {
            gamemodeWindow.visible = true;
        }

        GeneralButton {
            id: connect
            x: 1036
            y: 637
            text: "Connect to Internet"
            onClicked: gameScreen.toggleServer();
        }
    }

    GameScreen {
        id: gameScreen
        visible: false
    }

    Rectangle {
        id: gamemodeWindow
        x: 170
        y: 85
        width: 941
        height: 551
        visible: false
        color: "#2d3f2d"
        radius: 8
        border.color: "#ffffff"
        border.width: 8

        DesignEffect {
            effects: [
                DesignDropShadow {
                    color: "#82000000"
                    offsetY: 8
                    offsetX: 8
                }
            ]
        }

        Text {
            id: text1
            x: 329
            y: 42
            width: 283
            height: 48
            color: "#ffffff"
            text: qsTr("CHOOSE YOUR GAME MODE")
            font.pixelSize: 36
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
        }

        GeneralButton {
            id: generalButton
            x: 421
            y: 477
            text: "Back"
            onClicked: gamemodeWindow.visible = false
        }

        Rectangle {
            id: gm1
            x: 102
            y: 142
            width: 200
            height: 200
            color: "#2d3f2d"
            radius: 3
            border.color: "#ffffff"
            border.width: 4

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    gameScreen.gamemode = 0;
                    gamemodeWindow.visible = false;
                    gameScreen.visible = true;;
                }
            }

            Image {
                id: avatarDefaultSvgrepoCom
                x: 28
                y: 25
                width: 64
                height: 64
                source: "images/avatar-default-svgrepo-com.svg"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: robotSvgrepoCom
                x: 105
                y: 110
                width: 64
                source: "images/robot-svgrepo-com.svg"
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: text2
                color: "#ffffff"
                text: qsTr("You vs. AI")
                anchors.top: parent.bottom
                anchors.topMargin: 30
                font.pixelSize: 24
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
            }
        }

        Rectangle {
            id: gm2
            x: 371
            y: 142
            width: 200
            height: 200
            color: "#2d3f2d"
            radius: 3
            border.color: "#ffffff"
            border.width: 4
            MouseArea {
                id: mouseArea1
                anchors.fill: parent
                onClicked: {
                    gameScreen.gamemode = 1;
                    gamemodeWindow.visible = false;
                    gameScreen.visible = true;
                }
            }

            Image {
                id: avatarDefaultSvgrepoCom1
                x: 28
                y: 25
                width: 64
                height: 64
                source: "images/avatar-default-svgrepo-com.svg"
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: text3
                color: "#ffffff"
                text: qsTr("You vs. Human")
                anchors.top: parent.bottom
                anchors.topMargin: 30
                font.pixelSize: 24
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Image {
                id: avatarDefaultSvgrepoCom2
                x: 107
                y: 114
                width: 64
                height: 64
                source: "images/avatar-default-svgrepo-com.svg"
                fillMode: Image.PreserveAspectFit
            }
        }

        Rectangle {
            id: gm3
            x: 645
            y: 142
            width: 200
            height: 200
            color: "#2d3f2d"
            radius: 3
            border.color: "#ffffff"
            border.width: 4
            MouseArea {
                id: mouseArea2
                anchors.fill: parent
                onClicked: {
                    gameScreen.gamemode = 2;
                    gamemodeWindow.visible = false;
                    gameScreen.visible = true;
                }
            }

            Image {
                id: avatarDefaultSvgrepoCom3
                x: 28
                y: 25
                width: 64
                height: 64
                source: "images/avatar-default-svgrepo-com.svg"
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: text4
                color: "#ffffff"
                text: qsTr("Online Game")
                anchors.top: parent.bottom
                anchors.topMargin: 30
                font.pixelSize: 24
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Image {
                id: avatarDefaultSvgrepoCom4
                x: 107
                y: 114
                width: 64
                height: 64
                source: "images/avatar-default-svgrepo-com.svg"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: wifiHighSvgrepoCom
                x: 109
                y: 25
                width: 64
                source: "images/wifi-high-svgrepo-com.svg"
                fillMode: Image.PreserveAspectFit
            }
        }
    }

}

