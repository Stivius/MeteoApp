import QtQuick 2.9
import BluetoothWindowSettings 1.0
import FontSizes 1.0
import CommonSettings 1.0

Item {

    property string errorMessage: ""
    property string infoMessage: ""
    property real messageHeight: msg.height
    property bool hasError: errorMessage != ""
    property bool hasInfo: infoMessage != ""

    function init() {
    }

    function close() {
        app.prevPage()
    }

    Rectangle {
        id: msg
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: BluetoothWindowSettings.fieldHeight
        color: hasError ? BluetoothWindowSettings.errorColor : BluetoothWindowSettings.infoColor
        opacity: 0.9
        visible: hasError || hasInfo

        Text {
            id: error
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            minimumPixelSize: 5
            font.pixelSize: FontSizes.smallFontSize
            font.family: CommonSettings.themeFont
            fontSizeMode: Text.Fit
            color: BluetoothWindowSettings.messageCenterTextColor
            text: hasError ? errorMessage : infoMessage
        }
    }
}
