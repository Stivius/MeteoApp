#pragma once

#include <QObject>

#include "core/WeatherModel.hpp"
#include "core/GeoPositioning.hpp"
#include "core/WeatherDataParser.hpp"
#include "core/GlobalSettings.hpp"

template <typename WeatherData, typename Base = QObject>
class WeatherGeoModel : public WeatherModel<WeatherData, Base>
{
public:
    using BaseClass = WeatherModel<WeatherData, Base>;

    WeatherGeoModel(std::unique_ptr<WeatherBaseApi>&& weatherApi,
                    std::unique_ptr<typename BaseClass::ParserType>&& dataParser,
                    QObject* parent = nullptr)  :
       BaseClass(std::move(weatherApi), std::move(dataParser), parent)
    {
        QObject::connect(&m_geoPositioning, &GeoPositioning::coordsUpdated, this, &WeatherGeoModel::coordsUpdated);
        QObject::connect(&m_geoPositioning, &GeoPositioning::error, this, &WeatherGeoModel::geoLocationError);

        QObject::connect(&GlobalSettings::get(), &GlobalSettings::locationChanged, this, &WeatherGeoModel::locationChanged);
    }


public slots:
    void locationChanged(const QString& location)
    {
        if(location == "Current")
        {
            qDebug() << "Current location. Updating weather info...";
            m_geoPositioning.requestUpdates();
        }
        else
        {
            qDebug() << "Location changed. Updating weather info...";
            this->api().requestByCity(location);
        }
    }

protected:
    virtual void updateModel(const WeatherData& data) = 0;


private slots:
    void coordsUpdated(double latitude, double longitude)
    {
        qDebug() << "Coords changed. Updating weather info...";
        this->api().requestByCoords(latitude, longitude);
    }

    void geoLocationError(const QString& error)
    {
        qDebug() << error;
    }

    void responseError(const QString& error)
    {
        qDebug() << "API response error:" << error;
    }

private:
    GeoPositioning m_geoPositioning;

};
