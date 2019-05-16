#include "DeviceInfo.hpp"
#include <QBluetoothAddress>
#include <QBluetoothUuid>

DeviceInfo::DeviceInfo(const QBluetoothDeviceInfo& info):
    m_device(info)
{
}

QBluetoothDeviceInfo DeviceInfo::getDevice() const
{
    return m_device;
}

QString DeviceInfo::getName() const
{
    return m_device.name();
}

QString DeviceInfo::getAddress() const
{
    return m_device.address().toString();
}

void DeviceInfo::setDevice(const QBluetoothDeviceInfo& device)
{
    m_device = device;
    emit deviceChanged();
}
