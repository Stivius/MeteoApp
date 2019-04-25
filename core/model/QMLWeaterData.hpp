#ifndef AWEATHERDATA_H
#define AWEATHERDATA_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtQml/QQmlListProperty>
#include "WeatherData.hpp"

class AWeatherData : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString dayOfWeek
               READ dayOfWeek WRITE setDayOfWeek
               NOTIFY dataChanged)
    Q_PROPERTY(QString weatherIcon
               READ weatherIcon WRITE setWeatherIcon
               NOTIFY dataChanged)
    Q_PROPERTY(QString weatherDescription
               READ weatherDescription WRITE setWeatherDescription
               NOTIFY dataChanged)
    Q_PROPERTY(QString city
               READ city WRITE setCity
               NOTIFY dataChanged)
    Q_PROPERTY(QString condition
               READ condition WRITE setCondition
               NOTIFY dataChanged)
    Q_PROPERTY(double maxTemperature
               READ maxTemperature WRITE setMaxTemperature
               NOTIFY dataChanged)
    Q_PROPERTY(double minTemperature
               READ minTemperature WRITE setMinTemperature
               NOTIFY dataChanged)
    Q_PROPERTY(double pressure
               READ pressure WRITE setPressure
               NOTIFY dataChanged)
    Q_PROPERTY(int humidity
               READ humidity WRITE setHumidity
               NOTIFY dataChanged)

public:
    explicit AWeatherData(QObject *parent = nullptr);
    AWeatherData(const AWeatherData &other);

    QString dayOfWeek() const;
    QString city() const;
    QString weatherIcon() const;
    QString weatherDescription() const;
    QString condition() const;
    int maxTemperature() const;
    int minTemperature() const;
    double pressure() const;
    int humidity() const;

    void setDayOfWeek(const QString &value);
    void setCity(const QString &value);
    void setWeatherIcon(const QString &value);
    void setWeatherDescription(const QString &value);
    void setCondition(const QString &value);
    void setMaxTemperature(const int &value);
    void setMinTemperature(const int &value);
    void setPressure(const double &value);
    void setHumidity(const int &value);

signals:
    void dataChanged();

private:
    QString m_city;
    QString m_dayOfWeek;
    QString m_weatherIcon;
    QString m_weatherDescription;
    QString m_condition;
    int m_maxTemperature;
    int m_minTemperature;
    double m_pressure;
    int m_humidity;
};

Q_DECLARE_METATYPE(AWeatherData)

#endif // AWEATHERDATA_H
