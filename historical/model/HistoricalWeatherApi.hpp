#pragma once

#include "core/WeatherBaseApi.hpp"

#include <memory>

class HistoricalWeatherApi : public WeatherBaseApi
{
private:
    using DateCallback = std::function<std::pair<QDate, QDate>()>;

public:
    HistoricalWeatherApi(DateCallback callback, QObject* parent = nullptr);

protected:
    QUrl formRequest(const QString& city) override;
    QUrl formRequest(double latitude, double longitude) override;

private:
    DateCallback m_dateDelegate;
    static const QString ms_dateFormat;
};
