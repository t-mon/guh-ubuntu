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

import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import Guh 1.0

Page {
    id: root
    title: i18n.tr("Connection")

    head.actions: Action {
        id: reloadAction
        iconName: "reload"
        text: i18n.tr("Reload")
        onTriggered: Core.discovery.discover()
    }

    ListView {
        id: discoveryList
        anchors.fill: parent
        model: Core.discovery.discoveryModel;
        delegate: ListItem.SingleValue {
            text: model.name + " (" + model.hostAddress + ")"
            value: model.version
            onClicked: {
                Core.interface.connectGuh(model.hostAddress)
                selected = !selected
            }
        }

        ActivityIndicator {
            anchors.centerIn: parent
            id: activityIndicator
            running: Core.discovery.discovering
        }
    }
}
