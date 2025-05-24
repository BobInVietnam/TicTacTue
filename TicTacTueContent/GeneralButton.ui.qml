/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls

Button {
    id: control

    implicitWidth: Math.max(
                       buttonBackground ? buttonBackground.implicitWidth : 0,
                       textItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        buttonBackground ? buttonBackground.implicitHeight : 0,
                        textItem.implicitHeight + topPadding + bottomPadding)
    leftPadding: 4
    rightPadding: 4

    text: "My Button"
    highlighted: true

    background: buttonBackground
    Rectangle {
        id: buttonBackground
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        color: "#00ffffff"
        radius: 2
        border.color: "#ffffff"
        border.width: 3
    }

    contentItem: textItem
    Text {
        id: textItem
        text: control.text

        opacity: enabled ? 1.0 : 0.3
        color: "#1c1c1c"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        bottomPadding: 8
        topPadding: 8
        leftPadding: 16
        rightPadding: 16
        font.pointSize: 14
        font.bold: true
    }

    states: [
        State {
            name: "normal"
            when: !control.down

            PropertyChanges {
                target: buttonBackground
                color: "#00ffffff"
                border.color: "#ffffff"
                border.width: 3
            }

            PropertyChanges {
                target: textItem
                color: "#ffffff"
            }
        },
        State {
            name: "down"
            when: control.down
            PropertyChanges {
                target: textItem
                color: "#dcdcdc"
            }

            PropertyChanges {
                target: buttonBackground
                color: "#78000000"
                border.color: "#cccccc"
                border.width: 3
            }
        },
        State {
            name: "hover"
            when: control.hovered

            PropertyChanges {}
        }
    ]
}
