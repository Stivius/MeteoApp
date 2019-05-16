#include "GlobalSettings.hpp"

GlobalSettings::GlobalSettings(QObject* parent) :
    QObject(parent)
{
}

GlobalSettings& GlobalSettings::get()
{
    static GlobalSettings instance;
    return instance;
}

void GlobalSettings::setLocation(const QString& location)
{
    m_location = location;
    emit locationChanged(location);
}

QString GlobalSettings::location() const
{
    return m_location;
}
