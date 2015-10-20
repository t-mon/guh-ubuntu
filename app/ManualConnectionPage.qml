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
    title: i18n.tr("Manual Connection")

    Column {
        anchors.fill: parent
        anchors.margins: units.gu(2)
        spacing: units.gu(1)

        Label {
            text: i18n.tr("Please enter the websocket URL of guh")
        }

        TextField {
            id: urlTextField
            width: parent.width
            placeholderText: "ws://webdm.local:4444"
        }

        Button {
            id: connectButton
            width: parent.width
            color: UbuntuColors.green
            text: i18n.tr("Connect")
            onClicked: Core.interface.connectGuh(urlTextField.text)
        }
    }

}

