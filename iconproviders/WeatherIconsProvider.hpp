#pragma once

#include <qquickimageprovider.h>
#include <QImage>

#include "ResourcesIcons.hpp"
#include "ApplicationTheme.hpp"

class WeatherIconsProvider
        :   public QObject
        ,   public QQuickImageProvider
{

    Q_OBJECT

public:

    WeatherIconsProvider();
    ~WeatherIconsProvider() override = default;

public:

    Q_PROPERTY( ApplicationTheme::Theme CurrentTheme WRITE setTheme READ getTheme NOTIFY themeChanged )

signals:

    void themeChanged( ApplicationTheme::Theme );

public:

    QImage requestImage( const QString& id, QSize* size , const  QSize& requestedSize ) override;

    void setTheme( ApplicationTheme::Theme newTheme );

    ApplicationTheme::Theme getTheme() const;

private:

    bool isImageNeedResize( const  QSize& requestedSize );

private:

    ApplicationTheme::Theme currentTheme;
};
