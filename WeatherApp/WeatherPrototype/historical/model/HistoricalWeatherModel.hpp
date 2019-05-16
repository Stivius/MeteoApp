#pragma once

#include "core/WeatherModel.hpp"
#include "historical/model/HistoricalWeatherData.hpp"

class HistoricalWeatherModel : public WeatherModel<HistoricalWeatherModel, HistoricalWeatherData>
{
    Q_OBJECT

    Q_PROPERTY(int maxTemperature MEMBER m_temperatureMax NOTIFY maxTemperatureChanged)
    Q_PROPERTY(int minTemperature MEMBER m_temperatureMin NOTIFY minTemperatureChanged)
    Q_PROPERTY(QString maxTemperatureDate MEMBER m_tMaxDate NOTIFY maxTemperatureDateChanged)
    Q_PROPERTY(QString minTemperatureDate MEMBER m_tMinDate NOTIFY minTemperatureDateChanged)

signals:
    void maxTemperatureChanged(int temperature);
    void minTemperatureChanged(int temperature);
    void maxTemperatureDateChanged(const QString& date);
    void minTemperatureDateChanged(const QString& date);

public:
    HistoricalWeatherModel(QObject* parent = nullptr);

    Q_INVOKABLE void setDayDate(int day, int month, int year);
    Q_INVOKABLE void setWeekDate(int week, int year);
    Q_INVOKABLE void setMonthDate(int month, int year);

    static void registerQmlType();

protected:
    void updateModel(const HistoricalWeatherData& data) override;

private:
    int m_temperatureMax = 0;
    int m_temperatureMin = 0;
    QString m_tMaxDate   = "";
    QString m_tMinDate   = "";

private:
    QDate m_startDate;
    QDate m_finishDate;

};
