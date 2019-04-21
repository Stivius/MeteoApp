#include "ApiManager.hpp"

#include <QtNetwork>
#include <QUrl>

ApiManager::ApiManager(QObject* parent) :
    QObject(parent)
{
}

void ApiManager::sendRequest(const QSharedPointer<ApiRequest>& request)
{
    auto reply = m_networkAccessManager.get(QNetworkRequest(request->url()));

    connect(reply, &QNetworkReply::finished, this, [this, request](){
        requestFinished(request);
    });

    connect(reply, &QNetworkReply::sslErrors, [this, request](const QList<QSslError>& errors){
        sslErrors(errors, request);
    });
}

void ApiManager::requestFinished(const QSharedPointer<ApiRequest>& request)
{
    auto reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error())
    {
        emit request->error(reply->errorString());
    }
    else
    {
        emit request->received(QJsonDocument::fromJson(reply->readAll()));
    }

    reply->deleteLater();
}

void ApiManager::sslErrors(const QList<QSslError>& errors, const QSharedPointer<ApiRequest>& request)
{
    QStringList errorList;

    for(const QSslError& error: errors)
    {
        errorList.append(error.errorString());
    }    

    emit request->error(errorList.join('\n'));
}
