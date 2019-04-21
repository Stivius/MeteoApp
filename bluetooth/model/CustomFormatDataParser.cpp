#include "CustomFormatDataParser.hpp"

float CustomFormatDataParser::getHumidity() const
{
    return m_humidity;
}

float CustomFormatDataParser::getPressure() const
{
    return m_pressure;
}

float CustomFormatDataParser::getTemperature() const
{
    return m_temperature;
}

std::pair<int, int> CustomFormatDataParser::getKeyIndexes(
         const QString& _dataSource
     ,   const QString& _searchKeyBegin
     ,   const QString& _searchKeyEnd
)
 {
     int keyBegin = _dataSource.indexOf(_searchKeyBegin, 0) + _searchKeyBegin.length();
     int keyEnd = _dataSource.indexOf( _searchKeyEnd, 0 );

     return { keyBegin, keyEnd };
 }

float CustomFormatDataParser::getFloatFromRange( const QString& _dataSource, int _keyBegin, int _keyEnd )
{
    QStringRef subString(&_dataSource, _keyBegin, _keyEnd - _keyBegin);
    return subString.toFloat();
}

void CustomFormatDataParser::tryParseValue( const QString& _toParse )
{
    if ( isDataValid( _toParse ) )
    {
        try
        {
            {
                auto [ Item1,Item2 ] = getKeyIndexes( _toParse, PressureBegin, PressureEnd );
                m_pressure = getFloatFromRange( _toParse, Item1 , Item2 );
            }
            {
                auto [ Item1,Item2 ] = getKeyIndexes( _toParse, TempBegin, TempEnd );
                m_temperature= getFloatFromRange( _toParse , Item1, Item2 );
            }
            {
                auto [ Item1,Item2 ] = getKeyIndexes( _toParse, HumidityBegin, HumidityEnd );
                 m_humidity = getFloatFromRange( _toParse, Item1, Item2 );
            }
         }
         catch( ... )
         {
         }
     }
}

bool CustomFormatDataParser::isDataValid( const QString& _toParse ) const
{
    return  _toParse.contains( PressureBegin ) && _toParse.contains( PressureEnd )
            &&  ( _toParse.contains( TempBegin ) && _toParse.contains( TempEnd ) )
            &&  ( _toParse.contains( HumidityBegin ) && _toParse.contains( HumidityEnd ) );
}

