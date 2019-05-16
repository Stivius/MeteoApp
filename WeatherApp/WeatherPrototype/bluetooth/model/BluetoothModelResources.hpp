#pragma once
#include <QString>
#include <QObject>

namespace Resources :: BluetoothMessages::Errors
{
    const QString BLuetoothAdaptorIsPoweredOff  = QObject::tr( "Bluetooth adaptor is turned off"                                     );
    const QString IoError                       = QObject::tr( "Device reading/writing failed "                                      );
    const QString UnknownError                  = QObject::tr( "An unknown error has occurred"                                       );
    const QString CantFoundAnyBleDevices        = QObject::tr( "No Low Energy devices found"                                         );
    const QString CantConnectToDevice           = QObject::tr( "Cannot connect to remote device"                                     );
    const QString BleControllerDisconnected     = QObject::tr( "LowEnergy controller disconnected"                                   );
    const QString CantFindWeatherService        = QObject::tr( "Weather service not found"                                           );
    const QString WrPropertyNotFound            = QObject::tr( "WR Property not found"                                               );
    const QString InvalidDeviceDescrpitor       = QObject::tr( "Invalid CC2540 descriptor"                                           );
    const QString InvalidCharacteristic         = QObject::tr( "Invalid notification/indication for read characteristic"             );
    const QString BadPacket                     = QObject::tr( "Bad packet error. Check the station state"                           );
}
namespace Resources :: BluetoothMessages::Info
{
    const QString ScanningMoreDevices           = QObject::tr( "Low Energy device found. Scanning more..."                           );
    const QString ScanningDone                  = QObject::tr( "Scanning done"                                                       );
    const QString ScanningForDevices            = QObject::tr( "Scanning for devices..."                                             );
    const QString ConnectedTo                   = QObject::tr( "Connected to: %1"                                                    );
    const QString SearchServices                = QObject::tr( "Search services..."                                                  );
    const QString ServiceDiscovered             = QObject::tr(  "Weather station discovered. Waiting for service scan to be done..." );
    const QString ScanHasDone                   = QObject::tr( "Service scan has done"                                               );
    const QString DiscoveringServices           = QObject::tr( "Discovering services..."                                             );
    const QString ServiceDiscoveredState        = QObject::tr( "Service discovered"                                                  );
}
