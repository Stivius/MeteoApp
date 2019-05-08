#include "CurrentWeatherApi.hpp"

#include "core/ApiConfig.hpp"

QUrl CurrentWeatherApi::formRequest(const QString& city)
{
    std::map<QString, QString> params = {
        {"q", city},
        {"units", "metric"},
        {"appid", ApiConfig::apiKey()}
    };

    return formRequestUrl(ApiConfig::currentWeatherApi(), params);
}

QUrl CurrentWeatherApi::formRequest(double latitude, double longitude)
{
    std::map<QString, QString> params = {
        {"lat", QString::number(latitude)},
        {"lon", QString::number(longitude)},
        {"units", "metric"},
        {"appid", ApiConfig::apiKey()}
    };

    return formRequestUrl(ApiConfig::currentWeatherApi(), params);
}
