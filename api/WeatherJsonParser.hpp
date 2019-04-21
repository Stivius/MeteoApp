#pragma once

#include <QObject>

#include "WeatherData.hpp"

class WeatherJsonParser : public QObject
{
    Q_OBJECT
public:
    explicit WeatherJsonParser(QObject *parent = nullptr);

    WeatherDataCollection parseFromJson(const QJsonDocument& data);

private:
    WeatherData parseJsonObject(const QJsonObject& data);

};
