#include "GeoPositioning.hpp"

GeoPositioning::GeoPositioning(QObject *parent) :
    QObject(parent)
{
    m_positioningSource = QGeoPositionInfoSource::createDefaultSource(this);

    connect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, this, &GeoPositioning::positionUpdated);

    connect(m_positioningSource,
            QOverload<QGeoPositionInfoSource::Error>::of(&QGeoPositionInfoSource::error),
            this,
            &GeoPositioning::positionError);
}

GeoPositioning::~GeoPositioning()
{
}

void GeoPositioning::requestUpdates()
{
    m_positioningSource->requestUpdate();
}

void GeoPositioning::positionUpdated(QGeoPositionInfo gpsPosition)
{
    auto coords = gpsPosition.coordinate();

    emit coordsUpdated(coords.latitude(), coords.longitude());
}

void GeoPositioning::positionError(QGeoPositionInfoSource::Error)
{
    m_positioningSource->deleteLater();

    emit error("GeoPositioning error");
}
