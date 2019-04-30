#include "WeatherIconsProvider.hpp"

WeatherIconsProvider::WeatherIconsProvider()
    :   QQuickImageProvider{ QQuickImageProvider::Image }
    ,   m_currentTheme{ ApplicationTheme::Light }
{
}


QImage WeatherIconsProvider::requestImage(
        const QString& id
    ,   QSize* size
    ,   const  QSize& requestedSize
        )
{
    Q_UNUSED( size );

    QImage result ( Icons::Resources::Utility::getIconUrl( id, m_currentTheme ).toLocalFile() );

    if( isImageNeedResize( requestedSize ) )
    {
        result = result.scaled(
                requestedSize.width()
            ,   requestedSize.height()
            ,    Qt::KeepAspectRatio
        );
    }

    return  result;
}


bool WeatherIconsProvider::isImageNeedResize( const  QSize& requestedSize )
{
    return requestedSize.width() > 0 && requestedSize.height() > 0;
}
