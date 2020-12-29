#include "ForecastWeatherApi.hpp"

#include "core/ApiConfig.hpp"

ForecastWeatherApi::ForecastWeatherApi() :
    RapidWeatherApi{ApiConfig::forecastWeatherApiKey(), ApiConfig::forecstWeatherApiService()}
{
}

QUrl ForecastWeatherApi::formRequest(const QString& city)
{
    std::map<QString, QString> params = {
        {"q", city},
        {"units", "metric"}
    };

    return formRequestUrl(params);
}

QUrl ForecastWeatherApi::formRequest(double latitude, double longitude)
{
    std::map<QString, QString> params = {
        {"lat", QString::number(latitude)},
        {"lon", QString::number(longitude)},
        {"units", "metric"}
    };

    return formRequestUrl(params);
}
