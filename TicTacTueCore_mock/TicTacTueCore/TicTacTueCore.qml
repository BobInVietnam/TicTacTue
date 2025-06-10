import QtQuick

Item {
    id: root
    property bool xTurn: true;
    property QString xTimerString: "value"
    property QString oTimerString: "value"
    property int ping: 0
    property bool isX : true;
    property int aiDiff : -1;

    signal msgChanged()
    signal gameWon(QString side)
    signal boardChanged()
    signal roomCreated();
    signal roomJoined();
    signal usernameSet();
    signal serverConnected();
    signal serverDisconnected();
    signal roomErrorOccured();
    signal gameStarted();
    signal chatReceived(QString msg)
    signal opponentLeft()
    signal pingChanged();
    function getBoxPressed(index) {
        xTurn = !xTurn;
        return true;
    }

    function reset() {
        console.log("nothing");
    }
}
