#pragma once
#include <QString>


namespace Resources {

    namespace BluetoothMessages
    {
        namespace Errors
        {
            const QString BLuetoothAdaptorIsPoweredOff  = "The Bluetooth adaptor is powered off.";
            const QString IoError                       = "Writing or reading from the device resulted in an error.";
            const QString UnknownError                  = "An unknown error has occurred.";
            const QString CantFoundAnyBleDevices        = "No Low Energy devices found.";
            const QString CantConnectToDevice           = "Cannot connect to remote device.";
            const QString BleControllerDisconnected     = "LowEnergy controller disconnected";
            const QString CantFindWeatherService        = "Weather service not found.";
            const QString WrPropertyNotFound            = "WR Property not found.";
            const QString InvalidDeviceDescrpitor       = "Invalid CC2540 descriptor";
            const QString InvalidCharacteristic         = "Invalid notification/indication for read characteristic";
        }
        namespace Info
        {
            const QString ScanningMoreDevices           = "Low Energy device found. Scanning more..." ;
            const QString ScanningDone                  = "Scanning done.";
            const QString ScanningForDevices            = "Scanning for devices...";
            const QString ConnectedTo                   = "Connected to: %1";
            const QString SearchServices                = "Controller connected. Search services...";
            const QString ServiceDiscovered             =  "Weather station discovered. Waiting for service scan to be done..." ;
            const QString ScanHasDone                   = "Service scan has done.";
            const QString DiscoveringServices           = "Discovering services...";
            const QString ServiceDiscoveredState        = "Service discovered.";
        }
    }
}
