#include "WeatherModel.hpp"

WeatherModel::WeatherModel(std::unique_ptr<WeatherBaseApi>&& weatherApi,
                           std::unique_ptr<WeatherDataParser>&& dataParser,
                           QObject* parent) :
    QObject(parent),
    m_weatherApi(std::move(weatherApi)),
    m_dataParser(std::move(dataParser))
{
    connect(&m_geoPositioning, &GeoPositioning::coordsUpdated, this, &WeatherModel::coordsUpdated);
    connect(m_weatherApi.get(), &WeatherBaseApi::responseReceived, this, &WeatherModel::responseReceived);
}

void WeatherModel::locationUpdated(const QString& location)
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
    m_weatherApi->requestByCoords(latitude, longitude);
}

void WeatherModel::responseReceived(const QByteArray& response)
{
    updateModel(m_dataParser->parse(response));
}
