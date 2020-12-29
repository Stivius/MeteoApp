#include "ApiConfig.hpp"
#include "WeatherBaseApi.hpp"

#include <QNetworkReply>
#include <QUrlQuery>

WeatherBaseApi::WeatherBaseApi(const QString& apiService, QObject* parent) :
    QObject(parent),
    m_apiService(apiService)
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

QUrl WeatherBaseApi::formRequestUrl(const std::map<QString, QString>& params)
{
    QUrl apiRequest{m_apiService};
    QUrlQuery query;

    for(auto [name, value] : params)
    {
        query.addQueryItem(name, value);
    }

    apiRequest.setQuery(query);

    return apiRequest;
}

QNetworkRequest WeatherBaseApi::prepareNetworkRequest(const QUrl &url)
{
    return QNetworkRequest{url};
}

void WeatherBaseApi::sendRequestImpl(const QUrl& url)
{
    auto reply = m_networkAccessManager.get(prepareNetworkRequest(url));

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
