#include "ApiConfig.hpp"
#include "WeatherBaseApi.hpp"

#include <QNetworkReply>
#include <QUrlQuery>

WeatherBaseApi::WeatherBaseApi(QObject* parent) :
    QObject(parent)
{
}

void WeatherBaseApi::requestByCity(const QString& city)
{
    sendRequestImpl(formRequest(city));
}

void WeatherBaseApi::requestByCoords(double latitude, double longitude)
{
    sendRequestImpl(formRequest(latitude, longitude));
}

QUrl WeatherBaseApi::formRequestUrl(const QString& apiService, const std::map<QString, QString>& params)
{
    QUrl apiRequest{apiService};
    QUrlQuery query;

    for(auto [name, value] : params)
    {
        query.addQueryItem(name, value);
    }

    apiRequest.setQuery(query);

    return apiRequest;
}

void WeatherBaseApi::sendRequestImpl(const QUrl& url)
{
    QNetworkRequest nrq(url);
    nrq.setRawHeader("x-rapidapi-key", ApiConfig::apiKey().toStdString().c_str());
    nrq.setRawHeader("x-rapidapi-host", "community-open-weather-map.p.rapidapi.com");

    auto reply = m_networkAccessManager.get(nrq);

    connect(reply, &QNetworkReply::finished, this, &WeatherBaseApi::requestFinished);
    connect(reply, &QNetworkReply::sslErrors, this, &WeatherBaseApi::sslErrors);
}

void WeatherBaseApi::requestFinished()
{
    auto reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error())
    {
        emit error(reply->errorString());
    }
    else
    {
        emit responseReceived(reply->readAll());
    }

    reply->deleteLater();
}

void WeatherBaseApi::sslErrors(const QList<QSslError>& errors)
{
    QStringList errorList;

    for(const QSslError& error: errors)
    {
        errorList.append(error.errorString());
    }

    emit error(errorList.join('\n'));
}
