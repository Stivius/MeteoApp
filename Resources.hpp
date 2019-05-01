#pragma once

#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <map>

#include "core/api/WeatherInfo.hpp"

namespace Resources
{
    namespace Settings
    {
        const QString File = ":/settings.conf";

        const QString CurrentWeatherApiService = "CurrentWeatherApi";
        const QString HourlyForecastApiService = "HourlyForecastApi";
        const QString DailyForecastApiService = "DailyForecastApi";
        const QString HistoricalWeatherApiService = "HistoricalWeatherApi";
        const QString HistoricalApiKey = "HistoricalApiKey";
        const QString ApiKey = "ApiKey";
    }

    QString getApiService(WeatherInfo info);
    QUrl formRequestUrl(const QString& apiSerivce, const std::map<QString, QString>& params);
}
