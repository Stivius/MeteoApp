#include "RapidWeatherApi.hpp"

RapidWeatherApi::RapidWeatherApi(const QString& apiKey, const QString& apiService, QObject* parent) :
    WeatherBaseApi(apiService, parent),
    m_apiKey{apiKey}
{

}

QNetworkRequest RapidWeatherApi::prepareNetworkRequest(const QUrl& url)
{
    QNetworkRequest request{url};

    request.setRawHeader("x-rapidapi-key", m_apiKey.toUtf8());
    request.setRawHeader("x-rapidapi-host", url.host().toUtf8());

    return request;
}
