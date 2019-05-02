#include "WeatherModel.hpp"

#include "core/GlobalSettings.hpp"

WeatherModel::WeatherModel(std::unique_ptr<WeatherBaseApi>&& weatherApi,
                           std::unique_ptr<WeatherDataParser>&& dataParser,
                           QObject* parent) :
    QObject(parent),
    m_weatherApi(std::move(weatherApi)),
    m_dataParser(std::move(dataParser))
{
    connect(&m_geoPositioning, &GeoPositioning::coordsUpdated, this, &WeatherModel::coordsUpdated);
    connect(&m_geoPositioning, &GeoPositioning::error, this, &WeatherModel::geoLocationError);

    connect(m_weatherApi.get(), &WeatherBaseApi::responseReceived, this, &WeatherModel::responseReceived);
    connect(m_weatherApi.get(), &WeatherBaseApi::error, this, &WeatherModel::responseError);

    connect(&GlobalSettings::get(), &GlobalSettings::locationChanged, this, &WeatherModel::locationChanged);
}

void WeatherModel::locationChanged(const QString& location)
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

void WeatherModel::coordsUpdated(double latitude, double longitude)
{
    qDebug() << "coords";
    m_weatherApi->requestByCoords(latitude, longitude);
}

void WeatherModel::geoLocationError(const QString& error)
{
    qDebug() << error;
}

void WeatherModel::responseReceived(const QByteArray& response)
{
    updateModel(m_dataParser->parse(response));
}

void WeatherModel::responseError(const QString& error)
{
    qDebug() << "API response error:" << error;
}
