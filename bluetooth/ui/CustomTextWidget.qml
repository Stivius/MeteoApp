import QtQuick 2.9

import BluetoothWindowSettings 1.0
import FontSizes 1.0
import CommonSettings 1.0

Image {
    property string iconPath:""
    property string displayedText:""
    source: iconPath;
    asynchronous: true;
    cache: true;
    Text {
        text: parent.displayedText;
        font.family: CommonSettings.themeFont
        font.pixelSize: FontSizes.largeFontSize
        color: BluetoothWindowSettings.textColor
        anchors.left: parent.right
    }
}
