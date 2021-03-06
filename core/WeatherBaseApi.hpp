#pragma once

#include <QObject>
#include <QNetworkAccessManager>

class WeatherBaseApi : public QObject
{
    Q_OBJECT

signals:
    void responseReceived(const QByteArray& data);
    void error(const QString& error);

public:
    explicit WeatherBaseApi(const QString& apiService, QObject* parent = nullptr);

    void requestByCity(const QString& city);
    void requestByCoords(double latitude, double longitude);

protected:
    virtual QUrl formRequest(const QString& city) = 0;
    virtual QUrl formRequest(double latitude, double longitude) = 0;

    QUrl formRequestUrl(const std::map<QString, QString>& params);
    virtual QNetworkRequest prepareNetworkRequest(const QUrl& url);

private:
    void sendRequestImpl(const QUrl& url);

private slots:
    void requestFinished();
    void sslErrors(const QList<QSslError>& errors);

private:
    QString m_apiService;
    QNetworkAccessManager m_networkAccessManager;

};
