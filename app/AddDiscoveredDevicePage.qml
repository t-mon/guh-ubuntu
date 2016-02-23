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
    title: deviceClass.name

    property var deviceClass: null
    property var deviceDescriptors: []
    property var popup: null

    property int addId: 0
    property int pairPushButtonId: 0
    property int pairDisplayPinId: 0
    property int confirmPairingId: 0
    property int discoverId: 0

    property string deviceError
    property string pairingTransactionId
    property string message

    property bool waiting: false
    property bool discovering: false
    property bool pairing: false

    head.actions:[
        Action {
            id: manualConnectionAction
            iconName: "edit"
            text: i18n.tr("Manual")
            onTriggered: pageStack.push(Qt.resolvedUrl("AddDevicePage.qml"), { deviceClass: deviceClass })
        }
    ]

    Component.onCompleted: if (deviceClass.discoveryParamTypes.count() === 0) { discover() }

    Flickable {
        id: flickable
        anchors.fill: parent
        contentHeight: layout.height

        ColumnLayout {
            id: layout
            anchors.left: parent.left
            anchors.right: parent.right

            ColumnLayout {
                id: paramColumn
                anchors.left: parent.left
                anchors.right: parent.right

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    fontSize: "large"
                    visible: deviceClass.discoveryParamTypes.count() !== 0
                    color: UbuntuColors.lightGrey
                    text: i18n.tr("Parameters")
                }

                ThinDivider { }

                Repeater {
                    id: paramRepeater
                    model: deviceClass.discoveryParamTypes
                    delegate: ParamInput {
                        Layout.preferredHeight: implicitHeight
                        Layout.fillWidth: true
                        paramType: model
                    }
                }

                ThinDivider { }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    fontSize: "large"
                    color: UbuntuColors.lightGrey
                    text: i18n.tr("Search results")
                }

                ThinDivider { }

                ActivityIndicator {
                    id: searchingIndicator
                    anchors.horizontalCenter: parent.horizontalCenter
                    running: root.discovering
                    visible: root.discovering
                }

                Repeater {
                    id: deviceDescriptorRepeater
                    model: deviceDescriptors
                    visible: !root.discovering
                    delegate: SingleValue {
                        text: deviceDescriptors[index]['title']
                        value: deviceDescriptors[index]['description']
                        onClicked: {
                            switch (deviceClass.setupMethod) {
                            case DeviceClass.SetupMethodJustAdd:
                                console.log("SetupMethod: just add")
                                waiting = true
                                addId = Core.jsonRpcClient.addDiscoveredDevice(deviceClass.id, deviceDescriptors[index]['id'])
                                break
                            case DeviceClass.SetupMethodDisplayPin:
                                console.log("SetupMethod: display pin")
                                pairDisplayPinId = Core.jsonRpcClient.pairDevice(deviceClass.id, deviceDescriptors[index]['id'])
                                break
                            case DeviceClass.SetupMethodPushButton:
                                console.log("SetupMethod: push button")
                                pairPushButtonId = Core.jsonRpcClient.pairDevice(deviceClass.id, deviceDescriptors[index]['id'])
                                break
                            case DeviceClass.SetupMethodEnterPin:
                                console.log("SetupMethod: enter pin")
                                break
                            }
                        }
                    }
                }
            }

            Button {
                id: discoverButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: discovering ? i18n.tr("Searching...") : i18n.tr("Discover")
                onClicked: if (!discovering) { discover() }
            }
        }
    }

    WaitingOverlay {
        anchors.fill: parent
        visible: root.waiting
        enabled: root.waiting
    }

    Connections {
        target: Core.jsonRpcClient
        onResponseReceived: {
            if (commandId == discoverId) {
                root.discovering = false
                root.deviceDescriptors = response['deviceDescriptors']
            } else if (commandId == addId) {
                root.waiting = false
                deviceError = response['deviceError']
                if (deviceError !== "DeviceErrorNoError") {
                    popup = PopupUtils.open(deviceErrorComponent)
                } else {
                    pageStack.clear()
                    pageStack.push(Qt.resolvedUrl("DevicesPage.qml"))
                }
            } else if (commandId == pairPushButtonId) {
                root.waiting = false
                deviceError = response['deviceError']
                if (deviceError !== "DeviceErrorNoError") {
                    popup = PopupUtils.open(deviceErrorComponent)
                } else {
                    message = response['displayMessage']
                    pairingTransactionId = response['pairingTransactionId']
                    popup = PopupUtils.open(pushButtonComponent)
                }
            } else if (commandId == pairDisplayPinId) {
                root.waiting = false
                deviceError = response['deviceError']
                if (deviceError !== "DeviceErrorNoError") {
                    popup = PopupUtils.open(deviceErrorComponent)
                } else {
                    message = response['displayMessage']
                    pairingTransactionId = response['pairingTransactionId']
                    popup = PopupUtils.open(displayPinComponent)
                }
            } else if (commandId == confirmPairingId) {
                pairing = false
                deviceError = response['deviceError']
                if (deviceError !== "DeviceErrorNoError") {
                    deviceDescriptors = []
                    PopupUtils.close(popup)
                    popup = PopupUtils.open(deviceErrorComponent)
                } else {
                    PopupUtils.close(popup)
                    deviceDescriptors = []
                    pageStack.clear()
                    pageStack.push(Qt.resolvedUrl("DevicesPage.qml"))
                }
            }
        }
    }


    function discover() {
        deviceDescriptors = []
        var deviceParams = [];
        for (var i = 0; i < paramRepeater.count; i ++) {
            deviceParams.push({"name": paramRepeater.itemAt(i).paramName, "value": paramRepeater.itemAt(i).paramValue})
        }
        root.discovering = true
        root.discoverId = Core.jsonRpcClient.discoverDevices(deviceClass.id, deviceParams)
    }


    Component {
        id: pushButtonComponent
        Dialog {
            id: pushButtonDialog
            title: i18n.tr("Push button setup")
            text: message

            ActivityIndicator { running: pairing }

            Button {
                text: i18n.tr("Ok")
                onClicked: {
                    pairing = true
                    confirmPairingId = Core.jsonRpcClient.confirmPairing(pairingTransactionId)
                }
            }

            Button {
                text: i18n.tr("Cancel")
                onClicked: {
                    deviceDescriptors = []
                    PopupUtils.close(pushButtonDialog)
                }
            }
        }
    }

    Component {
        id: displayPinComponent
        Dialog {
            id: displayPinDialog
            title: i18n.tr("Display pin setup")
            text: message

            TextField { id: secretText }
            ActivityIndicator { running: pairing }

            Button {
                text: i18n.tr("Ok")
                color: "green"
                onClicked: {
                    pairing = true
                    confirmPairingId = Core.jsonRpcClient.confirmPairing(pairingTransactionId, secretText.text)
                }
            }

            Button {
                text: i18n.tr("Cancel")
                onClicked: {
                    deviceDescriptors = []
                    PopupUtils.close(pushButtonDialog)
                }
            }
        }
    }

    Component {
        id: deviceErrorComponent
        Dialog {
            id: deviceErrorDialog
            title: i18n.tr("Error occured")
            text: i18n.tr("Could not add device:") + "\n" + deviceError
            Button {
                text: i18n.tr("Cancel")
                onClicked: PopupUtils.close(deviceErrorDialog)
            }
        }
    }
}
