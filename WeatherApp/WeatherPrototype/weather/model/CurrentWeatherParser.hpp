#pragma once

#include "core/WeatherDataParser.hpp"
#include "weather/model/WeatherData.hpp"

class CurrentWeatherParser : public WeatherDataParser<WeatherApiData>
{
public:
    WeatherApiData parse(const QByteArray& data) override;

};
