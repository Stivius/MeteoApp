#pragma once

#include <QObject>

#include "core/WeatherDataParser.hpp"

class ForecastWeatherParser : public QObject, public WeatherDataParser
{
    Q_OBJECT
public:
    explicit ForecastWeatherParser(QObject *parent = nullptr);

    WeatherDataCollection parse(const QByteArray& data) override;

private:
    WeatherApiData parseJsonObject(const QJsonObject& data);
    qint64 toMSSinceEpoch(QJsonValue&& value) const;

};
