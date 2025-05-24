import QtQuick

Rectangle {
    id: root
    color: "#293b29"
    property alias mouseArea: mouseArea
    width: 100
    height: 100
    state: "empty"

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
    }

    Image {
        id: oState
        anchors.fill: parent
        source: "images/o.svg"
        sourceSize.height: 256
        sourceSize.width: 256
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: xState
        anchors.fill: parent
        source: "images/x.svg"
        sourceSize.height: 256
        sourceSize.width: 256
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "empty"

            PropertyChanges {
                target: oState
                visible: false
            }

            PropertyChanges {
                target: xState
                visible: false
            }
        },
        State {
            name: "x"

            PropertyChanges {
                target: xState
                visible: true
            }
            PropertyChanges {
                target: oState
                visible: false
            }
        },
        State {
            name: "o"

            PropertyChanges {
                target: oState
                visible: true
            }
            PropertyChanges {
                target: xState
                visible: false
            }
        }
    ]
}
