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

import "inputTypes"

Loader {
    id: root

    width: item ? item.implicitWidth : 0
    height: item ? item.implicitHeight : 0

    property var paramType: null
    property var paramName: paramType.name
    property var paramValue: paramType.defaultValue

    source: {
        var filename;
        if (paramType.type === "String" && paramType.allowedValues.length === 0) {
            filename = "inputTypes/StringInputComponent.qml";
        } else if ( paramType.allowedValues.length > 0) {
            filename = "inputTypes/NumberInputComponent.qml";
        } else if (paramType.type === "Int" || paramType.type === "Double" || paramType.type === "Uint") {
            if (paramType.allowedValues.length === 0) {
                filename = "inputTypes/NumberInputComponent.qml";
            }
        } else {
            filename = "inputTypes/BoolInputComponent.qml";
        }
        return Qt.resolvedUrl(filename);
    }
}

