#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "core/api/ApiRequest.hpp"

class ApiManager : public QObject
{
    Q_OBJECT

public:
    explicit ApiManager(QObject* parent = nullptr);

    void sendRequest(const QSharedPointer<ApiRequest>& request);

private slots:
    void requestFinished(const QSharedPointer<ApiRequest>& request);
    void sslErrors(const QList<QSslError>& errors,const QSharedPointer<ApiRequest>& request);

private:
    QNetworkAccessManager m_networkAccessManager;

};
