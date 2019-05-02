#pragma once

#include <QObject>
#include <QQmlEngine>

namespace ApplicationTheme
{
    Q_NAMESPACE

    enum Theme {
            Light
        ,   Dark
    };

    static void registerType()
    {
        qmlRegisterUncreatableMetaObject(
                ApplicationTheme::staticMetaObject
            ,   "ApplicationTheme"
            ,   1, 0
            ,   "AppThemeEnum"
            ,   "Error: only enums"
        );
        qRegisterMetaType<ApplicationTheme::Theme>( "ApplicationTheme::Theme" );
    }

    Q_ENUM_NS( Theme )
};
