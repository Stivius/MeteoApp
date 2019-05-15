#pragma once

#include <QJsonArray>

#include "core/WeatherDataParser.hpp"
#include "historical/model/HistoricalWeatherData.hpp"

class HistoricalWeatherParser : public WeatherDataParser<HistoricalWeatherData>
{
public:
    HistoricalWeatherData parse(const QByteArray& data) override;

private:
    HistoricalWeatherDay parseDay(const QJsonValueRef dayInfo);
    HistoricalWeatherUnit parseUnit(const QJsonValueRef unitInfo);

};
