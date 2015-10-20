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


Standard {
    id: root
    property var paramType: null
    property var name: paramType.name
    property var value: null

    height: {
        if (inputLoader.sourceComponent == stringInput)
            return units.gu(10)
        else if (inputLoader.sourceComponent == allowedValuesInput)
            return units.gu(6)
        else if (inputLoader.sourceComponent == numberInput)
            return units.gu(6)
        else
            return units.gu(6)
    }

    AllowedValuesInputComponent {
        id: allowedValuesInput
    }

    StringInputComponent {
        id: stringInput
    }

    NumberInputComponent {
        id: numberInput
    }

    BoolInputComponent {
        id: boolInput
    }

    Loader {
        id: inputLoader
        anchors.fill: parent
        sourceComponent: paramType.type == "QString" && paramType.allowedValues.length == 0
                         ? stringInput : paramType.allowedValues.length > 0
                           ? allowedValuesInput : (paramType.type == "int" ||
                                                   paramType.type == "double" ||
                                                   paramType.type == "uint") &&
                             paramType.allowedValues.length == 0 ? numberInput : boolInput
    }
}
