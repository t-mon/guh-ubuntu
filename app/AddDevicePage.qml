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
    title: i18n.tr("Add device")

    property var deviceClass: null
    property int id
    property string deviceError
    property bool waiting: false

    Flickable {
        id: flickable
        anchors.fill: parent
        contentHeight: paramColumn.height

        ColumnLayout {
            id: paramColumn
            anchors.left: parent.left
            anchors.right: parent.right
            Layout.fillWidth: true
            Layout.fillHeight: true
            Repeater {
                id: paramRepeater
                anchors.left: parent.left
                anchors.right: parent.right
                model: deviceClass.paramTypes
                delegate: ParamInput {
                    paramType: model
                }
            }

            ThinDivider {}

            Button {
                id: addButton
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - units.gu(4)
                text: root.title
                onClicked: {
                    print("Add device pressed with params: " + paramRepeater.count)
                    var deviceParams = [];
                    for (var i = 0; i < paramRepeater.count; i ++) {
                        deviceParams.push({"name": paramRepeater.itemAt(i).paramName, "value": paramRepeater.itemAt(i).paramValue})
                        print("   " + paramRepeater.itemAt(i).paramName + ": " + paramRepeater.itemAt(i).paramValue)
                    }
                    root.waiting = true
                    root.id = Core.jsonRpcClient.addDevice(deviceClass.id, deviceParams)
                }
            }
        }
    }

    Connections {
        target: Core.jsonRpcClient
        onResponseReceived: {
            if (commandId == id) {
                root.waiting = false
                deviceError = response['deviceError']
                if (deviceError !== "DeviceErrorNoError") {
                    PopupUtils.open(deviceErrorComponent)
                } else {
                    pageStack.clear()
                    pageStack.push(Qt.resolvedUrl("MainMenuPage.qml"))
                }
            }
        }
    }

    Component {
        id: deviceErrorComponent
        Dialog {
            id: deviceErrorDialog
            title: i18n.tr("Error occured")
            text: "Could not add device\n" + deviceError

            Button {
                text: i18n.tr("Cancel")
                onClicked: PopupUtils.close(deviceErrorDialog)
            }
        }
    }
}
