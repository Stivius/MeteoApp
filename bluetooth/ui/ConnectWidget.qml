import QtQuick 2.9
import BluetoothWindowSettings 1.0
import FontSizes 1.0

Rectangle {
    id: viewContainer
    width: parent.width - BluetoothWindowSettings.fieldMargin*2
    color: BluetoothWindowSettings.viewColor
    radius: BluetoothWindowSettings.buttonRadius

    Text {
        id: title
        width: parent.width
        height: BluetoothWindowSettings.fieldHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: BluetoothWindowSettings.textColor
        font.pixelSize: FontSizes.mediumFontSize
        text: qsTr("FOUND DEVICES")

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            width: parent.width * 0.85
            height: parent.height * 0.05
            radius: height*0.5
        }

        MessageCenter
        {
            id: connectionNotifications
            errorMessage: deviceFinder.error
            infoMessage: deviceFinder.info
        }
    }


    ListView {
        id: devices
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: title.bottom
        model: deviceFinder.devices
        clip: true

        delegate: Rectangle {
            id: box
            height:BluetoothWindowSettings.fieldHeight * 1.2
            width: parent.width
            color: index % 2 === 0 ? BluetoothWindowSettings.delegate1Color : BluetoothWindowSettings.delegate2Color

            MouseArea {
            anchors.fill: parent
                onClicked: {
                    deviceFinder.connectToService(modelData.deviceAddress);
                }
            }

            Text {
                id: device
                font.pixelSize: FontSizes.smallFontSize
                text: modelData.deviceName
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.1
                anchors.leftMargin: parent.height * 0.1
                anchors.left: parent.left
                color: BluetoothWindowSettings.textColor
            }

            Text {
                id: deviceAddress
                font.pixelSize: FontSizes.smallFontSize
                text: modelData.deviceAddress
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height * 0.1
                anchors.rightMargin: parent.height * 0.1
                anchors.right: parent.right
                color: Qt.darker(BluetoothWindowSettings.textColor)
            }
        }
    }

    SearchDevicesButton {
        id:searchButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin:  BluetoothWindowSettings.fieldMargin
        width: parent.width
        height: BluetoothWindowSettings.fieldHeight
        enabled: !deviceFinder.scanning
        onClicked: deviceFinder.startSearch()
        Text {
            anchors.centerIn: parent
            font.pixelSize: FontSizes.tinyFontSize
            text: qsTr("START SEARCH")
            color: searchButton.enabled? BluetoothWindowSettings.textColor: BluetoothWindowSettings.disabledTextColor
        }
    }
}
