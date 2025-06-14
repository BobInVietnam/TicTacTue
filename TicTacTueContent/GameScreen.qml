
import QtQuick
import QtQuick.Controls
import TicTacTue
import QtQuick.Layouts
import TicTacTueCore
import QtQuick.Studio.DesignEffects

Rectangle {
    id: root

    property string imageUrlPlayer : "images/ava1.png"
    property string imageUrlOpponent : "images/ava2.png"
    property int gamemode : -1
    property int aiDiffLevel : 1;
    property string playerName : "";
    property bool aiIsX : false;
    property int xWin : 0
    property int oWin : 0
    property bool online : false;
    property bool waitingForOpponent: true;
    width: Constants.width
    height: Constants.height
    z: 10
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

    onGamemodeChanged: {
        if (gamemode !== 2) {
            playerStats.playerName = "Player X"
            opponentStats.playerName = "Player O"
            playerStats.playerWin = 0
            opponentStats.playerLose = 0
            playerStats.playerLose = 0
            opponentStats.playerWin = 0
        }
        if (gamemode === 0) {
            core.isX = !aiIsX
        }
        core.gamemode = gamemode
        winStatus.visible = false;
        xWin = 0;
        oWin = 0;
    }

    MouseArea {
        id: mouseCapturer
        anchors.fill: parent
    }

    TicTacTueCore {
        id: core;
        aiDiff: aiDiffLevel
        onMsgChanged: () => console.log(msg)
        onGameWon: (side) => {
                       rematchButton.visible = true;
                       winStatus.text = side + " WON!!!";
                       winStatus.visible = true;
                       if (side === "X") {
                           xWin++;
                           playerStats.playerWin += 1
                           opponentStats.playerLose += 1
                       } else if (side === "O") {
                           playerStats.playerLose += 1
                           opponentStats.playerWin += 1
                           oWin++;
                       }
                    }
        onXTimerStringChanged: () => { xGameStats.playerTime.text = core.xTimerString }
        onOTimerStringChanged: () => { oGameStats.playerTime.text = core.oTimerString }
        onBoardChanged: () => {
                            loadBoardState(core.getBoardSeq())
                        }
        onRoomCreated: () => {
                           root.roomCreated();
                       }

        onRoomJoined: () => {
                          root.roomJoined();
                      }
        onUsernameSet: () => {
                        root.usernameSet();
                       }
        onRoomErrorOccured: (msg) => {
                                root.roomErrorOccured(msg);
                            }

        onServerConnected: () => {
                               online = true;
                           }
        onServerDisconnected: () => {
                                  online = false;
                              }
        onGameStarted: () => {
                        waitingForOpponent = false;
                       }
        onStatsChanged: (xName, xWin, xLose, oName, oWin, oLose) => {
                            playerStats.playerName = xName
                            opponentStats.playerName = oName
                            playerStats.playerWin = xWin
                            opponentStats.playerLose = oLose
                            playerStats.playerLose = xLose
                            opponentStats.playerWin = oWin
                        }

        onChatReceived: (msg) => {
                            myListModel.append(myListModel.createListElement(msg))
                            scrollView.ScrollBar.vertical.position = 1.0 - scrollView.ScrollBar.vertical.size;
                        }
        onOpponentLeft: () => {
                            waitingForOpponent = true;
                        }
        onPingChanged: () => {
                        pingText.text = "Ping: " + core.ping
                       }
    }

    signal roomCreated();
    signal roomJoined();
    signal usernameSet();
    signal roomErrorOccured(string msg);

    function toggleServer() {
        if (!online) {
            core.connectToServer();
        } else {
            core.disconnectFromServer();
        }
    }

    function setUsername(usr) {
        core.setUsername(usr);
    }

    function createRoom(rid) {
        core.createRoom(rid);
    }

    function joinRoom(rid) {
        core.joinRoom(rid);
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
                playerName: "Player X"
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
                playerName: "Player O"
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
                font.bold: true
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
                font.bold: true
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
            anchors.topMargin: 51
            anchors.bottomMargin: 32
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
            visible: gamemode == 2

            Text {
                id: chatTitle
                x: 85
                color: "#ffffff"
                text: qsTr("Chat")
                anchors.bottom: parent.top
                anchors.bottomMargin: 8
                font.pixelSize: 14
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: chat.horizontalCenter
                font.bold: true
            }

            Rectangle {
                id: chatInput
                x: 1
                y: 159
                width: 200
                height: 28
                color: "#00ffffff"
                border.color: "#ffffff"
                border.width: 2
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 2

                TextInput {
                    id: textInput
                    color: "#ffffff"
                    anchors.fill: parent
                    anchors.leftMargin: 8
                    anchors.rightMargin: 8
                    anchors.topMargin: 0
                    anchors.bottomMargin: 0
                    clip: true;
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                    selectionColor: "#beffffff"
                    selectedTextColor: "#1e1e1e"
                    onAccepted: () => {
                                if (textInput.text !== "") {
                                    core.sendMessage(textInput.text);
                                    textInput.clear()
                                }
                            }
                }
            }

            Rectangle {
                id: chatoutput
                x: 1
                y: 0
                width: 200
                height: 161
                color: "#00ffffff"
                border.color: "#ffffff"
                border.width: 2
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 28

                ColumnLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 8
                    anchors.rightMargin: 8
                    anchors.topMargin: 8
                    anchors.bottomMargin: 8

                    ScrollView {
                        id: scrollView
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        clip: true

                        Column {
                            id: contentColumn
                            width: parent.width
                            spacing: 4

                            Repeater {
                                id: repeater
                                model:  ListModel {
                                    id: myListModel
                                    function createListElement(msg) {
                                        return {"msg": msg}
                                    }
                                }

                                delegate: Rectangle {
                                    id: chatItem
                                    width: parent.width
                                    implicitHeight: chatMsg.height
                                    color: "#00ffffff"
                                    Text {
                                        id: chatMsg
                                        color: "#ffffff"
                                        text: msg
                                        width: 200
                                        wrapMode: Text.WordWrap
                                        font.pointSize: 10
                                    }
                                }
                            }
                        }
                    }
                }
            }
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
                            if (boxGenerator.itemAt(index).state !== "empty") {
                                return
                            } else {
                                core.getBoxPressed(index)
                            }
                        }
                    }
                }
            }
        }
    }

    function loadBoardState(seq: string) {
        for (var i = 0; i < 9; i++) {
            boxGenerator.itemAt(i).state = (seq.charAt(i) === ' ' ? "empty" : seq.charAt(i))
        }
    }

    Rectangle {
        id: connectingSign
        x: 243
        y: 215
        width: 521
        height: 279
        visible: gamemode == 2 && waitingForOpponent
        color: "#293b29"
        radius: 8
        border.color: "#ffffff"
        border.width: 8

        DesignEffect {
            effects: [
                DesignDropShadow {
                    color: "#89000000"
                    offsetY: 8
                    offsetX: 8
                    blur: 2
                }
            ]
        }

        Text {
            id: text1
            x: 142
            y: 58
            color: "#ffffff"
            text: qsTr("Connecting to server")
            font.pixelSize: 24
            font.bold: true
        }

        Text {
            id: text2
            x: 142
            y: 100
            color: "#ffffff"
            text: qsTr("Waiting for opponent")
            font.pixelSize: 24
            font.bold: true
        }

        GeneralButton {
            id: generalButton
            x: 183
            y: 185
            text: "Cancel & Quit"
            onClicked: {
                root.quitGame();
            }
        }
    }

    GeneralButton {
        id: quitGame
        width: 67
        height: 50
        text: "Quit"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 17
        anchors.topMargin: 13

        signal exitGame()
        Connections {
            target: quitGame
            function onClicked() {
                root.quitGame();
            }
        }
    }

    function quitGame() {
        for (var i = 0; i < 9; i++) {
            console.log(boxGenerator.itemAt(i).state)
            boxGenerator.itemAt(i).state = "empty"
        }
        root.visible = false;
        if (gamemode == 2) core.leaveRoom();
        gamemode = -1;
        myListModel.clear()
        scrollView.width = chatoutput.width
        contentColumn.width = scrollView.width
        scrollView.ScrollBar.vertical.position = 0;
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

    Rectangle {
        id: internet
        y: 664
        width: 64
        height: 48
        visible: gamemode == 2
        color: "#00ffffff"
        border.color: "#00ffffff"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 16
        anchors.bottomMargin: 8

        Text {
            id: pingText
            x: 6
            y: 15
            color: "#ffffff"
            text: qsTr("Ping: ")
            font.pixelSize: 16
            font.bold: true
        }
    }

    Image {
        id: xIndicator
        x: 79
        y: 153
        source: "images/x.svg"
        fillMode: Image.PreserveAspectFit
        visible: core.xTurn
    }

    Image {
        id: oIndicator
        x: 863
        y: 153
        source: "images/o.svg"
        fillMode: Image.PreserveAspectFit
        visible: !core.xTurn
    }

}
