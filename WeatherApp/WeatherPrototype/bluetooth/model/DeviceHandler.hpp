#pragma once

#include "BluetoothBaseClass.hpp"
#include "IReceivedDataParser.hpp"

#include <QDateTime>
#include <QVector>

#include <QLowEnergyController>
#include <QLowEnergyService>

#include <memory>

class DeviceInfo;
class IReceivedDataParser;

class DeviceHandler : public BluetoothBaseClass
{
    Q_OBJECT
    Q_PROPERTY(bool alive READ alive NOTIFY aliveChanged)
    Q_PROPERTY(float temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(float humidity READ humidity NOTIFY humidityChanged )
    Q_PROPERTY(float pressure READ pressure NOTIFY pressureChanged )
    Q_PROPERTY(AddressType addressType READ addressType WRITE setAddressType)

public:

    enum class AddressType
    {
        PublicAddress,
        RandomAddress
    };
    Q_ENUM(AddressType)

    DeviceHandler(
            std::unique_ptr<IReceivedDataParser> _resultsParser
        ,   QObject* parent = nullptr
    );

    void setDevice(DeviceInfo* device);
    void setAddressType(AddressType type);
    AddressType addressType() const;

    bool measuring() const;
    bool alive() const;

    float temperature() const;
    float humidity() const;
    float pressure() const;

signals:
    void aliveChanged();

    void temperatureChanged();
    void humidityChanged();
    void pressureChanged();

public slots:
    void disconnectService();

private:

    //QLowEnergyController
    void serviceDiscovered(const QBluetoothUuid&);
    void serviceScanDone();

    //QLowEnergyService
    void serviceStateChanged(QLowEnergyService::ServiceState s);

    void updtateWeatherData(
            const QLowEnergyCharacteristic& c
        ,   const QByteArray& value
    );

    void confirmedDescriptorWrite(
            const QLowEnergyDescriptor& d
        ,   const QByteArray& value
    );

private:

    void connectLowEnergyControllerSignals();

    bool isNotificationDescriptorValid( const QLowEnergyDescriptor& descriptor, const QByteArray& value );

private:

    bool m_foundBleWeatherService;
    bool m_isMeasuring;

    float m_temperatureValue;
    float m_humidityValue;
    float m_pressureValue;

    std::unique_ptr<QLowEnergyController> m_control;
    std::unique_ptr<QLowEnergyService> m_service;
    std::unique_ptr<QLowEnergyDescriptor> m_notificationDesc;
    std::unique_ptr<IReceivedDataParser> m_resultsParser;

    QLowEnergyController::RemoteAddressType m_addressType = QLowEnergyController::PublicAddress;
    DeviceInfo* m_currentDevice = nullptr;
};
