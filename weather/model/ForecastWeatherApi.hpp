#pragma once

#include "core/RapidWeatherApi.hpp"

class ForecastWeatherApi : public RapidWeatherApi
{
public:
    ForecastWeatherApi();

protected:
    QUrl formRequest(const QString& city) override;
    QUrl formRequest(double latitude, double longitude) override;
};
