#include "BaseIconsProvider.hpp"

BaseIconsProvider::BaseIconsProvider()
    :   QQuickImageProvider{ QQuickImageProvider::Image }
    ,   currentTheme{ ApplicationTheme::Theme::Dark }
{
}

void BaseIconsProvider::setTheme( ApplicationTheme::Theme newTheme )
{
    currentTheme = newTheme;
    emit themeChanged( newTheme );
}

ApplicationTheme::Theme BaseIconsProvider::getTheme() const
{
    return currentTheme;
}


bool BaseIconsProvider::isImageNeedResize( const  QSize& requestedSize )
{
    return requestedSize.width() > 0 && requestedSize.height() > 0;
}
