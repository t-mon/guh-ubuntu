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
    title: i18n.tr("Discover devices")

    property var deviceClass: null
    property var deviceDescriptors: []
    property int addId: 0
    property int discoverId: 0
    property string deviceError
    property bool waiting: false

    Component.onCompleted: {
        if (deviceClass.discoveryParamTypes.paramCount === 0) {
            discover()
        }
    }

    function discover() {
        root.deviceDescriptors = []
        print("Discover devices: " + paramRepeater.count)
        var deviceParams = [];
        for (var i = 0; i < paramRepeater.count; i ++) {
            deviceParams.push({"name": paramRepeater.itemAt(i).paramName, "value": paramRepeater.itemAt(i).paramValue})
            print("   " + paramRepeater.itemAt(i).paramName + ": " + paramRepeater.itemAt(i).paramValue)
        }
        root.waiting = true
        root.discoverId = Core.jsonRpcClient.discoverDevices(deviceClass.id, deviceParams)
    }

    Column {
        id: paramColumn
        anchors.fill: parent
        Repeater {
            id: paramRepeater
            model: deviceClass.discoveryParamTypes
            delegate: ParamInput {
                paramType: model
            }
        }

        Repeater {
            id: deviceDescriptorRepeater
            model: deviceDescriptors
            delegate: SingleValue {
                text: deviceDescriptors[index]['title']
                value: deviceDescriptors[index]['description']
                onClicked: {
                    root.addId = Core.jsonRpcClient.addDiscoveredDevice(deviceClass.id, deviceDescriptors[index]['id'])
                }
            }
        }
    }

    Rectangle {
        id: bottomBar
        color: Theme.palette.normal.background
        height: units.gu(6)
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Button {
            id: discoverButton
            anchors.centerIn: parent
            width: parent.width - units.gu(4)
            text: root.title
            onClicked: discover()
        }
    }

    Connections {
        target: Core.jsonRpcClient
        onResponseReceived: {
            if (commandId == discoverId) {
                root.waiting = false
                root.deviceDescriptors = response['deviceDescriptors']
            }
            if (commandId == addId) {
                root.waiting = false
                deviceError = response['deviceError']
                if (deviceError !== "DeviceErrorNoError") {
                    PopupUtils.open(deviceErrorComponent)
                } else {
                    pageStack.pop()
                    pageStack.pop()
                    pageStack.pop()
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
