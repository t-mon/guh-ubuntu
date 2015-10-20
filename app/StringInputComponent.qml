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

Component {
    id: root

    Rectangle {
        id: mainRectangle
        anchors.fill: parent
        color: "transparent"

        Column {
            anchors.fill: parent
            anchors.margins: units.gu(1)
            spacing: units.gu(1)

            Label {
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                font.capitalization: Font.Capitalize
                text: paramType.name
            }

            Loader {
                id: inputLoader

                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                anchors.right: parent.right
                anchors.rightMargin: units.gu(2)

                sourceComponent: textInputLine
            }

            Component {
                id: textInputLine
                TextField {
                    id: textField
                    inputMask: {
                        if (paramType.inputType == Types.InputTypeIPv4Address)
                            return "000.000.000.000;_"
                        else if (paramType.inputType == Types.InputTypeMacAddress)
                            return "HH:HH:HH:HH:HH:HH;_"
                        else
                            return ""
                    }
                    echoMode: paramType.inputType == Types.InputTypePassword ? TextInput.Password : TextInput.Normal
                    onTextChanged: {
                        value =  textField.text
                    }
                }
            }
        }
    }
}

