#pragma once

#include "core/RapidWeatherApi.hpp"

class CurrentWeatherApi : public RapidWeatherApi
{
public:
    CurrentWeatherApi();

protected:
    QUrl formRequest(const QString& city) override;
    QUrl formRequest(double latitude, double longitude) override;

};
