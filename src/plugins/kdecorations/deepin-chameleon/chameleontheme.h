// SPDX-FileCopyrightText: 2018 - 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later
#ifndef CHAMELEONTHEME_H
#define CHAMELEONTHEME_H

#include <QColor>
#include <QMarginsF>
#include <QDir>
#include <QSettings>
#include <qwindowdefs.h>
#include <QPointF>
#include <QIcon>
#include <QMap>
#include <QSharedData>
#include <QLoggingCategory>

#include <NETWM>

Q_DECLARE_LOGGING_CATEGORY(CHAMELEON)

enum class UIWindowType {
    Normal = 1001,
    Dialog,
    Dock,
    PopupMenu,
    DropdownMenu,
    Tooltip,
};

class ChameleonTheme
{
public:
    enum ThemeType {
        Light,
        Dark,
        ThemeTypeCount
    };

    enum ThemeClass {
        Decoration = 0x0001,
        TitleBar = 0x0002
    };
    Q_DECLARE_FLAGS(ThemeClassFlags, ThemeClass)

    struct ThemeConfig
    {
        struct TitlebarBtn {
            QPointF pos;
            qint32 width;
            qint32 height;
            QIcon  btnIcon;
        };
        struct TitlebarFont {
            QString   fontFamily;
            int       fontSize;
            QString   textAlign;
            QColor    textColor;
        };
        struct TitlebarConfig {
            qreal     height;
            Qt::Edge  area;
            QColor    backgroundColor;

            TitlebarFont font;

            TitlebarBtn   menuBtn;
            TitlebarBtn   minimizeBtn;
            TitlebarBtn   maximizeBtn;
            TitlebarBtn   unmaximizeBtn;
            TitlebarBtn   closeBtn;
        };
        struct BorderConfig {
            qreal borderWidth;
            QColor borderColor;
        };
        struct RadiusConfig {
            qreal top_left;
            qreal top_right;
            qreal bottom_right;
            qreal bottom_left;
        };
        struct ShadowConfig {
            // qreal h_off;
            // qreal v_off;
            // qreal blur;
            // qreal spread;
            // QColor color;
            qreal shadowRadius;
            QPointF shadowOffset;
            QColor shadowColor;
        };

        qreal        version;
        QString      themeName;
        UIWindowType windowType;
        QString      windowDesc;


        //tilebar
        TitlebarConfig titlebarConfig;

        //border
        BorderConfig  borderConfig;

        //radius
        QPointF       radius;

        //shadow
        ShadowConfig  shadowConfig;

        //blur
        qreal         blur;

        //opacity
        qreal         opacity;

        QMarginsF     mouseInputAreaMargins;
    };

    struct ConfigGroup {
        ThemeConfig normal;
        ThemeConfig inactive;
    };

    // managed and window config
    struct ConfigGroupMap : public QSharedData {
        QMap<UIWindowType, ConfigGroup> managedConfigGroupMap;
        QMap<UIWindowType, ThemeConfig> unmanagedConfigMap;
    };

    typedef QSharedDataPointer< ConfigGroupMap > ConfigGroupMapPtr;

    static QPair<qreal, qreal> takePair(const QVariant &value, const QPair<qreal, qreal> defaultValue);
    static QMarginsF takeMargins(const QVariant &value, const QMarginsF &defaultValue);
    static QPointF takePos(const QVariant &value, const QPointF defaultValue);

    static ChameleonTheme *instance();
    static ConfigGroupMapPtr loadTheme(const QString &themeFullName, const QList<QDir> themeDirList);
    static ConfigGroupMapPtr loadTheme(ThemeType themeType, const QString &themeName, const QList<QDir> themeDirList);
    static ConfigGroupMapPtr getBaseConfig(ThemeType type, const QList<QDir> &themeDirList);
    static QString typeString(ThemeType type);
    static ThemeType typeFromString(const QString &type);

    QString theme() const;
    bool setTheme(const QString &themeFullName);
    bool setTheme(ThemeType type, const QString &theme);

    ConfigGroupMapPtr loadTheme(const QString &themeFullName);
    ConfigGroupMapPtr themeConfig() const;
    ConfigGroup* themeConfig(NET::WindowType windowType) const;
    ThemeConfig* themeUnmanagedConfig(NET::WindowType windowType) const;

protected:
    ChameleonTheme();
    ~ChameleonTheme();

private:
    QList<QDir> m_themeDirList;
    ThemeType m_type;
    QString m_theme;
    ConfigGroupMapPtr m_configGroupMap;
};

#endif // CHAMELEONTHEME_H
