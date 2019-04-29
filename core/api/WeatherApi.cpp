#include "WeatherApi.hpp"
#include "WeatherJsonParser.hpp"

#include "Resources.hpp"
#include "ApiConfig.hpp"

WeatherApi::WeatherApi(QObject* parent) :
    QObject(parent)
{
}

// Hourly and Daily API are unstable and should not be used
void WeatherApi::requestCityWeather(const QString& city)
{
    auto service = Resources::getApiService(WeatherInfo::Current);
    std::map<QString, QString> params = {{"q", city}, {"units", "metric"}, {"appid", ApiConfig::apiKey()}};

    sendRequest(Resources::formRequestUrl(service, params));
}

void WeatherApi::requestCityForecast(const QString& city)
{
    auto service = Resources::getApiService(WeatherInfo::Daily);
    std::map<QString, QString> params =
    {
          {"q", city}
        , {"units", "metric"}
        , {"cnt", "5"}
        , {"appid"
        , ApiConfig::apiKey()}
    };

    sendRequest(Resources::formRequestUrl(service, params));
}

// Hourly and Daily API are unstable and should not be used
void WeatherApi::requestWeatherByCoordinates(double latitude, double longitude, WeatherInfo info)
{
    auto lat = QString::number(latitude);
    auto lon = QString::number(longitude);

    auto service = Resources::getApiService(info);
    std::map<QString, QString> params = {{"lat", lat}, {"lon", lon}, {"units", "metric"}, {"appid", ApiConfig::apiKey()}};

    sendRequest(Resources::formRequestUrl(service, params));
}

void WeatherApi::sendRequest(const QUrl& url)
{
    auto request = QSharedPointer<ApiRequest>::create(url);

    connect(request.get(), &ApiRequest::received, this, &WeatherApi::processResponse);
    connect(request.get(), &ApiRequest::error, this, &WeatherApi::error);

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

void WeatherApi::error(const QString& error)
{
    qDebug() << error;
}
