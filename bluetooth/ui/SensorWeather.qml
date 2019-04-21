import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.1
import QtQuick.Layouts 1.3
import BluetoothWindowSettings 1.0

Rectangle {
    visible: true
    width: parent.width
    height: parent.height

    color: BluetoothWindowSettings.backgroundColor

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        anchors.margins:10

        CustomTextWidget {
            id:temperatureWidget
            widgetName:  qsTr("Temperature:");
            displayedText: deviceHandler.temperature
        }

        CustomTextWidget {
            id:humidityWidget
            widgetName:  qsTr("Humidity:");
            displayedText: deviceHandler.humidity
        }

        CustomTextWidget {
            id:pressureWidget
            widgetName:  qsTr("Pressure:");
            displayedText: deviceHandler.pressure
        }

        ConnectWidget {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
