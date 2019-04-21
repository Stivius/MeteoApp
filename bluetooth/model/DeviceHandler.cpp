#include "simulator-config.hpp"
#include "DeviceHandler.hpp"
#include "DeviceInfo.hpp"

#include <QtEndian>

#include "CustomFormatDataParser.hpp"

static const QString CC2540_UUID {"0000ffe0-0000-1000-8000-00805f9b34fb"};
static const QString CC2540_RW_CHAR{"0000ffe1-0000-1000-8000-00805f9b34fb"};

//from  https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/bluetooth/BluetoothGattDescriptor.java
namespace BluetoothDescriptors {
    static const QByteArray EnableNotificationValue = QByteArray::fromHex( "0100" );
    static const QByteArray EnableIndicationValue = QByteArray::fromHex( "0200" );

}

DeviceHandler::DeviceHandler(
            std::unique_ptr<IReceivedDataParser> _resultsParser
        ,   QObject *parent
    )
    :   BluetoothBaseClass( parent )
    ,   m_foundBleWeatherService( false )
    ,   m_isMeasuring( false )
    ,   m_temperatureValue( 0.0f )
    ,   m_humidityValue( 0.0f )
    ,   m_pressureValue( 0.0f )
    ,   m_resultsParser( std::move( _resultsParser ) )
{
}

void DeviceHandler::setAddressType(AddressType type)
{
    switch (type) {
    case DeviceHandler::AddressType::PublicAddress:
        m_addressType = QLowEnergyController::PublicAddress;
        break;
    case DeviceHandler::AddressType::RandomAddress:
        m_addressType = QLowEnergyController::RandomAddress;
        break;
    }
}

DeviceHandler::AddressType DeviceHandler::addressType() const
{
    if (m_addressType == QLowEnergyController::RandomAddress)
        return DeviceHandler::AddressType::RandomAddress;

    return DeviceHandler::AddressType::PublicAddress;
}

void DeviceHandler::setDevice(DeviceInfo *device)
{
    clearMessages();
    m_currentDevice = device;
    // Disconnect and delete old connection
    if (m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = nullptr;
    }

    // Create new controller and connect it if device available
    if (m_currentDevice) {

        // Make connections
        //! [Connect-Signals-1]
        m_control = QLowEnergyController::createCentral(m_currentDevice->getDevice(), this);
        //! [Connect-Signals-1]
        m_control->setRemoteAddressType(m_addressType);
        //! [Connect-Signals-2]
        connect(m_control, &QLowEnergyController::serviceDiscovered,
                this, &DeviceHandler::serviceDiscovered);
        connect(m_control, &QLowEnergyController::discoveryFinished,
                this, &DeviceHandler::serviceScanDone);

        connect(m_control, static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
                this, [this](QLowEnergyController::Error error) {
            Q_UNUSED(error);
            setError("Cannot connect to remote device.");
        });
        connect(m_control, &QLowEnergyController::connected, this, [this]() {
            setInfo("Controller connected. Search services...");
            m_control->discoverServices();
        });
        connect(m_control, &QLowEnergyController::disconnected, this, [this]() {
            setError("LowEnergy controller disconnected");
        });

        // Connect
        m_control->connectToDevice();
        //! [Connect-Signals-2]
    }
}

void DeviceHandler::serviceDiscovered(const QBluetoothUuid& gatt)
{
    if (gatt == QBluetoothUuid( CC2540_UUID) )
    {
        setInfo("Heart Rate service discovered. Waiting for service scan to be done...");
        m_foundBleWeatherService = true;
    }
}

void DeviceHandler::serviceScanDone()
{
    setInfo("Service scan done.");

    // Delete old service if available
    if (m_service) {
        delete m_service;
        m_service = nullptr;
    }

//! [Filter HeartRate service 2]
    // If heartRateService found, create new service
    if (m_foundBleWeatherService)
        m_service = m_control->createServiceObject( QBluetoothUuid( CC2540_UUID ), this);

    if (m_service)
    {
        connect(m_service, &QLowEnergyService::stateChanged, this, &DeviceHandler::serviceStateChanged);
        connect(m_service, &QLowEnergyService::characteristicChanged, this, &DeviceHandler::updtateWeatherData);
        connect(m_service, &QLowEnergyService::descriptorWritten, this, &DeviceHandler::confirmedDescriptorWrite);
        m_service->discoverDetails();
    }
    else
    {
        setError("Weather service not found.");
    }
//! [Filter HeartRate service 2]
}

void DeviceHandler::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    switch (s) {
    case QLowEnergyService::DiscoveringServices:
        setInfo(tr("Discovering services..."));
        break;
    case QLowEnergyService::ServiceDiscovered:
    {
        setInfo(tr("Service discovered."));

        const QLowEnergyCharacteristic weatherCharactetistic
                = m_service->characteristic( QBluetoothUuid( CC2540_RW_CHAR ) );

        if ( !weatherCharactetistic.isValid() )
        {
            setError("HR Data not found.");
            break;
        }

        m_notificationDesc = weatherCharactetistic.descriptor( QBluetoothUuid::ClientCharacteristicConfiguration );
        if( !m_notificationDesc.isValid() )
        {
            setError( "Invalid CC2540 descriptor" );
            break;
        }

        if( weatherCharactetistic.properties().testFlag( QLowEnergyCharacteristic::Indicate ) )
        {
            m_service->writeDescriptor(
                    m_notificationDesc
                ,   BluetoothDescriptors::EnableNotificationValue
            );
        }
        else if( weatherCharactetistic.properties().testFlag( QLowEnergyCharacteristic::Notify ) )
        {
            m_service->writeDescriptor(
                    m_notificationDesc
                ,   BluetoothDescriptors::EnableNotificationValue
            );
        }
        else
        {
            setError("Invalid notification/indication for read characteristic");
            break;
        }
        break;
    }
    default:
        break;
    }

    emit aliveChanged();
}

void DeviceHandler::updtateWeatherData(const QLowEnergyCharacteristic& c, const QByteArray &value)
{
    if (c.uuid() != QBluetoothUuid( CC2540_RW_CHAR ))
        return;

    QByteArray received = value;
    QString toParse(received);
    m_resultsParser->tryParseValue( toParse );

    m_temperatureValue = m_resultsParser->getTemperature();
    m_humidityValue = m_resultsParser->getHumidity();
    m_pressureValue = m_resultsParser->getPressure();

    emit temperatureChanged();
    emit humidityChanged();
    emit pressureChanged();
}

void DeviceHandler::confirmedDescriptorWrite(const QLowEnergyDescriptor& d, const QByteArray &value)
{
    if (d.isValid() && d == m_notificationDesc && value == QByteArray::fromHex("0000")) {
        //disabled notifications -> assume disconnect intent
        m_control->disconnectFromDevice();
        delete m_service;
        m_service = nullptr;
    }
}

void DeviceHandler::disconnectService()
{
    m_foundBleWeatherService = false;

    //disable notifications
    if (m_notificationDesc.isValid() && m_service
            && m_notificationDesc.value() == QByteArray::fromHex("0100")) {
        m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0000"));
    } else {
        if (m_control)
            m_control->disconnectFromDevice();

        delete m_service;
        m_service = nullptr;
    }
}

bool DeviceHandler::alive() const
{
    if (m_service)
        return m_service->state() == QLowEnergyService::ServiceDiscovered;

    return false;
}

float DeviceHandler::temperature() const
{
    return m_temperatureValue;
}

float DeviceHandler::humidity() const
{
    return m_humidityValue;
}

float DeviceHandler::pressure() const
{
    return m_pressureValue;
}
