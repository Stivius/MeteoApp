#include "WeatherApi.hpp"
#include "WeatherJsonParser.hpp"

#include "Resources.hpp"

WeatherApi::WeatherApi(QObject* parent) :
    QObject(parent)
{
}

// Hourly and Daily API are unstable and should not be used
void WeatherApi::requestCityWeather(const QString& city, WeatherInfo info)
{
    auto collection = Resources::getCollection(info);

    auto url = Resources::formRequestUrl(collection, {{"q", city}, {"units", "metric"}, {"appid", "4bdac748869ecbd195cb05e9bce26006"}});

    sendRequest(url);
}

// Hourly and Daily API are unstable and should not be used
void WeatherApi::requestWeatherByCoordinates(double latitude, double longitude, WeatherInfo info)
{
    auto collection = Resources::getCollection(info);
    auto lat = QString::number(latitude);
    auto lon = QString::number(longitude);

    auto url = Resources::formRequestUrl(collection, {{"lat", lat}, {"lon", lon}, {"units", "metric"}, {"appid", "4bdac748869ecbd195cb05e9bce26006"}});

    sendRequest(url);
}

void WeatherApi::sendRequest(const QUrl& url)
{
    auto request = QSharedPointer<ApiRequest>::create(url);

    connect(request.get(), &ApiRequest::received, this, &WeatherApi::processResponse);

    m_manager.sendRequest(request);
}

void WeatherApi::processResponse(const QJsonDocument& data)
{
    WeatherJsonParser parser;
    auto result = parser.parseFromJson(data);

    if(result.size() > 1)
    {
        emit forecastReceived(result);
    }
    else
    {
        emit currentWeatherReceived(result.front());
    }
}
