#pragma once

#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <map>

#include "WeatherInfo.hpp"

namespace Resources
{
    namespace Settings
    {
        const QString File = "settings.conf";

        const QString CurrentWeatherApiService = "CurrentWeatherApi";
        const QString HourlyForecastApiService = "HourlyForecastApi";
        const QString DailyForecastApiService = "DailyForecastApi";
        const QString HistoricalWeatherApiService = "HistoricalWeatherApi";
        const QString ApiKey = "ApiKey";
    }

    QString getCollection(WeatherInfo info);
    QUrl formRequestUrl(const QString& apiSerivce, const std::map<QString, QString>& params);
}
