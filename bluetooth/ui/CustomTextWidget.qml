import QtQuick 2.9
import BluetoothWindowSettings 1.0

Text {
    property string widgetName:""
    property string displayedText;

    text: qsTr(widgetName);
    font.pixelSize: BluetoothWindowSettings.largeFontSize
    color: BluetoothWindowSettings.textColor

    Text {
        text: parent.displayedText;
        font.pixelSize: BluetoothWindowSettings.largeFontSize
        color: BluetoothWindowSettings.textColor
        anchors.left: parent.right
    }
}
