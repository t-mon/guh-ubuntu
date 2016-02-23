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

Item {
    id: root

    property var device: null
    property var deviceClass: null
    property bool waiting: false
    property string deviceError
    property int executeActionCommandId: 0

    Flickable {
        anchors.fill: parent
        contentHeight: actionsColumn.height

        ColumnLayout {
            id: actionsColumn
            anchors.left: parent.left
            anchors.right: parent.right

            spacing: units.gu(2)

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                fontSize: "large"
                color: UbuntuColors.lightGrey
                text: i18n.tr("Actions")
            }

            ThinDivider {}

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                visible: deviceClass.actionTypes.count() === 0
                text: i18n.tr("This device has no actions.")
            }

            Repeater {
                id: actionRepeater
                model: root.deviceClass.actionTypes
                delegate: ActionElement {
                    id: action
                    Layout.preferredHeight: implicitHeight
                    Layout.fillWidth: true

                    device: root.device
                    actionType: deviceClass.actionTypes.getActionType(model.id)

                    onExecuteAction: {
                        //console.log(model.id + " -> " + params)
                        waiting = true
                        root.executeActionCommandId = Core.jsonRpcClient.executeAction(device.id, model.id, params)
                    }
                }
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
            if (commandId == executeActionCommandId) {
                root.waiting = false
                if (!response['deviceError']) {
                    deviceError = i18n.tr("Interface error")
                } else {
                    deviceError = response['deviceError']
                }

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
            text: i18n.tr("Could not execute action:") + "\n" + deviceError

            Button {
                text: i18n.tr("Cancel")
                onClicked: PopupUtils.close(deviceErrorDialog)
            }
        }
    }
}
