#include "DeviceFinder.hpp"
#include "DeviceHandler.hpp"
#include "DeviceInfo.hpp"
#include "BluetoothModelResources.hpp"

DeviceFinder::DeviceFinder(DeviceHandler* handler, QObject* parent):
    BluetoothBaseClass(parent),
    m_deviceHandler(handler)
{
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent( this );
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout( FindTimeout );

    connectSignals();
}

DeviceFinder::~DeviceFinder()
{
    qDeleteAll( m_devices );
    m_devices.clear();
}

void DeviceFinder::startSearch()
{
    clearMessages();
    m_deviceHandler->setDevice( nullptr );
    qDeleteAll(m_devices);
    m_devices.clear();

    emit devicesChanged();

    m_deviceDiscoveryAgent->start( QBluetoothDeviceDiscoveryAgent::LowEnergyMethod );

    emit scanningChanged();
    setInfo( Resources::BluetoothMessages::Info::ScanningForDevices );
}

void DeviceFinder::addDevice(const QBluetoothDeviceInfo& device)
{
    // If device is LowEnergy-device, add it to the list
    if ( device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration )
    {
        m_devices.append( new DeviceInfo( device ) );
        setInfo( Resources::BluetoothMessages::Info::ScanningMoreDevices );

        emit devicesChanged();
    }
}


void DeviceFinder::scanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    if ( error == QBluetoothDeviceDiscoveryAgent::PoweredOffError )
        setError( Resources::BluetoothMessages::Errors::BLuetoothAdaptorIsPoweredOff );
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError )
        setError( Resources::BluetoothMessages::Errors::IoError );
    else
        setError( Resources::BluetoothMessages::Errors::UnknownError );
}

void DeviceFinder::scanFinished()
{

    if ( m_devices.isEmpty() )
        setError( Resources::BluetoothMessages::Errors::CantFoundAnyBleDevices );
    else
        setInfo( Resources::BluetoothMessages::Info::ScanningDone );

    emit scanningChanged();
    emit devicesChanged();
}

void DeviceFinder::connectToService(const QString& address)
{
    m_deviceDiscoveryAgent->stop();

    DeviceInfo *currentDevice = nullptr;
    for ( QObject *entry : qAsConst( m_devices ) )
    {
        auto device = qobject_cast<DeviceInfo *>( entry );
        if (device && device->getAddress() == address )
        {
            currentDevice = device;
            break;
        }
    }

    if ( currentDevice )
    {
        m_deviceHandler->setDevice( currentDevice );
        QString infoString = Resources::BluetoothMessages::Info::ConnectedTo.arg( currentDevice->getName() );
        setInfo( infoString );
    }

    clearMessages();
}

bool DeviceFinder::scanning() const
{
    return m_deviceDiscoveryAgent->isActive();
}

QVariant DeviceFinder::devices()
{
    return QVariant::fromValue( m_devices );
}

void DeviceFinder::connectSignals()
{
    connect(
            m_deviceDiscoveryAgent
        ,   &QBluetoothDeviceDiscoveryAgent::deviceDiscovered
        ,   this
        ,   &DeviceFinder::addDevice
    );

    connect(
            m_deviceDiscoveryAgent
        ,   static_cast<void (QBluetoothDeviceDiscoveryAgent::*)(QBluetoothDeviceDiscoveryAgent::Error)>(&QBluetoothDeviceDiscoveryAgent::error)
        ,   this
        ,   &DeviceFinder::scanError
    );

    connect(
            m_deviceDiscoveryAgent
        ,   &QBluetoothDeviceDiscoveryAgent::finished
        ,   this
        ,   &DeviceFinder::scanFinished
    );
    connect(
            m_deviceDiscoveryAgent
        ,   &QBluetoothDeviceDiscoveryAgent::canceled
        ,   this
        ,   &DeviceFinder::scanFinished
    );
}
