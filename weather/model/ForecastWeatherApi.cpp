#include "ForecastWeatherApi.hpp"

#include "core/ApiConfig.hpp"

QUrl ForecastWeatherApi::formRequest(const QString& city)
{
    std::map<QString, QString> params = {
        {"q", city},
        {"units", "metric"},
        {"cnt", "5"},
        {"appid", ApiConfig::apiKey()}
    };

    return formRequestUrl(ApiConfig::dailyForecstApi(), params);
}

QUrl ForecastWeatherApi::formRequest(double latitude, double longitude)
{
    std::map<QString, QString> params = {
        {"lat", QString::number(latitude)},
        {"lon", QString::number(longitude)},
        {"units", "metric"},
        {"cnt", "5"},
        {"appid", ApiConfig::apiKey()}
    };

    return formRequestUrl(ApiConfig::dailyForecstApi(), params);
}
