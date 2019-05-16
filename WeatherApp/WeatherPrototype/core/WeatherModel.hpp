#pragma once

#include <QObject>

#include "core/WeatherBaseApi.hpp"
#include "core/GeoPositioning.hpp"
#include "core/WeatherDataParser.hpp"
#include "core/GlobalSettings.hpp"

template <typename Derrived, typename Base = QObject>
class WeatherModel : public Base
{
public:
    WeatherModel(std::unique_ptr<WeatherBaseApi>&& weatherApi,
                 std::unique_ptr<WeatherDataParser>&& dataParser,
                 QObject* parent = nullptr)  :
        Base(parent),
        m_weatherApi(std::move(weatherApi)),
        m_dataParser(std::move(dataParser))
    {
        QObject::connect(&m_geoPositioning, &GeoPositioning::coordsUpdated, dthis(), &WeatherModel::coordsUpdated);
        QObject::connect(&m_geoPositioning, &GeoPositioning::error, dthis(), &WeatherModel::geoLocationError);

        QObject::connect(m_weatherApi.get(), &WeatherBaseApi::responseReceived, dthis(), &WeatherModel::responseReceived);
        QObject::connect(m_weatherApi.get(), &WeatherBaseApi::error, dthis(), &WeatherModel::responseError);

        QObject::connect(&GlobalSettings::get(), &GlobalSettings::locationChanged, dthis(), &WeatherModel::locationChanged);
    }


public slots:
    void locationChanged(const QString& location)
    {
        if(location == "Current")
        {
            m_geoPositioning.requestUpdates();
        }
        else
        {
            m_weatherApi->requestByCity(location);
        }
    }

protected:
    virtual void updateModel(const WeatherDataCollection& data) = 0;

private slots:
    void coordsUpdated(double latitude, double longitude)
    {
        m_weatherApi->requestByCoords(latitude, longitude);
    }

    void geoLocationError(const QString& error)
    {
        qDebug() << error;
    }

    void responseReceived(const QByteArray& response)
    {
        updateModel(m_dataParser->parse(response));
    }

    void responseError(const QString& error)
    {
        qDebug() << "API response error:" << error;
    }

private:
    Derrived* dthis()
    {
        return static_cast<Derrived*>(this);
    }

private:
    GeoPositioning m_geoPositioning;
    std::unique_ptr<WeatherBaseApi> m_weatherApi;
    std::unique_ptr<WeatherDataParser> m_dataParser;

};
