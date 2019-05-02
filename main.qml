import QtQuick 2.9
import QtQuick.Controls 2.5

import CommonSettings 1.0

ApplicationWindow {
    visible: true
    width: 720 * .7
    height: 1240 * .7
    title: qsTr("MeteoPrototype")

    Component.onCompleted: {
        CommonSettings.wWidth = Qt.binding( function(){ return width } )
        CommonSettings.wHeight = Qt.binding( function(){ return height} )
    }

    SwipeView {
        id: view

        currentIndex: 1
        anchors.fill: parent

        Repeater {
            model: 3
            Loader {
                active: SwipeView.isCurrentItem
                source: CommonSettings.getPage(index)
            }
        }
    }

    PageIndicator {
        id: indicator

        count: view.count
        currentIndex: view.currentIndex

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

}

