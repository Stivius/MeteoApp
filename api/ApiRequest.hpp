#pragma once

#include <QObject>
#include <QUrl>

class ApiRequest : public QObject
{
    Q_OBJECT

signals:
    void received(const QJsonDocument& doc);
    void error(const QString& error);

public:
    ApiRequest(const QUrl& url);
    QUrl url() const;

private:
    QUrl m_url;

};
