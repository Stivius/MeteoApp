#pragma once

#include <QObject>
#include <QJsonArray>

#include "historical/model/HistoricalWeatherData.hpp"

class HistoricalWeatherParser : public QObject
{
    Q_OBJECT

public:
    explicit HistoricalWeatherParser(QObject *parent = nullptr);

    HistoricalWeatherData parse(const QByteArray& data);

private:
    HistoricalWeatherDay parseDay(const QJsonValueRef dayInfo);
    HistoricalWeatherUnit parseUnit(const QJsonValueRef unitInfo);

};
