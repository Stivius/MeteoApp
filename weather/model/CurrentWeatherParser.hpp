#pragma once

#include <QObject>

#include "core/WeatherDataParser.hpp"

class CurrentWeatherParser : public QObject, public WeatherDataParser
{
    Q_OBJECT
public:
    explicit CurrentWeatherParser(QObject *parent = nullptr);

    WeatherDataCollection parse(const QByteArray& data) override;

private:
    WeatherApiData parseJsonObject(const QJsonObject& data);
    qint64 toMSSinceEpoch(QJsonValue&& value) const;

};
