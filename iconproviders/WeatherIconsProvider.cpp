#include "WeatherIconsProvider.hpp"

WeatherIconsProvider::WeatherIconsProvider()
    :   QQuickImageProvider{ QQuickImageProvider::Image }
    ,   currentTheme{ ApplicationTheme::Theme::Dark }
{
}


QImage WeatherIconsProvider::requestImage(
        const QString& id
    ,   QSize* size
    ,   const  QSize& requestedSize
        )
{
    Q_UNUSED( size );

    QImage result ( Icons::Resources::Utility::getIconPath( id, currentTheme ) );

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

void WeatherIconsProvider::setTheme( ApplicationTheme::Theme newTheme )
{
    currentTheme = newTheme;
    emit themeChanged( newTheme );
}

ApplicationTheme::Theme WeatherIconsProvider::getTheme() const
{
    return currentTheme;
}


bool WeatherIconsProvider::isImageNeedResize( const  QSize& requestedSize )
{
    return requestedSize.width() > 0 && requestedSize.height() > 0;
}
