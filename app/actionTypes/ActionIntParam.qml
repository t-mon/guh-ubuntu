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
    property bool changedFromState: false

    signal executeAction(var params);

    Column {
        id: column
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: units.gu(1)

        Label {
            id: nameLable
            anchors.left: parent.left
            anchors.leftMargin: units.gu(2)
            font.capitalization: Font.Capitalize
            text: paramType.name + " ( " + Math.round(slider.value) + " " + paramType.unitString + " )"
        }

        Slider {
            id: slider
            anchors.left: parent.left
            anchors.leftMargin: units.gu(2)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(2)
            maximumValue: root.paramType.maxValue
            minimumValue: root.paramType.minValue
            value: actionState.value
            onValueChanged: {
                if (!changedFromState) {
                    root.executeAction([ { "name": paramType.name, "value": Math.round(slider.value) } ])
                }
                changedFromState = false
            }

            Connections {
                target: actionState
                onValueChanged: {
                    console.log("State changed " + actionState.value)
                    changedFromState = true
                    slider.value = actionState.value
                }
            }
        }
    }
}

