#include "BluetoothIconsProvider.hpp"

QImage BluetoothIconsProvider::requestImage(
        const QString& id
    ,   QSize* size
    ,   const  QSize& requestedSize
        )
{
    Q_UNUSED( size );

    QImage result (
        Icons::Resources::Utility::getIconPath(
                id
            ,   BluetoothThemeMap
            ,   Icons::Bluetooth::Keys::Unknown
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
