#pragma once

#include "core/WeatherApiData.hpp"

class WeatherDataParser
{
public:
    virtual ~WeatherDataParser() = default;
    virtual WeatherDataCollection parse(const QByteArray& data) = 0;

};
