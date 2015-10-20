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
import Ubuntu.Components 1.2
import Ubuntu.Components.ListItems 1.0
import Guh 1.0

Page {
    id: root
    title: i18n.tr("Devices")

    head.actions: Action {
        id: addDeviceAction
        iconName: "add"
        text: i18n.tr("Add device")
        onTriggered: pageStack.push(Qt.resolvedUrl("VendorsPage.qml"))
    }

    ListView {
        id: deviceList
        anchors.fill: parent
        model: Core.deviceManager.devices
        clip: true
        delegate: ListItem {
            id: deviceItem
            leadingActions: ListItemActions {
                actions: [
                    Action {
                        iconName: "delete"
                        onTriggered: Core.deviceManager.removeDevice(model.id)
                    }
                ]
            }
            trailingActions: ListItemActions {
                actions: [
                    Action {
                        iconName: "info"
                        onTriggered: pageStack.push(Qt.resolvedUrl("DeviceParamPage.qml"), {
                                                        deviceName: model.name,
                                                        params: model.params
                                                    })
                    }
                ]
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)

                Label {
                    text: model.name
                    fontSize: "large"
                }
                Label {
                    text: {
                        var vendorId = Core.deviceManager.deviceClasses.getDeviceClass(model.deviceClassId).vendorId
                        Core.deviceManager.vendors.getVendor(vendorId).name
                    }
                }
            }

            onClicked: {
                var d = deviceList.model.get(index)
                console.log("device details for " + d.name)
                pageStack.push(Qt.resolvedUrl("DeviceDetailsPage.qml"),
                               { device: d })
            }
        }
    }
}

