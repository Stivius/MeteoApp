import QtQuick.Controls 2.5
import QtQml 2.9
import QtQuick 2.9

import CommonSettings 1.0
import FontSizes 1.0
Rectangle
{
    id: current
    color: Qt.darker( CommonSettings.backgroundColor, 1.4)
    radius: CommonSettings.wWidth *0.02
    anchors.leftMargin: CommonSettings.wWidth *0.02
    anchors.rightMargin: CommonSettings.wWidth *0.02
    Component
    {
        id:pathViewDelegate
        Rectangle
        {
            visible: PathView.onPath
            antialiasing: true
            height: current.height;
            width: current.width* 0.95;
            color: Qt.darker(CommonSettings.backgroundColor, 1.2)
            border.color: Qt.lighter( CommonSettings.backgroundColor, 1.4)
            border.width: CommonSettings.wWidth *0.01
            radius: CommonSettings.wWidth *0.02
            Text {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                text: "<";
                anchors.margins: CommonSettings.wWidth *0.04
                font.pixelSize: FontSizes.largeFontSize;
                font.family: CommonSettings.themeFont
                font.bold: true
                color: CommonSettings.fontColor
             }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: display;
                font.pixelSize: FontSizes.largeFontSize;
                font.family: CommonSettings.themeFont
                font.bold: true
                color: CommonSettings.fontColor
             }
            Text {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: ">";
                anchors.margins: CommonSettings.wWidth *0.04
                font.pixelSize: FontSizes.largeFontSize;
                font.family: CommonSettings.themeFont
                font.bold: true
                color: CommonSettings.fontColor
             }
        }
    }
    PathView {
        anchors.fill: parent
        model:locationListModel

        delegate: pathViewDelegate
        preferredHighlightBegin: 0.5;
        preferredHighlightEnd: 0.5;

        highlightRangeMode: PathView.StrictlyEnforceRange
        pathItemCount:1
        maximumFlickVelocity:1000
        path: Path {
            startX: 0;
            startY:current.height/2;
            PathLine {
                x:current.width ; y: current.height/2
            }
        }
        onCurrentIndexChanged:
        {
            appSettings.location = locationListModel.data(locationListModel.index(this.currentIndex ,0 ) );
        }
    }
}
