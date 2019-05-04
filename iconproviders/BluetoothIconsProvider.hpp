#pragma once

#include "BaseIconsProvider.hpp"

class BluetoothIconsProvider
        :   public BaseIconsProvider
{

    Q_OBJECT

public:

    ~BluetoothIconsProvider() override = default;

public:

    QImage requestImage( const QString& id, QSize* size , const  QSize& requestedSize ) override;

};
