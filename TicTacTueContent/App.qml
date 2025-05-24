import QtQuick
import TicTacTue

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "TicTacTue"

    MainScreen {
        id: mainScreen
        startButton.onClicked: {
            gameScreen.visible = true;
        }
    }

    GameScreen {
        id: gameScreen
        visible: false
    }

}

