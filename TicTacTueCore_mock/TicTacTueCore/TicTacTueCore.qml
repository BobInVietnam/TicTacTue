import QtQuick

Item {
    id: root
    property bool xTurn: true;
    property QString xTimerString: "value"
    property QString oTimerString: "value"

    signal msgChanged()
    signal gameWon(QString side)
    signal boardChanged()

    function getBoxPressed(index) {
        xTurn = !xTurn;
        return true;
    }

    function reset() {
        console.log("nothing");
    }
}
