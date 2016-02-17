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
import Ubuntu.Components.ListItems 1.3
import Guh 1.0

import "actionTypes"

Item {
    id: root

    property var device: null
    property var actionType: null
    property var actionState: device.hasState(actionType.id) ? device.states.getState(actionType.id) : null

    signal executeAction(var actionTypeId, var params)

    implicitWidth: loader.item ? loader.item.implicitWidth : 0
    implicitHeight: loader.item ? loader.item.implicitHeight : 0

    Loader {
        id: loader
        anchors.fill: parent
        source: {
            var filename;

            if (actionType.paramTypes.count() === 0) {
                filename = "actionTypes/ActionWithoutParams.qml";
            } else if (actionType.paramTypes.count() === 1) {
                var paramType = actionType.paramTypes.get(0)
                if (paramType.type === "Int" && paramType.minValue !== null && paramType.maxValue !== null) {
                    filename = "actionTypes/ActionIntParam.qml";
                } else if (paramType.type === "Bool") {
                    filename = "actionTypes/ActionBoolParam.qml";
                }
            } else {
                filename = "actionTypes/ActionWithoutParams.qml";
            }

            return Qt.resolvedUrl(filename);
        }

        Connections {
            target: loader.item
            onExecuteAction: root.executeAction(actionType.id, params)
        }
    }
}

