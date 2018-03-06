/*
 * This file is part of Liri Browser
 *
 * Copyright (C) 2018 Tim Süberkrüb <dev@timsueberkrueb.io>
 *
 * $BEGIN_LICENSE:GPL3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
*/

#ifndef BROWSERAPPLICATION_H
#define BROWSERAPPLICATION_H

#include <QObject>
#include <QLocale>
#include <QTranslator>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>
#include <QLocalServer>
#include <QLocalSocket>

#include "../core/models/tabsmodel.h"
#include "../core/models/tab.h"
#include "../core/models/downloadsmodel.h"
#include "../core/settings/settings.h"
#include "../core/utils/darkthemetimer.h"
#include "browserapplication.h"

const QString LOCAL_SOCKET_PATH = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/io.liri.Browser.sock";

class BrowserApplication : public QObject
{
    Q_OBJECT
public:
    explicit BrowserApplication(QObject *parent = nullptr);

    static void loadTranslations()
    {
        #ifndef QT_NO_TRANSLATION
            QString locale = QLocale::system().name();

            // Find the translations directory
            const QString path = QLatin1String("liri-browser/translations");
            const QString translationsDir =
                QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                       path,
                                       QStandardPaths::LocateDirectory);

            // Load translations
            QTranslator *appTranslator = new QTranslator(qGuiApp);
            if (appTranslator->load(QStringLiteral("%1/browser_%3").arg(translationsDir, locale))) {
                QCoreApplication::installTranslator(appTranslator);
            } else if (locale == QLatin1String("C") ||
                        locale.startsWith(QLatin1String("en"))) {
                // English is the default, it's translated anyway
                delete appTranslator;
            }
        #endif
    }

    bool checkForRunningInstance();
    bool loadOrForward();
    void loadUI();

private: // methods
    void onSocketConnection();

private: // members
    QQmlApplicationEngine m_engine;
    Settings m_settings;
    DarkThemeTimer m_darkThemeTimer;
    QLocalSocket m_localSocket;
    QLocalServer m_localServer;
    bool m_ipcEnabled = true;
};

#endif // BROWSERAPPLICATION_H
