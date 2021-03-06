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

Item {
    id: root

    implicitHeight: column.implicitHeight

    Column {
        id: column
        anchors.fill: parent
        anchors.margins: units.gu(1)
        spacing: units.gu(1)

        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            Label {
                id: nameLable
                Layout.alignment: Qt.AlignLeft
                //anchors.leftMargin: units.gu(2)
                font.capitalization: Font.Capitalize
                text: paramType.name
            }

            Switch {
                id: boolSwitch
                Layout.alignment: Qt.AlignRight
                //anchors.rightMargin: units.gu(2)
                checked: false
                onCheckedChanged: paramValue = checked
                Component.onCompleted: paramValue = checked
            }
        }

        ThinDivider { }
    }
}



