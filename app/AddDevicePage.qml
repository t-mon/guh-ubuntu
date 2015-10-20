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
import Ubuntu.Components 1.2
import Ubuntu.Components.ListItems 1.0
import Guh 1.0

Page {
    id: root
    title: i18n.tr("Add device")

    property var deviceClass: null

    ListView {
        id: paramList
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: bottomBar.top
        model: deviceClass.paramTypes
        delegate: ParamInput {
            paramType: model
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
            id: addButton
            anchors.centerIn: parent
            width: parent.width - units.gu(4)
            text: root.title
            onClicked: {
                console.log("Add device pressed with params: " + paramList.count)
                for (var i = 0; i < paramList.count; i ++) {
                    console.log("Param: " + paramList.itemAt(i).name + ": " + paramList.itemAt(i).value)
                }
            }
        }
    }
}



