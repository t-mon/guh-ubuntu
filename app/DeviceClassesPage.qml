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

Page {
    id: root
    title: Core.deviceManager.vendors.getVendor(Core.deviceManager.deviceClassesProxy.vendorId).name

    UbuntuListView {
        id: deviceClassesList
        anchors.fill: parent
        model: Core.deviceManager.deviceClassesProxy
        delegate: Standard {
            text: model.name
            progression: true
            onClicked: {
                var dc = Core.deviceManager.deviceClasses.getDeviceClass(model.id)
                if (dc.createMethods.indexOf("CreateMethodDiscovery") !== -1) {
                    console.log("CreateMethod: discovery")
                    pageStack.push(Qt.resolvedUrl("AddDiscoveredDevicePage.qml"), { deviceClass: dc })
                } else {
                    console.log("CreateMethod: user")
                    pageStack.push(Qt.resolvedUrl("AddDevicePage.qml"), { deviceClass: dc })
                }
            }
        }
    }
}
