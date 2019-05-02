import QtQuick.Controls 2.5

ComboBox {
    signal locationChanged(string location)

    textRole: "display"
    model: locationListModel

    onCurrentTextChanged: {
        locationChanged(currentText)
    }
}

