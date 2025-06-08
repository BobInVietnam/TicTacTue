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
        z: 0
        startButton.onClicked: {
            gamemodeWindow.visible = true;
        }
        settingsButton.onClicked: {
            settingWindow.visible = true;
        }

        Rectangle {
            id: connectionWarning
            x: 904
            y: 620
            width: 368
            height: 84
            visible: false
            color: "#2d3f2d"
            radius: 8
            border.color: "#ffffff"
            border.width: 8
            z: 10

            Text {
                id: text5
                color: "#ffffff"
                text: qsTr("You need to connect to the server first (Go to Settings -> Connect to Server)")
                anchors.fill: parent
                anchors.leftMargin: 27
                anchors.rightMargin: 32
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.Wrap
                font.bold: true
            }

            Timer {
                id: cWTimer
                interval: 5000
                onTriggered: connectionWarning.visible = false;
            }
        }
    }

    GameScreen {
        id: gameScreen
        visible: false
        z: 10
        onRoomCreated: { busyIndicator.running = false;
            gameScreen.gamemode = 2;
            gameScreen.visible = true;
            gamemodeWindow.visible = false;
        }

        onRoomJoined: { busyIndicator.running = false;
            gameScreen.gamemode = 2;
            gameScreen.visible = true;
            gamemodeWindow.visible = false;
        }

        onUsernameSet: {
            busyIndicator.running = false;
        }
        onRoomErrorOccured: (msg) => {
            busyIndicator.running = false;
            statusIndicator.visible = true;
            statusIndicator.text = msg;
        }
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
        z: 5

        MouseArea {
            id: mouseArea4
            anchors.fill: parent
        }

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
                    if (!gameScreen.online) {
                        connectionWarning.visible = true;
                        cWTimer.start();
                    } else {
                        gamemodeWindow.visible = false;
                        roomWindow.visible = true;
                    }
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

    Rectangle {
        id: settingWindow
        x: 211
        y: 103
        width: 859
        height: 515
        visible: false
        color: "#2d3f2d"
        radius: 8
        border.color: "#ffffff"
        border.width: 8
        z: 5

        MouseArea {
            id: mouseArea5
            anchors.fill: parent
        }

        Slider {
            id: diffSlider
            x: 531
            value: 1
            anchors.top: parent.top
            anchors.topMargin: 128
            stepSize: 1
            to: 3
            from: 1
            snapMode: RangeSlider.SnapAlways
        }


        Text {
            id: settings
            x: 288
            width: 283
            height: 48
            color: "#ffffff"
            text: qsTr("SETTINGS")
            anchors.top: parent.top
            anchors.topMargin: 36
            font.pixelSize: 36
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
        }


        Switch {
            id: aiIsXSwitch
            x: 531
            width: 66
            height: 47 ; anchors.top: diffSlider.bottom; anchors.topMargin: 8 ;icon.color: "#ffffff" }


        Text {
            id: aiSetting1
            x: 203
            color: "#ffffff"
            text: qsTr("AI Difficulty")
            anchors.top: parent.top
            anchors.topMargin: 128
            font.pixelSize: 24
            font.bold: true
        }


        Text {
            id: aiSetting2
            x: 237
            y: 647
            color: "#ffffff"
            text: qsTr("AI is X")
            anchors.top: aiSetting1.bottom
            anchors.topMargin: 32
            font.pixelSize: 24
            font.bold: true
        }


        Text {
            id: sliderText1
            y: 133
            width: 43
            height: 21
            color: "#ffffff"
            text: qsTr("Easy")
            anchors.left: diffSlider.left
            anchors.bottom: diffSlider.top
            anchors.leftMargin: 0
            anchors.bottomMargin: 4
            font.pixelSize: 20
            font.bold: true
        }


        Text {
            id: aiSetting4
            x: 667
            y: 133
            color: "#ffffff"
            text: qsTr("Impossible")
            anchors.right: diffSlider.right
            anchors.bottom: diffSlider.top
            anchors.rightMargin: -37
            anchors.bottomMargin: 2
            font.pixelSize: 20
            font.bold: true
        }


        GeneralButton {
            id: saveQuitButton
            x: 363
            y: 431
            text: "Save & Quit"
            onClicked: {
                gameScreen.aiDiffLevel = diffSlider.value;
                gameScreen.aiIsX = aiIsXSwitch.checked;
                settingWindow.visible = false;
            }
        }


        GeneralButton {
            id: connect
            x: 327
            y: 351
            text: "Connect to Internet"
            onClicked: gameScreen.toggleServer();
        }

    }

    Image {
        id: connectIndicator
        x: 23
        y: 635
        width: 64
        visible: gameScreen.online
        source: "images/wifi-high-svgrepo-com.svg"
        sourceSize.width: 800
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        id: roomWindow
        x: 351
        y: 205
        width: 580
        height: 353
        visible: false
        color: "#2d3f2d"
        radius: 8
        border.color: "#ffffff"
        border.width: 8
        z: 8


        MouseArea {
            id: mouseArea6
            anchors.fill: parent
        }

        Text {
            id: text6
            color: "#ffffff"
            text: qsTr("Enter username")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 56
            anchors.topMargin: 86
            font.pixelSize: 20
            font.bold: true
        }


        Text {
            id: text7
            color: "#ffffff"
            text: qsTr("Game room ID")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 72
            anchors.topMargin: 137
            font.pixelSize: 20
            font.bold: true
        }


        GeneralTextInput {
            id: usernameInput
            height: 36
            anchors.left: text6.right
            anchors.top: parent.top
            anchors.leftMargin: 112
            anchors.topMargin: 79
            textInput.onEditingFinished: {
                gameScreen.setUsername(textInput.text);
            }
        }


        GeneralTextInput {
            id: roomIdInput
            height: 36
            anchors.left: text7.right
            anchors.top: parent.top
            anchors.leftMargin: 112
            anchors.topMargin: 131
        }


        GeneralButton {
            id: roomWExitButton
            x: 50
            text: "Exit"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 32
            onClicked: {
                roomWindow.visible = false;
                statusIndicator.visible = false;
            }
        }


        GeneralButton {
            id: createRoomButton
            x: 205
            text: "Create Room"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 32
            onClicked: {
                busyIndicator.running = true;
                gameScreen.createRoom(roomIdInput.textInput.text);
                statusIndicator.visible = false;
            }
        }


        GeneralButton {
            id: joinRoomButton
            x: 402
            text: "Join Room"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 32
            onClicked: {
                busyIndicator.running = true;
                gameScreen.joinRoom(roomIdInput.textInput.text);
                statusIndicator.visible = false;
            }
        }


        BusyIndicator {
            id: busyIndicator
            x: 260
            y: 187
            running: false;
        }



        Text {
            id: statusIndicator
            x: 50
            y: 205
            width: 486
            height: 24
            visible: false
            color: "#ffffff"
            text: qsTr("Nothing there")
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

    }

}

