import QtQuick 2.5
import BluetoothWindowSettings 1.0

Rectangle {
    id: button
    color: baseColor
    onEnabledChanged: checkColor()
    radius: BluetoothWindowSettings.buttonRadius

    property color baseColor: BluetoothWindowSettings.buttonColor
    property color pressedColor: BluetoothWindowSettings.buttonPressedColor
    property color disabledColor: BluetoothWindowSettings.disabledButtonColor

    signal clicked()

    function checkColor() {

        if (!button.enabled) {
            button.color = disabledColor
        } else {
            if (mouseArea.containsPress)
                button.color = pressedColor
            else
                button.color = baseColor
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: checkColor()
        onReleased: checkColor()
        onClicked: {
            checkColor()
            button.clicked()
        }
    }
}
