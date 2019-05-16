#pragma once

#include <QObject>
#include <QtPositioning>

class GeoPositioning : public QObject
{
    Q_OBJECT

signals:
    void coordsUpdated(double latitude, double longitude);
    void error(const QString& error);

public:
    explicit GeoPositioning(QObject* parent = nullptr);

    void requestUpdates();

private slots:
    void positionUpdated(QGeoPositionInfo gpsPos);
    void positionError(QGeoPositionInfoSource::Error e);

private:
    QGeoPositionInfoSource* m_positioningSource = nullptr;

};
