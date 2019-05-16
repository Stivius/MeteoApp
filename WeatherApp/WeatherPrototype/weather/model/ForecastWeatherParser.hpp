#pragma once

#include <QJsonObject>

#include "core/WeatherDataParser.hpp"
#include "weather/model/WeatherData.hpp"

class ForecastWeatherParser : public WeatherDataParser<WeatherDataCollection>
{
public:
    WeatherDataCollection parse(const QByteArray& data) override;

private:
    WeatherApiData parseJsonObject(const QJsonObject& data);

};
