#pragma once

#include <qquickimageprovider.h>
#include <QImage>

#include "ResourcesIcons.hpp"
#include "ApplicationTheme.hpp"

class BaseIconsProvider
        :   public QObject
        ,   public QQuickImageProvider
{

    Q_OBJECT

public:

    BaseIconsProvider();
    virtual ~BaseIconsProvider() override = default;

public:

    Q_PROPERTY( ApplicationTheme::Theme CurrentTheme WRITE setTheme READ getTheme NOTIFY themeChanged )

signals:

    void themeChanged( ApplicationTheme::Theme );

public:

    virtual QImage requestImage( const QString& id, QSize* size , const  QSize& requestedSize ) = 0;

    void setTheme( ApplicationTheme::Theme newTheme );

    ApplicationTheme::Theme getTheme() const;

protected:

    bool isImageNeedResize( const  QSize& requestedSize );

private:

    ApplicationTheme::Theme currentTheme;
};
