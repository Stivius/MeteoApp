#pragma once

#include "BaseIconsProvider.hpp"

class WeatherIconsProvider
        :   public BaseIconsProvider
{

    Q_OBJECT

public:

    ~WeatherIconsProvider() override = default;

public:

    QImage requestImage( const QString& id, QSize* size , const  QSize& requestedSize ) override;

};
