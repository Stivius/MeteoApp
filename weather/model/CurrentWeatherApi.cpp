#include "CurrentWeatherApi.hpp"

#include "core/ApiConfig.hpp"

CurrentWeatherApi::CurrentWeatherApi() :
    RapidWeatherApi{ApiConfig::currentWeatherApiKey(), ApiConfig::currentWeatherApiService()}
{
}

QUrl CurrentWeatherApi::formRequest(const QString& city)
{
    std::map<QString, QString> params = {
        {"q", city},
        {"units", "metric"}
    };

    return formRequestUrl(params);
}

QUrl CurrentWeatherApi::formRequest(double latitude, double longitude)
{
    std::map<QString, QString> params = {
        {"lat", QString::number(latitude)},
        {"lon", QString::number(longitude)},
        {"units", "metric"}
    };

    return formRequestUrl(params);
}
