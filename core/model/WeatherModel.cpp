#include "WeatherModel.hpp"
#include <memory>
static void forecastAppend(QQmlListProperty<AWeatherData> *prop, AWeatherData *val)
{
    Q_UNUSED(val);
    Q_UNUSED(prop);
}

static AWeatherData *forecastAt(QQmlListProperty<AWeatherData> *prop, int index)
{
    PrivateWeatherAccessor *d = static_cast<PrivateWeatherAccessor*>(prop->data);
    return d->forecast.at(index).get();
}

static int forecastCount(QQmlListProperty<AWeatherData> *prop)
{
    PrivateWeatherAccessor *d = static_cast<PrivateWeatherAccessor*>(prop->data);
    return d->forecast.size();
}

static void forecastClear(QQmlListProperty<AWeatherData> *prop)
{
    static_cast<PrivateWeatherAccessor*>(prop->data)->forecast.clear();
}

WeatherModel::WeatherModel(QObject* parent) :
    QObject(parent), m_dataSource(new WeatherApi())
  , m_WeatherAccessor(new PrivateWeatherAccessor)
{
    m_WeatherAccessor->fcProp.reset(new QQmlListProperty<AWeatherData>(
                this
                ,m_WeatherAccessor.get()
                ,forecastAppend
                ,forecastCount
                ,forecastAt
                ,forecastClear));

    connect(m_dataSource, &WeatherApi::currentWeatherReceived, this, &WeatherModel::updateModel);
    connect(m_dataSource, &WeatherApi::forecastReceived, this, &WeatherModel::updateForecast);
    connect(&m_geoPositioning, &GeoPositioning::coordsUpdated, this, &WeatherModel::requestWeatherByCoords);
}

void WeatherModel::requestCityWeather(const QString& city)
{
    m_dataSource->requestCityWeather(city/*, WeatherInfo::Daily*/);
}

void WeatherModel::requestCityForecast(const QString &city)
{
    m_dataSource->requestCityForecast(city);
}

void WeatherModel::requestCurrentGeoWeather()
{
    m_geoPositioning.requestUpdates();
}

void WeatherModel::requestWeatherByCoords(double latitude, double longitude)
{
    m_dataSource->requestWeatherByCoordinates(latitude, longitude);
}

QQmlListProperty<AWeatherData> WeatherModel::forecast() const
{
    return *m_WeatherAccessor->fcProp.get();
}

QString WeatherModel::city() const
{
    return m_WeatherAccessor->now.city();
}

void WeatherModel::setCity(const QString& cityName)
{
    m_WeatherAccessor->now.setCity(cityName);
    emit cityChanged(cityName);
}

QString WeatherModel::condition() const
{
    return m_WeatherAccessor->now.condition();
}

void WeatherModel::setCondition(const QString& condition)
{
    m_WeatherAccessor->now.setCondition(condition);
    emit conditionChanged(condition);
}

void WeatherModel::setIcon(const QString &icon)
{
    m_WeatherAccessor->now.setWeatherIcon(icon);
    emit iconChanged(icon);
}

QString WeatherModel::icon() const
{
    return m_WeatherAccessor->now.weatherIcon();
}

QString WeatherModel::description() const
{
    return m_WeatherAccessor->now.weatherDescription();
}

void WeatherModel::setDescription(const QString& description)
{
    m_WeatherAccessor->now.setWeatherDescription(description);
    emit descriptionChanged(description);
}

double WeatherModel::maxTemperature() const
{
    return m_WeatherAccessor->now.maxTemperature();
}

double WeatherModel::minTemperature() const
{
    return m_WeatherAccessor->now.minTemperature();
}

void WeatherModel::setMaxTemperature(int temperature)
{
    m_WeatherAccessor->now.setMaxTemperature(temperature);
    emit temperatureChanged(temperature);
}

void WeatherModel::setMinTemperature(int temperature)
{
    m_WeatherAccessor->now.setMinTemperature(temperature);
    emit temperatureChanged(temperature);
}

double WeatherModel::pressure() const
{
    return m_WeatherAccessor->now.pressure();
}

void WeatherModel::setPressure(double pressure)
{
    m_WeatherAccessor->now.setPressure(pressure);
    emit pressureChanged(pressure);
}

int WeatherModel::humidity() const
{
    return m_WeatherAccessor->now.humidity();
}

void WeatherModel::setHumidity(int humidity)
{
    m_WeatherAccessor->now.setHumidity(humidity);
    emit humdityChanged(humidity);
}

void WeatherModel::updateModel(const WeatherData& data)
{
    setCity(data.city);
    setCondition(data.condition);
    setIcon(data.weatherIcon);
    setDescription(data.description);
    setMaxTemperature(data.temperatureMax);
    setMinTemperature(data.temperatureMin);
    setPressure(data.pressure);
    setHumidity(data.humidity);
}

void WeatherModel::updateForecast(const WeatherDataCollection& data)
{
    m_WeatherAccessor->forecast.clear();
    for(const auto& n_weater : data)
    {
        auto tempData = std::make_unique<AWeatherData>(new AWeatherData());
        tempData->setCity(n_weater.city);
        tempData->setDayOfWeek(n_weater.dayOfTheWeek);
        tempData->setPressure(n_weater.pressure);
        tempData->setHumidity(n_weater.humidity);
        tempData->setCondition(n_weater.condition);
        tempData->setMaxTemperature(n_weater.temperatureMax);
        tempData->setMinTemperature(n_weater.temperatureMin);
        tempData->setWeatherIcon(n_weater.weatherIcon);
        tempData->setWeatherDescription(n_weater.description);
        m_WeatherAccessor->forecast.emplace_back(std::move(tempData));
    }
    emit forecastChanged(forecast());
}


