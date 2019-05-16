#include "ConnectionHandler.hpp"

#include <QtBluetooth/qtbluetooth-config.h>
#include <QtCore/qsystemdetection.h>

ConnectionHandler::ConnectionHandler(QObject *parent)
    :   QObject(parent)
{
    connect(
            &m_localDevice
        ,   &QBluetoothLocalDevice::hostModeStateChanged
        ,   this
        ,   &ConnectionHandler::hostModeChanged
    );
}

bool ConnectionHandler::alive() const
{
    return m_localDevice.isValid() && m_localDevice.hostMode() != QBluetoothLocalDevice::HostPoweredOff;
}

bool ConnectionHandler::requiresAddressType() const
{
    return false;
}

QString ConnectionHandler::name() const
{
    return m_localDevice.name();
}

QString ConnectionHandler::address() const
{
    return m_localDevice.address().toString();
}

void ConnectionHandler::hostModeChanged(QBluetoothLocalDevice::HostMode /*mode*/)
{
    emit deviceChanged();
}
