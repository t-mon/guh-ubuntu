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

import "inputTypes"

Item {
    id: root
    property var paramType: null
    property var paramName: paramType.name
    property var paramValue: paramType.defaultValue

    width: parent.width
    height: inputLoader.implicitHeight

    Component {
        id: allowedValuesInput
        AllowedValuesInputComponent { }
    }

    Component {
        id: stringInput
        StringInputComponent { }
    }

    Component {
        id: numberInput
        NumberInputComponent { }
    }

    Component {
        id: boolInput
        BoolInputComponent { }
    }

    Loader {
        id: inputLoader
        width: parent.width
        height: item.implicitHeight
        sourceComponent: {
            if (paramType.type === "QString" && paramType.allowedValues.length === 0) {
                return stringInput
            } else if ( paramType.allowedValues.length > 0) {
                return allowedValuesInput
            } else if (paramType.type === "int" || paramType.type === "double" || paramType.type === "uint") {
                if (paramType.allowedValues.length === 0) {
                    return numberInput
                }
            } else {
                return boolInput
            }
        }
    }
}
