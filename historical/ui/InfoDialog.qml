import QtQuick 2.0
import QtQuick.Controls 2.5

import CommonSettings 1.0

Dialog {
    anchors.centerIn: parent

    property string message

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
            color: CommonSettings.fontColor
            font: CommonSettings.themeFont
            anchors.centerIn: parent
        }
    }
    standardButtons: Dialog.Ok
}
