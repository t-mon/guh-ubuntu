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
import QtQuick.Layouts 1.1
import Ubuntu.Components 1.3
import Ubuntu.Components.Popups 1.3
import Ubuntu.Components.ListItems 1.3
import Guh 1.0

Page {
    id: root
    title: i18n.tr("Connection")

    property string websocketError
    property var popup

    head.actions:[
        Action {
            id: manualConnectionAction
            iconName: "edit"
            text: i18n.tr("Manual")
            onTriggered: popup = PopupUtils.open(manualConnectionComponent)
        },
        Action {
            id: reloadAction
            iconName: "reload"
            text: i18n.tr("Reload")
            onTriggered: Core.discovery.discover()
        }
    ]

    Column {
        anchors.fill: parent
        spacing: units.gu(1)


        ThinDivider {}
        Label {
            text: "  " + i18n.tr("Known connections")
            fontSize: "large"
            color: UbuntuColors.lightGrey
            anchors.horizontalCenter: parent.horizontalCenter
        }

        ThinDivider {}

        Repeater {
            id: connectionList
            model: Core.connections;
            delegate: ListItem {
                leadingActions: ListItemActions {
                    actions: [
                        Action {
                            iconName: "delete"
                            onTriggered: Core.connections.removeConnection(Core.connections.get(model.webSocketUrl))
                        }
                    ]
                }
                height: units.gu(5)
                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(2)
                    text: model.name + " (" + model.hostAddress + ")"
                }
                onClicked: Core.interface.connectGuh(model.webSocketUrl)
            }
        }

        ThinDivider {}

        Label {
            text: i18n.tr("Discovered connections")
            fontSize: "large"
            color: UbuntuColors.lightGrey
            anchors.horizontalCenter: parent.horizontalCenter
        }

        ThinDivider {}

        Repeater {
            id: discoveryList
            model: Core.discovery.discoveryModel;
            delegate: SingleValue {
                text: model.name + " (" + model.hostAddress + ")"
                value: model.version
                onClicked: Core.interface.connectGuh(model.webSocketUrl)
            }
        }

        Text {
            anchors.left: parent.left
            anchors.leftMargin: units.gu(2)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(2)
            visible: !Core.discovery.available
            wrapMode: Text.WordWrap
            color: "white"
            text: i18n.tr("UPnP discovery not available.\nMaybe another application is using the same discovery method (UDP port 1900).")
        }

        ActivityIndicator {
            anchors.horizontalCenter: parent.horizontalCenter
            id: activityIndicator
            running: Core.discovery.discovering
            visible: Core.discovery.discovering
        }
    }

    Connections {
        target: Core.interface
        onWebsocketError: {
            websocketError = errorString
            PopupUtils.open(connectionErrorComponent)
        }
    }

    Component {
        id: connectionErrorComponent
        Dialog {
            id: connectionErrorDialog
            title: i18n.tr("Connection error")
            text: i18n.tr(websocketError)

            ThinDivider { }

            Button {
                id: closeButton
                text: i18n.tr("Close")
                onClicked: PopupUtils.close(connectionErrorDialog)
            }
        }
    }

    Component {
        id: manualConnectionComponent
        Dialog {
            id: manualConnectionDialog
            title: i18n.tr("Manual connection")
            text: i18n.tr("Please enter the connection data:")

            ThinDivider { }

            ValueSelector {
                id: connectionTypeSelector
                text: i18n.tr("Connection type")
                values: ["ws", "wss"]
                selected: true
            }

            Label {
                text: "URL"
                color: "black"
            }

            TextField {
                id: urlTextField
                width: parent.width
                placeholderText: "guh.local"
            }

            Label {
                text: "Port"
                color: "black"
            }

            TextField {
                id: portTextField
                width: parent.width
                text: "4444"
                placeholderText: "4444"
            }

            ThinDivider { }

            Button {
                id: connectButton
                color: UbuntuColors.green
                text: i18n.tr("Connect")
                onClicked: {
                    var webSocketUrl = connectionTypeSelector.values[connectionTypeSelector.selectedIndex] + "://" + urlTextField.text + ":" + portTextField.text
                    Core.interface.connectGuh(webSocketUrl)
                    PopupUtils.close(manualConnectionDialog)
                }
            }

            Button {
                id: cancelButton
                text: i18n.tr("Cancel")
                onClicked: PopupUtils.close(manualConnectionDialog)
            }
        }
    }
}
