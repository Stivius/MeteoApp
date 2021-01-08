import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

import CommonSettings 1.0

ColumnLayout {
    spacing: CommonSettings.wHeight * 0.008

    property date enteredDate: new Date(year.value, month.currentIndex + 1, day.value)

    SpinBox {
        id: day
        font: CommonSettings.themeFont
        Layout.preferredWidth: CommonSettings.wWidth * .45
        from: 1
        to: 31
        value:  new Date().getDay()
        editable: true
    }

    ComboBox {
        id: month
        font: CommonSettings.themeFont
        Layout.preferredWidth: CommonSettings.wWidth * .45
        model: ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    }

    SpinBox {
        id: year
        font: CommonSettings.themeFont
        Layout.preferredWidth: CommonSettings.wWidth * .45
        from: 2008
        to: new Date().getFullYear()
        value: new Date().getFullYear()
        textFromValue: function(value) {
            return value;
        }
        editable: true
    }
}

