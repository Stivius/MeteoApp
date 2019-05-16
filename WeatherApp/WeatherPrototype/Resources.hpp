#pragma once

#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <map>


namespace Resources
{
    namespace Settings
    {
        const QString File = ":/settings.conf";

        const QString CurrentWeatherApiService = "CurrentWeatherApi";
        const QString HourlyForecastApiService = "HourlyForecastApi";
        const QString DailyForecastApiService = "DailyForecastApi";
        const QString HistoricalWeatherApiService = "HistoricalWeatherApi";
        const QString ApiKey = "ApiKey";
    }
}
