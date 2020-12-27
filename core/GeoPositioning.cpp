#include "GeoPositioning.hpp"

GeoPositioning::GeoPositioning(QObject* parent) :
    QObject(parent)
{
    m_positioningSource = QGeoPositionInfoSource::createDefaultSource(this);

    if(!m_positioningSource)
        return;

    connect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, this, &GeoPositioning::positionUpdated);

    connect(m_positioningSource,
            QOverload<QGeoPositionInfoSource::Error>::of(&QGeoPositionInfoSource::error),
            this,
            &GeoPositioning::positionError);

    m_positioningSource->startUpdates();
}

void GeoPositioning::requestUpdates()
{
    if(m_positioningSource)
        m_positioningSource->requestUpdate();
}

void GeoPositioning::positionUpdated(QGeoPositionInfo gpsPosition)
{
    auto coords = gpsPosition.coordinate();

    emit coordsUpdated(coords.latitude(), coords.longitude());
}

void GeoPositioning::positionError(QGeoPositionInfoSource::Error)
{
    emit error("GeoPositioning error");
}
