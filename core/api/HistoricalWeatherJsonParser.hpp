#pragma once

#include <QObject>

#include "core/model/HistoricalWeatherWrappers.hpp"

class HistoricalWeatherJsonParser : public QObject
{
    Q_OBJECT

public:
    explicit HistoricalWeatherJsonParser(QObject *parent = nullptr);

    HistoricalWeatherData parseFromJson(const QJsonDocument& data);

};
