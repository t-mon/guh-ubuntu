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
import Guh 1.0

Item {
    id: root

    implicitHeight: column.implicitHeight

    property var paramType: actionType.paramTypes.get(0)

    signal executeAction(var params);

    function capitalize(s) {
        return s && s[0].toUpperCase() + s.slice(1);
    }

    Column {
        id: column
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: units.gu(1)

        Button {
            id: button
            text: actionState.value ? capitalize(paramType.name) + " off" : capitalize(paramType.name) + " on"
            anchors.left: parent.left
            anchors.leftMargin: units.gu(6)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(6)
            onClicked: root.executeAction([ { "name": paramType.name, "value": !actionState.value } ])

            Connections {
                target: actionState
                onValueChanged: {
                    console.log("State changed " + actionState.value)
                }
            }
        }
    }
}

