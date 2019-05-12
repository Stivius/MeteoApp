import QtQml 2.9
import QtQuick 2.9
import CommonSettings 1.0
import FontSizes 1.0

MouseArea {

    property int rotationAngle:0
    property string displayedText: ""

    width:textItem.contentWidth * 2
    height: parent.height

    Rectangle{
        id: clickedRect
        anchors.fill: parent
        color: Qt.darker(CommonSettings.backgroundColor, 1.2)
        radius: CommonSettings.wWidth *0.01
    }
    Text {
        id: textItem
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        text: displayedText;
        anchors.margins: CommonSettings.wWidth *0.04
        font.pixelSize: FontSizes.largeFontSize;
        font.family: CommonSettings.themeFont
        rotation: rotationAngle
        color: CommonSettings.fontColor
    }
    onPressed:
    {
        clickedRect.color = Qt.binding( function (){ return Qt.lighter(CommonSettings.backgroundColor, 1.2)});
    }
    onReleased:
    {
        clickedRect.color = Qt.binding( function (){ return Qt.darker(CommonSettings.backgroundColor, 1.2)});
    }
    onCanceled:
    {
        clickedRect.color = Qt.binding( function (){ return Qt.darker(CommonSettings.backgroundColor, 1.2)});
    }
}
