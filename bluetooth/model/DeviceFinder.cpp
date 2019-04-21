#include "DeviceFinder.hpp"
#include "DeviceHandler.hpp"
#include "DeviceInfo.hpp"

DeviceFinder::DeviceFinder(DeviceHandler* handler, QObject* parent):
    BluetoothBaseClass(parent),
    m_deviceHandler(handler)
{
    //! [devicediscovery-1]
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000);

    connectSignals();

#ifdef SIMULATOR
    m_demoTimer.setSingleShot(true);
    m_demoTimer.setInterval(2000);
    connect(&m_demoTimer, &QTimer::timeout, this, &DeviceFinder::scanFinished);
#endif
}

DeviceFinder::~DeviceFinder()
{
    qDeleteAll(m_devices);
    m_devices.clear();
}

void DeviceFinder::startSearch()
{
    clearMessages();
    m_deviceHandler->setDevice(nullptr);
    qDeleteAll(m_devices);
    m_devices.clear();

    emit devicesChanged();

#ifdef SIMULATOR
    m_demoTimer.start();
#else
    //! [devicediscovery-2]
    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    //! [devicediscovery-2]
#endif
    emit scanningChanged();
    setInfo(tr("Scanning for devices..."));
}

//! [devicediscovery-3]
void DeviceFinder::addDevice(const QBluetoothDeviceInfo& device)
{
    // If device is LowEnergy-device, add it to the list
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        m_devices.append( new DeviceInfo( device ) );
        setInfo( tr ("Low Energy device found. Scanning more..." ) );

        emit devicesChanged();
    }
}


void DeviceFinder::scanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        setError(tr("The Bluetooth adaptor is powered off."));
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        setError(tr("Writing or reading from the device resulted in an error."));
    else
        setError(tr("An unknown error has occurred."));
}

void DeviceFinder::scanFinished()
{

    if (m_devices.isEmpty())
        setError(tr("No Low Energy devices found."));
    else
        setInfo(tr("Scanning done."));

    emit scanningChanged();
    emit devicesChanged();
}

void DeviceFinder::connectToService(const QString& address)
{
    m_deviceDiscoveryAgent->stop();

    DeviceInfo *currentDevice = nullptr;
    for (QObject *entry : qAsConst(m_devices)) {
        auto device = qobject_cast<DeviceInfo *>(entry);
        if (device && device->getAddress() == address ) {
            currentDevice = device;
            break;
        }
    }

    if (currentDevice)
    {
        m_deviceHandler->setDevice(currentDevice);
        QString infoString = tr("Connected to") + currentDevice->getName();
        setInfo( infoString );
    }

    clearMessages();
}

bool DeviceFinder::scanning() const
{
#ifdef SIMULATOR
    return m_demoTimer.isActive();
#else
    return m_deviceDiscoveryAgent->isActive();
#endif
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
