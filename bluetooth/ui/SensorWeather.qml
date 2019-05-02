import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.1
import QtQuick.Layouts 1.3
import BluetoothWindowSettings 1.0
import CommonSettings 1.0

Rectangle {
    visible: true
    width: parent.width
    height: parent.height

    color: CommonSettings.backgroundColor

    GridLayout {
        id: columnLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom

        GridLayout
        {
            Layout.margins: BluetoothWindowSettings.fieldMargin
            flow: GridLayout.TopToBottom;
                CustomTextWidget {
                    id:temperatureWidget
                    Layout.preferredHeight: BluetoothWindowSettings.fieldHeight
                    Layout.preferredWidth: BluetoothWindowSettings.fieldHeight
                    iconPath:"resources/icons/thermometer.png"
                    displayedText: deviceHandler.temperature
                }

                CustomTextWidget {
                    id:humidityWidget
                    Layout.preferredHeight: BluetoothWindowSettings.fieldHeight
                    Layout.preferredWidth: BluetoothWindowSettings.fieldHeight
                    iconPath:"resources/icons/humidity.png"
                    displayedText: deviceHandler.humidity
                }

                CustomTextWidget {
                    id:pressureWidget
                    Layout.preferredHeight: BluetoothWindowSettings.fieldHeight
                    Layout.preferredWidth: BluetoothWindowSettings.fieldHeight
                    iconPath:"resources/icons/gauge.png"
                    displayedText: deviceHandler.pressure
                }
            }
        ConnectWidget {
            Layout.margins: BluetoothWindowSettings.fieldMargin
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
