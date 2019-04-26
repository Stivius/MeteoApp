#include "simulator-config.hpp"
#include "DeviceHandler.hpp"
#include "DeviceInfo.hpp"
#include "BluetoothModelResources.hpp"

static const QString CC2540_UUID {"0000ffe0-0000-1000-8000-00805f9b34fb"};
static const QString CC2540_RW_CHAR{"0000ffe1-0000-1000-8000-00805f9b34fb"};

//from  https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/bluetooth/BluetoothGattDescriptor.java
namespace BluetoothDescriptors {
    static const QByteArray EnableNotificationValue = QByteArray::fromHex( "0100" );
    static const QByteArray EnableIndicationValue = QByteArray::fromHex( "0200" );
    static const QByteArray EmptyValue = QByteArray::fromHex( "0000" );
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
    ,   m_control( nullptr )
    ,   m_service( nullptr )
    ,   m_notificationDesc ( nullptr )
    ,   m_resultsParser( std::move( _resultsParser ) )

{
}

void DeviceHandler::setAddressType(AddressType type)
{
    switch (type)
    {
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
    if ( m_control )
    {
        m_control->disconnectFromDevice();
        m_control.reset();
    }

    // Create new controller and connect it if device available
    if ( m_currentDevice )
    {

        m_control.reset(    QLowEnergyController::createCentral(
                        m_currentDevice->getDevice()
                )
        );

        m_control->setRemoteAddressType( m_addressType );

        connectLowEnergyControllerSignals();

        m_control->connectToDevice();
    }
}

void DeviceHandler::serviceDiscovered(const QBluetoothUuid& gatt)
{
    if ( gatt == QBluetoothUuid( CC2540_UUID ) )
    {
        setInfo( Resources::BluetoothMessages::Info::ServiceDiscovered );
        m_foundBleWeatherService = true;
    }
}

void DeviceHandler::serviceScanDone()
{
    setInfo( Resources::BluetoothMessages::Info::ScanHasDone );

    // Delete old service if available
    if ( m_service )
        m_service.reset();

    if ( m_foundBleWeatherService )
        m_service.reset(
                m_control->createServiceObject( QBluetoothUuid( CC2540_UUID ) )
            );

    if ( m_service )
    {
        connect(
                m_service.get()
            ,   &QLowEnergyService::stateChanged
            ,   this
            ,    &DeviceHandler::serviceStateChanged
        );
        connect(
                m_service.get()
            ,   &QLowEnergyService::characteristicChanged
            ,   this
            ,   &DeviceHandler::updtateWeatherData
        );
        connect(
                m_service.get()
            ,   &QLowEnergyService::descriptorWritten
            ,   this
            ,   &DeviceHandler::confirmedDescriptorWrite
        );

        m_service->discoverDetails();
    }
    else
        setError( Resources::BluetoothMessages::Errors::CantFindWeatherService );
}

void DeviceHandler::serviceStateChanged( QLowEnergyService::ServiceState _state )
{
    switch ( _state )
    {
    case QLowEnergyService::DiscoveringServices:
        setInfo( Resources::BluetoothMessages::Info::DiscoveringServices );
        break;
    case QLowEnergyService::ServiceDiscovered:
    {
        setInfo( Resources::BluetoothMessages::Info::ServiceDiscoveredState );

        const QLowEnergyCharacteristic weatherCharactetistic
                = m_service->characteristic( QBluetoothUuid( CC2540_RW_CHAR ) );

        if ( !weatherCharactetistic.isValid() )
        {
            setError( Resources::BluetoothMessages::Errors::WrPropertyNotFound );
            break;
        }

        m_notificationDesc.reset( new QLowEnergyDescriptor (
                    weatherCharactetistic.descriptor( QBluetoothUuid::ClientCharacteristicConfiguration )
            )
        );

        if( !m_notificationDesc->isValid() )
        {
            setError( Resources::BluetoothMessages::Errors::InvalidDeviceDescrpitor );
            break;
        }

        if( weatherCharactetistic.properties().testFlag( QLowEnergyCharacteristic::Indicate ) )
        {
            m_service->writeDescriptor(
                    *m_notificationDesc
                ,   BluetoothDescriptors::EnableNotificationValue
            );
        }
        else if( weatherCharactetistic.properties().testFlag( QLowEnergyCharacteristic::Notify ) )
        {
            m_service->writeDescriptor(
                    *m_notificationDesc
                ,   BluetoothDescriptors::EnableNotificationValue
            );
        }
        else
        {
            setError( Resources::BluetoothMessages::Errors::InvalidCharacteristic );
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
    if ( c.uuid() != QBluetoothUuid( CC2540_RW_CHAR ))
        return;

    QByteArray received = value;
    QString toParse( received );
    m_resultsParser->tryParseValue( toParse );

    m_temperatureValue = m_resultsParser->getTemperature();
    m_humidityValue = m_resultsParser->getHumidity();
    m_pressureValue = m_resultsParser->getPressure();

    emit temperatureChanged();
    emit humidityChanged();
    emit pressureChanged();
}

void DeviceHandler::confirmedDescriptorWrite( const QLowEnergyDescriptor& d, const QByteArray &value )
{
    if ( !isNotificationDescriptorValid( d, value ) )
    {
        m_control->disconnectFromDevice();
        m_service.reset();
    }
}

void DeviceHandler::disconnectService()
{
    m_foundBleWeatherService = false;

    if (
            isNotificationDescriptorValid( *m_notificationDesc, m_notificationDesc->value() )
        &&  m_service
        )
        m_service->writeDescriptor( *m_notificationDesc, QByteArray::fromHex ( BluetoothDescriptors::EmptyValue ) ) ;
    else
    {
        if ( m_control )
            m_control->disconnectFromDevice();

        m_service.reset();
    }
}

bool DeviceHandler::alive() const
{
    if ( m_service )
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

void DeviceHandler::connectLowEnergyControllerSignals()
{
    connect(
            m_control.get()
        ,   &QLowEnergyController::serviceDiscovered
        ,   this
        ,   &DeviceHandler::serviceDiscovered
    );

    connect(
            m_control.get()
        ,   &QLowEnergyController::discoveryFinished
        ,   this
        ,   &DeviceHandler::serviceScanDone
    );

    connect(
            m_control.get()
        ,   static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error)
        ,   this
        ,   [ this ]( QLowEnergyController::Error error )
            {
                Q_UNUSED( error );
            setError( Resources::BluetoothMessages::Errors::CantConnectToDevice );
            }
    );

    connect(
            m_control.get()
        ,   &QLowEnergyController::connected
        ,   this
        ,   [ this ]
            {
                setInfo( Resources::BluetoothMessages::Info::SearchServices );
                m_control->discoverServices();
            }
        );
    connect(
            m_control.get()
        ,   &QLowEnergyController::disconnected
        ,   this
        ,   [ this ]
            {
                setError( Resources::BluetoothMessages::Errors::BleControllerDisconnected );
            }
        );
}

bool DeviceHandler::isNotificationDescriptorValid(
        const QLowEnergyDescriptor& descriptor
    ,   const QByteArray& value
    )
{
    return descriptor.isValid()
    && descriptor == *m_notificationDesc
    && value == BluetoothDescriptors::EnableNotificationValue;
}
