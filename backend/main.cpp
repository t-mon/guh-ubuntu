/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of guh-ubuntu.                                       *
 *                                                                         *
 *  guh-ubuntu is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  guh-ubuntu is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with guh-ubuntu. If not, see <http://www.gnu.org/licenses/>.     *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QCommandLineParser>
#include <QtQml>
#include <QtQml/QQmlContext>

#include "core.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationVersion("0.1.0");

    qmlRegisterSingletonType<Core>("Guh", 1, 0, "Core", Core::qmlInstance);
    qmlRegisterUncreatableType<DeviceManager>("Guh", 1, 0, "DeviceManager", "Can't create this in QML. Get it from the Core.");
    qmlRegisterUncreatableType<GuhInterface>("Guh", 1, 0, "GuhInterface", "Can't create this in QML. Get it from the Core.");
    qmlRegisterUncreatableType<UpnpDiscovery>("Guh", 1, 0, "UpnpDiscovery", "Can't create this in QML. Get it from the Core.");
    qmlRegisterUncreatableType<UpnpDiscoveryModel>("Guh", 1, 0, "UpnpDiscoveryModel", "Can't create this in QML. Get it from the Core.");
    qmlRegisterUncreatableType<VendorModel>("Guh", 1, 0, "VendorModel", "Can't create this in QML. Get it from the DeviceManager.");

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:///app/Main.qml")));
    view.engine()->rootContext()->setContextProperty("versionString", app.applicationVersion());
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
