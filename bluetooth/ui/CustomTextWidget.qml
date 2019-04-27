import QtQuick 2.9
import BluetoothWindowSettings 1.0
import FontSizes 1.0

Text {
    property string widgetName:""
    property string displayedText;

    text: qsTr(widgetName);
    font.pixelSize: FontSizes.largeFontSize
    color: BluetoothWindowSettings.textColor

    Text {
        text: parent.displayedText;
        font.pixelSize: FontSizes.largeFontSize
        color: BluetoothWindowSettings.textColor
        anchors.left: parent.right
    }
}
