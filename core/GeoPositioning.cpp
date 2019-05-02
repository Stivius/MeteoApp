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

void GeoPositioning::requestUpdates()
{
    qDebug() << "requested updated";
    m_positioningSource->requestUpdate();
}

void GeoPositioning::positionUpdated(QGeoPositionInfo gpsPosition)
{
    qDebug() << "position updated";

    auto coords = gpsPosition.coordinate();

    emit coordsUpdated(coords.latitude(), coords.longitude());
}

void GeoPositioning::positionError(QGeoPositionInfoSource::Error)
{
    emit error("GeoPositioning error");
}
