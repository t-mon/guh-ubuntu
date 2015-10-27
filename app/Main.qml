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

import QtQuick 2.4
import Ubuntu.Components 1.3
import Ubuntu.Components.ListItems 1.3
import Guh 1.0

MainView {
    id: app
    objectName: "mainView"
    applicationName: "guh-ubuntu.stuerz-simon"
    automaticOrientation: false

    width: units.gu(40)
    height: units.gu(70)

    property string orientation: width > height ? "landscape" : "portrait"

    Component.onCompleted: {
        i18n.domain = "guh-ubuntu.stuerz-simon"
        Core.discovery.discover()
        Theme.name = "Ubuntu.Components.Themes.SuruDark"
    }

    PageStack {
        id: pageStack
        anchors.fill: parent
        Component.onCompleted: push(Qt.resolvedUrl("ConnectionPage.qml"))

        Connections {
            target: Core
            onConnectedChanged: {
                if (Core.connected) {
                    console.log("connected")
                    pageStack.clear()
                    pageStack.push(Qt.resolvedUrl("MainMenuPage.qml"))
                } else {
                    console.log("disconnected")
                    Core.discovery.discover()
                    pageStack.clear()
                    pageStack.push(Qt.resolvedUrl("ConnectionPage.qml"))
                }
            }
        }
    }
}

