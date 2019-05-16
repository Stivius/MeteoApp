#include "WeatherIconsProvider.hpp"

#include "ResourcesIcons.hpp"

QImage WeatherIconsProvider::requestImage(
        const QString& id
    ,   QSize* size
    ,   const  QSize& requestedSize
        )
{
    Q_UNUSED( size );

    QImage result (
        Icons::Resources::Utility::getIconPath(
                id
            ,   WeatherThemeMap
            ,   Icons::Weather::Keys::Unknown
            ,   BaseIconsProvider::getTheme()
            )
        );

    if( BaseIconsProvider::isImageNeedResize( requestedSize ) )
    {
        result = result.scaled(
                requestedSize.width()
            ,   requestedSize.height()
            ,    Qt::KeepAspectRatio
        );
    }

    return  result;
}
