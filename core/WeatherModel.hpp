#pragma once

#include <QObject>

#include "core/WeatherBaseApi.hpp"
#include "core/GeoPositioning.hpp"
#include "core/WeatherDataParser.hpp"

class WeatherModel : public QObject
{
    Q_OBJECT

public:
    WeatherModel(std::unique_ptr<WeatherBaseApi>&& weatherApi,
                 std::unique_ptr<WeatherDataParser>&& dataParser,
                 QObject* parent = nullptr);

public slots:
    void locationChanged(const QString& location);

protected:
    virtual void updateModel(const WeatherDataCollection& data) = 0;

private slots:
    void coordsUpdated(double latitude, double longitude);
    void geoLocationError(const QString& error);

    void responseReceived(const QByteArray& response);
    void responseError(const QString& error);

private:
    GeoPositioning m_geoPositioning;
    std::unique_ptr<WeatherBaseApi> m_weatherApi;
    std::unique_ptr<WeatherDataParser> m_dataParser;

};
