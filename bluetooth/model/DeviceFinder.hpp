#pragma once

#include "simulator-config.hpp"
#include "BluetoothBaseClass.hpp"

#include <QVariant>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>

class DeviceInfo;
class DeviceHandler;

class DeviceFinder: public BluetoothBaseClass
{
    Q_OBJECT

    Q_PROPERTY(bool scanning READ scanning NOTIFY scanningChanged)
    Q_PROPERTY(QVariant devices READ devices NOTIFY devicesChanged)

public:
    DeviceFinder(DeviceHandler* handler, QObject* parent = nullptr);
    ~DeviceFinder();

    bool scanning() const;
    QVariant devices();

public slots:
    void startSearch();
    void connectToService(const QString& address);

private slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void scanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void scanFinished();

signals:
    void scanningChanged();
    void devicesChanged();

private:

    static constexpr size_t FindTimeout = 5000;

    void connectSignals();

    bool isBleDevice( const QBluetoothDeviceInfo& deviceInfo );

private:
    DeviceHandler* m_deviceHandler;
    QBluetoothDeviceDiscoveryAgent* m_deviceDiscoveryAgent;
    QList<QObject*> m_devices;
};
