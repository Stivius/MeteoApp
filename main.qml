import QtQuick 2.12
import QtQuick.Controls 2.5
import QtCharts 2.3
import QtQuick.Layouts 1.12

import Resources 1.0

ApplicationWindow {
    visible: true
    width: Resources.windowWidth
    height: Resources.windowHeight
    title: qsTr("MeteoPrototype")

    SwipeView {
        id: view

        currentIndex: 0
        anchors.fill: parent

        Repeater {
            model: 3
            Loader {
                active: SwipeView.isCurrentItem
                source: Resources.getPage(index)
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

