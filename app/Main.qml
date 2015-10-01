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

import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import Guh 1.0

MainView {
    id: app
    objectName: "mainView"
    applicationName: "guh-ubuntu.stuerz-simon"
    automaticOrientation: false
    useDeprecatedToolbar: false

    width: units.gu(40)
    height: units.gu(70)

    property string orientation: width > height ? "landscape" : "portrait"

    Component.onCompleted: {
        i18n.domain = "guh-ubuntu.stuerz-simon"
        Core.discovery.discover()
    }

    PageStack {
        id: pageStack
        anchors.fill: parent
        Component.onCompleted: push(Qt.resolvedUrl("DiscoveryPage.qml"))

//        MainMenuPage {
//            id: mainMenuPage
//            visible: false
//        }

//        DiscoveryPage {
//            id: discoveryPage
//            visible: false
//        }

//        VendorsPage {
//            id: vendorsPage
//            visible: false
//        }

//        DeviceClassesPage {
//            id: deviceClassesPage
//            visible: false
//        }

        Connections {
            target: Core
            onConnectedChanged: {
                if (Core.connected) {
                    console.log("connected")
                    pageStack.pop()
                    pageStack.push(Qt.resolvedUrl("MainMenuPage.qml"))
                } else {
                    console.log("disconnected")
                    Core.discovery.discover()
                    pageStack.push(discoveryPage)
                }
            }
        }
    }



}

