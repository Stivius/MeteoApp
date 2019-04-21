#include "JsonFormatDataParser.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

float JsonFormatDataParser::getHumidity() const
{
    return m_humidity;
}

float JsonFormatDataParser::getPressure() const
{
    return m_pressure;
}

float JsonFormatDataParser::getTemperature() const
{
    return m_temperature;
}

void JsonFormatDataParser::tryParseValue( const QString& _toParse )
{
     QJsonDocument document = QJsonDocument::fromJson( _toParse.toUtf8() );
     QJsonObject received = document.object();

     m_humidity = static_cast<float>( received.value( Humidity ).toDouble() );
     m_pressure = static_cast<float>( received.value( Pressure ).toDouble() );
     m_temperature = static_cast<float>( received.value( Temp ).toDouble() );

}
