#include "ChunkedDataParser.hpp"

float ChunkedDataParser::getHumidity() const
{
    return m_humidity;
}

float ChunkedDataParser::getPressure() const
{
    return m_pressure;
}

float ChunkedDataParser::getTemperature() const
{
    return m_temperature;
}

float ChunkedDataParser::getFloatValueByKey( const QString& _key , const QString& _getFrom )
{
    auto substringIdx = _getFrom.indexOf( _key,0 ) + _key.length();
    auto contentLength = _getFrom.length() - substringIdx;
    QStringRef substr ( &_getFrom, substringIdx, contentLength );

    return substr.toFloat();
}

void ChunkedDataParser::tryParseValue( const QString& _toParse )
{
    if( _toParse.contains( Pressure ) )
    {
        m_pressure = getFloatValueByKey( Pressure , _toParse );
    }
    else if( _toParse.contains( Humidity ) )
    {
        m_humidity = getFloatValueByKey( Humidity , _toParse );
    }
    else if ( _toParse.contains( Temp ) )
    {
        m_temperature = getFloatValueByKey( Temp , _toParse );
    }
    else
    {
        assert( false );
    }
}
