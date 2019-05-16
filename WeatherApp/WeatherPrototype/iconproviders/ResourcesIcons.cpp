#include "ResourcesIcons.hpp"
#include <map>
#include <QRegExp>

namespace
{
    QString getUrlFromThemeMap(
        const QString& iconKey
    ,   const IconsStore& iconsHolder
    ,   const QString& unknownIconKey
    ,   const QString& regexFilter
    )

    {
        QString iconString;
        if( auto iconIt = iconsHolder.find( iconKey ); iconIt!= iconsHolder.end() )
            iconString= iconIt->second.toLocalFile();
        else
            iconString = iconsHolder.at( unknownIconKey ).toLocalFile();

        QRegExp regex { Icons::Paths::ThemePath::MatchRegex };
        iconString.replace( regex, regexFilter );

        return iconString;
    }
}

QString Icons::Resources::Utility::getIconPath(
        const QString& iconId
    ,   const IconsStore& iconsMap
    ,   const QString& unknownIconKey
    ,   ApplicationTheme::Theme theme
    )
{
    switch ( theme )
    {

    case ApplicationTheme::Theme::Dark:
    {
        return getUrlFromThemeMap(
                iconId
            ,   iconsMap
            ,   unknownIconKey
            ,   Icons::Paths::ThemePath::DarkTheme
        );
    }
    break;

    case ApplicationTheme::Theme::Light:
    {
        return getUrlFromThemeMap(
                iconId
            ,   iconsMap
            ,   unknownIconKey
            ,   Icons::Paths::ThemePath::LightTheme
        );
    }
    break;

    default:
    {
        Q_ASSERT(false);
        return QString("");
    }

    }
}
