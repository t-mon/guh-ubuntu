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
import Ubuntu.Components.ListItems 1.3
import Guh 1.0

Item {
    id: root

    property var device: null
    property var deviceClass: null

    Label {
        anchors.top: parent.top
        anchors.topMargin: units.gu(10)
        anchors.horizontalCenter: parent.horizontalCenter
        text: i18n.tr("This device has no states.")
        visible: deviceClass.stateTypes.count() === 0
    }

    Flickable {
        anchors.fill: parent
        anchors.topMargin: units.gu(2.5)

        contentHeight: statesColumn.height

        Column {
            id: statesColumn
            width: parent.width

            Repeater {
                id: stateRepeater
                model: root.deviceClass.stateTypes
                delegate: Item {
                    width: parent.width
                    height: units.gu(3)

                    property var stateValue: root.device.states.getState(model.id).value

                    Label {
                        anchors.left: parent.left
                        anchors.leftMargin: units.gu(2)
                        font.capitalization: Font.Capitalize
                        text: model.name
                    }

                    Label {
                        anchors.right: parent.right
                        anchors.rightMargin: units.gu(2)
                        text: {
                            if (model.unit === Types.UnitUnixTime) {
                                var date = new Date(stateValue * 1000)
                                print(stateValue + " = "+  date.toString("dd.MM.yyyy hh:mm"))
                                return date.toLocaleString(Qt.locale(),"dd.MM.yyyy hh:mm")
                            }
                            return stateValue + " " + model.unitString
                        }
                    }
                }
            }
        }
    }
}
