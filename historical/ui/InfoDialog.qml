import QtQuick 2.0
import QtQuick.Controls 2.5

import CommonSettings 1.0
import FontSizes 1.0

Dialog {
    anchors.centerIn: parent

    property string message

    width: CommonSettings.wWidth* .8
    height: CommonSettings.wHeight * .25

    background: Rectangle {
        anchors.fill: parent
        color: CommonSettings.backgroundColor
    }
    contentItem: Rectangle {
        anchors.fill: parent
        color: CommonSettings.backgroundColor
        Text {
            text: message
            wrapMode: Text.WordWrap
            color: CommonSettings.fontColor
            font.family: CommonSettings.themeFont
            font.pixelSize: FontSizes.miniFontSize
            anchors.centerIn: parent
        }
    }
    standardButtons: Dialog.Ok
}
