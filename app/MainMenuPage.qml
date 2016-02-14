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
import Ubuntu.Components.Popups 1.3
import Ubuntu.Components.ListItems 1.3
import Guh 1.0

Page {
    id: root
    title: i18n.tr("Devices")

    property string deviceError
    property int id

    head.actions: Action {
        id: addDeviceAction
        iconName: "add"
        text: i18n.tr("Add device")
        onTriggered: pageStack.push(Qt.resolvedUrl("VendorsPage.qml"))
    }

    ListView {
        id: deviceList
        anchors.fill: parent
        model: Core.deviceManager.devicesProxy
        clip: true
        delegate: ListItem {
            id: deviceItem
            leadingActions: ListItemActions {
                actions: [
                    Action {
                        iconName: "delete"
                        onTriggered: PopupUtils.open(removeComponent)
                    }
                ]
            }

            trailingActions: ListItemActions {
                actions: [
                    Action {
                        iconName: "info"
                        onTriggered: PopupUtils.open(deviceParamsComponent)
                    }
                ]
            }

            Component {
                id: removeComponent
                Dialog {
                    id: removeDialog
                    title: i18n.tr("Remove device")
                    text: i18n.tr("Are you sure you want to remove") + " \"" + model.name + "\"?"

                    property int commandId

                    ThinDivider {}

                    Button {
                        text: i18n.tr("Remove")
                        color: UbuntuColors.red
                        onClicked: {
                            root.id = Core.jsonRpcClient.removeDevice(model.id)
                            PopupUtils.close(removeDialog)
                        }
                    }

                    Button {
                        text: i18n.tr("Cancel")
                        onClicked: PopupUtils.close(removeDialog)
                    }
                }
            }

            Component {
                id: deviceParamsComponent
                Dialog {
                    id: deviceParamsDialog
                    title: i18n.tr("Device parameters")

                    Flickable {
                        width: parent.width
                        height: units.gu(35)

                        contentHeight: paramsColumn.height

                        Column {
                            id: paramsColumn
                            width: parent.width
                            Repeater {
                                id: paramRepeater
                                model: deviceList.model.devices.get(index).params
                                delegate: SingleValue {
                                    width: parent.width
                                    height: units.gu(5)

                                    text: model.name
                                    value: model.value
                                }
                            }
                        }
                    }

                    Button {
                        text: i18n.tr("Close")
                        onClicked: PopupUtils.close(deviceParamsDialog)
                    }
                }
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                text: model.name
            }

            Label {
                anchors.right: parent.right
                anchors.rightMargin: units.gu(2)
                anchors.top: parent.top
                anchors.topMargin: units.gu(1)
                text: model.deviceName
                color: UbuntuColors.lightGrey
            }

            Label {
                anchors.right: parent.right
                anchors.rightMargin: units.gu(2)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: units.gu(1)
                text: {
                    var vendorId = Core.deviceManager.deviceClasses.getDeviceClass(model.deviceClassId).vendorId
                    Core.deviceManager.vendors.getVendor(vendorId).name
                }
                color: UbuntuColors.lightGrey
            }

            onClicked: {
                var d = Core.deviceManager.devices.getDevice(model.id)
                pageStack.push(Qt.resolvedUrl("DeviceDetailsPage.qml"), { device: d } )
            }
        }

        add: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 300 }
            NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 300 }
        }

        remove:  Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0; duration: 300 }
            NumberAnimation { property: "scale"; from: 1.0; to: 0; duration: 300 }
        }
    }

    Connections {
        target: Core.jsonRpcClient
        onResponseReceived: {
            if (commandId == root.id) {
                deviceError = response['deviceError']
                if (deviceError !== "DeviceErrorNoError") {
                    PopupUtils.open(deviceErrorComponent)
                }
            }
        }
    }

    Component {
        id: deviceErrorComponent
        Dialog {
            id: deviceErrorDialog
            title: i18n.tr("Error occured")
            text: i18n.tr("Could not remove device") + "\n" + deviceError

            Button {
                text: i18n.tr("Cancel")
                onClicked: PopupUtils.close(deviceErrorDialog)
            }
        }
    }

}

