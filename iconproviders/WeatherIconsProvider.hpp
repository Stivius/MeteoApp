#pragma once

#include <qquickimageprovider.h>
#include <QImage>

#include "ResourcesIcons.hpp"

class WeatherIconsProvider
        :   public QQuickImageProvider
{

public:

    WeatherIconsProvider();

    QImage requestImage( const QString& id, QSize* size , const  QSize& requestedSize ) override;

private:

    bool isImageNeedResize( const  QSize& requestedSize );

private:

    ApplicationTheme m_currentTheme;
};
